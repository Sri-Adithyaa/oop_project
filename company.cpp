#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iomanip>
using namespace std;
class Company;
void update_file(Company &c1);
void update_file(Company &c1,string sym);
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
        friend void update_file(Company &c1);
        friend void update_file(Company &c1,string sym);
        bool check_exist(string c_name)
        {
            if(c_name==name)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        void get_c_name(string &c_name)
        {
            c_name=name;
        }
        string get_name()
        {
            return name;
        }
        string get_symbol()
        {
            return symbol;
        }
        float get_net()
        {
            return net_worth;
        }
        int get_share()
        {
            return no_shares;
        }
        void get_data(string &sym,float &net,int &share,float &ip,string &nam)
        {
            nam=name;
            sym=symbol;
            net=net_worth;
            ip=ipo;
            share=no_shares;
        }
        void Retain_stock(int stock)
        {
                if((no_shares-stock)>0)
                {
                    no_shares-=stock;
                    update_file(*this);
                }
                else
                {
                    cout<<"\033[31mCan't retain more than released\033[0m"<<endl;
                    for(int i=0;i<=1;i++)
                    {
                    this_thread::sleep_for(chrono::seconds(1));
                    }
                    return;
                }
        }
        void Release_stock(int stock)
        {
                no_shares+=stock;
                string temp_store;
                temp_store=string("./sync_engine.exe ")+string("C_SHARE ")+to_string(no_shares);
                system(temp_store.c_str());//complete the sync engine 
                update_file(*this);
                cout<<"Succesfully releassed Stocks to public Trade"<<endl;
                for(int i=0;i<1;i++)
                {
                this_thread::sleep_for(chrono::seconds(1));
                }
        }
        void update_data()
        {
            cout<<"Note: "<<endl;
            cout<<"company can only modify the company name or Trade symbol after listing \n";
            cout<<"and modifing other details is subject to crime"<<endl;
            int ch;
            cout<<"1)To change the Name \n2)To change Trade symbol \n3)To exit"<<endl;
            cout<<"Enter your choice= ";
            cin>>ch;
            switch(ch)
            {
                case 1:
                {   string temp_store;
                    L7:cout<<"Enter the new name of the company = ";
                    cin>>temp_store;
                    string line,c_name,temp;
                    int found=0;
                    fstream f1("company_list.txt",ios::in);
                    while(getline(f1,line))
                    {
                        stringstream str(line);
                        while(getline(str,temp,'|'))
                        {
                            c_name=temp;
                        }
                        if(temp_store==c_name)
                        {
                            found=1;
                            break;
                        }
                    }
                    f1.close();
                    if(found)
                    {
                        cout<<"\033[31mThe company name already excist\033[0m"<<endl;
                        goto L7;
                    }
                    else
                    {
                        string o_name;
                        o_name=name;
                        name=temp_store;
                        temp_store=string("./sync_engine.exe ")+string("C_NAME ")+symbol+" "+name+" "+o_name;
                        update_file(*this);
                        system(temp_store.c_str());
                        cout<<"\033[32m Company Name is Officialy changed \033[0m"<<endl;
                        for(int i=0;i<1;i++)
                        {
                        this_thread::sleep_for(chrono::seconds(1));
                        }
                    }
                    break;
                }
                case 2:
                {
                    string temp_store;
                    L4:cout<<"Enter the new Trade Symbol of the company = ";
                    cin>>temp_store;
                    string line,c_symbol;
                    int found=0;
                    fstream f1("company_list.txt",ios::in);
                    while(getline(f1,line))
                    {
                        stringstream str(line);
                        getline(str,c_symbol,'|');
                        if(temp_store==c_symbol)
                        {
                            found=1;
                            break;
                        }
                    }
                    f1.close();
                    if(found)
                    {
                        cout<<"\033[31mThe company Trade Symbol already excist\033[0m"<<endl;
                        goto L4;
                    }
                    else
                    {   string o_sym;
                        o_sym=symbol;
                        symbol=temp_store;
                        temp_store=string("./sync_engine.exe ")+string("C_SYM ")+symbol+" "+o_sym;
                        update_file(*this,o_sym);
                        system(temp_store.c_str());//complete the sync engine
                        cout<<"\033[32m Company Symbol is Officialy changed \033[0m"<<endl;
                        for(int i=0;i<1;i++)
                        {
                        this_thread::sleep_for(chrono::seconds(1));
                        }
                    }
                    break;
                }
                case 3:
                {
                    return;
                }
            }
            
        }
    }; 
    void update_file(Company &c1)
    {
        string line,symb;
        fstream f1("company_list.txt",ios::in);
        fstream f2("temp.txt",ios::out);
        while(getline(f1,line))
        {
            stringstream str(line);
            getline(str,symb,'|');
            if(symb==c1.symbol)
            {
                f2<<c1;
                f2.flush();
            }
            else
            {
                f2<<line<<endl;
                f2.flush();
            }
        }
        f1.close();
        f2.close();
        remove("company_list.txt");
        rename("temp.txt","company_list.txt");
    }
    void update_file(Company &c1 , string o_symb)
{
    string line, symb;

    fstream f1("company_list.txt", ios::in);
    fstream f2("temp.txt", ios::out);

    while(getline(f1, line))
    {
        stringstream str(line);

        getline(str, symb, '|');

        if(symb == o_symb)
        {
            f2 << c1;
            f2.flush();
        }
        else
        {
            f2 << line << endl;
            f2.flush();
        }
    }

    f1.close();
    f2.close();

    remove("company_list.txt");
    rename("temp.txt", "company_list.txt");
}
    ostream& operator<<(ostream& os,Company &c)
    {
        os<<c.symbol<<"|"<<fixed<<setprecision(2)<<c.net_worth<<"|"<<c.no_shares<<"|"<<fixed<<setprecision(2)<<c.ipo<<"|"<<c.name<<endl; 
        return os;
    }
    istream& operator>>(istream& is,Company &c)
    {
        cout<<"Enter the name of the company = ";
        is>>c.name;
        cout<<"Enter the symbol alloated to the company= ";
        is>>c.symbol;
        cout<<"Enter the estimated net worth of the company= ";
        is>>c.net_worth;
        cout<<"Enter the intial public offering of the company= ";
        is>>c.ipo;
        cout<<"Number of shares to split= ";
        is>>c.no_shares;
        return is;
    }
