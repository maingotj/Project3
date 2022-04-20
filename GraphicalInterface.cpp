#include "GraphicalInterface.h"
#include "HashTable.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
using namespace std;

//CONSTRUCTOR
GraphicalInterface::GraphicalInterface(HashTable& hashtable, Graph& graph) {
    this->myHashTable = &hashtable;
    this->myGraph = &graph;

    for (int i = 0; i < 26; i++) {
        keyCodes[i] = 'A' + i;
        keyCodes[-1 - i] = 'A' + i;
    }
    keyCodes[50] = '.';
    keyCodes[56] = '-';
    keyCodes[57] = ' ';
    keyCodes[-58] = ' ';

    floridaMap.setPosition(0, 0);
    floridaMap.setTexture(TextureManager::GetTexture("florida"));

    georgia.loadFromFile("georgiab.ttf");

    search.setFont(georgia);
    search.setString("Enter a Florida county:");
    search.setCharacterSize(24);
    search.setFillColor(sf::Color::Black);
    search.setPosition(190, 500);

    label_graphTime.setFont(georgia);
    label_graphTime.setCharacterSize(15);
    label_graphTime.setFillColor(sf::Color::White);
    label_graphTime.setPosition(550, 535);

    label_hashTime.setFont(georgia);
    label_hashTime.setCharacterSize(15);
    label_hashTime.setFillColor(sf::Color::White);
    label_hashTime.setPosition(550, 515);


    label_county.setFont(georgia);
    label_county.setString("County Name: ");
    label_county.setCharacterSize(20);
    label_county.setFillColor(sf::Color::White);
    label_county.setPosition(190, 600);

    county.setFont(georgia);
    county.setCharacterSize(24);
    county.setFillColor(sf::Color::Black);
    county.setPosition(550, 600);

    label_speed.setFont(georgia);
    label_speed.setString("Average Speed Limit: ");
    label_speed.setCharacterSize(20);
    label_speed.setFillColor(sf::Color::White);
    label_speed.setPosition(190, 640);

    speed.setFont(georgia);
    speed.setCharacterSize(24);
    speed.setFillColor(sf::Color::Black);
    speed.setPosition(550, 640);

    label_deaths.setFont(georgia);
    label_deaths.setString("Total Fatalities: ");
    label_deaths.setCharacterSize(20);
    label_deaths.setFillColor(sf::Color::White);
    label_deaths.setPosition(190, 680);

    deaths.setFont(georgia);
    deaths.setCharacterSize(24);
    deaths.setFillColor(sf::Color::Black);
    deaths.setPosition(550, 680);

    label_injuries.setFont(georgia);
    label_injuries.setString("Total Injuries: ");
    label_injuries.setCharacterSize(20);
    label_injuries.setFillColor(sf::Color::White);
    label_injuries.setPosition(190, 720);

    injuries.setFont(georgia);
    injuries.setCharacterSize(24);
    injuries.setFillColor(sf::Color::Black);
    injuries.setPosition(550, 720);

    label_impairments.setFont(georgia);
    label_impairments.setString("Drug/Alcohol Involvement: ");
    label_impairments.setCharacterSize(20);
    label_impairments.setFillColor(sf::Color::White);
    label_impairments.setPosition(190, 760);

    impairments.setFont(georgia);
    impairments.setCharacterSize(24);
    impairments.setFillColor(sf::Color::Black);
    impairments.setPosition(550, 760);

    label_weekday.setFont(georgia);
    label_weekday.setString("Weekdays: ");
    label_weekday.setCharacterSize(20);
    label_weekday.setFillColor(sf::Color::White);
    label_weekday.setPosition(190, 800);

    weekday.setFont(georgia);
    weekday.setCharacterSize(24);
    weekday.setFillColor(sf::Color::Black);
    weekday.setPosition(550, 800);

    label_weekend.setFont(georgia);
    label_weekend.setString("Weekends: ");
    label_weekend.setCharacterSize(20);
    label_weekend.setFillColor(sf::Color::White);
    label_weekend.setPosition(190, 840);

    weekend.setFont(georgia);
    weekend.setCharacterSize(24);
    weekend.setFillColor(sf::Color::Black);
    weekend.setPosition(550, 840);

    label_county2.setFont(georgia);
    label_county2.setString("Enter another county to display shortest path");
    label_county2.setCharacterSize(20);
    label_county2.setFillColor(sf::Color::Black);
    label_county2.setPosition(190, 880);

    path_fatal.setFont(georgia);
    path_fatal.setString("Fatalities: ");
    path_fatal.setCharacterSize(18);
    path_fatal.setFillColor(sf::Color::White);
    path_fatal.setPosition(190, 915);

    fatal.setFont(georgia);
    fatal.setCharacterSize(20);
    fatal.setFillColor(sf::Color::Black);
    fatal.setPosition(550, 915);

    path_injury.setFont(georgia);
    path_injury.setString("Injuries: ");
    path_injury.setCharacterSize(18);
    path_injury.setFillColor(sf::Color::White);
    path_injury.setPosition(190, 945);

    injure.setFont(georgia);
    injure.setCharacterSize(20);
    injure.setFillColor(sf::Color::Black);
    injure.setPosition(550, 945);

    path_crashes.setFont(georgia);
    path_crashes.setString("Crashes: ");
    path_crashes.setCharacterSize(18);
    path_crashes.setFillColor(sf::Color::White);
    path_crashes.setPosition(190, 975);

    crashes.setFont(georgia);
    crashes.setCharacterSize(20);
    crashes.setFillColor(sf::Color::Black);
    crashes.setPosition(550, 975);

    countyName.setFont(georgia);
    countyName.setCharacterSize(24);
    countyName.setFillColor(sf::Color::White);
    countyName.setPosition(200, 550);

    cursor.setFont(georgia);
    cursor.setString("|");
    cursor.setCharacterSize(24);
    cursor.setFillColor(sf::Color::White);
    cursor.setPosition(195, 550);

    color.r = 145;
    color.g = 140;
    color.b = 122;

    textBox.setFillColor(color);
    textBox.setOutlineColor(sf::Color::Black);
    textBox.setOutlineThickness(3);
    vector.x = 300;
    vector.y = 35;
    textBox.setSize(vector);
    textBox.setPosition(190, 550);

    setSprites();

    line = sf::VertexArray(sf::LinesStrip, myHashTable->size()); //will be used to connect county sprites
}
//COUNTY SPRITE SETTER: sets a star sprite corresponding to every county/position on the Florida map
void GraphicalInterface::setSprites() {
    Escambia.setPosition(476, 236);
    Escambia.setTexture(TextureManager::GetTexture("star"));
    Escambia.scale(0.0035, 0.0035);
    sprites["ESCAMBIA"] = Escambia;

    SantaRosa.setPosition(510, 234);
    SantaRosa.setTexture(TextureManager::GetTexture("star"));
    SantaRosa.scale(0.0035, 0.0035);
    sprites["SANTA ROSA"] = SantaRosa;

    Okaloosa.setPosition(554, 231);
    Okaloosa.setTexture(TextureManager::GetTexture("star"));
    Okaloosa.scale(0.0035, 0.0035);
    sprites["OKALOOSA"] = Okaloosa;

    Walton.setPosition(602, 239);
    Walton.setTexture(TextureManager::GetTexture("star"));
    Walton.scale(0.0035, 0.0035);
    sprites["WALTON"] = Walton;

    Holmes.setPosition(641, 200);
    Holmes.setTexture(TextureManager::GetTexture("star"));
    Holmes.scale(0.0035, 0.0035);
    sprites["HOLMES"] = Holmes;


    Washington.setPosition(665, 234);
    Washington.setTexture(TextureManager::GetTexture("star"));
    Washington.scale(0.0035, 0.0035);
    sprites["WASHINGTON"] = Washington;

    Bay.setPosition(680, 284);
    Bay.setTexture(TextureManager::GetTexture("star"));
    Bay.scale(0.0035, 0.0035);
    sprites["BAY"] = Bay;

    Jackson.setPosition(714, 215);
    Jackson.setTexture(TextureManager::GetTexture("star"));
    Jackson.scale(0.0035, 0.0035);
    sprites["JACKSON"] = Jackson;

    Calhoun.setPosition(720, 265);
    Calhoun.setTexture(TextureManager::GetTexture("star"));
    Calhoun.scale(0.0035, 0.0035);
    sprites["CALHOUN"] = Calhoun;

    Gulf.setPosition(723, 328);
    Gulf.setTexture(TextureManager::GetTexture("star"));
    Gulf.scale(0.0035, 0.0035);
    sprites["GULF"] = Gulf;

    Gadsden.setPosition(792, 232);
    Gadsden.setTexture(TextureManager::GetTexture("star"));
    Gadsden.scale(0.0035, 0.0035);
    sprites["GADSDEN"] = Gadsden;

    Liberty.setPosition(760, 259);
    Liberty.setTexture(TextureManager::GetTexture("star"));
    Liberty.scale(0.0035, 0.0035);
    sprites["LIBERTY"] = Liberty;

    Franklin.setPosition(767, 322);
    Franklin.setTexture(TextureManager::GetTexture("star"));
    Franklin.scale(0.0035, 0.0035);
    sprites["FRANKLIN"] = Franklin;

    Leon.setPosition(839, 245);
    Leon.setTexture(TextureManager::GetTexture("star"));
    Leon.scale(0.0035, 0.0035);
    sprites["LEON"] = Leon;

    Wakulla.setPosition(814, 297);
    Wakulla.setTexture(TextureManager::GetTexture("star"));
    Wakulla.scale(0.0035, 0.0035);
    sprites["WAKULLA"] = Wakulla;

    Jefferson.setPosition(880, 251);
    Jefferson.setTexture(TextureManager::GetTexture("star"));
    Jefferson.scale(0.0035, 0.0035);
    sprites["JEFFERSON"] = Jefferson;

    Madison.setPosition(932, 229);
    Madison.setTexture(TextureManager::GetTexture("star"));
    Madison.scale(0.0035, 0.0035);
    sprites["MADISON"] = Madison;

    Taylor.setPosition(924, 311);
    Taylor.setTexture(TextureManager::GetTexture("star"));
    Taylor.scale(0.0035, 0.0035);
    sprites["TAYLOR"] = Taylor;

    Hamilton.setPosition(991, 233);
    Hamilton.setTexture(TextureManager::GetTexture("star"));
    Hamilton.scale(0.0035, 0.0035);
    sprites["HAMILTON"] = Hamilton;

    Suwannee.setPosition(994, 292);
    Suwannee.setTexture(TextureManager::GetTexture("star"));
    Suwannee.scale(0.0035, 0.0035);
    sprites["SUWANNEE"] = Suwannee;

    Lafayette.setPosition(960, 305);
    Lafayette.setTexture(TextureManager::GetTexture("star"));
    Lafayette.scale(0.0035, 0.0035);
    sprites["LAFAYETTE"] = Lafayette;

    Dixie.setPosition(967, 375);
    Dixie.setTexture(TextureManager::GetTexture("star"));
    Dixie.scale(0.0035, 0.0035);
    sprites["DIXIE"] = Dixie;

    Columbia.setPosition(1030, 299);
    Columbia.setTexture(TextureManager::GetTexture("star"));
    Columbia.scale(0.0035, 0.0035);
    sprites["COLUMBIA"] = Columbia;

    Gilchrist.setPosition(1015, 341);
    Gilchrist.setTexture(TextureManager::GetTexture("star"));
    Gilchrist.scale(0.0035, 0.0035);
    sprites["GILCHRIST"] = Gilchrist;

    Levy.setPosition(1010, 384);
    Levy.setTexture(TextureManager::GetTexture("star"));
    Levy.scale(0.0035, 0.0035);
    sprites["LEVY"] = Levy;

    Alachua.setPosition(1051, 340);
    Alachua.setTexture(TextureManager::GetTexture("star"));
    Alachua.scale(0.0035, 0.0035);
    sprites["ALACHUA"] = Alachua;

    Union.setPosition(1063, 304);
    Union.setTexture(TextureManager::GetTexture("star"));
    Union.scale(0.0035, 0.0035);
    sprites["UNION"] = Union;

    Baker.setPosition(1069, 244);
    Baker.setTexture(TextureManager::GetTexture("star"));
    Baker.scale(0.0035, 0.0035);
    sprites["BAKER"] = Baker;

    Nassau.setPosition(1119, 229);
    Nassau.setTexture(TextureManager::GetTexture("star"));
    Nassau.scale(0.0035, 0.0035);
    sprites["NASSAU"] = Nassau;

    Duval.setPosition(1127, 268);
    Duval.setTexture(TextureManager::GetTexture("star"));
    Duval.scale(0.0035, 0.0035);
    sprites["DUVAL"] = Duval;

    Clay.setPosition(1118, 294);
    Clay.setTexture(TextureManager::GetTexture("star"));
    Clay.scale(0.0035, 0.0035);
    sprites["CLAY"] = Clay;

    StJohns.setPosition(1180, 342);
    StJohns.setTexture(TextureManager::GetTexture("star"));
    StJohns.scale(0.0035, 0.0035);
    sprites["ST. JOHNS"] = StJohns;

    Putnam.setPosition(1150, 376);
    Putnam.setTexture(TextureManager::GetTexture("star"));
    Putnam.scale(0.0035, 0.0035);
    sprites["PUTNAM"] = Putnam;

    Marion.setPosition(1099, 430);
    Marion.setTexture(TextureManager::GetTexture("star"));
    Marion.scale(0.0035, 0.0035);
    sprites["MARION"] = Marion;

    Citrus.setPosition(1052, 457);
    Citrus.setTexture(TextureManager::GetTexture("star"));
    Citrus.scale(0.0035, 0.0035);
    sprites["CITRUS"] = Citrus;

    Sumter.setPosition(1097, 463);
    Sumter.setTexture(TextureManager::GetTexture("star"));
    Sumter.scale(0.0035, 0.0035);
    sprites["SUMTER"] = Sumter;

    Lake.setPosition(1131, 482);
    Lake.setTexture(TextureManager::GetTexture("star"));
    Lake.scale(0.0035, 0.0035);
    sprites["LAKE"] = Lake;

    Volusia.setPosition(1213, 452);
    Volusia.setTexture(TextureManager::GetTexture("star"));
    Volusia.scale(0.0035, 0.0035);
    sprites["VOLUSIA"] = Volusia;

    Seminole.setPosition(1205, 483);
    Seminole.setTexture(TextureManager::GetTexture("star"));
    Seminole.scale(0.0035, 0.0035);
    sprites["SEMINOLE"] = Seminole;

    Orange.setPosition(1166, 509);
    Orange.setTexture(TextureManager::GetTexture("star"));
    Orange.scale(0.0035, 0.0035);
    sprites["ORANGE"] = Orange;

    Brevard.setPosition(1261, 559);
    Brevard.setTexture(TextureManager::GetTexture("star"));
    Brevard.scale(0.0035, 0.0035);
    sprites["BREVARD"] = Brevard;

    Hernando.setPosition(1047, 506);
    Hernando.setTexture(TextureManager::GetTexture("star"));
    Hernando.scale(0.0035, 0.0035);
    sprites["HERNANDO"] = Hernando;

    Pasco.setPosition(1034, 537);
    Pasco.setTexture(TextureManager::GetTexture("star"));
    Pasco.scale(0.0035, 0.0035);
    sprites["PASCO"] = Pasco;

    Polk.setPosition(1135, 570);
    Polk.setTexture(TextureManager::GetTexture("star"));
    Polk.scale(0.0035, 0.0035);
    sprites["POLK"] = Polk;

    Osceola.setPosition(1211, 577);
    Osceola.setTexture(TextureManager::GetTexture("star"));
    Osceola.scale(0.0035, 0.0035);
    sprites["OSCEOLA"] = Osceola;

    Hillsborough.setPosition(1073, 600);
    Hillsborough.setTexture(TextureManager::GetTexture("star"));
    Hillsborough.scale(0.0035, 0.0035);
    sprites["HILLSBOROUGH"] = Hillsborough;

    Pinellas.setPosition(1017, 595);
    Pinellas.setTexture(TextureManager::GetTexture("star"));
    Pinellas.scale(0.0035, 0.0035);
    sprites["PINELLAS"] = Pinellas;

    Manatee.setPosition(1090, 660);
    Manatee.setTexture(TextureManager::GetTexture("star"));
    Manatee.scale(0.0035, 0.0035);
    sprites["MANATEE"] = Manatee;

    Hardee.setPosition(1142, 647);
    Hardee.setTexture(TextureManager::GetTexture("star"));
    Hardee.scale(0.0035, 0.0035);
    sprites["HARDEE"] = Hardee;

    Highlands.setPosition(1185, 654);
    Highlands.setTexture(TextureManager::GetTexture("star"));
    Highlands.scale(0.0035, 0.0035);
    sprites["HIGHLANDS"] = Highlands;

    Okeechobee.setPosition(1249, 670);
    Okeechobee.setTexture(TextureManager::GetTexture("star"));
    Okeechobee.scale(0.0035, 0.0035);
    sprites["OKEECHOBEE"] = Okeechobee;

    StLucie.setPosition(1284, 650);
    StLucie.setTexture(TextureManager::GetTexture("star"));
    StLucie.scale(0.0035, 0.0035);
    sprites["ST. LUCIE"] = StLucie;

    Sarasota.setPosition(1058, 674);
    Sarasota.setTexture(TextureManager::GetTexture("star"));
    Sarasota.scale(0.0035, 0.0035);
    sprites["SARASOTA"] = Sarasota;

    Desoto.setPosition(1122, 684);
    Desoto.setTexture(TextureManager::GetTexture("star"));
    Desoto.scale(0.0035, 0.0035);
    sprites["DESOTO"] = Desoto;

    Glades.setPosition(1221, 708);
    Glades.setTexture(TextureManager::GetTexture("star"));
    Glades.scale(0.0035, 0.0035);
    sprites["GLADES"] = Glades;

    Martin.setPosition(1315, 699);
    Martin.setTexture(TextureManager::GetTexture("star"));
    Martin.scale(0.0035, 0.0035);
    sprites["MARTIN"] = Martin;

    Charlotte.setPosition(1140, 724);
    Charlotte.setTexture(TextureManager::GetTexture("star"));
    Charlotte.scale(0.0035, 0.0035);
    sprites["CHARLOTTE"] = Charlotte;

    Lee.setPosition(1130, 782);
    Lee.setTexture(TextureManager::GetTexture("star"));
    Lee.scale(0.0035, 0.0035);
    sprites["LEE"] = Lee;

    Hendry.setPosition(1221, 783);
    Hendry.setTexture(TextureManager::GetTexture("star"));
    Hendry.scale(0.0035, 0.0035);
    sprites["HENDRY"] = Hendry;

    PalmBeach.setPosition(1295, 772);
    PalmBeach.setTexture(TextureManager::GetTexture("star"));
    PalmBeach.scale(0.0035, 0.0035);
    sprites["PALM BEACH"] = PalmBeach;

    Collier.setPosition(1177, 823);
    Collier.setTexture(TextureManager::GetTexture("star"));
    Collier.scale(0.0035, 0.0035);
    sprites["COLLIER"] = Collier;

    Broward.setPosition(1287, 836);
    Broward.setTexture(TextureManager::GetTexture("star"));
    Broward.scale(0.0035, 0.0035);
    sprites["BROWARD"] = Broward;

    Monroe.setPosition(1224, 919);
    Monroe.setTexture(TextureManager::GetTexture("star"));
    Monroe.scale(0.0035, 0.0035);
    sprites["MONROE"] = Monroe;

    MiamiDade.setPosition(1278, 907);
    MiamiDade.setTexture(TextureManager::GetTexture("star"));
    MiamiDade.scale(0.0035, 0.0035);
    sprites["MIAMI-DADE"] = MiamiDade;

    Bradford.setPosition(1092, 318);
    Bradford.setTexture(TextureManager::GetTexture("star"));
    Bradford.scale(0.0035, 0.0035);
    sprites["BRADFORD"] = Bradford;

    IndianRiver.setPosition(1260, 615);
    IndianRiver.setTexture(TextureManager::GetTexture("star"));
    IndianRiver.scale(0.0035, 0.0035);
    sprites["INDIAN RIVER"] = IndianRiver;

    Flagler.setPosition(1193, 391);
    Flagler.setTexture(TextureManager::GetTexture("star"));
    Flagler.scale(0.0035, 0.0035);
    sprites["FLAGLER"] = Flagler;
}

