all:
	g++ -w -I src/include -L src/lib -o main main.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf