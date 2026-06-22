#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

const int MAX_PLANTS = 5;

enum GardenLevel { Beginner = 1, Intermediate = 2, Advanced = 3 };

void changeConsoleColor();
void displayBanner();
int displayMenu();
string getNonEmptyString(string prompt);
int getValidInt(string prompt, int minValue, int maxValue);
double getValidDouble(string prompt, double minValue, double maxValue);
GardenLevel getGardenLevel();
void collectPlantData(string plantNames[], int seeds[], double costs[], double waterGallons[], int plantCount);
double calculateTotalCost(double costs[], int plantCount);
int calculateTotalSeeds(int seeds[], int plantCount);
double calculateAverageWater(double waterGallons[], int plantCount);
void showRecommendation(GardenLevel level, int totalSeeds, double totalCost);
void displayReport(string gardenerName, string plantNames[], int seeds[], double costs[], double waterGallons[], int plantCount, GardenLevel level);
void saveReport(string gardenerName, string plantNames[], int seeds[], double costs[], double waterGallons[], int plantCount, GardenLevel level);

int main()
{
    string gardenerName;
    string plantNames[MAX_PLANTS];
    int seeds[MAX_PLANTS];
    double costs[MAX_PLANTS];
    double waterGallons[MAX_PLANTS];
    int plantCount = 0;
    GardenLevel level;
    int choice;

    changeConsoleColor();
    displayBanner();

    gardenerName = getNonEmptyString("Enter gardener name: ");
    level = getGardenLevel();

    do
    {
        choice = displayMenu();

        switch (choice)
        {
        case 1:
            plantCount = getValidInt("How many plant types do you want to track? 1-5: ", 1, MAX_PLANTS);
            collectPlantData(plantNames, seeds, costs, waterGallons, plantCount);
            break;

        case 2:
            if (plantCount > 0)
            {
                displayReport(gardenerName, plantNames, seeds, costs, waterGallons, plantCount, level);
                saveReport(gardenerName, plantNames, seeds, costs, waterGallons, plantCount, level);
            }
            else
            {
                cout << "Please add plant data first.\n";
            }
            break;

        case 3:
            if (plantCount > 0)
            {
                showRecommendation(level, calculateTotalSeeds(seeds, plantCount), calculateTotalCost(costs, plantCount));
            }
            else
            {
                cout << "Please add plant data first.\n";
            }
            break;

        case 4:
            cout << "Goodbye! Your garden tracker is closing.\n";
            break;

        default:
            cout << "Invalid menu choice.\n";
        }

    } while (choice != 4);

    return 0;
}

// Changes the console text color.
void changeConsoleColor()
{
    system("color 0A");
}

// Displays the program banner.
void displayBanner()
{
    cout << "=============================================\n";
    cout << "        Welcome to the Garden Tracker         \n";
    cout << "=============================================\n";
}

// Displays the menu and returns the user's choice.
int displayMenu()
{
    cout << "\nMenu\n";
    cout << "1. Add garden plants\n";
    cout << "2. View weekly report\n";
    cout << "3. Recommend garden level\n";
    cout << "4. Quit\n";
    return getValidInt("Choose an option: ", 1, 4);
}

// Gets a non-empty string.
string getNonEmptyString(string prompt)
{
    string value;

    cout << prompt;
    getline(cin, value);

    while (value == "")
    {
        cout << "Input cannot be blank. Try again: ";
        getline(cin, value);
    }

    return value;
}

