#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Speciality { COMPUTER_SCIENCE, INFORMATICS, MATH_ECON, PHYS_INF, HANDICRAFT };
string specialityStr[] = { "Comp. Science", "Informatics", "Math & Econ", "Phys & Inf", "Handicraft" };

struct Student {
    char prizv[61];
    int kurs;
    Speciality speciality;
    int phys_grade;
    int math_grade;
    int inf_grade;
};

int getValidInt(string prompt, int minVal, int maxVal) {
    int tmp;
    while (true) {
        cout << prompt;
        if (cin >> tmp && tmp >= minVal && tmp <= maxVal)
            return tmp;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Range: " << minVal << "-" << maxVal << endl;
    }
}

double GetAvg(Student s) {
    return (s.phys_grade + s.math_grade + s.inf_grade) / 3.0;
}

void Create(const char* fname) {
    ofstream f(fname, ios::binary);
    if (!f) return;
    char ch;
    Student s;
    do {
        cout << "Surname: "; cin >> s.prizv;
        s.kurs = getValidInt("Course (1-6): ", 1, 6);
        s.speciality = (Speciality)getValidInt("Speciality (0-CS, 1-Inf, 2-ME, 3-PI, 4-Hand): ", 0, 4);
        s.phys_grade = getValidInt("Physics grade (2-5): ", 2, 5);
        s.math_grade = getValidInt("Math grade (2-5): ", 2, 5);
        s.inf_grade = getValidInt("Informatics grade (2-5): ", 2, 5);
        f.write((char*)&s, sizeof(Student));
        cout << "Continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

void Print(const char* fname) {
    ifstream f(fname, ios::binary);
    if (!f) return;
    Student s;
    int i = 1;
    cout << "\n==========================================================================================" << endl;
    cout << "| " << setw(3) << "#" << " | " << setw(15) << left << "Surname" << " | " << setw(6) << "Course" << " | " << setw(15) << "Speciality" << " | " << setw(4) << "Phys" << " | " << setw(4) << "Math" << " | " << setw(4) << "Inf" << " | " << setw(8) << "Avg" << " |" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    while (f.read((char*)&s, sizeof(Student))) {
        cout << "| " << setw(3) << right << i++
            << " | " << setw(15) << left << s.prizv
            << " | " << setw(6) << right << s.kurs
            << " | " << setw(15) << left << specialityStr[s.speciality]
            << " | " << setw(4) << s.phys_grade
            << " | " << setw(4) << s.math_grade
            << " | " << setw(4) << s.inf_grade
            << " | " << setw(8) << fixed << setprecision(2) << GetAvg(s) << " |" << endl;
    }
    cout << "==========================================================================================" << endl;
    f.close();
}

void Sort(const char* fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f) return;
    f.seekg(0, ios::end);
    int size = f.tellg() / sizeof(Student);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Student s1, s2;
            f.seekg(j * sizeof(Student));
            f.read((char*)&s1, sizeof(Student));
            f.read((char*)&s2, sizeof(Student));
            bool swapFlag = false;
            if (GetAvg(s1) < GetAvg(s2)) swapFlag = true;
            else if (abs(GetAvg(s1) - GetAvg(s2)) < 0.001) {
                if (s1.kurs > s2.kurs) swapFlag = true;
                else if (s1.kurs == s2.kurs) {
                    if (strcmp(s1.prizv, s2.prizv) < 0) swapFlag = true;
                }
            }
            if (swapFlag) {
                f.seekp(j * sizeof(Student));
                f.write((char*)&s2, sizeof(Student));
                f.write((char*)&s1, sizeof(Student));
            }
        }
    }
    f.close();
}

