/*------------------------------------------------------------------------------
 * Programmer: Alex Wong
 * Date: 7/14/16
 * Name: hw4.c
 * Description:
 * Pseudocode:
-------------------------------------------------------------------------------*/
/*=======================
 *   Import Statements
 *=======================*/
#include <stdio.h>
#include <stdlib.h>
#include "useCurses.h"
#include "robotModel.h"
#include "maze.h"

/*=======================
 *       Structures
 *=======================*/
struct node {
    char data;
    struct node * nextPtr;
};

typedef struct node Path;
typedef struct node * nodePtr;


/*=======================
 *  Function Prototypes
 *=======================*/
int initMazeAndRobotFromCLArgs(int argc, char *argv[], Maze *maze, RobotModel *robot);
void straight(Maze *maze, RobotModel *robot);
void leftc(Maze *maze, RobotModel *robot);
void rightc(Maze *maze, RobotModel *robot);
void tee(Maze *maze, RobotModel *robot);
void leftt(Maze *maze, RobotModel *robot);
void rightt(Maze *maze, RobotModel *robot);
void cross(Maze *maze, RobotModel *robot);
void deadend(Maze *maze, RobotModel *robot);
int checkfinish(Maze *maze, RobotModel *robot);
void insertpath(nodePtr *startPtr, char direction);
void opt(nodePtr *startPtr);
void printpath(nodePtr startPtr);

/*=======================
 *      Main Method
 *=======================*/
