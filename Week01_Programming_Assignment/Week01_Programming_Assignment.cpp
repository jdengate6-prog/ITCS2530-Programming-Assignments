#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//constants for each color
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";

void printreport(string R_plant_type, double R_total_price, int R_amt_of_seeds, int R_days_old, int R_days_water, int R_times_watered, int R_total_yield);
double purchasechoice(double R_purchase_choice);
int plantedchoice(int R_planted_choice);
string setcolor();
void displaybanner(string R_chosen_color);
void waterhistory(int R_plant_date, int R_todays_date, int& days_water, int& times_watered);
int yield(int R_amt_of_seeds);

int main()
{
    string plant_type; //Type of Plant
    string chosen_color; // color for the terminal to be
    double plant_price; //Price of Plant
    double total_price; //Total Price of All Seeds
    int amt_of_seeds; //amt of seeds planted
    int plant_date;   //Date Plant was Planted
    int todays_date; //Todays Date
    int days_old;     //How Many Days Old the Plant is
    int purchase_choice; //Choice for if you purchased plant seeds
    int planted_choice;  //Choice for if you planted more than one seed
    int days_water = 0;   //How Many Days Since the Plant was Last Watered
    int info_choice;    //Variable for the counter
    int last_watered;
    int total_yield = 0;    //Total Yield - to return to main
    int times_watered = 0; //Variable for Times Watered, resets if information is reentered

    do
    {
        chosen_color = setcolor();
        displaybanner(chosen_color);
        cout << "Enter Plant Type:";
        cin >> plant_type;
        cout << "Did you buy the plant seeds? 1=Yes 2=No." << endl;
        cin >> purchase_choice;
        cout << "Did you plant more than one seed? 1=Yes 2=No." << endl;
        cin >> planted_choice;
        plant_price = purchasechoice(purchase_choice);
        amt_of_seeds = plantedchoice(planted_choice);
        total_price = plant_price * amt_of_seeds;
        total_yield = yield(amt_of_seeds);
        cout << "Enter Date Planted in 3 Digit Date Format:";
        cin >> plant_date;
        cout << "Enter Todays Date in 3 Digit Date Format:";
        cin >> todays_date;
        days_old = todays_date - plant_date;
        waterhistory(plant_date, todays_date, days_water, times_watered);
        cout << "If the Information was Entered Correctly, Enter 0. If There was a Mistake, Enter 1.";
        cin >> info_choice;
    } while (info_choice == 1);
    printreport(plant_type, total_price, amt_of_seeds, days_old, days_water, times_watered, total_yield);
}

string setcolor()
{
    string set_color;
    cout << RESET << "Enter what color you would like the terminal to be. Options: GREEN, RED, YELLOW, CYAN" << endl;
    cin >> set_color;
    if (set_color == "GREEN" || set_color == "green") 
    {
        return GREEN;
    }
    else if (set_color == "RED" || set_color == "red") 
    {
        return RED;
    }
    else if (set_color == "YELLOW" || set_color == "yellow") 
    {
        return YELLOW;
    }
    else if (set_color == "CYAN" || set_color == "cyan") 
    {
        return CYAN;
    }
    return RESET;
}

void displaybanner(string R_chosen_color)
{
    cout << R_chosen_color << "Welcome to my program which you can use to track your garden plants!" << endl;
}

int yield(int R_amt_of_seeds)
{
    int seed_yield;     //Yield of each seed
    int R_total_yield = 0;    //Total Yield - to return to main
    int i;              //Variable for the counter 
    for (i = 0; i < R_amt_of_seeds; i++)
    {
        cout << "Enter the expected yield of a plant:";
        cin >> seed_yield;
        R_total_yield = R_total_yield + seed_yield;
    }
    return R_total_yield;
}

void waterhistory(int R_plant_date, int R_todays_date, int& days_water,int& times_watered)
{
    int water_amt = 1;    //Times watered - for the counter
    int R_last_watered; //Date Plant was Last Watered - to pass to main
    times_watered = 0; // reset the counter for times watered if data is entered again
    while (water_amt == 1)
    {
        cout << "Enter Water Event Date in 3 Digit Date Format:";
        cin >> R_last_watered;
        cout << "If This Was the Last Water Event, Please Enter 0, If There Are More Events, Please Enter 1.";
        times_watered = times_watered + 1;
        cin >> water_amt;
    }
    if (R_plant_date > R_last_watered || R_last_watered > R_todays_date)
        cout << "Please re-enter date data in the correct format. Conversion can be done at https://www-air.larc.nasa.gov/tools/jday.htm";
    else {
        days_water = R_todays_date - R_last_watered;
    }
}

double purchasechoice(double R_purchase_choice)
{
    double R_plant_price;
    if (R_purchase_choice == 1) 
    {
        cout << "Enter Price of plant seeds:";
        cin >> R_plant_price;
    }
    if (R_purchase_choice == 2) 
    {
        R_plant_price = 0;
    }
    return R_plant_price;
}

int plantedchoice(int R_planted_choice)
{
    int R_amt_of_seeds;
    if (R_planted_choice == 1)
    {
        cout << "Enter how many seeds planted:";
        cin >> R_amt_of_seeds;
    }
    if (R_planted_choice == 2)
    {
        R_amt_of_seeds = 1;
    }
    return R_amt_of_seeds;
}

void printreport(string R_plant_type, double R_total_price, int R_amt_of_seeds, int R_days_old, int R_days_water, int R_times_watered, int R_total_yield)
{
    ofstream outdata;
    int choice;  //Choice for selection menu
    cout << "please select from the following menu" << endl;
    cout << "1 = Create report sheet in external document." << endl;
    cout << "2 = Create report sheet in computer terminal." << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        outdata.open("report.txt");
        outdata << fixed << showpoint;
        outdata << "-------------- " << R_plant_type << " Summary " << "--------------" << endl;
        outdata << setw(10) << "Price" << setw(10) << "Seed #" << setw(10) << "Age" << setw(12) << "Last Water" << setw(15) << "Times Watered" << setw(12) << "Total Yield" << endl;
        outdata << setw(6) << "$" << setprecision(2) << R_total_price << setw(8) << R_amt_of_seeds << setw(10) << R_days_old << setw(12) << R_days_water << setw(15) << R_times_watered << setw(12) << R_total_yield;
        outdata.close();
        break;
    case 2:
        cout << fixed << showpoint;
        cout << "-------------- " << R_plant_type << " Summary " << "--------------" << endl;
        cout << setw(10) << "Price" << setw(10) << "Seed #" << setw(10) << "Age" << setw(12) << "Last Water" << setw(15) << "Times Watered" << setw(12) << "Total Yield" << endl;
        cout << setw(6) << "$" << setprecision(2) << R_total_price << setw(8) << R_amt_of_seeds << setw(10) << R_days_old << setw(12) << R_days_water << setw(15) << R_times_watered << setw(12) << R_total_yield;
        break;
    default:
        cout << "Selection was not in range";
    }
}