#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATIENTS 100
#define MAX_BEDS 20

struct Patient {
    char name[50];
    int age;
    int emergencyLevel;
    int priorityScore;
    int treatmentTime;
};

struct Patient heap[MAX_PATIENTS + 1];
int heapSize = 0;

struct Patient allPatients[MAX_PATIENTS];
int totalPatients = 0;

void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

void insertPatient(struct Patient p) {
    if (heapSize >= MAX_PATIENTS) {
        printf("[WARNING] Heap is full. Cannot admit more patients.\n");
        return;
    }
    heap[++heapSize] = p;
    int i = heapSize;
    while (i > 1 && heap[i].priorityScore > heap[i / 2].priorityScore) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

struct Patient extractMax() {
    struct Patient maxPatient = heap[1];
    heap[1] = heap[heapSize--];
    int i = 1;
    while (1) {
        int left = 2 * i;
        int right = 2 * i + 1;
        int largest = i;
        if (left <= heapSize && heap[left].priorityScore > heap[largest].priorityScore)
            largest = left;
        if (right <= heapSize && heap[right].priorityScore > heap[largest].priorityScore)
            largest = right;
        if (largest == i) break;
        swap(&heap[i], &heap[largest]);
        i = largest;
    }
    return maxPatient;
}

int determineEmergencyLevel() {
    int score = 0, ans;

    printf("\n  -- Triage Assessment --\n");

    printf("  1. Heavy bleeding?          (1=Yes, 0=No): ");
    if (scanf("%d", &ans) != 1) ans = 0;
    if (ans == 1) score += 3;

    printf("  2. Chest pain?              (1=Yes, 0=No): ");
    if (scanf("%d", &ans) != 1) ans = 0;
    if (ans == 1) score += 3;

    printf("  3. Difficulty breathing?    (1=Yes, 0=No): ");
    if (scanf("%d", &ans) != 1) ans = 0;
    if (ans == 1) score += 3;

    printf("  4. Unconscious / fainting?  (1=Yes, 0=No): ");
    if (scanf("%d", &ans) != 1) ans = 0;
    if (ans == 1) score += 4;

    printf("  5. Pain level (0-10): ");
    if (scanf("%d", &ans) != 1) ans = 0;
    if (ans >= 8) score += 3;
    else if (ans >= 5) score += 2;
    else if (ans >= 2) score += 1;

    if (score >= 12) return 5;
    if (score >= 9) return 4;
    if (score >= 6) return 3;
    if (score >= 3) return 2;
    return 1;
}

int calculatePriority(int emergency, int age) {
    int score = emergency * 10;
    if (age > 60) score += 5;
    if (age < 12) score += 3;
    return score;
}

int estimateTreatmentTime(int emergency) {
    switch (emergency) {
        case 5: return 5;
        case 4: return 4;
        case 3: return 3;
        case 2: return 2;
        default: return 1;
    }
}

void dpBedAllocator(struct Patient patients[], int n) {
    int dp[MAX_PATIENTS + 1][MAX_BEDS + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        int w = patients[i - 1].treatmentTime;
        int v = patients[i - 1].priorityScore;
        for (int cap = 0; cap <= MAX_BEDS; cap++) {
            dp[i][cap] = dp[i - 1][cap];
            if (cap >= w && dp[i - 1][cap - w] + v > dp[i][cap])
                dp[i][cap] = dp[i - 1][cap - w] + v;
        }
    }

    printf("\n===== DP BED ALLOCATION (Knapsack, capacity = %d bed-hours) =====\n", MAX_BEDS);
    printf("Maximum achievable priority score: %d\n\n", dp[n][MAX_BEDS]);

    printf("Recommended patients to admit (optimal subset):\n");
    printf("%-20s | Emergency | Age | Priority | Treatment Time\n", "Name");
    printf("------------------------------------------------------------------\n");

    int remaining = MAX_BEDS;
    int totalTime = 0;
    for (int i = n; i >= 1 && remaining > 0; i--) {
        if (dp[i][remaining] != dp[i - 1][remaining]) {
            printf("%-20s | %-9d | %-3d | %-8d | %d hr(s)\n",
                   patients[i - 1].name,
                   patients[i - 1].emergencyLevel,
                   patients[i - 1].age,
                   patients[i - 1].priorityScore,
                   patients[i - 1].treatmentTime);
            remaining -= patients[i - 1].treatmentTime;
            totalTime += patients[i - 1].treatmentTime;
        }
    }
    printf("------------------------------------------------------------------\n");
    printf("Total bed-hours used: %d / %d\n", totalTime, MAX_BEDS);
}

int main() {
    int n;

    printf("=============================================================\n");
    printf("       HOSPITAL EMERGENCY TRIAGE SYSTEM\n");
    printf("       Greedy (Max-Heap) + Dynamic Programming (Knapsack)\n");
    printf("=============================================================\n");

    printf("\nEnter number of patients: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PATIENTS) {
        printf("[ERROR] Invalid number of patients.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        struct Patient p;

        printf("\n----- Patient %d -----\n", i + 1);

        printf("  Name: ");
        if (scanf("%49s", p.name) != 1) {
            printf("[ERROR] Failed to read name.\n");
            return 1;
        }

        printf("  Age: ");
        if (scanf("%d", &p.age) != 1 || p.age < 0 || p.age > 130) {
            printf("[ERROR] Invalid age.\n");
            return 1;
        }

        printf("\n--- Triage assessment for %s ---\n", p.name);
        p.emergencyLevel = determineEmergencyLevel();
        p.priorityScore = calculatePriority(p.emergencyLevel, p.age);
        p.treatmentTime = estimateTreatmentTime(p.emergencyLevel);

        printf("  => Emergency Level : %d\n", p.emergencyLevel);
        printf("  => Priority Score  : %d\n", p.priorityScore);
        printf("  => Est. Treatment  : %d hr(s)\n", p.treatmentTime);

        allPatients[totalPatients++] = p;

        insertPatient(p);
    }

    printf("\n===== GREEDY TREATMENT ORDER (Highest Priority First) =====\n");
    printf("%-20s | Emergency | Age | Priority Score\n", "Name");
    printf("------------------------------------------------------------\n");
    while (heapSize > 0) {
        struct Patient p = extractMax();
        printf("%-20s | %-9d | %-3d | %d\n",
               p.name, p.emergencyLevel, p.age, p.priorityScore);
    }

    dpBedAllocator(allPatients, totalPatients);

    printf("\n=============================================================\n");
    printf("  Program complete. Stay safe!\n");
    printf("=============================================================\n");

    return 0;
}
