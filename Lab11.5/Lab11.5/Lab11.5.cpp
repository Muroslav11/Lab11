#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

struct Faculty {
    char name[61];
    char specialities[200];
    double entrance_grade;
};

struct Institute {
    char name[61];
    int admission_plan;
    Faculty fac;
};

int getValidInt(string prompt) {
    int tmp;
    while (true) {
        cout << prompt;
        if (cin >> tmp) {
            cin.ignore(10000, '\n');
            return tmp;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: enter a valid integer." << endl;
    }
}

void Create(char* fname) {
    ofstream f(fname, ios::binary);
    if (!f) return;
    Institute inst;
    char ch;
    do {
        cout << "Institute name: "; cin.getline(inst.name, 61);
        inst.admission_plan = getValidInt("Admission plan: ");
        cout << "Faculty name: "; cin.getline(inst.fac.name, 61);
        cout << "Specialities: "; cin.getline(inst.fac.specialities, 200);
        cout << "Entrance grade: "; cin >> inst.fac.entrance_grade;
        cin.ignore(10000, '\n');
        f.write((char*)&inst, sizeof(Institute));
        cout << "Continue? (y/n): "; cin >> ch;
        cin.ignore(10000, '\n');
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

void Print(char* fname) {
    ifstream f(fname, ios::binary);
    if (!f) return;
    Institute inst;
    int i = 1;
    cout << "\n--------------------------------------------------------------------------------------------------------" << endl;
    cout << "| #  | Institute      | Plan | Faculty                | Grade | Specialities                           |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    while (f.read((char*)&inst, sizeof(Institute))) {
        cout << "| " << setw(2) << left << i++
            << " | " << setw(14) << left << inst.name
            << " | " << setw(4) << right << inst.admission_plan
            << " | " << setw(22) << left << inst.fac.name
            << " | " << setw(5) << fixed << setprecision(1) << inst.fac.entrance_grade
            << " | " << setw(38) << left << inst.fac.specialities << " |" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    f.close();
}

void Add(char* fname) {
    ofstream f(fname, ios::binary | ios::app);
    if (!f) return;
    Institute inst;
    cout << "Institute name: "; cin.getline(inst.name, 61);
    inst.admission_plan = getValidInt("Admission plan: ");
    cout << "Faculty name: "; cin.getline(inst.fac.name, 61);
    cout << "Specialities: "; cin.getline(inst.fac.specialities, 200);
    cout << "Entrance grade: "; cin >> inst.fac.entrance_grade;
    cin.ignore(10000, '\n');
    f.write((char*)&inst, sizeof(Institute));
    f.close();
}

void Change(char* fname, int n) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f) return;
    Institute inst;
    f.seekp((n - 1) * sizeof(Institute)); 
    cout << "New Institute name: "; cin.getline(inst.name, 61);
    inst.admission_plan = getValidInt("New Admission plan: ");
    cout << "New Faculty name: "; cin.getline(inst.fac.name, 61);
    cout << "New Specialities: "; cin.getline(inst.fac.specialities, 200);
    cout << "New Entrance grade: "; cin >> inst.fac.entrance_grade;
    cin.ignore(10000, '\n');
    f.write((char*)&inst, sizeof(Institute));
    f.close();
}

void Remove(char* fname, int n) {
    ifstream f(fname, ios::binary);
    if (!f) return;
    ofstream t("TMP.DAT", ios::binary);
    Institute inst;
    int i = 1;
    bool found = false;
    while (f.read((char*)&inst, sizeof(Institute))) {
        if (i != n) {
            t.write((char*)&inst, sizeof(Institute));
        }
        else {
            found = true;
        }
        i++;
    }
    f.close();
    t.close();
    remove(fname);
    rename("TMP.DAT", fname);
    if (found) cout << "Record #" << n << " removed." << endl;
    else cout << "Record not found." << endl;
}

void Sort(char* fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f) return;
    f.seekg(0, ios::end);
    int size = (int)f.tellg() / sizeof(Institute);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Institute inst1, inst2;
            f.seekg(j * sizeof(Institute));
            f.read((char*)&inst1, sizeof(Institute));
            f.read((char*)&inst2, sizeof(Institute));
            if (inst1.fac.entrance_grade < inst2.fac.entrance_grade ||
                (inst1.fac.entrance_grade == inst2.fac.entrance_grade && inst1.admission_plan < inst2.admission_plan)) {
                f.seekp(j * sizeof(Institute));
                f.write((char*)&inst2, sizeof(Institute));
                f.write((char*)&inst1, sizeof(Institute));
            }
        }
    }
    f.close();
    cout << "Sorted." << endl;
}

void SearchByGrade(char* fname, double g) {
    ifstream f(fname, ios::binary);
    Institute inst;
    bool found = false;
    while (f.read((char*)&inst, sizeof(Institute))) {
        if (abs(inst.fac.entrance_grade - g) < 0.1) {
            cout << "Faculty: " << inst.fac.name << ", Spec: " << inst.fac.specialities << endl;
            found = true;
        }
    }
    if (!found) cout << "Not found." << endl;
    f.close();
}

void SearchInstitute(char* fname, double g) {
    ifstream f(fname, ios::binary);
    Institute inst;
    bool found = false;
    while (f.read((char*)&inst, sizeof(Institute))) {
        if (abs(inst.fac.entrance_grade - g) < 0.1) {
            cout << "Institute: " << inst.name << " (Plan: " << inst.admission_plan << ")" << endl;
            found = true;
        }
    }
    if (!found) cout << "Not found." << endl;
    f.close();
}

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    char fname[100];
    cout << "Enter file name: "; cin.getline(fname, 100);
    int choice;
    do {
        cout << "\n1. Create 2. Print 3. Add 4. Change 5. Remove 6. Sort 7. Spec by Grade 8. Inst by Avg 0. Exit" << endl;
        choice = getValidInt("Choice: ");
        switch (choice) {
        case 1: Create(fname); break;
        case 2: Print(fname); break;
        case 3: Add(fname); break;
        case 4: Change(fname, getValidInt("Record # to change: ")); break;
        case 5: Remove(fname, getValidInt("Record # to remove: ")); break;
        case 6: Sort(fname); break;
        case 7: { double g; cout << "Grade: "; cin >> g; cin.ignore(); SearchByGrade(fname, g); break; }
        case 8: { double g; cout << "Avg Grade: "; cin >> g; cin.ignore(); SearchInstitute(fname, g); break; }
        }
    } while (choice != 0);
    return 0;
}