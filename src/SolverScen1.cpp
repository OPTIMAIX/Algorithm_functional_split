#include "SolverScen1.h"
#include "Log.h"
#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <glpk.h>

LOG_REGISTER_MODULE("SolverScen1");

SolverScen1::SolverScen1() 
{
}

void SolverScen1::Init(std::vector<double> coeficientesAreas, std::vector<double> recursosBSfisicas, std::vector<double> recursosminimos)
{
    m_coeficientesAreas=coeficientesAreas;
    m_recursosBSfisicas=recursosBSfisicas;
    m_recursosminimos=recursosminimos;
}

void SolverScen1::Run()
{
    /* declare variables */
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
    glp_add_rows(lp, 10);
    glp_set_row_name(lp, 1, "bs1");
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, eta1);
    glp_set_row_name(lp, 2, "bs2");
    glp_set_row_bnds(lp, 2, GLP_UP, 0.0, eta2);
    /* Area 1 contraints */
    glp_set_row_name(lp, 3, "a1b1s1");
    glp_set_row_bnds(lp, 3, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 4, "a1b1s2");
    glp_set_row_bnds(lp, 4, GLP_FX, 0.0, 0);
    /* Area 2 contraints */
    glp_set_row_name(lp, 5, "a2b2s1");
    glp_set_row_bnds(lp, 5, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 6, "a2b2s2");
    glp_set_row_bnds(lp, 6, GLP_FX, 0.0, 0);
    /* Area 3 contraints */
    glp_set_row_name(lp, 7, "a3b1s1");
    glp_set_row_bnds(lp, 7, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 8, "a3b1s2");
    glp_set_row_bnds(lp, 8, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 9, "a3b2s1"); 
    glp_set_row_bnds(lp, 9, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 10, "a3b2s2");
    glp_set_row_bnds(lp, 10, GLP_FX, 0.0, 0);

    // columns 
    glp_add_cols(lp, 10);
    glp_set_col_name(lp, 1, "x11");
    glp_set_col_bnds(lp, 1, GLP_DB, r11, eta1);
    glp_set_obj_coef(lp, 1, k11);

    glp_set_col_name(lp, 2, "x12");
    glp_set_col_bnds(lp, 2, GLP_DB, r12, eta2);
    glp_set_obj_coef(lp, 2, k12);

    glp_set_col_name(lp, 3, "x13");
    glp_set_col_bnds(lp, 3, GLP_DB, r13, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 3, k13);

    glp_set_col_name(lp, 4, "x21");
    glp_set_col_bnds(lp, 4, GLP_DB, r21, eta1);
    glp_set_obj_coef(lp, 4, k21);

    glp_set_col_name(lp, 5, "x22");
    glp_set_col_bnds(lp, 5, GLP_DB, r22, eta2);
    glp_set_obj_coef(lp, 5, k22);

    glp_set_col_name(lp, 6, "x23");
    glp_set_col_bnds(lp, 6, GLP_DB, r23, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 6, k23);

    glp_set_col_name(lp, 7, "y11");
    glp_set_col_bnds(lp, 7, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 7, 0.0);

    glp_set_col_name(lp, 8, "y12");
    glp_set_col_bnds(lp, 8, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 8, 0.0);

    glp_set_col_name(lp, 9, "y21");
    glp_set_col_bnds(lp, 9, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 9, 0.0);

    glp_set_col_name(lp, 10, "y22");
    glp_set_col_bnds(lp, 10, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 10, 0.0);
    
    // BS1 constraint  
    ia[1] = 1, ja[1] = 7, ar[1] = 1.0;
    ia[2] = 1, ja[2] = 9, ar[2] = 1.0;

    // BS2 constraint  
    ia[3] = 2, ja[3] = 8, ar[3] = 1.0;
    ia[4] = 2, ja[4] = 10, ar[4] = 1.0;

    // Area 1 bs1
    // Service 1
    ia[5] = 3, ja[5] = 1, ar[5] = 1.0;
    ia[6] = 3, ja[6] = 7, ar[6] = -1.0;
    // service 2
    ia[7] = 4, ja[7] = 4, ar[7] = 1.0;
    ia[8] = 4, ja[8] = 9, ar[8] = -1.0;

    // Area 2 bs2  
    // Service 1
    ia[9] = 5, ja[9] = 2, ar[9] = 1.0;
    ia[10] = 5, ja[10] = 8, ar[10] = -1.0;
    // Service 2
    ia[11] = 6, ja[11] = 5, ar[11] = 1.0;
    ia[12] = 6, ja[12] = 10, ar[12] = -1.0;

    // Area 3 BS1 constraint  
    // Service 1
    ia[13] = 7, ja[13] = 3, ar[13] = 1.0;
    ia[14] = 7, ja[14] = 7, ar[14] = -1.0;
    // Service 2
    ia[15] = 8, ja[15] = 6, ar[15] = 1.0;
    ia[16] = 8, ja[16] = 9, ar[16] = -1.0;

    // Area 3 BS2 constraint 
    // Service 1
    ia[17] = 9, ja[17] = 3, ar[17] = 1.0;
    ia[18] = 9, ja[18] = 8, ar[18] = -1.0;
    // service 2
    ia[19] = 10, ja[19] = 6, ar[19] = 1.0;
    ia[20] = 10, ja[20] = 10, ar[20] = -1.0;

    glp_load_matrix(lp, 20, ia, ja, ar);
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
    auto y21 = glp_get_col_prim(lp, 9);
    auto y22 = glp_get_col_prim(lp, 10);
    m_recursosAsignados={x11,x12,x13,x21,x22,x23};
    /* housekeeping */
    glp_delete_prob(lp);
    glp_free_env();
}

std::vector<double> SolverScen1::Decision(){
    return m_recursosAsignados;
}

SolverScen1::~SolverScen1() 
{
}