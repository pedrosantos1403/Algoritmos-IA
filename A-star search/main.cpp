#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Node.cpp"

#define BUFFER_SIZE 15
#define READ_ORIGIN_CITY_STATE 0
#define READ_TARGET_CITY_STATE 1

using namespace std;

Node* createNode(string name);
void fillCityWithBuffer(char *city, char *buffer);
int getDistanceFromBuffer(int index, char *buffer);
void deleteNode(Node* node);

int main(int argc, char* argv[]){

    // Variables
    char graph_file_name[] = "Grafo.txt";
    char heuristics_file_name[]  = "Heuristica.txt";
    char next_ch;
    char city_origin[BUFFER_SIZE] = "______________", city_target[BUFFER_SIZE] = "______________", input_buffer[BUFFER_SIZE] = "______________";
    int distance = 0;
    int index = 0, state = READ_ORIGIN_CITY_STATE;
    FILE *file_pointer;
    map<string /*City Name*/, Node* /*City Node*/> nodes;

    // Grafos.txt
    file_pointer = fopen(graph_file_name, "r");
    if(file_pointer == NULL)
    {
        printf("Impossivel abrir o arquivo %s", graph_file_name);
    }
    else
    {
        //find new roads
        while((next_ch = fgetc(file_pointer)) != -1)
        {
            if(next_ch == ';' && state == READ_ORIGIN_CITY_STATE)
            {
                //origin city ready to save
                fillCityWithBuffer(city_origin, input_buffer);

                //change state and clear index
                state = READ_TARGET_CITY_STATE;
                index = 0;
            }
            else if(next_ch == ';' && state == READ_TARGET_CITY_STATE)
            {
                //target city ready to save
                fillCityWithBuffer(city_target, input_buffer);

                //change state and clear index
                state = READ_ORIGIN_CITY_STATE;
                index = 0;
            }
            else if(next_ch == '\n'){
                //distance ready to save
                distance = getDistanceFromBuffer(index, input_buffer);

                //save origin city, target city and distance in node
                if(nodes.find(city_origin) == nodes.end()){ // Checking if origin city already exists in a Node, if not, create a Node for this city
            
                    nodes.insert(pair<string, Node*>(city_origin, createNode(city_origin)));

                }
                if(nodes.find(city_target) == nodes.end()){ // Checking if target city already exists in a Node, if not, create a Node for this city

                    nodes.insert(pair<string, Node*>(city_target, createNode(city_target)));

                }

                // Adding conections between cities
                auto it_first = nodes.find(city_origin);
                auto it_second = nodes.find(city_target);

                it_first->second->conections.insert(make_pair(it_second->second, distance));
                it_second->second->conections.insert(make_pair(it_first->second, distance));

                //cleaning index, distance, city origin and city target
                index = 0;
                distance = 0;
                sprintf(city_origin, "______________\0");
                sprintf(city_target, "______________\0");
            }
            else
            {
                //save the next character from file in input_buffer
                input_buffer[index] = next_ch;
                index++;
            }
        }
    }
    fclose(file_pointer);

    // Heurística.txt
    file_pointer = fopen(heuristics_file_name, "r");
    if(file_pointer == NULL)
    {
        printf("Impossivel abrir o arquivo %s", heuristics_file_name);
    }
    else
    {
        //in heuristics, target city is always Bucareste
        sprintf(city_target, "Bucareste");

        //find the origin city
        while((next_ch = fgetc(file_pointer)) != -1)
        {
            if(next_ch == ';')
            {
                //origin city ready to save
                fillCityWithBuffer(city_origin, input_buffer);

                //cleaning index
                index = 0;
            }
            else if(next_ch == '\n')
            {
                //distance ready to save
                distance = getDistanceFromBuffer(index, input_buffer);

                //save origin city and distance in node
                auto it_first = nodes.find(city_origin);
                it_first->second->straight_line_to_bucarest = distance;

                //cleaning index, distance and city origin
                index = 0;
                distance = 0;
                sprintf(city_origin, "______________\0");
            }
            else
            {
                //save the next character from file in input_buffer
                input_buffer[index] = next_ch;
                index++;
            }
        }
        fclose(file_pointer);

    }

    // A* Search Logic
    int smaller_f = INT_MAX; // Variable to store the smaller F(x) value
    bool isDestiny = false;
    string destiny = "Bucareste";
    string next_city;
    map<string /*City Name*/, Node*> opened_nodes;

    // Saving Arad's info
    auto it_Arad = nodes.find("Arad");
    string city = "Arad"; it_Arad->second->visited = true; // Savaing Arad as the origin city
    it_Arad->second->f_x = it_Arad->second->straight_line_to_bucarest; // Setting Arad's F(x) = H(x)
    opened_nodes["Arad"] = it_Arad->second; // Saving Arad in opened_nodes

    // While I have not reached Bucareste using the best way possible
    while(!isDestiny){

        smaller_f = INT_MAX;
        auto present_city = nodes.find(city);
        auto present_city_connections = present_city->second->conections; // Getting all the conections of the present city

        // Adding the conections of the present city in the opened_nodes map
        for (auto it = present_city_connections.begin(); it != present_city_connections.end(); ++it){

            // Saving the previous city visited
            if(it->first->visited == false) { it->first->previous_node = present_city->second->name; }
            
            // Calculating G(x) and F(x) of each node
            it->first->g_x = it->second /*G(x)*/ + present_city->second->g_x /*G(x) of the previous node*/;
            it->first->f_x /*F(x)*/ = it->first->g_x /*G(x)*/ + it->first->straight_line_to_bucarest /*H(x)*/;

            // Inserting the opened nodes in the map
            if(it->first->visited == false){
                opened_nodes.insert(pair<string, Node*>(it->first->name, it->first));
            }

        }

        cout << "Estou em " << city << " e posso ir para :" << endl;

        for (auto it = opened_nodes.begin(); it != opened_nodes.end(); ++it){
            if(it->second->visited == false) { cout << it->second->name << " com F(x) = " << it->second->f_x << endl; }
        }

        cout << endl << "De " << city << " escolhi ir para: ";
        
        // Finding the opened node with the smaller F(x)
        for (auto it = opened_nodes.begin(); it != opened_nodes.end(); ++it){
            if((it->second->f_x < smaller_f) && (it->second->visited == false)){
                smaller_f = it->second->f_x;
                city = it->first;
            }
        }

        // Printing next city to be visited
        cout << city << endl << endl;

        // Marking the next city as visited
        auto next_node = opened_nodes.find(city);
        next_node->second->visited = true;

        // Test if we have reached Bucareste
        if(city == "Bucareste"){

            cout << "Cheguei em Buscareste pelo melhor caminho!!!" << endl << endl;

            isDestiny = true;

            // Logic to print the fastest way
            bool complete_way = false;
            auto city_it = opened_nodes.find("Bucareste");
            int final_cost = city_it->second->f_x;
            stack<string> fastest_way;
            string previous_node;
            fastest_way.push(city); // Adding Bucareste in the stack

            while(complete_way == false){

                previous_node = city_it->second->previous_node;
                fastest_way.push(previous_node);
                city_it = opened_nodes.find(previous_node);

                if(city_it->second->previous_node == "Arad"){
                    fastest_way.push(city_it->second->previous_node);
                    complete_way = true;
                }
                
            }

            // Printing the best way
            cout << "Melhor Caminho: ";
            while (!fastest_way.empty()){
                if(fastest_way.top() == "Bucareste") { cout << fastest_way.top() << " ( Custo = " << final_cost << " )"<< endl; }
                else { cout << fastest_way.top() << " -> "; }
                fastest_way.pop();
            }

            cout << endl;

        }

    }


    // Deleting the nodes to free the memory
    for(auto it = nodes.begin(); it != nodes.end(); ++it){
        deleteNode(it->second);
    }

    return 0;

}

// Methods Implementation
void fillCityWithBuffer(char *city, char *buffer){ // Can be 
        //variables
        int index = 0;

        //city ready to save
        sprintf(city, "%s", buffer);

        //cleaning buffer
        sprintf(buffer, "______________\0");

        //fixing end of string in city
        while(city[index] != '_' && city[index] != '\0')
        {
            index++;
        }
        city[index] = '\0';
}

int getDistanceFromBuffer(int index, char *buffer){
    //variables
    int distance = 0;
    int factor = 1;

    //to integer
    for(index -= 1; index >= 0; index--)
    {
        distance += (buffer[index] - 48)*factor;
        factor *= 10;
    }
    
    //cleaning buffer
    sprintf(buffer, "______________\0");
    return distance;
}

Node* createNode(string name){
    Node* node = new Node(name);
    return node;
}

void deleteNode(Node* node){
    delete node;
}