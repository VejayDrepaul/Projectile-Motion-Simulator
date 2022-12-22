import math
import turtle 

WIDTH = 1200 #Window width
HEIGHT = 500 #Window height
WINDOW_X = 410 #x-axis startup position of window
WINDOW_Y = 225 #y-axis startup position of 
BLACK = (0, 0, 0)
GRAVITY = 9.81


def main():
    WINDOW = turtle.Screen()
    WINDOW.setup(WIDTH, HEIGHT, WINDOW_X, WINDOW_Y)
    ball = turtle.Turtle() #new turtle object
    ball.hideturtle()
    ball.penup()
    ball.goto(-70, -70)
    ball.showturtle()
    ball.pendown()
    ball.forward(30)


    turtle.done()


if __name__ == "__main__":
    main()