
#include <iostream>
#include <list> 
#include <vector> 
#include <math.h> 
#include <stdio.h>     
#include <chrono>
#include <fstream>


using namespace std;
#define size_x 1000
#define size_y 1000

struct short2 {
    short x;
    short y;
};

struct cell
{
    short2 pos;
    float g;
    float f;
    short val;
    struct cell* father;
};

void bild_board(cell ** board);
void bild_board1(cell ** board);
void bild_board2(cell ** board, vector<short2> path2);
void CSV_create(cell ** board);
vector<short2> get_path(cell* child);
vector<short2> serce(cell ** board, short2 start, short2 end);
short push_in_order(vector<cell*>* open_list, short insert, float curr_f, cell* per);

int main()
{
    cell ** board = new cell * [size_x];
    for (short i = 0; i < size_x; i++) {
        board[i] = new cell[size_y];
        for (short j = 0; j < size_y; j++)
        {
            board[i][j] = {{i,j},0,0,0,nullptr};
        }
    }

    short2 start = { 0, 0 };
    short2 end = { size_x-1,  size_y - 1 };

    bild_board(board);
    vector<short2> path2;
    vector<short2> path3;

    path2 = serce(board, start, end);
    bild_board(board);

    for (auto const& i : path2) {
        board[i.x][i.y].val = -500;
    }
    CSV_create(board);
    bild_board(board);

 //   bild_board2(board, path2);
    bild_board1(board);
    path3 = serce(board, start, end);
    bild_board2(board, path2);
    bild_board1(board);

    for (auto const& i : path3) {
        board[i.x][i.y].val = -500;
    }
    CSV_create(board);
    return 0;
}


vector<short2> serce(cell ** board, short2 start, short2 end) {
    float g;
    short h;
    short p;
    short j;
    float curr_f;
    short insert;
    short2 tmp_pos;
    short2 move[8] = {{ 1,0 }, { 0, 1 }, { -1,0 }, { 0,-1 },{ 1,-1 },{ -1,1 },{ -1,-1 },{ 1,1 } };

    vector<cell*> open_list;
    auto start_tik = chrono::high_resolution_clock::now();
    board[start.x][start.y].val = -3;
    open_list.push_back(&board[start.x][start.y]);
    
    while (open_list.size()) {

        insert = 0;
        cell* per = open_list[0];

        for (short i = 0; i < 8; i++) {
            tmp_pos.x = per->pos.x + move[i].x;
            tmp_pos.y = per->pos.y + move[i].y;

                
            if (tmp_pos.x == end.x && tmp_pos.y == end.y) {

                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = finish - start_tik;
                cout << "Elapsed time: " << elapsed.count() << " s\n";
                board[end.x][end.y].father = per;
                return get_path(&board[end.x][end.y]);
            }
            else if (tmp_pos.x > size_x - 1 || tmp_pos.x < 0 || tmp_pos.y>size_y - 1 || tmp_pos.y < 0) 
                continue;

            else if (board[tmp_pos.x][tmp_pos.y].val == -100) 
                continue;

            else if (board[tmp_pos.x][tmp_pos.y].val == -3) {
                if (board[tmp_pos.x][tmp_pos.y].g > per->g)
                    board[tmp_pos.x][tmp_pos.y].father = per;
            }
            else {

                if(i<4)
                    g = (per->g + 1);
                else
                    g = (per->g + 1.414);
                h = (abs(tmp_pos.x - end.x) + abs(tmp_pos.y - end.y));
                p = board[tmp_pos.x][tmp_pos.y].val;
                curr_f = g + h + p;
                board[tmp_pos.x][tmp_pos.y].f = curr_f;
                board[tmp_pos.x][tmp_pos.y].g = g;
                board[tmp_pos.x][tmp_pos.y].val = -3;
                board[tmp_pos.x][tmp_pos.y].father = per;
              
                insert = push_in_order(&open_list, insert, curr_f, &board[tmp_pos.x][tmp_pos.y]);
            }

        }
        open_list.erase(open_list.begin() + insert);
    }
}

