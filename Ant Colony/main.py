from City import City
from Ridge import Ridge
import math
import csv
import numpy as np

# Variáveis
alpha = 1
beta = 1
cities_array = []
ants = []
ridges = np.empty((6, 6), dtype=Ridge) # Vai da cidade 0 até a cidade 32
 
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
def build_ridges():
    global ridges, cities_array

    for i in range(len(ridges)):
        for j in range(len(ridges)):
            if i != j:
                ridges[i][j] = Ridge(i, j, 1, distance(cities_array[i].get_x(), cities_array[j].get_x(), cities_array[i].get_y(), cities_array[j].get_y()))
            else:
                ridges[i][j] = Ridge(i, j, 1, 0)


# Calcular a probabilidade de cada formiga ir para cada cidade
def propability(possible_cities:list, ant_cities:list):

    # Criar uma lista de pheromones para calcular o somatório
    global alpha, beta
    return ((pheromone)**alpha) * ((heuristic)**beta) / sum


# Calcular a próxima cidade a ser visitada por cada formiga
def next_city():
    global ants, cities_array, ridges
    possible_cities = []

    # Probability deve receber a lista de possíveis cidades a serem visitadas pela formiga e a lista das cidade já visitadas

    for i in range(len(ants)): # Percorrendo o vetor de formigas
        possible_cities.clear()
        for j in range(len(cities_array)): # Percorrendo o vetor de cidades para cada formiga
            if cities_array[j] not in ants[i]: # Checando se a cidade j já foi visitada pela formiga i
                possible_cities.append(cities_array[j]) # Adicionando a cidade na lista de possíveis cidades caso ela não tenha sido visitada
        # propability(possible_cities, ants[i])
        # for i in range(len(possible_cities)):
        #     print(possible_cities[i].get_id(), end=" ")
        # print("\n")




        


def main():

    global ridges, cities_array, ants

    # Limpando as variáveis
    cities_array.clear(), ants.clear()

    # Checando o conteúdo das variáveis
    print("hello")
    #print(ants)
    #print(ridges)

    # Construindo o vetor de cidades
    # build_cities()

    # DEBUG
    #for i in range(len(cities_array)):
     #   print(cities_array[i])

    #build_ants_initial_position()

    # DEBUG
    # for i in range(len(ants)):
    #     for j in range(len(ants[i])):
    #         print(ants[i][j].id, "-")

    #build_ridges()

    # DEBUG
    # for i in range(len(ridges)):
    #     for j in range(len(ridges)):
    #         print(ridges[i][j])
    # print(ridges[30][14])

    #next_city()


if __name__ == "__main__":
    main()






























if __name__ == "__main__":
    main()