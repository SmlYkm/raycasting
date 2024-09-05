all:
	g++ src/*.cpp src/Math/*.cpp src/Rendering/*.cpp src/Game/*.cpp -Iinclude -o bin/raycasting -O3 -lSDL2 -lSDL2_image
