/*****************************************************************
 * 
 * command_line_tokenizer.h
 * 
 * A somewhat simple tokenizer for a simple unix shell.
 * 
 * (c) 2026 Zachary Kurmas
 *******************************************************************/

int cl_tokenize(char *line, char *tokens[], int max_tokens);
extern const char SINGLE_TOKENS[];