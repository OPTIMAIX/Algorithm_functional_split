#ifndef Algorithm1_H
#define Algorithm1_H

#include "Common.h"
#include "AlgorithmBase.h"

class Algorithm1 : public AlgorithmBase
{
public:
  Algorithm1(const json &j);
  virtual ~Algorithm1();

  void Init(std::map<std::string, PhyBaseStation> &mapBSfisica,      //
            std::map<std::string, VirtualBaseStation> &mapBSvirtual, //
            std::map<std::string, Service> &mapService,              //
            std::vector<std::string> servglobdef,                    //
            std::map<std::string, Zone> &mapZona);
  void Run();
  std::map<std::string, VirtualBaseStation> Decision();
  std::vector<int> RemResourcesPhyBs();

private:
  std::map<std::string, PhyBaseStation> m_mapBSfisica;
  std::map<std::string, VirtualBaseStation> m_mapBSvirtual;
  std::map<std::string, Service> m_mapService;
  std::map<std::string, Zone> m_mapZona;
  std::vector<std::string> m_servglobdef;
  std::vector<int> m_recursosrestantesBSfisica;
};

#endif /* Algorithm1_H */