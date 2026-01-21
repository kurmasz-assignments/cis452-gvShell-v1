# Project 1: gvShell

For this project, you are going to add features to the simple Unix shell you wrote for Lab 2.

You are strongly encouraged to work in teams of two. This project is complex, and collaboration will help with design and debugging.

## Objectives

The objectives for this project are to:
 * Gain hands-on experience managing Unix processes, including foreground and background execution
 * Implement and test file redirection and inter-process communication using pipes
 * Gain a deeper understanding of the rich, elegant workflows supported by Unix shells
 * Design test cases that reveal subtle concurrency or I/O bugs in multi-process programs

 ## Specifications

 Write a Unix shell with the following features:
 1. A basic shell that has two modes of operation:
    * If the process is passed no command line arguments, the shell should be interactive and repeatedly read a command from the standard input then execute it. The shell should terminate when either the user enters `exit` or when end-of-file (EOF) is reached on the standard input. 
    * If there are command-line arguments, iterate through those arguments and treat each as a complete command. (If a command comprises multiple tokens, then enclose the command in quotes.) The shell should terminate after executing all the given commands.
 2. A built-in `exit` command
 3. File redirection (e.g., `ls -l > my_output.txt`)
 4. Piping (e.g., `ls -l | wc -l`)
 5. Processes can be run in the background by placing `&` at the end of a command
 6. The shell reports the exit status of every process
    * For synchronous processes (i.e., no `&`), report PID and exit status immediately after completion before prompting for a new command. Use a phrase like this: `"Process %d terminated with exit status %d\n"`
    * Before prompting the user for a command, check whether any asynchronous (background) processes have completed. If so, report their pid and exit status. Provide the status of _all_ completed processes in a chain of piped commands. Use a phrase like this: `"Background process %d terminated with exit status %d\n"` 
 7. The shell detects invalid input and responds appropriately. (Don't let the shell crash, and don't fail silently.)
 8. The shell’s exit value is determined by the execution of all commands processed during a session. The shell must exit with status 0
    if and only if every command is valid and completes successfully. The shell must exit with a non-zero status if any of the following occur at any point:
    * A command is invalid (e.g., improperly formatted)
    * A command fails to execute (e.g., the executable is not found)
    * A command executes but returns a non-zero exit status
    (Automated tests rely on this behavior)

In addition, you must prepare a thorough test plan. 

 ## Simplifying Assumptions

 1. You need not manage the path yourself. Use `execvp`, which will search the current path.
 2. You may use the provided parser in `command_line_tokenizer.c`. This code will 
    * handle quotation marks
    * handle whitespace (including extra whitespace)
    * separate the special characters as tokens, and
    * escape special characters (e.g., `echo "Hello, \"Tiny\", how are you?")
 3. You need only handle a single file redirection and it must appear at the end of the command.  (In other words, you need not support commands that combine multiple redirections or place the redirection anywhere but after the final step.
 4. Input redirection is optional. 
 5. The only valid location for an `&` is as the last token (e.g., you need not support an entire chain of parallel processes like `cmd1 & cmd2 & cmd3`)
 6. You need not implement these common shell features (however, the first one is straightforward and may be helpful)
    * File system navigation (e.g., `cd`)
    * Environment variables (e.g., `$HOME`)
    * Globs (`*`)
    * Signal handling

## Approach

Use your code from Lab 2 as a starting point.

1. Replace your tokenizer with a tokenizer that can handle the special characters and quotation marks
    * I have provided such a tokenizer in `command_line_tokenizer.c`. You are not required to use it.
2. Implement file redirection.
3. Implement a single pipe (e.g., `ls -l | wc -l`)
4. Implement background execution with `&`
5. Implement a chain of pipes (e.g., `ls -l | grep Jan | wc -l`)
6. Check for invalid commands and respond accordingly (e.g., multiple `&`, misplaced redirection, etc.)

## Test Plan 

Multi-process programs are susceptible to many subtle bugs. Brainstorming 
all the possible corner cases is an important aspect of developing multi-process programs. 

Prepare a written test plan. This need not be automated tests (although it can be). A text file listing test cases is sufficient. 
Each test case should contain
* A description of the test (e.g., "file redirection with no command")
* An example input (e.g., `> foobar.txt`)
* The expected output (e.g., "Shell responds with 'Invalid command' and re-prompts user")

Please divide your test plan into two categories:

1. Correctly formatted commands that exercise features of the shell (file redirection, piping, etc.)
2. Incorrectly formatted commands and the expected response

Don't forget to check for
* Zombie processes
* Memory leaks

## Hints

* Implement and test one feature at a time.
* Remember to close file handles after calling `dup2`. (If you don't the process may not recognize that the input is complete causing it to hang.) 
* Use the test program `debug_pipe` to help debug problems with piping. This program will produce output on both `stdout` and `stderr`
  so you can see whether your output is making into the next process in the chain.

## Deliverables

* Your working source code
* Your test plan and/or test code

## Submission

* I must be able to build your shell on EOS using the `make` command
* Make sure your names appear in all documents that you edit (source code, test plans, etc.)
* List any extra features you add (e.g., the ability for a command to contain multiple background processes).

To submit your project, simply commit and push your code with the phrase `GRADE ME` somewhere in the commit message.


