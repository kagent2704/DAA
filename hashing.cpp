#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class record {
public:
    int rollno;
    int marks;
    char name[20];

    record() {
        rollno = -1;
        marks = 0;
        strcpy(name, "");
    }

    friend class student;
};

class hashing {
    int rollno, pos;
public:
    hashing() {
        rollno = -1;
        pos = -1;
    }
    friend class student;
};

class student {
    record rec;
    hashing h[10];
    int s, relt;

public:
    student();
    void create_wr();   // With Replacement
    void create_wor();  // Without Replacement
    void modify();
    void retrieve();
    void display();
    void displayall();
};

student::student() {
    s = sizeof(record);
    relt = 0;
    for (int i = 0; i < 10; i++) {
        h[i].rollno = -1;
        h[i].pos = -1;
    }
}

void student::create_wr() {
    char ans;
    fstream f("student.txt", ios::binary | ios::app);
    if (!f) {
        cout << "File could not be opened!\n";
        return;
    }

    do {
        cout << "\nEnter Roll No: ";
        cin >> rec.rollno;
        cout << "Enter Name: ";
        string temp_name;
        cin >> temp_name;
        strncpy(rec.name, temp_name.c_str(), sizeof(rec.name) - 1);
        rec.name[sizeof(rec.name) - 1] = '\0';

        cout << "Enter Marks: ";
        cin >> rec.marks;

        int loc = rec.rollno % 10;

        if (h[loc].rollno == -1) {
            h[loc].rollno = rec.rollno;
            h[loc].pos = relt;
        } else {
            int existing_home = h[loc].rollno % 10;
            if (existing_home != loc) {
                hashing temp = h[loc];
                h[loc].rollno = rec.rollno;
                h[loc].pos = relt;

                int newloc = (loc + 1) % 10;
                bool placed = false;
                for (int i = 0; i < 9; i++) {
                    if (h[newloc].rollno == -1) {
                        h[newloc] = temp;
                        placed = true;
                        break;
                    }
                    newloc = (newloc + 1) % 10;
                }
                if (!placed) {
                    cout << "Hash table full. Displaced record cannot be placed!\n";
                    // Restore original hash
                    h[loc] = temp;
                }
            } else {
                int newloc = (loc + 1) % 10;
                bool placed = false;
                for (int i = 0; i < 9; i++) {
                    if (h[newloc].rollno == -1) {
                        h[newloc].rollno = rec.rollno;
                        h[newloc].pos = relt;
                        placed = true;
                        break;
                    }
                    newloc = (newloc + 1) % 10;
                }
                if (!placed) {
                    cout << "Hash table full. Cannot insert record.\n";
                }
            }
        }

        f.write((char *)&rec, s);
        relt++;

        displayall();
        cout << "Add another record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    f.close();
}

void student::create_wor() {
    char ans;
    fstream f("student.txt", ios::binary | ios::app);
    if (!f) {
        cout << "File could not be opened!\n";
        return;
    }

    do {
        cout << "\nEnter Roll No: ";
        cin >> rec.rollno;
        cout << "Enter Name: ";
        string temp_name;
        cin >> temp_name;
        strncpy(rec.name, temp_name.c_str(), sizeof(rec.name) - 1);
        rec.name[sizeof(rec.name) - 1] = '\0';

        cout << "Enter Marks: ";
        cin >> rec.marks;

        int loc = rec.rollno % 10;
        if (h[loc].rollno == -1) {
            h[loc].rollno = rec.rollno;
            h[loc].pos = relt;
        } else {
            int newloc = (loc + 1) % 10;
            bool placed = false;
            for (int i = 0; i < 9; i++) {
                if (h[newloc].rollno == -1) {
                    h[newloc].rollno = rec.rollno;
                    h[newloc].pos = relt;
                    placed = true;
                    break;
                }
                newloc = (newloc + 1) % 10;
            }
            if (!placed) {
                cout << "Hash table full. Cannot insert record.\n";
            }
        }

        f.write((char *)&rec, s);
        relt++;

        displayall();
        cout << "Add another record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    f.close();
}

void student::modify() {
    int roll;
    cout << "\nEnter Roll No. to modify: ";
    cin >> roll;

    for (int i = 0; i < 10; i++) {
        if (h[i].rollno == roll) {
            fstream f("student.txt", ios::binary | ios::in | ios::out);
            f.seekg(h[i].pos * s, ios::beg);
            f.read((char *)&rec, s);

            cout << "\nEnter new Name: ";
            string temp_name;
            cin >> temp_name;
            strncpy(rec.name, temp_name.c_str(), sizeof(rec.name) - 1);
            rec.name[sizeof(rec.name) - 1] = '\0';

            cout << "Enter new Marks: ";
            cin >> rec.marks;

            f.seekp(h[i].pos * s, ios::beg);
            f.write((char *)&rec, s);
            f.close();

            cout << "Record updated successfully!\n";
            return;
        }
    }

    cout << "Record not found!\n";
}

void student::retrieve() {
    int roll;
    cout << "\nEnter Roll No. to retrieve: ";
    cin >> roll;

    for (int i = 0; i < 10; i++) {
        if (h[i].rollno == roll) {
            fstream f("student.txt", ios::binary | ios::in);
            f.seekg(h[i].pos * s, ios::beg);
            f.read((char *)&rec, s);
            f.close();

            cout << "\nRoll No: " << rec.rollno << "\nName: " << rec.name << "\nMarks: " << rec.marks << "\n";
            return;
        }
    }

    cout << "Record not found!\n";
}

void student::display() {
    if (rec.rollno != -1)
        cout << rec.rollno << "\t" << rec.name << "\t" << rec.marks << "\n";
}

void student::displayall() {
    cout << "\nHash Table:\nIndex\tRoll No\tPosition\n";
    for (int i = 0; i < 10; i++) {
        cout << i << "\t" << h[i].rollno << "\t" << h[i].pos << "\n";
    }

    cout << "\nStored Records:\nRoll No\tName\tMarks\n";

    fstream f("student.txt", ios::binary | ios::in);
    record temp;
    int count = 0;
    while (f.read((char *)&temp, s)) {
        if (temp.rollno != -1) {
            cout << temp.rollno << "\t" << temp.name << "\t" << temp.marks << "\n";
            count++;
        }
    }

    if (count == 0) {
        cout << "No records found.\n";
    }

    f.close();
}

int main() {
    student st;
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert with Replacement\n";
        cout << "2. Insert without Replacement\n";
        cout << "3. Modify Record\n";
        cout << "4. Retrieve Record\n";
        cout << "5. Display All Records\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: st.create_wr(); break;
        case 2: st.create_wor(); break;
        case 3: st.modify(); break;
        case 4: st.retrieve(); break;
        case 5: st.displayall(); break;
        case 6: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
