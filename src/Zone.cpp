#include "Zone.h"
#include "Log.h"
#include <iostream>

LOG_REGISTER_MODULE("Zone");

Zone::Zone(std::vector<std::string> BS)
{
  BEG;
  m_BS = BS;
  END;
}

void Zone::Savedemand(float usersDemand)
{
  BEG;
  m_usersDemand.push_back(usersDemand);
  INFO ("Demand saved:  ", usersDemand);
  END;
}

void Zone::Reset()
{
  BEG;
  m_usersDemand.clear();
  END;
}

void Zone::Assign(int resources)
{
  BEG;
  m_resources = resources;
  INFO ("The resources assigned to users in the zone are: ", m_resources)
  END;
}

int Zone::ReadAssignment()
{
  BEG;
  INFO ("Reading resources assigned to used in zone: ", m_resources);            
  END;
  return m_resources;

}

void Zone::AssignBSv(std::string BSv)
{
  BEG;
  m_BSv.push_back(BSv);
  END;
}

std::vector<std::string> Zone::ReadBSv()
{
  BEGEND;
  return m_BSv;
}

void Zone::Savethroughput(float throughput)
{
  BEG;
  m_throughput.push_back(throughput);
  END;
}

std::vector<float> Zone::Readthroughput()
{
  BEGEND;
  return m_throughput;
}

void Zone::SaveSINR(float SINR)
{
  BEG;
  m_SINR=SINR;
  END;
}

float Zone::ReadSINR()
{
  BEGEND;
  return m_SINR;
}

std::vector<std::string> Zone::ReadBSfisicas()
{
  BEGEND;
  return m_BS;
}

void Zone::SaveResourcesMin(int resourcesMin)
{
  BEG;
  m_resourcesMin = resourcesMin;
  END;
}

int Zone::ReadResourcesMin()
{
  BEGEND;
  return m_resourcesMin;
}

void Zone::SavesiCentralization(float si){
  BEG;
  m_si=si;
  END;
}

float Zone::ReadsiCentralization(){
  BEGEND;
  return m_si;
}

void Zone::SaveInterferenceCentralization(float interference){
  BEG;
  m_interference=interference;
  END;
}

float Zone::ReadInterferenceCentralization(){
  BEGEND;
  return m_interference;
}

void Zone::SaveThroughputMin(float throughputmin){
  BEG;
  m_throughputMin=throughputmin;
  END;
}

float Zone::ReadThroughputMin(){
  BEGEND;
  return m_throughputMin;
}

void Zone::SaveSinrDef(float SINR){
  BEG;
  m_SINRdef.push_back(SINR);
  END;
}

std::vector<float> Zone::ReadSinrDef(){
  BEGEND;
  return m_SINRdef;
}


Zone::~Zone()
{
}
