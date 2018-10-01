/*----------------------------------------------------------
 * Programmer: Alex Wong
 * Date: 7/7/16
 * Name: hw3.c
 * Description:
 * To run this program:  This program requires a command line
 * argument that specifies the name of the text file containing
 * the input data for the program. In Code::Blocks this argument
 * can be specified by selecting the "Project" menu, then
 * "Set Program's arguments", and then typing the name of
 * of the text file (including the .txt extension) in the box
 * labeled "program's arguments".
 ---------------------------------------------------------*/
/*=======================
 *   Import Statements
 *=======================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*=======================
 *  Function Prototypes
 *=======================*/
int *countWords( char **words, int n);
void compress(char ***wordArray, int **countArray, int *size);
int *copyCountArray(int *countArray, int n);
char **copyWordArray(char **wordArray, int n);
void sortAlpha(char **wordArray, int *countArray, int n);
void sortFreq(char **wordArray, int *countArray, int n);

/*=======================
 *      Main Method
 *=======================*/
int main(int argc, char *argv[])
{
	/*=======================
	 *    Initial Values
	 *=======================*/
	char buffer[100];  //Maximum word size is 100 letters
	FILE *textFile;
	int numWords=0;
	int nextWord;
	int i, j, len, lastChar;
	char  *wordPtr;
	char  **wordArray;
	int *countArray;
	int *alphaCountArray;
	char **alphaWordArray;
	int *freqCountArray;
	char **freqWordArray;
	/*=======================
	 * End of Initial Values
	 *=======================*/
	//Check to see if command line argument (file name)
	//was properly supplied.  If not, terminate program
	if(argc == 1)
	{
		printf ("Must supply a file name as command line argument\n");
		return (0);
	}

	//Open the input file.  Terminate program if open fails
	textFile=fopen(argv[1], "r");
	if(textFile == NULL)
	{
		printf("Error opening file. Program terminated.\n");
		return (0);
	}

	//Read file to count the number of words
	fscanf(textFile, "%s", buffer);
	while(!feof(textFile))
	{
		numWords++;
		fscanf(textFile, "%s", buffer);
	}

	printf("The total number of words is: %d\n", numWords);
	//Create array to hold pointers to words
	wordArray = (char **) malloc(numWords*sizeof(char *));
	if (wordArray == NULL)
	{
		printf("malloc of word Array failed.  Terminating program.\n");
		return (0);
	}
	//Rewind file pointer and read file again to create
	//wordArray
	rewind(textFile);
	for(nextWord=0; nextWord < numWords; nextWord++)
	{
		//read next word from file into buffer.
		fscanf(textFile, "%s", buffer);

		//Remove any punctuation at beginning of word
		i=0;
		while(!isalpha(buffer[i]))
		{
			i++;
		}
		if(i>0)
		{
			len = strlen(buffer);
			for(j=i; j<=len; j++)
			{
				buffer[j-i] = buffer[j];
			}
		}

		//Remove any punctuation at end of word
		len  = strlen(buffer);
		lastChar = len -1;
		while(!isalpha(buffer[lastChar]))
		{
			lastChar--;
		}
		buffer[lastChar+1] = '\0';

		//make sure all characters are lower case
		for(i=0; i < strlen(buffer); i++)
		{
			buffer[i] = tolower(buffer[i]);
		}

		//Now add the word to the wordArray.
		//Need to malloc an array of chars to hold the word.
		//Then copy the word from buffer into this array.
		//Place pointer to array holding the word into next
		//position of wordArray
		wordPtr = (char *) malloc((strlen(buffer)+1)*sizeof(char));
		if(wordPtr == NULL)
		{
			printf("malloc failure.  Terminating program\n");
			return (0);
		}
		strcpy(wordPtr, buffer);
		wordArray[nextWord] = wordPtr;
	}

	//Call countWords() to create countArray and replace
	//duplicate words in wordArray with NULL
	countArray = countWords(wordArray, numWords);
	if(countArray == NULL)
	{
		printf("countWords() function returned NULL; Terminating program\n");
		return (0);
	}

	//Now call compress to remove NULL entries from wordArray
	compress(&wordArray, &countArray, &numWords);
	if(wordArray == NULL)
	{
		printf("compress() function failed; Terminating program.\n");
		return(0);
	}
	printf("Number of words in wordArray after eliminating duplicates and compressing is: %d\n", numWords);

	//Create copy of compressed countArray and wordArray and then sort them alphabetically
	alphaCountArray = copyCountArray(countArray, numWords);
	alphaWordArray = copyWordArray(wordArray, numWords);
	sortAlpha(alphaWordArray, alphaCountArray, numWords);

	//print words and frequencies alphabetically --For debugging use
	/*
  printf("ALPHABETIC LIST OF WORDS AND FREQUENCIES OF OCCURRENCE:\n");
  for(i=0; i< numWords; i++)
  {
    printf("%s %d\n", alphaWordArray[i], alphaCountArray[i]);
  }
	 */

	//Now make another copy of countArray and WordArray and sort them by frequency of occurrence (most to least).
	freqCountArray = copyCountArray(alphaCountArray, numWords);
	freqWordArray = copyWordArray(alphaWordArray, numWords);
	sortFreq(freqWordArray, freqCountArray, numWords);
	/*
  //print words and frequencies from largest to smallest frequency of occurrence--For debugging use
  printf("LIST OF WORDS AND FREQUENCIES FROM HIGHEST FREQUENCY OF OCCURRENCE TO LOWEST.\n");
  for(i=0; i<numWords; i++)
  {
    printf("%s %d\n", freqWordArray[i], freqCountArray[i]);
  }
	 */

	//**************************************************************
	// TODO
	// YOUR CODE HERE TO COMPLETE MAIN PROGRAM:
	// DISPLAY MENU TO ALLOW USERS TO VIEW WORDS AND
	//FREQUENCIES OF OCCURRANCE AS SPECIFIED IN HW3
	//ASSIGNMENT
	//**************************************************************

	/*=======================
	 *    Initial Values
	 *=======================*/
	int loop = 1, input;
	char input2;
	/*=======================
	 * End of Initial Values
	 *=======================*/
	while(loop)																/*            Loop Menu           */
	{																		/*     Printing Out The Array     */
		puts("  How would you like to display the list of words?  ");
		puts("-------------------Menu-----------------------------");		/*      Displaying The Menu       */
		puts("    1)Alphabetically        2)By Frequency          ");
		puts("    3)Exit                                          ");
		puts("----------------------------------------------------");		/*       End of Menu Display      */
		puts(" ");
		printf("Please enter one of the following options: ");
		scanf("%d", &input);												/*   User Input For Menu Options  */
		/*==================================
		 *  Start of Switch Case Statement
		 *==================================*/
		switch(input)
		{
		case 1:			/* Case for Organizing the List Alphabetically */
			puts("");
			printf(" Enter a letter a-z to display words starting with that letter: ");
			scanf(" %c", &input2);
			printf("List of words beginning with the letter %c:\n", input2);
			puts("");
			int count;
			for (count = 0; count < numWords; count++)
			{
			    char first = *(alphaWordArray[count]);
				if(first == input2)
				{
					printf("%s, ",  alphaWordArray[count]);
					printf("%d\n",  alphaCountArray[count]);
				}
			}
			puts("");
			break;
		case 2:			/* Case for Organizing the List by Most Frequent */
            puts("");
		    printf(" Enter a number between 0 and 358: ");
		    int input3;
		    scanf(" %d", &input3);
		    int count2;
		    for (count2 = 0; count2 < input3; count2++)			/* Printing the User Inputed Number of Top Frequent Words */
            {
                printf("%s, ",  freqWordArray[count2]);
                printf("%d\n",  freqCountArray[count2]);
            }
			break;
		case 3:			/* Exiting Program Case */
			loop = 0;
			puts("-----------------------End of Program-----------------------");
			break;
		default:		/* Catch Case */
			puts("Error - The number entered is not valid!");
		}
		/*================================
		 *  End of Switch Case Statement
		 *================================*/
	}
	return(0);
}

