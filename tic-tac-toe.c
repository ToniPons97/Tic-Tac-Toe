#include <ncurses.h>
#include <stdbool.h>

void drawBoard(int dim);
void populate(char matrix[3][3], int size);
void drawX(int x, int y);
void drawO(int x, int y);
void userInput (char matrix[3][3], int size, int *numOfPlays, int *tempX, int *tempY, char *lastShapePtr, char name1[], char name2[]);
bool checkWin(char matrix[3][3], int size, int lastX, int lastY, char lastShape);
void presentationScreen(void);
void setPlayerName(char name1[], char name2[]);
void displayWinner(bool win, int plays, char name1[20], char name2[20]);

#define SIZE 3
#define MAXPLAYS 9
#define NAMEBUFFER 20

int main(void) {
    int currNumOfPlays = 0;
    int *currNumOfPlaysPtr = &currNumOfPlays;
    int lastX, lastY;
    int *lastXPtr = &lastX;
    int *lastYPtr = &lastY;

    char player1[NAMEBUFFER];
    char player2[NAMEBUFFER];
    char lastShape = 'E';
    char *lastShapePtr = &lastShape;
    
    bool win = false;
    
    char gameMatrix[SIZE][SIZE] = {
        {'E', 'E', 'E'},
        {'E', 'E', 'E'},
        {'E', 'E', 'E'}
    };

    initscr();
    presentationScreen();
    setPlayerName(player1, player2);

    drawBoard(15);

    while (currNumOfPlays < MAXPLAYS && !win)
    {
        populate(gameMatrix, SIZE);
        
        if (currNumOfPlays > 4)
            win = checkWin(gameMatrix, SIZE, lastX, lastY, lastShape);
        if (!win)
            userInput(gameMatrix, SIZE, currNumOfPlaysPtr, lastXPtr, lastYPtr, lastShapePtr, player1, player2);
        refresh();
    }

    displayWinner(win, currNumOfPlays, player1, player2);

    endwin();
    return 0;
}

void populate(char matrix[3][3], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 'X')
                drawX(i, j);
            else if (matrix[i][j] == 'O')
                drawO(i, j);
        }
    }
}

void drawBoard(int dim) {
    for (int i = 0; i <= dim; i++) {
        for (int j = 0; j <= dim; j++) {
            if (i == 0 || i == 5 || i == 10 || i == dim)
                printw("# ");
            else if (j == 0 || j == 5 || j == 10 || j == dim)
                printw("# ");
            else
                printw("  ");
        }
        printw("\n");
    }
}

void drawX(int x, int y) {
    if (x == 0 && y == 0) {
        for (int i = 1; i < 5; i++) {
        for (int j = 2; j < 9; j += 2) {
            move(i, j);

            if (i * 2 == j 
            || (i == 1 && j == 8) 
            || (i == 2 && j == 6)
            || (i == 3 && j == 4)
            || (i == 4 && j == 2))
                printw("*");
            }
        }
    } else if (x == 0 && y == 1) {
        for (int i = 1; i < 5; i++) {
            for (int j = 12; j < 19; j += 2) {
                move(i, j);

                if (((i == 1 || i == 4) && j == 12)
                || ((i == 2 || i == 3) && (j == 14 || j == 16))
                || ((i == 1 || i == 4) && (j == 12 || j == 18)))
                    printw("*");
            }
        }
    } else if (x == 0 && y == 2) {
        for (int i = 1; i < 5; i++) {
            for (int j = 22; j < 29; j += 2) {
                move(i, j);

                if ((i == 1 && (j == 22 || j == 28)) 
                || ((i == 2 || i == 3) && (j == 24 || j == 26))
                || (i == 4 && (j == 22 || j == 28)))
                    printw("*");

            }
        }
    } else if (x == 1 && y == 0) {
        for (int i = 6; i < 10; i++) {
            for (int j = 2; j < 9; j += 2) {
                move(i, j);

                if ((i == 6 && (j == 2 || j == 8))
                || ((i == 7 || i == 8) && (j == 4 || j == 6))
                || (i == 9 && (j == 2 || j == 8)))
                    printw("*");
                }
            }
    } else if (x == 1 && y == 1) {
        for (int i = 6; i < 10; i++) {
            for (int j = 12; j < 19; j += 2) {
                move(i, j);

                if ((i == 6 && (j == 12 || j == 18))
                || ((i == 7 || i == 8) && (j == 14 || j == 16))
                || (i == 9 && (j == 12 || j == 18)))
                    printw("*");
            }
        }
    } else if (x == 1 && y == 2) {
        move(6, 22);
            
        for (int i = 6; i < 10; i++) {
            for (int j = 22; j < 29; j += 2) {
                move(i, j);

                if ((i == 6 && (j == 22 || j == 28))
                || ((i == 7 || i == 8) && (j == 24 || j == 26))
                || (i == 9 && (j == 22 || j == 28)))
                    printw("*");
            }
        }
    } else if (x == 2 && y == 0) {         
        for (int i = 11; i < 15; i++) {
            for (int j = 2; j < 9; j += 2) {
                move(i, j);

                if ((i == 11 && (j == 2 || j == 8))
                || ((i == 12 || i == 13) && (j == 4 || j == 6))
                || (i == 14 && (j == 2 || j == 8)))
                    printw("*");
            }
        }
    } else if (x == 2 && y == 1) {
        for (int i = 11; i < 15; i++) {
            for (int j = 12; j < 19; j += 2) {
                move(i, j);

                if ((i == 11 && (j == 12 || j == 18)) 
                || ((i == 12 || i == 13) && (j == 14 || j == 16))
                || (i == 14 && (j == 12 || j == 18)))
                    printw("*");
            }
        }
    } else if (x == 2 && y == 2) {
        for (int i = 11; i < 15; i++) {
            for (int j = 22; j < 29; j += 2) {
                move(i, j);

                if ((i == 11 && (j == 22 || j == 28))
                || ((i == 12 || i == 13) && (j == 24 || j == 26))
                || (i == 14 && (j == 22 || j == 28)))
                    printw("*");
            }
        }
    }
}

