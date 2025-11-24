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
    Genre genre;
    int duration; // minutes
};

class TimeSlot { 
public: 
    Movie movie;
    Time startTime;
};

// A)
int minutesSinceMidnight(Time time){
    return time.h * 60 + time.m;
}

int minutesUntil(Time earlier, Time later){
    return minutesSinceMidnight(later) - minutesSinceMidnight(earlier);
}

// B)
Time addMinutes(Time time0, int min){
    Time t;
    int total = minutesSinceMidnight(time0) + min;
    t.h = total / 60;
    t.m = total % 60;
    return t;
}

void printMovie(Movie mv){
    std::string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA"; break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    std::cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

// C)
void printTimeSlot(TimeSlot ts){
    Time end = addMinutes(ts.startTime, ts.movie.duration);

    printMovie(ts.movie);
    std::cout << " [starts at " 
              << ts.startTime.h << ":" << ts.startTime.m
              << ", ends by "
              << end.h << ":" << end.m << "]\n";
}

// D)
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie){
    Time endTime = addMinutes(ts.startTime, ts.movie.duration);
    TimeSlot newTs = { nextMovie, endTime };
    return newTs;
}

// E)
bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
    int start1 = minutesSinceMidnight(ts1.startTime);
    int end1 = start1 + ts1.movie.duration;

    int start2 = minutesSinceMidnight(ts2.startTime);
    int end2 = start2 + ts2.movie.duration;

    // Overlap occurs if both intervals intersect
    return !(end1 <= start2 || end2 <= start1);
}
