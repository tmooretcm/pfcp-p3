
% Copyright 2023 The University of Texas at Austin
%
% For licensing information see
%                http://www.cs.utexas.edu/users/flame/license.html 
%                                                                                 
% Programmed by: Name of author
%                Email of author

function [ C_out ] = syrk_blk_var1( A, C, nb_alg )

  [ AT, ...
    AB ] = FLA_Part_2x1( A, ...
                         0, 'FLA_TOP' );

  while ( size( AT, 1 ) < size( A, 1 ) )

    b = min( size( AB, 1 ), nb_alg );

    [ A0, ...
      A1, ...
      A2 ] = FLA_Repart_2x1_to_3x1( AT, ...
                                    AB, ...
                                    b, 'FLA_BOTTOM' );

    %------------------------------------------------------------%

    C = A1.' * A1 + C;

    %------------------------------------------------------------%

    [ AT, ...
      AB ] = FLA_Cont_with_3x1_to_2x1( A0, ...
                                       A1, ...
                                       A2, ...
                                       'FLA_TOP' );

  end

  C_out = C;


end
