#include "Algorithm5.h"
#include "Log.h"
#include <iostream>
#include <string>

LOG_REGISTER_MODULE("Algorithm5");

float resources_min(float demanda, float SINR)
{
  float factor = 180 * pow(10, 3) / 1e6;
  float capacidad = log2(1 + SINR);
  float recursos = demanda / (factor * capacidad);
  return recursos;
}

Algorithm5::Algorithm5(const json &j)
    : AlgorithmBase(j)
{
  BEG;
  m_v = j["V"];
  m_cargacompu = j["CompLoad"];
  END;
}

Algorithm5::~Algorithm5()
{
  BEGEND;
}

void Algorithm5::Init(std::map<std::string, PhyBaseStation> &mapBSfisica, //
                      std::map<std::string, VirtualBaseStation> &mapBSvirtual,     //
                      std::map<std::string, Service> &mapService,         //
                      std::vector<std::string> servglobdef,               //
                      std::map<std::string, Zone> &mapZona)
{
  BEG;
  m_mapBSfisica = mapBSfisica;
  m_mapBSvirtual = mapBSvirtual;
  m_mapService = mapService;
  m_mapZona = mapZona;
  m_servglobdef = servglobdef;
  m_recursosrestantesBSfisica.clear();
  END;
}

void Algorithm5::Run()
{
  BEG;
  std::vector<int> combinacionesposibles;
  for (int i = 1; i <= 4; i++)
  {
    for (int j = 1; j <= 4; j++)
    {
      for (int k = 1; k <= 4; k++)
      {
        combinacionesposibles.insert(combinacionesposibles.end(), {i, j, k});
      }
    }
  }
  int cargamax = m_cargacompu;
  int c = 0;
  float carga = 0;
  std::vector<int> combtemporal, combdefinitivas;
  for (auto i = 0u; i < combinacionesposibles.size(); i++)
  {
    carga = carga + m_tablacarga[combinacionesposibles[i] - 1][1];
    c++;
    combtemporal.push_back(combinacionesposibles[i]);
    if (c == 3)
    {
      if (carga <= cargamax)
      {
        for (auto x = 0u; x < combtemporal.size(); x++)
        {
          combdefinitivas.push_back(combtemporal[x]);
        }
      }
      combtemporal.clear();
      c = 0;
      carga = 0;
    }
  }
  int r = 0, z = 0; 
  auto max = 10000000000;
  std::vector<std::string> BSvirtual;
  std::vector<double> recursosAsignados, recursosasignadosdef;
  std::vector<int> combideal, recursosmindef;
  std::vector<float> SINRdef;
  for (auto iter = 0u; iter < combdefinitivas.size() / 3; iter++)
  {
    SolverScen33 solver;
    std::string zona;
    std::vector<float> cola, SINRprov;
    float coeficiente, SINR, capacidad, si, interferencia, sigma2 = 1 * pow(10, -3), cancelacionInter;
    std::vector<double> coeficientes_areas, recursosBSfisicas, recursosminimos;
    int nivelCentralizacion, recursosminzona;
    std::vector<int> recursosminprov;
    coeficientes_areas.clear();
    recursosBSfisicas.clear();
    recursosminimos.clear();
    SINRprov.clear();
    recursosminprov.clear();
    for (auto &item : m_mapService)
    {
      cola = m_mapService.at(item.first).GetVirutalQueue();
      SINR = m_mapService.at(item.first).GetSinr();
      zona = m_mapService.at(item.first).GetZone();
      if (zona == "Zona18" || zona == "Zona19" || zona == "Zona20")
      {
        si = m_mapZona.at(zona).ReadsiCentralization();
        interferencia = m_mapZona.at(zona).ReadInterferenceCentralization();
        nivelCentralizacion = combdefinitivas[r];
        cancelacionInter = m_tablanivel[nivelCentralizacion - 1][1];
        interferencia = interferencia * cancelacionInter;
        SINR = std::min(si / (sigma2 + interferencia), float(31.0));
        r++;
        SINRprov.push_back(SINR);
        recursosminzona = std::ceil(resources_min(m_mapZona.at(zona).ReadThroughputMin(), SINR));
        m_mapZona.at(zona).SaveResourcesMin(recursosminzona);
        recursosminprov.push_back(recursosminzona);
      }
      capacidad = log2(1 + SINR);
      coeficiente = m_v - cola[m_i] * capacidad;
      coeficientes_areas.push_back(coeficiente);
    }
    for (auto &item : m_mapBSfisica)
    {
      recursosBSfisicas.push_back(m_mapBSfisica.at(item.first).GetResources());
    }
    for (auto &item : m_mapZona)
    {
      recursosminimos.push_back(m_mapZona.at(item.first).ReadResourcesMin());
    }
    solver.Init(coeficientes_areas, recursosBSfisicas, recursosminimos);
    solver.Run();
    recursosAsignados = solver.Decision();
    double optimalvalue = solver.Optimalvalue();
    if (optimalvalue <= max)
    {
      combideal.clear();
      max = optimalvalue;
      combideal.insert(combideal.end(), {combdefinitivas[r - 3], combdefinitivas[r - 2], combdefinitivas[r - 1]});
      SINRdef = SINRprov;
      recursosmindef = recursosminprov;
      recursosasignadosdef = recursosAsignados;
    }
  }
  std::vector<std::string> BSvirtualeszona;
  int pos = 0;
  for (auto &item : m_mapZona)
  {
    if (item.first == "Zona18" || item.first == "Zona19" || item.first == "Zona20")
    {
      BSvirtualeszona = m_mapZona.at(item.first).ReadBSv();
      for (auto i = 0u; i < BSvirtualeszona.size(); i++)
      {
        m_mapBSvirtual.at(BSvirtualeszona[i]).SetCentralizationLevel(combideal[pos]);
      }
      m_mapZona.at(item.first).SaveResourcesMin(recursosmindef[pos]);
      m_mapZona.at(item.first).SaveSINR(SINRdef[pos]);
      pos++;
    }
  }
  for (auto &item : m_mapBSfisica)
  {
    for (auto &iter : m_mapZona)
    {
      BSvirtual = m_mapZona.at(iter.first).ReadBSv();
      for (auto i = 0u; i < BSvirtual.size(); i++)
      { 
        std::string BSfisicaBSvirtual = m_mapBSvirtual.at(BSvirtual[i]).GetPhysicalBs();
        if (BSfisicaBSvirtual == item.first)
        {
          m_mapBSvirtual.at(BSvirtual[i]).SetAssignment(recursosasignadosdef[z]);
        }
      }
      z++;
    }
  }
  int recursosrestantes, recursosasignados;
  std::vector<std::string> BSvirtualesBSf;
  for (auto &item : m_mapBSfisica)
  {
    BSvirtualesBSf = m_mapBSfisica.at(item.first).GetVirtualBss();
    recursosrestantes = m_mapBSfisica.at(item.first).GetResources();
    for (auto cont = 0u; cont < BSvirtualesBSf.size(); cont++)
    {
      recursosasignados = m_mapBSvirtual.at(BSvirtualesBSf[cont]).ReadAssignment();
      recursosrestantes = recursosrestantes - recursosasignados;
    }
    m_recursosrestantesBSfisica.push_back(recursosrestantes);
  }
  m_i++; 
  END;
}

std::map<std::string, VirtualBaseStation> Algorithm5::Decision()
{
  BEGEND;
  return m_mapBSvirtual;
}

std::vector<int> Algorithm5::RemResourcesPhyBs()
{
  BEGEND;
  return m_recursosrestantesBSfisica;
}