void IndexSort(const char* fname, const char* gname) {
    ifstream f(fname, ios::binary);
    if (!f) return;
    f.seekg(0, ios::end);
    int size = f.tellg() / sizeof(Student);
    int* I = new int[size];
    Student* temp = new Student[size];
    f.seekg(0, ios::beg);
    for (int i = 0; i < size; i++) {
        I[i] = i;
        f.read((char*)&temp[i], sizeof(Student));
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bool swapFlag = false;
            if (GetAvg(temp[I[j]]) < GetAvg(temp[I[j + 1]])) swapFlag = true;
            else if (abs(GetAvg(temp[I[j]]) - GetAvg(temp[I[j + 1]])) < 0.001) {
                if (temp[I[j]].kurs > temp[I[j + 1]].kurs) swapFlag = true;
                else if (temp[I[j]].kurs == temp[I[j + 1]].kurs) {
                    if (strcmp(temp[I[j]].prizv, temp[I[j + 1]].prizv) > 0) swapFlag = true;
                }
            }
            if (swapFlag) swap(I[j], I[j + 1]);
        }
    }
    ofstream g(gname, ios::binary);
    for (int i = 0; i < size; i++) g.write((char*)&I[i], sizeof(int));
    g.close(); f.close();
    delete[] I; delete[] temp;
}

void PrintIndex(const char* fname, const char* gname) {
    ifstream g(gname, ios::binary);
    if (!g) return;
    ifstream f(fname, ios::binary);
    if (!f) return;
    Student s;
    int idx, row = 1;
    cout << "\n==========================================================================================" << endl;
    cout << "| " << setw(3) << "#" << " | " << setw(15) << left << "Surname" << " | " << setw(6) << "Course" << " | " << setw(15) << "Speciality" << " | " << setw(4) << "Phys" << " | " << setw(4) << "Math" << " | " << setw(4) << "Inf" << " | " << setw(8) << "Avg" << " |" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    while (g.read((char*)&idx, sizeof(int))) {
        f.seekg(idx * sizeof(Student));
        f.read((char*)&s, sizeof(Student));
        cout << "| " << setw(3) << right << row++
            << " | " << setw(15) << left << s.prizv
            << " | " << setw(6) << right << s.kurs
            << " | " << setw(15) << left << specialityStr[s.speciality]
            << " | " << setw(4) << s.phys_grade
            << " | " << setw(4) << s.math_grade
            << " | " << setw(4) << s.inf_grade
            << " | " << setw(8) << fixed << setprecision(2) << GetAvg(s) << " |" << endl;
    }
    cout << "==========================================================================================" << endl;
    g.close(); f.close();
}

int BinSearch(const char* fname, const char* prizv, int kurs, double avg) {
    ifstream f(fname, ios::binary);
    if (!f) 
        return -1;
    f.seekg(0, ios::end);
    int L = 0, R = (f.tellg() / sizeof(Student)) - 1;
    while (L <= R) {
        int m = (L + R) / 2;
        Student s;
        f.seekg(m * sizeof(Student));
        f.read((char*)&s, sizeof(Student));
        if (strcmp(s.prizv, prizv) == 0 && s.kurs == kurs && abs(GetAvg(s) - avg) < 0.01) {
            f.close();
            return m;
        }
        if (GetAvg(s) < avg || (abs(GetAvg(s) - avg) < 0.01 && s.kurs > kurs) || (abs(GetAvg(s) - avg) < 0.01 && s.kurs == kurs && strcmp(s.prizv, prizv) > 0))
            R = m - 1;
        else
            L = m + 1;
    }
    f.close();
    return -1;
}

int main() {
    char fname[100], gname[100];
    cout << "Main file name: "; cin >> fname;
    cout << "Index file name: "; cin >> gname;
    int choice;
    do {
        cout << "\n1. Create 2. Print 3. Physical Sort 4. Index Sort & Print 5. Binary Search 0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1: Create(fname); break;
        case 2: Print(fname); break;
        case 3: Sort(fname); cout << "Physical sort done." << endl; break;
        case 4:
            IndexSort(fname, gname);
            PrintIndex(fname, gname);
            break;
        case 5: {
            char pr[61]; double av;
            cout << "Surname: "; cin >> pr;
            int kr = getValidInt("Course: ", 1, 6);
            cout << "Average: "; cin >> av;
            int res = BinSearch(fname, pr, kr, av);
            if (res != -1) cout << "Found at position (#): " << res + 1 << endl;
            else cout << "Not found." << endl;
            break;
        }
        }
    } while (choice != 0);
    return 0;
}