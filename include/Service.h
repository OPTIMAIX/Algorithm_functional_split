#ifndef SERVICE_H
#define SERVICE_H

#include "Common.h"

class Service
{
public:
  Service();
  ~Service();

  void SetSlotDemand(int slot, float demand);
  
  void SetAskedResources(int resources);
  int GetAskedResources();
  
  void SetVirutalQueue(float virtualQueue);
  std::vector<float> GetVirutalQueue();
  
  void SetGlobalService(std::string globalService);
  std::string GetGlobalService();

  void SetSinr(float sinr);
  float GetSinr();
  
  void SetZone(std::string zone);
  std::string GetZone();

private:
  std::vector<float> m_demand;
  std::vector<int> m_slot;
  std::vector<float> m_virtualQueue;
  int m_askedResources;
  std::string m_globalService;
  float m_sinr;
  std::string m_zone;
};

#endif /* SERVICE_H */