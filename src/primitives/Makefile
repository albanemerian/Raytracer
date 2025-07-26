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
				../../common/Random.cpp		\
				../../common/APrimitives.cpp


SRC_SPHERE	=	Sphere.cpp

SRC_PLANE	=	Plane.cpp

SRC_CONE	=	Cone.cpp

SRC_CYLINDER =	Cylinder.cpp

SRC_TORUS	=	Torus.cpp

SRC_INFINITE_CYLINDER = InfiniteCylinder.cpp

SRC_INFINITE_CONE = InfiniteCone.cpp

PRIMITIVES	=	raytracer_sphere.so		\
				raytracer_plane.so		\
				raytracer_cone.so		\
				raytracer_cylinder.so	\
				raytracer_torus.so		\
				raytracer_infinite_cylinder.so \
				raytracer_infinite_cone.so

all: $(PRIMITIVES)


raytracer_sphere.so: $(SRC_SPHERE) $(SRC_COMMON)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $< $(SRC_COMMON)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/


raytracer_plane.so: $(SRC_PLANE) $(SRC_COMMON)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $< $(SRC_COMMON)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/


raytracer_cone.so: $(SRC_CONE) $(SRC_COMMON)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $< $(SRC_COMMON)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/

raytracer_cylinder.so: $(SRC_CYLINDER) $(SRC_COMMON)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $< $(SRC_COMMON)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/

raytracer_torus.so: $(SRC_TORUS) $(SRC_COMMON) $(SRC_LIGHTS)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $< $(SRC_COMMON) $(SRC_LIGHTS)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/

raytracer_infinite_cylinder.so: $(SRC_INFINITE_CYLINDER) $(SRC_COMMON)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $< $(SRC_COMMON)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/

raytracer_infinite_cone.so: $(SRC_INFINITE_CONE) $(SRC_COMMON)
	@echo -e "$(CYAN)Compiling $@...$(RESET)"
	$(CC) $(CFLAGS) $(FPIC) -shared -o $@ $< $(SRC_COMMON)
	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/
clean:
	-@rm -fr *.o *.so
	@echo -e "$(YELLOWBIG)Primitives object files cleaned!$(RESET)"

fclean: clean
	-@rm -f $(GAMES)
	@echo -e "$(YELLOWBIG)Primitives libraries cleaned!$(RESET)"

re: fclean all

debug:
	@echo -e "$(RED)Debug mode activated!$(RESET)"
	@echo -e "$(YELLOWBIG)Compiling with debug flags...$(RESET)"
	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o \
		raytracer_sphere.so $(SRC_SPHERE) $(SRC_COMMON) $(SRC_LIGHTS)

	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o \
		raytracer_plane.so $(SRC_PLANE) $(SRC_COMMON) $(SRC_LIGHTS)

	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o \
		raytracer_cone.so $(SRC_CONE) $(SRC_COMMON) $(SRC_LIGHTS)

	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o \
		raytracer_infinite_cylinder.so $(SRC_INFINITE_CYLINDER) \
		$(SRC_COMMON) $(SRC_LIGHTS)

	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o \
		raytracer_cylinder.so $(SRC_CYLINDER) $(SRC_COMMON) $(SRC_LIGHTS)

	$(CC) $(CFLAGS) $(DEBUGFLAG) $(FPIC) -shared -o \
		raytracer_infinite_cone.so $(SRC_INFINITE_CONE) \
		$(SRC_COMMON) $(SRC_LIGHTS)

	@echo -e "$(MAGENTA)Compilation of $@ done!$(RESET)"
	cp -f *.so ../../plugins/
