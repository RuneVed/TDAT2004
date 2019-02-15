#include <iostream>
#include <thread>
#include <vector>
#include <math.h>
#include <mutex>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Method for checking if a number is prime;
bool isPrime(int number){
    for (int i =2; i*i<=number;i++){
        if(number%i == 0){
            return false;
        }
    }
    return true;
}

// Printing a vector
void print(std::vector<int> const &input){
    cout << " "<<endl;
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
    cout << " "<<endl;
}

// Main
int main() {

    vector<thread> threads;
    vector<int> primes; // Put the found primes here
    mutex mutex;

    int lowerLimit;
    cout << "Enter the lower number of the intervall you wanna check: ";
    cin >> lowerLimit;

    int upperLimit;
    cout << "Enter the upper number of the intervall you wanna check: ";
    cin >> upperLimit;

    int numberOfThreads;
    cout << "How many threads? ";
    cin >> numberOfThreads;

    auto start = high_resolution_clock::now();

    int intervall = upperLimit/numberOfThreads;

    for (int i = 0; i < numberOfThreads; ++i) {
        int lower = lowerLimit +intervall * i;
        int upper = lowerLimit+ intervall*(i+1)-1;
        if (i == numberOfThreads -1){
            upper = upperLimit;
        }

        //Printing out upper and lower limits for each thread.
        cout << "lower " << lower << endl;
        cout << "upper " << upper << endl;

        threads.emplace_back([&mutex, &primes, lower, upper] { // Do not capture i as reference (&i)
            for (int j = lower; j<=upper; j++){
                if (isPrime(j)){
                    mutex.lock();
                    primes.push_back(j);
                    mutex.unlock();
                }
            }
        });
    }

    // Joining the threads
    for (auto &thread : threads)
        thread.join();

    // Sort primes vector
    sort(primes.begin(),primes.end());

    //Print primes vector
    print(primes);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Microseconds taken to find primes: " <<duration.count() << endl;

    // Number of primes
    cout << "Number of primes: " << primes.size() << endl;
}