//DRAWING FUNCTIONS:
//draws all the objects, if enter has been pressed by user->county data drawn
void GraphicalInterface::Draw(sf::RenderWindow& window)
{
    window.draw(floridaMap);
    window.draw(search);
    window.draw(cursor);
    window.draw(textBox);
    window.draw(cursor);
    window.draw(countyName);
    if (drawCountybool) {
        drawSelectedCounties(window);
        drawCountyStats(window);
    }
}
//draws data based on how many counties have been entered, alters texts based on vector size
void GraphicalInterface::drawSelectedCounties(sf::RenderWindow& window)
{

    if (countiesDisplay.size() > 1) //two counties have been entered
    {
        label_county2.setString("County Along Path With Most..."); //changes display text
        window.draw(label_county2);
        window.draw(line);
        for (auto itr : path) {
            window.draw(sprites[itr]);
        }
        window.draw(path_crashes);   //draws data calculated along the path
        window.draw(crashes);
        window.draw(path_injury);
        window.draw(injure);
        window.draw(path_fatal);
        window.draw(fatal);
    }
    if (countiesDisplay.size() == 1) //one county has been entered
    {
        label_county2.setString("Enter another county to display shortest path"); //changes display text
        window.draw(label_county2);
    }
}
     //draws stats for the first county entered by user
