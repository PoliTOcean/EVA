import pygame

pygame.init()
clock = pygame.time.Clock()

while True:
    for event in pygame.event.get():
        if event.type == pygame.JOYDEVICEADDED:
            joystick = pygame.joystick.Joystick(event.device_index)

    buttons = joystick.get_numbuttons()
    for i in range(buttons):
        button = joystick.get_button(i)
        print(button)

    clock.tick(30)


pygame.quit()