
/* Copyright 2023 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Anne-Marie Prosper
                  aprosper@utexas.edu
                                                                     */

#include "FLAME.h"

int syrk_unb_var2( FLA_Obj A, FLA_Obj C )
{
  FLA_Obj AL,    AR,       A0,  a1,  A2;

  FLA_Obj CTL,   CTR,      C00,  c01,     C02, 
          CBL,   CBR,      c10t, gamma11, c12t,
                           C20,  c21,     C22;

  FLA_Part_1x2( A,    &AL,  &AR,      0, FLA_LEFT );

  FLA_Part_2x2( C,    &CTL, &CTR,
                      &CBL, &CBR,     0, 0, FLA_TL );

  while ( FLA_Obj_width( AL ) < FLA_Obj_width( A ) ){

    FLA_Repart_1x2_to_1x3( AL,  /**/ AR,        &A0, /**/ &a1, &A2,
                           1, FLA_RIGHT );

    FLA_Repart_2x2_to_3x3( CTL, /**/ CTR,       &C00,  /**/ &c01,     &C02,
                        /* ************* */   /* ************************** */
                                                &c10t, /**/ &gamma11, &c12t,
                           CBL, /**/ CBR,       &C20,  /**/ &c21,     &C22,
                           1, 1, FLA_BR );

    /*------------------------------------------------------------*/

    /* c10t = a1' * A0 +  c10t */

    FLA_Gemv( FLA_TRANSPOSE, FLA_ONE, A0, a1, FLA_ONE, c10t );

    /* gamma11 = a1' * a1  +  gamma11 */
    FLA_Dots( FLA_ONE, a1, a1, FLA_ONE, gamma11 );

    /* c01 = c10t' */
    // FLA_Copyt(FLA_TRANSPOSE, c10t, c01);
    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &AL,  /**/ &AR,        A0, a1, /**/ A2,
                              FLA_LEFT );

    FLA_Cont_with_3x3_to_2x2( &CTL, /**/ &CTR,       C00,  c01,     /**/ C02,
                                                     c10t, gamma11, /**/ c12t,
                            /* ************** */  /* ************************ */
                              &CBL, /**/ &CBR,       C20,  c21,     /**/ C22,
                              FLA_TL );

  }

  return FLA_SUCCESS;
}

