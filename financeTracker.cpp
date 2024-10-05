//Cooper Adcock
#include <iostream>
#include <fstream>
#include <list>
#include <iomanip> 
#include <chrono>
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
    std::chrono::year_month_day billDate;
public:
    void print(ostream& out);
    SubscriptionService(string n, float p, type b, std::chrono::year_month_day d);
    string getName(){return name;}
    float getPrice(){return price;}
    type getbillingPeriod(){return billingPeriod;}
    std::chrono::year_month_day getBillDate(){return billDate;}
    std::chrono::year_month_day getNextDate();

}


int main(){

    std::chrono::year_month_day date = year{2024}/month{1}/day{1};
    SubscriptionService temp("Disney", 10.00, Daily, )

    return 0;
}


SubscriptionService::SubscriptionService(string n, float p, type b, std::chrono::year_month_day d = chrono::system_clock::now()){
    name = n;
    price = p;
    billingPeriod + b;
    billDate = d;
}
std::chrono::year_month_day SubscriptionService::getNextDate(){
    std::chrono::year_month_day now = std::chrono::system_clock::now();
    std::chrono::year_month_day temp = billDate;
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
    cout << 
}