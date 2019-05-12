#include <stdio.h>
#include <curses.h>

int main()
{
    char c;
    initscr();
    keypad(stdscr, TRUE);
    while(1)
    {   
        c = getch();
        switch(c) {
            case 'w':
                printf("UP\n");
                break;
            case 'a':
                printf("LEFT\n");
                break;
            case 'd':
                printf("RIGHT\n");
                break;
            case 's':
                printf("DOWN\n");
                break;
        }
    }
    
}