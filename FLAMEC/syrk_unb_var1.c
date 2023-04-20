
/* Copyright 2023 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Anne-Marie Prosper
                  aprosper@utexas.edu
                                                                     */

#include "FLAME.h"

int syrk_blk_var1( FLA_Obj A, FLA_Obj C, int nb_alg )
{
  FLA_Obj AT,              A0,
          AB,              A1,
                           A2;

  int b;

  FLA_Part_2x1( A,    &AT, 
                      &AB,            0, FLA_TOP );

  while ( FLA_Obj_length( AT ) < FLA_Obj_length( A ) ){

    b = min( FLA_Obj_length( AB ), nb_alg );

    FLA_Repart_2x1_to_3x1( AT,                &A0, 
                        /* ** */            /* ** */
                                              &A1, 
                           AB,                &A2,        b, FLA_BOTTOM );

    /*------------------------------------------------------------*/

        FLA_Syrk( FLA_LOWER_TRIANGULAR, FLA_TRANSPOSE, 
              FLA_ONE, A1, FLA_ONE, C );

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x1_to_2x1( &AT,                A0, 
                                                  A1, 
                            /* ** */           /* ** */
                              &AB,                A2,     FLA_TOP );

  }

  return FLA_SUCCESS;
}

