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

//SoSo Play Mode Map
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

int hardMap[30][30] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 3, 2, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void intro();
void selectGrade();
void escapeGame();

void printMap();
void printMove();
void printHowto();
void printUpdate();
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
                escapeGame();
                break;
        }
    }
    //return 0;
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
            //printf("성공 1 단계\n");
            mainEasyplay();
            break;
        case 2:
            //printf("성공 2 단계\n");
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
                    printf("__");
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
    printf(" move_x == %d\tmove_y == %d\n", move_y, move_x);
}


void printHardMap() {
    int random = 0;
    for (int x = 0; x < 30; x++) {
        for (int y = 0; y < 30; y++) {
            random = hardMap[x][y];
            
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

            if (hardMap[move_y][move_x] == 0) {
                crash();
                exit(1);
            }
            
            if (hardMap[move_x][move_y] == 2) {
                ending();
            }
            
            if (x == move_y && y == move_x) {
                normalMap[x][y] = 3;
            }
            
            
        }   printf("\n");
    }
}

//In Mac cannot use Windows.h system("cls");
//So I decide use too many add new lines
//Actually this way is not good :(
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
    
    //break;
}

void escapeGame() {
    exit(1);
}

void crash() {
    printf("move_x == %d\nmove_y == %d\n", move_x, move_y);
    printf("Crash The Wall or Over the wall\n");
}

void ending() {
    score = 1;
    printCleaning();
    
    printf("\t\t!GAME!OVER!\n");
    exit(1);
}
