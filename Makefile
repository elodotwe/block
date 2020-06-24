block: main.c
	gcc -o block main.c -lSDL2 `pkg-config --cflags sdl2`
