#ifndef SolverScen11_H
#define SolverScen11_H

#include "Common.h"

class SolverScen11 {
public:
    SolverScen11();
    ~SolverScen11(); 
    
    void Init(std::vector<double> coeficientesAreas, std::vector< double> recursosBSfisicas, std::vector<double> recursosminimos);
    void Run();
    std::vector<double> Decision();
    
private:
    std::vector<double> m_coeficientesAreas, m_recursosBSfisicas, m_recursosAsignados, m_recursosminimos;    
};

#endif