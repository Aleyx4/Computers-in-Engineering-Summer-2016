/*-----------------------------------------------------------------------------
* Programmer: Alex Wong
* Date: 06/20/16
* Name: hw1/main.c
* Description:  This program will start by creating an array for the user using
*		this the user will input the numbers into the array. Then the
*		program will prompt the user with a list of choices in the
*		menu. In the menu the user will see the array they entered.
*		The user may input the number that is listed on the side
*		to allow the program to find the mean, median, variance, or
*		standard deviation. Some extra features will include the
*		ability to change the current array and the ability to sort
*		the array if it has not been already. The median function will
*		automatically sort the array. The program will exit if entered
*		option number five. To change the max value the constant MAX
*		is defined.
* Pseudocode:   Initialize all values, create a loop to allow the program to
* 		start over if asked. Prompt user to enter number of numbers
* 		they wish to enter. Care for the exception if user enters
* 		more than the MAX value. Allow the user to try again, else
* 		prompt the user to enter the values. While the number of nums
* 		is less than the number entered (count) then loop back to
* 		allow the user to continue entering. Once entered the last
* 		value. Create a loop to the menu. Display the original array
* 		the user inputed and then prompt the user with the menu
* 		options. Using a switch case to execute the methods asked and
* 		display the returned value. If user places anything besides
* 		what is asked in the switch case then prompt the user to
* 		enter a valid option.
*
* 		Mean()
* 		Add all values in the array inputed by user. Then divide the
* 		number of value. Then return the mean.
*
* 		Median()
* 		Sort the array using the sort method and then check if the
* 		number of elements in the array are even or odd. If it is odd
* 		the median is the middle number in the array, so divide the
* 		number of elements by two. If the array is even then the two
* 		middle numbers must be added and the divided by two. After
* 		the median is found return the value.
*
* 		Printarray()
* 		Take each value of the array and display it. Every ten values
* 		read and displayed inputs a new line.
*
* 		Sort()
* 		Take the first number in the array and check if the number
* 		next to it. If it is greater than the first number it is in
* 		the correct order. If it is less than the first number it must
* 		be switched to the next element in the array and tested on
* 		the other element on the right side to see if it is greater or
* 		less than. Once placed in the correct order check the next
* 		element till all the elements in the array are sorted.
*
* 		Variance()
* 		Call the mean method and the subtract the mean from all of the
* 		numbers on the array then take the square of all the numbers.
* 		After then sum them up and divide by the number of numbers to
* 		get the variance. Return the variance. Be sure to create a new
* 		array to not modify the original array, allowing the user to
* 		continue to use all the methods at the main menu.
*
* 		StandardDeviation()
* 		Using the variance method to return Variance via Pass-by-Reference.
* 		Take the square root of the variance to get the standard
* 		deviation. Return the Standard Deviation via Pass-by-Reference.
 -----------------------------------------------------------------------------*/

/*=======================
 *   Import Statements
 *=======================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*=======================
 *   Defined Constants
 *=======================*/
#define MAX 20

/*=======================
 *  Function Prototypes
 *=======================*/
void printarray(float arr[], int n);
float mean(float arr[], int n);
float median(float arr[], int n);
float variance(float arr[], int n);
void standarddev(float arr[], int n, float *var, float *stdDev);
void sort(float arr[], int n);

/*=======================
 *      Main Method
 *=======================*/
