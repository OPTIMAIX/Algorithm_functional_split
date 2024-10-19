#ifndef SolverScen1_H
#define SolverScen1_H

#include "Common.h"

class SolverScen1 {
public:
    SolverScen1();
    ~SolverScen1(); 

    void Init(std::vector<double> coeficientesAreas, std::vector< double> recursosBSfisicas, std::vector<double> recursosminimos);
    void Run();
    std::vector<double> Decision();

private:
    std::vector<double> m_coeficientesAreas, m_recursosBSfisicas, m_recursosAsignados, m_recursosminimos;
};

#endif