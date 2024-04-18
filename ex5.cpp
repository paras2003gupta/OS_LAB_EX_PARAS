#include <bits/stdc++.h>


using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;

    Process(int pid, int arrivalTime, int burstTime)
        : pid(pid), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime) {}
};

void roundRobinScheduling(const vector<Process>& processes, int quantum) {
    queue<Process> readyQueue;
    vector<int> completionTime(processes.size(), -1);
    int currentTime = 0;
    int totalBurstTime = 0;

    for (const auto& process : processes) {
        totalBurstTime += process.burstTime;
    }

    while (!readyQueue.empty() || currentTime <= totalBurstTime) {
        for (const auto& process : processes) {
            if (process.arrivalTime <= currentTime && process.remainingTime > 0) {
                readyQueue.push(process);
            }
        }

        if (!readyQueue.empty()) {
            Process currentProcess = readyQueue.front();
            readyQueue.pop();

            int executeTime = min(quantum, currentProcess.remainingTime);
            currentTime += executeTime;
            currentProcess.remainingTime -= executeTime;

            if (currentProcess.remainingTime == 0) {
                completionTime[currentProcess.pid - 1] = currentTime;
            } else {
                readyQueue.push(currentProcess);
            }
        } else {
            currentTime++;
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (size_t i = 0; i < processes.size(); ++i) {
        int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        cout << processes[i].pid << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t"
             << completionTime[i] << "\t\t" << turnaroundTime << "\t\t" << waitingTime << endl;
    }

    cout << "\nAverage Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << endl;
    cout << "Average Waiting Time: " << (float)totalWaitingTime / processes.size() << endl;
}

int main() {
    int n, quantum;
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

    cout << "Enter time quantum: ";
    cin >> quantum;

    roundRobinScheduling(processes, quantum);

    return 0;
}
