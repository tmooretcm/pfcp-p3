%% Symmetric Rank-K Update (syrk) 
% This Matlab Script tests the syrk implementation.  This driver
% initializes symmetric matrix A, its transpose A^T and symmetric 
% matrix C, where C is stored as a lower triangular matrix. 
% The driver then compares the result against a reference implementation.
% Notice that the matrix is square (n x n)

addpath flameatlab/:flameatlab/matvec:flameatlab/vecvec:flameatlab/util

%% 
% Size of the matrix and vectors.
n = 16;

%% 
% Create random $A$, $C$, 
A = randi([-3, 3], [n, n]);
C = randi([-2, 2], [n, n]);


%% 
% Notice that the matrix is NOT symmetric.  To make it symmetric, we replace 
% the strictly upper triangular part with the transpose of the strictly lower 
% triangular part.  In the command window you can type "help tril" to see how 
% that function works.

Csym = tril(C) + tril(C, -1).';


%% 
% Compute Cref with Csym

Cref = A.' * A + Csym;


%% 
% Compare Cref with the result of the different syrk variants.

Cflame1 = syrk_unb_var1( A, Csym );
Cflame2 = syrk_unb_var2( A, Csym );
Cflame3 = syrk_blk_var1( A, Csym, 4 );
Cflame4 = syrk_blk_var2( A, Csym, 4 );

%% 
% 

if isequal( Cflame1,  Cref )
    disp( 'Var 1 unb - All is well' );
else
    disp( 'Var 1 unb  - Something seems to be wrong' );
end

if isequal( Cflame2,  Cref )
    disp( 'Var 2 unb - All is well' );
else
    disp( 'Var 2 unb - Something seems to be wrong' );
end

if isequal( Cflame3,  Cref )
    disp( 'Var 1 blk - All is well' );
else
    disp( 'Var 1 blk - Something seems to be wrong' );
end

if isequal( Cflame4,  Cref )
    disp( 'Var 2 blk - All is well' );
else
    disp( 'Var 2 blk - Something seems to be wrong' );
end


