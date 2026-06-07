#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    cout << "Welcome to my program which you can use to track your garden plants!" << endl;

    string plant_type; //Type of Plant
    double plant_price; //Price of Plant
    int amt_of_seeds; //amt of seeds planted
    int plant_date;   //Date Plant was Planted
    int last_watered; //Date Plant was Last Watered
    int todays_date; //Todays Date
    int days_old;    //How Many Days Old the Plant is
    int days_water;  //How Many Days Since the Plant was Last Watered
    int choice;      //Choice for selection menu
    int purchase_choice; //Choice for if you purchased plant seeds
    int planted_choice;  //Choice for if you planted more than one seed

    ofstream outdata;

    cout << "Enter Plant Type:";
    cin >> plant_type;

    cout << "Did you buy the plant seeds? 1=Yes 2=No." << endl;
    cin >> purchase_choice;

    cout << "Did you plant more than one seed? 1=Yes 2=No." << endl;
    cin >> planted_choice;

    if (planted_choice && purchase_choice == 1) {
        cout << "Enter Price of plant seeds:";
        cin >> plant_price;
        cout << "Enter how many seeds planted:";
        cin >> amt_of_seeds;
    }
    if (planted_choice && purchase_choice == 2) {
        plant_price = 0;
        amt_of_seeds = 1;
    }
    if (planted_choice == 1 && purchase_choice == 2) {
        cout << "Enter how many seeds planted:";
        cin >> amt_of_seeds;
        plant_price = 0;
    }
    if (planted_choice == 2 && purchase_choice == 1) {
        cout << "Enter Price of plant seeds:";
        cin >> plant_price;
        amt_of_seeds = 1;
    }

    cout << "Enter Date Planted in 3 Digit Date Format:";
    cin >> plant_date;

    cout << "Enter Date Last Watered in 3 Digit Date Format:";
    cin >> last_watered;

    cout << "Enter Todays Date in 3 Digit Date Format:";
    cin >> todays_date;

    if (plant_date > last_watered || last_watered > todays_date)
        cout << "Please re-enter date data in the correct format. Conversion can be done at https://www-air.larc.nasa.gov/tools/jday.htm";
    else {
        days_old = todays_date - plant_date;
        days_water = todays_date - last_watered;
    }

    cout << "please select from the following menu" << endl;
    cout << "1 = Create report sheet in external document." << endl;
    cout << "2 = Create report sheet in computer terminal." << endl;
    cin >> choice;

    switch (choice)
     {
    case 1:
        outdata << fixed << showpoint;
        outdata.open("report.txt");
        outdata << "-------------- " << plant_type << " Summary " << "--------------" << endl;
        outdata << setw(10) << "Price" << setw(10) << "Seed #" << setw(10) << "Age" << setw(12) << "Last Water" << endl;
        outdata << setw(6) << "$" << setprecision(2) << plant_price << setw(8) << amt_of_seeds << setw(10) << days_old << setw(12) << days_water;
        outdata.close();
        break;

    case 2:
        cout << fixed << showpoint;
        cout << "-------------- " << plant_type << " Summary " << "--------------" << endl;
        cout << setw(10) << "Price" << setw(10) << "Seed #" << setw(10) << "Age" << setw(12) << "Last Water" << endl;
        cout << setw(6) << "$" << setprecision(2) << plant_price << setw(8) << amt_of_seeds << setw(10) << days_old << setw(12) << days_water;
        break;

    default:
        cout << "Selection was not in range";
     }

    return 0;
}