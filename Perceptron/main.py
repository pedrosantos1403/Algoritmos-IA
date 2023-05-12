import random
import pandas as pd
from classes import Matrix

# defines
SETOSA = '001'
VERSICOLOR = '010'
VIRGINICA = '100'
ALFA = 0.1

NEURON_MAX_NUMBER = 3

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
        w.insert_row([random.random() for x in range(NEURON_MAX_NUMBER)])

    # recover species from base
    setosa_base = io_base.loc[io_base['species'] == "Iris-setosa"]
    versicolor_base = io_base.loc[io_base['species'] == "Iris-versicolor"]
    virginica_base = io_base.loc[io_base['species'] == "Iris-virginica"]
    
    # recover train base
    setosa_train = setosa_base.sample(frac=0.7,random_state=50)
    versicolor_train = versicolor_base.sample(frac=0.7,random_state=50)
    virginica_train = virginica_base.sample(frac=0.7,random_state=50)
    train_base = [setosa_train, versicolor_train, virginica_train]
    train_base = pd.concat(train_base)
    # train_base = setosa_train.append(versicolor_train, ignore_index=True)
    # train_base = train_base.append(virginica_train, ignore_index=True)
    print(train_base)
    print(len(train_base))
    
    # recover test base
    # test_setosa = setosa_base.drop(train_setosa.index)
    # test_setosa = setosa_base.drop(train_setosa.index)
    # test_setosa = setosa_base.drop(train_setosa.index)
    

    # while E_past > E_current: #after set train base
        # io = [5.1         ,3.5        ,1.4         ,0.2        ]

        # name = 'Iris-setosa'
        # if name == 'Iris-setosa':
        #     d = [0,0,1]
        

if __name__ == '__main__':
    main()