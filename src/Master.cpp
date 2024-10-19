#include "Master.h"
#include "Log.h"
#include <iostream>
#include <cmath>
#include <string>
#include <unordered_map>
#include <map>
#include <ctime>
#include <iomanip>
#include <algorithm>

LOG_REGISTER_MODULE("Master");

float recursos_necesarios(float demanda, float SINR)
{
  float factor = 180 * pow(10, 3) / 1e6;
  float capacidad = log2(1 + SINR);
  float recursos = demanda / (factor * capacidad);
  return recursos;
}

double throughput(int recursosAsignados, float SINR)
{
  float factor = 180 * pow(10, 3) / 1e6;
  auto thput = recursosAsignados * factor * log2(1 + SINR);
  return thput;
}

Master::Master(const json &j)
{
  BEG;
  m_data = j;
  END;
}

void Master::Init()
{
  BEG;
  INFO ("Lading FS...");
  auto fs = m_data["FS"];
  INFO ("Lading BS...");
  for (auto &item : m_data["BS"])
  {
    m_mapResources[item["id"]] = item["resources"];
    m_mapPhyBs.insert({item["id"], PhyBaseStation(item["resources"])});
  }

  std::string BSv = "BSv", Serv = "Serv", BSvNombre, ServNombre;
  INFO ("Lading Zones...");
  for (auto &x : m_data["Zones"])
  {
    m_mapBS.emplace(x["id"], x["BS"]);
    m_mapZone.insert({x["id"], Zone(x["BS"])});
    m_mapSignalRange.emplace(x["id"], x["SignalRange"]);
    m_mapInterferenceRange.emplace(x["id"], x["InterferenceRange"]);
    m_mapTargetThput.emplace(x["id"], x["TargetThroughput"]);
    m_mapMinThput.emplace(x["id"], x["MinThroughput"]);
    m_mapGlobalService.emplace(x["id"], x["GlobalService"]);
    m_mapZone.at(x["id"]).SaveThroughputMin(x["MinThroughput"]);
  }

  int j = 1;
  for (auto &i : m_mapBS)
  {
    if (j < 10)
    {
      ServNombre = Serv + "0" + std::to_string(j);
    }
    else
    {
      ServNombre = Serv + std::to_string(j);
    }
    m_mapService.insert({ServNombre, Service()});
    m_mapService.at(ServNombre).SetGlobalService(m_mapGlobalService.at(i.first));
    m_mapService.at(ServNombre).SetZone(i.first);

    for (auto &iter : m_mapPhyBs)
    {
      for (auto y = 0u; y < i.second.size(); y++)
      {
        if (iter.first == i.second[y])
        {
          m_mapPhyBs.at(iter.first).AddService(ServNombre);
        }
      }
    }
    j++;
  }

  int c = 1, cont;
  std::vector<std::string> servBSf;
  for (auto &i : m_mapResources)
  {
    cont = 0;
    servBSf = m_mapPhyBs.at(i.first).GetServices();

    for (auto &j : m_mapBS)
    {
      for (auto z = 0u; z < j.second.size(); z++)
      {
        if (i.first == j.second[z])
        {
          if (c < 10)
          {
            BSvNombre = BSv + "0" + std::to_string(c);
          }
          else
          {
            BSvNombre = BSv + std::to_string(c);
          }
          c++;
          m_mapVirtBs.insert({BSvNombre, VirtualBaseStation()}); 
          m_mapZone.at(j.first).AssignBSv(BSvNombre);
          m_mapVirtBs.at(BSvNombre).SetZone(j.first);
          m_mapVirtBs.at(BSvNombre).SetService(servBSf[cont]);
          m_mapVirtBs.at(BSvNombre).SetCentralizationLevel(fs);
          m_mapPhyBs.at(i.first).AddVirtualBs(BSvNombre);
          m_mapVirtBs.at(BSvNombre).SetPhysicalBs(i.first);
          cont++;
        }
      }
    }
  }

  INFO ("Selecting algorithm... ", m_data["Algorithm"]); 
  for (auto &item : m_data["Algorithm"])
  {
    if (item["id"] == "Algorithm1")
    {
      m_algo = new Algorithm1(j);
    }
    else if (item["id"] == "Algorithm2")
    {
      m_algo = new Algorithm2(j);
    }
    else if (item["id"] == "Algorithm3")
    {
      m_algo = new Algorithm3(m_data);
    }
    else if (item["id"] == "Algorithm4")
    {
      m_algo = new Algorithm4(m_data);
    }
    else if (item["id"] == "Algorithm5")
    {
      m_algo = new Algorithm5(m_data);
    } else {
      MSG_ASSERT (false, "Bad algorithm",  m_data["Algorithm"]);
    }
  }
  MSG_ASSERT (m_algo != nullptr, "The algorithm does not exist!!!");

  INFO ("Iterations: ",  m_data["Iterations"]);
  for (auto &iter : m_data["Iterations"])
  {
    m_numIter = iter["Number"];
  }
  srand(time(NULL));
  END;
}

