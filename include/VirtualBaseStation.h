#ifndef VirtualBaseStation_H
#define VirtualBaseStation_H

#include "Common.h"

class VirtualBaseStation
{
public:
  VirtualBaseStation();
  ~VirtualBaseStation();

  void Reset();
  void SetZone(std::string zone);

  void SetAssignment(int resources);
  int ReadAssignment();
  
  void SetCentralizationLevel(int fs);
  int GetCentralizationLevel() const;

  void SetService(std::string service);
  std::string GetService();

  void SetPhysicalBs(std::string phyBs);
  std::string GetPhysicalBs();
  
  void AddAllowedCentralizationLevel(int nivel);
  std::vector<int> GetAllowedCentralizationLevels();

private:
  int m_resources;
  int m_centralizationLevel;
  std::string m_zone;
  std::string m_service;
  std::string m_physicalBs;
  std::vector<int> m_allowedCentralizationLevels;
};

#endif /* VirtualBaseStation_H */