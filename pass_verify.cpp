#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<thread>
#include<sstream>
#include<cstdlib>
using namespace std;
enum Mode {LOGIN,REGISTER};
class User
{
    protected:
            string name,pass,user_type;
    public:
            Mode mode ;
            User()
            {
                name="null";
                pass="null";
                user_type="null";
            }
            User(string nam,string p,string typ)
            {
                name=nam;
                pass=p;
                user_type=typ;
            }
            User(const User &u1)
            {
                name=u1.name;
                pass=u1.pass;
                user_type=u1.user_type;
            }
            User& operator=(const User &u1)
            {
                name=u1.name;
                pass=u1.pass;
                user_type=u1.user_type;
                return *this;
            }
            friend istream& operator>>(istream &is,User &u1);
            friend ostream& operator<<(ostream &os,User &u1);
            bool validate(string user,string key)
            {
                if(name==user && pass == key)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            bool check_user(string user)
            {
                if(name==user)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            void get_name(string &s)
            {
                s=name;
            }
            void get_type(string &s)
            {
                s=user_type;
            }
};
istream& operator>>(istream &is,User &u1)
{
    cout<<"Enter the user name= ";
    is>>u1.name;
    cout<<"Enter the password= ";
    is>>u1.pass;
    if(u1.mode==REGISTER)
    {
        do
        {
            cout<<"Enter whether a company are a investor= ";
            is>>u1.user_type;
        }while(u1.user_type!="company" && u1.user_type!="investor");
    }
    return is;
}
ostream& operator<<(ostream& os,User &u1)
{
    os<<u1.name<<","<<u1.pass<<","<<u1.user_type;
    return os;
}
int main()
{
    string user,key,user_type;
    User user1;
    cout<<"starting the engine...\n";
    for(int i=0;i<3;i++)
    {
    cout<<"\rstart's in "<<i+1<<flush;
    this_thread::sleep_for(chrono::seconds(1));
    }
    system("cls");
    int ch;
    while(true)
    {
    cout<<"\n1) to register a new user"<<endl;
    cout<<"2) login"<<endl;
    cout<<"3)exit"<<endl;
    cout<<"enter your choice= ";
    cin>>ch;
    string line;
    switch(ch)
    {
        case 1:
        {
            string u_type;
            user1.mode=REGISTER;
            cin>>user1;
            int found=1;
            fstream file1("user.txt",ios::in);
            while(getline(file1,line))
            {
                stringstream str(line);
                getline(str,user,',');
                getline(str,key,',');
                if(user1.check_user(user))
                {
                    cout<<"\033[31muser already excist\033[0m"<<endl;
                    found=0;
                    break;
                }
            }
            file1.close();
            if(found)
            {
                fstream file("user.txt",ios::app);
                file<<user1<<endl;
                cout<<"\n\033[32muser is being added...\033[0m\n"<<endl;
                for(int i=0;i<3;i++)
                {
                cout<<"\rtake's few seconds "<<i+1<<flush;
                this_thread::sleep_for(chrono::seconds(1));
                }
                file.close();
                user1.get_type(u_type);
                if(u_type=="company")
                {
                    string cmd;
                    cmd="company.exe";
                    system(cmd.c_str());
                    return 1;
                }
                else if(u_type=="investor")
                {
                    string cmd,name;
                    user1.get_name(name);
                    cmd="user.exe "+name;
                    system(cmd.c_str());
                    return 0;
                }
                return 0;
            }
        }
        case 2:
        {
            string name;
            int found=0;
            string user_typ;
            user1.mode=LOGIN;
            cin>>user1;
            fstream file1("user.txt",ios::in);
            while(getline(file1,line))
            {
                stringstream str(line);
                getline(str,user,',');
                getline(str,key,',');
                getline(str,user_typ,',');
                if(user1.validate(user,key))
                {
                    found=1;
                    break;
                }
            }
            if(found)
            {
                cout<<"\033[32mLogin succesful\033[0m\n";
                cout<<"Hang tight...\nwe are getting into wall's street\n";
                for(int i=0;i<3;i++)
                {
                cout<<"\rtake's few seconds "<<i+1<<flush;
                this_thread::sleep_for(chrono::seconds(1));
                }
                cout<<endl;
                if(user_typ=="investor")
                {
                 cout << "\033[2J\033[1;1H";
                 user1.get_name(user);
                 cout<<"Logged in as "<<"\033[32m"<<user<<"\033[0m"<<endl;
                 file1.close();
                 user1.get_name(name);
                    string cmd;
                    cmd="user.exe "+name;
                    system(cmd.c_str());
                 return 2;//returning 2 for suceesfully login the company
                }
                else if(user_typ=="company")
                {
                    cout << "\033[2J\033[1;1H";
                    user1.get_name(user);
                    cout<<"Logged in as "<<"\033[32m"<<user<<"\033[0m"<<endl;
                    file1.close();
                    user1.get_name(name);
                    string cmd;
                    cmd="company.exe "+name;
                    system(cmd.c_str());
                    return 3;//returning 3 for sucessfully login the investor
                }
            }
            else
            {
                cout<<"\033[31muser name or password missmatched\033[0m\n";
                file1.close();
                return 4;//returniing 4 missmatched
            }
            file1.close();
        }//closing case2
        case 3:
        {
            return -1;
        }
    }//closing switch
    }//closing while
}//closing main