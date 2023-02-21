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

In our case, the `cupCake` variable was the critical section of the code. This is because more than one thread might modify this variable at the same time, which could result in inaccurate results or an infinite loop (or other undefined behavior). We used the `mutex` to ensure that the threads have **mutually exclusive** access to this variable.

#### Runtime

I tested the runtime of the program taking the average runtime over `1000` trials. Below are the runtime results of the program for different number of threads:

```
16 threads: less than 0.001 seconds
32 threads: 0.003 seconds
100 threds: 0.034 seconds
1000 threads: 7.584 seconds
```

## Problem 2

### How to run
Use the following commands to run the program:

```
g++ -std=c++20 -pthread problem2.cpp
./a.out
```

Note: Windows Powershell users, the command is `.\a.exe`

### Chosen Strategy

The guests should choose the **second strategy**. This strategy provides the most effective way to ensure that the guests get to see the vase without causing crowds or queues at the door.

#### Advantages

- Using a sign means that the guests do not have to constantly check if the room is available. They can enjoy the party and roam the castle while being able to know if there is someone in the room or not.
- This approach reduces the chances of conflict because the guests will be certain if they can enter the room or not. As long as the sign says "AVAILABLE", they can enter the room that exact moment.
- The approach works better than strategy 1 or 3 as the number of guests grows. It does not require much space in front of the door since the guests can be anywhere in the castle, and would only come to the door if they can (and want to) enter the room.
 
#### Disadvantages

- There is a possibility that a guest would forget to change the status of the sign, which could result in having more than one guest in the room or not allowing any guests at all in the room (or possibly some other undefined behavior).

### Solution Analysis

#### Code

In the solution that was implemented for this problem. Each thread signifies a guest. The solution leverages the use of a `mutex` object provided by the c++ standard library. Whenever a thread needs to access a _critical section_ of the code, it locks the mutex then unlocks it when it is finished.

In our case, the `isAvailable` variable was the critical section of the code. This is because more than one thread might modify this variable at the same time, which could result in inaccurate results or an infinite loop (or other undefined behavior). We used the `mutex` to ensure that the threads have **mutually exclusive** access to this variable.

In this simulation:
- We have 4 guests at the party. This number is arbitrary and can be modified by changing the value of `N`.
- We are simulating the time each guest takes inside the room by sleeping the thread for 1 second.
- We stop the simulation when each guest enters the room once. The code can be easily modified to more accurately simulate a party by having each guest enter the room a different number of times than other guests (or zero times). However, this does not fundamentally affect how the protocol functions.
- We use print statements to visualize when guests enter/exit the room or check the sign.

#### Runtime

I tested the runtime of the program taking the average runtime over `1000` trials. Below are the runtime results of the program for different number of threads:

_Note: each thread will sleep for at least 1 second (the time the guest spends in the room), so that will affect the runtime of the program._

```
(Update these values)
16 threads: less than 0.001 seconds
32 threads: 0.003 seconds
100 threds: 0.034 seconds
1000 threads: 7.584 seconds
```