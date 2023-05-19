import random
import math
import numpy as np

best=-100000

populations =([[random.uniform(0,10) for x in range(2)] for i in range(100)])
#print(len(populations))
#print(type(populations))
#print(populations)

parents=[]
new_populations = []

def f_X(x1,x2):
    return math.sqrt(x1) * math.sin(x1) * math.sqrt(x2) * math.sin(x2) + 10


def fitness_score() :
    global populations,best
    fit_value = []
    fit_score=[]

    for i in range(100) :
        chromosome_value = f_X(populations[i][0], populations[i][1])
        fit_value.append(chromosome_value) # Calculo da função com os valores dos genes

    print(fit_value)
    fit_value = fit_value.sort(reverse = True) # Ordenando os indivíduos em relação ao fit value
    best= fit_value[0]
    
#fitness_score()

def main():
    pass

if __name__ == "__main__":
    main()