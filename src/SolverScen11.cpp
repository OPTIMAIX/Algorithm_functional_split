#include "SolverScen11.h"
#include "Log.h"
#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <glpk.h>

LOG_REGISTER_MODULE("SolverScen11");

SolverScen11::SolverScen11() 
{
}

void SolverScen11::Init(std::vector<double> coeficientesAreas, std::vector<double> recursosBSfisicas, std::vector<double> recursosminimos)
{
    m_coeficientesAreas=coeficientesAreas;
    m_recursosBSfisicas=recursosBSfisicas;
    m_recursosminimos=recursosminimos;
}


void SolverScen11::Run(){
    glp_prob *lp;
    int ia[1+1000], ja[1+1000];
    double ar[1+1000];
    double k11 = m_coeficientesAreas[0], k12 = m_coeficientesAreas[1], k13 = m_coeficientesAreas[2],  k21 = m_coeficientesAreas[3], k22 = m_coeficientesAreas[4], k23 = m_coeficientesAreas[5];
    double eta1 = m_recursosBSfisicas[0];
    double eta2 = m_recursosBSfisicas[1];
    double r11 = m_recursosminimos[0], r12 = m_recursosminimos[1], r13 = m_recursosminimos[2], r21 = m_recursosminimos[3], r22 = m_recursosminimos[4], r23 =m_recursosminimos[5];
    /* create problem */
    lp = glp_create_prob(); 
    glp_set_prob_name(lp, "myProblem");
    glp_set_obj_dir(lp, GLP_MIN);
    /* Base station capacity contraints */
    glp_add_rows(lp, 4);
    glp_set_row_name(lp, 1, "bs1");
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, eta1);
    glp_set_row_name(lp, 2, "bs2");
    glp_set_row_bnds(lp, 2, GLP_UP, 0.0, eta2);
    /* Area 3 contraints */
    glp_set_row_name(lp, 3, "s1a3");
    glp_set_row_bnds(lp, 3, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 4, "s2a3");
    glp_set_row_bnds(lp, 4, GLP_FX, 0.0, 0);

    // columns 
    glp_add_cols(lp, 12);
    glp_set_col_name(lp, 1, "x11");
    glp_set_col_bnds(lp, 1, GLP_DB, r11, eta1);
    glp_set_obj_coef(lp, 1, k11);

    glp_set_col_name(lp, 2, "x12");
    glp_set_col_bnds(lp, 2, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 2, 0.0);

    glp_set_col_name(lp, 3, "x13");
    glp_set_col_bnds(lp, 3, GLP_DB, r13, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 3, k13);

    glp_set_col_name(lp, 4, "x21");
    glp_set_col_bnds(lp, 4, GLP_DB, 0, eta2);
    glp_set_obj_coef(lp, 4, 0.0);

    glp_set_col_name(lp, 5, "x22");
    glp_set_col_bnds(lp, 5, GLP_DB, r12, eta2);
    glp_set_obj_coef(lp, 5, k12);

    glp_set_col_name(lp, 6, "x23");
    glp_set_col_bnds(lp, 6, GLP_DB, 0, eta2);
    glp_set_obj_coef(lp, 6, 0.0);

    glp_set_col_name(lp, 7, "y11");
    glp_set_col_bnds(lp, 7, GLP_DB, r21, eta2);
    glp_set_obj_coef(lp, 7, k21);

    glp_set_col_name(lp, 8, "y12");
    glp_set_col_bnds(lp, 8, GLP_DB, 0, eta1);
    glp_set_obj_coef(lp, 8, 0.0);

    glp_set_col_name(lp, 9, "y13");
    glp_set_col_bnds(lp, 9, GLP_DB, r23, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 9, k23);

    glp_set_col_name(lp, 10, "y21");
    glp_set_col_bnds(lp, 10, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 10, 0.0);

    glp_set_col_name(lp, 11, "y22");
    glp_set_col_bnds(lp, 11, GLP_DB, r22, eta2);
    glp_set_obj_coef(lp, 11, k22);

    glp_set_col_name(lp, 12, "y23");
    glp_set_col_bnds(lp, 12, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 12, 0.0);
    
    // BS1 constraint  
    ia[1] = 1, ja[1] = 1, ar[1] = 1.0;
    ia[2] = 1, ja[2] = 3, ar[2] = 1.0;
    ia[3] = 1, ja[3] = 7, ar[3] = 1.0;
    ia[4] = 1, ja[4] = 9, ar[4] = 1.0;

    // BS2 constraint  
    ia[5] = 2, ja[5] = 5, ar[5] = 1.0;
    ia[6] = 2, ja[6] = 6, ar[6] = 1.0;
    ia[7] = 2, ja[7] = 11, ar[7] = 1.0;
    ia[8] = 2, ja[8] = 12, ar[8] = 1.0;

    // Service 1 - area 3
    ia[9] = 3, ja[9] = 3, ar[9] = 1.0;
    ia[10] = 3, ja[10] = 6, ar[10] = -1.0;

    // Service 2 - area 3
    ia[11] = 4, ja[11] = 9, ar[11] = 1.0;
    ia[12] = 4, ja[12] = 12, ar[12] = -1.0;

    glp_load_matrix(lp, 12, ia, ja, ar);
    /* solve problem */
    glp_smcp param;
    glp_init_smcp(&param);
    param.msg_lev = GLP_MSG_OFF;
    glp_simplex(lp, &param);
    /* recover and display results */
    auto z = glp_get_obj_val(lp);
    auto x11 = glp_get_col_prim(lp, 1);
    auto x12 = glp_get_col_prim(lp, 2);
    auto x13 = glp_get_col_prim(lp, 3);
    auto x21 = glp_get_col_prim(lp, 4);
    auto x22 = glp_get_col_prim(lp, 5);
    auto x23 = glp_get_col_prim(lp, 6);
    auto y11 = glp_get_col_prim(lp, 7);
    auto y12 = glp_get_col_prim(lp, 8);
    auto y13 = glp_get_col_prim(lp, 9);
    auto y21 = glp_get_col_prim(lp, 10);
    auto y22 = glp_get_col_prim(lp, 11);
    auto y23 = glp_get_col_prim(lp, 12);
    std::cout << "Optimal value " << z << std::endl;
    m_recursosAsignados={x11,x12,x13,y11,y12,y13,x21,x22,x23,y21,y22,y23};
    /* housekeeping */
    glp_delete_prob(lp);
    glp_free_env();
}

std::vector<double> SolverScen11::Decision(){
    return m_recursosAsignados;
}

SolverScen11::~SolverScen11() 
{
}