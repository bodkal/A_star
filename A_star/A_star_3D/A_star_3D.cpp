#include <iostream>
#include <list> 
#include <vector> 
#include <stdio.h>     
#include <chrono>
#include <fstream>

#define x 1000
#define y 1000
#define z 360

struct cell
{
    int pos[3];
    int g;
 //   int h;
    int p;
    int f;
    struct cell * father;

};

struct Int3 {
    int pos[3];
};

using namespace std;

vector<Int3> bild_board(int*** board);
vector<Int3>  bild_board1(int*** board);
void bild_board2(int*** board, vector<Int3> path2);

vector<Int3> get_path(cell* child);
vector<Int3> serce(int*** board, int start[3], int end[3]);
void CSV_create(vector<Int3> obs, vector<Int3> path2);
cell* new_cell(int pos[], int g,  int f, cell* per);

int main()
{

    int*** board = new int** [x];
    for (int i = 0; i < x; i++) {
        board[i] = new int* [y];
        for (int j = 0; j < y; j++) {
            board[i][j] = new int[z];
            for (int k = 0; k < z; k++) {
                board[i][j][k] = 0;
            }
        }
    }
    int start[3] = { 1, 1 ,1 };
    int end[3] = { x-1, y-1,z-1 };

    vector<Int3> obs = bild_board(board);
   

    vector<Int3> path2;
    vector<Int3> path3;

    path2 = serce(board, start, end);
    CSV_create(obs, path2);

    bild_board2(board, path2);

    obs= bild_board1(board);

    path3 = serce(board, start, end);

    CSV_create(obs, path3);

}



vector<Int3> serce(int *** board, int start[3], int end[3]) {

    vector<cell *>  open_list;
    //vector<cell *>  clos_list;

    int move[6][3] = {{1,0,0},{0,1,0},{0,0,1},{-1,0,0},{0,-1,0},{0,0,-1}};
    int tmp_pos[3];
    cell curr_cell;

    auto start_tik = chrono::high_resolution_clock::now();
    open_list.push_back(new_cell(start,0,0,nullptr));
    while (!open_list.empty()) {
        cell * per = new cell;
        per = open_list[0] ;

        int insert = 0;

        for (int i = 0; i < 6; i++) {

            tmp_pos[0] = per[0].pos[0] + move[i][0];
            tmp_pos[1] = per[0].pos[1] + move[i][1];
            tmp_pos[2] = per[0].pos[2] + move[i][2];


            if (tmp_pos[0] == end[0] && tmp_pos[1] == end[1] && tmp_pos[2] == end[2]) {

               // cell node = { {end[0],end[1],end[2]},0,0,0,0 , per };
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = finish - start_tik;
                cout << "Elapsed time: " << elapsed.count() << " s\n";
                return get_path(new_cell(end,0,0, per));
            }
            else if (tmp_pos[0] > x - 1 || tmp_pos[0] < 0 || tmp_pos[1]>y - 1 || tmp_pos[1] < 0||tmp_pos[2]>z - 1 || tmp_pos[2] < 0) {
                continue;
            }
            else if (board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]] == 500) {
                continue;
            }
            else if (board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]] == -3) {
                continue;
            }
            else {
                int g = per[0].g + 1;
                int h = (abs(tmp_pos[0] - end[0]) + abs(tmp_pos[1] - end[1]) + abs(tmp_pos[2] - end[2]));
                int p = board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]];
                int curr_f = g + h + p;

                int j = 0;

                for (cell * const& i : open_list) {
                    if (i->f > curr_f)
                        break;
                    j++;

                }
                if (j <= insert)
                    insert++;
                open_list.insert(open_list.begin() + j, new_cell(tmp_pos,g, curr_f, per));
                board[tmp_pos[0]][tmp_pos[1]][tmp_pos[2]] = -3;
            }
        }
        //clos_list.push_back(curr_cell);
        //if (open_list[insert]->father != nullptr)
        //    delete open_list[insert]->father;
        delete open_list[insert];

        open_list.erase(open_list.begin() + insert);

    }
}





cell* new_cell(int pos[], int g,int f, cell* per) {

    cell * tmp_node = new cell();
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



vector<Int3> bild_board(int*** board) {

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                board[i][j][k] = 0;
            }
        }
    }
    vector<Int3> obs;
    int i;
    int j;
    int k;
    j = 3;
    for (int k = 2; k < 5; k++)
    {
        for (int i = 0; i < 6; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    i = 40;
    for (int j = 0; j < 30; j++)
    {
        for (int k = 0; k < 50; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    j = 40;
    for (int i = 0; i < 30; i++)
    {
        for (int k = 0; k < 20; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });
        }
    }


    j = 20;
    for (int k = 0; k < 19; k++)
    {
        for (int i = 0; i < 30; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    k = 20;
    for (int j = 50; j < 300; j++)
    {
        for (int i = 50; i < 100; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    i = 40;
    for (int j = 0; j < 30; j++)
    {
        for (int k = 0; k < 150; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    j = 40;
    for (int i = 50; i < x - 1; i++)
    {
        for (int k = 0; k < 130; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    k = 30;
    for (int i = 28; i < 63; i++)
    {
        for (int j = 12; j < 47; j++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }
    return obs;
}


vector<Int3>  bild_board1(int *** board) {
    vector<Int3> obs;
    int i;
    int j;
    int k;
    j = 20;
    for (int k = 21; k < 24; k++)
    {
        for (int i = 0; i < 30; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    j = 20;
    for (int k = 0; k < 19; k++)
    {
        for (int i = 0; i < 30; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }
    j = 30;

    for (int k = 0; k < 30; k++)
    {
        for (int i = 10; i < 40; i++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

  
    i = 40;
    for (int j = 0; j < 30; j++)
    {
        for (int k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }
    i = 60;
    for (int j = 0; j < 30; j++)
    {
        for (int k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    i = 20;
    for (int j = 7; j < 23; j++)
    {
        for (int k = 10; k < 50; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }


    j = 40;
    for (int i = 30; i < x ; i++)
    {
        for (int k = 0; k < z; k++)
        {
            board[i][j][k] = 500;
            obs.push_back({ i,j,k });

        }
    }

    k = 30;
    for (int i = 28; i < 63; i++)
    {
        for (int j = 12; j < 47; j++)
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
    for (Int3 const & i: obs) {
        
            fout << i.pos[0] << ", "<<i.pos[1] << ", "<<i.pos[2] << ", ";
        fout << "\n";
    }
    fout <<-1 << ", " << -1 << ", " << -1 << ", "<< "\n";

    for (Int3 const& i : path) {

        fout << i.pos[0] << ", " << i.pos[1] << ", " << i.pos[2] << ", ";
        fout << "\n";
    }
    fout.close();
    system("python plot_bprd.py");

}

void bild_board2(int*** board, vector<Int3> path2) {

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                board[i][j][k] = x;

            }
        }
    }
    for (auto const& i : path2) {
        board[i.pos[0]][i.pos[1]][i.pos[2]] = 0;
    }

    for (Int3 const& test : path2) {

        for (int i = -test.pos[0]; i < x - test.pos[0]; i++)
        {
            for (int j = -test.pos[1]; j < y - test.pos[1]; j++)
            {
                for (int k = -test.pos[2]; k < z - test.pos[2]; k++)
                {
                    if (board[i + test.pos[0]][j + test.pos[1]][k + test.pos[2]] > abs(k) + abs(j) + abs(i))
                        board[i + test.pos[0]][j + test.pos[1]][k + test.pos[2]] = abs(j) + abs(k) + abs(i);
                }
            }
        }
    }

}
