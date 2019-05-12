#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>

int score = 0;
int choose = 0;

int move_x = 1;
int move_y = 1;

int changeMap[100][100] = { '\n' };

//Easy Play Mode Map
int easyMap[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 1, 1, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//SoSo Play Mode Map
int normalMap[20][20] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
    {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void intro();
void selectGrade();
void escapeGame();

void printMap();
void printMove();
void printHowto();
void printUpdate();
void printCleaning();

void mainEasyplay();
void mainNormalplay();
void mainNoNoplay();

int main() {
    intro();
    return 0;
}

//Intro Select Options
void intro() {
    while (1) {
    printf("AWESOME_MIRO\n");

    printf("1.Play Game.\n");
    printf("2.How to Play.\n");
    printf("3. Exit :( \n");
    
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
                escapeGame();
                break;
        }
    }
    //return 0;
}

//Choose Easy, normal, hard...
//When it thourgh this code, then player have to go main play game Screen
void selectGrade() {
    printf("Choose NenYeeDo\n");

    printf("1. EASY\n");
    printf("2. So So...\n");
    printf("3. no no\n");

    printf(">>> ");
    scanf("%d", &choose);

    switch(choose) {
        case 1:
            //printf("성공 1 단계\n");
            mainEasyplay();
            break;
        case 2:
            //printf("성공 2 단계\n");
            mainNormalplay();
            break;
        case 3:
            //printf("성공 3 단계\n");
            //mainNoNoplay();
            break;
    }
}

//This fn is only print Easy Map
void printEasyMap() {
    int random = 0;
    int previous_x = 0;
    int previous_y = 0;

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            random = easyMap[x][y];
            
            //if (easyMap[x][y] == easyMap[move_y][move_x]) {
            //    printf("YOU CAN'T MOVE THERE!!!\n");
            //    continue;
            //}

            if (easyMap[move_y][move_x] == 0) {
                printf("You crash to the wall X(\nTry Again...\n\n\n");
                exit(1);
            }

            if (x == move_y && y == move_x) {
                //previousValue = easyMap[x][y];
                easyMap[x][y] = 3;
                //break;
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
            
            
            //if (easyMap[move_y][move_x] == easyMap[8][8]) {
            if (move_y == 7 && move_x == 7) {
                score = 1;
                printf("NewScore!!!");
                break;
            }

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

            if (easyMap[move_y][move_x] == 0) {
                printf("You crash to the wall X(\nTry Again...\n\n\n");
                exit(1);
            }

            if (x == move_y && y == move_x) {
                previousValue = normalMap[x][y];
                normalMap[x][y] = 3;
                //break;
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

//In Mac cannot use Windows.h system("cls"); 
//So I decide use too many add new lines
//Actually this way is not good :(
void printCleaning() {
    for (int i = 0; i <= 100; i++) {
        printf("\n");
    }
}

void mainEasyplay() {
    while (1) {
        printCleaning();
        printEasyMap();
        printMove();

        if (score == 1) {
            break;
        }
    }
}

void mainNormalplay() {
    while (1 != score) {
        printCleaning();
        printNormalMap();
        printMove();     
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
   }
     
}    

void printHowto() {
    printf("Move :\n");
    printf("\t\t\'W\' <== UP\n");
    printf("\t\'A\' <== LEFT\t\t\'D\' <== RIGHT \n");
    printf("\t\t\'S\' <== DOWN \n\n");
    //break;
}

void escapeGame() {
    exit(1);
}

