all: web-client

web-client: bin/web-client

bin/web-client: ./main.cpp ./src/*.cpp ./lib/*.h | bin
	g++ ./*.cpp ./src/*.cpp -I ./lib -o bin/web-client

bin:
	mkdir bin

clean:
	rm -rf bin