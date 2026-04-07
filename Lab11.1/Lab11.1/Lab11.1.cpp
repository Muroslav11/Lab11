#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

// Функція для створення початкового бінарного файлу з випадковими числами
void Create(const char* fName)
{
    srand((unsigned)time(NULL));
    ofstream f(fName, ios::binary);
    int x;
    int n;
    cout << "Enter count of numbers: "; cin >> n;
    for (int i = 0; i < n; i++)
    {
        x = -50 + rand() % 101; // генеруємо числа в діапазоні [-50; 50]
        f.write((char*)&x, sizeof(x));
    }
    f.close();
}

// Функція для виведення вмісту бінарного файлу на екран
void Print(const char* fName)
{
    ifstream f(fName, ios::binary);
    int x;
    cout << "\nfile \"" << fName << "\":" << endl;
    while (f.read((char*)&x, sizeof(x)))
    {
        cout << x << " ";
    }
    cout << endl;
    f.close();
}

// Функція для розподілу чисел на парні та непарні у два окремі файли
void Process(const char* fName, const char* evenName, const char* oddName)
{
    ifstream f(fName, ios::binary);
    ofstream g(evenName, ios::binary); 
    ofstream h(oddName, ios::binary); 
    int x;
    while (f.read((char*)&x, sizeof(x)))
    {
        if (x % 2 == 0)
            g.write((char*)&x, sizeof(x));
        else
            h.write((char*)&x, sizeof(x));
    }
    f.close();
    g.close();
    h.close();
}

int main()
{
    char fname[100];
    cout << "Enter main file name: "; cin >> fname;

    Create(fname);
    Print(fname);

    Process(fname, "even.dat", "odd.dat");

    Print("even.dat");
    Print("odd.dat");

    return 0;
}