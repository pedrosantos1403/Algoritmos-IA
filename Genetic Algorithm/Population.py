import random
import math
import numpy as np
import statistics as st
import matplotlib.pyplot as plt

SIZE_POPULATION = 50

taxa_crossover = 0.2
taxa_mutacao = 0.2

populations = []
new_population = []
best_individuals = [] # Saves best individual of each popultion
worst_individuals = [] # Saves worts individuals of each population
mean_individuals = [] # Saves the mean individuals of each population
fit_value = [] # Fitness Values
fit_value_sorted = [] # Fitness Values Sorted
fit_add = [] # Fitness sum
fit_parents = [] # Selected parents

def populating():
    global populations
    populations = ([[random.uniform(0,10) for x in range(2)] for i in range(SIZE_POPULATION)])

def f_X(x1,x2):
    return math.sqrt(x1) * math.sin(x1) * math.sqrt(x2) * math.sin(x2) + 10

def fitness_score():
    global populations, new_population
    global fit_value, fit_add, fit_parents, fit_value_sorted, best_individuals, mean_individuals

    # Calculating the fitness for each individual
    for i in range(SIZE_POPULATION) :
        chromosome_value = f_X(populations[i][0], populations[i][1])
        fit_value.append(chromosome_value)

    # Sorting the fit_value vector to get the best and worst individual of the population
    fit_value_sorted = fit_value.copy()
    fit_value_sorted.sort(reverse=True)

    # Saving the best individual of the population
    best_individuals.append(fit_value_sorted[0])

    # Saving the best individual of the population
    worst_individuals.append(fit_value_sorted[-1])

    # Saving the mean value of the population
    mean_individuals.append(st.mean(fit_value))

    # Building the sum vector
    for i in range(SIZE_POPULATION):
        if i == 0:
            fit_add.append(fit_value[i])  
        else:
            fit_add.append(fit_value[i] + fit_add[i-1])

    # Building the vector of selected parents
    for i in range(SIZE_POPULATION):
        fit_parent_number = random.randint(0, math.floor(fit_add[-1]))

        for j in range(SIZE_POPULATION):
            if fit_parent_number < fit_add[j]:
                fit_parents.append(j)
                break

def crossover(p1:list , p2:list):

    if random.uniform(0,1) > taxa_crossover:
        return p1, p2
    
    else:
        a = random.uniform(0,1)

        # Defining firts son
        new_x1 = a * p1[0] + (1 - a) * p2[0]
        new_x2 = a * p1[1] + (1 - a) * p2[1]
        o1 = [new_x1, new_x2]

        # Defining second son
        new_x1 = a * p2[0] + (1 - a) * p1[0]
        new_x2 = a * p2[1] + (1 - a) * p1[1]
        o2 = [new_x1, new_x2]

        return o1, o2

def mutation():
    global new_population

    for i in range(SIZE_POPULATION):
        for j in range(2):
            if random.uniform(0,1) < taxa_mutacao:
                # Mutating
                new_population[i][j] = random.uniform(new_population[i][j]*(1-taxa_mutacao),new_population[i][j]*(1+taxa_mutacao))
                
                # Cehcking if the mutated value is between 0 and 10
                while new_population[i][j] > 10 or new_population[i][j] < 0:
                    new_population[i][j] = random.uniform(new_population[i][j]*(1-taxa_mutacao),new_population[i][j]*(1+taxa_mutacao))
                
            else:
                # Don't mutate
                pass



def main():

    global populations, new_population
    global best_individuals, worst_individuals, fit_parents

    # Creating the initial population
    populating()

    for j in range (30):

         # Applying the fitness function
        fitness_score()

        # Creating the new population and applying crossover -> Some parents will do crossover and some will not
        for i in range(0, SIZE_POPULATION - 1, 2):
            new_population.append([])
            new_population.append([])
            new_population[i], new_population[i+1] = crossover(populations[fit_parents[i]], populations[fit_parents[i+1]])

        # Applying mutation in the new population
        mutation()

        # Adjusting Variables
        populations.clear()
        populations = new_population.copy()
        new_population.clear()
        fit_add.clear()
        fit_parents.clear()
        fit_value.clear()
        fit_value_sorted.clear()

    # Ploting graph
    plt.plot(best_individuals)
    plt.plot(worst_individuals)
    plt.plot(mean_individuals)


    # Cleaning vectors
    best_individuals.clear()
    worst_individuals.clear()
    mean_individuals.clear()

if __name__ == "__main__":
    main()