COMPILER = clang
FLAGS = -g -Wall -Wpedantic -Wextra

%: build/%
	@:

build/%: src/%.c
	mkdir -p build
	 $(COMPILER) $(FLAGS) $^ -o $@

clean: 
	rm -rf build