bloom_filter: bloom_filter.cpp
	clang++ -Wextra -Wall -Werror -g -std=c++23 bloom_filter.cpp -o build/bloom_filter


.PHONY: clean

clean:
	rm -rf build/*