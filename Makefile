FLAG=-lsfml-graphics \
	 -lsfml-window \
	 -lsfml-system \
	 -lsfml-audio \
	 -lsfml-network

CLASSES=application.o \
		button.o \
		$(HEADERS)category.hpp \
		command.o \
		commandQueue.o \
		component.o \
		container.o \
		gameState.o \
		main.o \
		menuState.o \
		$(HEADERS)resourceHolder.hpp \
		sceneNode.o \
		spriteNode.o \
		state.o \
		$(HEADERS)stateIdentifiers.hpp \
		stateStack.o \
		titleState.o \
		utility.o \
		world.o


LDFLAGS=-g

RDFLAGS=-std=c++11

SOURCES = Sources/

HEADERS = Headers/

all : main

main : $(CLASSES)
	g++ $(LDFLAGS) $(CLASSES) -o SpaceShooter $(RDFLAGS) $(FLAG)

main.o : $(SOURCES)main.cpp
	g++ $(LDFLAGS) -c $(SOURCES)main.cpp $(RDFLAGS)

application.o : $(SOURCES)application.cpp
	g++ $(LDFLAGS) -c $(SOURCES)application.cpp $(RDFLAGS)

button.o : $(SOURCES)button.cpp
	g++ $(LDFLAGS) -c $(SOURCES)button.cpp $(RDFLAGS)

command.o : $(SOURCES)command.cpp
	g++ $(LDFLAGS) -c $(SOURCES)command.cpp $(RDFLAGS)

commandQueue.o : $(SOURCES)commandQueue.cpp
	g++ $(LDFLAGS) -c $(SOURCES)commandQueue.cpp $(RDFLAGS)

component.o : $(SOURCES)component.cpp
	g++ $(LDFLAGS) -c $(SOURCES)component.cpp $(RDFLAGS)

container.o : $(SOURCES)container.cpp
	g++ $(LDFLAGS) -c $(SOURCES)container.cpp $(RDFLAGS)

gameState.o : $(SOURCES)gameState.cpp
	g++ $(LDFLAGS) -c $(SOURCES)gameState.cpp $(RDFLAGS)

menuState.o : $(SOURCES)menuState.cpp
	g++ $(LDFLAGS) -c $(SOURCES)menuState.cpp $(RDFLAGS)

sceneNode.o : $(SOURCES)sceneNode.cpp
	g++ $(LDFLAGS) -c $(SOURCES)sceneNode.cpp $(RDFLAGS)

spriteNode.o : $(SOURCES)spriteNode.cpp
	g++ $(LDFLAGS) -c $(SOURCES)spriteNode.cpp $(RDFLAGS)

state.o : $(SOURCES)state.cpp
	g++ $(LDFLAGS) -c $(SOURCES)state.cpp $(RDFLAGS)

stateStack.o : $(SOURCES)stateStack.cpp
	g++ $(LDFLAGS) -c $(SOURCES)stateStack.cpp $(RDFLAGS)

titleState.o : $(SOURCES)titleState.cpp
	g++ $(LDFLAGS) -c $(SOURCES)titleState.cpp $(RDFLAGS)

utility.o : $(SOURCES)utility.cpp
	g++ $(LDFLAGS) -c $(SOURCES)utility.cpp $(RDFLAGS)

world.o : $(SOURCES)world.cpp
	g++ $(LDFLAGS) -c $(SOURCES)world.cpp $(RDFLAGS)

clean :
	rm *.o
	rm SpaceShooter

oclean :
	rm *.o