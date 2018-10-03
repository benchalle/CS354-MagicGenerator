////////////////////////////////////////////////////////////////////////////////
// Main File:        generate_magic.c
// This File:        generate_magic.c
// Other Files:      none
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

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
    int size;
    int **array;
} Square;

int get_square_size();
Square * generate_magic(int size);
void write_to_file(char *filename, Square * square);

int main(int argc, char *argv[])                 
{
	Square *newsquare; //initialize square struct
	int size;
 	if(argc < 2 || argc > 2){  //check to make sure there is the poper amount of args passed in
		printf("%s\n", "Usage: ./generate_magic  <filename>"); 
		exit(1);
	} 
	size = get_square_size();	//call get_square_size() and save the size
	newsquare = generate_magic(size); //call generate_magic and save the square it returns
	write_to_file(argv[1],newsquare);// write the square to the file given
	for(int i = 0; i< newsquare->size; i++){ //for each column free the memory
		free(*(newsquare->array + i));
	}
	free(newsquare->array); //free the rows of the array
	free(newsquare); // free the square struct

    return 0;
}

/* get_square_size prompts the user for the magic square size
 * checks if it is an odd number >= 3 and returns the number
 */
int get_square_size()            
{
	int usersize;  //initialize vairable that saves the users desired size
	printf("Enter size of magic square, must be odd\n"); // ask the user for size
        scanf("%10d",&usersize); //scan the input for size
        if(usersize< 3 || (usersize % 2 == 0) ){ //make sure the size is valid
		printf("Size must be an odd number >= 3.\n");
		exit(1);

	}	

    return usersize; //return the users size
}

/* generate_magic constructs a magic square of size n
 * using the Siamese algorithm and returns the Square struct
 */
Square * generate_magic(int n)           
{
	Square *square; //initialize pointer to square struct
	int **array; //initialize a double pointer to an array
	square = malloc(sizeof(Square)); //allocate memory for the struct
	if(square = NULL){
		printf("Error, memory not allocated");
	}
	array = malloc(sizeof(int*)*n); // allocate memory for the array
	if(array = NULL){
		printf("Error, memory not allocated");
	}
	square->size = n; //save the size to the struct
	for(int x=0; x<n; x++){
		*(array + x) = malloc(sizeof(int)*n); // for desired size of matrix allocate the memory
	}
	int start = n/2; //set the starting position of algorithm
	int end = n*n; //set the ending position of algorithm
	*(*(array + 0) + start) = 1; // start the algorithm   array[0][start] = 1; //
	//initialize needed vairiables
	int col;
	int row;
	int ncol;
	int nrow;
	int x;
	for(x=2, row = 0, col= start; (x< end + 1); x++){
	if((row-1)<0){ //if moving up a row will be out of bounds
		nrow = n-1; //move to the bottom
	}
	else{ nrow = row -1; } //else go up a row
	if((col + 1) > (n-1)){  //if adding one with be out of the column
		ncol = 0; //set the column to the first
	}
	else{ncol = col + 1;} //if not move right
	
	if(*(*(array + nrow)+ ncol)>0){ //check if there is already data in the position
		if(row > (n-1)){  //check if at bottom of matrix
			nrow = 0; //go to top of matrix
		}
		else{
			nrow = row +1; //go down a row
			ncol = col; //same column
		}
	}
	row = nrow;
	col = ncol;
	*(*(array+row)+col) = x; // put value in the correct position
}
	
	square->array = array; //save the array in the struct
	return square; //return the struct
	
}

/* write_to_file opens up a new file(or overwrites the existing file)
 * and writes out the square in the format expected by verify_hetero.c
 */
void write_to_file(char *filename, Square * square)              
{
	int err;
	FILE *file = fopen(filename, "w"); //create a writable file
	if(file != NULL){ // if the file exists
	err = fprintf(file, "%d\n", square->size); //print the size
	if(err < 0){ // if unable to write throw error and quit
	printf("ERROR: unable to write to file\n");
	exit(1);
	}
	for(int x = 0; x<square->size; x++){
		for(int y =0; y<square->size; y++){
			err = fprintf(file,"%d", *(*(square->array + x) +y)); //print each row
			 if(err < 0){
			        printf("ERROR: unable to write to file\n");
       				 exit(1);
        		}

			if(y +1 != square->size){
				err = fprintf(file, "%s",","); //print a "," between each element
				 if(err < 0){
				        printf("ERROR: unable to write to file\n");
					exit(1);
				}

			}
		}
		err = fprintf(file,"%s","\n");
		 if(err < 0){
		        printf("ERROR: unable to write to file\n");
			exit(1);
        	}

	}
	}else{
		printf("file not found\n");
		exit(1);
	}
	fclose(file); //close the file
    // Write the square to file
}
