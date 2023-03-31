# Project 1: _Are you a reader or a writer?_
__This project is partial requirement of ITCS343: Principles of Operating System__  
__Faculty of Information and Communication Technology, Mahidol University, Thailand__  

For this project, we have to use the multithread programming, concurrency, and synchronization concepts to solve the problem. We have to create both the readers and the writers as
the multithread programs. Both the readers and the writers will access a shared list. Per the reader-and-writer problem, you will execute the writers to update the list, and the readers to read the list.

## Collaborators
- 6488069 Chattawat Riyong [Github](https://github.com/derKirschbaum) - host shared github project founder, begin the code, initializing readme.
- 6488112 Napatara Wangthongtana [Github](https://github.com/PattyaWang) - editing and proofread readme files, checking code runability and finalizing readme.
- 6488185 Sanphet Surakool [Github](https://github.com/MonikaElisch) - constructing code, research, editing, checking runability and finalizing the code.

## Prerequisites
- GCC
- Plain text input file containing ***N*** lines where ***0 < N <= 100,000*** lines  
Each line is an integer ***X*** where ***0 < X <= 1,000***

## Usage
- Clone this project
- *(Optional)* You can use `python3 gen.py` to help generate the input, the output of that script is `input.txt`
- For __Windows__ run `gcc ./multithread.c -o multithread.exe -lpthread`
  - then `./multithread.exe <#of writers> <#of readers> <input> <output> <seed> <N>`
- For __Linux__ run `$ gcc ./multithread.c -o multithread -lpthread`
  - then `./multithread <#of writers> <#of readers> <input> <output> <seed> <N>`
 
 ## Libraries
 - <pthread.h>  
 - <semaphore.h>  
 - <stdio.h>  
 - <stdlib.h>  
 - <string.h>  

## Process of the program
1. including libraries and functions and define some values
2. functions and structs for thread, insert item, buffer, start buffer, (pointer) writer, and (pointer) reader
3. ----main function----
4. The program will check the input at the beginning of the main.
5. The program will check if the numbe of the process is not equal to 7 or the program will exit for the standard error.
6. The program will check that number of writers must be from 1 to max writer
7. The program will check that number of readers must be from 1 to max reader
8. The program will check if there is any file, if no file or the file is unable to be opened the program will exit as it could not receive file or input.
9. program always check if the integer must be always from within 1 to Max number that the program defined or it will exit.
10. ----Assigned arguments----
11. we assigned some arguments
12. The assigned argument section started with the input name ( this case, the string will be copied from argv[3])
13. copied name of input
14. The output will be copied from argv[4] which is array no.5 of the argument.
15. copied name of the output file expected
16. the program will set seed before starting the buffer.
17. use the start_bufferlist function
18. ----writer section----
19. read file pointer
20. assign numero ID
21. ----reader section----
22. thread the argument[2] from assigned argument
23. //get size of name of the output file
24. apply name from our input
25. create empty file for writing
26. random amounf of integer on the list
27. ----thread section----
28. starting mutex
29. initializing threads
30. destroy mutex.
31. finished.
