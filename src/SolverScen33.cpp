#include "SolverScen33.h"
#include "Log.h"
#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <glpk.h>

LOG_REGISTER_MODULE("SolverScen33");

SolverScen33::SolverScen33() 
{
}

void SolverScen33::Init(std::vector<double> coeficientesAreas, std::vector<double> recursosBSfisicas, std::vector<double> recursosminimos)
{
    m_coeficientesAreas=coeficientesAreas;
    m_recursosBSfisicas=recursosBSfisicas;
    m_recursosminimos=recursosminimos;
}

void SolverScen33::Run(){
    glp_prob *lp;
    int ia[1+1000], ja[1+1000];
    double ar[1+1000];
    double k11 = m_coeficientesAreas[0], k12 = m_coeficientesAreas[1], k13 = m_coeficientesAreas[2],  k14 = m_coeficientesAreas[3], k15 = m_coeficientesAreas[4], k16 = m_coeficientesAreas[5], k17 = m_coeficientesAreas[6], k18 = m_coeficientesAreas[7], k19 = m_coeficientesAreas[8], k110 = m_coeficientesAreas[9];
    double k21 = 0, k22 = 0, k23 = 0, k24 = 0, k25 = 0, k26 = 0, k27 = 0, k28 = m_coeficientesAreas[17], k29 = m_coeficientesAreas[18], k210 = m_coeficientesAreas[19];
    double eta1 = m_recursosBSfisicas[0];
    double eta2 = m_recursosBSfisicas[1];
    double eta3 = m_recursosBSfisicas[2];
    double eta4 = m_recursosBSfisicas[3];
    double eta5 = m_recursosBSfisicas[4];
    double eta6 = m_recursosBSfisicas[5];
    double r11 = m_recursosminimos[0], r12 = m_recursosminimos[1], r13 = m_recursosminimos[2], r14 = m_recursosminimos[3], r15 = m_recursosminimos[4], r16 = m_recursosminimos[5], r17 = m_recursosminimos[6], r18 = m_recursosminimos[7], r19 = m_recursosminimos[8], r110 = m_recursosminimos[9];
    double r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = m_recursosminimos[17], r29 = m_recursosminimos[18], r210 = m_recursosminimos[19];
    /* create problem */
    lp = glp_create_prob();
    glp_set_prob_name(lp, "myProblem");
    glp_set_obj_dir(lp, GLP_MIN);
    /* Base station capacity contraints */
    glp_add_rows(lp, 22);
    glp_set_row_name(lp, 1, "bs1");
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, eta1);
    glp_set_row_name(lp, 2, "bs2");
    glp_set_row_bnds(lp, 2, GLP_UP, 0.0, eta2);
    glp_set_row_name(lp, 3, "bs3");
    glp_set_row_bnds(lp, 3, GLP_UP, 0.0, eta3);
    glp_set_row_name(lp, 4, "bs4");
    glp_set_row_bnds(lp, 4, GLP_UP, 0.0, eta4);
    glp_set_row_name(lp, 5, "bs5");
    glp_set_row_bnds(lp, 5, GLP_UP, 0.0, eta5);
    glp_set_row_name(lp, 6, "bs6");
    glp_set_row_bnds(lp, 6, GLP_UP, 0.0, eta6);
    /* Service 1 contraints */
    glp_set_row_name(lp, 7, "s1a4");
    glp_set_row_bnds(lp, 7, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 8, "s1a5");
    glp_set_row_bnds(lp, 8, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 9, "s1a6");
    glp_set_row_bnds(lp, 9, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 10, "s1a71");
    glp_set_row_bnds(lp, 10, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 11, "s1a72");
    glp_set_row_bnds(lp, 11, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 12, "s1a8");
    glp_set_row_bnds(lp, 12, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 13, "s1a9");
    glp_set_row_bnds(lp, 13, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 14, "s1a10");
    glp_set_row_bnds(lp, 14, GLP_FX, 0.0, 0);
    /* Service 2 contraints */
    glp_set_row_name(lp, 15, "s2a4");
    glp_set_row_bnds(lp, 15, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 16, "s2a5");
    glp_set_row_bnds(lp, 16, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 17, "s2a6");
    glp_set_row_bnds(lp, 17, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 18, "s2a71");
    glp_set_row_bnds(lp, 18, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 19, "s2a72");
    glp_set_row_bnds(lp, 19, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 20, "s2a8");
    glp_set_row_bnds(lp, 20, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 21, "s2a9");
    glp_set_row_bnds(lp, 21, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 22, "s2a10");
    glp_set_row_bnds(lp, 22, GLP_FX, 0.0, 0);

    // columns 
    glp_add_cols(lp, 120);
    glp_set_col_name(lp, 1, "x11");
    glp_set_col_bnds(lp, 1, GLP_DB, r11, eta1);
    glp_set_obj_coef(lp, 1, k11);

    glp_set_col_name(lp, 2, "x12");
    glp_set_col_bnds(lp, 2, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 2, 0.0);

    glp_set_col_name(lp, 3, "x13");
    glp_set_col_bnds(lp, 3, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 3, 0.0);

    glp_set_col_name(lp, 4, "x14");
    glp_set_col_bnds(lp, 4, GLP_DB, r14, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 4, k14);

    glp_set_col_name(lp, 5, "x15");
    glp_set_col_bnds(lp, 5, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 5, 0.0);

    glp_set_col_name(lp, 6, "x16");
    glp_set_col_bnds(lp, 6, GLP_DB, r16, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 6, k16);

    glp_set_col_name(lp, 7, "x17");
    glp_set_col_bnds(lp, 7, GLP_DB, r17, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 7, k17);

    glp_set_col_name(lp, 8, "x18");
    glp_set_col_bnds(lp, 8, GLP_DB, r18, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 8, k18);

    glp_set_col_name(lp, 9, "x19");
    glp_set_col_bnds(lp, 9, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 9, 0.0);

    glp_set_col_name(lp, 10, "x110");
    glp_set_col_bnds(lp, 10, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 10, 0.0);

    glp_set_col_name(lp, 11, "x21");
    glp_set_col_bnds(lp, 11, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 11, 0.0);

    glp_set_col_name(lp, 12, "x22");
    glp_set_col_bnds(lp, 12, GLP_DB, r12, eta2);
    glp_set_obj_coef(lp, 12, k12);

    glp_set_col_name(lp, 13, "x23");
    glp_set_col_bnds(lp, 13, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 13, 0.0);

    glp_set_col_name(lp, 14, "x24");
    glp_set_col_bnds(lp, 14, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 14, 0.0);

    glp_set_col_name(lp, 15, "x25");
    glp_set_col_bnds(lp, 15, GLP_DB, r15, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 15, k15);

    glp_set_col_name(lp, 16, "x26");
    glp_set_col_bnds(lp, 16, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 16, 0.0);

    glp_set_col_name(lp, 17, "x27");
    glp_set_col_bnds(lp, 17, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 17, 0.0);

    glp_set_col_name(lp, 18, "x28");
    glp_set_col_bnds(lp, 18, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 18, 0.0);

    glp_set_col_name(lp, 19, "x29");
    glp_set_col_bnds(lp, 19, GLP_DB, r19, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 19, k19);

    glp_set_col_name(lp, 20, "x210");
    glp_set_col_bnds(lp, 20, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 20, 0.0);

    glp_set_col_name(lp, 21, "x31");
    glp_set_col_bnds(lp, 21, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 21, 0.0);

    glp_set_col_name(lp, 22, "x32");
    glp_set_col_bnds(lp, 22, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 22, 0.0);

    glp_set_col_name(lp, 23, "x33");
    glp_set_col_bnds(lp, 23, GLP_DB, r13, eta3);
    glp_set_obj_coef(lp, 23, k13);

    glp_set_col_name(lp, 24, "x34");
    glp_set_col_bnds(lp, 24, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 24, 0.0);

    glp_set_col_name(lp, 25, "x35");
    glp_set_col_bnds(lp, 25, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 25, 0.0);

    glp_set_col_name(lp, 26, "x36");
    glp_set_col_bnds(lp, 26, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 26, 0.0);

    glp_set_col_name(lp, 27, "x37");
    glp_set_col_bnds(lp, 27, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 27, 0.0);

    glp_set_col_name(lp, 28, "x38");
    glp_set_col_bnds(lp, 28, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 28, 0.0);

    glp_set_col_name(lp, 29, "x39");
    glp_set_col_bnds(lp, 29, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 29, 0.0);

    glp_set_col_name(lp, 30, "x310");
    glp_set_col_bnds(lp, 30, GLP_DB, r110, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 30, k110);

    glp_set_col_name(lp, 31, "x41");
    glp_set_col_bnds(lp, 31, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 31, 0.0);

    glp_set_col_name(lp, 32, "x42");
    glp_set_col_bnds(lp, 32, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 32, 0.0);

    glp_set_col_name(lp, 33, "x43");
    glp_set_col_bnds(lp, 33, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 33, 0.0);

    glp_set_col_name(lp, 34, "x44");
    glp_set_col_bnds(lp, 34, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 34, 0.0);

    glp_set_col_name(lp, 35, "x45");
    glp_set_col_bnds(lp, 35, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 35, 0.0);

    glp_set_col_name(lp, 36, "x46");
    glp_set_col_bnds(lp, 36, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 36, 0.0);

    glp_set_col_name(lp, 37, "x47");
    glp_set_col_bnds(lp, 37, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 37, 0.0);

    glp_set_col_name(lp, 38, "x48");
    glp_set_col_bnds(lp, 38, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 38, 0.0);

    glp_set_col_name(lp, 39, "x49");
    glp_set_col_bnds(lp, 39, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 39, 0.0);

    glp_set_col_name(lp, 40, "x410");
    glp_set_col_bnds(lp, 40, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 40, 0.0);

    glp_set_col_name(lp, 41, "x51");
    glp_set_col_bnds(lp, 41, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 41, 0.0);

    glp_set_col_name(lp, 42, "x52");
    glp_set_col_bnds(lp, 42, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 42, 0.0);

    glp_set_col_name(lp, 43, "x53");
    glp_set_col_bnds(lp, 43, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 43, 0.0);

    glp_set_col_name(lp, 44, "x54");
    glp_set_col_bnds(lp, 44, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 44, 0.0);

    glp_set_col_name(lp, 45, "x55");
    glp_set_col_bnds(lp, 45, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 45, 0.0);

    glp_set_col_name(lp, 46, "x56");
    glp_set_col_bnds(lp, 46, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 46, 0.0);

    glp_set_col_name(lp, 47, "x57");
    glp_set_col_bnds(lp, 47, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 47, 0.0);

    glp_set_col_name(lp, 48, "x58");
    glp_set_col_bnds(lp, 48, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 48, 0.0);

    glp_set_col_name(lp, 49, "x59");
    glp_set_col_bnds(lp, 49, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 49, 0.0);

    glp_set_col_name(lp, 50, "x510");
    glp_set_col_bnds(lp, 50, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 50, 0.0);

    glp_set_col_name(lp, 51, "x61");
    glp_set_col_bnds(lp, 51, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 51, 0.0);

    glp_set_col_name(lp, 52, "x62");
    glp_set_col_bnds(lp, 52, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 52, 0.0);

    glp_set_col_name(lp, 53, "x63");
    glp_set_col_bnds(lp, 53, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 53, 0.0);

    glp_set_col_name(lp, 54, "x64");
    glp_set_col_bnds(lp, 54, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 54, 0.0);

    glp_set_col_name(lp, 55, "x65");
    glp_set_col_bnds(lp, 55, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 55, 0.0);

    glp_set_col_name(lp, 56, "x66");
    glp_set_col_bnds(lp, 56, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 56, 0.0);

    glp_set_col_name(lp, 57, "x67");
    glp_set_col_bnds(lp, 57, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 57, 0.0);

    glp_set_col_name(lp, 58, "x68");
    glp_set_col_bnds(lp, 58, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 58, 0.0);

    glp_set_col_name(lp, 59, "x69");
    glp_set_col_bnds(lp, 59, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 59, 0.0);

    glp_set_col_name(lp, 60, "x610");
    glp_set_col_bnds(lp, 60, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 60, 0.0);

    glp_set_col_name(lp, 61, "y11");
    glp_set_col_bnds(lp, 61, GLP_DB, r21, eta1);
    glp_set_obj_coef(lp, 61, k21);

    glp_set_col_name(lp, 62, "y12");
    glp_set_col_bnds(lp, 62, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 62, 0.0);

    glp_set_col_name(lp, 63, "y13");
    glp_set_col_bnds(lp, 63, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 63, 0.0);

    glp_set_col_name(lp, 64, "y14");
    glp_set_col_bnds(lp, 64, GLP_DB, r24, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 64, k24);

    glp_set_col_name(lp, 65, "y15");
    glp_set_col_bnds(lp, 65, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 65, 0.0);

    glp_set_col_name(lp, 66, "y16");
    glp_set_col_bnds(lp, 66, GLP_DB, r26, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 66, k26);

    glp_set_col_name(lp, 67, "y17");
    glp_set_col_bnds(lp, 67, GLP_DB, r27, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 67, k27);

    glp_set_col_name(lp, 68, "y18");
    glp_set_col_bnds(lp, 68, GLP_DB, r28, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 68, k28);

    glp_set_col_name(lp, 69, "y19");
    glp_set_col_bnds(lp, 69, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 69, 0.0);

    glp_set_col_name(lp, 70, "y110");
    glp_set_col_bnds(lp, 70, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 70, 0.0);

    glp_set_col_name(lp, 71, "y21");
    glp_set_col_bnds(lp, 71, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 71, 0.0);

    glp_set_col_name(lp, 72, "y22");
    glp_set_col_bnds(lp, 72, GLP_DB, r22, eta2);
    glp_set_obj_coef(lp, 72, k22);

    glp_set_col_name(lp, 73, "y23");
    glp_set_col_bnds(lp, 73, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 73, 0.0);

    glp_set_col_name(lp, 74, "y24");
    glp_set_col_bnds(lp, 74, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 74, 0.0);

    glp_set_col_name(lp, 75, "y25");
    glp_set_col_bnds(lp, 75, GLP_DB, r25, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 75, k25);

    glp_set_col_name(lp, 76, "y26");
    glp_set_col_bnds(lp, 76, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 76, 0.0);

    glp_set_col_name(lp, 77, "y27");
    glp_set_col_bnds(lp, 77, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 77, 0.0);

    glp_set_col_name(lp, 78, "y28");
    glp_set_col_bnds(lp, 78, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 78, 0.0);

    glp_set_col_name(lp, 79, "y29");
    glp_set_col_bnds(lp, 79, GLP_DB, r29, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 79, k29);

    glp_set_col_name(lp, 80, "y210");
    glp_set_col_bnds(lp, 80, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 80, 0.0);

    glp_set_col_name(lp, 81, "y31");
    glp_set_col_bnds(lp, 81, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 81, 0.0);

    glp_set_col_name(lp, 82, "y32");
    glp_set_col_bnds(lp, 82, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 82, 0.0);

    glp_set_col_name(lp, 83, "y33");
    glp_set_col_bnds(lp, 83, GLP_DB, r23, eta3);
    glp_set_obj_coef(lp, 83, k23);

    glp_set_col_name(lp, 84, "y34");
    glp_set_col_bnds(lp, 84, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 84, 0.0);

    glp_set_col_name(lp, 85, "y35");
    glp_set_col_bnds(lp, 85, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 85, 0.0);

    glp_set_col_name(lp, 86, "y36");
    glp_set_col_bnds(lp, 86, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 86, 0.0);

    glp_set_col_name(lp, 87, "y37");
    glp_set_col_bnds(lp, 87, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 87, 0.0);

    glp_set_col_name(lp, 88, "y38");
    glp_set_col_bnds(lp, 88, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 88, 0.0);

    glp_set_col_name(lp, 89, "y39");
    glp_set_col_bnds(lp, 89, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 89, 0.0);

    glp_set_col_name(lp, 90, "y310");
    glp_set_col_bnds(lp, 90, GLP_DB, r210, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 90, k210);

    glp_set_col_name(lp, 91, "y41");
    glp_set_col_bnds(lp, 91, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 91, 0.0);

    glp_set_col_name(lp, 92, "y42");
    glp_set_col_bnds(lp, 92, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 92, 0.0);

    glp_set_col_name(lp, 93, "y43");
    glp_set_col_bnds(lp, 93, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 93, 0.0);

    glp_set_col_name(lp, 94, "y44");
    glp_set_col_bnds(lp, 94, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 94, 0.0);

    glp_set_col_name(lp, 95, "y45");
    glp_set_col_bnds(lp, 95, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 95, 0.0);

    glp_set_col_name(lp, 96, "y46");
    glp_set_col_bnds(lp, 96, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 96, 0.0);

    glp_set_col_name(lp, 97, "y47");
    glp_set_col_bnds(lp, 97, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 97, 0.0);

    glp_set_col_name(lp, 98, "y48");
    glp_set_col_bnds(lp, 98, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 98, 0.0);

    glp_set_col_name(lp, 99, "y49");
    glp_set_col_bnds(lp, 99, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 99, 0.0);

    glp_set_col_name(lp, 100, "y410");
    glp_set_col_bnds(lp, 100, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 100, 0.0);

    glp_set_col_name(lp, 101, "y51");
    glp_set_col_bnds(lp, 101, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 101, 0.0);

    glp_set_col_name(lp, 102, "y52");
    glp_set_col_bnds(lp, 102, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 102, 0.0);

    glp_set_col_name(lp, 103, "y53");
    glp_set_col_bnds(lp, 103, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 103, 0.0);

    glp_set_col_name(lp, 104, "y54");
    glp_set_col_bnds(lp, 104, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 104, 0.0);

    glp_set_col_name(lp, 105, "y55");
    glp_set_col_bnds(lp, 105, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 105, 0.0);

    glp_set_col_name(lp, 106, "y56");
    glp_set_col_bnds(lp, 106, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 106, 0.0);

    glp_set_col_name(lp, 107, "y57");
    glp_set_col_bnds(lp, 107, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 107, 0.0);

    glp_set_col_name(lp, 108, "y58");
    glp_set_col_bnds(lp, 108, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 108, 0.0);

    glp_set_col_name(lp, 109, "y59");
    glp_set_col_bnds(lp, 109, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 109, 0.0);

    glp_set_col_name(lp, 110, "y510");
    glp_set_col_bnds(lp, 110, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 110, 0.0);

    glp_set_col_name(lp, 111, "y61");
    glp_set_col_bnds(lp, 111, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 111, 0.0);

    glp_set_col_name(lp, 112, "y62");
    glp_set_col_bnds(lp, 112, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 112, 0.0);

    glp_set_col_name(lp, 113, "y63");
    glp_set_col_bnds(lp, 113, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 113, 0.0);

    glp_set_col_name(lp, 114, "y64");
    glp_set_col_bnds(lp, 114, GLP_DB, 0.0, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 114, 0.0);

    glp_set_col_name(lp, 115, "y65");
    glp_set_col_bnds(lp, 115, GLP_DB, 0.0, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 115, 0.0);

    glp_set_col_name(lp, 116, "y66");
    glp_set_col_bnds(lp, 116, GLP_DB, 0.0, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 116, 0.0);

    glp_set_col_name(lp, 117, "y67");
    glp_set_col_bnds(lp, 117, GLP_DB, 0.0, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 117, 0.0);

    glp_set_col_name(lp, 118, "y68");
    glp_set_col_bnds(lp, 118, GLP_DB, 0.0, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 118, 0.0);

    glp_set_col_name(lp, 119, "y69");
    glp_set_col_bnds(lp, 119, GLP_DB, 0.0, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 119, 0.0);

    glp_set_col_name(lp, 120, "y610");
    glp_set_col_bnds(lp, 120, GLP_DB, 0.0, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 120, 0.0);

    // BS1 constraint  
    ia[1] = 1, ja[1] = 1, ar[1] = 1.0;
    ia[2] = 1, ja[2] = 4, ar[2] = 1.0; 
    ia[3] = 1, ja[3] = 6, ar[3] = 1.0;
    ia[4] = 1, ja[4] = 7, ar[4] = 1.0;
    ia[5] = 1, ja[5] = 8, ar[5] = 1.0;
    ia[6] = 1, ja[6] = 61, ar[6] = 1.0;
    ia[7] = 1, ja[7] = 64, ar[7] = 1.0;
    ia[8] = 1, ja[8] = 66, ar[8] = 1.0;
    ia[9] = 1, ja[9] = 67, ar[9] = 1.0;
    ia[10] = 1, ja[10] = 68, ar[10] = 1.0;

    // BS2 constraint 
    ia[11] = 2, ja[11] = 12, ar[11] = 1.0;
    ia[12] = 2, ja[12] = 14, ar[12] = 1.0;
    ia[13] = 2, ja[13] = 15, ar[13] = 1.0;
    ia[14] = 2, ja[14] = 17, ar[14] = 1.0;
    ia[15] = 2, ja[15] = 19, ar[15] = 1.0;
    ia[16] = 2, ja[16] = 72, ar[16] = 1.0;
    ia[17] = 2, ja[17] = 74, ar[17] = 1.0;
    ia[18] = 2, ja[18] = 75, ar[18] = 1.0;
    ia[19] = 2, ja[19] = 77, ar[19] = 1.0;
    ia[20] = 2, ja[20] = 79, ar[20] = 1.0;

    // BS3 constraint  
    ia[21] = 3, ja[21] = 23, ar[21] = 1.0;
    ia[22] = 3, ja[22] = 25, ar[22] = 1.0;
    ia[23] = 3, ja[23] = 26, ar[23] = 1.0;
    ia[24] = 3, ja[24] = 27, ar[24] = 1.0;
    ia[25] = 3, ja[25] = 30, ar[25] = 1.0;
    ia[26] = 3, ja[26] = 83, ar[26] = 1.0;
    ia[27] = 3, ja[27] = 85, ar[27] = 1.0;
    ia[28] = 3, ja[28] = 86, ar[28] = 1.0;
    ia[29] = 3, ja[29] = 87, ar[29] = 1.0;
    ia[30] = 3, ja[30] = 90, ar[30] = 1.0;

    // BS4 constraint
    ia[31] = 4, ja[31] = 38, ar[31] = 1.0;
    ia[32] = 4, ja[32] = 98, ar[32] = 1.0;

    // BS5 constraint
    ia[33] = 5, ja[33] = 49, ar[33] = 1.0;
    ia[34] = 5, ja[34] = 109, ar[34] = 1.0;

    // BS6 constraint
    ia[35] = 6, ja[35] = 60, ar[35] = 1.0;
    ia[36] = 6, ja[36] = 120, ar[36] = 1.0;

    // Service 1 - area 4
    ia[37] = 7, ja[37] = 4, ar[37] = 1.0;
    ia[38] = 7, ja[38] = 14, ar[38] = -1.0;

    // Service 1 - area 5
    ia[39] = 8, ja[39] = 15, ar[39] = 1.0;
    ia[40] = 8, ja[40] = 25, ar[40] = -1.0;

    // Service 1 - area 6
    ia[41] = 9, ja[41] = 6, ar[41] = 1.0;
    ia[42] = 9, ja[42] = 26, ar[42] = -1.0;

    // Service 1 - area 7 1
    ia[43] = 10, ja[43] = 7, ar[43] = 1.0;
    ia[44] = 10, ja[44] = 17, ar[44] = -1.0;

    // Service 1 - area 7 2
    ia[45] = 11, ja[45] = 7, ar[45] = 1.0;
    ia[46] = 11, ja[46] = 27, ar[46] = -1.0;

    // Service 1 - area 8
    ia[47] = 12, ja[47] = 8, ar[47] = 1.0;
    ia[48] = 12, ja[48] = 38, ar[48] = -1.0;

    // Service 1 - area 9
    ia[49] = 13, ja[49] = 19, ar[49] = 1.0;
    ia[50] = 13, ja[50] = 49, ar[50] = -1.0;

    // Service 1 - area 10
    ia[51] = 14, ja[51] = 30, ar[51] = 1.0;
    ia[52] = 14, ja[52] = 60, ar[52] = -1.0;

    // Service 2 - area 4
    ia[53] = 15, ja[53] = 64, ar[53] = 1.0;
    ia[54] = 15, ja[54] = 74, ar[54] = -1.0;

    // Service 2 - area 5
    ia[55] = 16, ja[55] = 75, ar[55] = 1.0;
    ia[56] = 16, ja[56] = 85, ar[56] = -1.0;

    // Service 2 - area 6
    ia[57] = 17, ja[57] = 66, ar[57] = 1.0;
    ia[58] = 17, ja[58] = 86, ar[58] = -1.0;

    // Service 2 - area 7 1
    ia[59] = 18, ja[59] = 67, ar[59] = 1.0;
    ia[60] = 18, ja[60] = 77, ar[60] = -1.0;

    // Service 2 - area 7 2
    ia[61] = 19, ja[61] = 67, ar[61] = 1.0;
    ia[62] = 19, ja[62] = 87, ar[62] = -1.0;

    // Service 2 - area 8
    ia[63] = 20, ja[63] = 68, ar[63] = 1.0;
    ia[64] = 20, ja[64] = 98, ar[64] = -1.0;

    // Service 2 - area 9
    ia[65] = 21, ja[65] = 79, ar[65] = 1.0;
    ia[66] = 21, ja[66] = 109, ar[66] = -1.0;

    // Service 2 - area 10
    ia[67] = 22, ja[67] = 90, ar[67] = 1.0;
    ia[68] = 22, ja[68] = 120, ar[68] = -1.0;

    glp_load_matrix(lp, 68, ia, ja, ar);
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
    auto x14 = glp_get_col_prim(lp, 4);
    auto x15 = glp_get_col_prim(lp, 5);
    auto x16 = glp_get_col_prim(lp, 6);
    auto x17 = glp_get_col_prim(lp, 7);
    auto x18 = glp_get_col_prim(lp, 8);
    auto x19 = glp_get_col_prim(lp, 9);
    auto x110 = glp_get_col_prim(lp, 10);
    auto x21 = glp_get_col_prim(lp, 11);
    auto x22 = glp_get_col_prim(lp, 12);
    auto x23 = glp_get_col_prim(lp, 13);
    auto x24 = glp_get_col_prim(lp, 14);
    auto x25 = glp_get_col_prim(lp, 15);
    auto x26 = glp_get_col_prim(lp, 16);
    auto x27 = glp_get_col_prim(lp, 17);
    auto x28 = glp_get_col_prim(lp, 18);
    auto x29 = glp_get_col_prim(lp, 19);
    auto x210 = glp_get_col_prim(lp, 20);
    auto x31 = glp_get_col_prim(lp, 21);
    auto x32 = glp_get_col_prim(lp, 22);
    auto x33 = glp_get_col_prim(lp, 23);
    auto x34 = glp_get_col_prim(lp, 24);
    auto x35 = glp_get_col_prim(lp, 25);
    auto x36 = glp_get_col_prim(lp, 26);
    auto x37 = glp_get_col_prim(lp, 27);
    auto x38 = glp_get_col_prim(lp, 28);
    auto x39 = glp_get_col_prim(lp, 29);
    auto x310 = glp_get_col_prim(lp, 30);
    auto x41 = glp_get_col_prim(lp, 31);
    auto x42 = glp_get_col_prim(lp, 32);
    auto x43 = glp_get_col_prim(lp, 33);
    auto x44 = glp_get_col_prim(lp, 34);
    auto x45 = glp_get_col_prim(lp, 35);
    auto x46 = glp_get_col_prim(lp, 36);
    auto x47 = glp_get_col_prim(lp, 37);
    auto x48 = glp_get_col_prim(lp, 38);
    auto x49 = glp_get_col_prim(lp, 39);
    auto x410 = glp_get_col_prim(lp, 40);
    auto x51 = glp_get_col_prim(lp, 41);
    auto x52 = glp_get_col_prim(lp, 42);
    auto x53 = glp_get_col_prim(lp, 43);
    auto x54 = glp_get_col_prim(lp, 44);
    auto x55 = glp_get_col_prim(lp, 45);
    auto x56 = glp_get_col_prim(lp, 46);
    auto x57 = glp_get_col_prim(lp, 47);
    auto x58 = glp_get_col_prim(lp, 48);
    auto x59 = glp_get_col_prim(lp, 49);
    auto x510 = glp_get_col_prim(lp, 50);
    auto x61 = glp_get_col_prim(lp, 51);
    auto x62 = glp_get_col_prim(lp, 52);
    auto x63 = glp_get_col_prim(lp, 53);
    auto x64 = glp_get_col_prim(lp, 54);
    auto x65 = glp_get_col_prim(lp, 55);
    auto x66 = glp_get_col_prim(lp, 56);
    auto x67 = glp_get_col_prim(lp, 57);
    auto x68 = glp_get_col_prim(lp, 58);
    auto x69 = glp_get_col_prim(lp, 59);
    auto x610 = glp_get_col_prim(lp, 60);
    auto y11 = glp_get_col_prim(lp, 61);
    auto y12 = glp_get_col_prim(lp, 62);
    auto y13 = glp_get_col_prim(lp, 63);
    auto y14 = glp_get_col_prim(lp, 64);
    auto y15 = glp_get_col_prim(lp, 65);
    auto y16 = glp_get_col_prim(lp, 66);
    auto y17 = glp_get_col_prim(lp, 67);
    auto y18 = glp_get_col_prim(lp, 68);
    auto y19 = glp_get_col_prim(lp, 69);
    auto y110 = glp_get_col_prim(lp, 70);
    auto y21 = glp_get_col_prim(lp, 71);
    auto y22 = glp_get_col_prim(lp, 72);
    auto y23 = glp_get_col_prim(lp, 73);
    auto y24 = glp_get_col_prim(lp, 74);
    auto y25 = glp_get_col_prim(lp, 75);
    auto y26 = glp_get_col_prim(lp, 76);
    auto y27 = glp_get_col_prim(lp, 77);
    auto y28 = glp_get_col_prim(lp, 78);
    auto y29 = glp_get_col_prim(lp, 79);
    auto y210 = glp_get_col_prim(lp, 80);
    auto y31 = glp_get_col_prim(lp, 81);
    auto y32 = glp_get_col_prim(lp, 82);
    auto y33 = glp_get_col_prim(lp, 83);
    auto y34 = glp_get_col_prim(lp, 84);
    auto y35 = glp_get_col_prim(lp, 85);
    auto y36 = glp_get_col_prim(lp, 86);
    auto y37 = glp_get_col_prim(lp, 87);
    auto y38 = glp_get_col_prim(lp, 88);
    auto y39 = glp_get_col_prim(lp, 89);
    auto y310 = glp_get_col_prim(lp, 90);
    auto y41 = glp_get_col_prim(lp, 91);
    auto y42 = glp_get_col_prim(lp, 92);
    auto y43 = glp_get_col_prim(lp, 93);
    auto y44 = glp_get_col_prim(lp, 94);
    auto y45 = glp_get_col_prim(lp, 95);
    auto y46 = glp_get_col_prim(lp, 96);
    auto y47 = glp_get_col_prim(lp, 97);
    auto y48 = glp_get_col_prim(lp, 98);
    auto y49 = glp_get_col_prim(lp, 99);
    auto y410 = glp_get_col_prim(lp, 100);
    auto y51 = glp_get_col_prim(lp, 101);
    auto y52 = glp_get_col_prim(lp, 102);
    auto y53 = glp_get_col_prim(lp, 103);
    auto y54 = glp_get_col_prim(lp, 104);
    auto y55 = glp_get_col_prim(lp, 105);
    auto y56 = glp_get_col_prim(lp, 106);
    auto y57 = glp_get_col_prim(lp, 107);
    auto y58 = glp_get_col_prim(lp, 108);
    auto y59 = glp_get_col_prim(lp, 109);
    auto y510 = glp_get_col_prim(lp, 110);
    auto y61 = glp_get_col_prim(lp, 111);
    auto y62 = glp_get_col_prim(lp, 112);
    auto y63 = glp_get_col_prim(lp, 113);
    auto y64 = glp_get_col_prim(lp, 114);
    auto y65 = glp_get_col_prim(lp, 115);
    auto y66 = glp_get_col_prim(lp, 116);
    auto y67 = glp_get_col_prim(lp, 117);
    auto y68 = glp_get_col_prim(lp, 118);
    auto y69 = glp_get_col_prim(lp, 119);
    auto y610 = glp_get_col_prim(lp, 120);

    m_recursosAsignados={x11,x12,x13,x14,x15,x16,x17,x18,x19,x110,y11,y12,y13,y14,y15,y16,y17,y18,y19,y110,x21,x22,x23,x24,x25,x26,x27,x28,x29,x210,y21,y22,y23,y24,y25,y26,y27,y28,y29,y210,x31,x32,x33,x34,x35,x36,x37,x38,x39,x310,y31,y32,y33,y34,y35,y36,y37,y38,y39,y310,x41,x42,x43,x44,x45,x46,x47,x48,x49,x410,y41,y42,y43,y44,y45,y46,y47,y48,y49,y410,x51,x52,x53,x54,x55,x56,x57,x58,x59,x510,y51,y52,y53,y54,y55,y56,y57,y58,y59,y510,x61,x62,x63,x64,x65,x66,x67,x68,x69,x610,y61,y62,y63,y64,y65,y66,y67,y68,y69,y610};
    m_z=z;
    /* housekeeping */
    glp_delete_prob(lp);
    glp_free_env();

}

std::vector<double> SolverScen33::Decision(){
    return m_recursosAsignados;
}

double SolverScen33::Optimalvalue(){
    return m_z;
}

SolverScen33::~SolverScen33() 
{
}