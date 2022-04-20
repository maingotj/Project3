#pragma once
#include <string>
using namespace std;


struct CarAccident
{
    //DATA
    float x, y;
    string county;
    int weekday;
    int speedLimit;
    bool injury;
    bool death;
    bool impairedDriver;

    //INITIALIZER
    CarAccident(float x, float y, string county, int weekday, int speedLimit, bool injury, bool death, bool impairedDriver)
    {
        //stores data from the csv file
        this->x = x;
        this->y = y;
        this->county = county;
        this->weekday = weekday;
        this->speedLimit = speedLimit;
        this->injury = injury;
        this->death = death;
        this->impairedDriver = impairedDriver;
    }

    //ACCESSER
    string getCounty()
    {
        return county;
    }
};

