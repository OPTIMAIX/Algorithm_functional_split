#ifndef AlgorithmBase_H
#define AlgorithmBase_H

#include "Common.h"
#include <map>
#include "PhyBaseStation.h"
#include "VirtualBaseStation.h"
#include "Service.h"
#include "Zone.h"

class AlgorithmBase
{
public:
  AlgorithmBase(const json &j);
  virtual ~AlgorithmBase();

  virtual void Init(std::map<std::string, PhyBaseStation> &mapBSfisica,      //
                    std::map<std::string, VirtualBaseStation> &mapBSvirtual, //
                    std::map<std::string, Service> &mapService,              //
                    std::vector<std::string> servglobdef,                    //
                    std::map<std::string, Zone> &mapZona) = 0;
  virtual void Run() = 0;
  virtual std::map<std::string, VirtualBaseStation> Decision() = 0;
  virtual std::vector<int> RemResourcesPhyBs() = 0;
};

#endif /* AlgorithmBase_H */