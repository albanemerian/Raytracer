##
## EPITECH PROJECT, 2025
## B-OOP-400-NAN-4-1-raytracer-albane.merian
## File description:
## Makefile
##

NAME	=	raytracer

CC	=	g++

CFLAGS	=	-std=c++20 -Wall -Wextra -Werror -Wshadow -ldl -g

DEBUGFLAG	=	-g

LDFLAGS	= -ldl -L./ -lDLLoader

LIBCONFIG	=	-lconfig++

LIBSFML = -lsfml-graphics -lsfml-window -lsfml-system

SRC		=		main.cpp	\
				utils/Utils.cpp	\
				Raytracer.cpp \
				RaytracerImage.cpp \
				RaytracerGraphic.cpp		\
				parser/Parser.cpp \
				parser/ConfigNode.cpp \
				parser/ConfigParser.cpp \
				parser/ObjectConstructor.cpp \
				parser/ValueConverter.cpp \
				parser/ObjectErrorHandling.cpp \
				factory/CameraFactory.cpp \
				factory/PrimitiveFactory.cpp \
				factory/FactoryManager.cpp \
				factory/LightFactory.cpp	\
				image/ConvertImage.cpp \
				../common/Vector2D.cpp \
				../common/Camera.cpp \
				../common/Rectangle3D.cpp \
				../common/Vector3D.cpp \
				../common/Point3D.cpp \
				../common/Rot3D.cpp \
				../common/Random.cpp \
				../common/Image.cpp	\
				../common/Scene.cpp \
				../common/Ray.cpp \
				../common/material/AMaterial.cpp \
				../common/material/flatColorMat.cpp \
				../common/material/transparencyMat.cpp \
				../common/material/chessboardMat.cpp \
				../common/material/fileTextureMat.cpp \
				../common/material/perlingNoiseMat.cpp \
				mediator/RayMediator.cpp


RESET	=	\033[0m
GREEN	=	\033[1;92m
BLUE	 =	\033[1;94m
YELLOWBIG	=	\033[1;93m
RED			=	\033[1;91m


all: $(NAME)

OBJ		=	$(SRC:.cpp=.o)

$(NAME): $(OBJ)
	@echo -e "$(GREEN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) $(LIBCONFIG) $(LIBSFML)
	@echo -e "$(BLUE)Compilation of $@ done!$(RESET)"
	mv -f $(NAME) ../

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-@rm -rf $(OBJ)
	@echo -e "$(YELLOWBIG)Core object files cleaned!$(RESET)"

fclean: clean
	-@rm -f $(NAME) $(TEST_NAME)
	-@rm -f ../$(NAME)
	-@rm -f ../raytracer_sfml.so
	-@rm *.a
	@echo -e "$(YELLOWBIG)Core binary and test files cleaned!$(RESET)"

re: fclean all

debug:
	@echo -e "$(RED)Compiling in debug mode...$(RESET)"
	$(CC) $(CFLAGS) $(DEBUGFLAG) $(SRC) -o $(NAME) $(LDFLAGS) \
	$(LIBCONFIG) $(LIBSFML)
	@echo -e "$(BLUE)Compilation of $@ done!$(RESET)"
	cp -f $(NAME) ../
