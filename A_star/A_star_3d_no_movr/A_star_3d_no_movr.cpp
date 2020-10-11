#include <iostream>
#include <list> 
#include <vector> 
#include <stdio.h>     
#include <chrono>
#include <fstream>
#include <stdlib.h> 
using namespace std;

#define x 100
#define y 100
#define z 360
#define shal 10 

struct Int3 {
     short pos[3];
};

struct cell
{
     short pos[3];
     short g;
    // short h;
    // short p;
     short f;
    struct cell* father;
    vector<Int3> move = {{1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,-1},
                        {1,1,0},{1,0,1},{0,1,1},{-1,-1,0},{-1,0,-1},{0,-1,-1},{-1,1,0},{1,-1,0},{0,1,-1},{0,-1,1},{1,0,-1},{-1,0,1},
                        {1,0,0},{0,1,0},{-1,0,0},{0,0,1},{0,-1,0},{0,0,-1}};
};


vector<Int3> bild_board( short*** board);
vector<Int3>  bild_board1( short*** board);
void bild_board2(short*** board, vector<Int3> path2);

vector<Int3> get_path(cell* child);
vector<Int3> serce(short*** board, short start[3], short end[3]);
void CSV_create(vector<Int3> obs, vector<Int3> path2);
cell* new_cell(short pos[], short g, short f, cell* per);

short main()
{

    short *** board = new short ** [x];
    for (short i = 0; i < x; i++) {
        board[i] = new short* [y];
        for (short j = 0; j < y; j++) {
            board[i][j] = new short[z];
            for (short k = 0; k < z; k++) {
                board[i][j][k] = 0;
            }
        }
    }
    short start[3] = { 1, 1 ,1 };
    short end[3] = { x - 1, y- 1,z-20};

    vector<Int3> obs = bild_board(board);
    vector<Int3> path2;
    vector<Int3> path3;

    path2 = serce(board, start, end);
    CSV_create(obs, path2);

    bild_board2(board, path2);

    obs = bild_board1(board);

    path3 = serce(board, start, end);

    CSV_create(obs, path3);
}



vector<Int3> serce(short*** board, short start[3], short end[3]) {

        vector<cell*>  open_list;// (new vector<shared_ptr<cell>>);
        //vector<shared_ptr<cell>>  clos_list;

        //short move[6][3] = { {1,0,0},{0,1,0},{0,0,1},{-1,0,0},{0,-1,0},{0,0,-1} };
        short tmp_pos[3];
        cell curr_cell;
        auto start_tik = chrono::high_resolution_clock::now();
        open_list.push_back(new_cell(start, 0, 0,  nullptr));
        while (!open_list.empty()) {



            while (!open_list[0]->move.size())
            {
                //delete open_list[0];
                open_list.erase(open_list.begin());
            }
            short i = 0;
           // cell * per=new cell;



            //per = open_list[0];
           // short r = rand() % open_list[0]->move.size();
            short r = 0;
            short insert = 0;
            tmp_pos[0] = open_list[0]->pos[0] + open_list[0]->move[r].pos[0];
            tmp_pos[1] = open_list[0]->pos[1] + open_list[0]->move[r].pos[1];
            tmp_pos[2] = open_list[0]->pos[2] + open_list[0]->move[r].pos[2];

            if (tmp_pos[0] == end[0] && tmp_pos[1] == end[1] && tmp_pos[2] == end[2]) {

                // cell node = { {end[0],end[1],end[2]},0,0,0,0 , per };
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = finish - start_tik;
                cout << "Elapsed time: " << elapsed.count() << " s\n";
                return get_path(new_cell(end, 0, 0, open_list[0]));
            }
            else if (tmp_pos[0] > x - 1 || tmp_pos[0] < 0 || tmp_pos[1]>y - 1 || tmp_pos[1] < 0 || tmp_pos[2]>z - 1 || tmp_pos[2] < 0) {
                open_list[0]->move.erase(open_list[0]->move.begin()+r);

                continue;
            }
            else if (board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]] == 500) {
                open_list[0]->move.erase(open_list[0]->move.begin()+r);

                continue;
            }
            else if (board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]] == -3) {
                open_list[0]->move.erase(open_list[0]->move.begin()+r);


                continue;
            }
            else {
                 cell * per=new cell;
                per = open_list[0];
                float g = (per->g + sqrtf(abs(per->move[0].pos[0]) + abs(per->move[0].pos[1]) + abs(per->move[0].pos[2])));
                short h = (abs(tmp_pos[0] - end[0]) + abs(tmp_pos[1] - end[1]) + abs(tmp_pos[2] - end[2]));
                short p = board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]];
                short curr_f = g + h + p;

                short j = 0;

                for (cell* const& i : open_list) {
                    if (i->f > curr_f)
                        break;
                    j++;

                }
                per->move.erase(per->move.begin()+r);
                open_list.insert(open_list.begin() + j, new_cell(tmp_pos, g, curr_f, per));
                board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]] = -3;
            }

        }
    }
   






