# Project 1: gvShell

For this project, you are going to add features to the simple Unix shell you wrote for Lab 2.

You ~~may~~ should work in teams of two. (This is a large, challenging project. You will want someone to help you debug.)

## Objectives

The objectives for this project are to:
 * Gain in-depth experience with process management
 * Gain in-depth experience using pipes 
 * Gain a deeper understanding of the rich, elegant workflows supported by unix shells
 * Gain experience identifying non-trivial corner cases and building tests for those cases


 ## Specifications

 Write a Unix shell with the following features:
 1. A basic interactive shell that repeatedly reads a command from the standard input and executes that command.
 2. A built-in `exit` command
 3. File redirection (e.g., `ls -l > my_output.txt`)
 4. Piping (e.g., `ls -l | wc -l`)
 5. Processes can be run in the background by placing `&` at the end of a command.
 6. The shell detects input and responds appropriately. (Don't let the shell crash, and don't fail silently.)

 ## Simplifying Assumptions

 1. You need not manage the path yourself. Use `execvp`, which will search the existing path.
 2. You may use the provided parser in `command_line_tokenizer.c`. This code will 
    * handle quotation marks
    * separate the special characters as tokens, and
    * escape special characters (e.g., `echo "Hello, \"Tiny\", how are you?")
 2. You need only handle a single file redirection that appears at the end of the command.  (In other words, things like `ls -l > f1 > f2` or 
    `ls -l > f1 | wc -l` are not valid. )
 3. The only valid location for an `&` is as the last token (e.g., you need not support an entire chain of parallel processes like `cmd1 & cmd2 & cmd3`)

## Approach

Use your code from Lab 2 as a starting point.

1. Replace your tokenizer with a tokenizer that can handle the special characters and quotation marks.
2. Add support for file redirection. 
3. Add support for a single pipe (e.g., `ls -l | wc -l`)
4. Add support for running processes in the background.
5. Check for invalid commands and respond accordingly (e.g., multiple `&` or `&` that doesn't appear at the end)

## Hints

* Implement and test one feature at a time.
* Remember to close file handles after calling `dup2`. (If you don't the process may not recognize that the input is complete causing it to hang.) 
* Use the test program `debug_pipe` to help debug problems with piping. This program will produce output on both `stdout` and `stderr`
  so you can see whether your output is making into the next process in the chain.

## Deliverables

* Your working source code
* A complete test plan. This need not be automated tests (although it can be). A text file of test cases is sufficient.
  (Be sure to include tests that verify your program correctly handles invalid input.)

## Submission

* I must be able to build your shell on EOS using the `make` command.
* Make sure your names appear in all documents that you edit (source code, test plans, etc.)

To submit your project, simply commit and push your code with the phrase `GRADE ME` somewhere in the commit message.


