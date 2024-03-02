// created by Ceren Duru Cinar 

#include <iostream>
#include <iomanip>        // for put_time
#include <thread>
#include <chrono>         // for chrono::system_clock
#include <ctime> // for time_t, tm, localtime, mktime
#include <string>
#include <mutex>
#include <vector>
#include "IntQueueHW6.h"
using namespace std;

mutex sit_mutex;

void sit(IntQueueHW6 & q, int id, struct tm * ptm)
{
    // Begin code taken from lecture slides
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));
    // End code taken from lecture slides
    sit_mutex.lock(); // locking the mutex for enqueuing
    if (!q.isFull()) // checking if it is full
    {
        q.enqueue(id);
        // Begin code taken from lecture slides
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // current time
        struct tm *ptm2 = localtime(&tt);
        // End code taken from lecture slides
        cout<< "Player " << id <<" captured a chair at "<< put_time(ptm2,"%X") <<endl;
        sit_mutex.unlock(); // unlocking mutex
    }
    else
    {
        cout<< "Player " << id << " couldn't capture a chair." << endl;
        sit_mutex.unlock();
    }

}

int main()
{
    int player_num, chair_num, player;
    cout << "Welcome to Musical Chairs game!" << endl;
    cout << "Enter the number of players in the game:" << endl;
    cin >> player_num;
    chair_num = player_num-1;
    vector<int> players; // vector for current players
    for (int i = 0; i < player_num; i++)
    {
        players.push_back(i);
    }
    cout << "Game Start!" << endl << endl;
    while (player_num > 1)
    {
        IntQueueHW6 chair_queue(chair_num);
        // Begin code taken from lecture slides
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm *ptm = localtime(&tt);
        // End code taken from lecture slides
        cout << "Time is now " << put_time(ptm,"%X")<<endl;
        if (ptm->tm_sec + 2 >= 60) // handling second >= 60
        {
            ptm->tm_sec = (ptm->tm_sec + 2) % 60;
            if (ptm->tm_min + 1 >= 60) // handling minute >= 60
            {
                ptm->tm_min = (ptm->tm_min + 1) % 60;
                ptm->tm_hour += 1;
            }
            else
            {
                ptm->tm_min+= 1;
            }
        }
        else
        {
            ptm->tm_sec+=2;
        }
        thread * threads = new thread[player_num]; // thread array
        for (int i = 0; i < player_num; i++)
        {
            threads[i] = thread(&sit, ref(chair_queue), players[i], ptm);
        }
        for (int i = 0; i < player_num; i++)
        {
            threads[i].join(); // joining the threads
        }
        for (int i = 0; i < player_num; i++)
        {
            players.pop_back();
        }
        cout << "Remaining players are as follows: ";
        while (!chair_queue.isEmpty()) // dequeueing the players and displaying
        {
            chair_queue.dequeue(player);
            cout << player << " ";
            players.push_back(player); // holding current players
        }
        cout << endl << endl;
        player_num -= 1; // eliminating a player
        chair_num -= 1;
        delete [] threads;
    }

    cout << "Game over!" << endl;
    cout << "Winner is Player " << player << "!" << endl;

    return 0;
}
