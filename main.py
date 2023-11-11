import serial
import pygame
import colorsys
from time import sleep

###############PYGAME################
size = [800, 800]
pygame.init()
screen = pygame.display.set_mode(size)

# Colours
BLACK = (0, 0, 0)

screen.fill(BLACK)

# Width and Height of game box
width = 30
height = 30

# Margin between each cell
margin = 1

# Set title of screen
pygame.display.set_caption("Spatial Recall")

# Used to manage how fast the screen updates
clock = pygame.time.Clock()
###############PYGAME################

# touch matrix dimensions
row_num = 24
col_num = 24


def split(a, n):
    k, m = divmod(len(a), n)
    return (a[i*k+min(i, m):(i+1)*k+min(i+1, m)] for i in range(n))


def set_color(value):
    hue = (100 - value * 5) / 360
    if hue < 0.1:
        hue = 0.1
    color = colorsys.hsv_to_rgb(hue, 1, 100)
    return color


def main():
    rcv_list = []

    arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1)
    arduino.flush()
    sleep(3)

    arduino.write(bytes('ok\n', 'utf-8'))
    while True:
        data = arduino.readline()
        # print(len(data))
        if len(data) > 0:
            rcv_list.append(int(data))

            if len(rcv_list) == row_num * col_num:
                # print(rcv_list)
                split_list = list(split(rcv_list, row_num))
                rcv_list = []
                print(split_list)

                for row in range(row_num):
                    for column in range(col_num):
                        # color = colorsys.hsv_to_rgb((100 - split_list[row][column]*2) / 360, 1, 100)
                        color = set_color(split_list[row][column])
                        pygame.draw.rect(screen, color,
                                         [(margin + width) * column + margin, (margin + height) * row + margin,
                                          width,
                                          height])
                # Go ahead and update the screen with what we've drawn.
                pygame.display.flip()
                # sleep(1)
                arduino.write(bytes('ok\n', 'utf-8'))

        # PYGAME WINDOW
        for event in pygame.event.get():  # User did something
            if event.type == pygame.QUIT:
                pygame.quit()


if __name__ == "__main__":
    main()
