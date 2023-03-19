#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 15

int main(int argc, char* argv[]){
    //variables
    FILE *file_pointer;
    char next_ch;
    char city_origin[BUFFER_SIZE] = "______________", city_target[BUFFER_SIZE] = "______________", input_buffer[BUFFER_SIZE] = "______________";
    int distance = 0;
    int index = 0, factor = 1;

    //get file names by terminal
    if(argc != 3)
    {
        printf("Usage: %s [Grafo.txt] [Heuristica.txt]\n", argv[0]);
        exit(1);
    }

    //graph file
    file_pointer = fopen(argv[1], "r");
    if(file_pointer == NULL)
    {
        printf("Impossivel abrir o arquivo %s", argv[1]);
    }
    else
    {
        //handle input

        //find new roads
        while((next_ch = fgetc(file_pointer)) != -1)
        {
            //get origin city
            //get target city
            //get distance
        }
    }
    fclose(file_pointer);

    //cleaning variables
    distance = 0;
    factor = 1;
    index = 0;
    sprintf(city_origin, "______________\0");
    sprintf(city_target, "______________\0");
    sprintf(input_buffer, "______________\0");

    //heuristics file
    file_pointer = fopen(argv[2], "r");
    if(file_pointer == NULL)
    {
        printf("Impossivel abrir o arquivo %s", argv[2]);
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
                while(city_origin[index] != '_')
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
                //printf("%s ate %s sao %dkm\n", city_origin, city_target, distance);

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