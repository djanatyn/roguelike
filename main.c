// message handler codes:
// 1 - player successfully moves, and the step is incremented
// 2 - player bumped into a wall
// 3 - player found gold (not implemented yet)
// 4 - player hit a monster (definitely not implemented yet)

#include <ncurses.h>
#include <time.h>

#define DOWN 106
#define UP 107
#define LEFT 104
#define RIGHT 108

#define LENGTH 80
#define HEIGHT 22


int x = 0;
int y = 0;
int steps = 0;
int message_code = 0;

void player_display()
{
    mvprintw(y,x,"@");
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
            if(y < HEIGHT && y >= 0)    // error codes:
            {                           // 0 - no error, ran successfully
                y = y + 1;              // 1 - wrong key entered (never entered a case)
                error = 0;              // 2 - bumped into a wall (entered a case, but didn't meet the requirements)
            }
            break;
        case UP:                        // up
            if(y <= HEIGHT  && y > 0)
            {
                y = y - 1;
                error = 0;
            }
            break;
        case LEFT:                      // left
            if(x <= LENGTH && x > 0)
            {
                x = x - 1;
                error = 0;
            }
            break;
        case RIGHT:                     // right
            if(x < LENGTH && x >= 0)
            {
                x = x + 1;
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
                mvprintw(24,0,"Steps: %i",steps);
                break;
            case 1:
                mvprintw(24,0,"Wrong key, stupid.");
                break;
            case 2:    
                mvprintw(24,0,"Ouch!");
                break;
        }
}
void floodfill(x,y,xlength,ylength)
{
    int posx = 0;
    int posy = 0;
    while(posy <= ylength)
    {
        while(posx <= xlength)
        {
            mvprintw((posy+y),(posx+x),".");
            posx = posx + 1;
        }
        posy = posy + 1;
        posx = 0;
    }
}

int main()
{
    char ch;
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    while(true)
    {  
        floodfill(0,0,LENGTH,HEIGHT);       // the playing field
        player_display();
        message_display(message_code);
        refresh();
        move(y,x);                  // moves the cursor to the player
        ch = getch();
        clear();
        if(player_walk(ch) == 0)
        {
            message_code = 1;
            steps = steps + 1;      // this means the player walked successfully
        }
        else
        {
            message_code = 0;       // this means the player bumped into a wall
        }
    }
    return 0;
}
