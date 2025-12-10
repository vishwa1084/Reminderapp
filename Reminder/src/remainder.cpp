#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <thread>
using namespace std;
struct Notification{
    int day;
    int month;
    int year;
    int hour;
    int minute;
};
class Reminder{
    string task;
    int day;
    int month;
    int year;
    bool status;
    string description;
    string subTime;
    string entrytime;
    int notifcount;
    vector<Notification> notif;
    

    
public:
    Reminder(string task="bullshit assesment",int day=1,int month=1,int year=2025,bool stat=false,string desc="bs"){
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
        cout<<"Enter the day of the month 01-31";
        cin>>day;
        cout<<"Enter the month 01-12";
        cin>>month;
        cout<<"Enter the year YYYY";
        cin>>year;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"additional info about the task";
        getline(cin,description);
        cout<<"enter the time of submission";
        cin>>subTime;
        auto now=std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        entrytime=std::ctime(&currentTime);
        cout<<"how many notifications do we need for this?";
        cin>>notifcount;
        notif.clear();
        for(int i=0;i<notifcount;i++){
            Notification n{};
            cout<<"Notification "<<i+1<<"date(dd mm yyyy)";
            cin>>n.day>>n.month>>n.year;
            cout<<"Notification "<<i+1<<"time(hh mm)";
            cin>>n.hour>>n.minute;
            notif.push_back(n);
        }
    }
    
     void Display(){
        cout<<"Task:";
        cout<<task;
        cout<<endl;
        cout<<"Time of entry :"<<entrytime<<endl;
        cout<<"Time of submission: "<<day<<"-"<<month<<"-"<<year<<endl;
        cout<<"description:";
        cout<<description<<endl;
        cout<<"status:"<<status<<endl;
    }
    void task_status_update(){
        
        status=true;
    }
    void sendNotification() const{
        char buffer[11];
        std::snprintf(buffer, sizeof(buffer), "%02d-%02d-%04d", day, month, year);

       
        std::string command =
            "notify-send \"Reminder\" \"Task: " + task +
            " is due on " + std::string(buffer) +
            " at " + subTime + "\"";

        std::system(command.c_str());
    }

    static std::chrono::system_clock::time_point makeTpoint(int d,int m,int y,int hh,int mm){
        std::tm tm{};
        tm.tm_mday=d;
        tm.tm_mon=m-1;
        tm.tm_year=y-1900;
        tm.tm_min=mm;
        tm.tm_hour=hh;
        std::time_t tt=std::mktime(&tm);
        return std::chrono::system_clock::from_time_t(tt);
    }
    void schedulingNotif()const{
        using namespace std::chrono;
        if(status) return;
        auto now=system_clock::now();
        for(const auto& n : notif){
            auto when=makeTpoint(n.day,n.month,n.year,n.hour,n.minute);
            if(when<=now){
                continue;
            }
            Reminder copy =*this;
            std::thread([copy,when](){
                std::this_thread::sleep_until(when);
                
                copy.sendNotification();
            }).detach();
        }

    }
};
int main() {
    vector<Reminder> r;

    while (true) {
        int choice;
        cout << "1. Push new tasks\n";
        cout << "2. Display\n";
        cout << "3. Update status\n";
        cout << "4. Schedule all notifications\n";
        cout << "5. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            int n;
            cout << "How many tasks do u wanna add? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                Reminder temp;
                temp.getData();
                r.push_back(temp);
            }
            break;
        }
        case 2: {
            for (int i = 0; i < (int)r.size(); i++) {
                cout << "---- Task " << i + 1 << " ----\n";
                r[i].Display();
            }
            break;
        }
        case 3: {
            int task_no;
            cout << "enter the task u wanna change status for: ";
            cin >> task_no;
            if (task_no >= 1 && task_no <= (int)r.size())
                r[task_no - 1].task_status_update();
            else
                cout << "Invalid task number\n";
            break;
        }
        case 4: {
            for (const auto& rem : r) {
                rem.schedulingNotif();
            }
            cout << "Notifications scheduled. Keep the program running.\n";
            break;
        }
        case 5:
            return 0;
        }
    }
}
