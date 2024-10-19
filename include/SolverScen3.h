#ifndef SolverScen3_H
#define SolverScen3_H

#include "Common.h"

class SolverScen3 {
public:
    SolverScen3();
    ~SolverScen3(); 

    void Init(std::vector<double> coeficientesAreas, std::vector< double> recursosBSfisicas, std::vector<double> recursosminimos);
    void Run();
    std::vector<double> Decision();

private:
    std::vector<double> m_coeficientesAreas, m_recursosBSfisicas, m_recursosAsignados, m_recursosminimos;    
};

#endif