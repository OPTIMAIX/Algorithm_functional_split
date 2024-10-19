#include "Algorithm1.h"
#include "Log.h"
#include <iostream>

LOG_REGISTER_MODULE("Algorithm1");

Algorithm1::Algorithm1(const json &j)
    : AlgorithmBase(j)
{
  BEGEND;
}

Algorithm1::~Algorithm1()
{
  BEGEND;
}

void Algorithm1::Init(std::map<std::string, PhyBaseStation> &mapBSfisica, //
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

void Algorithm1::Run()
{
  BEG;
  int recursosBSf, sumatorio, recursostotalesBSf, recursospedidos, max = -1, recursosasignados, recursosrestantes, recursosfinales;
  std::vector<std::string> serviciosBSf, BSvirtualesBSf, BSvirtualesrestantes;
  std::string Serv, Servglob;

  for (auto &i : m_mapBSfisica)
  {
    BSvirtualesrestantes.clear();
    sumatorio = 0;
    recursosBSf = m_mapBSfisica.at(i.first).GetResources();
    serviciosBSf = m_mapBSfisica.at(i.first).GetServices();
    BSvirtualesBSf = m_mapBSfisica.at(i.first).GetVirtualBss();
    for (auto sum = 0u; sum < serviciosBSf.size(); sum++)
    {
      sumatorio = sumatorio + m_mapService.at(serviciosBSf[sum]).GetAskedResources();
    }
    if (recursosBSf >= sumatorio)
    {
      for (auto sum = 0u; sum < BSvirtualesBSf.size(); sum++)
      {
        Serv = m_mapBSvirtual.at(BSvirtualesBSf[sum]).GetService();
        m_mapBSvirtual.at(BSvirtualesBSf[sum]).SetAssignment(m_mapService.at(Serv).GetAskedResources());
      }
      recursosrestantes = recursosBSf;
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
    else
    {
      recursostotalesBSf = recursosBSf;
      for (auto z = 0u; z < m_servglobdef.size(); z++)
      {
        for (auto cont = 0u; cont < BSvirtualesBSf.size(); cont++)
        {
          Serv = m_mapBSvirtual.at(BSvirtualesBSf[cont]).GetService();
          Servglob = m_mapService.at(Serv).GetGlobalService();
          if (Servglob == m_servglobdef[z])
          {
            recursospedidos = m_mapService.at(Serv).GetAskedResources();
            if (recursospedidos > max)
            {
              max = recursospedidos;
            }
          }
        }
        if (max <= recursostotalesBSf)
        {
          for (auto sum = 0u; sum < BSvirtualesBSf.size(); sum++)
          {
            Serv = m_mapBSvirtual.at(BSvirtualesBSf[sum]).GetService();
            Servglob = m_mapService.at(Serv).GetGlobalService();
            if (Servglob == m_servglobdef[z])
            {
              recursospedidos = m_mapService.at(Serv).GetAskedResources();
              m_mapBSvirtual.at(BSvirtualesBSf[sum]).SetAssignment(recursospedidos);
            }
          }
          recursostotalesBSf = recursostotalesBSf - max;
        }
        else
        {
          for (auto sum = 0u; sum < BSvirtualesBSf.size(); sum++)
          {
            Serv = m_mapBSvirtual.at(BSvirtualesBSf[sum]).GetService();
            Servglob = m_mapService.at(Serv).GetGlobalService();
            if (Servglob == m_servglobdef[z])
            {
              BSvirtualesrestantes.push_back(BSvirtualesBSf[sum]);
            }
          }
        }
        max = -1;
      }
      recursosfinales = recursostotalesBSf;
      for (auto sum = 0u; sum < BSvirtualesrestantes.size(); sum++)
      {
        m_mapBSvirtual.at(BSvirtualesrestantes[sum]).SetAssignment(recursostotalesBSf / BSvirtualesrestantes.size());
        recursosfinales = recursosfinales - recursostotalesBSf / BSvirtualesrestantes.size();
      }
      m_recursosrestantesBSfisica.push_back(recursosfinales);
    }
  }
  std::vector<std::string> BSvirtuales;
  int recursos, min = 100000000;
  for (auto &h : m_mapZona)
  {
    BSvirtuales = m_mapZona.at(h.first).ReadBSv();
    if (BSvirtuales.size() > 1)
    {
      for (auto v = 0u; v < BSvirtuales.size(); v++)
      {
        recursos = m_mapBSvirtual.at(BSvirtuales[v]).ReadAssignment();
        if (recursos < min)
        {
          min = recursos;
        }
      }
      for (auto v = 0u; v < BSvirtuales.size(); v++)
      {
        m_mapBSvirtual.at(BSvirtuales[v]).SetAssignment(min);
      }
      min = 100000000;
    }
  }
  END;
}

std::map<std::string, VirtualBaseStation> Algorithm1::Decision()
{
  BEGEND;
  return m_mapBSvirtual;
}

std::vector<int> Algorithm1::RemResourcesPhyBs()
{
  BEGEND;
  return m_recursosrestantesBSfisica;
}