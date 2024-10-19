#include "SolverScen3.h"
#include "Log.h"
#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <glpk.h>

LOG_REGISTER_MODULE("SolverScen3");

SolverScen3::SolverScen3() 
{
}

void SolverScen3::Init(std::vector<double> coeficientesAreas, std::vector<double> recursosBSfisicas, std::vector<double> recursosminimos)
{
    m_coeficientesAreas=coeficientesAreas;
    m_recursosBSfisicas=recursosBSfisicas;
    m_recursosminimos=recursosminimos;
}


void SolverScen3::Run()
{
    glp_prob *lp;
    int ia[1+1000], ja[1+1000];
    double ar[1+1000];
    double k11 = m_coeficientesAreas[0], k12 = m_coeficientesAreas[1], k13 = m_coeficientesAreas[2],  k14 = m_coeficientesAreas[3], k15 = m_coeficientesAreas[4], k16 = m_coeficientesAreas[5], k17 = m_coeficientesAreas[6], k18 = m_coeficientesAreas[7], k19 = m_coeficientesAreas[8], k110 = m_coeficientesAreas[9];
    double k21 = m_coeficientesAreas[10], k22 = m_coeficientesAreas[11], k23 = m_coeficientesAreas[12], k24 = m_coeficientesAreas[13], k25 = m_coeficientesAreas[14], k26 = m_coeficientesAreas[15], k27 = m_coeficientesAreas[16], k28 = m_coeficientesAreas[17], k29 = m_coeficientesAreas[18], k210 = m_coeficientesAreas[19];
    double eta1 = m_recursosBSfisicas[0];
    double eta2 = m_recursosBSfisicas[1];
    double eta3 = m_recursosBSfisicas[2];
    double eta4 = m_recursosBSfisicas[3];
    double eta5 = m_recursosBSfisicas[4];
    double eta6 = m_recursosBSfisicas[5];
    double r11 = m_recursosminimos[0], r12 = m_recursosminimos[1], r13 = m_recursosminimos[2], r14 = m_recursosminimos[3], r15 = m_recursosminimos[4], r16 = m_recursosminimos[5], r17 = m_recursosminimos[6], r18 = m_recursosminimos[7], r19 = m_recursosminimos[8], r110 = m_recursosminimos[9];
    double r21 = m_recursosminimos[10], r22 = m_recursosminimos[11], r23 = m_recursosminimos[12], r24 = m_recursosminimos[13], r25 = m_recursosminimos[14], r26 = m_recursosminimos[15], r27 = m_recursosminimos[16], r28 = m_recursosminimos[17], r29 = m_recursosminimos[18], r210 = m_recursosminimos[19];
    /* create problem */
    lp = glp_create_prob();
    glp_set_prob_name(lp, "myProblem");
    glp_set_obj_dir(lp, GLP_MIN);
    /* Base station capacity contraints */
    glp_add_rows(lp, 42);
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
    /* Area 1 contraints */
    glp_set_row_name(lp, 7, "a1b1s1");
    glp_set_row_bnds(lp, 7, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 8, "a1b1s2");
    glp_set_row_bnds(lp, 8, GLP_FX, 0.0, 0);
    /* Area 2 contraints */
    glp_set_row_name(lp, 9, "a2b2s1");
    glp_set_row_bnds(lp, 9, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 10, "a2b2s2");
    glp_set_row_bnds(lp, 10, GLP_FX, 0.0, 0);
    /* Area 3 contraints */
    glp_set_row_name(lp, 11, "a3b3s1");
    glp_set_row_bnds(lp, 11, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 12, "a3b3s2");
    glp_set_row_bnds(lp, 12, GLP_FX, 0.0, 0);
    /* Area 4 contraints */
    glp_set_row_name(lp, 13, "a4b1s1");
    glp_set_row_bnds(lp, 13, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 14, "a4b1s2");
    glp_set_row_bnds(lp, 14, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 15, "a4b2s1");
    glp_set_row_bnds(lp, 15, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 16, "a4b2s2");
    glp_set_row_bnds(lp, 16, GLP_FX, 0.0, 0);
    /* Area 5 contraints */
    glp_set_row_name(lp, 17, "a5b2s1");
    glp_set_row_bnds(lp, 17, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 18, "a5b2s2");
    glp_set_row_bnds(lp, 18, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 19, "a5b3s1");
    glp_set_row_bnds(lp, 19, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 20, "a5b3s2");
    glp_set_row_bnds(lp, 20, GLP_FX, 0.0, 0);
    /* Area 6 contraints */
    glp_set_row_name(lp, 21, "a6b1s1");
    glp_set_row_bnds(lp, 21, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 22, "a6b1s2");
    glp_set_row_bnds(lp, 22, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 23, "a6b3s1");
    glp_set_row_bnds(lp, 23, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 24, "a6b3s2");
    glp_set_row_bnds(lp, 24, GLP_FX, 0.0, 0);
    /* Area 7 contraints */
    glp_set_row_name(lp, 25, "a7b1s1");
    glp_set_row_bnds(lp, 25, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 26, "a7b1s2");
    glp_set_row_bnds(lp, 26, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 27, "a7b2s1");
    glp_set_row_bnds(lp, 27, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 28, "a7b2s2");
    glp_set_row_bnds(lp, 28, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 29, "a7b3s1");
    glp_set_row_bnds(lp, 29, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 30, "a7b3s2");
    glp_set_row_bnds(lp, 30, GLP_FX, 0.0, 0);
    /* Area 8 contraints */
    glp_set_row_name(lp, 31, "a8b1s1");
    glp_set_row_bnds(lp, 31, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 32, "a8b1s2");
    glp_set_row_bnds(lp, 32, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 33, "a8b4s1");
    glp_set_row_bnds(lp, 33, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 34, "a8b4s2");
    glp_set_row_bnds(lp, 34, GLP_FX, 0.0, 0);
    /* Area 9 contraints */
    glp_set_row_name(lp, 35, "a9b2s1");
    glp_set_row_bnds(lp, 35, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 36, "a9b2s2");
    glp_set_row_bnds(lp, 36, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 37, "a9b5s1");
    glp_set_row_bnds(lp, 37, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 38, "a9b5s2");
    glp_set_row_bnds(lp, 38, GLP_FX, 0.0, 0);
    /* Area 10 contraints */
    glp_set_row_name(lp, 39, "a10b3s1");
    glp_set_row_bnds(lp, 39, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 40, "a10b3s2");
    glp_set_row_bnds(lp, 40, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 41, "a10b6s1");
    glp_set_row_bnds(lp, 41, GLP_FX, 0.0, 0);
    glp_set_row_name(lp, 42, "a10b6s2");
    glp_set_row_bnds(lp, 42, GLP_FX, 0.0, 0);
 
    // columns 
    glp_add_cols(lp, 32);
    glp_set_col_name(lp, 1, "x11");
    glp_set_col_bnds(lp, 1, GLP_DB, r11, eta1);
    glp_set_obj_coef(lp, 1, k11);

    glp_set_col_name(lp, 2, "x12");
    glp_set_col_bnds(lp, 2, GLP_DB, r12, eta2);
    glp_set_obj_coef(lp, 2, k12);

    glp_set_col_name(lp, 3, "x13");
    glp_set_col_bnds(lp, 3, GLP_DB, r13, eta3);
    glp_set_obj_coef(lp, 3, k13);

    glp_set_col_name(lp, 4, "x14");
    glp_set_col_bnds(lp, 4, GLP_DB, r14, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 4, k14);

    glp_set_col_name(lp, 5, "x15");
    glp_set_col_bnds(lp, 5, GLP_DB, r15, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 5, k15);

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
    glp_set_col_bnds(lp, 9, GLP_DB, r19, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 9, k19);

    glp_set_col_name(lp, 10, "x110");
    glp_set_col_bnds(lp, 10, GLP_DB, r110, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 10, k110);

    glp_set_col_name(lp, 11, "x21");
    glp_set_col_bnds(lp, 11, GLP_DB, r21, eta1);
    glp_set_obj_coef(lp, 11, k21);

    glp_set_col_name(lp, 12, "x22");
    glp_set_col_bnds(lp, 12, GLP_DB, r22, eta2);
    glp_set_obj_coef(lp, 12, k22);

    glp_set_col_name(lp, 13, "x23");
    glp_set_col_bnds(lp, 13, GLP_DB, r23, eta3);
    glp_set_obj_coef(lp, 13, k23);

    glp_set_col_name(lp, 14, "x24");
    glp_set_col_bnds(lp, 14, GLP_DB, r24, std::min(eta1, eta2));
    glp_set_obj_coef(lp, 14, k24);

    glp_set_col_name(lp, 15, "x25");
    glp_set_col_bnds(lp, 15, GLP_DB, r25, std::min(eta2, eta3));
    glp_set_obj_coef(lp, 15, k25);

    glp_set_col_name(lp, 16, "x26");
    glp_set_col_bnds(lp, 16, GLP_DB, r26, std::min(eta1, eta3));
    glp_set_obj_coef(lp, 16, k26);

    glp_set_col_name(lp, 17, "x27");
    glp_set_col_bnds(lp, 17, GLP_DB, r27, std::min(std::min(eta1, eta2), std::min(eta2, eta3)));
    glp_set_obj_coef(lp, 17, k27);

    glp_set_col_name(lp, 18, "x28");
    glp_set_col_bnds(lp, 18, GLP_DB, r28, std::min(eta1, eta4));
    glp_set_obj_coef(lp, 18, k28);

    glp_set_col_name(lp, 19, "x29");
    glp_set_col_bnds(lp, 19, GLP_DB, r29, std::min(eta2, eta5));
    glp_set_obj_coef(lp, 19, k29);

    glp_set_col_name(lp, 20, "x210");
    glp_set_col_bnds(lp, 20, GLP_DB, r210, std::min(eta3, eta6));
    glp_set_obj_coef(lp, 20, k210);

    glp_set_col_name(lp, 21, "y11");
    glp_set_col_bnds(lp, 21, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 21, 0.0);

    glp_set_col_name(lp, 22, "y12");
    glp_set_col_bnds(lp, 22, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 22, 0.0);

    glp_set_col_name(lp, 23, "y13");
    glp_set_col_bnds(lp, 23, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 23, 0.0);

    glp_set_col_name(lp, 24, "y14");
    glp_set_col_bnds(lp, 24, GLP_DB, 0.0, eta4);
    glp_set_obj_coef(lp, 24, 0.0);

    glp_set_col_name(lp, 25, "y15");
    glp_set_col_bnds(lp, 25, GLP_DB, 0.0, eta5);
    glp_set_obj_coef(lp, 25, 0.0);

    glp_set_col_name(lp, 26, "y16");
    glp_set_col_bnds(lp, 26, GLP_DB, 0.0, eta6);
    glp_set_obj_coef(lp, 26, 0.0);

    glp_set_col_name(lp, 27, "y21");
    glp_set_col_bnds(lp, 27, GLP_DB, 0.0, eta1);
    glp_set_obj_coef(lp, 27, 0.0);

    glp_set_col_name(lp, 28, "y22");
    glp_set_col_bnds(lp, 28, GLP_DB, 0.0, eta2);
    glp_set_obj_coef(lp, 28, 0.0);

    glp_set_col_name(lp, 29, "y23");
    glp_set_col_bnds(lp, 29, GLP_DB, 0.0, eta3);
    glp_set_obj_coef(lp, 29, 0.0);

    glp_set_col_name(lp, 30, "y24");
    glp_set_col_bnds(lp, 30, GLP_DB, 0.0, eta4);
    glp_set_obj_coef(lp, 30, 0.0);

    glp_set_col_name(lp, 31, "y25");
    glp_set_col_bnds(lp, 31, GLP_DB, 0.0, eta5);
    glp_set_obj_coef(lp, 31, 0.0);

    glp_set_col_name(lp, 32, "y26");
    glp_set_col_bnds(lp, 32, GLP_DB, 0.0, eta6);
    glp_set_obj_coef(lp, 32, 0.0);
    
    // BS1 constraint  
    ia[1] = 1, ja[1] = 21, ar[1] = 1.0;
    ia[2] = 1, ja[2] = 27, ar[2] = 1.0;

    // BS2 constraint  
    ia[3] = 2, ja[3] = 22, ar[3] = 1.0;
    ia[4] = 2, ja[4] = 28, ar[4] = 1.0;

    // BS3 constraint  
    ia[5] = 3, ja[5] = 23, ar[5] = 1.0;
    ia[6] = 3, ja[6] = 29, ar[6] = 1.0;

    // BS4 constraint  
    ia[7] = 4, ja[7] = 24, ar[7] = 1.0;
    ia[8] = 4, ja[8] = 30, ar[8] = 1.0;

    // BS5 constraint  
    ia[9] = 5, ja[9] = 25, ar[9] = 1.0;
    ia[10] = 5, ja[10] = 31, ar[10] = 1.0;

    // BS6 constraint  
    ia[11] = 6, ja[11] = 26, ar[11] = 1.0;
    ia[12] = 6, ja[12] = 32, ar[12] = 1.0;

    // Area 1 bs1
    // Service 1
    ia[13] = 7, ja[13] = 1, ar[13] = 1.0;
    ia[14] = 7, ja[14] = 21, ar[14] = -1.0;
    // service 2
    ia[15] = 8, ja[15] = 11, ar[15] = 1.0;
    ia[16] = 8, ja[16] = 27, ar[16] = -1.0;

    // Area 2 BS2 constraint  
    // Service 1
    ia[17] = 9, ja[17] = 2, ar[17] = 1.0;
    ia[18] = 9, ja[18] = 22, ar[18] = -1.0;
    // Service 2
    ia[19] = 10, ja[19] = 12, ar[19] = 1.0;
    ia[20] = 10, ja[20] = 28, ar[20] = -1.0;

    // Area 3 BS3 constraint
    // Service 1
    ia[21] = 11, ja[21] = 3, ar[21] = 1.0;
    ia[22] = 11, ja[22] = 23, ar[22] = -1.0;
    // service 2
    ia[23] = 12, ja[23] = 13, ar[23] = 1.0;
    ia[24] = 12, ja[24] = 29, ar[24] = -1.0;

    // Area 4 BS1 constraint
    // Service 1
    ia[25] = 13, ja[25] = 4, ar[25] = 1.0;
    ia[26] = 13, ja[26] = 21, ar[26] = -1.0;
    // service 2
    ia[27] = 14, ja[27] = 14, ar[27] = 1.0;
    ia[28] = 14, ja[28] = 27, ar[28] = -1.0;

    // Area 4 BS2 constraint
    // Service 1
    ia[29] = 15, ja[29] = 4, ar[29] = 1.0;
    ia[30] = 15, ja[30] = 22, ar[30] = -1.0;
    // service 2
    ia[31] = 16, ja[31] = 14, ar[31] = 1.0;
    ia[32] = 16, ja[32] = 28, ar[32] = -1.0;

    // Area 5 BS2 constraint
    // Service 1
    ia[33] = 17, ja[33] = 5, ar[33] = 1.0;
    ia[34] = 17, ja[34] = 22, ar[34] = -1.0;
    // service 2
    ia[35] = 18, ja[35] = 15, ar[35] = 1.0;
    ia[36] = 18, ja[36] = 28, ar[36] = -1.0;

    // Area 5 BS3 constraint
    // Service 1
    ia[37] = 19, ja[37] = 5, ar[37] = 1.0;
    ia[38] = 19, ja[38] = 23, ar[38] = -1.0;
    // service 2
    ia[39] = 20, ja[39] = 15, ar[39] = 1.0;
    ia[40] = 20, ja[40] = 29, ar[40] = -1.0;

    // Area 6 BS1 constraint
    // Service 1
    ia[41] = 21, ja[41] = 6, ar[41] = 1.0;
    ia[42] = 21, ja[42] = 21, ar[42] = -1.0;
    // service 2
    ia[43] = 22, ja[43] = 16, ar[43] = 1.0;
    ia[44] = 22, ja[44] = 27, ar[44] = -1.0;

    // Area 6 BS3 constraint
    // Service 1
    ia[45] = 23, ja[45] = 6, ar[45] = 1.0;
    ia[46] = 23, ja[46] = 23, ar[46] = -1.0;
    // service 2
    ia[47] = 24, ja[47] = 16, ar[47] = 1.0;
    ia[48] = 24, ja[48] = 29, ar[48] = -1.0;

    // Area 7 BS1 constraint
    // Service 1
    ia[49] = 25, ja[49] = 7, ar[49] = 1.0;
    ia[50] = 25, ja[50] = 21, ar[50] = -1.0;
    // service 2
    ia[51] = 26, ja[51] = 17, ar[51] = 1.0;
    ia[52] = 26, ja[52] = 27, ar[52] = -1.0;

    // Area 7 BS2 constraint
    // Service 1
    ia[53] = 27, ja[53] = 7, ar[53] = 1.0;
    ia[54] = 27, ja[54] = 22, ar[54] = -1.0;
    // service 2
    ia[55] = 28, ja[55] = 17, ar[55] = 1.0;
    ia[56] = 28, ja[56] = 28, ar[56] = -1.0;

    // Area 7 BS3 constraint
    // Service 1
    ia[57] = 29, ja[57] = 7, ar[57] = 1.0;
    ia[58] = 29, ja[58] = 23, ar[58] = -1.0;
    // service 2
    ia[59] = 30, ja[59] = 17, ar[59] = 1.0;
    ia[60] = 30, ja[60] = 29, ar[60] = -1.0;

    // Area 8 BS1 constraint
    // Service 1
    ia[61] = 31, ja[61] = 8, ar[61] = 1.0;
    ia[62] = 31, ja[62] = 21, ar[62] = -1.0;
    // service 2
    ia[63] = 32, ja[63] = 18, ar[63] = 1.0;
    ia[64] = 32, ja[64] = 27, ar[64] = -1.0;

    // Area 8 BS4 constraint
    // Service 1
    ia[65] = 33, ja[65] = 8, ar[65] = 1.0;
    ia[66] = 33, ja[66] = 24, ar[66] = -1.0;
    // service 2
    ia[67] = 34, ja[67] = 18, ar[67] = 1.0;
    ia[68] = 34, ja[68] = 30, ar[68] = -1.0;

    // Area 9 BS2 constraint
    // Service 1
    ia[69] = 35, ja[69] = 9, ar[69] = 1.0;
    ia[70] = 35, ja[70] = 22, ar[70] = -1.0;
    // service 2
    ia[71] = 36, ja[71] = 19, ar[71] = 1.0;
    ia[72] = 36, ja[72] = 28, ar[72] = -1.0;

    // Area 9 BS5 constraint
    // Service 1
    ia[73] = 37, ja[73] = 9, ar[73] = 1.0;
    ia[74] = 37, ja[74] = 25, ar[74] = -1.0;
    // service 2
    ia[75] = 38, ja[75] = 19, ar[75] = 1.0;
    ia[76] = 38, ja[76] = 31, ar[76] = -1.0;

    // Area 10 BS3 constraint
    // Service 1
    ia[77] = 39, ja[77] = 10, ar[77] = 1.0;
    ia[78] = 39, ja[78] = 23, ar[78] = -1.0;
    // service 2
    ia[79] = 40, ja[79] = 20, ar[79] = 1.0;
    ia[80] = 40, ja[80] = 29, ar[80] = -1.0;

    // Area 10 BS6 constraint
    // Service 1
    ia[81] = 41, ja[81] = 10, ar[81] = 1.0;
    ia[82] = 41, ja[82] = 26, ar[82] = -1.0;
    // service 2
    ia[83] = 42, ja[83] = 20, ar[83] = 1.0;
    ia[84] = 42, ja[84] = 32, ar[84] = -1.0;


    glp_load_matrix(lp, 84, ia, ja, ar);
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
    auto y11 = glp_get_col_prim(lp, 21);
    auto y12 = glp_get_col_prim(lp, 22);
    auto y13 = glp_get_col_prim(lp, 23);
    auto y14 = glp_get_col_prim(lp, 24);
    auto y15 = glp_get_col_prim(lp, 25);
    auto y16 = glp_get_col_prim(lp, 26);
    auto y21 = glp_get_col_prim(lp, 27);
    auto y22 = glp_get_col_prim(lp, 28);
    auto y23 = glp_get_col_prim(lp, 29);
    auto y24 = glp_get_col_prim(lp, 30);
    auto y25 = glp_get_col_prim(lp, 31);
    auto y26 = glp_get_col_prim(lp, 32);
    m_recursosAsignados={x11,x12,x13,x14,x15,x16,x17,x18,x19,x110,x21,x22,x23,x24,x25,x26,x27,x28,x29,x210};
    /* housekeeping */
    glp_delete_prob(lp);
    glp_free_env();
}

std::vector<double> SolverScen3::Decision()
{
    return m_recursosAsignados;
}

SolverScen3::~SolverScen3() 
{
}
