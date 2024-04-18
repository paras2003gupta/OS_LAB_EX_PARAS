#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time of the process
};

void calculateWaitingTime(vector<Process>& processes, vector<int>& waitingTime) {
    int n = processes.size();
    
    waitingTime[0] = 0; // First process will have 0 waiting time
    
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(vector<Process>& processes, vector<int>& waitingTime, vector<int>& turnaroundTime) {
    int n = processes.size();
    
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

void calculateAverageTime(vector<Process>& processes) {
    int n = processes.size();
    vector<int> waitingTime(n, 0), turnaroundTime(n, 0);
    
    calculateWaitingTime(processes, waitingTime);
    calculateTurnaroundTime(processes, waitingTime, turnaroundTime);
    
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        
        cout << processes[i].pid << "\t\t"
             << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t"
             << waitingTime[i] << "\t\t"
             << turnaroundTime[i] << "\n";
    }
    
    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    cout << "Enter arrival time and burst time for each process:\n";
    
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        processes[i].pid = i + 1;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }
    
    calculateAverageTime(processes);
    
    return 0;
}
