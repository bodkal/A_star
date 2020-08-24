
#include <iostream>
#include <list> 
#include <vector> 
#include <math.h> 
#include <stdio.h>     
#include <chrono>
#include <fstream>


using namespace std;
#define x 1000
#define y 1000

struct Int2 {
    short pos[2];
};
struct cell
{
    short pos[2];
    short g;
    short f;
    struct cell* father;
    vector<Int2> move = {{1,0},{0,1},{-1,0},{0,-1}};

};



void bild_board(short** board);
void bild_board1(short** board);
void bild_board2(short** board, vector<Int2> path2);
void CSV_create(short** board);

cell* new_cell(short pos[], short g, short f, cell* per);
vector<Int2> get_path(cell* child);
vector<Int2> serce(short** board, short start[2], short end[2]);

void main()
{
    
    short** board = new short* [x];
    for (short i = 0; i < x; i++) {
        board[i] = new short[y];
        for (short j = 0; j < y; j++) {
            board[i][j] = 0;
        }
    }

    cell** board1 = new cell * [x];
    for (short i = 0; i < x; i++) {
        board1[i] = new cell[y];
    }

    short start[2] = { 1, 1 };
    short end[2] = { x - 1, y - 1 };

    bild_board(board);
    vector<Int2> path2;
    vector<Int2> path3;

    path2 = serce(board, start, end);
    for (auto const& i : path2) {
        board[i.pos[0]][i.pos[1]] = -100;
    }
    CSV_create(board);

    bild_board2(board, path2);

    //bild_board1(board);
    path3 = serce(board, start, end);

    bild_board2(board, path2);
    for (auto const& i : path2) {
        board[i.pos[0]][i.pos[1]] = -100;
    }
    CSV_create(board);
}


vector<Int2> serce(short** board, short start[2], short end[2]) {

    short tmp_pos[2];

  //  short move[4][2] = { { 1,0 }, { 0, 1 }, { -1,0 }, { 0,-1 } };

    vector<cell*> open_list;

    auto start_tik = chrono::high_resolution_clock::now();

    open_list.push_back(new_cell(start, 0, 0, nullptr));


    while (open_list.size()) {


        while (!open_list[0]->move.size()) {
            open_list.erase(open_list.begin());
        }

            tmp_pos[0] = open_list[0]->pos[0] + open_list[0]->move[0].pos[0];
            tmp_pos[1] = open_list[0]->pos[1] + open_list[0]->move[0].pos[1];

            open_list[0]->move.erase(open_list[0]->move.begin());
            if (tmp_pos[0] == end[0] && tmp_pos[1] == end[1]) {

                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = finish - start_tik;
                cout << "Elapsed time: " << elapsed.count() << " s\n";

                return get_path(new_cell(end, 0, 0, open_list[0]));
            }
            else if (tmp_pos[0] > x - 1 || tmp_pos[0] < 0 || tmp_pos[1]>y - 1 || tmp_pos[1] < 0) {
                continue;
            }
            else if (board[tmp_pos[0]][tmp_pos[1]] == 500) {
                continue;
            }
            else if (board[tmp_pos[0]][tmp_pos[1]] == -3) {
                continue;
            }
            else {
                cell* per = new cell;
                per = open_list[0];
                float g = (per->g + 1); //sqrtf(abs(per->move[0].pos[0]) + abs(per->move[0].pos[1]))));
                short h = (abs(tmp_pos[0] - end[0]) + abs(tmp_pos[1] - end[1]));
                short p = board[tmp_pos[0]][tmp_pos[1]];
                short curr_f = g + h + p;

                short j = 0;

                for (cell* const& i : open_list) {
                    if (i->f > curr_f)
                        break;
                    j++;

                }
                open_list.insert(open_list.begin() + j, new_cell(tmp_pos, g, curr_f, per));
                board[tmp_pos[0]][tmp_pos[1]] = -3;
            }

    }
}

cell* new_cell(short pos[], short g, short f, cell* per) {

    cell* tmp_node = new cell;
    tmp_node->pos[0] = pos[0];
    tmp_node->pos[1] = pos[1];
    tmp_node->g = g;
    tmp_node->f = f;
    tmp_node->father = per;

    return tmp_node;

}

