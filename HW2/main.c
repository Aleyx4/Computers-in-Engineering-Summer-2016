/*-----------------------------------------------------------------------------
* Programmer: Alex Wong
* Date: 6/27/2016
* Name: hw2/main.c
*
* Description: The User will start by entering in the dimensions of the matrix.
* The program will promopt to enter the rows and then the columns. After
* the user will then enter the data values in by-row order. The program will
* then print out the matrix. On the right side of the user created matrix
* there will be the average values for each corresponding row. On the bottom
* of the user created matrix the user will see the average values for each
* corresponding column. At the very bottom there will print the average to the
* entire matrix. The user will be prompt to end the program or to press "0"
* to create a new matrix.
*
* Pseudocode: We start by importing the required functions. Then initialize the
* prototypes for each function. We will have a define to define constant max
* dimension for the users matrix. Initialize all the variables. Create a while
* loop to allow the user to recreate the matrix if needed. Prompt the user
* to enter the dimensions of the matrix row and column. After allow the user
* to input the values into the matrix. Create a while loop to catch any number
* than the max dimensions allowed in the defined constant. Use the readMatrix()
* method to allow user to input the values to matrix. Then use rowAverage() and
* colAverage() method. After use overallAverage() then printAverages() to
* compute and print out the averages for the user. Prompt user to end or
* create a new matrix.
*
* readMatrix()
* Initialize array and use malloc to hold the number of floats needed from the
* what the user specified. Then check if malloc was successful if not then end
* the program else then allow the user to input floats in the new created matrix
* in by-row order. Then return the data if failed then return null to end the
* program.
*
* rowAverage()
* Creating a new array for the average of the user matrix. The size is the number
* of rows in the original matrix. Call malloc and make sure it does not fail
* if it does then return null otherwise to calculate the average get sum of all
* the numbers from the row and divide it by the number of columns to get the
* average of the row. Store that average in the same row number in the new array.
* So row 0 gets the average row array 0 and so forth. Return the array of averages.
* To get the the sum of the rows use a for loop to add up the columns max.
* Multiply the the number of columns to get to the next row.
*
* colAverage()
* Creating a new array for the average of the user matrix. The size is the number
* of columns in the original matrix. Call malloc and make sure it does not fail if
* it does then return null otherwise to calculate the average get the
* not sum of all the numbers from the column and divide it by the number of rows
* not to get the average of the column. Store the average in the same column number
* as the new array. So column 0 get average column array 0 and so forth. Return
* the array of averages. To add all the numbers in the column, use a loop to get
* the value of each value in the column. Multiply the number of elements in the
* row to get how much you need to increment to get the location for the next number
* that needs to be added.
*
* overallAverage()
* Get the sum of all the numbers from the matrix and divide by the same number of
* numbers added. This will get the average of the entire matrix. Return the
* average as a float. Use a for loop to go through the entire matrix array.
*
* printAverages()
* Print the array of floats by looping each time it reaches to the max column
* it will print \n for a new line. To make sure it is aligned use \t to get to
* the next tab stop for each element in the array. After each time it reaches
* to the end of the column before \n insert the average of that row. After it
* prints all of the matrix on the bottom print out the entire array for the
* average columns. Make sure to use \t to align it to the corresponding columns.
* After print out the overall average of the entire matrix.
 -----------------------------------------------------------------------------*/
/*=======================
 *   Import Statements
 *=======================*/
 #include <stdio.h>
 #include <stdlib.h> 		/*Must include stdlib.h in order to use malloc and free functions*/

/*=======================
 *  Function Prototypes
 *=======================*/
 float *readMatrix(int numRows, int numCols);
 float *rowAverage(float *matrix, int numRows, int numCols);
 float *colAverage(float *matrix, int numRows, int numCols);
 float overallAverage(float* matrix, int numRows, int numCols);
 void printAverages(float *matrix, float *rowAve, float *colAve, float overallAve, int numRows, int numCols);

 /*=======================
  *   Defined Constants
  *=======================*/
 #define MAX_DIM 5

/*=======================
 *       Main Method
 *=======================*/
int main(void)
{
/*=======================
 *    Initial Values
 *=======================*/
  int done = 0;
  int rows, cols;
  float *dataMatrix;
  float *rowAveVector;
  float *colAveVector;
  float overallAve;
  setbuf(stdout, NULL); 				/* Buffer Disabled - Used for Eclipse Debugging */
  while (!done)
  {
    // Prompt user to enter row and column dimensions of matrix (must be > 0)
    do
    {
        printf("Enter row dimension (must be between 1 and %d): ", MAX_DIM);
        scanf("%d", &rows);

    } while(rows <= 0 || rows > MAX_DIM);
    do
    {
        printf("Enter column dimension (must be between 1 and %d): ", MAX_DIM);
        scanf("%d", &cols);
    } while(cols <= 0 || cols > MAX_DIM);
    // Read read matrix values from keyboard and place into a
    //dynamically allocated array in by-row order. dataMatrix
    // should point to this array.  If the dataMatrix is NULL
    //terminate the program

    dataMatrix = readMatrix(rows, cols);
    if (dataMatrix == NULL)
    {
        printf ("Program terminated due to dynamic memory allocation failure\n");
        return (0);
    }

    //Compute averages.  Terminate the program if
    //rowAveVector or colAveVector are NULL
    rowAveVector = rowAverage(dataMatrix, rows, cols);
    colAveVector = colAverage(dataMatrix, rows, cols);
    if(rowAveVector == NULL || colAveVector == NULL)
    {
     printf("malloc failed.  Terminating program\n");
     return (0);
    }
    overallAve = overallAverage(dataMatrix, rows, cols);

    //Print Averages
    printAverages(dataMatrix, rowAveVector, colAveVector, overallAve, rows, cols);

    //Free dynamically allocated storage
    // TODO: PUT CODE HERE TO FREE DYNAMICALLY ALLOCATED STORAGE: dataMatrix, rowVector,
    //colVector
    free(dataMatrix);
    free(rowAveVector);
    free(colAveVector);

    //Check if user wants to enter a new matrix
    printf("Enter 0 to continue with a new matrix\n");
    printf("Enter any other number to terminate the program: ");
    scanf("%d", &done);
  }
  //That's it, we are done
  return (0);
}
/*=======================
 *     Matrix Creator
 *=======================*/
