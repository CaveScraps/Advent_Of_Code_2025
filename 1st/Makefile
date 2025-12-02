PROJECT_NAME=Advent_2025_Day1
OBJECT_FILES=main.o

CFLAGS=-std=c++20 -Wall -Wextra -Werror

$(PROJECT_NAME): $(OBJECT_FILES)
	g++ $(OBJECT_FILES) -o $(PROJECT_NAME)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -f $(PROJECT_NAME) $(OBJECT_FILES)

check:
	cppcheck --enable=all --inline-suppr --suppress=missingIncludeSystem --suppress=checkersReport --language=c++ --std=c++20 --quiet .
