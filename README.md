# Hospital-Management-System
Hospital Emergency Triage System
 Project Description

The Hospital Emergency Triage System is a C-based console application that simulates how hospitals manage emergency patients efficiently.

It prioritizes patients based on severity and allocates limited hospital resources using advanced algorithms.

This project combines Data Structures and Algorithms (DSA) with a real-world healthcare scenario.

 Objectives
Prioritize patients based on emergency severity
Ensure critical patients are treated first
Optimize usage of limited hospital resources (beds/time)
Demonstrate practical use of algorithms in real-world problems
 Technologies Used
Programming Language: C
Concepts:
Structures
Arrays
Heap (Priority Queue)
Dynamic Programming
 Algorithms Implemented
1. Greedy Algorithm (Max-Heap)
Used to determine treatment order
Patients are stored in a max-heap
The patient with the highest priority score is treated first
Key Operations:
Insert patient → Heapify Up
Extract patient → Heapify Down
Time Complexity:
Insertion: O(log n)
Deletion: O(log n)
2. Dynamic Programming (0-1 Knapsack)
Used for bed/resource allocation
Selects the optimal subset of patients
Maximizes total priority score within limited capacity
Knapsack Mapping:
Weight → Treatment Time
Value → Priority Score
Capacity → Available bed-hours
Time Complexity:
O(n × MAX_BEDS)
    Data Structure Used
struct Patient {
    char name[50];
    int age;
    int emergencyLevel;
    int priorityScore;
    int treatmentTime;
};
 Triage Assessment System

The system evaluates patients using a questionnaire:

Heavy bleeding
Chest pain
Difficulty breathing
Unconsciousness
Pain level (0–10)
Emergency Level Mapping:
Score	Emergency Level
≥12	5 (Critical)
9–11	4
6–8	3
3–5	2
<3	1 (Minor)
 Priority Calculation
Priority Score = Emergency Level × 10 + Age Bonus
Age Bonus:
Age > 60 → +5
Age < 12 → +3
 Treatment Time Estimation
Emergency Level	Time (hours)
5	5
4	4
3	3
2	2
1	1
 Program Workflow
Start program
Input number of patients
For each patient:
Enter name and age
Perform triage assessment
Calculate:
Emergency level
Priority score
Treatment time
Add to heap
Store for DP
Display treatment order using Greedy approach
Apply Dynamic Programming for bed allocation
Display optimal patient subset
End program
 How to Run
Compile:
gcc triage.c -o triage
Execute:
./triage
Sample Input
Enter number of patients: 2

Patient 1:
Name: Ravi
Age: 65
Symptoms:
1 1 0 0 8

Patient 2:
Name: Anu
Age: 25
Symptoms:
0 0 1 0 5
 Sample Output
Greedy Order:
Ravi  -> Highest priority
Anu   -> Lower priority
DP Allocation:
Selected patients maximizing total priority within bed limit
Configuration

You can modify system limits in code:

#define MAX_PATIENTS 100
#define MAX_BEDS 20
Increase MAX_BEDS → More capacity
Increase MAX_PATIENTS → More patients
Applications
Hospital emergency systems
ICU management
Disaster response systems
Healthcare simulations
Academic DSA projects
 Limitations
Console-based (no GUI)
Simplified medical logic
Static memory (fixed array size)
No real-time updates
 Future Enhancements
Web or mobile application
Database integration
AI-based diagnosis
Real-time monitoring system
Multi-resource allocation (ICU, ventilators)
 Conclusion

This project demonstrates how Greedy algorithms and Dynamic Programming can be combined to solve real-world problems like hospital triage and resource optimization effectively.
