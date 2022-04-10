///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2021, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////

// add your own File Header information here
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      magicSquare1.txt
// Semester:         CS 354 Fall 2021
// Instructor:       Deppeler
//
// Author:           Christopher Yang
// Email:            cyang397@wisc.edu
// CS Login:         chrisy
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Dad, helped with the higher level thinking of the generate
//		     magic square method. Also helped with the syntax of the
//		     getsize method, specifically the input portion.
//
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
	printf("Enter magic square's size (odd integer >=3)\n");
	char *input;
	input = malloc(sizeof(char) * 5);
	fgets(input, 5, stdin);
	int arg = atoi(input);
	if(arg % 2 == 0) {
		printf("Magic square size must be odd.\n");
		exit(1);
	}
	else if(arg < 3) {
		printf("Magic square size must be >= 3.\n");
		exit(1);
	}
	return arg;
}

/* TODO:
 * Makes a magic square of size n using the alternate
 * Siamese magic square algorithm from assignment and
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
    	// create an instance of Magic Square struct
	MagicSquare *mSq;
	mSq = malloc(sizeof(MagicSquare));
	mSq->size = n;
	int **magicSquareN;
	magicSquareN = malloc(sizeof(int *) * n);
	for(int i = 0; i < n; i++)
		*(magicSquareN + i) = malloc(sizeof(int) * n);
	mSq->magic_square = magicSquareN;

	// initalize the 2D array
	for(int j = 0; j < n; j++)
		for(int k = 0; k < n; k++) {
			*(*(magicSquareN + j) + k) = 0;
		}
	// fill the elements of 2D array using the
	// up-and-to-the-right version of siamese method

	// keep track of current index
	int currRow = 0;
	int currCol = 0;
	// keep track of next index
	int nextRow = 0;
	int nextCol = (n - 1)/2;
	int counter = 1;
	while(counter <= n * n) {
		if(*(*(magicSquareN + nextRow) + nextCol) == 0) {
			*(*(magicSquareN + nextRow) + nextCol) = counter;
			currRow = nextRow;
			currCol = nextCol;
//			*(*(magicSquareN + currCol) + currRow) = counter;
		} else {
			currRow = (currRow + 1) % n;
			*(*(magicSquareN + currRow) + currCol) = counter;
			nextCol = currCol;
			nextRow = currRow;
		}
	nextCol = (nextCol + 1) % n;
	nextRow--;;
	if(nextRow < 0)
		nextRow = n - 1;
	counter++;
	}
//	for(int l = 1; l <= n*n; l++) {
		// check value at index & assign value
//		if(*(*(magicSquareN + j) + k) == 0)
//			*(*(magicSquareN + j) + k) = l;
//		else {
//			k = (k + 1) % n;
//			j--;
//			if(j < 0)
//				j = n - 1;
//			*(*(magicSquareN + j) + k) = l;
//		}
//		j = (j + 1) % n;
//		k--;
//		if(k < 0)
//			k = n - 1;
		//
//	}
	return mSq;
}

/* TODO:
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
	FILE *fp = fopen(filename, "w");
	if(fp == NULL) {
                printf("Can't open file for writing.\n");
                exit(1);
        }
	// write to file
	fprintf(fp, "%d\n", magic_square->size);
	for(int i = 0; i < magic_square->size; i++) {
		for(int j = 0; j < magic_square->size - 1; j++) {
			fprintf(fp, "%d,", *(*(magic_square->magic_square + i) + j));
		}
	fprintf(fp,"%d\n", *(*(magic_square->magic_square + i) + magic_square->size -1));
	}
	// close the file
	if(fclose(fp) != 0) {
		printf("Error while closing the file.\n");
		exit(1);
	}
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the square to the output filename
 */
int main(int argc, char *argv[]) {
    // TODO: Check input arguments to get output filename
	if( argc < 2 || argc > 2) {
		printf("Usage: %s <output_filename>\n", *(argv));
		//printf("Usage: ./myMagicSquare <output_filename>\n");
		exit(1);
	}

    // TODO: Get magic square's size from user
	int sizeOfBoard = getSize();
    //	printf("Size: %d\n", sizeOfBoard);
    // TODO: Generate the magic square
	MagicSquare *mSquare = generateMagicSquare(sizeOfBoard);
    // TODO: Output the magic square
	fileOutputMagicSquare(mSquare, *(argv + 1));

    // free heap memory
    	for(int i = 0; i < mSquare->size; i++)
        	    free(*(mSquare->magic_square + i));
        free(mSquare);
        mSquare = NULL;
    //	printf("%d",*(*(mSquare->magic_square)));
    return 0;
}


//  F21 deppeler myMagicSquare.c

