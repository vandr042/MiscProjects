import numpy as np


class Perceptron():
    """Class implementing the perceptron machine learning algorithm."""

    # Declare variable to hold weights
    weights_ = None

    # Declare vars to hold step size and number of rounds
    step = None
    rounds = None

    def __init__(self, step=0.01, rounds=100):
        self.step = step
        self.rounds = rounds

    def learn(self, X, y):
        """Runs the Perceptron algorithm.

        :param X: A 2D mxn array with m observations and n features
        :param y: A 1D array of m ground-truth classifications of the
            observations in X
        """

        # Initialize weights to 0 (n + 1 weights) 
        self.weights_ = np.zeros(1 + X.shape[1])

        converged = False
        i = 0

        while(not converged and i < self.rounds):
            converged = True
            for xi,yi in zip(X,y):
                output = self.activation(xi,yi)
                if output != yi:
                    converged = False
                
                self.updateWeights(yi, output, xi)
            i += 1

    def updateWeights(self, true_y, output, x):
        """Updates the weights according to the output from the
        activation function and the ground-truth classification.

        :param true_y: The ground-truth classification for the current
            observation -- 1 or -1. 
        :param output: An integer value returned by activation
        :param x: A 1D array with n features
        """
        
        for i in range(len(x)):
            delta_wj = self.step * (true_y - output) * x[i]
            self.weights_[i+1] = self.weights_[i+1] + delta_wj

        self.weights_[0] += self.step * (true_y - output)

    def activation(self, x, y):
        """Computes dot product of weights_ and X.

        :param x: A 1D array with n features
        :returns: 1 if >= 0 and -1 otherwise
        """

        output = np.dot(x, self.weights_[1:])

        if output >= 0:
            return 1
        else:
            return -1
