#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Common.h"
#include <experimental/filesystem>
#include "Master.h"
namespace fs = std::experimental::filesystem;

int main(int argc, char *argv[])
{
  /************************************
  Set the log level for each component/class 
  or for all together
  *************************************/
  // LOG_SET_ALL_LEVEL(LogLevel::ALL);
  // LOG_SET_LEVEL("Algoritmo3", LogLevel::ALL);
  // LOG_SET_LEVEL("Zona", LogLevel::ALL);
  // LOG_SET_LEVEL("Maestra", LogLevel::ALL);

  /************************************
  Read the configuration file (.json)
  *************************************/
  MSG_ASSERT(argc == 2, "Bad number of arguments");
  std::string confFile = argv[1];
  std::ifstream ifs(confFile);
  MSG_ASSERT(ifs.is_open(), "Cannot find config file");
  json j;
  ifs >> j;


  /************************************
  Prepare the folder for results and any 
  other necessary step
  *************************************/
  //auto resPath = JsonCheckAndGet<>(j, "/Results/ResultsPath");
  //UINFO("Creating results folder: " + resPath)
  //fs::create_directories(resPath);

  /************************************
  Check that config file at least contains the 
  required fields for the classes
  *************************************/

  JSON_CHECK(j, "Zones");
  JSON_CHECK(j, "Algorithm");
  JSON_CHECK(j, "Iterations");
  Master scenario(j);
  scenario.Init();


  /************************************
  Run a simulation and chrono it
  *************************************/
  
  auto start = SYSTEM_NOW;
  scenario.Run();
  auto end = SYSTEM_NOW;
  std::cout << "**** ELEPASED TIME " << DurationSec(end, start) << " sec\t****\n"; 
  // return 0;
}