/*================================
 *       Word Count Method
 *================================*/
int *countWords( char **wordArray, int n)
{
	int *countArr = (int *) malloc(n * sizeof(int));
	if (countArr != NULL)
    {
        int counter;
        for(counter = 0; counter < n; counter++)
        {
            int inc;
            for(inc = 0; inc <= counter; inc++)
            {
                if (wordArray[inc] != NULL && wordArray[counter] != NULL)	/* Check if Element is already NULL */
                {
                    if (strcmp(wordArray[counter],wordArray[inc]) == 0)		/* Compare Words to see if they are the exact same Word */
                    {
                            countArr[inc]+=1;
                            if (countArr[inc] > 1)
                            {
                                wordArray[counter] = NULL;					/* Get Rid of Duplicated Words in Array by Replace to NULL for compress() */
                                countArr[counter] = 0;
                            }
                    }
                }
            }
        }
        return countArr;
    }
    else
    {
        return NULL;
    }
	//TODO:  COMPLETE THIS FUNCTION AS SPECIFIED IN HW3 ASSIGNMENT
}

/*================================
 *     List Compressor Method
 *================================*/
void compress(char ***wordArray, int **countArray, int *size)
{
	int i;
	int nullCount = 0;
	char **newWordArray;
	int *newCountArray;
	int next;

	//Determine number of NULL entries in wordArray
	for (i=0; i< *size; i++)
	{
		if ((*wordArray)[i] == NULL)
			nullCount++;
	}

	//if wordArray has NULL entries, malloc a new wordArray and a
	//new countArray.
	if (nullCount != 0)
	{
		newWordArray = (char **) malloc((*size-nullCount)*sizeof(char *));
		newCountArray = (int *) malloc((*size-nullCount)*sizeof(int));
		if (newWordArray != NULL && newCountArray != NULL)
		{
			//Copy entries from original wordArray and countArray to new arrays,
			//skipping NULL entries.
			next = 0;
			for (i=0; i< *size; i++)
			{
				if ((*wordArray)[i] != NULL)
				{
					newWordArray[next] = (*wordArray)[i];
					newCountArray[next] = (*countArray)[i];
					next++;
				}
			}
			//Free original arrays
			free(*wordArray);
			free(*countArray);

			//Assign new values to pass-by-reference parameters
			*wordArray = newWordArray;
			*countArray = newCountArray;
			*size = *size - nullCount;
		}
		else
		{
			*wordArray=NULL;
			*countArray=NULL;
		}
	}
}

