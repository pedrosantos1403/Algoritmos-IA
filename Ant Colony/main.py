from City import City
from Ridge import Ridge
import math
import csv
import numpy as np

# Variáveis
cities_array = []
ants = []
ridges = np.empty((33, 33), dtype=Ridge) # Vai da cidade 0 até a cidade 32
 
# Construindo o vetor de cidades, e instanciando os objetos City para salvar as coordenadas de cada cidade
def build_cities():
    global cities_array
    with open('C:\\Users\\pedro\\OneDrive\\Documentos\\CEFETMG\\2023.1\\Inteligência Artificial\\Laboratório\\AI-Algorithms\\Ant Colony\\Colonia.csv', "r") as csvfile:
        filereader = csv.reader(csvfile, delimiter=';')
        next(filereader, None)
        for row in filereader:
            id, x, y = row
            id = int(id)
            x = float(x)
            y = float(y)
            cities_array.append(City(id, x, y))


# Construindo o vetor de formigas, cada formiga começa em uma cidade diferente
def build_ants_initial_position() -> list:
    global ants, cities_array
    for i in cities_array:
        ants.append([i])


# Cálculo da distância entre duas cidades usando função euclidiana
def distance(x1:float,x2:float,y1:float,y2:float) -> float:
    return math.sqrt((x1-x2)**2 + (y1-y2)**2)


# Criando uma matriz de arestas para salvar todas as distâncias entre todas as cidades
def build_ridges() -> list:
    global ridges, cities_array

    for i in range(len(ridges)):
        for j in range(len(ridges)):
            if i != j:
                ridges[i][j] = Ridge(i, j, 1, distance(cities_array[i].get_x(), cities_array[j].get_x(), cities_array[i].get_y(), cities_array[j].get_y()))
            else:
                ridges[i][j] = Ridge(i, j, 1, 0)


def main():

    global ridges, cities_array, ants

    build_cities()

    # DEBUG
    # for i in range(len(cities_array)):
    #     print(cities_array[i], type(cities_array[i]))

    build_ants_initial_position()

    # DEBUG
    # for i in range(len(ants)):
    #     for j in range(len(ants[i])):
    #         print(ants[i][j].id, "-")

    build_ridges()

    # DEBUG
    # for i in range(len(ridges)):
    #     for j in range(len(ridges)):
    #         print(ridges[i][j])


if __name__ == "__main__":
    main()






























if __name__ == "__main__":
    main()