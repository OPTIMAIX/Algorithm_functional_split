#include "Service.h"
#include "Log.h"
#include <iostream>

LOG_REGISTER_MODULE("Service");

Service::Service()
{
  BEGEND;
}

Service::~Service()
{
  BEGEND;
}

void Service::SetSlotDemand(int slot, float demand)
{
  BEG;
  m_slot.push_back(slot);
  m_demand.push_back(demand);
  END;
}

void Service::SetAskedResources(int resources)
{
  BEG;
  m_askedResources = resources;
  END;
}

int Service::GetAskedResources()
{
  BEGEND;
  return m_askedResources;
}

void Service::SetVirutalQueue(float virtualQueue)
{
  BEG;
  m_virtualQueue.push_back(virtualQueue);
  END;
}

std::vector<float> Service::GetVirutalQueue()
{
  BEGEND;
  return m_virtualQueue;
}

void Service::SetGlobalService(std::string globalService)
{
  BEG;
  m_globalService = globalService;
  END;
}

std::string Service::GetGlobalService()
{
  BEGEND;
  return m_globalService;
}

void Service::SetSinr(float sinr)
{
  BEG;
  m_sinr = sinr;
  END;
}

float Service::GetSinr()
{
  BEGEND;
  return m_sinr;
}

void Service::SetZone(std::string zone)
{
  BEG;
  m_zone = zone;
  END;
}

std::string Service::GetZone()
{
  BEGEND;
  return m_zone;
}
