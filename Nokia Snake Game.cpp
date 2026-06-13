#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <ctime>

using namespace std;
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
void hideConsoleCursor()
{
    cout << "\033[?25l";
    cout.flush();
}

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOutput, scrn);
}

void wait_before_start()
{
    gotoRowCol(20, 20);
    cout << "**=====================================**" << endl;
    gotoRowCol(21, 20);
    cout << "**=====================================**" << endl;
    gotoRowCol(25, 20);
    cout << "**            NOKIA SNAKE GAME         **    " << endl;
    gotoRowCol(28, 20);
    cout << "**=====================================**" << endl;
    gotoRowCol(29, 20);
    cout << "**=====================================**" << endl;
    color(7);
    gotoRowCol(40, 20);
    cout << "Press ENTER to start the game";
    gotoRowCol(45, 20);
    cout << "USE ARROW KEY (P1), WASD (P2), IJKL (P3)";
    color(7);

    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 13)
                break;
        }
    }

    gotoRowCol(2, 20);
    cout << "                              ";
    system("cls");
}

struct position
{
    int ri, ci;
};

struct SNAKE
{
    position* ps;
    int size;
    char sym;
    int score;
    int direction;
    char LKEY, RKEY, UKEY, DKEY;
};

bool valid_food(position& fp, SNAKE& S1, SNAKE& S2, SNAKE& S3)
{
    
    for (int i = 0; i < S1.size; i++)
    {
        if (S1.ps[i].ri == fp.ri and S1.ps[i].ci == fp.ci)
        {
            return false;
        }
    }
    for (int i = 0; i < S2.size; i++)
    {
        if (S2.ps[i].ri == fp.ri and S2.ps[i].ci == fp.ci)
        {
            return false;
        }
    }
    for (int i = 0; i < S3.size; i++)
    {
        if (S3.ps[i].ri == fp.ri and S3.ps[i].ci == fp.ci)
        {
            return false;
        }
    }
    return true;
}

void FOOD(position& fp, SNAKE& S1, SNAKE& S2, SNAKE& S3, int rows, int cols)
{
    do
    {
        fp.ri = rand() % rows;
        fp.ci = rand() % cols;
    } while (!valid_food(fp, S1, S2, S3));
}

bool snake_eatenfood(SNAKE& S, position& fp)
{
    return S.ps[0].ri == fp.ri and S.ps[0].ci == fp.ci;
}

void display_food(const position& fp, char fs = '@')
{
    gotoRowCol(fp.ri, fp.ci);
    color(12);
    cout << fs;
    color(7);
}

void score_display(int base_row, int base_col, SNAKE& S, int color_code)
{
    color(color_code);
    gotoRowCol(base_row, base_col);
    cout << "SCORE";
    gotoRowCol(base_row + 1, base_col);
    cout << S.score << "   ";
    color(7);
}

void increase_score_snake(SNAKE& S)
{
    S.score++;
    position* nps = S.ps;

    S.ps = new position[S.size + 1];

    for (int i = 0; i < S.size; i++)
        S.ps[i] = nps[i];
    S.ps[S.size] = S.ps[S.size - 1];
    S.size += 1;
}

void init(SNAKE& S, int rows, int cols, char sym, int start_ri, int start_ci)
{
    S.sym = sym;
    S.size = 3;
    S.ps = new position[S.size]{};
    S.ps[0].ri = start_ri;
    S.ps[0].ci = start_ci;
    S.ps[1].ri = start_ri;
    S.ps[1].ci = start_ci - 1;
    S.ps[2].ri = start_ri;
    S.ps[2].ci = start_ci - 2;
    S.direction = RIGHT;
    S.score = 0;
}

void DISPLAYSNAKE(const SNAKE& S, int color_start)
{
    for (int i = 0; i < S.size; i++)
    {
        gotoRowCol(S.ps[i].ri, S.ps[i].ci);
        color(color_start + i);
        cout << S.sym;
    }
    color(7);
}

