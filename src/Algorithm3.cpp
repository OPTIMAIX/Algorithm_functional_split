#include "Algorithm3.h"
#include "Log.h"
#include <iostream>
#include <string>

LOG_REGISTER_MODULE("Algorithm3");

Algorithm3::Algorithm3(const json &j)
    : AlgorithmBase(j)
{
  BEG;
  m_v = j["V"];  
  END;
}

Algorithm3::~Algorithm3()
{
  BEGEND;
}

void Algorithm3::Init(std::map<std::string, PhyBaseStation> &mapBSfisica, //
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

void Algorithm3::Run()
{
  BEG;
  SolverScen1 solver;
  int numBSfisicas = 0;
  std::vector<std::string> BSfisicas;
  std::string zona;
  std::vector<float> cola;
  float coeficiente, SINR, capacidad;
  std::vector<double> coeficientes_areas, recursosBSfisicas, recursosAsignados, recursosminimos;
  std::vector<std::string> BSvirtual;
  int z = 0;

  coeficientes_areas.clear();
  recursosBSfisicas.clear();
  recursosminimos.clear();

  for (auto &item : m_mapService)
  {
    cola = m_mapService.at(item.first).GetVirutalQueue();
    SINR = m_mapService.at(item.first).GetSinr();
    capacidad = log2(1 + SINR);
    zona = m_mapService.at(item.first).GetZone();
    BSfisicas = m_mapZona.at(zona).ReadBSfisicas();
    numBSfisicas = BSfisicas.size();
    coeficiente = m_v * numBSfisicas - cola[m_i] * capacidad;
    coeficientes_areas.push_back(coeficiente);
  }
  m_i++;

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
  for (auto &item : m_mapZona)
  {
    BSvirtual = m_mapZona.at(item.first).ReadBSv();
    for (auto i = 0u; i < BSvirtual.size(); i++)
    {
      m_mapBSvirtual.at(BSvirtual[i]).SetAssignment(recursosAsignados[z]);
    }
    z++;
  }
  int recursosrestantes, recursosasignados, max = -1;
  std::vector<std::string> BSvirtualesBSf;
  std::string Serv, Servglob;

  for (auto &item : m_mapBSfisica)
  {
    BSvirtualesBSf = m_mapBSfisica.at(item.first).GetVirtualBss();
    recursosrestantes = m_mapBSfisica.at(item.first).GetResources();
    for (auto z = 0u; z < m_servglobdef.size(); z++)
    {
      for (auto cont = 0u; cont < BSvirtualesBSf.size(); cont++)
      {
        Serv = m_mapBSvirtual.at(BSvirtualesBSf[cont]).GetService();
        Servglob = m_mapService.at(Serv).GetGlobalService();
        if (Servglob == m_servglobdef[z])
        {
          recursosasignados = m_mapBSvirtual.at(BSvirtualesBSf[cont]).ReadAssignment();
          if (recursosasignados > max)
          {
            max = recursosasignados;
          }
        }
      }
      recursosrestantes = recursosrestantes - max;
      max = -1;
    }
    m_recursosrestantesBSfisica.push_back(recursosrestantes);
  }
  END;
}

std::map<std::string, VirtualBaseStation> Algorithm3::Decision()
{
  BEGEND;
  return m_mapBSvirtual;
}

std::vector<int> Algorithm3::RemResourcesPhyBs()
{
  BEGEND;
  return m_recursosrestantesBSfisica;
}
