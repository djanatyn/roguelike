// message handler codes:
// 1 - player successfully moves, and the step is incremented
// 2 - player bumped into a wall
// 3 - player found gold (not implemented yet)
// 4 - player hit a monster (definitely not implemented yet)

//  $$$$$$$$$$$$$$$$$$
//  $$$$$$$   $$$$$$$$
//  $$$$$$$ @ $$lo$er$
//  $$$$$$$   $$$$$$$$
//  $$$$$$$$$$$$$$$$$$
//  $$$$$$$$$$$$$$$$$$


#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DOWN 106
#define UP 107
#define LEFT 104
#define RIGHT 108

#define LENGTH 79
#define HEIGHT 21


int player_x = 0;
int player_y = 0;
int gold_x = 5;
int gold_y = 5;

int score = 0;
int message_code = 0;

void player_display()
{
    mvprintw(player_y,player_x,"@");
}

int player_walk(dir)                    // now includes collision check!
{
    int error = 2;                      // set as an error by default; if it runs successfully, change it
    switch(dir)
    {
        default:
            error = 1;
            break;
        case DOWN:                      // down
            if(player_y < HEIGHT && player_y >= 0)    // error codes:
            {                           // 0 - no error, ran successfully
                player_y = player_y + 1;              // 1 - wrong key entered (never entered a case)
                error = 0;              // 2 - bumped into a wall (entered a case, but didn't meet the requirements)
            }
            break;
        case UP:                        // up
            if(player_y <= HEIGHT  && player_y > 0)
            {
                player_y = player_y - 1;
                error = 0;
            }
            break;
        case LEFT:                      // left
            if(player_x <= LENGTH && player_x > 0)
            {
                player_x = player_x - 1;
                error = 0;
            }
            break;
        case RIGHT:                     // right
            if(player_x < LENGTH && player_x >= 0)
            {
                player_x = player_x + 1;
                error = 0;
            }
            break;
    }
    return error;
}

void message_display(code)
{
    switch(code)
        {   
            case 0:
                mvprintw(23,0,"Score: %i",score);
                break;
            case 1:
                mvprintw(23,0,"Wrong key, stupid.");
                break;
            case 2:    
                mvprintw(23,0,"Ouch!");
                break;
        }
}

void floodfill(xlength,ylength)
{
    int posx = 0;
    int posy = 0;
    while(posy <= ylength)
    {
        while(posx <= xlength)
        {
            mvprintw((posy),(posx),".");
            posx = posx + 1;
        }
        posy = posy + 1;
        posx = 0;
    }
}

void gold_display(x,y)
{
    mvprintw(y,x,"$");
}

void gold_generate()
{
    gold_x = rand()%LENGTH;
    gold_y = rand()%HEIGHT;
}

void gold_check()
{
    if(gold_x == player_x && gold_y == player_y)
    {
        score = score + 1;
        gold_generate();
    }
}

int main()
{
    srand(time(NULL));
    char ch;
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    while(true)
    {  
        floodfill(LENGTH,HEIGHT);       // the playing field
        message_display(player_walk(ch));
        gold_check();
        gold_display(gold_x,gold_y);
        player_display();
        refresh();
        move(player_y,player_x);                          // moves the cursor to the player
        ch = getch();
        clear();
        
    }
    return 0;
}