int main(int argc,char* argv[])
{
    Company c1;
    
    if(argc>1)
    {
        int found=0;
        string comp_name,line,sym;
        float ip,net;
        int share;
        comp_name=argv[1];
        fstream file("company_list.txt",ios::in);
        while(getline(file,line))
        {
            string temp_c_name,c_name,temp;
                stringstream str(line);
                getline(str,sym,'|');
                getline(str,temp,'|');
                net=stof(temp);
                getline(str,temp,'|');
                share=stoi(temp);
                getline(str,temp,'|');
                ip=stof(temp);
                getline(str,c_name,'|');
            if(c_name==comp_name)
            {
                found=1;
                c1=Company(sym,net,share,ip,c_name);
                break;
            }
        } 
        if(found)
        {
            cout<<"Gathering "<<comp_name<<" details..."<<endl;
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
            cout<<"\033[31m"<<comp_name<<" doesn't listed "<<"\033[0m"<<endl;
            for(int i=1;i<=2;i++)
            {
                this_thread::sleep_for(chrono::seconds(1));
            }
            return 1;//if compsany name not found
        } 
    }
    else
    {
        int found=0;
        string admin,key,line,temp_admin,temp_key;
        L2:fstream f1("admin_user.txt",ios::in);
        cout<<"\nEnter the admin user name and password to add a new company"<<endl;
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
            string line,rest,c_name;
            L1:cout<<"\nAdding a new Company:"<<endl;
            cin>>c1;
            fstream f1("company_list.txt",ios::in);
            //checking bfore adding 
            while(getline(f1,line))
            {
                string temp_c_name;
                stringstream str(line);
                while(getline(str,temp_c_name,'|'))
                {
                    c_name=temp_c_name;
                }
                if(c1.check_exist(c_name))
                {
                    cout<<"\033[31m"<<"Company is already listed"<<"\033[0m"<<endl;
                    goto L1;
                }
            }
            f1.close();
            f1.open("company_list.txt",ios::app);
            f1<<c1;
            f1.flush();
            c1.get_c_name(c_name);
            cout<<"\033[32m"<<c_name<<" is listed to the public and availabe for tradding"<<"\033[0m"<<endl;
            f1.close();
        }
        else
        {
             cout<<"\033[31m"<<"Admin access denied"<<"\033[0m"<<endl;
             cout<<"try again..."<<endl;
             goto L2;
        }
    }
    //company interface
    while(true)
    {   cout<<"\033[0m";
       system("cls");
        string c_name;
        int ch;
        c1.get_c_name(c_name);
        cout<<"\033[35m"<<c_name<<"\033[0m"<<endl;
        cout<<"1)view company details"<<endl;
        cout<<"2)update company details"<<endl;
        cout<<"3)Retain shares"<<endl;
        cout<<"4)Release shares"<<endl;
        cout<<"5)exit"<<endl;
        cout<<"Enter your choice =";
        cin>>ch;
        switch(ch)
        {
            case 1:
            {
                system("cls");
                string symb;
                float net_worth,ipo;
                int no_share;
                c1.get_data(symb,net_worth,no_share,ipo,c_name);
                cout<<"company name: "<<"\033[35m\t\t\t"<<c_name<<"\033[0m"<<endl;
                cout<<"Trade symbol: "<<"\033[35m\t\t\t"<<symb<<"\033[0m"<<endl;
                cout<<"current NET WORTH: "<<"\033[35m\t\t"<<fixed<<setprecision(2)<<net_worth<<"\033[0m"<<endl;
                cout<<"Initial public offering: "<<"\033[35m\t"<<fixed<<setprecision(2)<<ipo<<"\033[0m"<<endl;
                cout<<"Number of shares available: "<<"\033[35m\t"<<no_share<<"\033[0m"<<endl;
                string line,sym,temp;
                float last_price;
                int found=0;
                fstream f1("transaction.txt",ios::in);
                while(getline(f1,line))
                {
                    stringstream str(line);
                    getline(str,sym,'|');
                    if(c1.get_symbol()==sym)
                    {
                        found=1;
                        while(getline(str,sym,'|'))
                        {
                        temp=sym;
                        }
                        last_price=stof(sym);
                    }
                }
                if(found)
                {
                    if((c1.get_net()/c1.get_share())>last_price)
                    {
                        cout<<"Price per stock: "<<"\033[32m\t\t"<<(c1.get_net()/c1.get_share())<<"\033[0m"<<endl;
                    }
                    else
                    {
                        cout<<"Price per stock: "<<"\033[31m\t\t"<<(c1.get_net()/c1.get_share())<<"\033[0m"<<endl;
                    }
                }
                else
                {
                    cout<<"Price per stock: "<<"\033[33m"<<(c1.get_net()/c1.get_share())<<"\033[0m"<<endl;
                }
                cout<<"press Enter key continue..."<<endl;
                cin.ignore();
                cin.get();
                break;
            }
            case 2:
            {
               system("cls");
                c1.update_data();
                break;
            }
            case 3:
            {
                system("cls");
                int stock;
                cout<<"Enter the number of stock you need to Retain= ";
                cin>>stock;
                c1.Retain_stock(stock);
                break;
            }
            case 4:
            {
                system("cls");
                int stock;
              
                cout<<"Enter the number of stock you need to Release= ";
                cin>>stock;
                c1.Release_stock(stock);
                break;
            }
            case 5:
            {
                return 0;
            }
        }
    }


}