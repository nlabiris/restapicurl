CFLAGS=-Wall -I include
LDFLAGS=-L /usr/lib/i386-linux-gnu/libcurl.so
LDLIBS=-ljansson -lcurl -lm
TARGET=bin/main
.PHONY: all clean help

# Make executables for all targets
all: $(TARGET)

$(TARGET): src/main.o src/api.o src/json.o src/list.o
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@ $(LDLIBS)

main.o: src/main.c src/api.c include/api.h src/json.c include/json.h src/list.c include/list.h
	$(CC) $(CFLAGS) -c $<

api.o: src/api.c include/api.h
	$(CC) $(CFLAGS) -c $<

json.o: src/json.c include/json.h
	$(CC) $(CFLAGS) -c $<

list.o: src/list.c include/list.h
	$(CC) $(CFLAGS) -c $<

# Clean object files
clean:
	@echo "\033[1;32mDeleting object files...\033[0m"
	rm src/*.o
	@echo "\033[1;32mDone.\033[0m"

# Print help
help:
	@echo "Usage: make all                 # Compile"
	@echo "       make clean               # Delete any object files"
	@echo "       make help                # Print this help message"