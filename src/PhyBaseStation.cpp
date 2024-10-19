#include "PhyBaseStation.h"
#include "Log.h"
#include <iostream>

LOG_REGISTER_MODULE("PhyBaseStation");

PhyBaseStation::PhyBaseStation(int resources) : m_resources(resources)
{
  BEG;
  DBG("Resources of the Phy BS:  ", resources);
  END;
}

PhyBaseStation::~PhyBaseStation()
{
  BEGEND;
}

int PhyBaseStation::GetResources()
{
  BEGEND;
  return m_resources;
}

void PhyBaseStation::AddService(std::string service)
{
  BEG;
  m_services.push_back(service);
  END;
}

std::vector<std::string> PhyBaseStation::GetServices()
{
  BEGEND;
  return m_services;
}

void PhyBaseStation::AddVirtualBs(std::string virtualBs)
{
  BEG;
  m_virtualBss.push_back(virtualBs);
  END;
}

std::vector<std::string> PhyBaseStation::GetVirtualBss()
{
  BEGEND;
  return m_virtualBss;
}

void PhyBaseStation::AddResourcesVirtualBsv(int resVirBs)
{
  BEG;
  m_resourcesVirtualBs.push_back(resVirBs);
  END;
}

std::vector<int> PhyBaseStation::GetResourcesVirtualBss()
{
  BEGEND;
  return m_resourcesVirtualBs;
}

void PhyBaseStation::SetSlot(int slot)
{
  BEG;
  m_slot.push_back(slot);
  END;
}

std::vector<int> PhyBaseStation::GetSlot()
{
  BEGEND;
  return m_slot;
}