void drawO(int x, int y) {
    if (x == 0 && y == 0) {
        for (int i = 1; i < 5; i++) {
            for (int j = 2; j < 9; j += 2) {
                move(i, j);

                if ((i == 1 && (j == 4 || j == 6))
                || ((i == 2 || i == 3) && (j == 2 || j == 8))
                || (i == 4 && (j == 4 || j == 6)))
                    printw("*");
            }
        }
    } else if (x == 0 && y == 1) {
        for (int i = 1; i < 5; i++) {
            for (int j = 12; j < 19; j += 2) {
                move(i, j);

                if ((i == 1 && (j == 14 || j == 16))
                || ((i == 2 || i == 3) && (j == 12 || j == 18))
                || (i == 4 && (j == 14 || j == 16)))
                    printw("*");
            }
        }
    } else if (x == 0 && y == 2) {
        for (int i = 1; i < 5; i++) {
            for (int j = 22; j < 29; j += 2) {
                move(i , j);

                if ((i == 1 && (j == 24 || j == 26))
                || ((i == 2 || i == 3) && (j == 22 || j == 28))
                || (i == 4 && (j == 24 || j == 26)))
                    printw("*");
            }
        }
    } else if (x == 1 && y == 0) {
        for (int i = 6; i < 10; i++) {
            for (int j = 2; j < 9; j += 2) {
                move(i, j);

                if ((i == 6 && (j == 4 || j == 6))
                || ((i == 7 || i == 8) && (j == 2 || j == 8))
                || (i == 9 && (j == 4 || j == 6)))
                    printw("*");
            }
        }
    } else if (x == 1 && y == 1) {
        for (int i = 6; i < 10; i++) {
            for (int j = 12; j < 19; j += 2) {
                move(i, j);

                if ((i == 6 && (j == 14 || j == 16))
                || ((i == 7 || i == 8) && (j == 12 || j == 18))
                || (i == 9 && (j == 14 || j == 16)))
                    printw("*");
            }
        }
    } else if (x == 1 && y == 2) {
        for (int i = 6; i < 10; i++) {
            for (int j = 22; j < 29; j += 2) {
                move(i, j);

                    if ((i == 6 && (j == 24 || j == 26))
                    || ((i == 7 || i == 8) && (j == 22 || j == 28))
                    || (i == 9 && (j == 24 || j == 26)))
                        printw("*");
            }
        }
    } else if (x == 2 && y == 0) {
        for (int i = 11; i < 15; i++) {
            for (int j = 2; j < 9; j += 2) {
                move(i, j);

                if ((i == 11 && (j == 4 || j == 6))
                || ((i == 12 || i == 13) && (j == 2 || j == 8))
                || (i == 14 && (j == 4 || j == 6)))
                    printw("*");
            }
        }
    } else if (x == 2 && y == 1) {
        for (int i = 11; i < 15; i++) {
            for (int j = 12; j < 19; j += 2) {
                move(i, j);

                if ((i == 11 && (j == 14 || j == 16))
                || ((i == 12 || i == 13) && (j == 12 || j == 18))
                || (i == 14 && (j == 14 || j == 16)))
                    printw("*");
            }
        }
    } else if (x == 2 && y == 2) {
        for (int i = 11; i < 15; i++) {
            for (int j = 22; j < 29; j += 2) {
                move(i, j);

                if ((i == 11 && (j == 24 || j == 26))
                || ((i == 12 || i == 13) && (j == 22 || j == 28))
                || (i == 14 && (j == 24 || j == 26)))
                    printw("*");
            }
        }
    }
}

