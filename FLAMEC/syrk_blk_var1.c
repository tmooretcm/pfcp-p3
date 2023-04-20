
/* Copyright 2023 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Anne-Marie Prosper
                  aprosper@utexas.edu
                                                                     */

#include "FLAME.h"

int syrk_unb_var1( FLA_Obj A, FLA_Obj C )
{
  FLA_Obj AT,              A0,
          AB,              a1t,
                           A2;

  FLA_Part_2x1( A,    &AT, 
                      &AB,            0, FLA_TOP );

  while ( FLA_Obj_length( AT ) < FLA_Obj_length( A ) ){

    FLA_Repart_2x1_to_3x1( AT,                &A0, 
                        /* ** */            /* *** */
                                              &a1t, 
                           AB,                &A2,        1, FLA_BOTTOM );

    /*------------------------------------------------------------*/

    /* A =  x * x' + A */ 

    // TODO fix this because we need x' * x
    FLA_Syr( FLA_LOWER_TRIANGULAR, FLA_ONE, a1t, C ); 

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x1_to_2x1( &AT,                A0, 
                                                  a1t, 
                            /* ** */           /* *** */
                              &AB,                A2,     FLA_TOP );

  }

  return FLA_SUCCESS;
}

