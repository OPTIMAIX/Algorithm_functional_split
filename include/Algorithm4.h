#ifndef Algorithm4_H
#define Algorithm4_H

#include "Common.h"
#include "AlgorithmBase.h"
#include "SolverScen33.h"

class Algorithm4 : public AlgorithmBase
{
public:
  Algorithm4(const json &j);
  virtual ~Algorithm4();

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
  double m_v;
};

#endif /* Algorithm4_H */