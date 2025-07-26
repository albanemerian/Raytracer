##
## EPITECH PROJECT, 2025
## B-OOP-400-NAN-4-1-raytracer-albane.merian
## File description:
## Makefile
##

# Compiler and flags
CC = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -fPIC -g
LIBSFML	=	-lsfml-graphics -lsfml-window -lsfml-system

GRAPHICSO = raytracer_sfml.so

# Files
SRC = GraphicMode.cpp

all: $(GRAPHICSO) $(LIB_STATIC)
	cp $(GRAPHICSO) -f ../../src/

$(GRAPHICSO):
	@echo -e "$(BLUE)Building graphical library: $@$(RESET)"
	$(CC) $(SRC) $(CXXFLAGS) -shared -o $@ $< $(LIBSFML)

clean:
	@rm -rf *.o

fclean: clean
	@rm -f $(GRAPHICSO)
	@rm -f ../../src/$(GRAPHICSO)

re: fclean all
