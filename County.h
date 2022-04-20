#pragma once
#include "CarAccident.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class County
{
private:
    string name;


public:
    //CAR ACCIDENTS AND STATS
    vector<CarAccident*> vecAccidents;
    string avg_speedlimit;
    string stat_injuries;
    string stat_deaths;
    string stat_impaired;
    string stat_weekday;
    string stat_weekend;

    //INITIALIZER
    County(CarAccident* accident);

    //MODIFIERS
    void insert(CarAccident* accident);
    string convertToPercent(float val);
    void setStats();
    
    //ACCESSERS
    string getName();
};


