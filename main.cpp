#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// limitation since not allowed to dynamically allocate memory
#define SIZE 1000

// FUNCTIONS
// getline(file, s);

//Function Prototypes
void addStudent(string fileName, string name, string rollNum, string section, string marksFile,int &numStudents);
void readStudentData(string fileName);
string searchStudent(string fileName, string query);
void addMarks(string marksFile,string rollNum);
void displayStudentData(string fileName, string marksFile);
void averageMarks(string marksFile);

int main() {
    string fileName = "students.txt";
    ifstream file(fileName, ios::in);
    string marksFile = "marks.txt";
    int numStudents;

    string s;
    cout << s << endl;
    string Students[SIZE];

    int choice;
    do{
        cout<<"Select Action: "<<endl
            <<"\t1. Enter New Student Record. "<<endl
            <<"\t2. Retrieve Student Data. "<<endl
            <<"\t3. Update or delete Student Data."<<endl
            <<"\t4. Display Student Records. "<<endl
            <<"\t5. Search for Student Records. "<<endl
            <<"\t6. Show Class Performance Report."<<endl;
        cin>>choice;
        switch (choice){
            case 1:
                {string name,rollNum,section;
                    cout<<"Enter Student Name: ";
                    cin.ignore();
                    getline(cin,name);
                    cout<<"Enter Rollnumber: ";
                    cin>>rollNum;
                    cout<<"Enter Student Section: ";
                    cin>>section;
                    addStudent(fileName,name,rollNum,section,marksFile,numStudents);
                    // issue here
                    addMarks(marksFile,rollNum);
                    break;
                }
            case 2:
                {readStudentData(fileName);
                break;
                }
            case 3:
                break;
            case 4:{
                // displayStudentData(fileName,marksFile);
                break;
            }
            case 5:{
                
            }
            case 6:{
                
            }
        }
    }while (choice>0&&choice<=6);
    
    return 0;
}

void addStudent(string fileName, string name, string rollNum, string section, string marksFile, int &numStudents) {
    fstream file(fileName, ios::app);
    fstream markfile(marksFile, ios::app);
    if (!file.is_open()) {
        cout << "Error in opening file while writing student data" << endl;
        exit(1);
    }
    if (!markfile.is_open()) {
        cout << "Error in opening file while writing student data" << endl;
        exit(1);
    }
    // using backslash t for partition
    file << name << "\t" << rollNum << "\t" << section << '\n';
    markfile << rollNum << '\t' << "-  " << '\t' << "-  " << '\t' << "-  "
    << '\t' << "-  " << '\t' << "-  " << '\t' << "-  " << '\n';
    file.close();
    markfile.close();
    numStudents++;
}

void addMarks(string marksFile, string rollNum) {
    // some issue in this function
    int quizCnt = 0, midCnt = 0, finalCnt = 0;
    fstream markfile(marksFile, ios::app);
    string s;
    while (getline(markfile, s)) {
        string temp;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != '\t') {
                temp += s[i];
            } else {
                break;
            }
        }
        // temp will be the rollNum we should check, if it doesn't match then go to the next line
        if (rollNum != temp) {
            continue;
        } else {
            int cnt = 0;
            int marksArr[6] = {0};
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '-') {
                    int marks = 0;
                    if (quizCnt < 3) {
                        cout << "Enter marks for quiz " << quizCnt + 1 << ": ";
                        quizCnt++;
                    } else if (midCnt < 2) {
                        cout << "Enter marks for mid " << midCnt + 1 << ": "; 
                        midCnt++;
                    } else if (finalCnt < 1) {
                        cout << "Enter marks for final: ";
                        finalCnt++;
                    }
                    do {
                        
                        cin >> marks;
                        if (marks < 0 || marks > 100) {
                            cout << "Incorrect input, Please enter again: ";
                            continue;
                        }
                        marksArr[cnt] = marks;
                        cnt++;
                    } while (marks < 0 || marks > 100);
                    string strMark = to_string(marks);
                    for (int j = 0; j < 3; j++) {
                        if (j < strMark.length()) {
                            s[i + j] = strMark[j];
                        }
                    }
                }
            }
        }
    }
}

void readStudentData(string fileName) {
    fstream file(fileName, ios::in);
    if (!file.is_open()) {
        cout << "Error in opening file while reading student data" << endl;
        exit(1);
    }
    string s;
    while(getline(file, s)) {
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