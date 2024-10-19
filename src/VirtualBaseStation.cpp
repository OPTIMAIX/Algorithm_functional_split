#include "VirtualBaseStation.h"
#include "Log.h"
#include <iostream>

LOG_REGISTER_MODULE("VirtualBaseStation");

VirtualBaseStation::VirtualBaseStation()
{
  BEG;
  m_centralizationLevel = 1;
  END;
}

VirtualBaseStation::~VirtualBaseStation()
{
  BEGEND;
}

void VirtualBaseStation::Reset()
{
  BEG;
  m_resources = 0;
  END;
}

void VirtualBaseStation::SetZone(std::string zone)
{
  BEG;
  m_zone = zone;
  END;
}

void VirtualBaseStation::SetAssignment(int resources)
{
  BEG;
  m_resources = resources;
  END;
}

int VirtualBaseStation::ReadAssignment()
{
  BEGEND;
  return m_resources;
}

void VirtualBaseStation::SetCentralizationLevel(int fs)
{
  BEG;
  m_centralizationLevel = fs;
  END;
}

int VirtualBaseStation::GetCentralizationLevel() const
{
  BEGEND;
  return m_centralizationLevel;
}

void VirtualBaseStation::SetService(std::string service)
{
  BEG;
  m_service = service;
  END;
}

std::string VirtualBaseStation::GetService()
{
  BEGEND;
  return m_service;
}

void VirtualBaseStation::SetPhysicalBs(std::string phyBs)
{
  BEG;
  m_physicalBs = phyBs;
  END;
}

std::string VirtualBaseStation::GetPhysicalBs()
{
  BEGEND;
  return m_physicalBs;
}

void VirtualBaseStation::AddAllowedCentralizationLevel(int nivel)
{
  BEG;
  m_allowedCentralizationLevels.push_back(nivel);
  END;
}

std::vector<int> VirtualBaseStation::GetAllowedCentralizationLevels()
{
  BEGEND;
  return m_allowedCentralizationLevels;
}