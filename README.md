# Project 1: _Are you a reader or a writer?_
__This project is partial requirement of ITCS343: Principles of Operating System__  
__Faculty of Information and Communication Technology, Mahidol University, Thailand__  

For this project, we have to use the multithread programming, concurrency, and synchronization concepts to solve the problem. We have to create both the readers and the writers as
the multithread programs. Both the readers and the writers will access a shared list. Per the reader-and-writer problem, you will execute the writers to update the list, and the readers to read the list.

## Collaborators
- 6488069 Chattawat Riyong [Github](https://github.com/derKirschbaum)
- 6488112 Napatara Wangthongtana [Github](https://github.com/PattyaWang)
- 6488185 Sanphet Surakool [Github](https://github.com/MonikaElisch)

## Prerequisites
- GCC
- Plain text input file containing ***N*** lines where ***0 < N <= 100,000*** lines  
Each line is an integer ***X*** where ***0 < X <= 1,000***

## Usage
- Clone this project
- For __Windows__ run `gcc ./multithread.c -o multithread.exe`
  - then `./multithread.exe <#of writers> <#of readers> <input> <output> <seed> <N>`
- For __Linux__ run `$ gcc ./multithread.c -o multithread`
  - then `./multithread <#of writers> <#of readers> <input> <output> <seed> <N>`

## Process of the program
1. The program will check the input at the beginning of the main.
2. The program will check if the numbe of the process is not equal to 7 or the program will exit for the standard error.
3. The program will check if the number of the array must be more than 1 otherwise it is not valid and exit.
4. The program will check that the array will always start at 1.
5. The program will check if there is any file, if no file or the file is unable to be opened the program will exit as it could not receive file or input.
6. program always check if the integer must be always from within 1 - 1000
7. In this case, we have Max number defined by 100000 however, this could be change. The program will check that the amount of integer must not exceed the MAX_NUMBER
8. The assigned argument section started with the input name ( this case, the string will be copied from argv[3] "array no. 4 of the argument" )
// no.8 simply copied the name of the input
9. The output will be copied from argv[4] which is array no.5 of the argument.
// no.9 simply copied the name of the output
10. the program will set seet before starting the buffer.
11. destroy semaphores
12. program exit
