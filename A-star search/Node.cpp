#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:

        string name;
        int straight_line_to_bucarest;
        bool visited;
        set<pair<Node* /*Neighbour Node*/, int /*Distance*/>> conections;


        Node(string str){
            name = str;
            visited = false;
        }

        void addNode(Node* node, int dist){
            conections.insert(make_pair(node, dist));
        }

};