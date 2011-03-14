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
	int message_code = 0;
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    while(true)
    {  
        mvprintw(y,x,"@");
		switch(message_code)
		{
			case 0:
		        mvprintw(23,0,"Ouch!");
				break;
			case 1:
				mvprintw(23,0,"Steps: %i",steps);
				break;
		}
        move(y,x);
        refresh();
        ch = getch();
        clear();
		if(player_walk(ch) == 0)
		{
			message_code = 1;
			steps = steps + 1;		// this means the player walked successfully
    	}
		else
		{
			message_code = 0;
		}
	}
    return 0;
}
