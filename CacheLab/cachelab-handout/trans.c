/* 
 * Author : Ishant Dawer (idawer@andrew.cmu.edu)
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"
#include "contracts.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. The REQUIRES and ENSURES from 15-122 are included
 *     for your convenience. They can be removed if you like.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    REQUIRES(M > 0);
    REQUIRES(N > 0);
/*
 * temp* are local variables used to store rows in A
 * i,j,k are loop iterators
 */

    int i,j,k,temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
    int BS ;
    if (M == 32 && N == 32 ) 
    {
/*
 * Moving rowwise in A by 8 integers (32 bytes)
 * as cache can handle full 8x8 blocks
 */

            BS = 8;//Block Size (Blocking)
            for ( k = 0 ; k < N ; k += BS) { 
                    for ( j = 0 ; j < M ; j+=BS ) 
                    { 
                           for ( i = k ; i < (k + BS) ; i++) 
                           { 
                                 temp1 = A[i][j + 0];
                                 temp2 = A[i][j + 1];
                                 temp3 = A[i][j + 2];
                                 temp4 = A[i][j + 3];
                                 temp5 = A[i][j + 4];
                                 temp6 = A[i][j + 5];
                                 temp7 = A[i][j + 6];
                                 temp8 = A[i][j + 7];
                                 B[j + 0][i] = temp1;
                                 B[j + 1][i] = temp2;
                                 B[j + 2][i] = temp3;
                                 B[j + 3][i] = temp4;
                                 B[j + 4][i] = temp5;
                                 B[j + 5][i] = temp6;
                                 B[j + 6][i] = temp7;
                                 B[j + 7][i] = temp8;
                                  
                           }
                           
                    }
            }
    }

/*
 * Moving rowwise in A by 6 integers (24 bytes)
 * as cache can handle full 8x8 blocks
 */    
    if (M == 61 && N == 67) 
    {
            BS  = 6;//Block Size (Blocking)
            for ( k = 0 ; k < M ; k+=BS) 
            { 
                    for (i = 0 ; i < N  ; i++) 
                    {
                           temp1 = A[ i][k + 0]; 
                           if ( k != 60 ) 
                           {
                                   temp2 = A[ i][k + 1]; 
                                   temp3 = A[ i][k + 2]; 
                                   temp4 = A[ i][k + 3]; 
                                   temp5 = A[ i][k + 4]; 
                                   temp6 = A[ i][k + 5]; 
                                   B[k + 1][i] = temp2;
                                   B[k + 2][i] = temp3;
                                   B[k + 3][i] = temp4;
                                   B[k + 4][i] = temp5;
                                   B[k + 5][i] = temp6;
                           } 
                           B[k + 0][i] = temp1;
                    }

            }
    }
/*
 * Moving rowwise in A by 4 integers (24 bytes)
 * as cache can handle full 8x8 blocks
 * Dividing 64x64 into 8x8 blocks and further 4x4 blocks are
 * transposed such that block upper left, lower left, lower right
 * and upper right are transposed respectively.
 * and 
 */
    if (M == 64 && N == 64) 
    {
            BS  = 4;
            int temp9,temp10;
            for ( temp6 = 0; temp6 < M; temp6 += 8)
            { 
                    for (temp5 = 0 ; temp5 < N ; temp5+=8) 
                    { 
                            for (i = temp5 ; i < (temp5 + 8)  ; i++) 
                            {
                                   temp1 = A[ i][temp6 + 0]; 
                                   temp2 = A[ i][temp6 + 1]; 
                                   temp3 = A[ i][temp6 + 2]; 
                                   temp4 = A[ i][temp6 + 3]; 
                                   temp9 = A[ i][temp6 + 4]; 
                                   temp10 = A[ i][temp6 + 5]; 
                                   temp7 = A[ i][temp6 + 6]; 
                                   temp8 = A[ i][temp6 + 7]; 
                                   B[temp6 + 0][i] = temp1;
                                   B[temp6 + 1][i] = temp2;
                                   B[temp6 + 2][i] = temp3;
                                   B[temp6 + 3][i] = temp4;
                            }
                            for ( j = temp5 + 4 ; j < (temp5 + 7) ; j++ ) 
                            { 
                                    temp1 = A[j][temp6 + 4 ];
                                    temp2 = A[j][temp6 + 5];
                                    temp3 = A[j][temp6 + 6];
                                    temp4 = A[j][temp6 + 7];
                                    B[temp6 + 4 ][j] = temp1;
                                    B[temp6 + 5][j] = temp2;
                                    B[temp6 + 6][j] = temp3;
                                    B[temp6 + 7][j] = temp4;
                            }

                            B[temp6 + 4][j] = temp9;
                            B[temp6 + 5][j] = temp10;
                            B[temp6 + 6][j] = temp7;
                            B[temp6 + 7][j] = temp8;
                            for ( k = temp5 ; k < (temp5 + 4); k++ ) 
                            { 
                                    temp1 = A[k][temp6 + 4 ];
                                    temp2 = A[k][temp6 + 5];
                                    temp3 = A[k][temp6 + 6];
                                    temp4 = A[k][temp6 + 7];
                                    B[temp6 + 4][k] = temp1;
                                    B[temp6 + 5][k] = temp2;
                                    B[temp6 + 6][k] = temp3;
                                    B[temp6 + 7][k] = temp4;
                            }
                    }
            }

    }




    ENSURES(is_transpose(M, N, A, B));
}



/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

