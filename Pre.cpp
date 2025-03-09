#include <iostream>
#include <limits.h>

using namespace std;

// Structure to represent a process
struct Process {
    int id, arrivalTime, burstTime, remainingTime, completionTime, waitingTime, turnaroundTime;
};

// Function to find the process with the shortest remaining time
int findShortestJob(Process processes[], int n, int currentTime) {
    int shortestIndex = -1;
    int minRemainingTime = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 &&
            processes[i].remainingTime < minRemainingTime) {
            minRemainingTime = processes[i].remainingTime;
            shortestIndex = i;
        }
    }
    return shortestIndex;
}

// Function to implement Preemptive SJF (SRTF)
void sjf_preemptive(Process processes[], int n) {
    int completed = 0, currentTime = 0;
    
    while (completed < n) {
        int shortestIndex = findShortestJob(processes, n, currentTime);

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        processes[shortestIndex].remainingTime--;
        currentTime++;

        if (processes[shortestIndex].remainingTime == 0) {
            completed++;
            processes[shortestIndex].completionTime = currentTime;
            processes[shortestIndex].turnaroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
            processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;
        }
    }
}

// Function to display process details
void displayProcesses(Process processes[], int n) {
    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].waitingTime << "\t"
             << processes[i].turnaroundTime << "\t\t"
             << processes[i].completionTime << "\n";
    }
}

// Main function
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        processes[i].id = i + 1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    // Execute Preemptive SJF Scheduling
    sjf_preemptive(processes, n);

    // Display process details
    displayProcesses(processes, n);

    return 0;
}
