/*****************************************************************
 * 
 * gv_shell.c
 * 
 * A simple Unix shell.
 * 
 * **NAME 1**
 * **NAME 2**
 *******************************************************************/

#include "command_line_tokenizer.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Helpful when using pipes
const int READ = 0;
const int WRITE = 1;

const int MAX_TOKENS = 256;

int main(int argc, char *argv[]) {

   char *input = NULL;
   size_t ipt_len = 0;
   int exit_status = 0;

   while (1) {
      ssize_t nread;
      printf("gvShell> ");

      // If a command-line argument is provided, use that instead of 
      // reading from stdin. (This can make debugging easier -- especially
      // if you use llvm on a Mac.)
      if (argc == 1) {
         nread = getline(&input, &ipt_len, stdin);
      } else {
         input = argv[1];
         nread = strlen("input");
      }


      char *tokens[MAX_TOKENS];
      int num_tokens = cl_tokenize(input, tokens, MAX_TOKENS);

      for (int i = 0; i < num_tokens; ++i) {
         printf("   %s\n", tokens[i]);
      }
    
      if (argc > 1) {
         break;
      }
   } // end while

   return exit_status;
} // end main
