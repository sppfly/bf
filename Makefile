

build/main: main.cpp
	clang++ -Wextra -Wall -Werror -g -std=c++23 main.cpp  -o build/main



.PHONY: clean

clean:
	rm -rf build/*
