#ifndef PRODUCTS_H_
#define PRODUCTS_H_

#include <cmath>

const double e3 = pow(ITM_QE, 3);

const double me_c2 = ITM_ME * pow(ITM_C, 2);

const double me2_c3 = me_c2 * ITM_ME * ITM_C;

const double me2_c3__e = me2_c3 / ITM_QE;

const double pi_4_e02_me2_c3__e4 = ITM_PI * 4.0 * pow(ITM_EPS0, 2) * me2_c3 / pow(ITM_QE, 4);

const double pi_4_e02_me2__e4  = ITM_PI * 4.0 * pow(ITM_EPS0, 2) * ITM_ME *ITM_ME  / pow(ITM_QE, 4);

const double pi_e02_me_4_c2 = ITM_PI * pow(ITM_EPS0, 2) * ITM_ME * 4.0 * pow(ITM_C, 2);

#endif /* PRODUCTS_H_ */