short push_in_order(vector<cell *> * open_list,short insert,float curr_f,cell * per) {
    short j = 0;
    for (cell* const& i : *open_list) {
        if (i->f > curr_f)
            break;
        j++;

    }
    if (j <= insert)
        insert++;
    open_list->insert(open_list->begin() + j, per);
    return insert;
}

vector<short2> get_path(cell* child) {
    vector<short2> path;
    while (child->father != NULL) {
        path.push_back({ child->pos.x,child->pos.y });
        child = child->father;
    }
    path.push_back({ child->pos.x,child->pos.y });
    return path;
}


void bild_board(cell** board) {

    for (short i = 0; i < size_x; i++)
    {
        for (short j = 0; j < size_y; j++)
        {
            board[i][j].val = 0;
        }
    }

    short i;
    short j;
    j = 20;
    for (short i = 0; i < 6; i++)
    {
        board[i][j].val = -100;
    }
    
    i = 40;
    for (short j = 0; j < 30; j++)
    {

        board[i][j].val = -100;

    }
    for (short j =20; j < 70; j++)
    {

        board[i][j].val = -100;

    }
    for (short j = 410; j < 790; j++)
    {

        board[999-j][j].val = -100;

    }
    for (short j = 410; j < 790; j++)
    {

        board[998 ][j].val = -100;

    }
    for (short j = 122; j < 478; j++)
    {

        board[558][j].val = -100;

    }
    for (short j = 122; j < 478; j++)
    {

        board[558][j].val = -100;

    }
    for (short j = 410; j < 790; j++)
    {

        board[122][j].val = -100;

    }
    for (short j = 410; j < 790; j++)
    {

        board[998 - j][j].val = -100;

    }
    for (short j = 200; j < 790; j++)
    {

        board[i][j].val = -100;

    }
    for (short j = 26; j < 142; j++)
    {

        board[480][j].val = -100;

    }
    for (short j = 260; j < 690; j++)
    {

        board[j][j].val = -100;

    }
    for (short i = 3; i < 49; i++)
    {

        board[i][50].val = -100;

    }
   /* for (short i = 0; i < 70; i++)
    {

        board[i][90].val = -100;

    }*/
  
}

void bild_board1(cell ** board) {

    short i;
    short j;
    j = 20;
    for (short i = 0; i < 6; i++)
    {
        board[i][j].val = -100;
    }

    i = 40;
    for (short j = 0; j < 30; j++)
    {

        board[i][j].val = -100;

    }
    for (short j = 0; j < 1; j++)
    {

        board[5][j].val = -100;

    }
    for (short j = 20; j < 70; j++)
    {

        board[i][j].val = -100;

    }
    for (short i = 3; i < 49; i++)
    {

        board[i][50].val = -100;

    }
    for (short i = 0; i < 70; i++)
    {

        board[i][90].val = -100;

    }
    for (int j = 5; j < 12; j++)
    {
        board[7][j].val = -100;
    }

    for (int j = 0; j < 30; j++)
    {
        board[30][j].val = -100;
    }
    for (int j = 50; j < -100; j++)
    {
        board[70][j].val = -100;
    }
    for (short j = 0; j < 30; j++)
    {

        board[40][j].val = -100;

    }
}


void bild_board2(cell** board, vector<short2> path2) {

    for (short i = 0; i < size_x; i++)
    {
        for (short j = 0; j < size_y; j++)
        {
            board[i][j].val = size_x + size_y;
        }
    }

    for (auto const& i : path2) {
        board[i.x][i.y].val = 0;
    }

    for (const short2& test : path2) {

        for (short i = -test.x; i < size_x - test.x; i++)
        {
            for (short k = -test.y; k < size_y - test.y; k++)
            {
                if (board[i + test.x][k + test.y].val > abs(k) + abs(i))
                    board[i + test.x][k + test.y].val = abs(k) + abs(i);
            }
        }
    }
}


void CSV_create(cell** board) {
    // file pointer 
    fstream fout;
    remove("board.csv");
    // opens an esize_xisting csv file or creates a new file. 
    fout.open("board.csv", ios::out | ios::app);

    // Read the input 
    for (short i = 0; i < size_x; i++) {
        for (short j = 0; j < size_y; j++)
        {
            fout << board[i][j].val << ", ";
        }
        fout << "\n";
    }
    fout.close();
    system("python plot_bprd.py");

}