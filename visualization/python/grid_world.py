#!/usr/bin/env python

import os
import sys

# Setting argv manually as calling using embedded python doesn't do this
# It is required by pygame
if not hasattr(sys, 'argv'):
    sys.argv = ['']
import math
import pygame
import random

"""
Drawing functions. Must not be called standalone ------------------------------

"""

# Draw the cells (color coded)
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
        # x and y refer to the actual axes (horizontal and vertical)
        x = (col + 0.5)*(screen.get_width()/cells_per_row) - cell_size/2
        y = (row + 0.5)*(screen.get_width()/cells_per_row) - cell_size/2

        # Plotting using the required color. If its not a special cell, 
        # the highlight information is used
        cell_color = cell_highlighted_color if cell_highlighted_state[i] == 1 \
                else cell_color_map[cell_state[i]]
        pygame.draw.rect(screen, cell_color,
                pygame.Rect(x, y, cell_size, cell_size), 0)


# Draw the values on the cells (floating point numbers)
def draw_value(screen, value_color, cell_state, value, value_font, cell_size):

    num_states = len(cell_state)
    cells_per_row = int(math.sqrt(num_states))

    for i in range(num_states):

        row = i//cells_per_row
        col = i%cells_per_row

        # Obtaining the left corner of the cells such that the 
        # text is in the middle
        x = (col + 0.5)*(screen.get_width()/cells_per_row) - cell_size/4
        y = (row + 0.5)*(screen.get_width()/cells_per_row) - cell_size/4

        # Drawing the numbers (Except on obstacles and goals)
        if cell_state[i] != -1 and cell_state[i] != 2:
            value_render = value_font.render(str(value[i]), True, value_color)
            screen.blit(value_render, (x, y))

# Draw the policy on the cells as arrows
def draw_policy(screen, policy_color, policy_start_color, cell_state, policy, \
        cell_size):

    num_states = len(cell_state)
    cells_per_row = int(math.sqrt(num_states))

    for i in range(num_states):

        row = i//cells_per_row
        col = i%cells_per_row

        # Different arrow color for the start yellow cell
        color = policy_color if cell_state[i] == 0 \
                else policy_start_color

        # Obtaining the center of the cells
        x = (col + 0.5)*(screen.get_width()/cells_per_row)
        y = (row + 0.5)*(screen.get_width()/cells_per_row)
        offset = cell_size/3

        # Drawing the arrows (Except on obstacles and goals)
        if cell_state[i] != -1 and cell_state[i] != 2:

            # Left
            if policy[i] == 0:
                pygame.draw.polygon(screen, color, \
                        ((x + offset, y - offset), \
                         (x + offset, y + offset), \
                         (x - offset, y)))
            # Top
            if policy[i] == 2:
                pygame.draw.polygon(screen, color, \
                        ((x - offset, y - offset), \
                         (x + offset, y - offset), \
                         (x, y + offset)))
            # Right
            if policy[i] == 1:
                pygame.draw.polygon(screen, color, \
                        ((x - offset, y - offset), \
                         (x - offset, y + offset), \
                         (x + offset, y)))
            # Bottom
            if policy[i] == 3:
                pygame.draw.polygon(screen, color, \
                        ((x - offset, y + offset), \
                         (x + offset, y + offset), \
                         (x, y - offset)))


def setup_grid_world(num_states):# {{{

    if not hasattr(sys, 'argv'):
        sys.argv = ['']

    # Verifying that the number of states is a square number
    assert int(math.sqrt(num_states))**2 == num_states, \
            "Number of states is not a square"

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
        if pygame.mouse.get_focused() and \
                cell_state[row*cells_per_row + col] == 0:
            cell_highlighted_state[row*cells_per_row + col] = 1

        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                done = True

            if event.type == pygame.MOUSEBUTTONDOWN:

                if mode == 'obstacle':

                    # Toggle enabled
                    if cell_state[row * cells_per_row + col] == 0:
                        cell_state[row * cells_per_row + col] = -1
                    elif cell_state[row * cells_per_row + col] == -1:
                        cell_state[row * cells_per_row + col] = 0

                # As there is only one start, the mode is changed right after
                # The start cell must not be an obstacle cell
                elif mode == 'start':

                    if (1 not in cell_state) and \
                            (cell_state[row * cells_per_row + col] == 0):
                        cell_state[row * cells_per_row + col] = 1

                # The goal cell must not be a start or obstacle cell
                else:

                    # Toggle enabled
                    if cell_state[row * cells_per_row + col] == 0:
                        cell_state[row * cells_per_row + col] = 2
                    elif cell_state[row * cells_per_row + col] == 2:
                        cell_state[row * cells_per_row + col] = 0


            if event.type == pygame.KEYDOWN:

                if event.key == pygame.K_q:
                    done = True

                if event.key == pygame.K_RETURN:

                    # Switching between modes
                    if mode == 'obstacle':
                        mode = 'start'
                        break

                    if mode == 'start':

                        # Don't allow to move forward if start has not been set
                        if 1 not in cell_state:
                            print('Start position has not been set')
                        else:
                            mode = 'goal'
                        break

                    # Exiting
                    if mode == 'goal':

                        # Don't allow to exit if goals have not been set
                        if 2 not in cell_state:
                            print('Goal positions have not been set')
                        else:
                            done = True


        # Drawing
        draw_cells(screen, colors, cell_state, cell_highlighted_state,
                cell_size*cell_size_multiplier)
        pygame.display.flip()
        clock.tick(60)

    # Quitting and returning
    pygame.display.quit()
    pygame.quit()
    return cell_state

