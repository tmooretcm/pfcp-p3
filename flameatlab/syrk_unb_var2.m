
% Copyright 2023 The University of Texas at Austin
%
% For licensing information see
%                http://www.cs.utexas.edu/users/flame/license.html 
%                                                                                 
% Programmed by: Name of author
%                Email of author

function [ C_out ] = syrk_unb_var2( A, C )

  [ AL, AR ] = FLA_Part_1x2( A, ...
                               0, 'FLA_LEFT' );

  [ CTL, CTR, ...
    CBL, CBR ] = FLA_Part_2x2( C, ...
                               0, 0, 'FLA_TL' );

  while ( size( AL, 2 ) < size( A, 2 ) )

    [ A0, a1, A2 ]= FLA_Repart_1x2_to_1x3( AL, AR, ...
                                         1, 'FLA_RIGHT' );

    [ C00,  c01,     C02,  ...
      c10t, gamma11, c12t, ...
      C20,  c21,     C22 ] = FLA_Repart_2x2_to_3x3( CTL, CTR, ...
                                                    CBL, CBR, ...
                                                    1, 1, 'FLA_BR' );

    %------------------------------------------------------------%

    c10t = a1.' * A0 + c10t;
    gamma11 = a1.' * a1 + gamma11;
    c01 = c10t.';

    %------------------------------------------------------------%

    [ AL, AR ] = FLA_Cont_with_1x3_to_1x2( A0, a1, A2, ...
                                           'FLA_LEFT' );

    [ CTL, CTR, ...
      CBL, CBR ] = FLA_Cont_with_3x3_to_2x2( C00,  c01,     C02,  ...
                                             c10t, gamma11, c12t, ...
                                             C20,  c21,     C22, ...
                                             'FLA_TL' );

  end

  C_out = [ CTL, CTR
            CBL, CBR ];

end
