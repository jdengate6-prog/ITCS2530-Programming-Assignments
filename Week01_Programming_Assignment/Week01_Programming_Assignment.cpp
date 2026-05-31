#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    cout << "Welcome to my program which you can use to track your gareden plants!" << endl;

    string plant_type; //Type of Plant
    double plant_price; //Price of Plant
    int amt_of_seeds; //amt of seeds planted
    int plant_date;   //Date Plant was Planted
    int last_watered; //Date Plant was Last Watered
    int todays_date; //Todays Date
    int days_old;    //How Many Days Old the Plant is
    int days_water;  //How Many Days Since the Plant was Last Watered

    ofstream outdata;

    cout << "Enter Plant Type:";
    cin >> plant_type;

    cout << "Enter Price of plant seeds:";
    cin >> plant_price;

    cout << "Enter how many seeds planted:";
    cin >> amt_of_seeds;
    
    cout << "Enter Date Planted in 3 Digit Date Format:";
    cin >> plant_date;

    cout << "Enter Date Last Watered in 3 Digit Date Format:";
    cin >> last_watered;

    cout << "Enter Todays Date in 3 Digit Date Format:";
    cin >> todays_date;

    days_old = todays_date - plant_date;
    days_water = todays_date - last_watered;

    outdata << fixed << showpoint;
    outdata.open("report.txt");

    outdata << "-------------- " << plant_type << " Summary " << "--------------" << endl ;
    outdata << setw(10) << "Price" << setw(10) << "Seed #" << setw(10) << "Age" << setw(12) << "Last Water" << endl;
    outdata << setw(6) << "$" << setprecision(2) << plant_price << setw(8) << amt_of_seeds << setw(10) << days_old << setw(12) << days_water;
    
    outdata.close();

    

    return 0;
}