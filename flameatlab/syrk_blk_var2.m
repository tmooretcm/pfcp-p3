
% Copyright 2023 The University of Texas at Austin
%
% For licensing information see
%                http://www.cs.utexas.edu/users/flame/license.html 
%                                                                                 
% Programmed by: Name of author
%                Email of author

function [ C_out ] = syrk_blk_var2( A, C, nb_alg )

  [ AL, AR ] = FLA_Part_1x2( A, ...
                               0, 'FLA_LEFT' );

  [ CTL, CTR, ...
    CBL, CBR ] = FLA_Part_2x2( C, ...
                               0, 0, 'FLA_TL' );

  while ( size( AL, 2 ) < size( A, 2 ) )

    b = min( size( AR, 2 ), nb_alg );

    [ A0, A1, A2 ]= FLA_Repart_1x2_to_1x3( AL, AR, ...
                                         b, 'FLA_RIGHT' );

    [ C00, C01, C02, ...
      C10, C11, C12, ...
      C20, C21, C22 ] = FLA_Repart_2x2_to_3x3( CTL, CTR, ...
                                               CBL, CBR, ...
                                               b, b, 'FLA_BR' );

    %------------------------------------------------------------%

    C10 = A1.' * A0 + C10;
    C11 = A1.' * A1 + C11;
    C01 = C10.';

    %------------------------------------------------------------%

    [ AL, AR ] = FLA_Cont_with_1x3_to_1x2( A0, A1, A2, ...
                                           'FLA_LEFT' );

    [ CTL, CTR, ...
      CBL, CBR ] = FLA_Cont_with_3x3_to_2x2( C00, C01, C02, ...
                                             C10, C11, C12, ...
                                             C20, C21, C22, ...
                                             'FLA_TL' );

  end

  C_out = [ CTL, CTR
            CBL, CBR ];

end
