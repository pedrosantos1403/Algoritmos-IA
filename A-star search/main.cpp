#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 15
#define READ_ORIGIN_CITY_STATE 0
#define READ_TARGET_CITY_STATE 1

int main(int argc, char* argv[]){
    //variables
    char graph_file_name[] = "Grafo.txt";
    char heuristics_file_name[]  = "Heuristica.txt";
    FILE *file_pointer;
    char next_ch;
    char city_origin[BUFFER_SIZE] = "______________", city_target[BUFFER_SIZE] = "______________", input_buffer[BUFFER_SIZE] = "______________";
    int distance = 0;
    int index = 0, factor = 1, state = READ_ORIGIN_CITY_STATE;

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

}