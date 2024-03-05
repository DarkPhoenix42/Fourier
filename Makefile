#OBJS specifies which files to compile as part of the project
files = src/main.cpp

#CC specifies which compiler we're using
compiler = g++

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -Ofast --unroll-loops

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -Ofast

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = fourier

#This is the target that compiles our executable
all :
	$(compiler) $(CFLAGS) $(files) $(LINKER_FLAGS) -o build/$(OBJ_NAME)
