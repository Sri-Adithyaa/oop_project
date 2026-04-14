#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iomanip>
using namespace std;
class Company
{
   protected:
        string name,symbol;
        float net_worth,ipo;
        int no_shares;
    public:
        Company()
        {
            name="null";
            symbol="null";
            net_worth=0.0;
            ipo=0.0;
            no_shares=0;
        }
        Company(string sym,float net,int share,float ip,string nam)
        {
            name=nam;
            symbol=sym;
            net_worth=net;
            ipo=ip;
            no_shares=share;
        }
        friend ostream& operator<<(ostream& os,Company &c);
        friend istream& operator>>(istream& is,Company &c);
};
ostream& operator<<(ostream& os,Company &c)
{
        os<<c.symbol<<"|"<<fixed<<setprecision(2)<<c.net_worth<<"|"<<c.no_shares<<"|"<<fixed<<setprecision(2)<<c.ipo<<"|"<<c.name<<endl; 
        return os;
}
 class STOCK
 {
    protected:
        float price;
        Company C;
        


 };
 int main(int argc,char *argv[])
 {

 }