// Write a Program for your own Signal Handler which will execute when you type
// Ctrl + D
 
// Ctrl + D is already defined as EOF within the Linux distribution in use,
// therefore EOF will be intercepted by the signal handler, via a custom signal.
 
// Preprocessor Header Files
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
 
// Defining alias for SIGUSR1 as SIGCTRLD for user clarity
// Here SIGUSR1 is used as the signal which will intercept (Ctrl + D), or EOF
#define SIGCTRLD (SIGUSR1)
 
// Defining Boolean True as TRUE macro
#define TRUE 1
 
// Max size of string
#define MAX_STR 150
 
// Method to handle SIGCTRLD signal
void signalHandler(int signalNumber) {
   (signalNumber == SIGCTRLD)
       ? fprintf(stdout, "\nEOF (Ctrl + D) intercepted, exiting program\n")
       : fprintf(stderr, " ");
 
   exit(signalNumber);
}
 
int main(void) {
   // Command string
   char* cmd;
   cmd = (char*) malloc(MAX_STR * sizeof(char));
 
   // Placeholder character
   char ch;
 
   // Registering signalHandler() to intercept the SIGCTRLD signal
   signal(SIGCTRLD, signalHandler);
 
   // Keep program running until "exit" encountered
   do {
      // Prints prompt
      fprintf(stdout, "\n$ ");
 
      // Command string index
      unsigned int i = 0;
 
      while (TRUE) {
         // Checks if Ctrl + D is encountered
         if ((ch = getchar()) == EOF) {
            // Custom signal must be raised as Ctrl + D is not a standard signal
            raise(SIGCTRLD);
         }
 
         // End command string
         if ((ch == '\n') || (i == MAX_STR - 1)) {
            *(cmd + i) = '\0';
            break;
         }
 
         *(cmd + (i++)) = ch;
      }
 
      // Runs command
      system(cmd);
   } while (strcmp(cmd, "exit") != 0);
 
   fprintf(stdout, "Exiting program, going back to shell");
   // Deallocates cmd string
   free(cmd);
 
   return 0;
}
