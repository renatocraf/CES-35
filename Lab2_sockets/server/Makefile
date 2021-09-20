all: web-server

web-server: bin/web-server

bin/web-server: ./server.cpp ./src/*.cpp ./lib/*.h | bin
	g++ ./*.cpp ./src/*.cpp -I ./lib -o bin/web-server -lpthread

bin:
	mkdir bin
	cp ./file/ola.html ./bin/ola.html
	cp ./file/index.html ./bin/index.html

clean:
	rm -rf bin