void Master::Run()
{
  BEG;
  std::vector<int> recursos_BSf, recursos_servicios_i, recursos_usuarios_i, recursos_AsignadosBSv, recursos_AsignadosUsuarios, rangosenal, rangointerferencia;
  std::vector<float> demanda_servicios, demanda_usuarios, recursos_servicios, recursos_usuarios, throughputUsuarios, SINR;
  std::vector<std::string> BSvirtuales, BSv, BSvir;
  float cancelacionInter, sigma2, si, interferencia;
  int x = 0, b = 0, c = 0, f = 0, e = 0, nivelCentralizacion, AsigBSv = 0, r = 0, h = 0, w = 0, recursoszona;
  std::vector<std::vector<int>> recursos_restantes_BSfisica;
  float y, cola;
  std::vector<float> Zs;

  for (auto &iter : m_mapService)
  {
    Zs.push_back(0);
    m_mapService.at(iter.first).SetVirutalQueue(0);
  }

  std::vector<std::string> servicioglobal, servglobdef;
  for (auto &j : m_mapGlobalService)
  {
    servicioglobal.push_back(j.second);
  }
  auto z = 0u;
  for (z = 0u; z < servicioglobal.size() - 1; z++)
  {
    if (servicioglobal[z] != servicioglobal[z + 1])
    {
      servglobdef.push_back(servicioglobal[z]);
    }
  }
  servglobdef.push_back(servicioglobal[z]);
  std::ofstream fich2("Results_throughput.txt");
  std::ofstream fich3("Results_SINR.txt");
  std::ofstream fich4("Results_virtualQueue.txt");
  std::ofstream fich5("Results_remResourcesPhysicalBs.txt");

  for (auto &item : m_mapResources)
  {
    recursos_BSf.push_back(m_mapPhyBs.at(item.first).GetResources());
  }

  for (auto i = 0; i < m_numIter; i++)
  {
    INFO("\r****** Iteration ", i ," ******");
    for (auto &item : m_mapTargetThput)
    {
      demanda_servicios.push_back(item.second); // Demanda en Mbps
    }
    for (auto &s : m_mapService)
    {
      m_mapService[s.first].SetSlotDemand(i, demanda_servicios[x]);
      x++;
    }
    for (auto &a : m_mapBS)
    {
      m_mapZone.at(a.first).Reset();
    }
    for (auto &item : m_mapZone)
    {
      m_mapZone.at(item.first).Savedemand(demanda_servicios[b]);
      b++;
    }
    for (auto &item : m_mapVirtBs)
    {
      m_mapVirtBs[item.first].Reset();
    }
    for (auto &x : m_mapBS)
    {
      rangosenal = m_mapSignalRange.at(x.first);
      rangointerferencia = m_mapInterferenceRange.at(x.first);
      si = rangosenal[0] + rand() % (rangosenal[1] - rangosenal[0] + 1);
      sigma2 = 1 * pow(10, -3);
      interferencia = rangointerferencia[0] + rand() % (rangointerferencia[1] - rangointerferencia[0] + 1);
      m_mapZone.at(x.first).SavesiCentralization(si);
      m_mapZone.at(x.first).SaveInterferenceCentralization(interferencia);
      if (x.second.size() != 1)
      {
        BSv = m_mapZone.at(x.first).ReadBSv();
        nivelCentralizacion = m_mapVirtBs.at(BSv[0]).GetCentralizationLevel();
        cancelacionInter = m_tabla[nivelCentralizacion - 1][1];
        interferencia = interferencia * cancelacionInter;
      }
      auto sinr = std::min(si / (sigma2 + interferencia), float(1073741823.0));
      SINR.push_back(sinr);
      m_mapZone.at(x.first).SaveSINR(SINR[f]);
      f++;
    }
    for (auto &iter : m_mapService)
    {
      m_mapService.at(iter.first).SetSinr(SINR[c]);
      recursos_servicios.push_back(recursos_necesarios(demanda_servicios[c], SINR[c]));
      recursos_servicios_i.push_back(std::ceil(recursos_servicios[c]));
      m_mapService.at(iter.first).SetAskedResources(recursos_servicios_i[c]);
      c++;
    }
    for (auto &item : m_mapMinThput)
    {
      recursoszona = std::ceil(recursos_necesarios(item.second, SINR[w]));
      m_mapZone.at(item.first).SaveResourcesMin(recursoszona);
      w++;
    }
    m_algo->Init(m_mapPhyBs, m_mapVirtBs, m_mapService, servglobdef, m_mapZone);
    m_algo->Run();
    m_mapVirtBs = m_algo->Decision();
    recursos_restantes_BSfisica.push_back(m_algo->RemResourcesPhyBs());
    for (auto &iter : m_mapVirtBs)
    { 
      recursos_AsignadosBSv.push_back(m_mapVirtBs.at(iter.first).ReadAssignment());
    }
    for (auto &iter : m_mapPhyBs)
    {
      BSvir = m_mapPhyBs.at(iter.first).GetVirtualBss();
      m_mapPhyBs.at(iter.first).SetSlot(i);
      for (auto j = 0u; j < BSvir.size(); j++)
      {                                                         
        AsigBSv = m_mapVirtBs.at(BSvir[j]).ReadAssignment();
        m_mapPhyBs.at(iter.first).AddResourcesVirtualBsv(AsigBSv);
      }
    }
    for (auto &x : m_mapZone)
    {
      auto VirtualBS = m_mapZone.at(x.first).ReadBSv();
      auto recursosAsig = m_mapVirtBs.at(VirtualBS[0]).ReadAssignment();
      auto throughusu = throughput(recursosAsig, m_mapZone.at(x.first).ReadSINR());
      throughputUsuarios.push_back(throughusu);
      m_mapZone.at(x.first).Savethroughput(throughputUsuarios[r]); 
      r++; 
    }
    for (auto &item : m_mapService)
    {
      y = demanda_servicios[e] - throughputUsuarios[e];
      cola = Zs[h] + y;
      if (cola > 0)
      {
        Zs.insert(Zs.begin() + h + m_mapService.size(), cola);
        m_mapService.at(item.first).SetVirutalQueue(cola);
      }
      else
      {
        Zs.insert(Zs.begin() + h + m_mapService.size(), 0);
        m_mapService.at(item.first).SetVirutalQueue(0);
      }
      e++;
      h++;
    }
    float sinrdef;
    for(auto& val : m_mapZone){
      sinrdef=m_mapZone.at(val.first).ReadSINR();
      m_mapZone.at(val.first).SaveSinrDef(sinrdef);
    }
    int split;
    for(auto& val:m_mapVirtBs){
      split = m_mapVirtBs.at(val.first).GetCentralizationLevel();
      m_mapVirtBs.at(val.first).AddAllowedCentralizationLevel(split);
    }

  }

  std::vector<int> slot, recursosBSv;
  int cont = 0;
  std::string nombre_BSfisica;

  for (auto &iter : m_mapPhyBs)
  {
    nombre_BSfisica = iter.first + "_resources.txt";
    std::ofstream fich(nombre_BSfisica);
    slot = m_mapPhyBs.at(iter.first).GetSlot();
    BSvir = m_mapPhyBs.at(iter.first).GetVirtualBss();
    fich << "Slot" << std::setw(10);
    for (auto j = 0u; j < BSvir.size(); j++)
    {   
      fich << std::setw(10) << BSvir[j];
    }
    fich << std::endl;
    for (auto j = 0u; j < slot.size(); j++)
    {
      fich << std::setw(4) << slot[j] << std::setw(10);
      recursosBSv = m_mapPhyBs.at(iter.first).GetResourcesVirtualBss();
      for (auto z = 0u; z < BSvir.size(); z++)
      {
        fich << std::setw(10) << recursosBSv[cont];
        cont++;
      }
      fich << std::endl;
    }
    cont = 0;
  }
  std::vector<int> nivelsplit;
  cont = 0;

  for (auto &iteracion : m_mapPhyBs)
  {
    nombre_BSfisica = iteracion.first + "_split.txt";
    std::ofstream fich1(nombre_BSfisica);
    BSvir = m_mapPhyBs.at(iteracion.first).GetVirtualBss();
    fich1 << "Slot";
    for (auto j = 0u; j < BSvir.size(); j++)
    {
      fich1 << std::setw(10) << BSvir[j];
    }
    fich1 << std::endl;
    for (auto j = 0u; j < slot.size(); j++)
    {
      fich1 << std::setw(4) << slot[j];
      for (auto z = 0u; z < BSvir.size(); z++)
      {
        nivelsplit = m_mapVirtBs.at(BSvir[cont]).GetAllowedCentralizationLevels();
        fich1 << std::setw(10) << nivelsplit[j];
        cont++;
      }
      cont = 0;
      fich1 << std::endl;
    }
  }

  std::vector<float> throughputusu, sinr;
  fich2 << "Slot";
  fich3 << "Slot";
  for (auto &x : m_mapZone)
  {
    fich2 << std::setw(20) << x.first;
    fich3 << std::setw(20) << x.first;
  }
  fich2 << std::endl;
  fich3 << std::endl;
  for (auto j = 0u; j < slot.size(); j++)
  {
    fich2 << std::setw(4) << slot[j];
    fich3 << std::setw(4) << slot[j];
    for (auto iter : m_mapZone)
    {
      throughputusu = m_mapZone.at(iter.first).Readthroughput();
      fich2 << std::setw(25) << throughputusu[j];
      sinr = m_mapZone.at(iter.first).ReadSinrDef();
      fich3 << std::setw(25) << sinr[j];
    }
    fich2 << std::endl;
    fich3 << std::endl;
  }

  std::vector<float> colavirtual;
  fich4 << "Slot";
  for (auto &x : m_mapService)
  {
    fich4 << std::setw(25) << x.first;
  }
  fich4 << std::endl;
  for (auto j = 0u; j < slot.size(); j++)
  {
    fich4 << std::setw(4) << slot[j];
    for (auto iter : m_mapService)
    {
      colavirtual = m_mapService.at(iter.first).GetVirutalQueue();
      fich4 << std::setw(30) << colavirtual[j];
    }
    fich4 << std::endl;
  }

  std::vector<int> filarecres;
  fich5 << "Slot";
  for (auto &x : m_mapPhyBs)
  {
    fich5 << std::setw(10) << x.first;
  }
  fich5 << std::endl;

  for (auto j = 0u; j < slot.size(); j++)
  {
    fich5 << std::setw(4) << slot[j] << std::setw(10);
    filarecres = recursos_restantes_BSfisica[j];
    for (auto contador = 0u; contador < filarecres.size(); contador++)
    {
      fich5 << std::setw(10) << filarecres[contador];
    }
    fich5 << std::endl;
  }
  END;
}

Master::~Master()
{
  BEG;
  delete m_algo;
  END;
}
