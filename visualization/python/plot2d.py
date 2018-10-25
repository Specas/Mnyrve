import numpy as np
import matplotlib.pyplot as plt

def create_figure(frame_title = None):

    fig = plt.figure(frame_title)
    ax = fig.gca()
    return fig, ax

def plot_sample():
    plt.plot([1, 2, 3], [1, 2, 3])
    plt.show()

def plot_simple(x, y):

    fig, ax = create_figure()
    ax.plot(x, y, 'b')
    plt.show()

if __name__ == '__main__':

    #fig, ax = create_figure('Title')
    pass
    