// Gets and validates an integer.
int getValidInt(string prompt, int minValue, int maxValue)
{
    int value;

    cout << prompt;
    cin >> value;

    while (cin.fail() || value < minValue || value > maxValue)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Enter " << minValue << " through " << maxValue << ": ";
        cin >> value;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Gets and validates a double.
double getValidDouble(string prompt, double minValue, double maxValue)
{
    double value;

    cout << prompt;
    cin >> value;

    while (cin.fail() || value < minValue || value > maxValue)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Enter " << minValue << " through " << maxValue << ": ";
        cin >> value;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Gets the gardening skill level using an enum.
GardenLevel getGardenLevel()
{
    int choice;

    cout << "\nGarden level:\n";
    cout << "1. Beginner\n";
    cout << "2. Intermediate\n";
    cout << "3. Advanced\n";

    choice = getValidInt("Choose your level: ", 1, 3);

    return static_cast<GardenLevel>(choice);
}

// Collects plant data into arrays.
void collectPlantData(string plantNames[], int seeds[], double costs[], double waterGallons[], int plantCount)
{
    for (int i = 0; i < plantCount; i++)
    {
        cout << "\nPlant #" << i + 1 << endl;
        plantNames[i] = getNonEmptyString("Enter plant name: ");
        seeds[i] = getValidInt("Enter number of seeds planted: ", 1, 1000);
        costs[i] = getValidDouble("Enter total cost for this plant type: $", 0.0, 10000.0);
        waterGallons[i] = getValidDouble("Enter weekly water used in gallons: ", 0.0, 500.0);

        if (seeds[i] >= 20 && costs[i] <= 25.00)
        {
            cout << "Good value: many seeds for a low cost.\n";
        }
        else
        {
            cout << "This plant may need a higher budget or fewer seeds.\n";
        }

        if (waterGallons[i] <= 10.0 && seeds[i] >= 5)
        {
            cout << "Water usage looks efficient.\n";
        }
        else
        {
            cout << "Watch the water use for this plant.\n";
        }
    }
}

// Calculates total cost.
double calculateTotalCost(double costs[], int plantCount)
{
    double total = 0;

    for (int i = 0; i < plantCount; i++)
    {
        total = total + costs[i];
    }

    return total;
}

// Calculates total seeds.
int calculateTotalSeeds(int seeds[], int plantCount)
{
    int total = 0;

    for (int i = 0; i < plantCount; i++)
    {
        total = total + seeds[i];
    }

    return total;
}

// Calculates average weekly water.
double calculateAverageWater(double waterGallons[], int plantCount)
{
    double total = 0;

    for (int i = 0; i < plantCount; i++)
    {
        total = total + waterGallons[i];
    }

    return total / plantCount;
}

// Uses enum in a switch decision.
void showRecommendation(GardenLevel level, int totalSeeds, double totalCost)
{
    cout << "\nGarden Recommendation\n";

    switch (level)
    {
    case Beginner:
        cout << "Beginner: Start small and focus on easy plants.\n";
        break;
    case Intermediate:
        cout << "Intermediate: You can handle a medium garden.\n";
        break;
    case Advanced:
        cout << "Advanced: You are ready for a larger garden plan.\n";
        break;
    }

    if (totalSeeds >= 50 && totalCost <= 100.00)
    {
        cout << "Your garden plan is large but still affordable.\n";
    }
    else
    {
        cout << "Your garden plan may need budget or seed adjustments.\n";
    }
}

// Displays formatted report.
void displayReport(string gardenerName, string plantNames[], int seeds[], double costs[], double waterGallons[], int plantCount, GardenLevel level)
{
    cout << fixed << showpoint << setprecision(2);

    cout << "\nGarden Report for " << gardenerName << endl;
    cout << left << setw(18) << "Plant"
         << right << setw(10) << "Seeds"
         << setw(12) << "Cost"
         << setw(15) << "Water Gal." << endl;

    cout << "-------------------------------------------------------\n";

    for (int i = 0; i < plantCount; i++)
    {
        cout << left << setw(18) << plantNames[i]
             << right << setw(10) << seeds[i]
             << setw(12) << costs[i]
             << setw(15) << waterGallons[i] << endl;
    }

    cout << "-------------------------------------------------------\n";
    cout << left << setw(18) << "Totals"
         << right << setw(10) << calculateTotalSeeds(seeds, plantCount)
         << setw(12) << calculateTotalCost(costs, plantCount)
         << setw(15) << calculateAverageWater(waterGallons, plantCount) << endl;
}

// Saves formatted report to file.
void saveReport(string gardenerName, string plantNames[], int seeds[], double costs[], double waterGallons[], int plantCount, GardenLevel level)
{
    ofstream outFile("report.txt");

    outFile << fixed << showpoint << setprecision(2);

    outFile << "Garden Report for " << gardenerName << endl;
    outFile << left << setw(18) << "Plant"
            << right << setw(10) << "Seeds"
            << setw(12) << "Cost"
            << setw(15) << "Water Gal." << endl;

    outFile << "-------------------------------------------------------\n";

    for (int i = 0; i < plantCount; i++)
    {
        outFile << left << setw(18) << plantNames[i]
                << right << setw(10) << seeds[i]
                << setw(12) << costs[i]
                << setw(15) << waterGallons[i] << endl;
    }

    outFile << "-------------------------------------------------------\n";
    outFile << left << setw(18) << "Totals"
            << right << setw(10) << calculateTotalSeeds(seeds, plantCount)
            << setw(12) << calculateTotalCost(costs, plantCount)
            << setw(15) << calculateAverageWater(waterGallons, plantCount) << endl;

    outFile.close();

    cout << "Report saved to report.txt\n";
}