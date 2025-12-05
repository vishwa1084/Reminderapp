#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <ctime>
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
        auto now=std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        entrytime=std::ctime(&currentTime);
    }
     void Display(){
        cout<<"Task:";
        cout<<task;
        cout<<endl;
        cout<<day<<"-"<<month<<"-"<<year<<endl;
        cout<<"description:";
        cout<<description<<endl;
        cout<<"Time of entry :"<<entrytime<<endl;
        cout<<"time of submission:";
        cout<<subTime;
    }
    void task_status_update(){
        
        status=true;
    }
    

    


};
int main(){
    vector<Reminder> r;
    while(true){
        int choice;
        cout<<"1.To push new tasks"<<endl;
        cout<<"2.display"<<endl;
        cout<<"3.update status"<<endl;
        cout<<"4.exit";
        cin>>choice;
        switch(choice){
            case 1:
                int n;
                cout<<"How many tasks do u wanna add?";
                cin>>n;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                for(int i=0;i<n;i++){
                    Reminder temp;
                    temp.getData();
                    r.push_back(temp);
                }
                break;
            case 2:
                for(int i=0;i<r.size();i++){
                    cout<<i+1<<".";
                    r[i].Display();
                }
                break;
            case 3:
                int task_no;
                cout<<"enter the task u wanna change status for";
                cin>>task_no; 
                r[task_no-1].task_status_update();
                break; 
            case 4:
                return 0;
                
            }
    }
    
    
    
    
}