// Timer.h documents a simple, platform-independent interval timer
//  that measures CPU usage in (fractional) seconds. 
//  
// Author: Joel Adams, for Hands On C++.
// Date:   November 1997
//
// Revision History
//
// Seconds() added - kvlinden, 5-Feb-98
//
// ANSI compliance, interface improvements
//  - Adams, March, 1998.
//

#ifndef TIMER
#define TIMER

#include <iostream>   // ostream
#include <ctime>      // C time library: clock_t, clock(), CLOCKS_PER_SEC
using namespace std;

class Timer
{
public:
  Timer();
  void Start();
  void Stop();
  void Reset();
  double Seconds() const;
  void Print(ostream & out) const;

private:
  clock_t myStartTime;
  clock_t myRunTime;
  bool running;
};

//***************************************************************
// Timer constructor.                                           *
// Postcondition: myStartTime == 0 && myRunTime == 0 &&         *
//                 running == false.                            *
//***************************************************************
inline Timer::Timer()
{
  myStartTime = myRunTime = 0;
  running = false;
}

//***************************************************************
// Start myself.                                                *
// Postcondition: myStartTime == the current clock value &&     *
//                 running == true.                             *
// Note: Start() while I'm running re-starts me.                *
//***************************************************************
inline void Timer::Start()
{
  running = true;
  myStartTime = clock();
}

//***************************************************************
// Stop myself.                                                 *
// Precondition:  running == true.                              *
// Postcondition: myRunTime has been updated with time interval *
//                 since the Timer was started &&               *
//                 running == false.                            *
// Note: Stop() only has an effect when I'm running.            *
//***************************************************************
inline void Timer::Stop()
{
  if (running)
    {
      myRunTime += clock() - myStartTime;
      running = false;
    }
}

//***************************************************************
// Reset myself.                                                *
// Postcondition: myStartTime is the current clock value &&     *
//                 myRunTime == 0.                              *
// Note: Reset() while I'm running re-starts me.                *
//***************************************************************
inline void Timer::Reset()
{
  myRunTime = 0;
  myStartTime = clock();
}


//***************************************************************
// My current time value (in seconds)                           *
// Return: the elapsed time since I was started.                *
// Note: If I'm not running:                                    *
//        repeated calls to Seconds() return the same value.    *
//       Otherwise:                                             *
//        repeated calls to Seconds() return different values.  *
//***************************************************************
inline double Timer::Seconds() const
{
  if (running)
    return double(clock() - myStartTime) / double(CLOCKS_PER_SEC);
  else
    return double(myRunTime) / double(CLOCKS_PER_SEC);
}


//***************************************************************
// Output myself (function member).                             *
// Receive: out, an ostream.                                    *
// Output: the time since I was started.                        *
// Passback: out, containing the Timer output.                  *
// Note: If I'm not running:                                    *
//        repeated calls to Print() display the same value.     *
//       Otherwise:                                             *
//        repeated calls to Print() display different values.   *
//***************************************************************
inline void Timer::Print(ostream & out) const
{
  out << Seconds();
}

//***************************************************************
// Output a Timer (operator<<)                                  *
// Receive: out, an ostream,                                    *
//          aTimer, a Timer.                                    *
// Output: the value of aTimer via out.                         *
// Passback: out, containing the time since aTimer was started. *
// Return: out, for output chaining.                            *
// Note: If I'm not running:                                    *
//        repeated calls to << display the same value.          *
//       Otherwise:                                             *
//        repeated calls to << display different values.        *
//***************************************************************
inline ostream & operator<< (ostream & out, const Timer & aTimer)
{
  aTimer.Print(out);
  return out;
}


#endif

