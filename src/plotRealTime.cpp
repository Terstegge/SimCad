/*
 * plotRealTime.cpp
 *
 *  Created on: 28.07.2022
 *      Author: andreas
 */

#include "plotRealTime.h"
#include <chrono>
#include <cmath>
using namespace std;
using std::thread;
using namespace std::chrono;
using namespace std::this_thread;

plotRealTime::plotRealTime(double interval, int samples)
: _gp(/*"tee script.gp | gnuplot"*/) {
    _running    = false;
    _interval   = interval;
    _samples    = samples;

    _gp << scientific << setprecision(3);
}

plotRealTime::~plotRealTime() {
    stop(false);
}

void plotRealTime::addEntry(function<double()> value, string name, string color) {
    _plotEntries.emplace_back(_samples, value, name, color);
}

void plotRealTime::start() {
    if (!_running) {
        _running = true;
        _thread = thread([&]() {
            double xrange_start = -(_samples-1) * _interval;
            double xrange_end   =  0.0;
            auto startTime = system_clock::now();
            // Set y range
            //_gp << "set yrange [-0.001:0.01]\n";
            _gp << "set autoscale y\n";
            while (_running) {
                // Set xrange
                _gp << "set xrange [" << xrange_start << ":" << xrange_end << "]\n";

                // Update data
                for (auto & elem : _plotEntries) {
                    elem.data.pop_front();
                    elem.data.push_back( elem.value() );
                }

                // Plot command
                _gp << "plot";
                int index = 2;
                for (auto & elem : _plotEntries) {
                    _gp << " '-'";
                    _gp << " u 1:" << index++;
                    _gp << " with lines";
                    _gp << " lc '"    << elem.color << "'";
                    _gp << " title '" << elem.name << "',";
                }
                _gp << "\n";

                // Plot data
                for (int i = 0; i < _samples; ++i) {
                    _gp << ( xrange_start + i * _interval);
                    for (auto & elem : _plotEntries) {
                        _gp << " " << ( elem.data[i] );
                    }
                    _gp << "\n";
                }
                _gp << "e\n";
                //_gp.flush();

                // Wait for another interval
                startTime += milliseconds((int)(_interval * 1000));
                sleep_until(startTime);

                // Update xrange
                xrange_start += _interval;
                xrange_end   += _interval;
            }
            sleep_for(milliseconds(500));
        });
    }
}

void plotRealTime::stop(bool closeWindow) {
    if (_running) {
        _running = false;
        _thread.join();
    }
    if (closeWindow) _gp << "set terminal qt close\n";
}

double plotRealTime::round6(double v) {
    return 1e6 * round(v * 1e6);
}

