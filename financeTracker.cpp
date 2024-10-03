//Cooper Adcock
#include <iostream>
#include <fstream>
#include <list>
#include <iomanip> 
#include <ctime>
using namespace std;

enum Timeframe {
    Daily,
    Weekly,
    Monthly
};
class SubscriptionService {
private:
    string serviceName;
    Timeframe timeframe;
    float price;
    tm date;

public:
    // Constructor
    SubscriptionService(string name, Timeframe tf, float p, tm d){
    serviceName = name; // name of service
    timeframe = tf; // payment window
    price = p;
    date = d;
    }
    void print(ostream& outS){
        outS << left << setw(20) << serviceName << " | ";
        outS << left << setw(10);
        switch(timeframe){
            case Daily:
                outS << "Daily";
                break;
            case Weekly:
                outS << "Weekly";
                break;
            case Monthly:
                outS << "Monthly";
                break;
        }
        outS << " | $";
        outS << left << setw(10);
        outS << fixed << setprecision(2) << price << " | ";
        outS << date.tm_mon + 1 << "/" << date.tm_mday << "/" << date.tm_year + 1900 << endl;
    }
    void rawdataout(ostream& outS){
        outS << serviceName << endl;
        outS << timeframe << ' ' << price << ' ' << date.tm_mday << ' ' << date.tm_mon << ' ' << date.tm_year;
        outS << endl;
    }
    tm nextPaymentDueDate(){

    }
};
tm createTm(int day, int month, int year);
bool isValidDate(int year, int month, int day);
float getFloat();
tm getDate();
tm currentTime();



int main(){
    
    float p;
    Timeframe myTimeframe = Monthly;
    string n;
    cout << "Name: ";
    getline(cin, n);
    cout << "Price: ";
    p = getFloat();
    tm d = getDate();
    
    
    SubscriptionService test(n, myTimeframe, p, d);
    test.print(cout);
    test.rawdataout(cout);
}



tm createTm(int day, int month, int year) {
    tm date = {};
    date.tm_mday = day;            // Day of the month (1-31)
    date.tm_mon = month - 1;       // Month of the year (0-11)
    date.tm_year = year - 1900;    // Year since 1900
    date.tm_isdst = -1;             // Let the system determine whether DST is in effect

    return date;
}


float getFloat(){
    float input; //initializes input as a float
    bool inputInvalid = true; //initializes inputInvalid and sets it to true
    while(inputInvalid){ // while the input is invalid continue to prompt the user
        cin >> input;// get input
        inputInvalid = !cin.good(); // sets inputInvalid to weather the input is valid or not
        if(inputInvalid){ // checks if input is invalid
            cout << "Need a float value; please try again.\n"; //user warning
            cin.clear(); //clears cin
            cin.ignore(256, '\n'); //ignores latest input
        }
    }
    return input; //returns input
}

tm getDate(){
    int d,m,y; // variables for day month year
    do{
        cout << "Day: ";
        cin >> d;
        cout << "Month: ";
        cin >> m;
        cout << "Year: ";
        cin >> y;
        if(!isValidDate(y, m, d)){
            cout << "Not valid Date." << endl;
        }
    }while(!isValidDate(y, m, d));
    return createTm(d,m,y);
}

tm currentTime(){
    time_t now = time(0);
    tm* d = localtime(&now);
    return *d;
}

bool isValidDate(int year, int month, int day) {
    // Create a tm structure and set values
    std::tm timeStruct = {};
    timeStruct.tm_year = year - 1900; // tm_year is years since 1900
    timeStruct.tm_mon = month - 1;     // tm_mon is 0-11
    timeStruct.tm_mday = day;

    // Normalize the tm structure
    std::time_t time = std::mktime(&timeStruct);

    // Check if the conversion back gives us the same values
    return (time != -1 && timeStruct.tm_year + 1900 == year &&
            timeStruct.tm_mon + 1 == month && timeStruct.tm_mday == day);
}
