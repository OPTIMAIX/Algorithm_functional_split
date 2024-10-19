#ifndef Master_H
#define Master_H

#include "Common.h"
#include "Service.h"
#include "PhyBaseStation.h"
#include "VirtualBaseStation.h"
#include "Zone.h"
#include "AlgorithmBase.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
#include "Algorithm4.h"
#include "Algorithm5.h"
#include <cmath>
#include <string>
#include <unordered_map>

class Master
{
public:
  Master(const json &j);
  void Init();
  void Run();
  ~Master();

private:
  std::map<std::string, PhyBaseStation> m_mapPhyBs;
  std::map<std::string, VirtualBaseStation> m_mapVirtBs;
  std::map<std::string, Service> m_mapService;
  std::map<std::string, Zone> m_mapZone;

  std::map<std::string, int> m_mapResources;
  std::map<std::string, std::vector<std::string>> m_mapBS;

  std::map<std::string, std::vector<int>> m_mapSignalRange;
  std::map<std::string, std::vector<int>> m_mapInterferenceRange;

  std::map<std::string, float> m_mapTargetThput;
  std::map<std::string, float> m_mapMinThput;

  std::map<std::string, std::string> m_mapGlobalService;

  json m_data;

  // Centralization level and interference cancelation factor
  float m_tabla[4][2] = {{1, 1}, {2, 0.6}, {3, 0.2}, {4, 0.01}};
  AlgorithmBase *m_algo;
  int m_numIter;
};

#endif /* Master_H */