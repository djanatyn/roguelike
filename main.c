#include <ncurses.h>
int x = 0;
int y = 0;

void player_walk(dir)
{
    switch(dir)
    {  
        case 106:
            y = y + 1;
            break;
        case 107:
            y = y - 1;
            break;
        case 104:
            x = x - 1;
            break;
        case 108:
            x = x + 1;
            break;
    }
}

int main()
{
    int ch;
    int steps = 0;
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    while(true)
    {  
        mvprintw(y,x,"@");
        mvprintw(23,0,"Steps: %i",steps);
        move(y,x);
        refresh();
        ch = getch();
        clear();
        player_walk(ch);
        steps = steps + 1;
    }

    return 0;
}

