from City import City
from Ridge import Ridge
import math

# build cities list
def build_cities(cities_array:list):
    while(1):
        try:
            # recover from file until EOF
            line = input()
            id, x, y = line.split(";")
            cities_array.append(City(id, x, y))
        except:
            break

def build_ants_first_position(cities_array:list) -> list:
    ants = []
    for i in cities_array:
        ants.append([i])
    return ants

def distance(x1:float,x2:float,y1:float,y2:float) -> float:
    return math.sqrt((x1-x2)**2 + (y1-y2)**2)

def build_ridges(cities_array:list) -> list:
    # to fix
    ridges = []
    for i in range(1,len(cities_array) - 2,1):
        for j in range(1,len(cities_array) - 2,1):
            if i != j:
                ridges.append(Ridge(i, j, 1, distance(cities_array[i].get_x(), cities_array[j].get_x(), cities_array[i].get_y(), cities_array[j].get_y())))
    return ridges

def main():
    # variables
    cities_array = []
    ants = []
    ridges = []
    
    # init cities
    build_cities(cities_array)
    
    # init ants
    ants = build_ants_first_position(cities_array)

    # init ridges, at first pheromone in 1
    ridges = build_ridges(cities_array)

    for ridge in ridges:
        print(ridge)

    # for ant in ants:
    #     for city in ant:
    #         print(city.id)
    # for i in cities_array:
    #     print(i)

if __name__ == "__main__":
    main()