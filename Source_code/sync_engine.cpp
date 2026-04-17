#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iomanip>
using namespace std;
int main(int argc,char* argv[])
{
    if (argc < 3)
    {
        cout << "Error: No command provided\n";
        return 1;
    }
    string cmd = argv[1];
    if(cmd=="C_NAME")
    {
        string symbol,c_name,o_name;
        c_name=argv[3];
        o_name=argv[4];
        string line;
        //changing the user file 
        fstream f1("user.txt",ios::in);
        fstream f2("temp.txt",ios::out);
        while(getline(f1,line))
        {   string name,key,type;
            stringstream str(line);
            getline(str,name,',');
            getline(str,key,',');
            getline(str,type,',');
            if(name==o_name)
            {
                f2<<c_name<<","<<key<<","<<type<<endl;
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
        remove("user.txt");
        rename("temp.txt","user.txt");
    }

    else if(cmd=="C_SYM")
    {
        string symbol,new_sym,o_sym;
        new_sym=argv[2];
        o_sym=argv[3];
        string line;

        //changing the trascation file 
        fstream f1("transaction.txt",ios::in);
        fstream f2("temp.txt",ios::out);
        while(getline(f1,line))
        {   string sym,user,type,quat,last_price;
            stringstream str(line);
            getline(str,sym,'|');
            getline(str,user,'|');
            getline(str,type,'|');
            getline(str,quat,'|');
            getline(str,last_price,'|');
            if(sym==o_sym)
            {
                f2<<new_sym<<"|"<<user<<"|"<<type<<"|"<<quat<<"|"<<last_price<<endl;
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
        remove("transaction.txt");
        rename("temp.txt","transaction.txt");
    }
    else if(cmd=="BUY")
    {
        string line,c_sym;
        float b_price,worth;
        int shares;
        fstream tr("transaction.txt",ios::app);
        tr<<argv[2]<<"|"<<argv[3]<<"|"<<cmd<<"|"<<argv[4]<<"|"<<fixed<<setprecision(2)<<stof(argv[5])<<endl;
        tr.flush();
        tr.close();
        fstream f1("company_list.txt",ios::in);
        fstream f2("temp.txt",ios::out);
        while(getline(f1,line))
        {
            stringstream str(line);
            getline(str,c_sym,'|');
            if(c_sym==argv[2])
            {
                string net,share,ipo,c_name;
                getline(str,net,'|');
                getline(str,share,'|');
                getline(str,ipo,'|');
                getline(str,c_name,'|');
                shares=stoi(argv[4]);
                b_price=stof(argv[5]);
                worth=stof(net);
                f2<<c_sym<<"|"<<fixed<<setprecision(2)<<(worth+(shares*b_price))<<"|"<<(stoi(share)-shares)<<"|"<<ipo<<"|"<<c_name<<endl;
                f2.flush();
            }
            else
            {
                f2<<line<<endl;
            }
        }
        f1.close();
        f2.close();
        remove("company_list.txt");
        rename("temp.txt","company_list.txt");
    }
    else if(cmd=="SELL")
    {
        string line,c_sym;
        float b_price,worth;
        int shares;
        fstream tr("transaction.txt",ios::app);
        tr<<argv[2]<<"|"<<argv[3]<<"|"<<cmd<<"|"<<argv[4]<<"|"<<fixed<<setprecision(2)<<stof(argv[5])<<endl;
        tr.flush();
        tr.close();
        fstream f1("company_list.txt",ios::in);
        fstream f2("temp.txt",ios::out);
        while(getline(f1,line))
        {
            stringstream str(line);
            getline(str,c_sym,'|');
            if(c_sym==argv[2])
            {
                string net,share,ipo,c_name;
                getline(str,net,'|');
                getline(str,share,'|');
                getline(str,ipo,'|');
                getline(str,c_name,'|');
                shares=stoi(argv[4]);
                b_price=stof(argv[5]);
                worth=stof(net);
                f2<<c_sym<<"|"<<fixed<<setprecision(2)<<(worth-(shares*b_price))<<"|"<<(stoi(share)+shares)<<"|"<<ipo<<"|"<<c_name<<endl;
                f2.flush();
            }
            else
            {
                f2<<line<<endl;
            }
        }
        f1.close();
        f2.close();
        remove("company_list.txt");
        rename("temp.txt","company_list.txt");
    }
}
