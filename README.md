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
