#ifndef SolverScen2_H
#define SolverScen2_H

#include "Common.h"

class SolverScen2 {
public:
    SolverScen2();
    ~SolverScen2(); 

    void Init(std::vector<double> coeficientesAreas, std::vector< double> recursosBSfisicas, std::vector<double> recursosminimos);
    void Run();
    std::vector<double> Decision();

private:
    std::vector<double> m_coeficientesAreas, m_recursosBSfisicas, m_recursosAsignados, m_recursosminimos;
};

#endif