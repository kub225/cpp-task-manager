#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
using namespace std;

class Task{
protected:
    int id;
    string title;
    bool completed;
public:
    Task(int i, string t, bool c=false):id(i), title(t), completed(c){
        cout<<"created"<<endl;
    }

    virtual void display() const = 0;

    virtual string serialize() const = 0;

    int getId()const{
        return id;
    }
    string getTitle()const{
        return title;
    }
    bool isCompleted()const{
        return completed;
    }
    void markCompleted(){
        completed = true;
    }

    virtual ~Task() = default;
};

class SimpleTask: public Task{
public:
    SimpleTask(int i, string t, bool c=false):Task(i,t,c){
        cout<<"completed"<<endl;
    }
    void display()const override{
        cout<<"|"<<(completed ? " X " : " ")<<"| "<<id<<" . "<<title<<" (easy)"<<endl;

    }
    string serialize() const override{
        return "SIMPLE |"+to_string(id)+" | "+title+" | "+(completed ? "1" : "0");
    }

    ~SimpleTask(){}

};

class DeadlineTask:public Task{
private:
    string deadline;

public:
    DeadlineTask(int i, string t,string d, bool c =false):Task(i,t,c), deadline(d){
        cout<<"completed"<<endl;
    }
    void display() const override{
        cout<<"|"<<(completed ? " X " : " ")<<"| "<<id<<" . "<<title<<" Deadline: "<<deadline<<"|"<<endl;
    }
    string serialize()const override{
        return "DEADLINE |"+to_string(id)+" | "+title+" | "+deadline+" | "+(completed ? "1" : "0");
    }
    string getDeadline() const{
        return deadline;
    }
};

class TaskManager{
private:
    vector<unique_ptr<Task>> tasks;
public:
    TaskManager() = default;

    void addTask(unique_ptr<Task> task){
        tasks.push_back(move(task));
    }

    void saveToFile(const string& filename)const{
        ofstream file(filename);
        if(file.is_open()){
            for(const auto& task : tasks){
                file<<task->serialize()<<"\n";
            }
        }
    }

    void markTaskDone(int id){
        for(auto& task : tasks){
            if(task->getId()==id){
                task->markCompleted();
                cout<<"Task # "<<id<<" marked as completed."<<endl;
                return;
            }
        }
        cout<<"Task with ID"<<id<<"was not found."<<endl;

    }

    void displayAll()const{
        if(tasks.empty()){
            cout<<"Tasks list is empty."<<endl;
            return;
        }
        for(const auto& task : tasks){
            task->display();
        }
    }
    ~TaskManager() =default;
};



int main(){
    TaskManager manager;

    manager.addTask(make_unique<SimpleTask>(1,"TASK1"));
    manager.addTask(make_unique<DeadlineTask>(2, "TASK2","tomorrow"));
    manager.displayAll();
    manager.markTaskDone(2);
    manager.displayAll();
    manager.saveToFile("filename.txt");
    return 0;
}
