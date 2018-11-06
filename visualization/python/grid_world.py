#!/usr/bin/env python

import pygame
import os
import math

"""
Drawing functions. Must not be called standalone ------------------------------

"""

def draw_cells(screen, colors, cell_state, cell_highlighted_state, cell_size):

    bg_color, cell_normal_color, cell_highlighted_color, \
    cell_obstacle_color, cell_start_color, cell_goal_color = colors

    # Dict to map from the cell state to the color
    cell_color_map = {0: cell_normal_color,
                      -1: cell_obstacle_color,
                      1: cell_start_color,
                      2: cell_goal_color}

    screen.fill(bg_color)

    # Drawing the cells
    num_states = len(cell_state)
    cells_per_row = int(math.sqrt(num_states))

    for i in range(num_states):

        row = i//cells_per_row
        col = i%cells_per_row

        # Obtaining the top left corner of the cells
        x = (col + 0.5)*(screen.get_width()/cells_per_row) - cell_size/2
        y = (row + 0.5)*(screen.get_width()/cells_per_row) - cell_size/2

        # Plotting using the required color. If its not a special cell, 
        # the highlight information is used
        cell_color = cell_highlighted_color if cell_highlighted_state[i] == 1 else cell_color_map[cell_state[i]]
        pygame.draw.rect(screen, cell_color, pygame.Rect(x, y, cell_size, cell_size), 0)




def setup_grid_world(num_states):

    # Verifying that the number of states is a square number
    assert int(math.sqrt(num_states))**2 == num_states, "Number of states is not a square"

    cells_per_row = int(math.sqrt(num_states))

    # Centering the pygame window on the screen
    os.environ['SDL_VIDEO_CENTERED'] = '1'

    # Colors
    BLACK = (0, 0, 0)
    WHITE = (255, 255, 255)
    BACKGROUND = (50, 50, 50)
    CELL_NORMAL = (205, 205, 205)
    CELL_HIGHLIGHTED = (150, 150, 150)
    CELL_OBSTACLE = (109, 82, 148)
    CELL_START = (240, 209, 122)
    CELL_GOAL = (82, 168, 82)

    colors = (BACKGROUND,
              CELL_NORMAL,
              CELL_HIGHLIGHTED,
              CELL_OBSTACLE,
              CELL_START,
              CELL_GOAL) 

    # Computing the size of each cell and size of the window
    cell_size = 75

    # Actual size of the cell is obtained by multiplying the factor.
    # This is to account for the grid width
    cell_size_multiplier = 0.95
    screen_width = cells_per_row * cell_size
    screen_height = cells_per_row * cell_size
    screen_size = (screen_width, screen_height)
    screen = pygame.display.set_mode(screen_size)

    pygame.display.set_caption('Grid World')

    pygame.init()

    """
    Initializing the required variables ---------------------------------------

    """
    cell_state = [0]*num_states

    done = False
    clock = pygame.time.Clock()

    # The mode can be 'obstacle', 'start' or 'goal'
    mode = 'obstacle'

    """
    Draw and control loop -----------------------------------------------------

    """

    while not done:

        mouse_x, mouse_y = pygame.mouse.get_pos()

        # Update highlighted state
        row = int((mouse_y + cell_size/2)/(screen_width/cells_per_row) - 0.5)
        col = int((mouse_x + cell_size/2)/(screen_width/cells_per_row) - 0.5)
        cell_highlighted_state = [0]*num_states

        # Only updated highlighted cell if the mouse in in the screen
        # and the cell is normal
        if pygame.mouse.get_focused() and  cell_state[row*cells_per_row + col] == 0:
            cell_highlighted_state[row*cells_per_row + col] = 1

        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                done = True

            if event.type == pygame.MOUSEBUTTONDOWN:

                if mode == 'obstacle':

                    cell_state[row * cells_per_row + col] = -1

                # As there is only one start, the mode is changed right after
                # The start cell must not be an obstacle cell
                elif mode == 'start':

                    if (1 not in cell_state) and (cell_state[row * cells_per_row + col] == 0):
                        cell_state[row * cells_per_row + col] = 1

                # The goal cell must not be a start or obstacle cell
                else:

                    if cell_state[row * cells_per_row + col] == 0:
                        cell_state[row * cells_per_row + col] = 2


            if event.type == pygame.KEYDOWN:

                if event.key == pygame.K_q:
                    done = True

                if event.key == pygame.K_RETURN:

                    # Switching between modes
                    if mode == 'obstacle':
                        mode = 'start'
                        break

                    if mode == 'start':
                        mode = 'goal'
                        break

                    # Exiting
                    if mode == 'goal':
                        done = True


        # Drawing
        draw_cells(screen, colors, cell_state, cell_highlighted_state,
                cell_size*cell_size_multiplier)
        pygame.display.flip()
        clock.tick(60)

    return cell_state



if __name__ == '__main__':
    setup_grid_world(81)
