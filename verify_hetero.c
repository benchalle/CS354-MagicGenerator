////////////////////////////////////////////////////////////////////////////////
// Main File:        verify_hetero.c
// This File:        verify_heter0.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2018
//
// Author:           Benjamin Challe
// Email:            bchalle@wisc.edu
// CS Login:         challe
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
    int size;
    int **array;
} Square;

Square * construct_square(char *filename);
int verify_hetero(Square * square);
void insertion_sort(int* arr, int size);

int main(int argc, char *argv[])                        
{
	Square *newSquare;  //initialize square struct
	if(argc < 2 || argc > 2){	//test to see if the correct # of args are used
		printf("%s\n", "Usage: ./verify_hetero  <filename>");
		exit(1);
	}
	newSquare = construct_square(argv[1]); //call construct_square and save what is returned
	int istrue = verify_hetero(newSquare); // call verify_hetero and save the return value
	if(istrue == 1){ //test to see if the return value means it hetero or not
		printf("true\n");
	}else{
		printf("false\n");
	}
	for(int i = 0; i< newSquare->size; i++){  //free the array column by column
		free(*(newSquare->array + i));
	}	
	free(newSquare->array); // free the rows
	free(newSquare); //free the struct

    return 0;
}

/* construct_square reads the input file to initialize a square struct
 * from the contents of the file and returns the square.
 * The format of the file is defined in the assignment specifications
 */
Square * construct_square(char *filename)                
{
	const int BUFFSIZE = 100;	//set buffer size
	char buff[BUFFSIZE];  //create an array with buffer size
	Square *sqptr; //create a pointer to a square struct
	sqptr = malloc(sizeof(Square));		//allocate the memory for the square
	FILE *file; //initialize file pointer
	int err; //initialize error variable
	int x,y; //initialize counters
	int sizeOfSquare; // initialize size variable
	int **array; // initialize double pointer to an array
	file = fopen(filename,"r"); //read the file with filename
	if(file != NULL){ //if the file exists and is readable
		err = fscanf(file, "%d", &sizeOfSquare); // get the size of the square
		 if(err != 1){ // if the size isnt the write type throw error
		        printf("ERROR: incorrect type\n");
		        exit(1);
        	}

		sqptr->size = sizeOfSquare; // save the size of square in struct
		array = malloc(sizeof(int*)*sizeOfSquare); //allocate memory for an array with the size inputed
		
		for(x=0; x< sizeOfSquare; x++){ //allocate each column
		*(array + x) = malloc(sizeof(int)*sizeOfSquare);
		}
		x=0;
		char *elements;
		while(x<sizeOfSquare){
		err = fscanf(file, "%s", buff); // get each element of the matrix
		  if(err != 1){ //if its not the correct type throw error and exit
                        printf("ERROR: incorrect type\n");
                        exit(1);
                }

		elements = strtok(buff,","); //tokenize the input and split by a ","
		y=0;
			while(elements != NULL){
			*(*(array + x)+y) = atoi(elements); // put the element in the array
			elements = strtok(NULL, ","); //set to null
			++y;
			}		
		x++;
		}	
	}else{
	printf("Cannot open file for reading. \n"); // if file doesnt exist throw error and exit
	exit(1);
	}
	fclose(file); //close file
	sqptr-> array = array; // save the array in the struct
	return sqptr; // return the pointer to the struct
	

}

/* verify_hetero verifies if the square is a heterosquare
 * 
 * returns 1(true) or 0(false)
 */
int verify_hetero(Square *square)               
{
	int total[square->size*2+2]; //create an array based on the size of the matrix
	int x,y;
	int counter=0;
	int aTotal=0;
	for(x=0; x<square->size; x++){
		for(y=0; y<square->size; y++){
			aTotal += *(*(square->array+x)+y); // get total of the column
		}
	total[counter] = aTotal; //save total
	counter++; //increase the counter
	aTotal =0; //reset total
	}	
	for(x=0; x<square->size; x++){
		for(y=0; y<square->size; y++){
			aTotal+= *(*(square->array+y)+x); //get total for row
		}
	total[counter] = aTotal; //save total
	counter++;  //increase counter
	aTotal = 0; //reset total
	}
	y =0;
	for(x=0; x<square->size; x++){
		aTotal += *(*(square->array+x)+y); //get first diagnol
		y++;
	}
	total[counter] = aTotal; //save total
	counter++; //increase counter
	aTotal = 0; // reset total
	y = 0;
	for(x=square->size-1; x>=0; x--){
		aTotal += *(*(square->array +x)+y);  //get second diagnol
		y++;
	} 
	total[counter] = aTotal; //save total
  

    // Pass the array to insertion_sort function

	insertion_sort(total, square->size*2+2);
	
	for(int i =0; i<counter; i++){ //check for duplicates in the sorted array
		if(total[i] == total[i+1]){
			return 0; //if there is return that it is not hetero
		}
	}
		return 1; //if no duplicates return that it is a hetero matrix
}

/* insertion_sort sorts the arr in ascending order
 *
 */
void insertion_sort(int* arr, int size)
{
	int x, element,y;
	for(x=1; x<size; x++){  //compare the value of each element in array
		element = arr[x];
		y = x-1;
		while(y>=0 && arr[y] > element){  //if out of place sort it
			arr[y+1] = arr[y];
			y=y-1;
		}
	arr[y+1] = element;
	}
}                
  // Sort the arr
	

