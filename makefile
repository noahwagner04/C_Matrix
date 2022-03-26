.PHONY: all
all: build/libmatrix.a

build/libmatrix.a: build/matrix.o
	ar rcs $@ $<

build/matrix.o: src/matrix.c include/matrix.h
	gcc -Wall -c -I include $< -o $@

.PHONY: clean
clean:
	rm build/matrix.o build/libmatrix.a