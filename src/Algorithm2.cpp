#include "Algorithm2.h"
#include "Log.h"
#include <iostream>

LOG_REGISTER_MODULE("Algorithm2");

Algorithm2::Algorithm2(const json &j)
    : AlgorithmBase(j)
{
  BEG;
  m_i = 0; 
  END;
}

Algorithm2::~Algorithm2()
{
  BEGEND;
}

void Algorithm2::Init(std::map<std::string, PhyBaseStation> &mapBSfisica, //
                      std::map<std::string, VirtualBaseStation> &mapBSvirtual,     //
                      std::map<std::string, Service> &mapService,         //
                      std::vector<std::string> servglobdef,               //
                      std::map<std::string, Zone> &mapZone)
{
  BEG;
  m_mapBSfisica = mapBSfisica;
  m_mapBSvirtual = mapBSvirtual;
  m_mapService = mapService;
  m_mapZona = mapZone;
  m_servglobdef = servglobdef;
  m_recursosrestantesBSfisica.clear();
  END;
}

void Algorithm2::Run()
{
  BEG;
  int V = 10, numBSfisicas = 0;
  std::vector<std::string> BSfisicas, servicios, servservglob, BSvirtualesBSf, BSvServnegativo;
  std::string servicio, servglob, servglobnegativo, servBSv, zona;
  int recursosBSf, recursosres;
  float max = 1000;
  std::vector<float> cola;
  float coeficiente, SINR, capacidad;
  for (auto &item : m_mapService)
  {
    cola = m_mapService.at(item.first).GetVirutalQueue();
    SINR = m_mapService.at(item.first).GetSinr();
    capacidad = log2(1 + SINR);
    zona = m_mapService.at(item.first).GetZone();
    BSfisicas = m_mapZona.at(zona).ReadBSfisicas();
    numBSfisicas = BSfisicas.size();
    coeficiente = V * numBSfisicas - cola[m_i] * capacidad;
    if (coeficiente < max)
    {
      max = coeficiente;
      servicio = item.first;
    }
  }
  servglobnegativo = m_mapService.at(servicio).GetGlobalService();
  for (auto &item : m_mapBSfisica)
  {
    servicios = m_mapBSfisica.at(item.first).GetServices();
    for (auto i = 0u; i < servicios.size(); i++)
    {
      servglob = m_mapService.at(servicios[i]).GetGlobalService();
      if (servglob == servglobnegativo)
      {
        servservglob.push_back(servicios[i]);
      }
    }
    BSvirtualesBSf = m_mapBSfisica.at(item.first).GetVirtualBss();
    for (auto s = 0u; s < BSvirtualesBSf.size(); s++)
    {
      servBSv = m_mapBSvirtual.at(BSvirtualesBSf[s]).GetService();

      for (auto c = 0u; c < servservglob.size(); c++)
      {
        if (servBSv == servservglob[c])
        {
          BSvServnegativo.push_back(BSvirtualesBSf[s]);
        }
      }
    }
    recursosBSf = m_mapBSfisica.at(item.first).GetResources();
    recursosres = recursosBSf;
    for (auto d = 0u; d < BSvServnegativo.size(); d++)
    {
      m_mapBSvirtual.at(BSvServnegativo[d]).SetAssignment(recursosBSf / BSvServnegativo.size());
      recursosres = recursosres - recursosBSf / BSvServnegativo.size();
    }
    m_recursosrestantesBSfisica.push_back(recursosres);
    servservglob.clear();
    BSvServnegativo.clear();
  }
  m_i++;
  END;
}

std::map<std::string, VirtualBaseStation> Algorithm2::Decision()
{
  BEGEND;
  return m_mapBSvirtual;
}

std::vector<int> Algorithm2::RemResourcesPhyBs()
{
  BEGEND;
  return m_recursosrestantesBSfisica;
}