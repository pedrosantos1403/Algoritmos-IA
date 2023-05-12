import random

# defines
SETOSA = '001'
VERSICOLOR = '010'
VIRGINICA = '100'
ALFA = 0.1

NEURON_MAX_NUMBER = 3

def main():
    # target arrey d values recovered from IO
    d = []

    # heuristic output
    y = []

    # d - y
    z = []

    # Epoch error
    E_current = 0
    E_past = 1

    # bias for all neurons
    b = [random.random() for x in range(NEURON_MAX_NUMBER)]

    while E_past > E_current: #after set train base
        pass
        

if __name__ == '__main__':
    main()