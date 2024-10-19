#include "Algorithm4.h"
#include "Log.h"
#include <iostream>
#include <string>

LOG_REGISTER_MODULE("Algorithm4");

Algorithm4::Algorithm4(const json &j)
    : AlgorithmBase(j)
{
  BEG;
  m_v = j["V"];
  m_i = 0;
  END;
}

Algorithm4::~Algorithm4()
{
  BEGEND;
}

void Algorithm4::Init(std::map<std::string, PhyBaseStation> &mapBSfisica, //
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

void Algorithm4::Run()
{
  BEG;
  SolverScen33 solver;
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
    coeficiente = m_v - cola[m_i] * capacidad;
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
          m_mapBSvirtual.at(BSvirtual[i]).SetAssignment(recursosAsignados[z]);
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
  END;
}

std::map<std::string, VirtualBaseStation> Algorithm4::Decision()
{
  BEGEND;
  return m_mapBSvirtual;
}

std::vector<int> Algorithm4::RemResourcesPhyBs()
{
  BEGEND;
  return m_recursosrestantesBSfisica;
}