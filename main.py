import math
import turtle 


WIDTH = 1200 #Window width
HEIGHT = 500 #Window height
WINDOW_X = 410 #x-axis startup position of window
WINDOW_Y = 225 #y-axis startup position of 
BLACK = (0, 0, 0)
GRAVITY = 9.81


# Initial window setup
WINDOW = turtle.Screen()
WINDOW.setup(WIDTH, HEIGHT, WINDOW_X, WINDOW_Y)
WINDOW.title("Projectile Motion Simulator")
WINDOW.setworldcoordinates(-1, -1, WIDTH, HEIGHT)
velocity = WINDOW.numinput("Velocity", "Enter an velocity for the projectile: ")
angle = WINDOW.numinput("Angle", "Enter an angle for the projectile: ")


def draw_axis():
    #Draw x-axis 
    x = turtle.Turtle()#don't draw when turtle moves
    x.forward(WIDTH)

    #Draw y-axis
    y = turtle.Turtle()
    y.setheading(90)
    y.forward(HEIGHT)
    

def ball_movement(velocity, angle):
    vx = velocity * math.cos(angle) #x-axis velocity
    vy = velocity * math.sin(angle) #y-axis velocity

    ball = turtle.Turtle()
    ball.shape("circle")
    ball.setheading(30)
    ball.forward(30)


def main():
    draw_axis()
    ball_movement(velocity, angle)
    

    turtle.done()





if __name__ == "__main__":
    main()