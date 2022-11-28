/**
 * @file matrix.c
 * @author Simon J. Thür
 * @brief matrix functions
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "matrix.h"

#include <nds.h>
#include <stdio.h>


void printMatrix( int mat[], int rows, int columns )
{
    for ( int i = 0; i < rows; i++ )
        {
            for ( int j = 0; j < columns; j++ )
                {
                    if ( j != 0 )
                        {
                            printf( "\t" );
                        }
                    printf( "%d", mat[ i * columns + j ] );
                }
            printf( "\n\n" );
        }
}

void identity( int mat[], int columns )
{
    int i, j;
    for ( i = 0; i < columns; i++ )
        {
            for ( j = 0; j < columns; j++ )
                {
                    mat[ columns * i + j ] = i == j ? 1 : 0;
                }
        }
}


int sumMatrix( int mat[], int rows, int columns )
{
    int i;
    int ret = 0;
    for ( i = 0; i < rows * columns; i++ )
        {
            ret += mat[ i ];
        }
    return ret;
}


void multMatrices( int mat1[], int mat2[], int rows, int columns, int result[] )
{
    int tmp;
    int i, j, k;
    for ( i = 0; i < rows; i++ )
        {
            for ( j = 0; j < columns; j++ )
                {
                    tmp = 0;
                    for ( k = 0; k < columns; k++ )
                        {
                            tmp += mat1[ rows * j + k ] * mat2[ columns * k + i ];
                        }
                    result[ i + rows * j ] = tmp;
                }
        }
}


tMatrix* multMatrices2( tMatrix* m1, tMatrix* m2 )
{
    tMatrix* ret = malloc( sizeof( tMatrix ) );
    ret->rows    = m1->rows;
    ret->cols    = m2->cols;
    ret->mat     = malloc( ret->cols * ret->cols * sizeof( int ) );
    // multMatrices( m1->mat, m2->mat, ret->rows, ret->cols, ret->mat ); // doesnt
    // work, because it is not square!

    int i, j, k;
    for ( i = 0; i < m1->rows; i++ )
        {
            for ( j = 0; j < m2->cols; j++ )
                {
                    int tmp = 0;
                    for ( k = 0; k < m1->cols; k++ )
                        {
                            tmp += m1->mat[ m1->cols * i + k ] *
                                   m2->mat[ m2->cols * k + j ];
                        }
                    ret->mat[ ret->cols * i + j ] = tmp;
                }
        }


    return ret;
}


void sumDiagonal( const tMatrix* m, int* sum )
{
    int i;
    int t = m->cols > m->rows ? m->rows : m->cols;
    *sum  = 0;
    for ( i = 0; i < t; i++ )
        {
            *sum += m->mat[ m->cols * i + i ];
        }
}
