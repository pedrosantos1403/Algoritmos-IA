import random
import pandas as pd
from classes import Matrix

# defines
SETOSA = '001'
VERSICOLOR = '010'
VIRGINICA = '100'
ALFA = 0.1

# one neuron per class of plant
NEURON_MAX_NUMBER = 3

# sepal_length, sepal_width, petal_length, petal_width
PROPERTIES_MAX_NUMBER = 4 

def main():
    io_base = pd.DataFrame(pd.read_csv('Iris_Data.csv'))
    
    # target arrey d values recovered from IO
    d = []

    # heuristic output
    y = []

    # d - y
    z = []

    # Epoch error per neuron
    E_current = [0 for x in range(NEURON_MAX_NUMBER)]
    E_past = [1 for x in range(NEURON_MAX_NUMBER)]

    # bias for all neurons
    b = [random.random() for x in range(NEURON_MAX_NUMBER)]

    # weights
    w = Matrix()
    for i in range(NEURON_MAX_NUMBER):
        w.insert_row([random.random() for x in range(PROPERTIES_MAX_NUMBER)])

    # recover species from base
    setosa_base = io_base.loc[io_base['species'] == "Iris-setosa"]
    versicolor_base = io_base.loc[io_base['species'] == "Iris-versicolor"]
    virginica_base = io_base.loc[io_base['species'] == "Iris-virginica"]
    
    # recover training base
    setosa_training = setosa_base.sample(frac=0.7,random_state=50)
    versicolor_training = versicolor_base.sample(frac=0.7,random_state=50)
    virginica_training = virginica_base.sample(frac=0.7,random_state=50)
    training_base = [setosa_training, versicolor_training, virginica_training]
    training_base = pd.concat(training_base)
    
    # recover test base
    setosa_test = setosa_base.drop(setosa_training.index)
    versicolor_test = versicolor_base.drop(versicolor_training.index)
    virginica_test = virginica_base.drop(virginica_training.index)
    test_base = [setosa_test, versicolor_test, virginica_test]
    test_base = pd.concat(test_base)

    # while E_past > E_current: #after set train base
        # io = [5.1         ,3.5        ,1.4         ,0.2        ]

        # name = 'Iris-setosa'
        # if name == 'Iris-setosa':
        #     d = [0,0,1]
        

if __name__ == '__main__':
    main()