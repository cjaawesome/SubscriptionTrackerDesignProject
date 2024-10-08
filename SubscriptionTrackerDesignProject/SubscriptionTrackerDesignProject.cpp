//Cooper Adcock
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip> 
#include <vector>
using namespace std;

const string ERROR_HEADER = "Error: ";
const string ERROR_LOG_FILE = "error.txt";
const string SAVE_FILE = "save.txt";





enum type {
    Daily = 0,
    Weekly = 1,
    Monthly = 2,
    Yearly = 3
};

chrono::year_month_day currentTime();
string dateToString(chrono::year_month_day t);
string typeToString(type bp);
int userInputValidator(istream& in);
void addInputValidator(istream& in, ostream& out);
void removeInputValidator(istream& in, ostream& out);

class SubscriptionService {
private:
    string name;
    float price;
    type billingPeriod;
    chrono::year_month_day aniversaryDate;
public:
    
    SubscriptionService(string n, float p, type b, chrono::year_month_day d);
    SubscriptionService();
    void print(ostream& out);
    void rawdata(ostream& out);
    string getName() { return name; }
    float getPrice() { return price; }
    type getbillingPeriod() { return billingPeriod; }
    chrono::year_month_day getBillDate() { return aniversaryDate; }
    chrono::year_month_day getNextDate();

};

SubscriptionService dataValidator(istream& in);



vector<SubscriptionService> Services;

int main() {
    ifstream in;
    ofstream out;
    in.open(SAVE_FILE);

    in.seekg(0, ios::end); //set position of stream to end
    streampos size = in.tellg(); //get size of stream


    if (!in.good() || size <= 0) { // if file is not good or empty return 1 and display error message
        cout << "Welcome to Subscription Tracker!" << endl;
    }
    else {
        in.seekg(0, ios::beg);
        while (!in.eof()) {
            SubscriptionService newService;
            newService = dataValidator(in); // checks if service is valid
            if (newService.getPrice() != -1) {
                Services.push_back(newService); // add new service if valid
            }
        }
    }
     //set position of stream to begining
    in.close();

    int userInput = 0;
    do {
        if(Services.size() == 0){
            cout << "No services logged yet" << endl;
        }
        else {
            for (int i = 0; i < Services.size(); i++) {
                cout << "Index: " << i + 1 << endl;
                Services[i].print(cout);
            }
            cout << "If you would like to remove a service type \"Remove\" or \"remove\" " << endl;
        }
        cout << "If you would like to add a service type \"Add\" or \"add\" " << endl;
        cout << "If you would like to exit and save type \"Exit\" or \"exit\" " << endl;
        userInput = userInputValidator(cin);

        if (userInput == 0) {
            cout << "Fairwell!" << endl;
        }
        else if (userInput == 1) {
            addInputValidator(cin, cout);
            cin.clear(); //clears cin
            cin.ignore(256, '\n');
        }
        else if (userInput == 2) {
            removeInputValidator(cin, cout);
            cin.clear(); //clears cin
            cin.ignore(256, '\n');
        }
        else {
            cout << "Invalid Input. Try again." << endl;
        }
        
    } while (userInput != 0);
    out.open(SAVE_FILE, ios::out);
    for (int i = 0; i < Services.size(); i++) {
        Services[i].rawdata(out);
        if(i < Services.size()-1)out << endl;
    }
    out.close();
    
    return 0;
}


float getPrice(istream& in, ostream& out) {
    float input; //initializes input as a float
    bool inputInvalid = true; //initializes inputInvalid and sets it to true
    while (inputInvalid) { // while the input is invalid continue to prompt the user
        in >> input;// get input
        inputInvalid = (!cin.good() || input < 0); // sets inputInvalid to weather the input is valid or not
        if (inputInvalid) { // checks if input is invalid
            out << "Need a positive real number; please try again.\n"; //user warning
            in.clear(); //clears cin
            in.ignore(256, '\n'); //ignores latest input
        }
    }
    return input; //returns input
}

