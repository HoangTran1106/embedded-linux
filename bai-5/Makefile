# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -g

TARGETS = bai1_sigint bai2_timer bai3_process_comm bai4_signal_input bai4_signal_input_poll

all: $(TARGETS)

bai1_sigint: bai1_sigint.c
	$(CC) $(CFLAGS) -o $@ $

bai2_timer: bai2_timer.c
	$(CC) $(CFLAGS) -o $@ $

bai3_process_comm: bai3_process_comm.c
	$(CC) $(CFLAGS) -o $@ $

bai4_signal_input: bai4_signal_input.c
	$(CC) $(CFLAGS) -o $@ $

bai4_signal_input_poll: bai4_signal_input_poll.c
	$(CC) $(CFLAGS) -o $@ $

clean:
	rm -f $(TARGETS)

.PHONY: all clean