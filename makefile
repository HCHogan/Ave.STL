export CC = clang++ -std=c++11

all: test02.cpp
	$(CC) -o test02 test02.cpp -g

run:
	./test02

debug:
	lldb ./test02

clean:
	rm -r ./test02
