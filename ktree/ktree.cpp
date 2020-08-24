// ktree.cpp : This file contains the 'main' function. Program execution begins and ends there.

//#include "Ktree.h"

tree::tree(Vector2i data) {
		cout << "start new tree object\n";
		node* tmp_node = new node();
		tmp_node->data = data;
		tmp_node->id = 0;
		root = tmp_node;
		node_map.insert({ 0 , root });

	}

	void tree::new_node(Vector2i data, int id,int name) {
		//node* tmp_node_id = this->serche_tree(id);
		node* tmp_node_id =this->node_map[id];
		node* tmp_node = new node();
		tmp_node->data = data;
		tmp_node->id = name;
		tmp_node->father = tmp_node_id;
		tmp_node_id->childs.push_back(tmp_node);
		node_map.insert({ name,tmp_node });
	}


	tree::node * tree::serche_tree(int id) {
		vector<node*> q;
		q.push_back(node_map[id]);
		while (!q.empty())
		{
			for (int n = q.size(); n > 0; n--)
			{
				node* p = q[0];
				if (p->id == id)
					return p;
				q.erase(q.begin());
				for (int i = 0; i < p->childs.size(); i++) {
					q.push_back(p->childs[i]);
				}
			}
		}
		return NULL;
	}

	int tree::get_deep(int id) {
		int i = 0;
		node* child = this->node_map[id];

		//node* child = this->serche_tree(id); 
		while (child->father != NULL) {
			i++;
			child = child->father;
		}
		return i;
	}

	int tree::get_father(int id) {
		if (id == 0)
			return -1;
		else
			return  this->node_map[id]->father->id;
	}

	void tree::remove_node(int id) {

		vector<node*> q;
		q.push_back(this->node_map[id]);
		
		for (size_t i = 0; i < this->node_map[id]->father->childs.size(); i++)
		{
			if (this->node_map[id]->father->childs[i]->id == id) {
				this->node_map[id]->father->childs.erase(this->node_map[id]->father->childs.begin() + i);
				break;
			}
		}
		
		while (!q.empty())
		{
			for (int n = q.size(); n > 0; n--)
			{
				node* p = q[0];
				
				q.erase(q.begin());

				for (int i = 0; i < p->childs.size(); i++) {
					q.push_back(p->childs[i]);
				}
				this->node_map.erase(p->id);
			}
		}
		
	}

	void tree::change_father(int from, int to) {
		for (size_t i = 0; i < node_map[from]->father->childs.size(); i++)
		{
			if (node_map[from]->father->childs[i]->id == from) {
				node_map[from]->father->childs.erase(node_map[from]->father->childs.begin() + i);
				break;
			}
		}
		node_map[from]->father = node_map[to];
		node_map[to]->childs.push_back(node_map[from]);

	}

	void tree::print_tree(int id)
	{
			vector<node *> q;
			q.push_back(node_map[id]);
			//q.push_back(this->serche_tree(id));
			int  tmp = id;
			vector<int> tabs;
			while (!q.empty())
			{
				for (int n = q.size(); n > 0; n--)			
				{
					node* p = q[0];
					q.erase(q.begin());
					if (p->id != id) {
						if (tmp == p->father->id)
							cout << " " << p->id << " ";
						else
							cout << "\t\t(" << p->father->id << ")" << p->id;
						tmp = p->father->id;
					}
					else {
						cout << " " << p->id << " ";
						tmp = id;
					}
					for (int i = 0; i < p->childs.size(); i++) {
						q.push_back(p->childs[i]);
					}
				}
				cout << endl << endl; 
				if (q.size() && q[0]->id != 0)
				{
					tmp = q[0]->father->id;
					cout << "(" << q[0]->father->id << ")";
				}
			}
		}


	/*
void main() {

	Vector2i data= Vector2i(0,0);
	Vector2i data1 = Vector2i(1, 1);
	Vector2i data2 = Vector2i(2, 2);
	Vector2i data3 = Vector2i(2, 2);
	Vector2i data4 = Vector2i(3, 3);

	auto start_tik = chrono::high_resolution_clock::now();

	
	tree a(data);

	a.new_node(data1, 0,1);
	a.new_node(data2, 0,2);
	a.new_node(data3, 0,3);
	a.new_node(data3, 1,4);
	a.new_node(data3, 2,5);
	a.new_node(data3, 3,6);
	a.new_node(data3, 3,7);
	a.new_node(data4, 5,8);
	a.new_node(data3, 2,9);
	a.new_node(data3, 2,10);
	a.new_node(data3, 9,11);

	a.print_tree(0);
	
	cout << a.get_deep(2)<<"\n";
	a.change_father(2, 3);

	a.print_tree(0);
	cout << a.get_deep(2) << "\n";;

	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start_tik;
	cout << "Elapsed time: " << elapsed.count() << " s\n";

}*/