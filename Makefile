CC      = gcc
CFLAGS  = -Wall -g

.PHONY: all clean

all: debug_pipe gv_shell 

debug_pipe: debug_pipe.c
	$(CC) $(CFLAGS) debug_pipe.c -o debug_pipe

gv_shell: gv_shell.c command_line_tokenizer.c
	$(CC) $(CFLAGS) gv_shell.c command_line_tokenizer.c -o gv_shell

clean:
	rm -f debug_pipe gv_shell
