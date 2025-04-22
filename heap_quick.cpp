#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Record {
    string name;
    string mobile_number;
    float bill_amt;
};

vector<Record> records;

void accept(int n) {
    for (int i = 0; i < n; ++i) {
        Record r;
        cout << "Enter name: ";
        cin >> ws;
        getline(cin, r.name);
        cout << "Enter mobile number: ";
        cin >> r.mobile_number;
        cout << "Enter bill amount: ";
        cin >> r.bill_amt;
        records.push_back(r);
    }
}

void display(const vector<Record>& d) {
    cout << "+----------------+----------------------+-------------+" << endl;
    cout << "| Mobile Number  | Name                 | Bill Amount |" << endl;
    cout << "+----------------+----------------------+-------------+" << endl;
    for (const auto& r : d) {
        cout << "| " << setw(14) << left << r.mobile_number
             << "| " << setw(22) << left << r.name
             << "| " << setw(11) << right << fixed << setprecision(2) << r.bill_amt << " |" << endl;
    }
    cout << "+----------------+----------------------+-------------+" << endl;
}

void heapify(vector<Record>& d, int n, int i, const string& key) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    auto compare = [&](int a, int b) {
        if (key == "bill_amt")
            return d[a].bill_amt > d[b].bill_amt;
        else
            return d[a].mobile_number > d[b].mobile_number;
    };

    if (l < n && compare(l, largest)) largest = l;
    if (r < n && compare(r, largest)) largest = r;

    if (largest != i) {
        swap(d[i], d[largest]);
        heapify(d, n, largest, key);
    }
}

void heapSort(vector<Record>& d, const string& key) {
    int n = d.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(d, n, i, key);

    for (int i = n - 1; i >= 1; i--) {
        swap(d[0], d[i]);
        heapify(d, i, 0, key);
    }
}

int linearSearch(const vector<Record>& d, const string& key, const string& value) {
    for (size_t i = 0; i < d.size(); ++i) {
        if ((key == "mobile_number" && d[i].mobile_number == value)) {
            cout << "Record found at index: " << i << endl;
            return i;
        }
    }
    cout << "Record not found" << endl;
    return -1;
}

int binarySearch(const vector<Record>& d, const string& key, const string& value) {
    int low = 0, high = d.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (d[mid].mobile_number == value)
            return mid;
        else if (d[mid].mobile_number < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int binarySearchRecursive(const vector<Record>& d, const string& value, int low, int high) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (d[mid].mobile_number == value)
        return mid;
    else if (d[mid].mobile_number < value)
        return binarySearchRecursive(d, value, mid + 1, high);
    else
        return binarySearchRecursive(d, value, low, mid - 1);
}

int partition(vector<Record>& d, int low, int high, const string& key) {
    Record pivot = d[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool condition = (key == "mobile_number") ?
            d[j].mobile_number <= pivot.mobile_number :
            d[j].bill_amt <= pivot.bill_amt;

        if (condition) {
            ++i;
            swap(d[i], d[j]);
        }
    }
    swap(d[i + 1], d[high]);
    return i + 1;
}

void quickSort(vector<Record>& d, int low, int high, const string& key) {
    if (low < high) {
        int pi = partition(d, low, high, key);
        quickSort(d, low, pi - 1, key);
        quickSort(d, pi + 1, high, key);
    }
}

int main() {
    int choice;
    int n;

    while (true) {
        cout << "\nWELCOME TO THE MENU DRIVEN PROGRAM\n"
             << "1. Accept Data\n2. Display Data\n3. Sort Data (Heap Sort)\n"
             << "4. Linear Search\n5. Binary Search (Non-recursive)\n"
             << "6. Binary Search (Recursive)\n7. Quick Sort\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter number of records: ";
            cin >> n;
            accept(n);
            cout << "Data accepted successfully.\n";
        } else if (choice == 2) {
            display(records);
        } else if (choice == 3) {
            heapSort(records, "bill_amt");
            cout << "Data sorted using Heap Sort (by bill amount):\n";
            display(records);
        } else if (choice == 4) {
            string mobile;
            cout << "Enter mobile number to search: ";
            cin >> mobile;
            linearSearch(records, "mobile_number", mobile);
        } else if (choice == 5) {
            heapSort(records, "mobile_number"); // Ensure sorted for binary search
            string mobile;
            cout << "Enter mobile number to search: ";
            cin >> mobile;
            int index = binarySearch(records, "mobile_number", mobile);
            if (index != -1)
                cout << "Record found at index: " << index << endl;
            else
                cout << "Record not found\n";
        } else if (choice == 6) {
            heapSort(records, "mobile_number");
            string mobile;
            cout << "Enter mobile number to search: ";
            cin >> mobile;
            int index = binarySearchRecursive(records, mobile, 0, records.size() - 1);
            if (index != -1)
                cout << "Record found at index: " << index << endl;
            else
                cout << "Record not found\n";
        } else if (choice == 7) {
            quickSort(records, 0, records.size() - 1, "mobile_number");
            cout << "Data sorted using Quick Sort:\n";
            display(records);
        } else if (choice == 8) {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
