/*
 * plotRealTime.h
 *
 *  Created on: 28.07.2022
 *      Author: andreas
 */

#ifndef PLOTTING_PLOTREALTIME_H_
#define PLOTTING_PLOTREALTIME_H_

#include <functional>
#include <string>
#include <thread>
#include <chrono>
#include <deque>
#include <gnuplot-iostream.h>

using namespace std;
using namespace std::chrono;
using namespace std;
using std::thread;
using namespace std::chrono;
using namespace std::this_thread;

class plotRealTime {
public:
    plotRealTime(double interval=0.02, int samples=300);
    virtual ~plotRealTime();

    void addEntry(function<double()> value, string name, string color);

    void start();
    void stop(bool closeWindow = true);

private:

    struct plotEntry {
        plotEntry(int samples, function<double()>  v, string n, string c) : data(samples, 0.0) {
            value = v;
            name  = n;
            color = c;
        }
        function<double()>  value;
        string              name;
        string              color;
        deque<double>       data;
    };

    double round6(double);

    vector<plotEntry>   _plotEntries;
    double  _interval;
    bool    _running;
    thread  _thread;
    int     _samples;
    Gnuplot _gp;
};

#endif /* PLOTTING_PLOTREALTIME_H_ */
