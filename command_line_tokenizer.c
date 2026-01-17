/*****************************************************************
 * 
 * command_line_tokenizer.c
 * 
 * A somewhat simple tokenizer for a simple unix shell.
 * 
 * (c) 2026 Zachary Kurmas
 *******************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 const char SINGLE_TOKENS[] = "><&|;";

int contains_char(char c, const char *str) {
   if (str == NULL)
      return 0; // handle NULL pointer

   for (; *str != '\0'; str++) {
      if (*str == c) {
         return 1;
      }
   }
   return 0;
}

int cl_tokenize(char *line, char *tokens[], int max_tokens) {

   int token_count = 0;
   char *src = line;
   char buffer[4096]; // Temporary buffer for building tokens
   int buf_idx;

   // Skip leading whitespace
   while (*src && isspace(*src)) {
      src++;
   }

   while (*src && token_count < max_tokens - 1) {
      buf_idx = 0;

      // Check for special operators that are always separate tokens
      if (*src == '>' && *(src + 1) == '>') {
         buffer[buf_idx++] = '>';
         buffer[buf_idx++] = '>';
         buffer[buf_idx] = '\0';
         src += 2;
         tokens[token_count] = strdup(buffer);
         token_count++;
      } else if (contains_char(*src, SINGLE_TOKENS)) {
         buffer[buf_idx++] = *src;
         buffer[buf_idx] = '\0';
         src++;
         tokens[token_count] = strdup(buffer);
         token_count++;
      }
      // Handle quoted strings (single or double quotes)
      else if (*src == '"' || *src == '\'') {
         char quote_char = *src;
         src++; // Skip opening quote

         while (*src) {
            if (*src == '\\' && *(src + 1)) {
               // Escape sequence - add the next character literally
               src++;
               buffer[buf_idx++] = *src;
               src++;
            } else if (*src == quote_char) {
               // Found closing quote
               src++;
               break;
            } else {
               buffer[buf_idx++] = *src;
               src++;
            }
         }

         buffer[buf_idx] = '\0';
         tokens[token_count] = strdup(buffer);
         token_count++;
      }
      // Handle regular tokens
      else {
         while (*src && !isspace(*src)) {
            // Check if we hit a special character
            if (contains_char(*src, SINGLE_TOKENS)) {
               break;
            }

            if (*src == '\\' && *(src + 1)) {
               // Escape sequence
               src++;
               buffer[buf_idx++] = *src;
               src++;
            } else if (*src == '"' || *src == '\'') {
               // Embedded quote in the middle of a token
               char quote_char = *src;
               src++; // Skip opening quote

               while (*src) {
                  if (*src == '\\' && *(src + 1)) {
                     src++;
                     buffer[buf_idx++] = *src;
                     src++;
                  } else if (*src == quote_char) {
                     src++;
                     break;
                  } else {
                     buffer[buf_idx++] = *src;
                     src++;
                  }
               }
            } else {
               buffer[buf_idx++] = *src;
               src++;
            }
         }

         if (buf_idx > 0) {
            buffer[buf_idx] = '\0';
            tokens[token_count] = strdup(buffer);
            token_count++;
         }
      }

      // Skip whitespace between tokens
      while (*src && isspace(*src)) {
         src++;
      }
   }

   tokens[token_count] = NULL;
   return token_count;
}