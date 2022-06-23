// Write a program to generate maximum number of child processes in your system
// and with the help of program explain what are Zombie process

// The program needs `ulimit -u` as command line arguments.
// ulimit -u gives the process limit and is used such that the program can get
// the maximum number of processes for the current non-root user

// In this program, if top or htop is executed simultaneously with the program,
// one can see the processes being generated, followed by them being converted
// into Zombie processes, which are processes that have finished execution but
// remain in the process list

// Preprocessor Header Files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to clear temporary file
void clearFile() {
   FILE* fp;
   fp = fopen("temp.txt", "w");
   fclose(fp);
}

int main(int argc, char* argv[]) {
   // Gets the maximum possible processes for the current user using the `ulimit
   // -u` command
   const unsigned int processLimit = atoi(argv[1]);

   // Creating an empty temporary file
   FILE* fp;
   clearFile();

   // Variable to count number of processes formed
   int processCount = 0;

   // Loop to form child processes upto a max of processLimit
   for (int i = 0; i < processLimit; i++) {
      // Checks whether child process is formed. If formed, a character is
      // appended to the temporary file to keep track of the number of processes
      // generated
      if (fork() == 0) {
         fp = fopen("temp.txt", "a");
         fprintf(fp, "0");
         fclose(fp);

         // Exiting child process
         exit(0);
      }
   }

   // Counting number of processes generated using the temp file
   FILE* fptr;
   fptr = fopen("temp.txt", "r");
   int c;

   // Counting number of characters in the file, which corresponds to the number
   // of child processes generated
   while ((c = getc(fptr)) != EOF) {
      processCount++;
   }

   fclose(fptr);

   clearFile();

   fprintf(stdout, "Number of child processes generated: %d", processCount);

   fprintf(stdout, "\n\nPress any key to exit");
   getchar();

   return 0;
}