void GraphicalInterface::drawCountyStats(sf::RenderWindow& window) {
    window.draw(label_county);
    window.draw(label_speed);
    window.draw(label_deaths);
    window.draw(label_injuries);
    window.draw(label_impairments);
    window.draw(label_weekday);
    window.draw(label_weekend);
    window.draw(label_graphTime);
    window.draw(label_hashTime);
    window.draw(sprites[countiesDisplay[0]]);
    county.setString(countiesDisplay[0]);
    window.draw(county);
    speed.setString(myHashTable->getCounty(countiesDisplay[0])->avg_speedlimit);
    window.draw(speed);
    deaths.setString(myHashTable->getCounty(countiesDisplay[0])->stat_deaths);
    window.draw(deaths);
    impairments.setString(myHashTable->getCounty(countiesDisplay[0])->stat_impaired);
    window.draw(impairments);
    weekday.setString(myHashTable->getCounty(countiesDisplay[0])->stat_weekday);
    window.draw(weekday);
    weekend.setString(myHashTable->getCounty(countiesDisplay[0])->stat_weekend);
    window.draw(weekend);
    injuries.setString(myHashTable->getCounty(countiesDisplay[0])->stat_injuries);
    window.draw(injuries);
}

//USER INPUT FUNCTIONALITY
     //used to create a flash the cursor in the user input textbox by alternating the color from
     //background color to text color every 800 frames based on if it is "on" or not
