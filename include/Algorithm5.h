#ifndef Algorithm5_H
#define Algorithm5_H

#include "Common.h"
#include "AlgorithmBase.h"
#include "SolverScen33.h"

class Algorithm5 : public AlgorithmBase
{
public:
  Algorithm5(const json &j);
  virtual ~Algorithm5();

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
  int m_i = 0, m_cargacompu;
  double m_v;
  float m_tablacarga[4][2] = {{1, 4.7}, {2, 6.7}, {3, 10.7}, {4, 20.9}};
  float m_tablanivel[4][2] = {{1, 1}, {2, 0.6}, {3, 0.2}, {4, 0.01}};
};

#endif /* Algorithm5_H */