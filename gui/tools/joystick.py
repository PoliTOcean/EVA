import sdl2
import sdl2.ext

if __name__ == "__main__":
    sdl2.SDL_Init(sdl2.SDL_INIT_JOYSTICK)

    while True:
        for event in sdl2.ext.get_events():
            if event.type == sdl2.SDL_JOYAXISMOTION:
                print(event.jaxis.axis, event.jaxis.value)
            elif event.type == sdl2.SDL_JOYBUTTONDOWN:
                print(event.jbutton.button, event.jbutton.state)
            elif event.type == sdl2.SDL_JOYBUTTONUP:
                print(event.jbutton.button, event.jbutton.state)
            elif event.type == sdl2.SDL_JOYHATMOTION:
                print(event.jhat.hat, event.jhat.value)
            elif event.type == sdl2.SDL_JOYDEVICEADDED:
                joystick = sdl2.SDL_JoystickOpen(0)
            elif event.type == sdl2.SDL_JOYDEVICEREMOVED:
                sdl2.SDL_JoystickClose(joystick)
