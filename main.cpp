#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// limitation since not allowed to dynamically allocate memory
#define SIZE 1000

// FUNCTIONS
// getline(file, s);

// Function Prototypes
void addStudent(string fileName, string name, string rollNum, string section, string marksFile, int &numStudents);
bool doesStudentExist(string fileName, string rollNum);
void readStudentData(string fileName);
string searchStudent(string fileName, string query);
void addMarks(string marksFile, string rollNum, string quizFile, string midsFile, string finalsFile);
void displayStudentData(string fileName, string marksFile);
void averageMarks(string marksFile);

int main()
{
    // file names
    string fileName = "students.txt";
    string quizFile = "quiz.txt";
    string midsFile = "mids.txt";
    string finalsFile = "final.txt";
    string marksFile = "marks.txt";

    ifstream file(fileName, ios::in);
    // numStudents should be initialized by reading the file for lines every time the program runs
    int numStudents;

    string s;
    cout << s << endl;
    string Students[SIZE];

    int choice;
    do
    {
        cout << "Select Action: " << endl
             << "\t1. Enter New Student Record. " << endl
             << "\t2. Retrieve Student Data. " << endl
             << "\t3. Update or delete Student Data." << endl
             << "\t4. Display Student Records. " << endl
             << "\t5. Search for Student Records. " << endl
             << "\t6. Show Class Performance Report." << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string name, rollNum, section;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Rollnumber: ";
            cin >> rollNum;
            cin.ignore();
            bool exists = doesStudentExist(fileName, rollNum);
            if (exists) {
                cout << "Student already exists!" << std::endl;
                break;
            }
            cout << "Enter Student Section: ";
            cin >> section;
            cin.ignore();
            addStudent(fileName, name, rollNum, section, marksFile, numStudents);
            // issue here
            addMarks(marksFile, rollNum, quizFile, midsFile, finalsFile);
            break;
        }
        case 2:
        {
            readStudentData(fileName);
            break;
        }
        case 3:
            break;
        case 4:
        {
            // displayStudentData(fileName,marksFile);
            break;
        }
        case 5:
        {
        }
        case 6:
        {
        }
        }
    } while (choice > 0 && choice <= 6);

    return 0;
}

bool doesStudentExist(string fileName, string rollNum)
{
    fstream file(fileName, ios::in);
    string s;
    while (getline(file, s))
    {
        string temp; 
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != '\t')
            {
                temp += s[i];
            }
            else
            {
                if (temp == rollNum)
                {
                    return true;
                }
                else
                {
                    temp = "";
                }
            }
        }
    }
    file.close();
    return false;
}

void addStudent(string fileName, string name, string rollNum, string section, string marksFile, int &numStudents)
{

    fstream file(fileName, ios::app);
    fstream markfile(marksFile, ios::app);
    if (!file.is_open())
    {
        cout << "Error in opening file while writing student data" << endl;
        exit(1);
    }
    if (!markfile.is_open())
    {
        cout << "Error in opening file while writing student data" << endl;
        exit(1);
    }
    // using backslash t for partition
    file << name << "\t" << rollNum << "\t" << section << '\n';
    file.close();
    markfile.close();
    numStudents++;
}

void addMarks(string marksFile, string rollNum, string quizFile, string midsFile, string finalsFile)
{
    // some issue in this function
    int quizCnt = 0, midCnt = 0, finalCnt = 0;
    int marks[6] = {0};
    for (int i = 0; i < 6; i++) {
        if (quizCnt < 3 ) {
            fstream quizfile (quizFile, ios::app);
            if (quizCnt == 0) {
                quizfile << rollNum << '\t';
            }
            cout << "Enter marks for quiz " << quizCnt + 1 << ": ";
            cin >> marks[i];
            quizfile << marks[i]; 
            quizCnt++;

            
            if (quizCnt == 3) {
                quizfile << '\n';
            } else {
                quizfile << '\t';
            }
        } else if (midCnt < 2) {
            fstream midsfile(midsFile, ios::app);
            if (midCnt == 0) {
                midsfile << rollNum << '\t';
            }
            cout << "Enter marks for mid " << midCnt + 1 << ": ";
            cin >> marks[i];
            midsfile << marks[i];
            midCnt++;

            if (midCnt == 2) {
                midsfile << '\n';
            } else {
                midsfile << '\t';
            }

        } else if (finalCnt < 1) {
            fstream finalfile(finalsFile, ios::app);
            if (finalCnt == 0) {
                finalfile << rollNum << '\t';
            }
            cout << "Enter marks for final: ";
            cin >> marks[i];
            finalfile << marks[i]; 
            finalCnt++;
            
            if (finalCnt == 1) {
                finalfile << '\n';
            } else {
                finalfile << '\t';
            }
        }
    }
    fstream markfile(marksFile, ios::app);
    markfile << rollNum << "\t";
    for (int i = 0; i < 6; i++) {
        markfile << to_string(marks[i]);
        if (i == 5) {
            markfile << '\n';
        } else {
            markfile << '\t';
        }
    }

    markfile.close();
}

void readStudentData(string fileName)
{
    fstream file(fileName, ios::in);
    if (!file.is_open())
    {
        cout << "Error in opening file while reading student data" << endl;
        exit(1);
    }
    string s;
    while (getline(file, s))
    {
        cout << s << endl;
    }
    file.close();
}
// string searchStudent(string fileName, string query) {
//     fstream file(fileName, ios::in);
//     if (!file.is_open()) {
//         cout << "Error in opening file while querying for data" <<endl;
//         exit(1);
//     }
//     // TODO
//     file.close();
// }
