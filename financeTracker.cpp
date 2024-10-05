//Cooper Adcock
#include <iostream>
#include <fstream>
#include <list>
#include <iomanip> 
#include <chronos>
using namespace std;

enum type{
    Daily,
    Weekly,
    Monthly,
    Yearly
}


class SubscriptionService{
private:
    string name;
    float price;
    type billingPeriod;
    date::year_month_day billDate;
public:
    void print(ostream& out);
    SubscriptionService(string n, float p, type b, year_month_day d);
    string getName(){return name;}
    float getPrice(){return price;}
    type getbillingPeriod(){return billingPeriod;}
    year_month_day getBillDate(){return billDate;}
    year_month_day getNextDate();

}


int main(){
    

    return 0;
}


SubscriptionService::SubscriptionService(string n, float p, type b, year_month_day d = chrono::system_clock::now()){
    name = n;
    price = p;
    billingPeriod + b;
    billDate = d;
}
year_month_day SubscriptionService::getNextDate(){
    date::year_month_day now = std::chrono::system_clock::now();
    date::year_month_day temp = billDate;
    while(temp < now){
        switch(billingPeriod){
            case Daily:
                temp += chrono::days{1};
                break;
            case Weekly:
                temp += chrono::days{7};
                break;
            case Monthly:
                temp += chrono::month{1};
                break;
            case Yearly:
                temp += chrono::year{1};
                break;
        }
    }
}

void print(ostream& out){
    string date = "" + billDate.month() + "/" + billDate.day() + "/" + billDate.year();
    
}