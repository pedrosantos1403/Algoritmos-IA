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

    //cout << name << "  ->  Node created" << endl;
    Node* node = new Node(name);
    return node;

}

void fillCityWithBuffer(char *city, char *buffer);
int getDistanceFromBuffer(int index, char *buffer);
void deleteNode(Node* node);

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
                //printf("%s;%s;%d\n", city_origin, city_target, distance);
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
                //cout << "H( " << city_origin << " ) : " << distance << endl;
                auto it_first = nodes.find(city_origin);
                it_first->second->straight_line_to_bucarest = distance;

                ////////////////////////////////////////////////////////////////////////////
                /*
                    There it is, here we can get all info about heuristics
                */
                //printf("%s ate %s sao %d\n", city_origin, city_target, distance);
                //printf("%s;%d\n", city_origin, distance);
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
    int smaller_f = INT_MAX; // Variável para salvar o menor f dentre os nós que foram abertos
    bool isDestiny = false;

    
    map<string, pair<Node*, int /*G(x)*/>> opened_nodes;  // Ex: Arad : {Arad Node Object, F(Arad)}
    list<string> cities; // Salvar as cidades que podem ser visitadas a partir da cidade atual

    // Salvando configurações iniciais de Arad
    auto it_Arad = nodes.find("Arad");
    string city = "Arad"; it_Arad->second->visited = true; // Salvando Arad como a cidade de partida
    it_Arad->second->f_x = it_Arad->second->straight_line_to_bucarest; // Setando o F(x) de Arad que é igual a H(x)
    opened_nodes["Arad"] = pair<Node*, int>(it_Arad->second, it_Arad->second->f_x); // Salvando Arad em opened_nodes

    string destiny = "Bucareste";
    string next_city;

    while(!isDestiny){

        auto present_city = nodes.find(city);
        auto present_city_connections = present_city->second->conections;
        smaller_f = INT_MAX;

        // Printando as conexões da cidade atual
        cout << "As conexoes de " << city << " sao: ";
        for (auto it = present_city_connections.begin(); it != present_city_connections.end(); ++it){
            cout << it->first->name << " | ";
        }

        cout << endl;


        // Adiconando as conexões da cidade atual em um map de nós abertos junto com o F(x) de cada uma das conexões
        for (auto it = present_city_connections.begin(); it != present_city_connections.end(); ++it){

            //TO-DO: Acrescentar lógica de salvar o Nó anterior de cada Nó filho
            it->first->previous_node = present_city->second->name;
            
            // Calculando G(x) e F(x) de cada Nó
            it->first->g_x = it->second /*G(x)*/ + present_city->second->g_x /*G(x) do Nó anterior*/;
            it->first->f_x /*F(x)*/ = it->first->g_x /*G(x)*/ + it->first->straight_line_to_bucarest /*H(x)*/;
            cout << "F( " << it->first->name << " ) : " << it->first->g_x << " + " << it->first->straight_line_to_bucarest << " = " << it->first->f_x << endl;

            // Para cada Nó aberto será salvo seu nome junto com seu objeto e seu F(x)
            if(it->first->visited == false){
                opened_nodes.insert(pair<string, pair<Node*,int>>(it->first->name, pair<Node*, int>(it->first, it->first->f_x)));
            }

        }

        cout << "Estou em " << city << " e posso ir para :" << endl /*Todos os nós que estão em opened_nodes que ainda não foram visitados*/;

        for (auto it = opened_nodes.begin(); it != opened_nodes.end(); ++it){
            if(it->second.first->visited == false) { cout << it->second.first->name /*Nome do Nó*/ << " com F(x) = " << it->second.first->f_x << endl; }
        }

        cout << endl;
        
        // Percorrer o map opened_nodes e checar qual o Nó com menor F(x) -> Esse será o próximo Nó a ser visitado
        for (auto it = opened_nodes.begin(); it != opened_nodes.end(); ++it){

            if((it->second.first->f_x < smaller_f) && (it->second.first->visited == false)){

                smaller_f = it->second.first->f_x;

                // Salvando o nome do Nó com menor F(x)
                city = it->first;

            }

        }

        // Printando o próximo Nó a ser visitado -> O Nó com menor F(x) dentre os nós abertos
        cout << "Escolhi ir para " << city << " com F(x) = " << smaller_f << endl;
        //cout << "\n" << "\n";

        // Agora já sabemos qual Nó será o próximo Nó a ser visitado -> Logo, marcamos esse Nó como visitado
        auto next_node = opened_nodes.find(city);
        next_node->second.first->visited = true;

        // Testa se eu cheguei em Bucareste
        if(city == "Bucareste"){

            isDestiny = true;

            // TO-DO: Arrumar estrutura de dados que irá salvar o caminho ótimo
            // Percorro todos os Nós visitados para montar o caminho mais rápido para ser printado
            bool complete_way = false;
            auto city_it = opened_nodes.find("Bucareste");
            stack<string> fastest_way;
            fastest_way.push(city); // Adicionando bucareste na pilha

            ///////////////////////////////////////////////////////////////////////////////////
            // debug mode
            
            /*
                best way
                Arad | Sibiu | Rimnicu Vilcea | Pitesti | Bucareste
            */ 
            // cout << "city_it->first: " << city_it->first << endl;
            // while(complete_way == false){
            for(int i = 0; i<6; i++){
                string previous_node = city_it->second.first->previous_node;
                fastest_way.push(previous_node);
                city_it = opened_nodes.find(previous_node);
                
                // Percorrer o map opened_nodes e ver o que tem 
                // for (auto it = opened_nodes.begin(); it != opened_nodes.end(); ++it){
                //     cout << "it->second.first->previous_node " << it->second.first->previous_node << endl;
                // }
                // cout << endl;
                // cout << "previus_node: " << previous_node << endl;
                // cout << "city_it->first: " << city_it->first << endl;
                // cout << "city_it->second.first->previous_node: " << city_it->second.first->previous_node << endl;
                if(city_it->second.first->previous_node == "Arad"){
                    complete_way = true;
                }
                
                // city_it = opened_nodes.find(city_it->second.first->previous_node);

                /*
                    A impressao que tenho eh que falta informacao sobre o anterior do anterior
                    Desse jeito estamos entrando em loop

                    tem que fazer alguma coisa antes com city_it para que o anterior
                    de Rimnicu Vilcea seja Sibiu e nao Pitesti
                */
            }

            ///////////////////////////////////////////////////////////////////////////////////

            // Printando o caminho ótimo
            cout << "O melhor caminho para chegar em Bucareste: ";
            while (!fastest_way.empty()){
                cout << fastest_way.top() << " | ";
                fastest_way.pop();
            }

            cout << endl;

        }

        // O fato de sempre escolher o Nó com o menor F(x) dentre os Nós abertos para ser o próximo Nó visitado, garante que
        // se eu eventualmente chegar em Bucareste eu vou chegar pelo melhor caminho possível (Caminho Ótimo)

        // Revisar se o map opened_nodes precisa realmente do pair uma vez que F(x) está sendo salvo como atributo do objeto Node
        // Revisar se estamos usando estruturas de dados a mais do que o necessário

    }


    // Deletando os nós para liberar o espaço alocado na memória
    for(auto it = nodes.begin(); it != nodes.end(); ++it){
        deleteNode(it->second);
    }

    return 0;

}

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

void deleteNode(Node* node){
    delete node;
}