cell* new_cell(short pos[], short g,short f, cell* per) {

    cell* tmp_node=new cell;
    tmp_node->pos[0] = pos[0];
    tmp_node->pos[1] = pos[1];
    tmp_node->pos[2] = pos[2];
    tmp_node->g = g;
   // tmp_node->h = h;
   // tmp_node->p = p;
    tmp_node->f = f;
    tmp_node->father = per;

    return tmp_node;

}

vector<Int3> get_path(cell* child) {
    vector<Int3> path;
    while (child->father != NULL) {
        path.push_back({ child->pos[0],child->pos[1],child->pos[2] });
        child = child->father;
    }
    path.push_back({ child->pos[0],child->pos[1],child->pos[2] });
    return path;
}



vector<Int3> bild_board(short*** board) {

    for (short i = 0; i < x; i++)
    {
        for (short j = 0; j < y; j++)
        {
            for (short k = 0; k < z; k++)
            {
                board[i][j][k] = 0;
            }
        }
    }
    vector<Int3> obs;
    short i;
    short j;
    short k;
    j = 3;
    for (short k = 2; k < 5; k++)
    {
        for (short i = 0; i < 6; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }
    
    i = 40;
    for (short j = 0; j < 30; j++)
    {
        for (short k = 0; k <20; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    j = 40;
    for (short i = 0; i < 30; i++)
    {
        for (short k = 0; k < z/2; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });
        }
    }
    

    j = 20;
    for (short k = 0; k < 19; k++)
    {
        for (short i = 0; i < 30; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    k = 20;
    for (short j = 50; j < y; j++)
    {
        for (short i = 50; i < x; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    i = 40;
    for (short j = 0; j < 30; j++)
    {
        for (short k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    j = 40;
    for (short i = 50; i < x - 1; i++)
    {
        for (short k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    k = 30;
    for (short i = 28; i < 63; i++)
    {
        for (short j = 12; j < 47; j++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }
    return obs;
}

vector<Int3>  bild_board1(short*** board) {
    vector<Int3> obs;
    short i;
    short j;
    short k;
    j = 20;
    for (short k = 21; k < 24; k++)
    {
        for (short i = 0; i < 30; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    j = 20;
    for (short k = 0; k < 19; k++)
    {
        for (short i = 0; i < 30; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }
    j = 30;

    for (short k = 0; k < 30; k++)
    {
        for (short i = 10; i < 40; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }


    i = 40;
    for (short j = 0; j < 30; j++)
    {
        for (short k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    i = 40;
    for (short j = 0; j < 99; j++)
    {
        for (short k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });
        }
    }
    i = 60;
    for (short j = 0; j < 30; j++)
    {
        for (short k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    i = 20;
    for (short j = 7; j < 23; j++)
    {
        for (short k = 10; k < 50; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }


    j = 40;
    for (short i = 30; i < x; i++)
    {
        for (short k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    k = 30;
    for (short i = 28; i < 63; i++)
    {
        for (short j = 12; j < 47; j++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }
    return obs;

}


void CSV_create(vector<Int3> obs, vector<Int3> path) {
    // file pointer 
    fstream fout;
    remove("board.csv");
    // opens an existing csv file or creates a new file. 
    fout.open("board.csv", ios::out | ios::app);

    // Read the input 
    for (Int3 const& i : obs) {

        fout << i.pos[0] << ", " << i.pos[1] << ", " << i.pos[2] << ", ";
        fout << "\n";
    }
    fout << -1 << ", " << -1 << ", " << -1 << ", " << "\n";

    for (Int3 const& i : path) {

        fout << i.pos[0] << ", " << i.pos[1] << ", " << i.pos[2] << ", ";
        fout << "\n";
    }
    fout.close();
    system("python plot_bprd.py");

}

void bild_board2(short*** board, vector<Int3> path2) {

    for (short i = 0; i < x; i++)
    {
        for (short j = 0; j < y; j++)
        {
            for (short k = 0; k < z; k++)
            {
                board[i][j][k] = x;

            }
        }
    }
    for (auto const& i : path2) {
        board[i.pos[0]][i.pos[1]][i.pos[2]] = 0;
    }

    for (Int3 const& test : path2) {

        for (short i = (test.pos[0] - shal)/20; i < (x - test.pos[0])/20; i++)
        {
            for (short j =( -test.pos[1])/20; j < (y - test.pos[1])/20; j++)
            {
                for (short k =( -test.pos[2])/20; k < (z - test.pos[2])/20; k++)
                {
                    if (board[i + test.pos[0]][j + test.pos[1]][k + test.pos[2]] > abs(k) + abs(j) + abs(i))
                        board[i + test.pos[0]][j + test.pos[1]][k + test.pos[2]] = abs(j) + abs(k) + abs(i);
                }
            }
        }
    }

}
