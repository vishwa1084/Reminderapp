#include <iostream>
#include <vector>
#include <limits>
using namespace std;
class Reminder{


    string task;
    int day;
    int month;
    int year;
    bool status;
    string description;
    string subTime;
    string entrytime;
public:
    Reminder(string task="bullshit assesment",int day=0,int month=0,int year=2025,bool stat=false,string desc="bs"){
        this->task=task;
        this->day=day;
        this->month=month;
        this->year=year;
        this->status=stat;
        this->description=desc;
    }
    void getData(){
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"enter the name of the task";
        getline(cin,task);
        cout<<"enter the day of the month(day..1-31)";
        cin>>day;
        cout<<"enter the month(1-12)";
        cin>>month;
        cout<<"enter the year";
        cin>>year;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"additional info about the task";
        getline(cin,description);
        cout<<"enter the time of submission";
        cin>>subTime;
    }
     void Display(){
        cout<<"Task:";
        cout<<task;
        cout<<endl;
        cout<<day<<"-"<<month<<"-"<<year<<endl;
        cout<<"description:";
        cout<<description<<endl;

        cout<<"time of submission:";
        cout<<subTime;
    }
    

    


};
int main(){
    vector<Reminder> r;
    int n;
    cout<<"How many tasks do u wanna add?";
    cin>>n;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    for(int i=0;i<n;i++){
        Reminder temp;
        temp.getData();
        r.push_back(temp);
    }
    for(int i=0;i<r.size();i++){
        r[i].Display();
    }

    
}