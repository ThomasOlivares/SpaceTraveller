FLAG=-lsfml-graphics \
	 -lsfml-window \
	 -lsfml-system \
	 -lsfml-audio \
	 -lsfml-network

CLASSES=application.o \
		button.o \
		$(HEADERS)category.hpp \
		circle.o \
		command.o \
		commandQueue.o \
		component.o \
		container.o \
		cursor.o \
		dataTables.o \
		entity.o \
		fleet.o \
		fleetHandler.o \
		gameState.o \
		main.o \
		menuState.o \
		planet.o \
		player.o \
		$(HEADERS)resourceHolder.hpp \
		sceneNode.o \
		ship.o \
		spriteNode.o \
		state.o \
		$(HEADERS)stateIdentifiers.hpp \
		stateStack.o \
		symbol.o \
		textNode.o \
		titleState.o \
		utility.o \
		viewNode.o \
		world.o

COMPILER=g++

LDFLAGS=-g

RDFLAGS=-std=c++14

SOURCES = Sources/

HEADERS = Headers/

all : main

main : $(CLASSES)
	$(COMPILER) $(LDFLAGS) $(CLASSES) -o SpaceTraveller $(RDFLAGS) $(FLAG)

main.o : $(SOURCES)main.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)main.cpp $(RDFLAGS)

application.o : $(SOURCES)application.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)application.cpp $(RDFLAGS)

button.o : $(SOURCES)button.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)button.cpp $(RDFLAGS)

circle.o : $(SOURCES)circle.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)circle.cpp $(RDFLAGS)

command.o : $(SOURCES)command.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)command.cpp $(RDFLAGS)

commandQueue.o : $(SOURCES)commandQueue.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)commandQueue.cpp $(RDFLAGS)

component.o : $(SOURCES)component.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)component.cpp $(RDFLAGS)

container.o : $(SOURCES)container.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)container.cpp $(RDFLAGS)

cursor.o : $(SOURCES)cursor.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)cursor.cpp $(RDFLAGS)

dataTables.o : $(SOURCES)dataTables.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)dataTables.cpp $(RDFLAGS)

entity.o : $(SOURCES)entity.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)entity.cpp $(RDFLAGS)

fleet.o : $(SOURCES)fleet.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)fleet.cpp $(RDFLAGS)

fleetHandler.o : $(SOURCES)fleetHandler.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)fleetHandler.cpp $(RDFLAGS)

gameState.o : $(SOURCES)gameState.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)gameState.cpp $(RDFLAGS)

menuState.o : $(SOURCES)menuState.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)menuState.cpp $(RDFLAGS)

planet.o : $(SOURCES)planet.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)planet.cpp $(RDFLAGS)

player.o : $(SOURCES)player.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)player.cpp $(RDFLAGS)

sceneNode.o : $(SOURCES)sceneNode.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)sceneNode.cpp $(RDFLAGS)

ship.o : $(SOURCES)ship.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)ship.cpp $(RDFLAGS)

spriteNode.o : $(SOURCES)spriteNode.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)spriteNode.cpp $(RDFLAGS)

state.o : $(SOURCES)state.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)state.cpp $(RDFLAGS)

stateStack.o : $(SOURCES)stateStack.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)stateStack.cpp $(RDFLAGS)

symbol.o : $(SOURCES)symbol.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)symbol.cpp $(RDFLAGS)

textNode.o : $(SOURCES)textNode.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)textNode.cpp $(RDFLAGS)

titleState.o : $(SOURCES)titleState.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)titleState.cpp $(RDFLAGS)

utility.o : $(SOURCES)utility.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)utility.cpp $(RDFLAGS)

viewNode.o : $(SOURCES)viewNode.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)viewNode.cpp $(RDFLAGS)

world.o : $(SOURCES)world.cpp
	$(COMPILER) $(LDFLAGS) -c $(SOURCES)world.cpp $(RDFLAGS)

clean :
	rm *.o
	rm SpaceTraveller

oclean :
	rm *.o