void ERASESNAKE(const SNAKE& S, char sym = ' ')
{
    for (int i = 0; i < S.size; i++)
    {
        gotoRowCol(S.ps[i].ri, S.ps[i].ci);
        cout << sym;
    }
}

void MOVESNAKE(SNAKE& S, int ROWS, int COLS)
{
    for (int i = S.size - 1; i > 0; i--)
    {
        S.ps[i] = S.ps[i - 1];
    }
    switch (S.direction)
    {
    case UP:
        S.ps[0].ri--;
        if (S.ps[0].ri == -1)
            S.ps[0].ri = ROWS - 1;
        break;
    case DOWN:
        S.ps[0].ri++;
        if (S.ps[0].ri == ROWS)
            S.ps[0].ri = 0;
        break;
    case LEFT:
        S.ps[0].ci--;
        if (S.ps[0].ci == -1)
            S.ps[0].ci = COLS - 1;
        break;
    case RIGHT:
        S.ps[0].ci++;
        if (S.ps[0].ci == COLS)
            S.ps[0].ci = 0;
        break;
    }
}

bool snake_hit_itself(SNAKE& S)
{
    for (int i = 1; i < S.size; i++)
    {
        if (S.ps[0].ri == S.ps[i].ri && S.ps[0].ci == S.ps[i].ci)
            return true;
    }
    return false;
}

bool snake_hit_snake(SNAKE& S1, SNAKE& S2)
{
    for (int i = 0; i < S2.size; i++)
    {
        if (S1.ps[0].ri == S2.ps[i].ri && S1.ps[0].ci == S2.ps[i].ci)
            return true;
    }
    return false;
}

