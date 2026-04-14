#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<iterator>
using namespace std;
class User;
class Trader;
void update_current(string &c_symbol,int &no_share,float &b_price,Trader &t,int c_inveted=0);
void update_file(string&,string&,int,float,Trader&);
void get_cur_price(string&,string&,float&);
void find_price(string,string&);
void find_c_name(string,string&);
void update_this(Trader &t1);
class User
{
protected:
    string user_name;
    float balance;
public:
    User()
    {
        user_name="nil";
        balance=1000000.00;
    }
    User(const User &u1)
    {
        user_name=u1.user_name;
        balance=u1.balance;
    }   
    User& operator=(const User &u1)
    {
        user_name=u1.user_name;
        balance=u1.balance;
        return *this;
    }
    bool check_exist(string user)
    {
        if(user==user_name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void get_base_data(string name,float bal=1000000.00)
    {
        user_name=name;
        balance=bal;
    }
};
class Trader:public User
{
    protected:
        int company_invested;
        vector<string> invest;
        vector<float> initial_price;
        vector<int> share;
    public:
        friend void update_current(string &c_symbol,int &no_share,float &b_price,Trader &t,int c_inveted);
        friend void update_this(Trader &t);
        Trader()
        {
            //doing nothing
            company_invested=0;
        }
        Trader(const Trader &t1)
        {
            company_invested=t1.company_invested;
            invest=t1.invest;
            initial_price=t1.initial_price;
            share=t1.share;
        }
        Trader& operator=(const Trader &t1)
        {
            User::operator=(t1);
            company_invested=t1.company_invested;
            invest=t1.invest;
            initial_price=t1.initial_price;
            share=t1.share;
            return *this;
        }
        void get_data(string inv,float init_price,int shar)
        {
            invest.push_back(inv);
            initial_price.push_back(init_price);
            share.push_back(shar);
        }
        void n_comp()
        {
            company_invested++;
        }
        friend ostream& operator<<(ostream &os,Trader &t1);
        void show_data()
        {
            cout<<"Trader name: "<<user_name<<endl;
            cout<<"current Balance: "<<fixed<<setprecision(2)<<balance<<endl;
            cout<<"Number of companies in portfolio: "<<company_invested<<endl;
            char ch;
            cout<<"would you like to view the portfolio status (y/n) : ";
            cin>>ch;
            if(ch=='y')
            {
                portfolio();
            }
        }
        void portfolio()
        { 
            system("cls");
            float cur_price=0.0,total_net=0.0;
            string c_name="";
            for(int i=0;i<company_invested;i++)
            {
                get_cur_price(invest[i],c_name,cur_price);
                cout<<"company name: "<<c_name<<endl;
                cout<<"current holdings :"<<share[i]<<endl;
                cout<<"price at time of buying: "<<fixed<<setprecision(2)<<initial_price[i]<<endl;
                if(cur_price>=initial_price[i])
                {
                    cout<<"current Trading price :\033[32m"<<fixed<<setprecision(2)<<cur_price<<"\033[0m"<<endl;
                    cout<<"you have a \033[32mProfit\033[0m of \033[32m"<<fixed<<setprecision(2)<<(cur_price-initial_price[i])<<"\033[0m"<<endl;
                }
                else
                {
                    cout<<"current Trading price :\033[31m"<<fixed<<setprecision(2)<<cur_price<<"\033[0m"<<endl;
                    cout<<"you have a \033[31mLOSS\033[0m of \033[31m"<<fixed<<setprecision(2)<<(cur_price-initial_price[i])<<"\033[0m"<<endl;
                }
                total_net+=(cur_price*share[i]);
                cout<<"_____________________________________________________________________________________________"<<endl;
            }
            cout<<"YOUR TOTAL NET WORTH BY SHARE HOLDINGS :"<<balance+total_net;
            cout<<"\npress Enter key continue..."<<endl;
            cin.ignore();
            cin.get();
        }
        void BUY_stock()
        {
            string line,temp1,temp2,c_name;
            vector<string> symb;
            float price;
            int comp=0;
            fstream file("company_list.txt",ios::in);
            while(getline(file,line))
            {
                stringstream str(line);
                getline(str,temp1,'|');
                cout<<"Trade symbol: "<<temp1<<endl;
                symb.push_back(temp1);
                getline(str,temp1,'|');
                getline(str,temp2,'|');
                getline(str,c_name,'|');
                getline(str,c_name,'|');
                cout<<"NAME of the company: "<<c_name<<endl;
                price=(stof(temp1)/stoi(temp2));
                cout<<"current price of each stock: "<<price<<endl;
                cout<<"_____________________________________________________________________________________________"<<endl;
            }
            file.flush();
            file.close();
            string c_symbol,s_price;
            int no_share;
            L8:cout<<"Enter the Trade symbol you want to buy: ";
            cin>>c_symbol;
            if((find(symb.begin(),symb.end(),c_symbol)==symb.end()))
            {
                cout<<"Invalid Trade symbol"<<endl;
                goto L8;    
            }
            if((find(invest.begin(),invest.end(),c_symbol)==invest.end()))
            {
                company_invested++;
                comp=1;
            }
            L0:cout<<"Enter the number of shares to Buy: ";
            cin>>no_share;
            find_price(c_symbol,s_price);
            price=stof(s_price);
            if(balance<no_share*price)
            {
                cout<<"\033[31mLOW Balance to buy shares\033[0m"<<endl;
                goto L0;
            }
            balance-=(no_share*price);
            if(comp)
            {
                invest.push_back(c_symbol);
                initial_price.push_back(price);
                share.push_back(no_share);
            }
            else
            {
                int index;
                auto it = find(invest.begin(),invest.end(),c_symbol);
                if(it != invest.end())
                {
                    index=distance(invest.begin(),it);
                }
                initial_price[index]=price;
                share[index]+=no_share;
            }
            
            string file_name=user_name+".txt";
            update_this(*this);
            string cmd;
            cmd=string("sync_engine.exe ")+string("BUY ")+c_symbol+string(" ")+string(user_name)+string(" ")+to_string(no_share)+string(" ")+to_string(price);
            system(cmd.c_str());

        }
        void SELL_stock()
        {
           string c_sym="",c_name="",c_price="0";
           int shares=0;
           for(int i=0;i<invest.size();i++)
           {
            find_c_name(invest[i],c_name);
            cout<<"Company name: "<<c_name<<endl;
            cout<<"Company symbol: "<<invest[i]<<endl;
            cout<<"Bought price: "<<initial_price[i]<<endl;
            cout<<"current Holdings: "<<share[i]<<endl;
            find_price(invest[i],c_price);
            cout<<"current price: "<<fixed<<setprecision(2)<<stof(c_price)<<endl;
            cout<<"_____________________________________________________________________________________________"<<endl;
           }
           L189:cout<<"Enter the Trade symbol you want to Sell: ";
           cin>>c_sym;
           if(find(invest.begin(),invest.end(),c_sym)==invest.end())
           {
            cout<<"Invalid Trade symbol"<<endl;
            goto L189;
           }
            auto it = find(invest.begin(),invest.end(),c_sym);
            int index;
            if(it != invest.end())
            {
                index=distance(invest.begin(),it);
            }
            find_price(c_sym,c_price);
           L202:cout<<"Enter the no of share you want to Sell: ";
           cin>>shares;
           if(shares>share[index])
           {
                cout<<"You can't sell more than you have"<<endl;
                goto L202;
           }
           balance+=shares*(stof(c_price));
           share[index]-=shares;
           if(share[index] == 0) 
           {
                invest.erase(invest.begin() + index);
                initial_price.erase(initial_price.begin() + index);
                share.erase(share.begin() + index);
                company_invested--;
            }
           update_this(*this);
           string cmd;
           cmd=string("sync_engine.exe ")+string("SELL ")+c_sym+string(" ")+string(user_name)+string(" ")+to_string(shares)+string(" ")+c_price;
           system(cmd.c_str());
        } 
};
void update_this(Trader &t1)
{  
    string line;
    string file_name=t1.user_name;
    file_name=file_name+".txt";
    fstream f2("temp.txt",ios::out);
    f2<<t1.company_invested<<endl;
    f2<<t1.balance<<endl;
    for(int i=0;i<t1.company_invested;i++)
    {
        f2<<t1.invest[i]<<','<<t1.share[i]<<','<<t1.initial_price[i]<<endl;
    }
    f2.close();
    remove(file_name.c_str());
    rename("temp.txt",file_name.c_str());
}
void find_price(string c_sym,string &c_price)
{
    string line;
    fstream f1("company_list.txt",ios::in);
    while(getline(f1,line))
    {
        string name,net;
        stringstream str(line);
        getline(str,name,'|');
        if(name==c_sym)
        {
            getline(str,net,'|');
            getline(str,name,'|');
            float price;
            price=((stof(net))/(stoi(name)));
            c_price=to_string(price);
            return;
        }
    }
}
void find_c_name(string c_sym,string &c_name)
{
    string line;
    fstream f1("company_list.txt",ios::in);
    while(getline(f1,line))
    {
        string name;
        stringstream str(line);
        getline(str,name,'|');
        if(name==c_sym)
        {
            while(getline(str,name,'|'))
            {
                c_name=name;
            }
            return;
        }
    }
}
void get_cur_price(string &c_sym,string &c_name,float &cur_price)
{
    string line,n_share,net_worth,temp_symb;
    fstream file("company_list.txt",ios::in);
    while(getline(file,line))
    {
        stringstream str(line);
        getline(str,temp_symb,'|');
        if(temp_symb==c_sym)
        {
            getline(str,net_worth,'|');
            getline(str,n_share,'|');
            getline(str,line,'|');
            getline(str,line,'|');
            c_name=line;
            cur_price=(stof(net_worth)/stoi(n_share));
            return;
        }
    }
    
}
ostream& operator<<(ostream &os,Trader &t1)
{
    os<<t1.company_invested<<endl;
    os<<t1.balance<<endl;
    for(int i=0;i<t1.company_invested;i++)
    {
        os<<t1.invest[i]<<","<<t1.share[i]<<","<<t1.initial_price[i]<<","<<endl;
    }
    return os;
}
void Display_market()
{
    string line,c_sym,net_worth,share,ipo,c_name;
    fstream f1("company_list.txt",ios::in);
    cout<<"company name\t|"<<"company symbol\t|"<<"company net worth\t|"<<"share\t|"<<"IPO"<<endl;
    while(getline(f1,line))
    {
        stringstream str(line);
        getline(str,c_sym,'|');
        getline(str,net_worth,'|');
        getline(str,share,'|');
        getline(str,ipo,'|');
        getline(str,c_name,'|');
        cout<<c_name<<"\t\t|"<<c_sym<<"\t\t|"<<net_worth<<"\t|"<<share<<"\t|"<<ipo<<endl;
    }
    f1.close();
    string ch;
    cout<<"would you like to see the trade graph (yes/no) :";
    cin>>ch;
    if(ch=="yes")
    {
        system("graph_sim.exe");
    }
}
int main(int argc,char* argv[])
{
    Trader T1;
        int found=0;
        string user_name,u_name,line;
        float cur_balence;
        int invested;
        user_name=argv[1];
        fstream file("trader_details.txt",ios::in);
        while(getline(file,line))
        {
            stringstream str(line);
            getline(str,u_name,',');
            if(user_name==u_name)
            {
                found=1;
                break;
            }
        } 
        if(found)
        {
            int no_company,shares;
            string c_symbol,temp;
            float buy_price,balance;
            string filename=user_name+".txt";
            fstream f1(filename,ios::in);
            getline(f1,line);
            no_company=stoi(line);
            getline(f1,line);
            balance=stof(line);
            T1.get_base_data(user_name,balance);
            for(int i=0;i<no_company;i++)
            {
                    getline(f1,line);
                    stringstream str(line);
                    getline(str,c_symbol,',');
                    getline(str,temp,',');
                    shares=stoi(temp);
                    getline(str,temp,',');
                    buy_price=stof(temp);
                    T1.get_data(c_symbol,buy_price,shares);
                    T1.n_comp();
                
            }
            for(int i=1;i<=2;i++)
            {
                cout<<"\rwait for "<<i<<"sec"<<flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            cout<<"\033[32m\t\t\tSuccesfully logged in....\033[0m"<<endl;
            for(int i=0;i<=1;i++)
            {
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        else
        {
            found=0;
            cout<<"\n\033[31m"<<user_name<<" is not listed Trader"<<"\033[0m"<<endl;
            for(int i=1;i<=2;i++)
            {
                this_thread::sleep_for(chrono::seconds(1));
            }
            system("cls");
            string admin,key,line,temp_admin,temp_key;
            L2:fstream f1("admin_user.txt",ios::in);
            cout<<"Enter the admin user name and password to add a new Trader"<<endl;
            cout<<"Enter the admin User name= ";
            cin>>admin;
            cout<<"Enter admin password= ";
            cin>>key;
            while(getline(f1,line))
            {
                stringstream str(line);
                getline(str,temp_admin,',');
                getline(str,temp_key,',');
                if(temp_admin==admin && temp_key==key)
                {
                    found=1;
                    break;
                }
            }
            f1.close();
            if(found)
            {
                cout<<"\nAdding a new User:"<<endl;
                fstream file("trader_details.txt",ios::app);
                file<<user_name<<","<<"0,1000000.00"<<endl;
                file.flush();
                file.close();
                string filename=user_name+".txt";
                fstream f1(filename,ios::out);
                f1<<"0"<<endl;
                f1.flush();
                T1.get_base_data(user_name);
                f1<<T1;
            }
            else
            {
                cout<<"\033[31m"<<"Admin access denied"<<"\033[0m"<<endl;
                cout<<"try again..."<<endl;
                goto L2;
            }
        }
    //completed connecting 


    cout<<"\033[32mWELCOME "<<user_name<<"\033[0m...."<<endl;
    while(true)
    {   int ch;
        system("cls");
        cout<<"Logged in as \033[32m"<<user_name<<"\033[0m"<<endl;
        cout<<"1)To see the complete PORTFOLIO"<<endl;
        cout<<"2)To BUY stocks"<<endl;
        cout<<"3)To sell stocks"<<endl;
        cout<<"4)To view the market"<<endl;
        cout<<"5)Exit"<<endl;
        cout<<"Enter your choice= ";
        cin>>ch;
        switch(ch)
        {
            case 1:
            {
                system("cls");
                T1.show_data();
                break;
            }
            case 2:
            {
                system("cls");
                T1.BUY_stock();
                break;
            }
            case 3:
            {
                system("cls");
                T1.SELL_stock();
                break;
            }
            case 4:
            {
                system("cls");
                Display_market();
                break;
            }
            case 5:
            {
                exit(0);
            }
        }   
    }
}