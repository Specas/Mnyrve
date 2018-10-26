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

    plot_details = {}
    x_limits = {}
    y_limits = {}
    x_limits["lower"] = 0
    x_limits["upper"] = 5
    y_limits["lower"] = 0
    y_limits["upper"] = 10
    plot_details["figure_title"] = 'figure_title'
    plot_details["plot_title"] = 'plot_title'
    plot_details["x_label"] = 'xlabel'
    plot_details["y_label"] = 'ylabel'
    plot_details["fmt"] = 'g'
    plot_details["x_limits"] = x_limits
    plot_details["y_limits"] = y_limits
    plot_complete([1, 2, 3], [4, 5, 7], plot_details)
    pass
    


