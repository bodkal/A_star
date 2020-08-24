//#pragma comment(lib, "Ktree.cpp")

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <map>
#include <chrono>

using namespace std;
using namespace Eigen;


class tree
{
public:
	struct node {
		Vector2i data;
		int id;
		vector<struct node*> childs;
		struct node* father;
	};
	node* root;
	map<int, node*> node_map;

	tree(Vector2i data);
	node* serche_tree(int id);
	void new_node(Vector2i data, int id, int name);
	int get_deep(int id);
	int get_father(int id);
	void remove_node(int id);
	void change_father(int from, int to);
	void print_tree(int id);

};
	