#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<thread>
#include<sstream>
using namespace std;
class User
{
    protected:
            string name,pass;
    public:
            User()
            {
                name="null";
                pass="null";
            }
            User(string nam,string p)
            {
                name=nam;
                pass=p;
            }
            User(const User &u1)
            {
                name=u1.name;
                pass=u1.pass;
            }
            User& operator=(const User &u1)
            {
                name=u1.name;
                pass=u1.pass;
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
};
istream& operator>>(istream &is,User &u1)
{
    cout<<"enter the user name= ";
    is>>u1.name;
    cout<<"enter the password= ";
    is>>u1.pass;
    return is;
}
ostream& operator<<(ostream& os,User &u1)
{
    os<<"\n"<<u1.name<<","<<u1.pass;
    return os;
}
int main()
{
    string user,key;
    User user1;
    cout<<"starting the engine...\n";
    for(int i=0;i<3;i++)
    {
    cout<<"\rstart's in "<<i+1<<flush;
    this_thread::sleep_for(chrono::seconds(1));
    }
    int ch;
    while(true)
    {
    cout<<"\n1) to register a new user"<<endl;
    cout<<"2) login"<<endl;
    cout<<"enter your choice= ";
    cin>>ch;
    string line;
    switch(ch)
    {
        case 1:
        {
            cin>>user1;
            int found=1;
            fstream file1("user.txt",ios::in);
            while(getline(file1,line))
            {
                stringstream str(line);
                getline(str,user,',');
                getline(str,key,',');
                if(user1.validate(user,key))
                {
                    cout<<"user already excist"<<endl;
                    found=0;
                    break;
                }
            }
            file1.close();
            if(found)
            {
                fstream file("user.txt",ios::app);
                file<<user1;
                cout<<"\nuser is being added...\n"<<endl;
                for(int i=0;i<3;i++)
                {
                cout<<"\rtake's few seconds "<<i+1<<flush;
                this_thread::sleep_for(chrono::seconds(1));
                }
                return 1;//returning 1 to for adding new user
            }
        }
        case 2:
        {
            cin>>user1;
            fstream file1("user.txt",ios::in);
            while(getline(file1,line))
            {
                stringstream str(line);
                getline(str,user,',');
                getline(str,key,',');
                if(user1.validate(user,key))
                {
                    break;
                }
            }
            file1.close();
            return 2;//returniing 2 for suceesfully addeing the user
        }//closing case2
    }//closing switch
    }//closing while
}//closing main