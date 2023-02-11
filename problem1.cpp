#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <mutex>

#define N 100

using namespace std;
using namespace std::chrono;

atomic<bool> cupCake{true};
mutex m;

int main()
{
    atomic<int> numSeen{0};

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
                    // cout << "decider has entered\n";
                }

                m.lock();
                if (!cupCake)
                {
                    // cout << "pow\n";
                    cupCake = true;
                    numSeen++;
                }
                m.unlock();
            }
            else
            {
                if (numSeen == 0)
                {
                    // cout << "alreadyEntered\n";
                    continue;
                }
                
                m.lock();
                if (cupCake && !alreadyEntered)
                {
                    // cout << "boom\n";
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