/*******************************************************************
** Program: Assignment 0 - Simple OpenMP Experiment
** Author: Casey Anderson
** Date: 04/09/2023
** Description: Assignment 0 program using OpenMP to create threads
and time their performance
** Input: N/A
** Output: csv of results
*******************************************************************/
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#ifndef NUMT
#define NUMT    1	// number of threads to use -- do once for 1 and once for 4
#endif

#ifndef NUMTRIES
#define NUMTRIES    10	// how many times to run the timing to get reliable timing data
#endif

#define SIZE        16384 	// array size -- you get to decide

/*
const int NUMT = 1;
const int SIZE = 16384; //16K
const int NUMTRIES = 20;
*/

float A[SIZE] = {};
float B[SIZE] = {};
float C[SIZE] = {};

int main( ) {
#ifdef   _OPENMP
	fprintf( stderr, "OpenMP version %d is supported here\n", _OPENMP );
#else
	fprintf( stderr, "OpenMP is not supported here - sorry!\n" );
	exit( 0 );
#endif

	// initialize the arrays:
	for( int i = 0; i < SIZE; i++ )
	{
		A[i] = 1.;
		B[i] = 2.;
	}

        omp_set_num_threads( NUMT );

        double maxMegaMults = 0.;
        double summMults = 0.;

        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );

                #pragma omp parallel for
                for( int i = 0; i < SIZE; i++ )
                {
                        C[i] = A[i] * B[i];
                }

                double time1 = omp_get_wtime( );
                double megaMults = (double)SIZE/(time1-time0)/1000000.;
                summMults += megaMults;
                if( megaMults > maxMegaMults )
                        maxMegaMults = megaMults;
        }
        // Threads, Array Size, Loops, MFLOPS, Avg. MFlops
        printf("%d,%d,%d,%lf,%lf\n", NUMT, SIZE, NUMTRIES, maxMegaMults, summMults/(double)NUMTRIES);

        fprintf( stderr, "For %d threads, Peak Performance = %8.2lf MegaMults/Sec\n", NUMT, maxMegaMults);

	// note: %lf stands for "long float", which is how printf prints a "double"
	//        %d stands for "decimal integer", not "double"

	// Speedup = (Peak performance for 4 threads) / (Peak performance for 1 thread)

        return 0;
}
