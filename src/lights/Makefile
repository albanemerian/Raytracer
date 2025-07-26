##
## EPITECH PROJECT, 2025
## B-OOP-400-NAN-4-1-raytracer-albane.merian
## File description:
## Makefile
##

CC	=	g++


FPIC 	=	-fPIC

CFLAGS	= -std=c++20 -Wall -Wextra -Werror -Wshadow -g

DEBUGFLAG =		-g

RESET	=	\033[0m
CYAN	=	\033[1;96m
MAGENTA =	\033[1;95m
YELLOWBIG	=	\033[1;93m
RED			=	\033[1;91m

SRC_COMMON	=	../../common/Vector3D.cpp	\
				../../common/Point3D.cpp 	\
				../../common/Vector2D.cpp	\
				../../common/Rot3D.cpp		\
				../../common/Ray.cpp		\
				../../common/ALight.cpp

SRC_DIRECTIONEL = DirectionalLight.cpp

SRC_PHONG	=	PhongLight.cpp

OBJ_LIGHTS	=	raytracer_directional.so

all: $(OBJ_LIGHTS)

raytracer_directional.so: $(SRC_DIRECTIONEL) $(SRC_COMMON)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $(SRC_DIRECTIONEL) $(SRC_COMMON)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f $@ ../../plugins/


# raytracer_phong.so: $(SRC_PHONG) $(SRC_COMMON)
# 	@echo -e "$(CYAN)Compiling $@...$(RESET)"
# 	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $(SRC_PHONG) $(SRC_COMMON)
# 	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
# 	cp -f $@ ../../plugins/

clean:
	-@rm -fr *.o
	-@rm -rf *.so
	@echo -e "$(YELLOWBIG)Lights object files cleaned!$(RESET)"

fclean: clean
	@echo -e "$(YELLOWBIG)Lights libraries cleaned!$(RESET)"

re: fclean all

debug:
	@echo -e "$(RED)Debug mode activated!$(RESET)"
	@echo -e "$(YELLOWBIG)Compiling with debug flags...$(RESET)"
	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o raytracer_directional.so \
		$(SRC_DIRECTIONEL) $(SRC_COMMON)
	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o raytracer_point.so \
		$(SRC_POINT) $(SRC_COMMON)
	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o raytracer_phong.so \
		$(SRC_PHONG) $(SRC_COMMON)
	cp -f *.so ../../plugins/
	@echo -e "$(MAGENTA)Debug compilation done!$(RESET)"