void GraphicalInterface::flashCursor() {
    if (on) {
        cursor.setFillColor(color);
        on = false;
    }
    else
    {
        cursor.setFillColor(sf::Color::White);
        on = true;
    }
}
     //moves the cursor to the end of the input based on the size of the input text
void GraphicalInterface::moveCursor()
{
    float y = cursor.getPosition().y;
    cursor.setPosition(195 + countyName.getLocalBounds().width, y);
}

//EVENT HANDLER
void GraphicalInterface::checkEvent(sf::RenderWindow& window) {
    sf::Event event;
    std::string txt;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) //ends program
            window.close();
        if (event.type == sf::Event::EventType::KeyPressed) { //checks if/what key has been pressed
            //'-' == 50 space == (57,-58) '.' == 56 enter == 58 backspace == 59 capslock == -1
                if (event.key.code == -1) {
                capital = !capital;
            }
            else if (event.key.code == 58) {
                handleCountyInput(countyName.getString()); //handles user input
                drawCountybool = true;    // enter->displays data for county
                countyName.setString(""); //clears input textbox
            }
            else if (event.key.code == 59)
                countyName.setString(countyName.getString().substring(0, countyName.getString().getSize() - 1));
            else if ((event.key.code < 26 && event.key.code >= 0) || event.key.code == 57 ||
                     event.key.code == -58 || event.key.code == 50 || event.key.code == 56) {
                //adds or removed char to user input
                if (!capital)
                    countyName.setString(countyName.getString() + keyCodes[event.key.code]);
                else
                    countyName.setString(countyName.getString() + keyCodes[-1 - event.key.code]);
            }
            moveCursor(); //moves cursor to end of user input string
        }
    }
    flash++; //frame count tracker
    if (flash % 800 == 0) //flashes cursor every 800 frames
        flashCursor();

}
     //sets data based on user input/number of input
