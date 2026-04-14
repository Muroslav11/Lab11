#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct Route {
    char startPoint[61];
    char endPoint[61];
    int routeNumber;
};

int getValidInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(10000, '\n');
            return value;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: enter a valid integer." << endl;
    }
}

void Create(char* fname) {
    ofstream f(fname, ios::binary);
    if (!f) return;
    Route r;
    char ch;
    do {
        cout << "Start Point: "; cin >> r.startPoint;
        cout << "End Point:   "; cin >> r.endPoint;
        r.routeNumber = getValidInt("Route Number: ");
        f.write((char*)&r, sizeof(Route));
        cout << "Continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

void Print(char* fname) {
    ifstream f(fname, ios::binary);
    if (!f) return;
    Route r;
    int i = 1;
    cout << "\n-------------------------------------------------------------" << endl;
    cout << "|  # | Start Point      | End Point        | Route Number   |" << endl;
    cout << "-------------------------------------------------------------" << endl;
    while (f.read((char*)&r, sizeof(Route))) {
        cout << "| " << setw(2) << right << i++
            << " | " << setw(16) << left << r.startPoint
            << " | " << setw(16) << left << r.endPoint
            << " | " << setw(14) << right << r.routeNumber << " |" << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
    f.close();
}

void Sort(char* fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f) return;
    f.seekg(0, ios::end);
    int size = (int)f.tellg() / sizeof(Route);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Route r1, r2;
            f.seekg(j * sizeof(Route));
            f.read((char*)&r1, sizeof(Route));
            f.read((char*)&r2, sizeof(Route));
            if (r1.routeNumber > r2.routeNumber) {
                f.seekp(j * sizeof(Route));
                f.write((char*)&r2, sizeof(Route));
                f.write((char*)&r1, sizeof(Route));
            }
        }
    }
    f.close();
    cout << "\nFile sorted successfully." << endl;
}

void Search(char* fname, int target) {
    ifstream f(fname, ios::binary);
    if (!f) return;
    Route r;
    bool found = false;
    while (f.read((char*)&r, sizeof(Route))) {
        if (r.routeNumber == target) {
            cout << "\nRoute Found:" << endl;
            cout << "Start Point: " << r.startPoint << endl;
            cout << "End Point:   " << r.endPoint << endl;
            cout << "Number:      " << r.routeNumber << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Route with number " << target << " not found." << endl;
    f.close();
}

int main() {
    char fname[100];
    cout << "Enter file name: "; cin >> fname;
    int choice;
    do {
        cout << "\n1. Create File\n2. Print File\n3. Physical Sort\n4. Search by Number\n0. Exit" << endl;
        choice = getValidInt("Choice: ");
        switch (choice) {
        case 1: Create(fname); break;
        case 2: Print(fname); break;
        case 3: Sort(fname); break;
        case 4:
            int num = getValidInt("Enter route number to search: ");
            Search(fname, num);
            break;
        }
    } while (choice != 0);
    return 0;
}