import random
import math
import numpy as np

populations = []
best = -10000

# Function to create the initial population
def populating():
    global populations
    populations = ([[random.uniform(0,10) for x in range(2)] for i in range(100)])
    #print(len(populations))
    #print(populations)

# F(X)
def f_X(x1,x2):
    return math.sqrt(x1) * math.sin(x1) * math.sqrt(x2) * math.sin(x2) + 10

# Fitness Function
def fitness_score() :
    global populations
    global best
    fit_value = []

    # Calculating the fitness for each individual
    for i in range(100) :
        chromosome_value = f_X(populations[i][0], populations[i][1])
        fit_value.append(chromosome_value)

    # Sorting the fit values to get the best individual
    fit_value.sort(reverse = True)
    best = fit_value[0]

    print(len(fit_value))
    print(best) # Lembrar que o valor está sendo printado somando +10

    

def main():
    populating()
    fitness_score()

if __name__ == "__main__":
    main()