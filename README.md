# Mnyrve

Mnyrve is an open source Reinforcement Learning library built using C++. It aims to provide implementations of both well established and more recent learning algorithms. It also leverages the [Python C API](https://docs.python.org/3.6/c-api/index.html) to provide visualizations of different environments and results.

For applications related to robotics, Mnyrve aims to use [Drake](https://drake.mit.edu/), which is a C++ toolbox for planning and control for non-linear dynamical systems.

## Build status

Platform | Status
---------|-------
Ubuntu (14.04 and 16.04) | [![Build Status](https://travis-ci.com/shrenikm/Mnyrve.svg?branch=master)](https://travis-ci.com/shrenikm/Mnyrve)

## Installation

Mnyrve is built using [Bazel](https://bazel.build/). 
Currently, the build has only been tested for C++14, running on Ubuntu Trusty and Xenail.

### Requirements
* Ubuntu 14.04 or 16.04 (Build tested for these two versions)
* [Bazel](https://github.com/bazelbuild/bazel/releases) version > 0.14.0
* [Python](https://www.python.org/downloads/) version 3.x
  * [Numpy](http://www.numpy.org/)
  * [matplotlib](https://matplotlib.org/)
  * [Pygame](https://www.pygame.org/)

### Building
To build the current version, clone the repository and run:  
`bazel build ...`<br/><br/>
To build the tests, run:    
`bazel test ...`<br/><br/>
To do both:  
`bazel build ... && bazel test ...`<br/><br/>

### Run examples
After building, the build can be tested by running some of the examples from the main directory:<br/>
`bazel-bin/examples/<directory>/<run_file>`

<br/>


## Example results

### Multi armed bandits

The following figure gives the result of a 10 armed bandit problem  where each reward is taken from a normal distribution with mean and standard deviation equal to 1.0. At each time step, the reward obtained is sampled using a normal distribution around the selected mean with standard deviation 1.0.

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1x9fNZMc4OTgcjePfOOqG-BdPVsgiBmQx" alt="10 armed bandits" width="600" />
</p>

-------

### Iterative policy evaluation

The value function for each state in a grid world MDP, evaluating a policy that can take each of the four actions with equal probability is shown below. <br/>

<br/>

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1-h4oJhzqdgcVxgTlWoQGJyLQUH7VW2qD" alt="Grid world" width="500"/> 
</p>

<br/>

The result is for the following reward configuration:

State | Reward
------| ------
Normal step | -1
Obstacle/Boundary | -5
Goal | 10

-------

## License

[MIT License](LICENSE)



