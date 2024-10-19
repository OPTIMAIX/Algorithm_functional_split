#ifndef SolverScen22_H
#define SolverScen22_H

#include "Common.h"

class SolverScen22 {
public:
    SolverScen22();
    ~SolverScen22(); 

    void Init(std::vector<double> coeficientesAreas, std::vector< double> recursosBSfisicas, std::vector<double> recursosminimos);
    void Run();
    std::vector<double> Decision();

private:
    std::vector<double> m_coeficientesAreas, m_recursosBSfisicas, m_recursosAsignados, m_recursosminimos;
};

#endif