#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <mutex>
#include <stdio.h>

#define N 4

using namespace std;
using namespace std::chrono;

mutex m;

int main()
{
    bool isAvailable{true};

    auto strategy = [&](int guest)
    {
        while (true)
        {
            m.lock();
            if (isAvailable)
            {
                printf("Guest %d noticed that the sign reads \"AVAILABLE\" and entered the room.\n", guest);
                isAvailable = false;
                printf("Guest %d set the sign to \"BUSY\".\n", guest);
                m.unlock();

                // to simulate the time it takes to admire the vase
                this_thread::sleep_for(seconds(1));
                break;
            }
            m.unlock();
            printf("Guest %d noticed that the sign reads \"BUSY\", so they continue roaming the castle.\n", guest);

            // simulate the guest roaming the castle
            this_thread::sleep_for(seconds(1));
        }

        m.lock();
        isAvailable = true;
        printf("Guest %d set the sign to \"AVAILABLE\" and exited the room.\n", guest);
        m.unlock();
    };

    auto start = high_resolution_clock::now();
    vector<thread> threads;

    for (int i = 1; i <= N; i++)
        threads.emplace_back(strategy, i);

    for (int i = 0; i < N; i++)
        threads[i].join();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "\n\nRuntime: " << duration.count() / 1e+3 << " seconds" << endl;

    return 0;
}