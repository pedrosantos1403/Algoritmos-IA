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
    E = 0

    # bias for all neurons
    b = [random.random() for x in range(NEURON_MAX_NUMBER)]

if __name__ == '__main__':
    main()