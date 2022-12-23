import math
import turtle 


WIDTH = 1200 #Window width
HEIGHT = 500 #Window height
WINDOW_X = 410 #x-axis startup position of window
WINDOW_Y = 225 #y-axis startup position of 
BLACK = (0, 0, 0)
GRAVITY = 9.80665
INITIAL_X = 0 #Initial x-value
INITIAL_Y = 0 #Initial y-value


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
    ball = turtle.Turtle()
    ball.shape("circle")

    vx = velocity * math.cos(math.radians(angle)) #x-axis velocity
    vy = velocity * math.sin(math.radians(angle)) #y-axis velocity
    flight_time = 2*(vy)/GRAVITY
    print(flight_time)

    x_dist = vx * flight_time
    y_dist = (vy * flight_time) + ((GRAVITY * flight_time**2) / 2)

    t = 0
    """
    for t in range(0, int(flight_time)):
        x = vx * t + INITIAL_X
        y = vy * t - (((t**2) * GRAVITY) / 2) + INITIAL_Y
        ball.goto(x, y)
        """
    while t <= flight_time:
        x = vx * t + INITIAL_X
        y = vy * t - (((t**2) * GRAVITY) / 2) + INITIAL_Y
        ball.goto(x, y)
        t += 0.01


def main():
    draw_axis()
    ball_movement(velocity, angle)
    turtle.done()


if __name__ == "__main__":
    main()