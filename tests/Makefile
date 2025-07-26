##
## EPITECH PROJECT, 2025
## B-OOP-400-NAN-4-1-raytracer-albane.merian
## File description:
## Makefile
##


TEST_NAME =	unit_tests

TEST_FLAGS	=	--coverage -lcriterion -include cstdint


RESET	=	\033[0m
YELLOW	=	\033[0;93m

SRC =	../common/APrimitives.cpp	\
		../common/Camera.cpp	\
		../common/Image.cpp	\
		../common/Point3D.cpp	\
		../common/Ray.cpp	\
		../common/Rectangle3D.cpp	\
		../common/Rot3D.cpp	\
		../common/Random.cpp \
		../common/Scene.cpp	\
		../common/Vector2D.cpp	\
		../common/Vector3D.cpp	\
		../lib/DLLoader.cpp	\
		../src/factory/CameraFactory.cpp	\
		../src/factory/FactoryManager.cpp	\
		../src/factory/PrimitiveFactory.cpp	\
		../src/factory/LightFactory.cpp	\
		../src/parser/ConfigNode.cpp	\
		../src/parser/ConfigParser.cpp	\
		../src/parser/ObjectErrorHandling.cpp	\
		../src/parser/ValueConverter.cpp	\
		../src/primitives/Cone.cpp	\
		../src/utils/Utils.cpp	\
		../src/Raytracer.cpp \
		../common/ALight.cpp \
		../src/mediator/RayMediator.cpp \
		../common/material/AMaterial.cpp \
		../common/material/chessboardMat.cpp \
		../common/material/flatColorMat.cpp \
		../common/material/fileTextureMat.cpp \
		../common/material/transparencyMat.cpp \
		../common/material/perlingNoiseMat.cpp \


TESTSRC = 	Helper-test.cpp	\
			Raytracer-test.cpp	\
			Exeption-test.cpp	\
			Camera-test.cpp	\
			Image-test.cpp	\
			Color-test.cpp	\
			APrimitives-test.cpp	\
			Vector3D-test.cpp	\
			Vector2D-test.cpp	\
			Rot3D-test.cpp	\
			Point3D-test.cpp	\
			Rextangle3D-test.cpp	\
			Ray-test.cpp	\
			Scene-test.cpp	\
			Cone-test.cpp	\
			ConfigNode-test.cpp	\
			ValueConverter-test.cpp	\
			ConfigParser-test.cpp	\
			IFactory-test.cpp	\
			ObjectError-test.cpp	\
			ALight-test.cpp	\
			Random-test.cpp	\
			RayMediator-test.cpp	\
			Material-test.cpp	\
			FileTextureMat-test.cpp \
			PrimitiveFactory-test.cpp \

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lconfig++

clean:
	@echo -e "$(YELLOW)Cleaning up...$(RESET)"
	-@rm -rf *.gc*
	-@rm -rf *.gcov
	-@rm -f *.gcno *.gcda
	-@rm -f $(TEST_NAME)

unit_tests: clean
	g++ -o $(TEST_NAME) $(SRC) $(TESTSRC) $(TEST_FLAGS) $(LIBS)


tests_run: unit_tests
	@echo -e "$(YELLOW)Running tests...$(RESET)"
	@./$(TEST_NAME)

coverage: tests_run
	@gcovr --root=.. --exclude='.*-test.cpp' --exclude-directories='tests'
