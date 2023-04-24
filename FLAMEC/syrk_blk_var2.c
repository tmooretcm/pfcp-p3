
/* Copyright 2023 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Anne-Marie Prosper
                  aprosper@utexas.edu
                                                                     */

#include "FLAME.h"

int syrk_blk_var2( FLA_Obj A, FLA_Obj C, int nb_alg )
{
  FLA_Obj AL,    AR,       A0,  A1,  A2;

  FLA_Obj CTL,   CTR,      C00, C01, C02, 
          CBL,   CBR,      C10, C11, C12,
                           C20, C21, C22;

  int b;

  FLA_Part_1x2( A,    &AL,  &AR,      0, FLA_LEFT );

  FLA_Part_2x2( C,    &CTL, &CTR,
                      &CBL, &CBR,     0, 0, FLA_TL );

  while ( FLA_Obj_width( AL ) < FLA_Obj_width( A ) ){

    b = min( FLA_Obj_width( AR ), nb_alg );

    FLA_Repart_1x2_to_1x3( AL,  /**/ AR,        &A0, /**/ &A1, &A2,
                           b, FLA_RIGHT );

    FLA_Repart_2x2_to_3x3( CTL, /**/ CTR,       &C00, /**/ &C01, &C02,
                        /* ************* */   /* ******************** */
                                                &C10, /**/ &C11, &C12,
                           CBL, /**/ CBR,       &C20, /**/ &C21, &C22,
                           b, b, FLA_BR );

    /*------------------------------------------------------------*/

    /* C10 = A1T * A0 + C10*/
    FLA_Gemm( FLA_TRANSPOSE, FLA_NO_TRANSPOSE, FLA_ONE, A1, A0, FLA_ONE, C10 );
    /* C11 = A1T * A1 + C11*/
    FLA_Gemm( FLA_TRANSPOSE, FLA_NO_TRANSPOSE, FLA_ONE, A1, A1, FLA_ONE, C11 );
    /* C01 = C10T */
    FLA_Copyt( FLA_TRANSPOSE, C10, C01 );


    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &AL,  /**/ &AR,        A0, A1, /**/ A2,
                              FLA_LEFT );

    FLA_Cont_with_3x3_to_2x2( &CTL, /**/ &CTR,       C00, C01, /**/ C02,
                                                     C10, C11, /**/ C12,
                            /* ************** */  /* ****************** */
                              &CBL, /**/ &CBR,       C20, C21, /**/ C22,
                              FLA_TL );

  }

  return FLA_SUCCESS;
}

