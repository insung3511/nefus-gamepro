#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int score = 0;
int choose = 0;

int move_x = 1;
int move_y = 1;

//Easy Play Map
int easyMap[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//Normal Play Map
int normalMap[20][20] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 3, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//Hard Play Map
int hardMap[30][30] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 3, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 2, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//Here is Function Part 
void intro();                      
void selectGrade();
void ready();
void printMap();
void printMove();
void printHowto();
void printCleaning();
void printEasyMap();
void printNormalMap();
void printHardMap();
void mainEasyplay();
void mainNormalplay();
void mainHardplay();
void ending();
void crash();

int main() {
    intro();
    return 0;
}

//Intro Select Options
void intro() {
    while (1) {
        printf("====+====AWESOME_MIRO====+====\n");
        
        printf("\t1.Play Game.\n");
        printf("\t2.How to Play.\n");
        printf("\t3. Exit :( \n");
        
        printf(">>> ");
        scanf("%d", &choose);
        
        switch (choose) {
            case 1:
                selectGrade();
                break;
            case 2:
                printHowto();
                break;
            case 3:
                exit(1);
                break;
        }
    }
}

//Choose Easy, normal, hard...
//When it thourgh this code, then player have to go main play game Screen
void selectGrade() {
    printf("====+====Choose NanYeeDo====+====\n");
    
    printf("\t1. EASY\n");
    printf("\t2. So So...\n");
    printf("\t3. no no\n");
    
    printf(">>> ");
    scanf("%d", &choose);
    
    switch(choose) {
        case 1:
            mainEasyplay();
            break;
        case 2:
            mainNormalplay();
            break;
        case 3:
            mainHardplay();
            break;
    }
}

//This fn is only print Easy Map
void printEasyMap() {
    int random = 0;
    int previousValue = 0;
    
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            random = easyMap[x][y];
            previousValue = easyMap[x][y];
            
            if (easyMap[move_y][move_x] == 0) {
                crash();
                exit(1);
            }
            
            if (easyMap[move_x][move_y] == 2) {
                ending();
            }
            
            if (x == move_y && y == move_x) {
                easyMap[x][y] = 3;
            }
            
            switch(random) {
                case 0:
                    printf(" *");
                    break;
                case 1:
                    printf("  ");
                    break;
                case 2:
                    printf(" $");
                    break;
                case 3:
                    printf(" @");
                    easyMap[move_y][move_x] = 1;
                    break;
            }
        }   printf("\n");
    }
}



void printNormalMap() {
    int random = 0;
    int previousValue = 0;
    
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            random = normalMap[x][y];
            
            if (normalMap[move_y][move_x] == 0) {
                crash();
                exit(1);
            }
            
            if (move_x == 18 && move_y == 18) {
                ending();
            }
            
            if (x == move_y && y == move_x) {
                normalMap[x][y] = 3;
            }
            
            switch(random) {
                case 0:
                    printf(" *");
                    break;
                case 1:
                    printf("  ");
                    break;
                case 2:
                    printf(" $");
                    break;
                case 3:
                    printf(" @");
                    normalMap[move_y][move_x] = 1;
                    break;
            }
        }   printf("\n");
    }
}


void printHardMap() {
    int random = 0;
    for (int x = 0; x < 30; x++) {
        for (int y = 0; y < 30; y++) {
            random = hardMap[x][y];
        
            if (hardMap[move_y][move_x] == 0) {
                crash();
                exit(1);
            }
            
            if (hardMap[move_y][move_x] == 2) {
                ending();
            }
            
            if (x == move_y && y == move_x) {
                hardMap[x][y] = 3;
            }

            switch(random) {
                case 0:
                    printf(" *");
                    break;
                case 1:
                    printf("  ");
                    break;
                case 2:
                    printf(" $");
                    break;
                case 3:
                    printf(" @");
                    hardMap[move_y][move_x] = 1;
                    break;
            }
            
        }   printf("\n");
    }
}

void printCleaning() {
    int looping = 0;
    while (1) {
        printf("\n");
        looping++;
        
        if (looping == 100) break;
    }
}

void mainEasyplay() {
    for (int i = 0; i >= score; i++) {
        printCleaning();
        printEasyMap();
        printMove();
    }
}

void mainNormalplay() {
    ready();
    while (1) {
        printCleaning();
        printNormalMap();
        printMove();
        
        if (score == 1) {
            break;
        }
    }
}

void mainHardplay() {
    ready();
    while (1) {
        printCleaning();
        printHardMap();
        printMove();
        
        if (score == 1) {
            break;
        }
    }
}

void printMove() {
    /*
        W
     A       D
        S
     */
    int looping = 0;
    char keyValue = ' ';
    printf(" >>> ");
    scanf("%c", &keyValue);
    
    switch(keyValue) {
        case 'w':
            --move_y;
            break;
        case 'a':
            --move_x;
            break;
        case 'd':
            ++move_x;
            break;
        case 's':
            ++move_y;
            break;
        case 'q':
            exit(1);
            break;
        default:
            keyValue = 'x';
            break;

        case 'c':
            printf("move_x >>> ");
            scanf("%d", &move_x);

            printf("move_y >>> ");
            scanf("%d", &move_y);
    }
    
}

void printHowto() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Move :\n");
    printf("\t\t\t\'W\' <== UP\n");
    printf("\t\'A\' <== LEFT\t\t\t\'D\' <== RIGHT \n");
    printf("\t\t\t\'S\' <== DOWN \n\n\n\n");
    printf("\t@ <== That is you.\n\t$ <== And you have to go here.\n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void crash() {
    printf("You Crash to wall...\nTry Again....or not\n");
}

void ending() {
    score = 1;
    printCleaning();
    
    printf("\t\t!GAME!OVER!\n\n");
    exit(1);
}

void ready() {
    getch();
}
