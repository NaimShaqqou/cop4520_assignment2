# COP 4520 Assignment 2

## Problem 1

### How to run
Use the following commands to run the program:

```
g++ -std=c++20 -pthread problem1.cpp
./a.out
```

Note: Windows Powershell users, the command is `.\a.exe`

### Approach

- One of the guests will be appointed as the "decider". The decider's job is to count the number of unique guests whoentered the labyrinth. 
- Each guest (except for the decider) eats the cupcake ONLY ONCE.
- If a guest enters the labyrinth and finds that the cupcake is eaten, they do nothing. They can eat it when the minotaur brings out a new one.
- If the decider enters the room and finds the cupcake has been eaten, they can guarantee that one NEW UNIQUE guest has entered the room. At this point, they can ask for a new cupcake to be brought out.
- As soon as the cupcake has been eaten N - 1 times (decider doesn't need to eat it), the decider knows that all N guests have entered the labyrinth.

### Solution Analysis

#### Code

In the solution that was implemented for this problem. Each thread signifies a guest. The solution leverages the use of a `mutex` object provided by the c++ standard library. Whenever a thread needs to access a _critical section_ of the code, it locks the mutex then unlocks it when it is finished.

In our case, the `cupCake` variable was the critical section of the code. This is because more than one thread might modify this variable at the same time, which could result in inaccurate results or an infinite loop. We used the `mutex` to ensure that the threads have **mutually exclusive** access to this variable.

#### Runtime

I tested the runtime of the program taking the average runtime over `1000` trials. Below are the runtime results of the program for different number of threads:

```
16 threads: less than 0.001 seconds
32 threads: 0.003 seconds
100 threds: 0.034 seconds
1000 threads: 7.584 seconds
```