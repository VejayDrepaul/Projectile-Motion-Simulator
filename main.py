import pygame

WIDTH = 500
HEIGHT = 500
BLACK = (0, 0, 0)
FPS = 60
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Projectile Motion Simulator")


def draw_window():
    WIN.fill(BLACK)
    WIN.blit(pygame.draw.circle(WIN, "red", (200, 200), 10), (100, 100))
    pygame.display.update()


def main():
    clock = pygame.time.Clock()
    run = True
    while run:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False

        draw_window()
            
    pygame.quit()


if __name__ == "__main__":
    main()