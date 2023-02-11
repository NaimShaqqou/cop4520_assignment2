#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <mutex>

#define N 100 // number of guests

using namespace std;
using namespace std::chrono;

// true -> not eaten
// false -> eaten
atomic<bool> cupCake{true};
mutex m;

int main()
{
    // This is the number of unique guests who
    // entered the labyrinth
    atomic<int> numSeen{0};
    
    /*
        - One of the guests will be appointed as the "decider".
          The decider's job is to count the number of unique guests who
          entered the labyrinth. 
        - Each guest (except for the decider) eats the cupcake ONLY ONCE.
        - If a guest enters the labyrinth and finds that the cupcake is eaten, they
          do nothing. They can eat it when the minotaur brings out a new one.
        - If the decider enters the room and finds the cupcake has been eaten,
          they can guarantee that one NEW UNIQUE guest has entered the room.
        - As soon as the cupcake has been eaten N times, the decider knows that
          all N guests have entered the labyrinth 
    */
    auto strategy = [&](bool isDecider)
    {
        bool alreadyEntered = false;
        while (numSeen < N)
        {
            if (isDecider)
            {
                if (!alreadyEntered)
                {
                    numSeen++;
                    alreadyEntered = true;
                }

                m.lock();
                if (!cupCake)
                {
                    cupCake = true;
                    numSeen++;
                }
                m.unlock();
            }
            else
            {
                if (numSeen == 0)
                    continue;
                
                m.lock();
                if (cupCake && !alreadyEntered)
                {
                    cupCake = false;
                    alreadyEntered = true;
                }
                m.unlock();
            }
        }
    };

    auto start = high_resolution_clock::now();
    vector<thread> threads;

    // the first guest is the one that can decide
    // whether everyone has seen the cupcake
    threads.emplace_back(strategy, true);

    for (int i = 1; i < N; i++)
        threads.emplace_back(strategy, false);

    for (int i = 0; i < N; i++)
        threads[i].join();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << duration.count() / 1e+3 << endl;

    return 0;
}