#include<bits/stdc++.h>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    Process(int pid, int arrivalTime, int burstTime, int priority)
        : pid(pid), arrivalTime(arrivalTime), burstTime(burstTime), priority(priority),
          completionTime(0), turnaroundTime(0), waitingTime(0) {}
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool comparePriority(const Process& a, const Process& b) {
    return a.priority > b.priority;
}

void priorityScheduling(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        int minPriority = INT_MAX;
        int selectedProcess = -1;

        for (int j = i; j < n && processes[j].arrivalTime <= currentTime; ++j) {
            if (processes[j].priority < minPriority && processes[j].completionTime == 0) {
                minPriority = processes[j].priority;
                selectedProcess = j;
            }
        }

        if (selectedProcess != -1) {
            processes[selectedProcess].completionTime = currentTime + processes[selectedProcess].burstTime;
            processes[selectedProcess].turnaroundTime = processes[selectedProcess].completionTime - processes[selectedProcess].arrivalTime;
            processes[selectedProcess].waitingTime = processes[selectedProcess].turnaroundTime - processes[selectedProcess].burstTime;

            currentTime = processes[selectedProcess].completionTime;
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (const auto& process : processes) {
        totalTurnaroundTime += process.turnaroundTime;
        totalWaitingTime += process.waitingTime;

        cout << process.pid << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
             << process.priority << "\t\t" << process.completionTime << "\t\t"
             << process.turnaroundTime << "\t\t" << process.waitingTime << endl;
    }

    cout << "\nAverage Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    cout << "Enter arrival time, burst time, and priority for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        int arrival, burst, priority;
        cout << "Process " << i + 1 << ": ";
        cin >> arrival >> burst >> priority;
        processes.push_back(Process(i + 1, arrival, burst, priority));
    }

    priorityScheduling(processes);

    return 0;
}
