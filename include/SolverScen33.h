#ifndef SolverScen33_H
#define SolverScen33_H

#include "Common.h"

class SolverScen33 {
public:
    SolverScen33();
    ~SolverScen33(); 

    void Init(std::vector<double> coeficientesAreas, std::vector< double> recursosBSfisicas, std::vector<double> recursosminimos);
    void Run();
    std::vector<double> Decision();
    double Optimalvalue();

private:
    std::vector<double> m_coeficientesAreas, m_recursosBSfisicas, m_recursosAsignados, m_recursosminimos;
    double m_z;
};

#endif