vector<Int2> get_path(cell* child) {
    vector<Int2> path;
    while (child->father != NULL) {
        path.push_back({ child->pos[0],child->pos[1] });
        child = child->father;
    }
    path.push_back({ child->pos[0],child->pos[1] });
    return path;
}


void bild_board(short** board) {

    for (short i = 0; i < x; i++)
    {
        for (short j = 0; j < y; j++)
        {
            board[i][j] = 0;
        }
    }
    short i;
    short j;
    j = 20;
    for (short i = 0; i < 6; i++)
    {
        board[i][j] = 500;

    }

    i = 40;
    for (short j = 0; j < 30; j++)
    {

        board[i][j] = 500;

    }
    /*
        j = 40;
        for (short i = 0; i < 30; i++)
        {

                board[i][j] = 500;
        }


        j = 20;

            for (short i = 0; i < 30; i++)
            {
                board[i][j] = 500;

            }

        for (short j = 50; j < y; j++)
        {
            for (short i = 50; i < x; i++)
            {
                board[i][j] = 500;

            }
        }

        i = 40;
        for (short j = 0; j < 30; j++)
        {
                board[i][j] = 500;
        }

        j = 40;
        for (short i = 50; i < x - 1; i++)
        {
                board[i][j] = 500;
        }

        for (short i = 59; i < 63; i++)
        {
            for (short j = 12; j < 47; j++)
            {
                board[i][j] = 500;

            }
        }*/
}
/*
void bild_board1(int** board) {


    for (int j = 5; j < 12; j++)
    {
        board[7][j] = 500;
    }

    for (int j = 0; j < 300; j++)
    {
        board[250][j] = 500;
    }
    for (int j = 400; j < 500; j++)
    {
        board[400][j] = 500;
    }
    for (int j = 400; j < 500; j++)
    {
        board[50][j] = 500;
    }
    for (int j = 400; j < 500; j++)
    {
        board[j][300] = 500;
    }
    for (int j = 350; j < 450; j++)
    {
        board[j][200] = 500;
    }
    for (int j = 50; j < 100; j++)
    {
        board[200][j] = 500;
    }
    for (int j = 0; j < 30; j++)
    {
        board[j][50] = 500;
    }
    for (int j = 80; j < 150; j++)
    {
        board[250][j] = 500;
    }
    for (int j = 3; j < 69; j++)
    {
        board[j][j] = 500;
    }

    for (int j = 3; j < 20; j++)
    {
        board[j + 30][j + 50] = 500;
    }

    for (int j = 3; j < 20; j++)
    {
        board[j + 30][j + 50] = 500;
    }


    for (int j = 3; j < 41; j++)
    {
        board[j][60] = 500;
    }
    for (int j = 45; j < 80; j++)
    {
        board[j][60] = 500;
    }
    for (int j = 3; j < 55; j++)
    {
        board[25][j] = 500;
    }
    for (int j = 40; j < 90; j++)
    {
        board[20][j] = 500;
    }

    for (int j = 4; j < 20; j++)
    {
        board[15][j] = 500;
    }
    for (int j = 7; j < 40; j++)
    {
        board[j][13] = 500;
    }
}
*/
void bild_board2(short** board, vector<Int2> path2) {

    for (short i = 0; i < x; i++)
    {
        for (short j = 0; j < y; j++)
        {
            board[i][j] = x + y;
        }
    }
    for (auto const& i : path2) {
        board[i.pos[0]][i.pos[1]] = 0;
    }

    for (const Int2& test : path2) {

        for (short i = -test.pos[0]; i < x - test.pos[0]; i++)
        {
            for (short k = -test.pos[1]; k < y - test.pos[1]; k++)
            {
                if (board[i + test.pos[0]][k + test.pos[1]] > abs(k) + abs(i))
                    board[i + test.pos[0]][k + test.pos[1]] = abs(k) + abs(i);
            }
        }
    }
}

void CSV_create(short** board) {
    // file pointer 
    fstream fout;
    remove("board.csv");
    // opens an existing csv file or creates a new file. 
    fout.open("board.csv", ios::out | ios::app);

    // Read the input 
    for (short i = 0; i < x; i++) {
        for (short j = 0; j < y; j++)
        {
            fout << board[i][j] << ", ";
        }
        fout << "\n";
    }
    fout.close();
    system("python plot_bprd.py");

}