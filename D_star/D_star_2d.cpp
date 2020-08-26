
#include <iostream>
#include <list> 
#include <vector> 
#include <math.h> 
#include <stdio.h>     
#include <chrono>
#include <fstream>
#include <limits>

using namespace std;
#define x_max 1000
#define y_max 1000


struct cell
{
    pair<short ,short> pos;
    float g;
    float f;
    float rms;
    struct cell* father;
};

float inf = numeric_limits<float>::infinity();

void add_obs(cell ** board);
//void add_p(cell ** board, vector<pair<short ,short>> path2);
//void CSV_create(short** board);
cell* update_cell(cell * update_cell,float new_g,float curr_f,cell * per);

vector<pair<short ,short>> get_path(cell* child);
vector<pair<short ,short>> serce(cell ** board,  pair<short ,short> start,  pair<short ,short> end);
float heuristic (pair<float,float> u,pair<float,float> v);

int main()
{
    cell ** board = new cell * [x_max];
    for (short i = 0; i < x_max; i++) {
        board[i] = new cell [y_max];
        for (short j = 0; j < y_max; j++) {
                board[i][j].g =inf;
                board[i][j].rms = inf;
                board[i][j].pos={i,j};
        }
    }

    pair<short ,short> start( 1, 1 );
    pair<short ,short> end ( x_max-1, y_max-1);


    add_obs(board);
    vector< pair<short ,short>> path2;

    path2 = serce(board, start, end);

    for (auto const& i : path2) {
        board[i.first][i.second].g = -1;
    }

   // CSV_create(board);

    return 0;
}
float heuristic (pair<short,short> u,pair<short,short> v){
    return sqrt(pow((u.first - v.first),2) + pow((u.first - v.first),2));
}

vector<pair<short ,short>> serce(cell ** board, pair<short ,short> start, pair<short ,short> end) {
    bool finise = false;

    pair<short ,short> tmp_pos;
    //short move[8][2] = {{ 1,1 },{ -1, 1 },{ -1,1 },{ -1,-1 },{ 1,0 },{ 0, 1 },{ -1,0 },{ 0,-1 } };
    short move[4][2] = {{ 1,0 },{ 0, 1 },{ -1,0 },{ 0,-1 } };

    vector< cell * > open_list;
    auto start_tik = chrono::high_resolution_clock::now();
   // new_cell(start, 0, 0, nullptr);

    board[start.first][start.second].g=0;
    board[start.first][start.second].rms=0;

    open_list.push_back(&board[start.first][start.second]);

    while (open_list.size()) {


        short insert = 0;
        for (short i = 0; i < 8; i++) {
            tmp_pos.first = open_list[0]->pos.first + move[i][0];
            tmp_pos.second = open_list[0]->pos.second + move[i][1];

            if (tmp_pos.first == end.first && tmp_pos.second== end.second){

                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = finish - start_tik;
                cout << "Elapsed time: " << elapsed.count() << " s\n";
                finise = true;
                board[tmp_pos.first][tmp_pos.second].father=open_list[0];

                return get_path(&board[tmp_pos.first][tmp_pos.second]);
            }
            else if (tmp_pos.first > x_max - 1 || tmp_pos.first < 0 || tmp_pos.second>y_max - 1 || tmp_pos.second < 0) {
                continue;
            }
            else if (board[tmp_pos.first][tmp_pos.second].g == -1) {
                continue;
            }
            else if (board[tmp_pos.first][tmp_pos.second].g !=inf) {
                continue;
            }
            else {


                float g = (open_list[0]->g + 1);
                float h =heuristic(open_list[0]->pos,end);
                short p = 0;//board[tmp_pos[0]][tmp_pos[1]];
                float curr_f = g + h + p;

                short j = 0;

                for (cell* const& i : open_list) {
                    if (i->f > curr_f)
                        break;
                    j++;

                }
                if (j <= insert)
                    insert++;
                if(j==0)
                    open_list.insert(open_list.begin(), update_cell(&board[tmp_pos.first][tmp_pos.second], g, curr_f, open_list[1]));
                else
                    open_list.insert(open_list.begin() + j, update_cell(&board[tmp_pos.first][tmp_pos.second], g, curr_f, open_list[0]));
            }

        }
        if (finise)
            break;
        delete open_list[insert];
        open_list.erase(open_list.begin() + insert);

    }
}

vector<pair<short,short>> get_path(cell * child) {
    vector<pair<short,short>> path;
    while (child->father != NULL) {
        path.push_back({ child->pos.first,child->pos.second});
        child = child->father;
    }
    return path;
}

cell* update_cell(cell * update_cell,float new_g,float curr_f,cell * per){
update_cell->g = new_g;
update_cell->f = curr_f;
update_cell->father = per;
return update_cell;
}


void cell(cell ** board) {

    short i;
    short j;

    j = 20;
    for (short i = 0; i < 6; i++) {
        board[i][j].g = -1;

    }

    i = 40;
    for (short j = 0; j < 30; j++) {

        board[i][j].g = -1;

    }
}
/*
void add_p(short** board, vector<Int2> path2) {

    for (short i = 0; i < x; i++)
    {
        for (short j = 0; j < y; j++)
        {
            board[i][j]->g = x + y;
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
*/
void CSV_create(short** board) {
    // file pointer 
    fstream fout;
    remove("board.csv");
    // opens an existing csv file or creates a new file. 
    fout.open("board.csv", ios::out | ios::app);

    // Read the input 
    for (short i = 0; i < x_max; i++) {
        for (short j = 0; j < y_max; j++)
        {
            fout << board[i][j] << ", ";
        }
        fout << "\n";
    }
    fout.close();
    system("python plot_bprd.py");

}