void userInput (char matrix[3][3], int size, int *numOfPlays, int *tempX, int *tempY, char *lastShapePtr, char name1[], char name2[]) {
    int x = 3, y = 3;
    char shape = 'E';
    int curX = 17, curY = 0;

    do {
        if (*numOfPlays % 2 == 0) {
            move(curX, curY);
            clrtoeol();
            mvprintw(curX, curY, "%s > ", name1);
        }
        else {
            move(curX, curY);
            clrtoeol();
            mvprintw(curX, curY, "%s > ", name2);
        }

        scanw("%d %d %c", &x, &y, &shape);
        if (x < 0 || x > 2 || y < 0 || y > 2) {
            move(curX, curY);
            clrtoeol();
            printw("Invalid X and Y coordinates (Valid coordinate values: 0, 1 and 2). Press Enter.");
            getch();
            clrtoeol();
        } else if (shape != 'X' && shape != 'O') {
            move(curX, curY);
            clrtoeol();
            printw("Invalid shape (Valid shapes: X and O). Press Enter.");
            getch();
            clrtoeol();
        } else if (shape == *lastShapePtr) {
            move(curX, curY);
            clrtoeol();
            printw("This shape is taken by your opponent.");
            getch();
            clrtoeol();
        } else if (matrix[x][y] != 'E') {
            move(curX, curY);
            clrtoeol();
            printw("Coordinate (%d, %d) is already taken. Press Enter.", x, y);
            getch();
            clrtoeol();
        }
        refresh();
    } while ((matrix[x][y] != 'E') || (shape == *lastShapePtr) ||
     ((x < 0 || x > 2 || y < 0 || y > 2 || (shape != 'X' && shape != 'O'))));
    
    matrix[x][y] = shape;
    
    *numOfPlays += 1;
    *tempX = x;
    *tempY = y;
    *lastShapePtr = shape;

    clrtoeol();
}

bool checkWin(char matrix[3][3], int size, int lastX, int lastY, char lastShape) {
    int numberOfShapes = 0;

    if (lastX == 0 && lastY == 0) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping diagonally.
        for (int i = 0; i < size; i++) {
            if (matrix[i][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

    } else if (lastX == 0 && lastY == 2) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping diagonally
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY - i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

    }  else if (lastX == 2 && lastY == 0) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;
        
        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping diagonally.
        for (int i = 0; i < size; i++) {
            if (matrix[2 - i][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else 
            numberOfShapes = 0;

    } else if (lastX == 2 && lastY == 2) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping diagonally.
        for (int i = 0; i < size; i++) {
            if (matrix[i][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;
    } else if (lastX == 1 && lastY == 0) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;
    } else if (lastX == 0 && lastY == 1) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else 
            numberOfShapes = 0;
    } else if (lastX == 1 && lastY == 2) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else 
            numberOfShapes = 0;

    } else if (lastX == 2 && lastY == 1) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

    } else if (lastX == 1 && lastY == 1) {
        //Looping through y axis.
        for (int i = 0; i < size; i++) {
            if (matrix[lastX][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through x axis.
        for (int i = 0; i < size; i++) {
            if (matrix[i][lastY] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;

        //Looping through diagonal 1.
        for (int i = 0; i < size; i++) {
            if (matrix[i][i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else 
            numberOfShapes = 0;

        //Looping through diagonal 2.
        for (int i = 0; i < size; i++) {
            if (matrix[i][2 - i] == lastShape)
                numberOfShapes++;
        }

        if (numberOfShapes == 3)
            return true;
        else
            numberOfShapes = 0;
    }
    return false;
}

void presentationScreen(void) {
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    int y = max_y / 2;
    int x = max_x / 2;

    mvprintw(x + 10, y + 10, "PvP Tic-Tac-Toe!");
    mvprintw(x + 10, y + 10, "Press Enter to play!");
    getch();
    move(5, 40);
    clrtoeol();
    move(7, 39);
    clrtoeol();
    move(0, 0);
}

void setPlayerName(char name1[], char name2[]) {
    mvprintw(0, 0, "Enter name for player1: ");
    scanw("%s", name1);
    mvprintw(1, 0, "Enter name for player2: ");
    scanw("%s", name2);
    move(0, 0);
    clrtoeol();
    move(1, 0);
    clrtoeol();
    move(0, 0);
    mvprintw(0, 0, "%s vs %s!!!!", name1, name2);
    mvprintw(1, 0, "Press Enter");
    getch();
    move(0, 0);
    clrtoeol();
    move(1, 0);
    clrtoeol();
    move(0, 0);
}

void displayWinner(bool win, int plays, char name1[20], char name2[20]) {
    move(17, 0);
    clrtoeol();

    if (win) {
        if (plays % 2 != 0)
            printw("%s wins!", name1);
        else 
            printw("%s wins!", name2);
    } else {
        printw("It's a draw!");
    }
    getch();
}
