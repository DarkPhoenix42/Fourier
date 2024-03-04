#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp

#CC specifies which compiler we're using
CC = g++

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -Ofast

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Fourier

#This is the target that compiles our executable
all :
	$(CC) $(OBJS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)