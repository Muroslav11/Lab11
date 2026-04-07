#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

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

void Create(char* fname) {
    ofstream f(fname, ios::binary);
    char ch;
    int spec;
    Student s;
    do {
        cout << "Surname: "; cin >> s.prizv;
        cout << "Course: "; cin >> s.kurs;
        cout << "Speciality (0 - CS, 1 - Inf, 2 - ME, 3 - PI, 4 - Hand): "; cin >> spec;
        s.speciality = (Speciality)spec;
        cout << "Physics grade: "; cin >> s.phys_grade;
        cout << "Math grade: "; cin >> s.math_grade;
        cout << "Informatics grade: "; cin >> s.inf_grade;

        f.write((char*)&s, sizeof(Student)); 

        cout << "Continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

void Print(char* fname) {
    ifstream f(fname, ios::binary);
    Student s;
    int i = 1;
    cout << "=============================================================================\n";
    cout << "| No | Surname      | Course | Speciality    | Physics | Math | Informatics |\n";
    cout << "-----------------------------------------------------------------------------\n";
    while (f.read((char*)&s, sizeof(Student))) {
        cout << "| " << setw(2) << right << i++ << " | " 
            << setw(12) << left << s.prizv << " | "   
            << setw(6) << right << s.kurs << " | "   
            << setw(13) << left << specialityStr[s.speciality] << " | "
            << setw(7) << right << s.phys_grade << " | "
            << setw(4) << right << s.math_grade << " | "
            << setw(11) << right << s.inf_grade << " |" << endl;
    }
    cout << "=============================================================================\n";
    f.close();
}

void CountGoodGrades(char* fname, int& ph, int& mt, int& inf) {
    ifstream f(fname, ios::binary);
    Student s;
    ph = mt = inf = 0;
    while (f.read((char*)&s, sizeof(Student))) {
        if (s.phys_grade == 4) ph++;
        if (s.math_grade == 4) mt++;
        if (s.inf_grade == 4) inf++;
    }
    f.close();
}

double PercentExcellentPhysMath(char* fname) {
    ifstream f(fname, ios::binary);
    Student s;
    int total = 0, count = 0;
    while (f.read((char*)&s, sizeof(Student))) {
        total++;
        if (s.phys_grade == 5 && s.math_grade == 5)
            count++;
    }
    f.close();
    if (total == 0) return 0;
    return 100.0 * count / total;
}

int main() {
    char fname[100];
    cout << "Enter file name: "; cin >> fname;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Create file\n";
        cout << "2. Print table\n";
        cout << "3. Count 'good' (4) grades by subjects\n"; 
        cout << "4. Calculate percentage of students with 5 in Phys & Math\n"; 
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Create(fname);
            break;
        case 2:
            Print(fname);
            break;
        case 3: {
            int ph, mt, inf;
            CountGoodGrades(fname, ph, mt, inf);
            cout << "\nCount of 'good' (4) grades:\n";
            cout << "Physics: " << ph << "\nMath: " << mt << "\nInformatics: " << inf << endl;
            break;
        }
        case 4:
            cout << "\nPercentage of students with 5 in Phys & Math: "
                << fixed << setprecision(2) << PercentExcellentPhysMath(fname) << "%" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}