#include "AlgorithmBase.h"
#include "Log.h"
#include <iostream>

LOG_REGISTER_MODULE("AlgorithmBase");

AlgorithmBase::AlgorithmBase([[maybe_unused]] const json &j) 
{
  BEGEND;
}


AlgorithmBase::~AlgorithmBase() 
{
  BEGEND;
}
