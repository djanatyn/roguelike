#include <ncurses.h>
int x = 2;
int y = 2;

int player_walk(dir)	// now includes collision check!
{
	int error = 1;
    switch(dir)
    {  
        case 106:		// down
            if(y < 21 && y >= 2)
			{
				y = y + 1;
				error = 0;
			}
            break;
        case 107:		// up
            if(y <= 21  && y > 2)
			{
				y = y - 1;
				error = 0;
			}
            break;
        case 104:		// left
            if(x <= 77 && x > 2)
			{
				x = x - 1;
				error = 0;
			}
            break;
        case 108:		// right
            if(x < 77 && x >= 2)
			{
				x = x + 1;
				error = 0;
			}
            break;
    }
	return error;
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
        if(player_walk(ch) == 0)
		{
			steps = steps + 1;
		}
    }

    return 0;
}

