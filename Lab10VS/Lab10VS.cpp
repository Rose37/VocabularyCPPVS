#include <iostream>
#include <fstream>
#include <stdio.h>
#include <Windows.h>

/*Задание: Разработать программу проверки орфографии (правильности написания) слов в некоторой строке, сравнивая их со словами из словаря.
В качестве словаря использовать одномерный массив слов, заданный в программе. При сравнении учитывать возможность записи слов с прописными и строчными буквами.
*/
using namespace std;
void sentence();
void print(string*, int*, int, int);
int orfo(string*, int*, int);
void intrface();
void testing();
void filling();
void del();
void read();

int main()
{
    intrface();

    return 0;
}

void testing()
{
    sentence();
    int* color = new int[100];
    string* ptrmass = new string[100];
    int counter = 0, errors = 0;
    cout << "Write in Russian(EXIT for end): " << endl;
    for (int i = 0; i < 100; i++)
    {
        cin >> ptrmass[i];
        counter++;
        color[i] = 0;
        if ((ptrmass[i] == "EXIT") || (ptrmass[i] == "ВЫХОД"))
        {
            break;
        }
    }
    cin.ignore(32767, '\n');
    errors = orfo(ptrmass, color, counter);
    print(ptrmass, color, counter, errors);
    cout << endl;
    delete[] ptrmass;
    delete[] color;
}

void intrface()
{
    while (true)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "Hi, I am a vocabulary program!" << endl << "Menu:" << endl;
        cout << "1.Spelling" << endl << "2.Fill Vocabulary" << endl;
        cout << "3.Read Vocabulary" << endl << "4.Delete the word" << endl << "5.Exit" << endl << endl;
        int check;
        cout << "Check: ";
        cin >> check;
        switch (check) {
        case 1:
            testing();
            break;
        case 2:
            filling();
            break;
        case 3:
            read();
            break;
        case 4:
            del();
            //SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | 6));
            //cout<<"SOON...";
            //SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 15));
            break;
        case 5:
            return exit(0);
            break;
        default:
            cout << "Wrong answer! Please, try again!" << endl;
            break;
        }
    }
}

void del()
{
    ifstream in("dictionaryEng.txt", ios_base::in);
    cout << "What word do you want to delete? ";
    string word;
    cin >> word;
    int f = 0;
    string* vocabulary = new string[1000];
    char* letter = new char[35];
    while (in >> letter)
    {
        vocabulary[f] = letter;
        f++;
    }
    cout << endl << "F is " << f;
    in.close();
    int switcher = 0;
    for (int i = 0; i < f; i++)
    {
        if (vocabulary[i] == word)
        {
            string temp = vocabulary[i];
            vocabulary[i] = vocabulary[f];
            vocabulary[f] = temp;
            switcher++;
        }
        if (((i == f - 1) || (i == f)) && (word != vocabulary[i]) && (switcher == 0))
        {
            cout << endl << "Unknown word! Try again." << endl;
            exit(100500);
        }
    }

    ofstream clean;
    clean.open("dictionaryEng.txt", ofstream::out | ofstream::trunc);
    clean.close();

    cout << endl << endl << endl;

    ofstream out("dictionaryEng.txt", ios_base::app);
    for (int j = 0; j < f ; j++)
    {
        out << vocabulary[j] << endl;
    }
    for (int l = 0; l < f; l++)
    {
        vocabulary[l] = l;
    }
    cout << "The word '" << word << "' has been deleted from the dictionary!" << endl << endl;
    delete[] vocabulary;
    delete[] letter;
    out.close();

}

void read()
{
    ifstream book("dictionaryEng.txt");
    string temp;
    int k = 0, c = 0;

    while (book >> temp)
    {
        cout << temp << '\t';
        if (k == 5)
        {
            k = 0;
            cout << endl;
            c++;
        }
        else k++;
        if (c == 5)
        {
            c = 0;
            cout << endl << endl;
        }

    }
    cout << endl << endl;
    book.close();
}

void filling()
{
    ofstream dict("dictionaryEng.txt", ios_base::app);
    string word1;
    cout << "Please, enter the word, what you want to add: ";
    cin >> word1;
    dict << endl << word1;
    cout << "The word '" << word1 << "' has added.";
    cout << endl << endl;
    dict.close();
}

int orfo(string* mass, int* colo, int length)
{

    int countest = 0;
    for (int i = 0; i < length - 1; i++)
    {
        ifstream dict("dictionaryEng.txt");
        if (!dict)
            exit(100500);
        string temp;
        int xx = 0;
        while (dict >> temp)
        {
            if (temp == mass[i])
            {
                xx++;
            }
        }
        if (xx == 0)
        {
            //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            countest++;
            colo[i] = 1;
            //SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
        }
        dict.close();
    }
    return countest;
}

void sentence()
{
    cout << "Please, tell us about your day (^_^) " << endl;
}

void print(string* mass, int* colo, int length, int counter)
{
    cout << "Your sentence:   ";
    for (int i = 0; i < length - 1; i++)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (colo[i] == 1)
        {
            SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 15));
        }
        cout << mass[i];
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
        cout << " ";
    }
    cout << endl << "And you have " << counter << " errors/unknowing points!" << endl;
}

