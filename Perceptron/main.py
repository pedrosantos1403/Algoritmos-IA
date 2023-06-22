from math import exp
import numpy as np
import random
import pandas as pd


class Matrix:
    def __init__(self, data=0):
        self.rows = 0
        self.columns = 0
        self.items = []
        if not data == 0:
            for row in data:
                self.columns = 0
                self.items.append([])
                for item in row:
                    self.items[self.rows].append(item)
                    self.columns += 1
                self.rows += 1

    def __str__(self):
        output = ''
        for i in range(self.rows):
            output += '[\t'
            for j in range(self.columns):
                output += str(self.items[i][j]) + '\t'
            output += ']\n'
        return output

    def insert_row(self, row):
        self.items.append([])
        self.columns = 0
        for item in row:
            self.items[self.rows].append(item)
            self.columns += 1
        self.rows += 1

    def get_item(self, r, c):
        return self.items[r][c]

    def get_size_rows(self):
        return self.rows

    def get_size_columns(self):
        return self.columns

    def get_row(self, r):
        return self.items[r]

    def set_row(self, r, L):
        self.items[r] = L

    def get_column(self, c):
        return [row[c] for row in self.items]

    def set_column(self, c, K):
        for r in range(self.rows):
            self.items[r][c] = K[r]

    def set_item(self, r, c, value):
        self.items[r][c] = value


# Learning rate
ALPHA = 0.1

# Species
species = {'Iris-setosa': [0, 0, 1], 'Iris-versicolor': [0, 1, 0], 'Iris-virginica': [1, 0, 0]}

# One neuron per class of plant
NEURON_MAX_NUMBER = 3

# All properties in use
PROPERTIES = ['sepal_length', 'sepal_width', 'petal_length', 'petal_width']


def step_function(wn, x, b):
    f = sum(wn[i] * x[i] for i in range(len(wn))) + b
    return 1 if f > 0 else 0


def sigmoid_function(wn, x, b):
    f = sum(wn[i] * x[i] for i in range(len(wn))) + b
    return 1 / (1 + exp(-f))


def sigmoid_output_handler(y):
    max_value = max(y)
    return [1 if val == max_value else 0 for val in y]


def get_random_index(vector):
    return random.choice(vector)


def main():
    io_base = pd.DataFrame(pd.read_csv('Iris_Data.csv'))

    # Target array d values recovered from IO
    d = []

    # Heuristic output
    y = []

    # d - y
    z = []

    # Recover species from base
    setosa_base = io_base.loc[io_base['species'] == "Iris-setosa"]
    versicolor_base = io_base.loc[io_base['species'] == "Iris-versicolor"]
    virginica_base = io_base.loc[io_base['species'] == "Iris-virginica"]

    # Recover training base
    setosa_training = setosa_base.head(40)
    versicolor_training = versicolor_base.head(40)
    virginica_training = virginica_base.head(40)

    # Recover test base
    setosa_test = setosa_base.tail(10)
    versicolor_test = versicolor_base.tail(10)
    virginica_test = virginica_base.tail(10)

    # Recover training and test bases
    training_base = pd.concat([setosa_training, versicolor_training, virginica_training], ignore_index=True)
    test_base = pd.concat([setosa_test, versicolor_test, virginica_test], ignore_index=True)

    # Training data classes
    classes_training_base = training_base['species']

    # Test data classes
    classes_test_base = test_base['species']

    # Find columns with non-numeric values
    non_numeric_cols = training_base.apply(lambda x: pd.to_numeric(x, errors='coerce')).isnull().any()

    # Remove columns with non-numeric values from DataFrame
    training_base = training_base.loc[:, ~non_numeric_cols]

    # Convertendo as colunas para o tipo numérico
    training_base = training_base.apply(pd.to_numeric)

    # Normalizar a base de treinamento
    normalized_training_base = (training_base - training_base.min()) / (training_base.max() - training_base.min())

    # Find columns with non-numeric values
    non_numeric_cols = test_base.apply(lambda x: pd.to_numeric(x, errors='coerce')).isnull().any()

    # Remove columns with non-numeric values from DataFrame
    test_base = test_base.loc[:, ~non_numeric_cols]

    # Convertendo as colunas para o tipo numérico
    test_base = test_base.apply(pd.to_numeric)

    # Create normalized test base
    normalized_test_base = (test_base - test_base.min()) / (test_base.max() - test_base.min())

    # Base with only properties to train
    properties_training_base = normalized_training_base[PROPERTIES]

    # Training data
    x = Matrix(properties_training_base.values.tolist())

    # Test base with only properties
    properties_test_base = normalized_test_base[PROPERTIES]

    # Test data
    x_test = Matrix(properties_test_base.values.tolist())

    # Creating output neurons randomly
    wn = Matrix([[random.uniform(-0.5, 0.5) for _ in range(x.get_size_columns())] for _ in range(NEURON_MAX_NUMBER)])
    b = [random.uniform(-0.5, 0.5) for _ in range(NEURON_MAX_NUMBER)]

    # Create target array d based on species
    for species_type in classes_training_base:
        d.append(species[species_type])

    # Initialize epoch counter
    epoch = 0

    # Initialize error accumulator
    E_history = []

    # Continue while error exists
    while True:
        # Initialize error counter
        E = 0

        # Initialize index list
        index_list = list(range(x.get_size_rows()))

        # Shuffle index list for stochasticity
        random.shuffle(index_list)

        # Iterate over each sample in the training set
        for i in index_list:
            # Select sample and target output
            sample = x.get_row(i)
            target = d[i]

            # Calculate the output
            output = [sigmoid_function(wn.get_row(j), sample, b[j]) for j in range(NEURON_MAX_NUMBER)]

            # Adjust the weights and bias
            for j in range(NEURON_MAX_NUMBER):
                for k in range(len(sample)):
                    wn.set_item(j, k, wn.get_item(j, k) + ALPHA * (target[j] - output[j]) * output[j] * (1 - output[j]) * sample[k])
                b[j] = b[j] + ALPHA * (target[j] - output[j]) * output[j] * (1 - output[j])

            # Accumulate the error
            E += sum((target[j] - output[j]) ** 2 for j in range(NEURON_MAX_NUMBER))

        # Increment epoch counter
        epoch += 1

        # Append accumulated error to history
        E_history.append(E)

        # Break if error is below a certain threshold or maximum epochs reached
        if E < 0.001 or epoch >= 1000:
            break

    # Print results
    print("Final Weights:")
    print(wn)
    print("Final Bias:")
    print(b)
    print("Epochs:", epoch)
    print("Error:", E)

    # Evaluate the model on the test set
    correct = 0

    for i in range(x_test.get_size_rows()):
        sample = x_test.get_row(i)
        target = classes_test_base[i]

        output = sigmoid_output_handler([sigmoid_function(wn.get_row(j), sample, b[j]) for j in range(NEURON_MAX_NUMBER)])

        if species[target] == output:
            correct += 1

    accuracy = correct / x_test.get_size_rows() * 100

    print("Accuracy on Test Set:", accuracy)


if __name__ == "__main__":
    main()