# }}}

def visualize_grid_solution(cell_state, value):# {{{

    # Verifying that the number of states is a square number
    num_states = len(cell_state)
    assert int(math.sqrt(num_states))**2 == num_states, \
            "Number of states is not a square."
    assert len(cell_state) == len(value), \
            "State and value dimensions don't match."

    # Rounding off appropriately
    value = [round(v, 2) for v in value]

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
    pygame.font.init()

    value_font = pygame.font.SysFont('Comic Sans MS', int(cell_size/4))

    """
    Initializing the required variables ---------------------------------------

    """
    cell_highlighted_state = [0]*num_states
    display_value = True

    done = False
    clock = pygame.time.Clock()


    """
    Draw and control loop -----------------------------------------------------

    """

    while not done:

        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                done = True

            if event.type == pygame.KEYDOWN:

                if event.key == pygame.K_q or event.key == pygame.K_RETURN:
                    done = True

                # Toggle value display
                if event.key == pygame.K_t:
                    display_value = not display_value
            
        # Drawing
        draw_cells(screen, colors, cell_state, cell_highlighted_state, \
                cell_size*cell_size_multiplier)
        if display_value:
            draw_value(screen, BACKGROUND, cell_state, value, value_font, \
                    cell_size*cell_size_multiplier)
        pygame.display.flip()
        clock.tick(60)

# }}}

def visualize_grid_solution_with_policy(cell_state, value, policy):# {{{

    # Verifying that the number of states is a square number
    num_states = len(cell_state)
    assert int(math.sqrt(num_states))**2 == num_states, \
            "Number of states is not a square."
    assert len(cell_state) == len(value), \
            "State and value dimensions don't match."

    # Rounding off appropriately
    value = [round(v, 2) for v in value]

    cells_per_row = int(math.sqrt(num_states))

    # Centering the pygame window on the screen
    os.environ['SDL_VIDEO_CENTERED'] = '1'

    # Colors
    BLACK = (0, 0, 0)
    WHITE = (255, 255, 255)
    BACKGROUND = (50, 50, 50)
    POLICY = (180, 180, 180)
    POLICY_START = (218, 180, 103)
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
    pygame.font.init()

    value_font = pygame.font.SysFont('Comic Sans MS', int(cell_size/4))

    """
    Initializing the required variables ---------------------------------------

    """
    cell_highlighted_state = [0]*num_states
    display_value = True
    display_policy = True

    done = False
    clock = pygame.time.Clock()


    """
    Draw and control loop -----------------------------------------------------

    """

    while not done:

        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                done = True

            if event.type == pygame.KEYDOWN:

                if event.key == pygame.K_q or event.key == pygame.K_RETURN:
                    done = True

                # Toggle value display
                if event.key == pygame.K_v:
                    display_value = not display_value
                if event.key == pygame.K_p:
                    display_policy = not display_policy
            
        # Drawing
        draw_cells(screen, colors, cell_state, cell_highlighted_state, \
                cell_size*cell_size_multiplier)
        if display_policy:
            draw_policy(screen, POLICY, POLICY_START, cell_state, policy, \
                    cell_size*cell_size_multiplier)
        if display_value:
            draw_value(screen, BACKGROUND, cell_state, value, value_font, \
                    cell_size*cell_size_multiplier)
        pygame.display.flip()
        clock.tick(60)

# }}}



if __name__ == '__main__':
    cell_state = setup_grid_world(81)
    visualize_grid_solution(cell_state,
            [random.uniform(0, 10) for _ in range(len(cell_state))])
    visualize_grid_solution_with_policy(cell_state,
            [random.uniform(0, 10) for _ in range(len(cell_state))], 
            [random.randrange(0, 4) for _ in range(len(cell_state))])
