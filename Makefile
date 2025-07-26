##
## EPITECH PROJECT, 2025
## raytracer
## File description:
## Makefile
##

RESET	=	\033[0m
YELLOW	=	\033[0;93m
GREEN   =	\033[0;92m

raytracer: light loader primitives image

all: light loader primitives image

loader:
	@echo -e "$(YELLOW)Building the Loader library...$(RESET)"
	@$(MAKE) -C lib/

light:
	@echo -e "$(GREEN)Building lights...$(RESET)"
	$(MAKE) -C src/lights

primitives: loader
	$(MAKE) -C src/primitives

image: loader primitives
	$(MAKE) -C src/

re: fclean all

clean:
	$(MAKE) clean -C src/primitives
	$(MAKE) clean -C src/
	$(MAKE) clean -C lib/
	$(MAKE) clean -C src/lights

fclean:
	$(MAKE) fclean -C src/primitives
	$(MAKE) fclean -C src/
	$(MAKE) fclean -C lib/
	$(MAKE) clean -C tests/
	$(MAKE) fclean -C src/lights
	@rm -f raytracer
	@rm -f coding-style-cpp-reports.log
	@rm -rf plugins/*.so
	@rm -f common/*.o

# Unit test compilation

unit_tests:
	$(MAKE) unit_tests -C tests/


tests_run:
	$(MAKE) tests_run -C tests/

coverage:
	$(MAKE) coverage -C tests/


# Debug compilation

debug: fclean
	$(MAKE) -C lib/
	@echo -e "$(YELLOW)Building in debug mode...$(RESET)"
	$(MAKE) -C lib/
	$(MAKE) -C src/primitives debug
	$(MAKE) -C src/ debug

# Norm

linter: clean
	cpplint $(CPPLINT_FLAGS) ./src/

format:
	find . -type f \( -name "*.cpp" -o -name "*.hpp" \) ! -path "./tests/*"	\
	-exec clang-format -i {} +