void DISPLAY_GAME_OVER(int player_num, int base_row, int base_col, SNAKE& S)
{
    color(3);
    gotoRowCol(base_row, base_col - 10);
    cout << "=======================";
    gotoRowCol(base_row + 1, base_col - 10);
    cout << "    GAME OVER - Player " << player_num << "    ";
    gotoRowCol(base_row + 2, base_col - 10);
    cout << "    SCORE: " << S.score << "           ";
    gotoRowCol(base_row + 3, base_col - 10);
    cout << "=======================";
    color(7);
}
void GAMELOOP(int rows, int cols)
{
    wait_before_start();


    SNAKE S1, S2, S3;
    init(S1, rows, cols, -37, rows / 2, cols / 4);
    init(S2, rows, cols, '#', rows / 3, cols / 2);
    init(S3, rows, cols, '*', rows / 4, 3 * cols / 4);


    int dir1 = RIGHT, dir2 = RIGHT, dir3 = RIGHT;
    int* p1 = &dir1;
    int* p2 = &dir2;
    int* p3 = &dir3;
    S1.direction = *p1;
    S2.direction = *p2;
    S3.direction = *p3;


    position food_pos;
    FOOD(food_pos, S1, S2, S3, rows, cols);


    score_display(0, 70, S1, 9);
    score_display(2, 70, S2, 10);
    score_display(4, 70, S3, 11);


    DISPLAYSNAKE(S1, 10);
    DISPLAYSNAKE(S2, 11);
    DISPLAYSNAKE(S3, 12);
    display_food(food_pos);

    bool gameover1 = false, gameover2 = false, gameover3 = false;

    while (!(gameover1 or gameover2 or gameover3))
    {
        hideConsoleCursor();

        if (_kbhit())
        {
            char pressed = _getch();


            if (pressed == -32)
            {
                pressed = _getch();
                if (pressed == 72 and *p1 != DOWN)
                {
                    *p1 = UP;
                }
                else if (pressed == 80 and *p1 != UP)
                {
                    *p1 = DOWN;
                }
                else if (pressed == 75 and *p1 != RIGHT)
                {
                    *p1 = LEFT;
                }
                else if (pressed == 77 and *p1 != LEFT)
                {
                    *p1 = RIGHT;
                }
            }
            else
            {

                if ((pressed == 'w' or pressed == 'W') and *p2 != DOWN)
                    *p2 = UP;
                else if ((pressed == 's' or pressed == 'S') and *p2 != UP)
                    *p2 = DOWN;
                else if ((pressed == 'a' or pressed == 'A') and *p2 != RIGHT)
                    *p2 = LEFT;
                else if ((pressed == 'd' or pressed == 'D') and *p2 != LEFT)
                    *p2 = RIGHT;


                else if ((pressed == 'i' or pressed == 'I') and *p3 != DOWN)
                    *p3 = UP;
                else if ((pressed == 'k' or pressed == 'K') and *p3 != UP)
                    *p3 = DOWN;
                else if ((pressed == 'j' or pressed == 'J') and *p3 != RIGHT)
                    *p3 = LEFT;
                else if ((pressed == 'l' or pressed == 'L') and *p3 != LEFT)
                    *p3 = RIGHT;
            }
        }


        ERASESNAKE(S1);
        ERASESNAKE(S2);
        ERASESNAKE(S3);


        S1.direction = *p1;
        S2.direction = *p2;
        S3.direction = *p3;


        MOVESNAKE(S1, rows, cols);
        MOVESNAKE(S2, rows, cols);
        MOVESNAKE(S3, rows, cols);


        if (snake_hit_itself(S1) or snake_hit_snake(S1, S2) or snake_hit_snake(S1, S3))
        {
            gameover1 = true;
            break;
        }
        if (snake_hit_itself(S2) or snake_hit_snake(S2, S1) or snake_hit_snake(S2, S3))
        {
            gameover2 = true;
            break;
        }
        if (snake_hit_itself(S3) or snake_hit_snake(S3, S1) or snake_hit_snake(S3, S2))
        {
            gameover3 = true;
            break;
        }


        if (!gameover1)
            DISPLAYSNAKE(S1, 10);
        if (!gameover2)
            DISPLAYSNAKE(S2, 11);
        if (!gameover3)
            DISPLAYSNAKE(S3, 12);


        bool food_eaten = false;
        if (!gameover1 and snake_eatenfood(S1, food_pos))
        {
            increase_score_snake(S1);
            food_eaten = true;
            score_display(0, 70, S1, 9);
        }
        else if (!gameover2 and snake_eatenfood(S2, food_pos))
        {
            increase_score_snake(S2);
            food_eaten = true;
            score_display(2, 70, S2, 10);
        }
        else if (!gameover3 and snake_eatenfood(S3, food_pos))
        {
            increase_score_snake(S3);
            food_eaten = true;
            score_display(4, 70, S3, 11);
        }


        if (food_eaten)
            FOOD(food_pos, S1, S2, S3, rows, cols);


        display_food(food_pos);

        Sleep(70);
    }

    system("cls");

   
    color(3);
    gotoRowCol(rows / 2 - 2, cols / 2 - 15);
    cout << "===========================";
    gotoRowCol(rows / 2 - 1, cols / 2 - 15);
    cout << "       GAME OVER           ";
    gotoRowCol(rows / 2, cols / 2 - 15);
    if (gameover1)
        cout << " Player 1 lost!             ";
    else if (gameover2)
        cout << " Player 2 lost!             ";
    else if (gameover3)
        cout << " Player 3 lost!             ";
    gotoRowCol(rows / 2 + 1, cols / 2 - 15);
    cout << "---------------------------";
    gotoRowCol(rows / 2 + 2, cols / 2 - 15);
    cout << "Player 1 score: " << S1.score << "       ";
    gotoRowCol(rows / 2 + 3, cols / 2 - 15);
    cout << "Player 2 score: " << S2.score << "       ";
    gotoRowCol(rows / 2 + 4, cols / 2 - 15);
    cout << "Player 3 score: " << S3.score << "       ";
    gotoRowCol(rows / 2 + 5, cols / 2 - 15);
    cout << "===========================";
    color(7);

   

}
int main()
{
    srand(time(0));
    hideConsoleCursor();

    int rows = 90; 
    int cols = 60;

    GAMELOOP(rows, cols);
    _getch();
    return 0;
}
