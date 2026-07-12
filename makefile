COMPILER = clang
FLAGS = -g -Wall -Wpedantic -Wextra -Werror

PROG ?= a1
EXE = build/$(PROG)

%: build/%
	@:

build/%: src/%.c
	mkdir -p build
	 $(COMPILER) $(FLAGS) $^ -o $@

run: $(EXE)
	./$(EXE)

clean: 
	rm -rf build