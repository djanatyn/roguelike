// message handler codes:
// 1 - player successfully moves, and the step is incremented
// 2 - player bumped into a wall
// 3 - player found gold (not implemented yet)
// 4 - player hit a monster (definitely not implemented yet)

#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DOWN 106
#define UP 107
#define LEFT 104
#define RIGHT 108

#define LENGTH 68
#define HEIGHT 22

#define WALL 49
#define FLOOR 50
#define DOOR 51
#define PORTAL 52

int player_x = 3;
int player_y = 3;
int gold_x = 2;
int gold_y = 2;

int score = 0;
int message_code = 0;

int dungeon_level = 0;

int map[22][78];

void load_map()
{
    FILE *fp;
    int i;

    switch(dungeon_level)
    {
        case 0:
            fp = fopen("town.map", "r");
            break;
        case 1:
            fp = fopen("dungeon.map", "r");
            break;
    }
    int posx = 0;
    int posy = 0;

    i = fgetc(fp);

    while(i != -1)
    {
        if(i != 10)
        {
            map[posy][posx] = i;
            posx = posx + 1;
        }
        else
        {
            posx = 0;
            posy = posy + 1;
        }
        i = fgetc(fp);
    }

    fclose(fp);
}


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
        case DOWN:
            if(map[(player_y + 1)][player_x] != WALL)
            {
                player_y = player_y + 1;
                error = 0;
            }
            break;
        case UP:
            if(map[(player_y - 1)][player_x] != WALL)
            {
                player_y = player_y - 1;
                error = 0;
            }
            break;
        case LEFT:
            if(map[player_y][(player_x - 1)] != WALL)
            {
                player_x = player_x - 1;
                error = 0;
            }
            break;
        case RIGHT:
            if(map[player_y][(player_x + 1)] != WALL)
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

void mapfill()
{
    int posx = 0;
    int posy = 0;
    int location;
    while(posy < HEIGHT)
    {
        while(posx < LENGTH)
        {
            location = map[posy][posx];
            switch(location)
            {
                case WALL:

                    mvprintw(posy,posx,"#");
                    break;
                case FLOOR:
                    mvprintw(posy,posx,".");
                    break;
                case DOOR:
                    mvprintw(posy,posx,"+");
                    break;
                case PORTAL:
                    mvprintw(posy,posx,">");
                    break;
            }
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
    if(map[gold_x][gold_y] == WALL)
    {
        gold_generate();
    }
}

void gold_check()
{
    if(gold_x == player_x && gold_y == player_y)
    {
        score = score + 1;
        gold_generate();
    }
}

void check_level(change_x, change_y)
{
    if(player_x == change_x && player_y == change_y)
    {
        player_x = 20;
        player_y = 10;
        dungeon_level = 1;
        load_map();
    }
}
int main()
{
    srand(time(NULL));
    char ch;
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    load_map();

    while(true)
    {
        mapfill();
        message_display(player_walk(ch));
        gold_check();
        gold_display(gold_x,gold_y);
        player_display();
        refresh();
        move(player_y,player_x);
        ch = getch();
        check_level(4,4);
        clear();
    }
    return 0;
}