int getBillingPeriod(istream& in, ostream& out) {
    int input; //initializes input as a int
    bool inputInvalid = true; //initializes inputInvalid and sets it to true
    while (inputInvalid) { // while the input is invalid continue to prompt the user
        in >> input;// get input
        inputInvalid = (!cin.good() || input > 3 || input < 0); // sets inputInvalid to weather the input is valid or not
        if (inputInvalid) { // checks if input is invalid
            out << "Need a whole number between 0 and 3; please try again.\n"; //user warning
            in.clear(); //clears cin
            in.ignore(256, '\n'); //ignores latest input
        }
    }
    return input; //returns input
}
int getInt(istream& in, ostream& out) {
    int input; //initializes input as a int
    bool inputInvalid = true; //initializes inputInvalid and sets it to true
    while (inputInvalid) { // while the input is invalid continue to prompt the user
        in >> input;// get input
        inputInvalid = (!cin.good()); // sets inputInvalid to weather the input is valid or not
        if (inputInvalid) { // checks if input is invalid
            out << "Need a whole number; please try again.\n"; //user warning
            in.clear(); //clears cin
            in.ignore(256, '\n'); //ignores latest input
        }
    }
    return input; //returns input
}

chrono::year_month_day currentTime() {
    auto now = chrono::system_clock::now();
    auto days_since_epoch = duration_cast<chrono::days>(now.time_since_epoch());
    auto ymd = chrono::year_month_day{ chrono::sys_days{days_since_epoch} };
    return ymd;
}
bool isValidDate(int year, unsigned month, unsigned day, ostream& out) {

    // create date object
    chrono::year_month_day date{ chrono::year{year}, chrono::month{month},chrono::day{day} };

    // 
    if (!date.ok()) out << "Date not valid. Try Again." << endl;
    return date.ok();  // Returns true if the date is valid
}
void addInputValidator(istream& in, ostream& out) {
    //inti
    string name;

    float price;
    int billPeriod;
    int year;
    unsigned day, month;
    
    out << "Name of Service: " << endl;
    getline(in, name);

    out << "Price: " << endl;
    price = getPrice(in, out);

    out << "Billing Period (0 = Daily, 1 = Weekly, 2 = Monthly, 3 = Yearly): " << endl;
    billPeriod = getBillingPeriod(in, out);

    do {
        out << "Day: " << endl;
        day = getInt(in, out);

        out << "Month: " << endl;
        month = getInt(in, out);
        
        out << "Year: " << endl;
        year = getInt(in, out);

    } while (!isValidDate(year, month, day, out));

    chrono::year_month_day aniversaryDate = { chrono::year{year}, chrono::month{month}, chrono::day{day} };
    
   
    SubscriptionService newService(name, price, static_cast<type>(billPeriod), aniversaryDate);

    Services.push_back(newService);
}

int getIndex(istream& in, ostream& out) {
    int input; //initializes input as a int
    bool inputInvalid = true; //initializes inputInvalid and sets it to true
    while (inputInvalid) { // while the input is invalid continue to prompt the user
        in >> input;// get input
        inputInvalid = (!cin.good() || input <= 0 || input > Services.size()); // sets inputInvalid to weather the input is valid or not
        if (inputInvalid) { // checks if input is invalid
            out << "Need a whole number; please try again.\n"; //user warning
            in.clear(); //clears cin
            in.ignore(256, '\n'); //ignores latest input
        }
    }
    return input; //returns input
}
void removeInputValidator(istream& in, ostream& out) {
    out << "Index of Service: " << endl; // prompt user
    int index = getIndex(in, out); // verify if index is valid
    Services.erase(Services.begin() + index - 1); //remove item from list

}

