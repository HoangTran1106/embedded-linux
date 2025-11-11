# Makefile for Linux System Programming Exercises

CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executables
TARGETS = filestat process_basic process_exec process_zombie process_orphan

# Default target - build all
all: $(TARGETS)

# Exercise 1: File metadata checker
filestat: filestat.c
	$(CC) $(CFLAGS) -o filestat filestat.c

# Exercise 2: Process operations
process_basic: process_basic.c
	$(CC) $(CFLAGS) -o process_basic process_basic.c

process_exec: process_exec.c
	$(CC) $(CFLAGS) -o process_exec process_exec.c

process_zombie: process_zombie.c
	$(CC) $(CFLAGS) -o process_zombie process_zombie.c

process_orphan: process_orphan.c
	$(CC) $(CFLAGS) -o process_orphan process_orphan.c

# Clean up compiled files
clean:
	rm -f $(TARGETS)

# Test filestat
test_filestat: filestat
	@echo "=== Testing filestat ==="
	@echo "\n1. Testing with regular file:"
	./filestat filestat.c
	@echo "\n2. Testing with directory:"
	./filestat .
	@echo "\n3. Testing with symbolic link (if exists):"
	@ln -sf filestat.c test_link 2>/dev/null || true
	@./filestat test_link 2>/dev/null || true
	@rm -f test_link

# Run all process demos
test_process: $(TARGETS)
	@echo "=== Testing Process Basic ==="
	./process_basic
	@echo "\n\n=== Testing Process Exec ==="
	./process_exec
	@echo "\n\n=== Testing Zombie Process ==="
	@echo "Run './process_zombie' and check 'ps aux | grep defunct' in another terminal"
	@echo "\n=== Testing Orphan Process ==="
	./process_orphan

.PHONY: all clean test_filestat test_process
