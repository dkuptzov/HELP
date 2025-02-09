#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25

void input_matrix(char **matr, int *n) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (scanf("%s",&matr[i][j])!=1) {
                *n=-1;
                return;
            }
        }
    }
}

void output_matrix(char **matr) {
    clear();
    for (int i=0;i<WIDTH+3;i++) {
        printw("_");
    }
    printw("\n");
    for (int i = 0; i < HEIGHT; i++) {
        printw("| ");
        for (int j = 0; j < WIDTH; j++) {
            printw("%c", (matr[i][j]=='0')?' ':matr[i][j]);
        }
        printw(" |");
        if (i < HEIGHT - 1) printw("\n");
    }
    printw("\n");
    for (int i=0;i<WIDTH+3;i++) printw("¯");
    printw("\n"); 
    refresh();
}

int live_neighboor_count(char **matr, int i, int j) {
    int count = 0;

    int left = (j==0)?WIDTH-1:j-1;
    int right = (j==WIDTH-1)?0:j+1;
    int up = (i==0)?HEIGHT-1:i-1;
    int down = (i==HEIGHT-1)?0:i+1;

    count +=(matr[up][left] =='*')?1:0;
    count +=(matr[up][j] == '*')?1:0;
    count +=(matr[up][right] == '*')?1:0;
    count +=(matr[i][right] == '*')?1:0;
    count +=(matr[i][left] == '*')?1:0;
    count +=(matr[down][left] == '*')?1:0;
    count +=(matr[down][j] == '*')?1:0;
    count +=(matr[down][right] == '*')?1:0;

    return count;
}

char dot_is_live(int neighboor_count,  char state) {
    char live = '0';
    if (state == '0' && neighboor_count == 3)
        live = '*';
    else if (state == '*' && (neighboor_count == 2 || neighboor_count == 3))
        live = '*';
    else
        live = '0';
    return live;

}

void logic(char **matrix)
{
    char temp[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            int live_neigboors = live_neighboor_count(matrix, i, j);
            temp[i][j] = dot_is_live(live_neigboors, matrix[i][j]);
        }
    }

    for (int i=0;i<HEIGHT;i++) {
        for (int j=0;j<WIDTH;j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}


int main() {
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    int running = 1;
    char *matr[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        matr[i] = (char *)malloc(WIDTH * sizeof(char));
    }
    int n=1;
    input_matrix(matr, &n);
    if (n<=0){
        printf("n/a");
        return 0;
    }
    
    int c; 
    while (running) {
        output_matrix(matr);
        logic(matr);
        usleep(80000);

        c = getch();
        if (c == 'q' || c == 'Q') {
            running=0;
        }
    }
    endwin();
    printf("The game is end");
}
