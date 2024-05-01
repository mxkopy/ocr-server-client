CC              = g++
CPP             = src/cpp
HPP             = src/hpp
BUILD           = build
CFLAGS          = -Wall -Wno-infinite-recursion -MMD -MP -MF build/.d -g -O2
INCL            = -I$(HPP) -I$(CPP)
LIBS            = -ltesseract -lpng -lleptonica -lboost_serialization -lasio-network
SOURCES         = $(wildcard $(CPP)/*)
HEADERS         = $(wildcard $(HPP)/*)
OBJECTS         = $(patsubst $(CPP)/%.cpp, %, $(wildcard $(CPP)/*))

build: build-dir asio-network-main client server

build-dir:
	mkdir -p $(BUILD)

asio-network-main: build-dir
	cd build && wget -O asio-network-main.tar.gz https://github.com/mxkopy/asio-network/archive/main.tar.gz
	cd build && tar -xvf asio-network-main.tar.gz
	cd build/asio-network-main && make && make install

$(BUILD)/%.o: $(CPP)/%.cpp $(HPP)/%.hpp
	$(CC) $< -c $(CFLAGS:.d=$*.d) $(INCL) $(LIBS) -o $@

client: $(BUILD)/tesseract_client.o
	$(CC) -DCLIENT_MAIN $(CPP)/main.cpp $(INCL) $(CFLAGS:-MMD -MP -MF build/.d=) $(LIBS) -o client

server: $(BUILD)/tesseract_server.o
	$(CC) -DSERVER_MAIN $(CPP)/main.cpp $(INCL) $(CFLAGS:-MMD -MP -MF build/.d=) $(LIBS) -o server

.PHONY: clean remove

clean:
	@ rm -rf build/*

remove: 
	@ rm client server
