/*Write a C program to load the binary executable of the previous program in a child
process using exec system call.*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
