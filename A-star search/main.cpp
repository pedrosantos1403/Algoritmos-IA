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

Node* createNode(string name){

    cout << name << "  ->  Node created" << endl;
    Node* node = new Node(name);
    return node;

}

void fillCityWithBuffer(char *city, char *buffer);
int getDistanceFromBuffer(int index, char *buffer);

int main(int argc, char* argv[]){
    //variables
    char graph_file_name[] = "Grafo.txt";
    char heuristics_file_name[]  = "Heuristica.txt";
    FILE *file_pointer;
    char next_ch;
    char city_origin[BUFFER_SIZE] = "______________", city_target[BUFFER_SIZE] = "______________", input_buffer[BUFFER_SIZE] = "______________";
    int distance = 0;
    int index = 0, state = READ_ORIGIN_CITY_STATE;
    map<string /*City Name*/, Node* /*City Node*/> nodes;

    //graph file
    file_pointer = fopen(graph_file_name, "r");
    if(file_pointer == NULL)
    {
        printf("Impossivel abrir o arquivo %s", graph_file_name);
    }
    else
    {
        //handle input

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

                ////////////////////////////////////////////////////////////////////////////
                /*
                    There it is, here we can get all info about roads
                */
                // printf("%s;%s;%d\n", city_origin, city_target, distance);
                ////////////////////////////////////////////////////////////////////////////

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

    //heuristics file
    file_pointer = fopen(heuristics_file_name, "r");
    if(file_pointer == NULL)
    {
        printf("Impossivel abrir o arquivo %s", heuristics_file_name);
    }
    else
    {
        //handle input

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
                cout << "H( " << city_origin << " ) : " << distance << endl;
                auto it_first = nodes.find(city_origin);
                it_first->second->straight_line_to_bucarest = distance;

                ////////////////////////////////////////////////////////////////////////////
                /*
                    There it is, here we can get all info about heuristics
                */
                // printf("%s ate %s sao %d\n", city_origin, city_target, distance);
                // printf("%s;%d\n", city_origin, distance);
                ////////////////////////////////////////////////////////////////////////////

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

    // Printar todas as conexoes de cada cidade para checar se o salvamento das conexoes está correto


    // A* Search Logic

    int node_g = 0 /*Gasto*/, node_h = 0; /*Heurística*/;
    int node_f = 0; // g + h -> Disntacia entre cidade origem e cidade alvo + distancia da cidade alvo até Bucareste
    int smaller_f = 0; // Variável para salvar o menor f dentre os nós que foram abertos
    bool isDestiny = false;

    vector<pair<Node*, int /*node_f*/>> opened_nodes;
    list<string> cities; // Salvar as cidades que podem ser visitadas a partir da cidade atual

    auto it = nodes.find("Arad");
    string city = "Arad"; it->second->visited = true; // Salvando Arad como a cidade de partida
    string destiny = "Bucareste";
    string next_city;


    //while(!isDestiny){

        // Abrir todos os nós a partir da cidade atual
        // Salvar todos os Nós abertos em uma vetor
        // Percorrer esse vetor para checar qual nó possui o menor valor de f -> Esse nó será o próximo a ser visitado
        auto present_city = nodes.find(city);
        auto present_city_connections = present_city->second->conections;

        cout << "Estou em " << city << " e posso ir para ";
        for(auto it = present_city_connections.begin(); it != present_city_connections.end(); ++it){
            cout << it->first->name << " | ";
        }

        cout << endl;

        for (auto it = present_city_connections.begin(); it != present_city_connections.end(); ++it){
            
            // Calculando f para cada Nó aberto
            node_f = it->second + it->first->straight_line_to_bucarest;
            cout << "F( " << it->first->name << " ) : " << it->second << " + " << it->first->straight_line_to_bucarest << " = " << node_f << endl;

            // Salvando as conexoes da cidade atual que ainda náo foram visitadas em um vetor de Nós abertos
            if(it->first->visited == false){
                opened_nodes.push_back(make_pair(it->first, node_f));
            }

        }



        
        // Percorrer o vetor de nós abertos e checar qual o Nó com menor f -> Esse será o próximo Nó a ser visitado
        smaller_f = opened_nodes[0].second;
        for (int i = 1; i < opened_nodes.size(); i++){

            if(opened_nodes[i].second < smaller_f && !(opened_nodes[i].first->visited)){

                smaller_f = opened_nodes[i].second;

                // Salvando o nome do Nó com menor f
                city = opened_nodes[i].first->name;

            }

        }

        // Agora já sabemos qual Nó será o próximo Nó a ser visitado -> Logo, marcamos esse Nó como visitado
        auto next_node = nodes.find(city);
        next_node->second->visited = true;

        cout << "Escolhi ir para " << city << " com F(x) = " << smaller_f << endl;

        // Somar o custo para chegar no nó com a heurística do nó (Comparar essa soma entre todos os nós)
        // Andar para o nó com menor custo f
        // Checar se chegamos no destino
    //}


    cout << "Fim do teste!!!" << endl;


    return 0;

}

void fillCityWithBuffer(char *city, char *buffer){
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