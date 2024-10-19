#ifndef Algorithm2_H
#define Algorithm2_H

#include "Common.h"
#include "AlgorithmBase.h"

class Algorithm2 : public AlgorithmBase
{
public:
  Algorithm2(const json &j);
  virtual ~Algorithm2();

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
  int m_i;
};

#endif /* Algorithm2_H */