float *readMatrix(int numRows, int numCols)
//Dynamically allocate an array to hold a matrix of floats.
//The dimension of the matrix is numRows x numCols.
//If the malloc fails, return NULL.
//Otherwise, prompt the user to enter numRows*numCols values
//for the matrix in by-row order.
//Store the values entered by the user into the array and
//return a pointer to the array.
{
  //TODO:  Implement this function
	float *dataMatrixx;
	dataMatrixx = (float *) malloc((numRows * numCols) * sizeof(float));
	if (dataMatrixx != NULL)
	{
		int i;
		float user;
		printf("Enter %d data values for %d x %d matrix, in by-row order:\n", numRows * numCols, numRows, numCols);
		for(i = 0; i < (numRows * numCols); i++)
		{
			scanf("%f", &user);
			dataMatrixx[i] = user;
		}
		return dataMatrixx;
	}
	else
	{
		return NULL;
	}
}

/*=======================
 *    Average of Rows
 *=======================*/
float *rowAverage(float *matrix, int numRows, int numCols)
// Dynamically allocate an array of floats with numRows elements.
// Return NULL if the memory allocation fails.
// Otherwise, for 0 <= i < numRows, set the  ith element of the
// new array to the mean of the values in the ith row of the array
//pointed to by matrix.  The dimension of the matrix is
//numRows x numCols and its elements are stored in by-row order.
{
  //TODO: Implement this function
	float *rowAveVectorr;
	rowAveVectorr = (float *) malloc(numRows * sizeof(float));
	if (rowAveVectorr != NULL)
	{
		int i, j, sum = 0;
		for(i = 0; i < numRows; i++)
		{
			sum = 0;
			for(j = 0; j < numCols; j++)
			{
				sum = sum + (matrix[j + (i * numCols)]);
			}
			rowAveVectorr[i] = (float)sum / (float)numCols;
		}
		return rowAveVectorr;
	}
	else
	{
		return NULL;
	}
}

/*=======================
 *  Average of Columns
 *=======================*/
float *colAverage(float *matrix, int numRows, int numCols)
// Dynamically allocate an array of floats with numCols elements.
// Return NULL if the memory allocation fails.
// Otherwise, for 0 <= j < numCols, set the  jth element of the
// new array to the mean of the values in the jth column of the array
//pointed to by matrix.  The dimension of the matrix is
//numRows x numCols and its elements are stored in by-row order.
{
  //TODO: Implement this function.
	float *colAveVectorr;
	colAveVectorr = (float *) malloc(numRows * sizeof(float));
	if (colAveVectorr != NULL)
	{
		int i, j, sum = 0;
		for(i = 0; i < numCols; i++)
		{
			sum = 0;
			for(j = 0; j < numRows; j++)
			{
				sum = sum + (matrix[i + (j * numRows)]);
			}
			colAveVectorr[i] = (float)sum / (float)numRows;
		}
		return colAveVectorr;
	}
	else
	{
		return NULL;
	}
}

/*============================
 *  Average of Entire Matrix
 *============================*/
float overallAverage(float* matrix, int numRows, int numCols)
// Return the mean value of the elements of the array pointed
// to by matrix.  The dimension of the matrix is numRows x numCols.
{
  //TODO: Implement this function.
	float overallAveragee;
	int i, sum = 0;
	for (i = 0; i < (numRows * numCols); i++)
	{
		sum = sum + matrix[i];
	}
	overallAveragee = (float)sum / (float)(numRows * numCols);
	return overallAveragee;
}

/*==============================
 *  Matrix and Average Printer
 *==============================*/
void printAverages(float *matrix, float *rowAve, float *colAve, float overallAve, int numRows, int numCols)
 // Print the matrix with the row average displayed to the right of each row
 // and the column average displayed below each column.
 // Also print the overall average
 {
   //TODO: Implement this function.
	int i;								/*     Initialize Loop Counter     */
	for (i = 0; i < (numRows * numCols); i++)
	{
		if (i % numCols == 0)
		{
			if (((i % numCols) == 0) && (i != 0 ))
			{
				printf("\t[ %2.2f ]", rowAve[(i / numCols) - 1]);
			}
			printf("\n");				/* Begin New Line Every New Row Values */
		}
		{
		}
		printf("\t[ %2.2f ]", matrix[i]);		/*    Print This Elements Value    */
	}

	printf("\t[ %2.2f ]", rowAve[numRows - 1]);
	printf("\n");
	for (i = 0; i < numCols; i++)
	{
		if (i % numCols == 0)
			printf("\n");				/* Begin New Line Every New Row Values */
		{
		}
		printf("\t[ %2.2f ]", colAve[i]);		/*    Print This Elements Value    */
	}
	printf("\n");
	printf("\n");
	printf("\tOverall Average: %2.2f\n", overallAve);
	printf("\n");
 }

