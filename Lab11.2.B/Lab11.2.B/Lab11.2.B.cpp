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
    union {
        int programming_grade;
        int numerical_methods_grade;
        int pedagogy_grade;
    };
};

void Create(char* fname) {
    ofstream f(fname, ios::binary);
    char ch;
    int spec;
    Student s;
    do {
        cout << "Surname: "; cin >> s.prizv;
        cout << "Course: "; cin >> s.kurs;
        cout << "Speciality (0-CS, 1-Inf, 2-ME, 3-PI, 4-Hand): "; cin >> spec;
        s.speciality = (Speciality)spec;
        cout << "Physics grade: "; cin >> s.phys_grade;
        cout << "Math grade: "; cin >> s.math_grade;

        if (s.speciality == COMPUTER_SCIENCE) {
            cout << "Programming grade: "; cin >> s.programming_grade;
        }
        else if (s.speciality == INFORMATICS) {
            cout << "Numerical methods grade: "; cin >> s.numerical_methods_grade;
        }
        else {
            cout << "Pedagogy grade: "; cin >> s.pedagogy_grade;
        }

        f.write((char*)&s, sizeof(Student));
        cout << "Continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

void Print(char* fname) {
    ifstream f(fname, ios::binary);
    Student s;
    int i = 1;
    cout << "==================================================================================\n";
    cout << "| No | Surname      | Course | Speciality    | Phys | Math | Prog | NumM | Pedag |\n";
    cout << "----------------------------------------------------------------------------------\n";
    while (f.read((char*)&s, sizeof(Student))) {
        cout << "| " << setw(2) << right << i++ << " | "
            << setw(12) << left << s.prizv << " | "
            << setw(6) << right << s.kurs << " | "
            << setw(13) << left << specialityStr[s.speciality] << " | "
            << setw(4) << right << s.phys_grade << " | "
            << setw(4) << right << s.math_grade << " | ";

        if (s.speciality == COMPUTER_SCIENCE)
            cout << setw(4) << s.programming_grade << " | " << setw(4) << "-" << " | " << setw(5) << "-" << " |" << endl;
        else if (s.speciality == INFORMATICS)
            cout << setw(4) << "-" << " | " << setw(4) << s.numerical_methods_grade << " | " << setw(5) << "-" << " |" << endl;
        else
            cout << setw(4) << "-" << " | " << setw(4) << "-" << " | " << setw(5) << s.pedagogy_grade << " |" << endl;
    }
    cout << "==================================================================================\n";
    f.close();
}

void CountGoodGrades(char* fname, int& ph, int& mt, int& prg, int& num, int& ped) {
    ifstream f(fname, ios::binary);
    Student s;
    ph = mt = prg = num = ped = 0;
    while (f.read((char*)&s, sizeof(Student))) {
        if (s.phys_grade == 4) ph++;
        if (s.math_grade == 4) mt++;

        if (s.speciality == COMPUTER_SCIENCE) {
            if (s.programming_grade == 4) prg++;
        }
        else if (s.speciality == INFORMATICS) {
            if (s.numerical_methods_grade == 4) num++;
        }
        else {
            if (s.pedagogy_grade == 4) ped++;
        }
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
    return (total == 0) ? 0 : 100.0 * count / total;
}

int main() {
    char fname[100];
    cout << "Enter file name: "; cin >> fname;
    int choice;
    do {
        cout << "\nMenu:\n1. Create file\n2. Print table\n3. Count 'good' (4) grades\n4. Percent Phys & Math (5)\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1: Create(fname); break;
        case 2: Print(fname); break;
        case 3: {
            int ph, mt, prg, num, ped;
            CountGoodGrades(fname, ph, mt, prg, num, ped);
            cout << "\n'Good' (4) grades:\n";
            cout << "Physics: " << ph << "\nMath: " << mt << endl;
            cout << "Programming: " << prg << "\nNumerical Methods: " << num << "\nPedagogy: " << ped << endl;
            break;
        }
        case 4:
            cout << "\nPercentage with 5 in Phys & Math: " << fixed << setprecision(2)
                << PercentExcellentPhysMath(fname) << "%" << endl;
            break;
        }
    } while (choice != 0);
    return 0;
}