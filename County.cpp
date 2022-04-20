#include "County.h"

//INITIALIZER
County::County(CarAccident* accident)
{
    this->name = accident->getCounty();
    vecAccidents.push_back(accident);
}

//MODIFIERS
void County::insert(CarAccident* accident)
{
    vecAccidents.push_back(accident);
}
string County::convertToPercent(float val) { //function to convert to a percent and convert it to a string
    string returnStr = to_string(val).substr(0, 5);
    returnStr += '%';
    return returnStr;
}
void County::setStats() {
    int weekdays = 0, weekends = 0, speedLimitCounter = 0, speedlimits = 0, injuries = 0, deaths = 0, impaired = 0;
    for (CarAccident* itr : vecAccidents) {
        if (itr->weekday > 5) //if it occured on a weekend increases number of weekdays by 1
            weekends++;
        if (itr->weekday <= 5)//if it occured on a weekday increases number of weekdays by 1
            weekdays++;
        if (itr->speedLimit != 0) { //if a speedlimit existed in the csv increase num of speedlimits
            speedLimitCounter++;
            speedlimits += itr->speedLimit; //add the speedlimit to the combined speed limit
        }
        if (itr->injury) //if injury occured increase counter
            injuries++;
        if (itr->death) //if death occured increase counter
            deaths += 1;
        if (itr->impairedDriver) //if driver was impared increase counter
            impaired++;
    }

    //turn values into statistics used in the sfml
    avg_speedlimit = to_string(speedlimits / speedLimitCounter);
    stat_deaths = to_string(deaths);
    stat_injuries = to_string(injuries);
    stat_impaired = convertToPercent((float)impaired / vecAccidents.size() * 100);
    stat_weekday = convertToPercent((float)weekdays / vecAccidents.size() * 100);
    stat_weekend = convertToPercent((float)weekends / vecAccidents.size() * 100);
}

//ACCESSERS
string County::getName()
{
    return name;
}