int main( void )
{
	setbuf(stdout, NULL); 				/* Buffer Disabled - Used for Eclipse Debugging */
	int loop = 1;						/*       Initialize Loop Value to be True       */
	while(loop)
	{
		/*=======================
		 *    Initial Values
		 *=======================*/
		float standardDEV = 0, VAR = 0, currentnum;
		int loop2 = 1, nums, count, input;
		/*=======================
		 * End of Initial Values
		 *=======================*/
		printf("How many numbers do you wish to enter (Maximum of %d): ", MAX);
		scanf("%d", &nums);
		puts(" ");
		float myarray[nums];				/*                     Creating The Array                  */
		if ((nums <= MAX) && (nums > 0))	/* If Statement to Check if Number Entered is Within Range */
		{
			printf("Please enter your numbers (press enter after each number you enter): \n");
			for(count = 0; count < nums; count++)
			{
				scanf("%f", &currentnum);
				myarray[count] = currentnum;
			}
			while(loop2)															/*            Loop Menu           */
			{
				puts("Your Array:");
				printarray(myarray, nums);											/*     Printing Out The Array     */
				puts(" ");
				puts("-------------------Menu-----------------------------");		/*      Displaying The Menu       */
				puts("    1)Mean                  2)Median                ");
				puts("    3)Variance              4)Standard Deviation    ");
				puts("    5)Exit                  6)Change Array          ");
				puts("    7)Sort Array                                    ");
				puts("----------------------------------------------------");		/*       End of Menu Display      */
				puts(" ");
				printf("Please enter one of the following options: ");
				scanf("%d", &input);												/*   User Input For Menu Options  */
				/*==================================
				 *  Start of Switch Case Statement
				 *==================================*/
				switch(input)
				{
					case 1:
						printf("The mean value is: %2.2f\n", mean(myarray, nums));
						break;
					case 2:
						printf("The median value is: %2.2f\n", median(myarray, nums));
						break;
					case 3:
						printf("The variance value is: %2.2f\n", variance(myarray, nums));
						break;
					case 4:
						standarddev(myarray, nums, &VAR, &standardDEV);
						printf("The variance value is: %2.2f\n", VAR);
						printf("The standard deviation value is: %2.2f\n", standardDEV);
						break;
					case 5:
						loop2 = 0;
						loop = 0;
						puts("-----------------------End of Program-----------------------");
						break;
					case 6:
						loop2 = 0;
						break;
					case 7:
						sort(myarray, nums);
						break;
					default:
						puts("Error - The number entered is not valid!");
				}
				/*================================
				 *  End of Switch Case Statement
				 *================================*/
			}
		}
		else	/* Else Statement If The Number of Numbers The User Inputed is Too Small or Too Large */
		{
			printf("This is an invalid number please enter a number within the range of 1 - %d.\n", MAX);
		}
	}
	return 0;
}

/*========================
 *  Array Display Method
 *========================*/
void printarray(float arr[], int n)
{
	int i;								/*     Initialize Loop Counter     */
	for (i = 0; i < n; i++)
	{
	    if (i % 10 == 0)
	        printf("\n");				/* Begin New Line Every Ten Values */
	    {
	    }
	    printf("[%2.2f] ", arr[i]);		/*    Print This Elements Value    */
	}
	printf("\n");
}

/*=======================
 *  Array Sorter Method
 *=======================*/
void sort(float arr[], int n)
{
	int i, j;
	float place;						/* Number Holder for Swap */
	for(i = 0; i < (n); ++i)
	{
		for(j = 0; j < n; ++j)
		{
			if(arr[i] < arr[j])			/* Check if Left Integer is a Larger Value than Right Integer then Swap */
			{
				place = arr[i];
				arr[i] = arr[j];
			 	arr[j] = place;
			}
		}
	}
}

/*=======================
 *      Mean Method
 *=======================*/
float mean(float arr[], int n)
{
	float sum = 0, mean = 0;
	int i;
	for(i = 0; i < n; i++)		/* Loop to Sum Numbers in Array */
	{
		sum = arr[i] + sum;
	}
	mean = sum / n;				/* Divide the Sum by the Number of Numbers in the Array */
	return mean;
}

/*=======================
 *     Median Method
 *=======================*/
float median(float arr[], int n)
{
	sort(arr, n);
	int medianarr = 0, low = 0, high = 0;
	float medianval = 0;
	if ((n % 2) != 0)			/* Loop for Odd Number of Numbers in the Array */
	{
		medianarr = (n / 2);
		return arr[medianarr];
	}
	else						/* Loop for Even Number of Numbers in the Array */
	{
		low = (n / 2) - 1 ;
		high = low + 1 ;
		medianval =  (arr[low] + arr[high]) / 2;
		return medianval;
	}
}

/*=======================
 *    Variance Method
 *=======================*/
float variance(float arr[], int n)
{
	int i;
	float meanval, arr2[n];
	for(i = 0; i < n; i++)		/* Copy Array to Not Modify Original Array */
	{
		arr2[i] = arr[i];
	}
	meanval = mean(arr2, n);
	for(i = 0; i < n; i++)		/* Variance Loop Formula */
	{
		arr2[i] = pow((arr2[i] - meanval),2);
	}
	return mean(arr2, n);		/* Getting Variance Array Mean then Return as Variance */
}

/*=============================
 *  Standard Deviation Method
 *=============================*/
void standarddev(float arr[], int n, float *var, float *stdDev)
{
	*var = variance(arr, n);
	*stdDev = sqrtf(*var);		/* Standard Deviation Formula */
}
