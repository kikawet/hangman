#include <chrono>

#ifndef TIMER_H
#define TIMER_H

template <class TimeT = std::chrono::milliseconds,
          class ClockT = std::chrono::steady_clock>
class Timer
{
    using timep_t = typename ClockT::time_point;
    timep_t _start = ClockT::now(), _end = {};

public:
    void start() { 
        _end = timep_t{}; 
        _start = ClockT::now(); 
    }
    
    void end() { _end = ClockT::now(); }
    
    template <class TT = TimeT> 
    std::size_t duration() { 
        if(_end == timep_t{}) this->end();
        return std::chrono::duration_cast<TT>(_end - _start).count(); 
    }
};

#endif // TIMER_H