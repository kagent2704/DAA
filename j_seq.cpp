#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    char id;
    int deadline, profit;
};

bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

void jobSequencing(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), cmp);
    int n = jobs.size();
    vector<char> result(n, '-');
    vector<bool> slot(n, false);

    for (Job& job : jobs) {
        for (int j = min(n, job.deadline) - 1; j >= 0; --j) {
            if (!slot[j]) {
                slot[j] = true;
                result[j] = job.id;
                break;
            }
        }
    }

    cout << "Job order for max profit: ";
    for (char c : result)
        if (c != '-') cout << c << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;
    vector<Job> jobs(n);
    cout << "Enter job id, deadline and profit:\n";
    for (int i = 0; i < n; ++i)
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;

    jobSequencing(jobs);
    return 0;
}
