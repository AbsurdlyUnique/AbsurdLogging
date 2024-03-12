CC=g++
CFLAGS=-Iinclude
AR=ar
ARFLAGS=rcs
LIBRARY_NAME=liblogger.a
LIBRARY_PATH=build/lib/$(LIBRARY_NAME)
EXAMPLE_EXECUTABLE=logger_example
EXAMPLE_PATH=build/example/$(EXAMPLE_EXECUTABLE)

# Ensure output directories exist
$(shell mkdir -p build/lib build/example)

all: $(LIBRARY_PATH) $(EXAMPLE_PATH)

$(LIBRARY_PATH): logger.o
	$(AR) $(ARFLAGS) $(LIBRARY_PATH) logger.o

logger.o: src/logger.cpp
	$(CC) $(CFLAGS) -c src/logger.cpp

$(EXAMPLE_PATH): $(LIBRARY_PATH)
	$(CC) $(CFLAGS) examples/main.cpp -o $(EXAMPLE_PATH) -Lbuild/lib -llogger

clean:
	rm -f logger.o
	rm -rf build