/*==================================
 * Word Frequency Array Copy Method
 *==================================*/
int *copyCountArray(int *countArray, int n)
{
	int a;
	int *copy;
	copy = (int *) malloc(n * sizeof(int));
	if (copy != NULL)
	{
		for (a = 0; a < n; a++)
		{
			copy[a] = countArray[a];
		}
		return copy;
	}
	else
	{
		return NULL;
	}
	//TODO:  COMPLETE THIS FUNCTION AS SPECIFIED IN HW3 ASSIGNMENT
}

/*================================
 *     Word Array Copy Method
 *================================*/
char **copyWordArray(char **wordArray, int n)
{
	int a;
	char **copy;
	copy = (char **) malloc(n * sizeof(char *));
	if (copy != NULL)
	{

		for (a = 0; a < n; a++)
		{
			copy[a] = wordArray[a];
		}
		return copy;
	}
	else
	{
		return NULL;
	}
	//TODO:  COMPLETE THIS FUNCTION AS SPECIFIED IN HW3 ASSIGNMENT
}

/*====================================
 *   Alphabetical Array Sort Method
 *====================================*/
void sortAlpha(char **wordArray, int *countArray, int n)
{
	int i, j;
	for(i = 0; i < (n); ++i)
	{
		for(j = 0; j < n; ++j)
		{
			if(strcmp(wordArray[j], wordArray[i]) > 0)
			{
				char place[strlen(wordArray[i])];
				place = wordArray[i];
				wordArray[i] = wordArray[j];
				wordArray[j] = place;
				int place2;
				place2 = countArray[i];
				countArray[i] = countArray[j];
				countArray[j] = place2;
			}
		}
	}
}
//TODO:  COMPLETE THIS FUNCTION AS SPECIFIED IN HW3 ASSIGNMENT

/*====================================
 *    Frequency Array Sort Method
 *====================================*/
void sortFreq(char **wordArray, int *countArray, int n)
{
	int i, j;
		int place;
		for(i = 0; i < (n); ++i)
		{
			for(j = 0; j < n; ++j)
			{
				if(countArray[i] > countArray[j])
				{
					place = countArray[i];
					countArray[i] = countArray[j];
					countArray[j] = place;
					char place2[strlen(wordArray[i])];
					place2 = wordArray[i];
					wordArray[i] = wordArray[j];
					wordArray[j] = place;
					wordArray[j] = place2;
				}
			}
		}
	//TODO:  COMPLETE THIS FUNCTION AS SPECIFIED IN HW3 ASSIGNMENT
}