void GraphicalInterface::handleCountyInput(string input)
{
    timeInput(input); //used for time comparison with the two data structs

    if (myHashTable->has(input)) {    //makes sure that the string is in the hashtable
        if (countiesDisplay.empty()) {  //no counties in vector yet -> adds
            countiesDisplay.push_back(input);
        }
        else if (countiesDisplay.size() == 1) { //county vector already has one county
            secondCounty = true;                //ready to display second countie/path data
            countiesDisplay.push_back(input);   //adds second county
            string data[3];                     //array to keep track of path data
            int hiFatal = 0,                    //path data ints
                    hiInjury = 0,
                    hiCrashes = 0;
            path = myGraph->connectingPath(countiesDisplay[0], countiesDisplay[1]); //calculates path from second to first
            line.resize(path.size()); //resizes linespace "line"
            for (int i = 0; i < path.size(); i++) {  //initializes linespace
                line[i].position = sf::Vector2f(sprites[path[i]].getPosition() + sf::Vector2f(12, 12));
                line[i].color = sf::Color::Black;
                //PATH DATA COMPARISONS-> edits corresponding index in data array
                if (hiFatal < stoi(myHashTable->getCounty(path[i])->stat_deaths)) {
                    hiFatal = stoi(myHashTable->getCounty(path[i])->stat_deaths);
                    data[0] = path[i];
                }
                if (hiInjury < stoi(myHashTable->getCounty(path[i])->stat_injuries))
                {
                    hiInjury = stoi(myHashTable->getCounty(path[i])->stat_injuries);
                    data[1] = path[i];
                }
                if (hiCrashes < myHashTable->getCounty(countiesDisplay[0])->vecAccidents.size())
                {
                    hiCrashes = myHashTable->getCounty(countiesDisplay[0])->vecAccidents.size();
                    data[2] = path[i];
                }

            }
            crashes.setString(data[2]);
            fatal.setString(data[0]);
            injure.setString(data[1]);
        }
        else {
            //RESET AFTER TWO INPUTS
            secondCounty = false;
            countiesDisplay.clear();
            line.clear();
            countiesDisplay.push_back(input);
        }
    }
}
//TIME TRACKER
void GraphicalInterface::timeInput(string input)
{
    numCalculations++;

    auto start = chrono::high_resolution_clock::now();
    myHashTable->has(input);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    totalSecondsHash += duration.count();
    avgTimeHash = totalSecondsHash / numCalculations;
    string avgTime = "Hash Access Avg: ";
    avgTime.append(to_string(avgTimeHash));
    avgTime.append(" ns");

    label_hashTime.setString(avgTime);

    start = chrono::high_resolution_clock::now();
    myGraph->has(input);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    totalSecondsGraph += duration.count();
    avgTimeGraph = totalSecondsGraph / numCalculations;
    avgTime = "Graph Access Avg: ";
    avgTime.append(to_string(avgTimeGraph));
    avgTime.append(" ns");

    label_graphTime.setString(avgTime);
}




