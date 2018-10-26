import numpy as np
import matplotlib.pyplot as plt

def create_figure(frame_title = None):

    fig = plt.figure(frame_title)
    ax = fig.gca()
    return fig, ax

def plot_simple(x, y):

    fig, ax = create_figure()
    ax.plot(x, y)
    plt.show()

def plot_complete(x, y, plot_details):

    fig, ax = create_figure(plot_details["figure_title"])
    ax.set_title(plot_details["plot_title"])
    ax.set_xlabel(plot_details["x_label"])
    ax.set_ylabel(plot_details["y_label"])
    ax.plot(x, y, plot_details["fmt"])
    ax.set_xlim(plot_details["x_limits"]["lower"],
            plot_details["x_limits"]["upper"])
    ax.set_ylim(plot_details["y_limits"]["lower"],
            plot_details["y_limits"]["upper"])
    plt.show()


if __name__ == '__main__':

    pass
    


