#ifndef Zone_H
#define Zone_H

#include "Common.h"

class Zone
{

public:
  Zone(std::vector<std::string> BS);
  void Savedemand(float usersDemand);
  void Reset();
  void Assign(int resources);
  int ReadAssignment();
  void AssignBSv(std::string BSv);
  std::vector<std::string> ReadBSv();
  void Savethroughput(float throughput);
  std::vector<float> Readthroughput();
  void SaveSINR(float SINR);
  float ReadSINR();
  std::vector<std::string> ReadBSfisicas();
  void SaveResourcesMin(int resourcesMin);
  int ReadResourcesMin();
  void SavesiCentralization(float si);
  float ReadsiCentralization();
  void SaveInterferenceCentralization(float interference);
  float ReadInterferenceCentralization();
  void SaveThroughputMin(float throughputmin);
  float ReadThroughputMin();
  void SaveSinrDef(float SINR);
  std::vector<float> ReadSinrDef();
  ~Zone();

private:
  std::vector<float> m_usersDemand;
  std::vector<std::string> m_BS;       
  int m_resources;
  int m_resourcesMin;       
  std::vector<std::string> m_BSv;      
  std::vector<float> m_throughput;     
  float m_throughputMin;               
  float m_SINR;                        
  float m_si;                          
  float m_interference;                 
  std::vector<float> m_SINRdef;     
};

#endif /* Zone_H */