int main( int argc, char *argv[] )
{
    Maze maze;             	 				/* structure to store maze */
    RobotModel robot;       				/* structure to model robot (current position + direction) */
    nodePtr startPtr = NULL;				/* pointer that points to the start of the path list */
    int intialcol, intialrow, intialdir;	/* variables to store robots intial location and direction */

    initscr();								/* initialize curses mode */

    /* if successfully have initialized robot and maze, solve maze */
    if (initMazeAndRobotFromCLArgs(argc, argv, &maze, &robot))
    {
        printMazePlusCurrentPos(maze, robot);

        intialcol = colrobotlocation(&robot);				/* Start Location Column of Robot */
        intialrow = rowrobotlocation(&robot);				/* Start Location Row of Robot */
        intialdir = dirrobot(&robot);						/* Start Direction of Robot */

        /* loop to check if it reaches to the finish line */
        while(!checkfinish(&maze, &robot))
        {
        	/* check if robot is on a straight away */
            if((blackInFront(maze, robot))&&(!blackToLeft(maze, robot))&&(!blackToRight(maze, robot)))
            {
                straight(&maze, &robot);
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* check if robot is on a left corner */
            else if((!blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(!blackToRight(maze, robot)))
            {
                leftc(&maze, &robot);
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* check if robot is on a right corner */
            else if((!blackInFront(maze, robot))&&(!blackToLeft(maze, robot))&&(blackToRight(maze, robot)))
            {
                rightc(&maze, &robot);
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* check if robot is on a tee section */
            else if((!blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(blackToRight(maze, robot)))
            {
                tee(&maze, &robot);
                insertpath(&startPtr, 'R');
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* check if robot is on a left tee junction */
            else if((blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(!blackToRight(maze, robot)))
            {
                leftt(&maze, &robot);
                insertpath(&startPtr, 'S');
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* check if robot is on a right tee junction */
            else if((blackInFront(maze, robot))&&(!blackToLeft(maze, robot))&&(blackToRight(maze, robot)))
            {
                rightt(&maze, &robot);
                insertpath(&startPtr, 'R');
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* check if robot is on a cross section */
            else if((blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(blackToRight(maze, robot)))
            {
                cross(&maze, &robot);
                insertpath(&startPtr, 'R');
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* check if robot is on a dead end */
            else if((!blackInFront(maze, robot))&&(!blackToLeft(maze, robot))&&(!blackToRight(maze, robot)))
            {
                deadend(&maze, &robot);
                insertpath(&startPtr, 'U');
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* unlikely to happen, but if it does here is a catcher */
            else
            {
                printw("Error - Sensor Readings Do Not Fall In Any Conditions");
            }
            printMazePlusCurrentPos(maze, robot);
            printpath(startPtr);
            refresh();
            napms(200);
        }
        opt(&startPtr);												/* optimize path list after robot finishes list for the first time */
        placeRobot(&robot, intialrow, intialcol, intialdir);		/* robot is set back on the original position where it first started */
        printMazePlusCurrentPos(maze, robot);
        printw("                                                                 \n");		/* clear the buffered section of printw */
        printw("                                                                 \n");		/* clear the buffered section of printw */
        printMazePlusCurrentPos(maze, robot);
        printpath(startPtr);										/* print list of optimized path list */
        refresh();
        nodePtr currentPtr = startPtr;
        /* check when robot is at finish line to the new optimized path */
        while(!checkfinish(&maze, &robot))
        {
        	/* if the robot is on a path that requires a choice it will go to the linked list */
        	/* else follow the normal path rules */
            if(((!blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(blackToRight(maze, robot)))||
            		((blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(!blackToRight(maze, robot)))||
					((blackInFront(maze, robot))&&(!blackToLeft(maze, robot))&&(blackToRight(maze, robot)))||
					((blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(blackToRight(maze, robot)))||
					((!blackInFront(maze, robot))&&(!blackToLeft(maze, robot))&&(!blackToRight(maze, robot))))
            {
            	/* if path lists current pointer has R then turn right */
                if((currentPtr->data) == 'R')
                {
                    turnRight(&robot);
                    printMazePlusCurrentPos(maze, robot);
                    refresh();
                    napms(200);
                }
                /* if path lists current pointer has L then turn left */
                else if((currentPtr->data) == 'L')
                {
                    turnLeft(&robot);
                    printMazePlusCurrentPos(maze, robot);
                    refresh();
                    napms(200);
                }
                /* if path lists current pointer is anything other than that go straight */
                else
                {
                    moveStraight(&robot);
                    printMazePlusCurrentPos(maze, robot);
                    refresh();
                    napms(200);
                }
                /* current pointer gets the next pointer of current pointer */
                currentPtr = currentPtr->nextPtr;
            }
            /* if robot is on the left corner turn left */
            else if((!blackInFront(maze, robot))&&(blackToLeft(maze, robot))&&(!blackToRight(maze, robot)))
            {
                leftc(&maze, &robot);
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* if robot is on the right corner turn right */
            else if((!blackInFront(maze, robot))&&(!blackToLeft(maze, robot))&&(blackToRight(maze, robot)))
            {
                rightc(&maze, &robot);
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
            /* go straight if it is not a corner turn */
            else
            {
                moveStraight(&robot);
                printMazePlusCurrentPos(maze, robot);
                refresh();
                napms(200);
            }
        }
    }
    printMazePlusCurrentPos(maze, robot);
    printw("                                                                 \n");		/* clear the buffered section of printw */
    printw("                                                                 \n");		/* clear the buffered section of printw */
    refresh();
    printMazePlusCurrentPos(maze, robot);
    printw("\nDONE!");
    refresh();
    getch();
    endwin();
    return 0;
}

/*-----------------------------------------------------------------------------
 * Function name: initMazeAndRobotFromCLArgs
 * Description: This function uses the specified command-line arguments to
 *              initialize the given Maze and RobotModel variables. If the
 *              incorrect number of command-line arguments is passed, an
 *              error message is displayed (and 0 is returned).
 * Inputs: argc = int = number of command-line arguments
 *         argv = array of strings = command-line arguments, with argv[1]
 *                                   being the input file name
 *         m = Maze * = pointer to Maze structure that should be initialized
 *                      in this function (passed by simulated reference)
 *         robot = RobotModel * = pointer to RobotModel that should be
 *                                initialized in this function (passed by
 *                                simulated reference)
 * Outputs: m = Maze * = pointer to initialized Maze
 *          robot = RobotModel * = pointer to initialized RobotModel
 *          int = 1 if initialization successful
 *                0 if error encountered
 ----------------------------------------------------------------------------*/
int initMazeAndRobotFromCLArgs(int argc, char *argv[], Maze *maze, RobotModel *robot)
{
    int success = 1;
    char *inputFileName;    /* input file name containing maze */
    /* obtain input filename from command line */
    if (argc >= 2) /* require at least two command-line arguments */
    {
        inputFileName = argv[1];
    }
    else
    {
        /* when incorrect number of command-line arguments are passed,
           print message indicating proper usage of program  */
        printf("Usage: %s inputFileName.txt\n", argv[0]);
        success = 0;
    }

    if (success)
    {
        success = readMaze(inputFileName, maze, robot);
    }

    return success;
}

/*=======================
 *     Straight Away
 *=======================*/
void straight(Maze *maze, RobotModel *robot)
{
    moveStraight(robot);
}

/*=======================
 *      Left Corner
 *=======================*/
void leftc(Maze *maze, RobotModel *robot)
{
    turnLeft(robot);
}

/*=======================
 *      Right Corner
 *=======================*/
void rightc(Maze *maze, RobotModel *robot)
{
    turnRight(robot);
}

/*=======================
 *      Tee Section
 *=======================*/
void tee(Maze *maze, RobotModel *robot)
{
    turnRight(robot);
}

/*=======================
 *   Left Tee Section
 *=======================*/
void leftt(Maze *maze, RobotModel *robot)
{
    moveStraight(robot);
}

/*=======================
 *   Right Tee Section
 *=======================*/
void rightt(Maze *maze, RobotModel *robot)
{
    turnRight(robot);
}

/*=======================
 *     Cross Section
 *=======================*/
void cross(Maze *maze, RobotModel *robot)
{
    turnRight(robot);
}

/*=======================
 *        Dead End
 *=======================*/
void deadend(Maze *maze, RobotModel *robot)
{
    uTurn(robot);
}

/*==============================
 *  Finish Line Checker Method
 *==============================*/
int checkfinish(Maze *maze, RobotModel *robot)
{
    if((blackToLeft(*maze, *robot))&&(blackToRight(*maze, *robot))&&(blackInFront(*maze, *robot)))
    {
        moveStraight(robot);
        if((blackToLeft(*maze, *robot))&&(blackToRight(*maze, *robot))&&(blackInFront(*maze, *robot)))
        {
            return 1;
        }
        else
        {
            reverse(robot);
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

/*===========================
 *   Print Path List Method
 *===========================*/
void printpath(nodePtr startPtr)
{
    nodePtr currentPtr;
    printw("Path List:\n");
    for (currentPtr = startPtr; currentPtr != NULL; currentPtr = currentPtr->nextPtr)
    {
        printw("%c -> ", currentPtr->data);
    }
    if(currentPtr == NULL)
    {
        printw("NULL");
    }
}

/*==============================
 *   Insert Path Node Methods
 *==============================*/
void insertpath(nodePtr *startPtr, char direction)
{
    nodePtr newNodePtr;
    nodePtr beforeNodePtr, afterNodePtr;
    newNodePtr = (nodePtr) malloc(sizeof(Path));
    if (newNodePtr != NULL)
    {
        newNodePtr->data = direction;
        newNodePtr->nextPtr = NULL;
        beforeNodePtr = NULL;
        afterNodePtr = *startPtr;
        while (afterNodePtr != NULL)
        {
            beforeNodePtr = afterNodePtr;
            afterNodePtr = afterNodePtr->nextPtr;
        }
        if (beforeNodePtr == NULL)
        {
            newNodePtr->nextPtr = *startPtr;
            *startPtr = newNodePtr;
        }
        else
        {
            beforeNodePtr->nextPtr = newNodePtr;
            newNodePtr->nextPtr = afterNodePtr;
        }
    }
    else
    {
        printw("Error - Allocating memory failed for path creation.\n");
    }
}

/*========================
 *   Optimization Method
 *========================*/
void opt(nodePtr *startPtr)
{
    nodePtr beforePtr, afterPtr, middlePtr;
    beforePtr = *startPtr;
    middlePtr = beforePtr->nextPtr;
    if(middlePtr != NULL)
    {
        afterPtr = middlePtr->nextPtr;
    }
    else
    {
        afterPtr = NULL;
    }
    while(afterPtr != NULL)
    {
        if(middlePtr->data == 'U')
        {
            nodePtr delPtr, delnextPtr;
            if((beforePtr->data == 'S')&&(afterPtr->data == 'R'))
            {
                delPtr = middlePtr;
                delnextPtr = afterPtr;
                beforePtr->data = 'L';
                beforePtr->nextPtr = afterPtr->nextPtr;
                free(delPtr);
                free(delnextPtr);
            }
            else if((beforePtr->data == 'R')&&(afterPtr->data == 'R'))
            {
                delPtr = middlePtr;
                delnextPtr = afterPtr;
                beforePtr->data = 'S';
                beforePtr->nextPtr = afterPtr->nextPtr;
                free(delPtr);
                free(delnextPtr);
            }
            else if((beforePtr->data == 'R')&&(afterPtr->data == 'S'))
            {
                delPtr = middlePtr;
                delnextPtr = afterPtr;
                beforePtr->data = 'L';
                beforePtr->nextPtr = afterPtr->nextPtr;
                free(delPtr);
                free(delnextPtr);
            }
            else if((beforePtr->data == 'S')&&(afterPtr->data == 'S'))
            {
                delPtr = middlePtr;
                delnextPtr = afterPtr;
                beforePtr->data = 'U';
                beforePtr->nextPtr = afterPtr->nextPtr;
                free(delPtr);
                free(delnextPtr);
            }
            else if((beforePtr->data == 'L')&&(afterPtr->data == 'S'))
            {
                delPtr = middlePtr;
                delnextPtr = afterPtr;
                beforePtr->data = 'R';
                beforePtr->nextPtr = afterPtr->nextPtr;
                free(delPtr);
                free(delnextPtr);
            }
            else if((beforePtr->data == 'L')&&(afterPtr->data == 'R'))
            {
                delPtr = middlePtr;
                delnextPtr = afterPtr;
                beforePtr->data = 'U';
                beforePtr->nextPtr = afterPtr->nextPtr;
                free(delPtr);
                free(delnextPtr);
            }
            beforePtr = *startPtr;
            middlePtr = beforePtr->nextPtr;
            if(middlePtr != NULL)
            {
                afterPtr = middlePtr->nextPtr;
            }
            else
            {
                afterPtr = NULL;
            }
        }
        else
        {
            beforePtr = beforePtr->nextPtr;
            middlePtr = middlePtr->nextPtr;
            if(middlePtr != NULL)
            {
                afterPtr = middlePtr->nextPtr;
            }
            else
            {
                afterPtr = NULL;
            }
        }
    }
}
