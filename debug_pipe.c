/*****************************************************************
 * 
 * debug_pipe.c
 * 
 * When given command-line arguments, this program copies those
 * arguments to both the standard output and the standard error.
 * 
 * When given no command-line arguments, this program copies the
 * standard input to both the standard output and the standard
 * error.
 * 
 * This program is useful for debugging the setup of pipes and 
 * file redirection.
 * 
 * (c) 2026 Zachary Kurmas
 *******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int pid = getpid();
   if (argc > 1) {
      printf("Args to stdout (%d):\n", pid);
      fprintf(stderr, "Args to stderr (%d):\n", pid);
      for (int i = 1; i < argc; i++) {
         printf("  (%d out) %2d: %s\n", pid, i, argv[i]);
         fprintf(stderr, "  (%d err) %2d: %s\n", pid, i, argv[i]);
      }
   } else {
      char *line = NULL;
      size_t len = 0;
      ssize_t nread;

      printf("Stdin to stdout (%d):\n", pid);
      fprintf(stderr, "Stdin to stderr (%d):\n", pid);

      int i = 1;
      while ((nread = getline(&line, &len, stdin)) != -1) {
         printf("  (%d out) %2d: %s", pid, i, line);
         fprintf(stderr, "  (%d err) %2d: %s", pid, i, line);
         ++i;
      }
       printf("  (%d out) DONE\n", pid);
       fflush(stdout);
       fprintf(stderr, "  (%d err) DONE\n", pid);
       fflush(stderr);

      free(line);
   }
}
