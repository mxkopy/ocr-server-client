CC              = g++
CPP             = src/cpp
HPP             = src/hpp
BUILD           = build
CFLAGS          = -Wall -Wno-infinite-recursion -MMD -MP -MF build/.d -g -O2
INCL            = -I$(HPP) -I$(CPP)
LIBS            = -ltesseract -lpng -lleptonica -lboost_serialization
SOURCES         = $(wildcard $(CPP)/*)
HEADERS         = $(wildcard $(HPP)/*)
SERVER_SOURCES  = $(filter-out $(CPP)/tesseract_client.cpp, $(SOURCES))
CLIENT_SOURCES  = $(filter-out $(CPP)/tesseract_server.cpp, $(SOURCES))

build:
	mkdir build

client: $(SOURCES) $(HEADERS) build
	$(CC) -DCLIENT_MAIN $(CLIENT_SOURCES) $(INCL) $(CFLAGS:.d=$@.d) $(LIBS) -o client

server: $(SOURCES) $(HEADERS) build
	$(CC) -DSERVER_MAIN $(SERVER_SOURCES) $(INCL) $(CFLAGS:.d=$@.d) $(LIBS) -o server

.PHONY: clean remove

clean:
	@ rm build/*

remove: 
	@ rm client server

-include tesseract_server.d tesseract_server.d