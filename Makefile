all:
	g++ -c main.cpp engine.cpp input.cpp update.cpp draw.cpp balk.cpp fastener.cpp -g
	g++ main.o engine.o input.o update.o draw.o balk.o fastener.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -g