string dateToString(chrono::year_month_day t) {
    stringstream ss;
    ss << unsigned(t.month()) << "/" << unsigned(t.day()) << "/" << int(t.year());
    return ss.str();
}
string typeToString(type bp) {
    switch (bp) { //converts type to string
    case Daily:
        return "Daily";
        break;
    case Weekly:
        return "Weekly";
        break;
    case Monthly:
        return "Monthly";
        break;
    case Yearly:
        return "Yearly";
        break;
    }
    return "ERROR"; //returns error if something bad happens
}

SubscriptionService::SubscriptionService(string n, float p, type b, chrono::year_month_day d){ // constructor for subscription service
    // sets values to values given from inputs
    name = n;
    price = p;
    billingPeriod = b;
    aniversaryDate = d;
}
SubscriptionService::SubscriptionService() {
    // default constructor
    name = "Empty";
    price = -1;
    billingPeriod = static_cast<type>(0);
    aniversaryDate = currentTime();
}
std::chrono::year_month_day SubscriptionService::getNextDate() { // gets next payment date
    
    //intialize variables for the current time and a temp variable for the next payment date
    auto now = currentTime();
    auto nowSysDays = chrono::sys_days(now);
    auto tempSysDays = chrono::sys_days(aniversaryDate);

    while (nowSysDays >= tempSysDays) { // increments date depending on the payment period
        switch (billingPeriod) {
        case Daily:
            tempSysDays = tempSysDays + chrono::days{ 1 };
            break;
        case Weekly:
            tempSysDays += chrono::days{ 7 };
            break;
        case Monthly:
            tempSysDays += chrono::days{ 30 };
            break;
        case Yearly:
            tempSysDays += chrono::days{ 365 };
            break;
        }
    }
    return chrono::year_month_day(tempSysDays); // returns next payment date
}

void SubscriptionService::print(ostream& out) {
    string date = dateToString(aniversaryDate); //converts date to string
    out << "Name: " << name << endl; // prints name
    out << "Price: $" << fixed << setprecision(2) << price << endl; //prints price
    out << "Billing Period: " << typeToString(billingPeriod) << endl; // prints billing period
    out << "Start Date: " << date << endl; // prints date
    out << "Next Payment Date: : " << dateToString(getNextDate()) << endl; // prints next payment date
}

void SubscriptionService::rawdata(ostream& out) { //prints out data in a raw form for the save file
    out << name << endl;
    out << price << " " << billingPeriod << " " << int(aniversaryDate.year()) << " " << unsigned(aniversaryDate.month()) << " " << unsigned(aniversaryDate.day());
}


int userInputValidator(istream& in) { // validates user input
    string input;
    getline(in, input);
    if (input == "exit" || input == "Exit") { //if input is exit, add, or remove repective numbers will be returned.
        return 0;
    }
    else if (input == "add" || input == "Add") {
        return 1;
    }
    else if ((input == "remove" || input == "Remove") && Services.size() > 0) {
        return 2;
    }


    return -1; //return -1 for invalid input
}



SubscriptionService dataValidator(istream& in) { //validator for save file.
     //intialization of variables for a new sevice
     string name;
     float price;
     int billPeriod;
     int year;
     unsigned day, month;
     
     SubscriptionService service;
  
     getline(in, name);
     //takes in a
     in >> price;
     in >> billPeriod;
     in >> year;
     in >> month;
     in >> day;
     chrono::year_month_day aniversaryDate = { chrono::year{year}, chrono::month{month}, chrono::day{day} };
     if (in.fail() || !isValidDate(year, month, day, cout)) { // if data is corrupted set price to -1 and name to invalid. also send message to user
         name = "Invalid Service";
         price = -1;
         cout << "Save file has been corrupted. Services may be missing." << endl;
     }
      // create date based on input

     service = SubscriptionService(name, price, static_cast<type>(billPeriod), aniversaryDate); // creates new

     string trash;
     getline(in, trash);


     return service; //returns new service
}



