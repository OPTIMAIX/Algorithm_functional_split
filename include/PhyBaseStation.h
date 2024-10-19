#ifndef PhyBaseStation_H
#define PhyBaseStation_H

#include "Common.h"

class PhyBaseStation
{
public:
  PhyBaseStation(int recursos);
  ~PhyBaseStation();

  int GetResources();

  void AddService(std::string service);
  std::vector<std::string> GetServices();

  void AddVirtualBs(std::string vitBs);
  std::vector<std::string> GetVirtualBss();

  void AddResourcesVirtualBsv(int resVirBs);
  std::vector<int> GetResourcesVirtualBss();

  void SetSlot(int slot);
  std::vector<int> GetSlot();

private:
  int m_resources;
  std::vector<std::string> m_services;
  std::vector<std::string> m_virtualBss;
  std::vector<int> m_slot;
  std::vector<int> m_resourcesVirtualBs;
};

#endif /* PhyBaseStation_H */