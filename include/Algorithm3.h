#ifndef Algorithm3_H
#define Algorithm3_H

#include "Common.h"
#include "AlgorithmBase.h"
#include "SolverScen1.h"
#include "SolverScen2.h"
#include "SolverScen3.h"

class Algorithm3 : public AlgorithmBase
{
public:
  Algorithm3(const json &j);
  virtual ~Algorithm3();

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
  int m_i = 0;
  double m_v;
};

#endif /* Algorithm3_H */