#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int score = 0;
int choose = 0;
int mapArray[10][10] = {
    { 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 2, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 }
};

void intro();
void selectGrade();
void printMap();
void printMove();
void printHowto();
void printUpdate();

void mainEasyplay();
void mainSoSoplay();
void mainNoNoplay();

void exitGame();

int main() {
    intro();
    printMap();
    return 0;
}

//Intro Select Options
void intro() {
    printf("AWESOME_MIRO\n");

    printf("1.Play Game.\n");
    printf("2.How to Play.\n");
    printf("3. Exit :( \n");
    scanf("%d", &choose);

    switch (choose) {
        case 1:
            selectGrade();
            break;
        case 2:
            printHowto();
            break;
        case 3:
            exitGame();
            break;
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
    scanf("%d", &choose);

    switch(choose) {
        case 1:
            printf("성공 1 단계");
            //mainEasyplay();
            break;
        case 2:
            printf("성공 2 단계");
            //mainSoSoplay();
            break;
        case 3:
            printf("성공 3 단계");
            //mainNoNoplay();
            break;
    }
}

//Print map
//Still demo map...
void printMap() {
    int random = 0;
    
    for (int x = 0; x <= 10; x++) {
        for (int y = 0; y <= 10; y++ ) {
            random = mapArray[x][y];
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
            } 
        }   printf("\n");
    }
}

/*
void printMove() {
    while (1) {
        
                        W(Top)
            
            A(Left)     +       D(Right)
                
                        X(Bottom)

       swtich(getchar()) {
           case 'w':
                printf('')
       }
    }
}
*/

void mainEasyplay() {

}