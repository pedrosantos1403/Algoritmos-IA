#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:

        string name;
        string previous_node; // Salva Nó por onde eu cheguei

        int straight_line_to_bucarest;
        int f_x;
        int g_x;

        bool visited;

        set<pair<Node* /*Neighbour Node*/, int /*Distance*/>> conections;

        Node(string str){
            name = str;
            visited = false;
            previous_node = " ";
            f_x = 0;
            g_x = 0;
        }

        void addNode(Node* node, int dist){
            conections.insert(make_pair(node, dist));
        }

};