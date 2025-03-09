#include <iostream>
#include <algorithm>

using namespace std;

// Structure to represent a process
struct Process {
    int id, arrivalTime, burstTime, waitingTime, turnaroundTime, completionTime;
};

// Function to compare processes based on burst time (if arrival times are the same)
bool compare(Process p1, Process p2) {
    if (p1.arrivalTime == p2.arrivalTime)
        return p1.burstTime < p2.burstTime; // If arrival times are equal, sort by burst time
    return p1.arrivalTime < p2.arrivalTime; // Otherwise, sort by arrival time
}

// Function to calculate waiting time and turnaround time
void calculateTimes(Process processes[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime; // Handle idle time
        
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        
        currentTime += processes[i].burstTime;
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
    }

    // Sort processes by arrival time, then by burst time
    sort(processes, processes + n, compare);

    // Calculate waiting and turnaround times
    calculateTimes(processes, n);

    // Display process details
    displayProcesses(processes, n);

    return 0;
}
