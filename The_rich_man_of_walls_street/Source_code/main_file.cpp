#include <iostream>
#include<windows.h>
#include<string>
#include<chrono>
#include<thread>
#include<cstdlib>
using namespace std;
int main() {
    system("cls");
    cout<<"\033[32m";
    cout<<"\t\t\tWELCOME TO THE WALL'S STREET\033[33m";
    cout <<"\t\t"<<R"(
    ==================================================================                
                            WALL'S STREET
    ==================================================================
            )";
    cout<<"\033[0m"<<endl;
    for(int i=1;i<3;i++)
    {
        this_thread::sleep_for(chrono::seconds(1));
    }
    system("cls");
    int result;
    result=system("pass_verify.exe");
    if(result==1)
    {
        system("cls");
        cout<<"THANK YOU FOR REGISTERING YOUR COMPANY IN WALL'S STREET"<<endl;
        cout<<"A LEGACY STARTED HERE....";
    }
    else if(result==0)
    {
        system("cls");
        cout<<"THANK YOU FOR ENTERING INTO WALL'S STREET"<<endl;
        cout<<"HAVE A GREAT JOURNEY AHEAD....";
    }
    else if(result==3)
    {
        system("cls");
        cout<<"THANK YOU DEAR COMPANY , CONTINUE GROWING"<<endl;
        cout<<"RETURN TO WALL'S STREET AGAIN....";
    }
    else if(result==2)
    {
        system("cls");
        cout<<"THANK YOU DEAR USER ,GROW RICH "<<endl;
        cout<<"RETURN TO WALL'S STREET AGAIN....";
    }
    else
    {
        system("cls");
        char ch;
        cout<<"HAVE A GREAT JOURNEY IN WALL'S STREET"<<endl;
        cout<<"would you like try again (y/n): ";
        cin>>ch;
        if(ch=='y')
        {
            system("pass_verify.exe");
        }
    }
    for(int i=0;i<4;i++)
    {
        this_thread::sleep_for(chrono::seconds(1));
    }
}
