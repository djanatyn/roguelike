#include <ncurses.h>
int x = 2;
int y = 2;

void player_walk(dir)	// now includes collision check!
{
    switch(dir)
    {  
        case 106:		// down
            if(y < 21 && y >= 2)
			{
				y = y + 1;
			}
            break;
        case 107:		// up
            if(y <= 21  && y > 2)
			{
				y = y - 1;
			}
            break;
        case 104:		// left
            if(x <= 77 && x > 2)
			{
				x = x - 1;
			}
            break;
        case 108:		// right
            if(x < 77 && x >= 2)
			{
				x = x + 1;
			}
            break;
    }
}

int main()
{
    char ch;
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

