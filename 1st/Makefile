PROJECT_NAME=Advent_2025_Day1.exe
OBJECT_FILES=main.o RotaryDial.o

CFLAGS=-std=c++20 -Wall -Wextra -Werror

$(PROJECT_NAME): $(OBJECT_FILES)
	g++ $(OBJECT_FILES) -o $(PROJECT_NAME)

main.o: main.cpp RotaryDial.h
	g++ $(CFLAGS) -c main.cpp -o main.o

RotaryDial.o: RotaryDial.cpp RotaryDial.h
	g++ $(CFLAGS) -c RotaryDial.cpp -o RotaryDial.o

clean:
	rm -f $(PROJECT_NAME) $(OBJECT_FILES)

check:
	cppcheck --enable=all --inline-suppr --suppress=missingIncludeSystem --suppress=checkersReport --language=c++ --std=c++20 --quiet .
