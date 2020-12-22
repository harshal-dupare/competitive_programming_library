#pragma once

#include <chrono>
#include <string>
#include <iostream>

class timer
{
public:
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    std::string *event_names;
    double *event_time;
    int at = 0;
    int n;

    timer(int n = 10)
    {
        this->n = n;
        this->start = std::chrono::system_clock::now();
        this->event_names = new std::string[n];
        this->event_time = new double[n];
    }

    void set()
    {
        this->start = std::chrono::system_clock::now();
    }

    double get(int flg = 0)
    {
        this->elapsed_seconds = std::chrono::system_clock::now() - this->start;
        if(flg) this->set();
        return this->elapsed_seconds.count();
    }

    void save(std::string s, int reset = 1)
    {
        if (at == n)
            at = 0;
        event_names[at] = s;
        event_time[at] = this->get();
        if (reset == 1)
            this->set();
        at++;
    }

    void show_events()
    {
        for (int i = 0; i < at; i++)
        {
            std::cout << event_names[i] << ": " << event_time[i] << "\n";
        }
    }
};
