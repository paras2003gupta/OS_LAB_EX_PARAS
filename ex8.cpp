#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int P = 5; // Number of processes
const int R = 3; // Number of resources

bool isSafe(int available[], int max[][R], int allocated[][R], int need[][R], int processSequence[]) {
    bool finish[P] = {false};

    int work[R];
    for (int i = 0; i < R; ++i) {
        work[i] = available[i];
    }

    int completed = 0;
    while (completed < P) {
        bool found = false;
        for (int i = 0; i < P; ++i) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; ++j) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == R) {
                    for (int k = 0; k < R; ++k) {
                        work[k] += allocated[i][k];
                    }

                    processSequence[completed++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is not in safe state." << endl;
            return false;
        }
    }

    cout << "System is in safe state." << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < P; ++i) {
        cout << processSequence[i] << " ";
    }
    cout << endl;

    return true;
}

int main() {
    int available[R] = {3, 3, 2}; // Available instances of each resource
    int max[P][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int allocated[P][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int need[P][R];

    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < R; ++j) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    int processSequence[P];
    isSafe(available, max, allocated, need, processSequence);

    return 0;
}
