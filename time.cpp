/*
    Author: Zhao Zhang
    Course: CSCI-135
    Instructor: Tong Yi
    Assignment: Project 10A, 10B, 10C, 10D, 10E

    A)
    The first function should return the number of minutes from 0:00AM until time.

    The second function should receive two Time arguments earlier and later and 
    report how many minutes separate the two moments. For example, when passing 10:30AM and 1:40PM:

    B)
    The function should create and return a new moment of time that is min minutes after time0.

    C)
    Create function printTimeSlot(TimeSlot ts)

    D)
    The function should produce and return a new TimeSlot for the movie nextMovie, 
    scheduled immediately after the time slot ts.

    E)
    The function should return true if the two time slots overlap, otherwise return false. 
    (Take into account the starting times of the time slots and the duration of the scheduled movies.)
*/

#include <iostream>

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

class Time { 
public:
    int h;
    int m;
};
class Movie { 
public: 
    std::string title;
    Genre genre;     // only one genre per movie
    int duration;    // in minutes
};

class TimeSlot { 
public: 
    Movie movie;     // what movie
    Time startTime;  // when it starts
};
int minutesSinceMidnight(Time time){
    return time.h*60 + time.m;
}
int minutesUntil(Time earlier, Time later){
    if (later.m < earlier.m){
        return {(later.h-earlier.h-1)*60+((earlier.m+60)-later.m)};
    }
}
Time addMinutes(Time time0, int min){
    Time x = time0;
    if(x.m + min >= 60){
        x.h += (x.m+min)/60;
        x.m = (x.m+min)%60;
    }
    return x;
}
void printMovie(Movie mv){
    std::string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    std::cout << mv.title << " " << g << " (" << mv.duration << " min)";
}
void printTimeSlot(TimeSlot ts){
    printMovie(ts.movie);
    std::cout << " [starts at " << ts.startTime.h << ":"<<ts.startTime.m << ", ends by " <<
                 addMinutes(ts.startTime,ts.movie.duration).h << ":"  <<
                 addMinutes(ts.startTime,ts.movie.duration).m << "]" << std::endl; 
}
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie){
    TimeSlot newTs = {nextMovie, Time() = {addMinutes(ts.startTime, ts.movie.duration).h,addMinutes(ts.startTime, ts.movie.duration).m}};
    return newTs;
}
bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
    if (ts1.startTime.h < ts2.startTime.h){
        if (addMinutes(ts1.startTime, ts1.movie.duration).h > ts2.startTime.h){
            return false;
        }else if (addMinutes(ts1.startTime, ts1.movie.duration).h <= ts2.startTime.h){
            return true;
        }
    }else if (ts1.startTime.h > ts2.startTime.h){
        if (addMinutes(ts2.startTime, ts2.movie.duration).h > ts1.startTime.h){
            return false;
        }else if (addMinutes(ts2.startTime, ts2.movie.duration).h <= ts1.startTime.h){
            return true;
        }
    }
    return false;
}
