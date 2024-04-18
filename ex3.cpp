#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    bool completed;

    Process(int pid, int arrivalTime, int burstTime)
        : pid(pid), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime), completed(false) {}
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    cout << "Enter arrival time and burst time for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        int arrival, burst;
        cout << "Process " << i + 1 << ": ";
        cin >> arrival >> burst;
        processes.push_back(Process(i + 1, arrival, burst));
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;
    vector<int> completionTime(n, INT_MAX);

    while (completedProcesses < n) {
        int shortestRemainingTime = INT_MAX;
        int shortestIndex = -1;

        for (int i = 0; i < n; ++i) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestRemainingTime) {
                shortestRemainingTime = processes[i].remainingTime;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        processes[shortestIndex].remainingTime--;
        currentTime++;

        if (processes[shortestIndex].remainingTime == 0) {
            completionTime[shortestIndex] = currentTime;
            processes[shortestIndex].completed = true;
            completedProcesses++;
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; ++i) {
        int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        cout << processes[i].pid << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t"
             << completionTime[i] << "\t\t" << turnaroundTime << "\t\t" << waitingTime << endl;
    }

    cout << "\nAverage Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;

    return 0;
}
