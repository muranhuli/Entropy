CC = g++
CFLAGS = -std=c++17 -Wall -O3

include_path = include
I_include = $(include_path:%=-I%)

cpp_src = $(shell find src -name "*.cpp")
cpp_obj = $(patsubst src/%.cpp, obj/%.o, $(cpp_src))

obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(I_include) -c $^ -o $@

bin/hypergraph_merge: $(cpp_obj)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o bin/hypergraph_merge

debug:
	@echo $(cpp_obj)

clean:
	rm -rf obj/
	rm -rf bin/

.PHONY: clean debug run
