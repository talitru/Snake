#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ROWS 25
#define COLS 75
#define SIGN '@'
#define MAXSPEED 0.1
#define DROPSPEED 0.03


// terminal escape codes/ANSI escape codes (or ANSI escape sequences)
// "\x1B" is the escape character that tells your terminal that what comes next is not meant to be printed on the screen,
// but rather a command to the terminal (or most likely terminal emulatoion).

// Turn escape codes ON.
void init(void);

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y);

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds.
void sleep(float secs);

typedef struct Snake
{
    int x, y;
    char data;
    struct Snake* next;
}Snake;

void printBoard();

void printlist(Snake* head);

void Thegame(Snake* head);

void insertNodeToTail(Snake* head, Snake* newTail);

Snake* createNewNode(int x, int y, Snake* next);

void freeList(Snake* head);

bool IsgameOver(Snake* head);

void ChangeRestSnake(Snake* head);

int main()
{
    int i;
    init();
    printBoard();
    Snake* head = (Snake*)malloc(sizeof(Snake));
    head->next = NULL;
    head->data = SIGN;
    head->x = ROWS / 2;
    head->y = COLS / 2;
    gotoxy(head->x, head->y);
    printlist(head);
    Thegame(head);
    gotoxy(ROWS / 2, COLS / 2);
    printf("GAME OVER!");
}

void printBoard()
{
    int i,j;
    for (i = 0; i < ROWS;i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if ((i == 0)||(i==ROWS-1)||(j == 0) || (j == COLS - 1))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void Thegame(Snake* head)
{
    char c = 'd', prevC = 'd';
    int row = ROWS / 2, col = COLS / 2, count = 0;
    int tempx, tempy;
    float speed = 1;
    Snake* tail = NULL;
    while (IsgameOver(head)==false)
    {
        count++;
        if (count == 5)
        {
            if (speed > MAXSPEED)
            {
                speed = speed - DROPSPEED;
            }
            count = 0;
            tail = createNewNode(head->x, head->y, NULL);
            insertNodeToTail(head, tail);
        }
        gotoxy(head->x, head->y);
        printlist(head);
        sleep(speed);
        if (_kbhit())
        {
            c = _getch();
        }
        if (c != 'd' && c != 'a' && c != 'w' && c != 's')
        {
            c = prevC;
        }


        switch (c)
        {
            case 'd':
                /*tempx = head->x;
                tempy=(head->y)+1;*/
                gotoxy(head->x, head->y);
                printf(" ");
                head->y++;
                break;
            case 'a':
                /*tempx = head->x;
                tempy=(head->y)-1;*/
                gotoxy(head->x, head->y);
                printf(" ");
                head->y--;
                break;
            case 'w':
                /*tempx=(head->x)-1;
                tempy = head->y;*/
                gotoxy(head->x, head->y);
                printf(" ");
                head->x--;
                break;
            case 's':
                /*tempx=(head->x)+1;
                tempy = head->y;*/
                gotoxy(head->x, head->y);
                printf(" ");
                head->x++;
                break;
        }
        prevC = c;
        /*ChangeRestSnake(head)*/
        /*head->x = tempx;
        head->y = tempy;*/
    }
}
void printlist(Snake* head)
{
    Snake* current = head;

    while (current != NULL)
    {
        printf("%c", current->data);
        current = current -> next;
    }

}
//This function recieves two numbers (x,y) and a node
//And creates a new node then returns it
Snake* createNewNode(int x, int y, Snake* next)
{
    Snake* node = (Snake*)malloc(sizeof(Snake));

    node->x = x;
    node->y = y;
    node->data = SIGN;
    node->next = next;

    return node;
}

//This function recieves the head address of the list and a new node
//And inserts the new node at the end of the list
void insertNodeToTail(Snake* head, Snake* newTail)
{
    Snake* current = head;

    while (current->next != NULL)
    {
    current = current->next;
    }
    current->next = newTail;
}

void freeList(Snake* head)
{
    //This function recieves am adreess start of a list frees the list memory

    Snake* next;

    while (head != NULL)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

//This function recieves a head of a list
//And changes all the data of every node to the previous node data
void ChangeRestSnake(Snake* head)
{
    if (head->next == NULL)
    {
        head = NULL;
    }
    else
    {
        ChangeRestSnake(head->next);
        head->next->x = head->x;
        head->next->y = head->y;
    }
}

//This function recieves a snake head
//And returns "true" if the gamer lost by hitting himself or hitting the board
//"false" if otherwise
bool IsgameOver(Snake* head)
{
    if (head->x == 0 || head->x == ROWS - 1 || head->y == 0 || head->y == COLS - 1)
    {
        return true;
    }


    int tempx = head->x;
    int tempy = head->y;
    head = head->next;

    while (head != NULL)
    {
        if (tempx == head->x && tempy == head->y)
        return true;
        else
        head = head->next;
    }

    return false;
}

// Turn escape codes ON.
void init(void)
{
    system("cls");
}

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y)
{
    printf("\x1b[%d;%df", x, y);
}

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds.
void sleep(float secs)
{
    clock_t clocks_start = clock();

    while (clock() - clocks_start < secs*CLOCKS_PER_SEC);
}