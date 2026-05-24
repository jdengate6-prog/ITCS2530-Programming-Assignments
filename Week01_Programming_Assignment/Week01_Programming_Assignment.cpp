#include <iostream>

using namespace std;

int main()
{
    string plant_type; //Type of Plant
    int plant_date;   //Date Plant was Planted
    int last_watered; //Date Plant was Last Watered
    int todays_date; //Todays Date
    int days_old;    //How Many Days Old the Plant is
    int days_water;  //How Many Days Since the Plant was Last Watered

    cout << "Enter Plant Type:";
    cin >> plant_type;

    cout << "Enter Date Planted in 3 Digit Date Format:";
    cin >> plant_date;

    cout << "Enter Date Last Watered in 3 Digit Date Format:";
    cin >> last_watered;

    cout << "Enter Todays Date in 3 Digit Date Format:";
    cin >> todays_date;

    days_old = todays_date - plant_date;
    days_water = todays_date - last_watered;

    cout << "Your " << plant_type << " crop is " << days_old << " days old, and was last watered " << days_water << " days ago." << endl;

    

    return 0;
}