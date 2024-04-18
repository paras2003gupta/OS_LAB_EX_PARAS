#include<iostream>
using namespace std;

struct Process{
int pid;
int arrivalTime;
int burstTime;
int completionTime;
int turnaroundTime;
int waitingTime;

};
void findSJF(Process pro[],int n){
    int remainingTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = pro[i].burstTime;;
    }
    int currentTime = 0;
    int complete = 0;
    int shortest = 0;
    int minBurst = 9999;
    while(complete<n){
        minBurst = 9999;
        for (int i = 0; i < n; i++)
        {
            if(pro[i].arrivalTime<=currentTime&&remainingTime[i]<minBurst&&remainingTime[i]>0){
                minBurst=remainingTime[i];
                shortest = i;
            }
        }
        remainingTime[shortest]--;
        if(remainingTime[shortest]==0){
            complete++;
            pro[shortest].completionTime=currentTime+1;
            pro[shortest].turnaroundTime=pro[shortest].completionTime-pro[shortest].arrivalTime;
            pro[shortest].waitingTime=pro[shortest].turnaroundTime-pro[shortest].burstTime;
        }
        currentTime++;
        
    }

}
void displayProcessDetails(Process pro[],int n){
    cout<<"Process\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\t"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<pro[i].pid<<"\t\t"<<pro[i].arrivalTime<<"\t\t"<<pro[i].burstTime<<"\t\t"<<pro[i].completionTime<<"\t\t"<<pro[i].turnaroundTime<<"\t\t "<<pro[i].waitingTime<<endl;
    }
    cout<<endl;
    
}
int main(){
    int n = 5;
    Process pro[5];
    cout<<"Enter process details(ID,ArrivalTime,BurstTime)"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"Enter Process "<<i+1<<endl;
        cin>>pro[i].pid>>pro[i].arrivalTime>>pro[i].burstTime;

    }
    findSJF(pro,n);
    displayProcessDetails(pro,n);
    

}
