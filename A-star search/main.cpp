#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Node.cpp"

#define BUFFER_SIZE 15
#define READ_ORIGIN_CITY_STATE 0
#define READ_TARGET_CITY_STATE 1

Node* createNode(string name){

    Node* node = new Node(name);
    return node;

}

int main(int argc, char* argv[]){

    //variables
    char graph_file_name[] = "Grafo.txt";
    char heuristics_file_name[]  = "Heuristica.txt";
    FILE *file_pointer;
    char next_ch;
    char city_origin[BUFFER_SIZE] = "______________", city_target[BUFFER_SIZE] = "______________", input_buffer[BUFFER_SIZE] = "______________";
    int distance = 0;
    int index = 0, factor = 1, state = READ_ORIGIN_CITY_STATE;
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
            if(next_ch == ';' && state == 0)
            {
                //origin city ready to save
                sprintf(city_origin, "%s", input_buffer);

                //cleaning input buffer and index
                index = 0;
                sprintf(input_buffer, "______________\0");

                //fixing end of string in city_origin
                while(city_origin[index] != '_' && city_origin[index] != '\0')
                {
                    index++;
                }
                city_origin[index] = '\0';
                index = 0;

                //change state
                state = READ_TARGET_CITY_STATE;
            }
            else if(next_ch == ';' && state == 1)
            {
                //target city ready to save
                sprintf(city_target, "%s", input_buffer);

                //cleaning input buffer and index
                index = 0;
                sprintf(input_buffer, "______________\0");

                //fixing end of string in city_target
                while(city_target[index] != '_' && city_target[index] != '\0')
                {
                    index++;
                }
                city_target[index] = '\0';
                index = 0;

                //change state
                state = READ_ORIGIN_CITY_STATE;
            }
            else if(next_ch == '\n'){
                //distance ready to save
                for(index -= 1; index >= 0; index--)
                {
                    distance += (input_buffer[index] - 48)*factor;
                    factor *= 10;
                }

                //cleaning input buffer
                factor = 1;
                index = 0;
                sprintf(input_buffer, "______________\0");

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
                printf("%s ate %s sao %dkm\n", city_origin, city_target, distance);
                ////////////////////////////////////////////////////////////////////////////

                //cleaning distance and city origin
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

    //cleaning variables
    printf("\n");
    distance = 0;
    factor = 1;
    index = 0;
    sprintf(city_origin, "______________\0");
    sprintf(city_target, "______________\0");
    sprintf(input_buffer, "______________\0");



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
                sprintf(city_origin, "%s", input_buffer);

                //cleaning input buffer and index
                index = 0;
                sprintf(input_buffer, "______________\0");

                //fixing end of string in city_origin
                while(city_origin[index] != '_' && city_origin[index] != '\0')
                {
                    index++;
                }
                city_origin[index] = '\0';
                index = 0;
            }
            else if(next_ch == '\n')
            {
                //distance ready to save
                for(index -= 1; index >= 0; index--)
                {
                    distance += (input_buffer[index] - 48)*factor;
                    factor *= 10;
                }

                //cleaning input buffer
                factor = 1;
                index = 0;
                sprintf(input_buffer, "______________\0");

                //save origin city and distance in node
                auto it_first = nodes.find(city_origin);
                it_first->second->straight_line_to_bucarest = distance;

                ////////////////////////////////////////////////////////////////////////////
                /*
                    There it is, here we can get all info about heuristics
                */
                printf("%s ate %s sao %dkm\n", city_origin, city_target, distance);
                ////////////////////////////////////////////////////////////////////////////

                //cleaning distance and city origin
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

        return 0;
    }


    // A* Search Logic

    int node_g = 0 /*Gasto*/, node_h = 0; /*Heurística*/;
    int node_f = 0; // g + h -> Disntacia entre cidade origem e cidade alvo + distancia da cidade alvo até Bucareste
    bool isDestiny = false;

    vector<pair<Node*, int /*node_f*/>> opened_nodes;
    list<string> cities; // Salvar as cidades que podem ser visitadas a partir da cidade atual

    auto it = nodes.find("Arad");
    string city = "Arad"; it->second->visited = true; // Salvando Arad como a cidade de partida
    string destiny = "Bucareste";
    string next_city;


    while(isDestiny == false){

        // Abrir todos os nós a partir da cidade atual
        // Salvar todos os Nós abertos em uma vetor
        // Percorrer esse vetor para checar qual nó possui o menor valor de f -> Esse nó será o próximo a ser visitado
        auto present_city = nodes.find(city);
        auto present_city_connections = present_city->second->conections;
        int smaller_dist = 10000;

        for (auto it = present_city_connections.begin(); it != present_city_connections.end(); ++it){
            
            // Calculando f para cada Nó aberto
            node_f = it->second + it->first->straight_line_to_bucarest;
            // Salvando as conexoes da cidade atual que ainda náo foram visitadas em um vetor de Nós abertos
            if(it->first->visited == false){
                opened_nodes.push_back(make_pair(it->first, node_f));
            }

        }

        
        // Percorrer o vetor de nós abertos e checar qual o Nó com menor f -> Esse será o próximo Nó a ser visitado
        for (int i = 0; i < opened_nodes.size(); i++){}

        // Quando eu decidir a próxima cidade a ser visitada eu devo marcar ela como visitada visited = true

        // Somar o custo para chegar no nó com a heurística do nó (Comparar essa soma entre todos os nós)
        // Andar para o nó com menor custo f
        // Checar se chegamos no destino
    }

}