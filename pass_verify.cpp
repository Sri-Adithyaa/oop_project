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
int main()
{
    string user,key;
    User user1;
    cout<<"starting he engine...";
    for(int i=0;i<3;i++)
    {
    cout<<"\rstart's in "<<i+1<<flush;
    this_thread::sleep_for(chrono::seconds(1));
    }
    int ch;
    l1:cout<<"1) to register a new user"<<endl;
    cout<<"2) login"<<endl;
    cout<<"enter your choice= ";
    cin>>ch;
    string line;
    switch(ch)
    {
        case 1:
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
                    cout<<"user already excist"<<endl;
                    goto l1;
                }
            }
            file1.close();
            fstream file("user.txt",ios::app);
            file<<"\n"<<user<<','<<key<<endl;
            cout<<"user is being added..."<<endl;
            for(int i=0;i<3;i++)
            {
            cout<<"\rtake's few seconds "<<i+1<<flush;
            this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }

    


}