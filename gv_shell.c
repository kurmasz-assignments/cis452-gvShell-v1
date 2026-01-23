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
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

// Helpful when using pipes
const int READ = 0;
const int WRITE = 1;

const int MAX_TOKENS = 256;

int main(int argc, char *argv[]) {

   char *input = NULL;
   size_t ipt_len = 0;
   int exit_status = 0;

   int command_num = 1;
   while (argc == 1 || (argc > 1 && command_num < argc)) {
      
      ssize_t nread;
      if (argc == 1) {
         // Take commands from stdin
         printf("gvShell> ");
         nread = getline(&input, &ipt_len, stdin);
      } else {
         // Take commands from command line for debugging purposes
         input = argv[command_num];
         printf("gvShell p%d> %s\n", command_num , input);
         nread = strlen("input");
         ++command_num;
      }


      char *tokens[MAX_TOKENS];
      int num_tokens = cl_tokenize(input, tokens, MAX_TOKENS);

      for (int i = 0; i < num_tokens; ++i) {
         printf("   %s\n", tokens[i]);
      }
   } // end while

   return exit_status;
} // end main
