#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// limitation since not allowed to dynamically allocate memory
#define SIZE 1000

struct Student {
    string name;
    string rollNum;
    string section;
};

struct MarksStruct {
    string rollNum;
    int quiz[3] = {0};
    int m1;
    int m2;
    int f;
    string grade;
    float percentage;
};

// FUNCTIONS
// getline(file, s);

// Function Prototypes
void addStudent(string fileName, string name, string rollNum, string section, string marksFile, int &numStudents);
bool doesStudentExist(string fileName, string rollNum);
void readStudentData(string fileName);
string searchStudent(string fileName, string query);
void addMarks(string marksFile, string rollNum, string quizFile, string midsFile, string finalsFile);
void displayStudentData(string fileName, string marksFile);
void showClassPerformanceStats(MarksStruct marksArray[], int count);
void loadMarksInArray(string marksFile, MarksStruct marksArray[]);
int loadDataInArray(string file, Student arr[]);
void updateStudentData(Student students[], MarksStruct marks[], string studentsFile, string marksFile, int& noOfStudents);
void addChangesToStudentFile(string studentsFile, Student students[], int noOfStudents);
void displayLine();
void displayStudentData(Student student, MarksStruct mark);
void deleteFromStudentFile(string studentsFile, string marksFile, Student students[], MarksStruct marks[], int noOfStudents, string rNum, string quizFile, string midsFile, string finalsFile);
void addStudentMarksWithoutPrompting(string marksFile, string rollNum, string quizFile, string midsFile, string finalsFile, MarksStruct marks[], int noOfStudents);
void sortArrays(Student students[], MarksStruct marks[], int noOfStudents, string studentsFile, string marksFile, string quizFile, string midsFile, string finalsFile);
void calculateGrade(MarksStruct marks[], int noOfStudents);
bool validateRollNum(string rollNum);
bool validateSection(string section);
bool validateName(string name);

int main()
{
    // file names
    string fileName = "students.txt";
    string quizFile = "quiz.txt";
    string midsFile = "mids.txt";
    string finalsFile = "final.txt";
    string marksFile = "marks.txt";

    Student students[SIZE];
    MarksStruct marks[SIZE];
    // reading students in this array
    int noOfStudents = loadDataInArray(fileName, students);
    
    // loading marks in marksArray
    loadMarksInArray(marksFile, marks);
    sortArrays(students, marks, noOfStudents, fileName, marksFile, quizFile, midsFile, finalsFile);
    calculateGrade(marks, noOfStudents);

    int choice;
    do
    {
        cout << "Select Action: " << endl << endl
        << setw(60) << setfill('-') << " " << setfill(' ') << endl 
             << '|' << setw(51) <<  left 
             << "\t1. Enter New Student Record. " << right << '|' << endl
             << '|' << setw(51) << left 
             << "\t2. Retrieve Student Data. " << right << '|' << endl
             << '|' << setw(51) << left
             << "\t3. Update or delete Student Data." << right << '|' << endl
             << '|' << setw(51) << left
             << "\t4. Show Class Performance Report." << right << '|' << endl
             << '|' << setw(51) << left
             << "\t5. Exit."<<  right << '|' << endl
             << setw(60) << setfill('-') << " " << setfill(' ') << setw(60)
             << "\nSelect Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string name, rollNum, section;
            bool containsAnomaly;

            cin.ignore(); 

            do {
                cout << "Enter Student Name: ";
                getline(cin, name);

            }while(!validateName(name));
            // prevent anomalies
            // rollNum
            do {
                containsAnomaly = false;
                cout << "Enter Rollnumber: ";
                getline(cin, rollNum);
                
            } while (!validateRollNum(rollNum));
            
            bool exists = doesStudentExist(fileName, rollNum);
            if (exists) {
                cout << "Student Already Exists!" << std::endl;
                break;
            }

            // prevent anomalies
            // section
            do {
                cout << "Enter Student Section: ";
                getline(cin, section);

            }while(!validateSection(section));

            
            // save data
            addStudent(fileName, name, rollNum, section, marksFile, noOfStudents);
            addMarks(marksFile, rollNum, quizFile, midsFile, finalsFile);

            // perform calculations again
            noOfStudents = loadDataInArray(fileName, students);
            loadMarksInArray(marksFile, marks);
            calculateGrade(marks, noOfStudents);
            sortArrays(students, marks, noOfStudents, fileName, marksFile, quizFile, midsFile, finalsFile);
            break;
        }
        case 2:
        {
            cout << "Select: " << endl
            << setw(60) << setfill('-') << " " << setfill(' ') << endl
            << '|' << setw(51) << left  
            << "\t1. All Students." << right << '|' << endl
            << '|' << setw(51) << left
            << "\t2. Particular Student (Roll Number Required)." << right << '|' << endl
            << setw(60) << setfill('-') << " " << setfill(' ') << endl
            <<"Enter Choice: ";
            int dataChoice;
            inQuery: 
            cin >> dataChoice;
            if (dataChoice == 1) {
                displayLine();
                for (int i = 0; i < noOfStudents; i++) {
                    displayStudentData(students[i], marks[i]);
                }
                cout << endl;
            } else if (dataChoice == 2) {
                cin.ignore();
                string rNum;
                do {
                cout << "Enter Roll Number of the Required Student: ";
                cin >> rNum;
                } while (!validateRollNum(rNum));
                // for printing line
                displayLine();
                // line ends here
                // student data begins here
                int stdntsIdx = -1, marksIdx = -1;
                for (int i = 0; i < noOfStudents; i++) {
                    if (students[i].rollNum == rNum) {
                        stdntsIdx = i;
                    }
                    if (marks[i].rollNum == rNum) {
                        marksIdx = i;
                        displayStudentData(students[stdntsIdx], marks[marksIdx]);
                        break;
                    }
                    if (i == noOfStudents - 1) {
                        cout << "Student not found!" << endl;
                        // printing line
                        cout << setfill('-');
                        cout << setw(42);
                        cout << " ";
                        cout << '\n';
                        cout << setfill(' ');
                        // line ends here
                        break;
                    }
                }

            } else {
                cout << "Incorrect Input!" << endl;
                goto inQuery;
            }
            // readStudentData(fileName);
            break;
        }
        case 3:
            updateStudentData(students, marks, fileName, marksFile, noOfStudents);
            break;
        
        case 4:
        {
            showClassPerformanceStats(marks,noOfStudents);
            break;
        }
        case 5:
        {
            return 0;
            break;
        }
        default: 
            cout << "Invalid choice. Please select a number between 1 and 5" << endl;
            break;
        }

    } while (choice > 0 && choice <= 6);

    return 0;
}

void displayLine() {
    // big line
    cout << setw(56) << setfill('-') << " " << endl << setfill(' ');
    cout << '|' << setw(8) << left << "ROLL NUM" << '|'
         << setw(20) << right << "NAME" << '|'
         << setw(10) << right << "SECTION" << '|'
         << setw(6) << right << "%" << '|'
         << setw(5) << right << "GRADE" << '|' << '\n';
         
    cout << setw(56) << setfill('-') << " " << endl << setfill(' ');
}

void displayStudentData(Student student, MarksStruct mark) {
    //this is printed below the line in most cases

    if (student.name == "" || student.rollNum == "" || student.section == "") return;
    cout << '|';
    cout << setw(8) << left << student.rollNum << '|'
    << setw(20) << right << student.name << '|' 
    << setw(10) << right << student.section << '|'
    << setw(6) << right << fixed << setprecision(1) << mark.percentage << '|'
    << setw(5) << right << mark.grade << '|' << '\n';
    cout << setw(56) << setfill('-') << " " << endl << setfill(' ');
}

bool doesStudentExist(string fileName, string rollNum)
{
    fstream file(fileName, ios::in);
    string s;
    while (getline(file, s))
    {
        if (s == "") continue;
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
    if (!file.is_open())
    {
        cout << "Error in opening file while writing student data" << endl;
        exit(1);
    }
    // using backslash t for partition
    file << name << "\t" << rollNum << "\t" << section << '\n';
    file.close();
    numStudents++;
}

void addMarks(string marksFile, string rollNum, string quizFile, string midsFile, string finalsFile)
{
    
    int quizCnt = 0, midCnt = 0, finalCnt = 0;
    int marks[6] = {0};
    for (int i = 0; i < 6; i++) {
        if (quizCnt < 3 ) {
            fstream quizfile (quizFile, ios::app);
            if (quizCnt == 0) {
                quizfile << rollNum << '\t';
            }
            do{
                cout << "Enter Marks for Quiz " << quizCnt + 1 << ": ";
                cin >> marks[i];
                quizfile << marks[i];
                if (marks[i]>100||marks[i]<0)
                    cout<<"Invalid Input! Enter marks between 0 and 100.\n";
            }while(marks[i]>100||marks[i]<0); 
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
            do{
                cout << "Enter Marks for Mid " << midCnt + 1 << ": ";
                cin >> marks[i];
                if (marks[i]>100||marks[i]<0)
                    cout<<"Invalid Input! Enter Marks between 0 and 100.\n";
            }while(marks[i]>100||marks[i]<0);
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
            do{
                cout << "Enter Marks for Final: ";
                cin >> marks[i];
                if (marks[i]>100||marks[i]<0)
                    cout<<"Invalid Input! Enter Marks between 0 and 100.\n";
            }while(marks[i]>100||marks[i]<0);
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

void addStudentMarksWithoutPrompting(string marksFile, string rollNum, string quizFile, string midsFile, string finalsFile, MarksStruct marks[], int noOfStudents) {
    fstream markfile(marksFile, ios::out);
    fstream quizfile (quizFile, ios::out);
    fstream midsfile(midsFile, ios::out);
    fstream finalfile(finalsFile, ios::out);
    for (int j = 0; j < noOfStudents; j++) {
        if (marks[j].rollNum == rollNum) continue;
        if (marks[j].rollNum == "") continue;
    
        int quizCnt = 0, midCnt = 0, finalCnt = 0;
        quizfile << marks[j].rollNum << '\t';
        for (int l = 0; l < 3; l++) {
            if (l < 2)
            quizfile << marks[j].quiz[l] << '\t';
            else 
            quizfile << marks[j].quiz[l] << '\n'; 
        }
        midsfile << marks[j].rollNum << '\t';
        midsfile << marks[j].m1 << '\t';
        midsfile << marks[j].m2 << '\n';
        
        finalfile << marks[j].rollNum << '\t';            
        finalfile << marks[j].f << '\n'; 
            
        markfile << marks[j].rollNum << "\t";
        for (int i = 0; i < 3; i++) {
            markfile << to_string(marks[j].quiz[i]);
            markfile << '\t';
        }
            markfile << to_string(marks[j].m1) << '\t';
            markfile << to_string(marks[j].m2) << '\t';
            markfile << to_string(marks[j].f) << '\n';
    }
        markfile.close();
        quizfile.close();
        midsfile.close();
        finalfile.close();
}

int loadDataInArray(string file, Student arr[]) {
    fstream studentsFile(file, ios::in);
    string line;
    int i = 0;
    while (getline(studentsFile, line, '\n')) {
        if (line == "") continue;
        string rollNum, name, section;
        int read_index = 0;
        while(read_index < line.length() && line[read_index] != '\t' && line[read_index] != '\n') {
            name += line[read_index];
            read_index++;
        }
        read_index++;
        while(read_index < line.length() && line[read_index] != '\t' && line[read_index] != '\n') {
            rollNum += line[read_index];
            read_index++;
        }
        read_index++;
        while(read_index < line.length() && line[read_index] != '\t' && line[read_index] != '\n') {
            section += line[read_index];
            read_index++;
        }
        Student temp;
        if (i < SIZE) {
            temp.name = name;
            temp.rollNum = rollNum;
            temp.section = section;
            arr[i] = temp;
            i++;
        } else {
            cout << "Maximum size reached. Cannot add more students" << endl;
        }
    }
    // resolving off by one error since last getline does not end with a \n
    return i;
}
void loadMarksInArray(string marksFile, MarksStruct marksArray[]){
    fstream file(marksFile,ios::in);
    if (!file.is_open())
        return;
    
    string line;
    int count =0;

    while (getline(file,line)&&count<SIZE){
        if (line == "" || line == "\n")
            continue;

        string temp= ""; // empty string instead of " "
        int colIndex=0;

        for (int i = 0; i < line.length(); i++){
            if (line[i] != '\t' && line[i] != '\n') {
                temp += line[i];
            }
            else if (line[i] == '\t') {
                if (colIndex == 0) {
                    marksArray[count].rollNum = temp;
                    colIndex++;
                    temp = "";
                } 
                else if (colIndex >= 1) {
                    if (temp!="") {
                        int val = stoi(temp);
                        if (colIndex==1) {
                            marksArray[count].quiz[0]=val;
                            colIndex++;
                            temp = "";
                        }
                        else if (colIndex==2) {
                            marksArray[count].quiz[1]=val;
                            colIndex++;
                            temp = "";
                        }
                        else if (colIndex==3) {
                            marksArray[count].quiz[2]=val;
                            colIndex++;
                            temp = "";
                        }
                        else if (colIndex==4) {
                            marksArray[count].m1=val;
                            colIndex++;
                            temp = "";
                        }
                        else if (colIndex==5) {
                            marksArray[count].m2=val;
                            colIndex++;
                            temp = "";
                        }
                        else if (colIndex==6) {
                            marksArray[count].f=val;
                        }
                        temp = "";
                    }
                }
            } else if (i == line.length() - 1) {
                marksArray[count].f = stoi(temp);
                colIndex = 0;
            }
        }
        if (temp != "") {
            marksArray[count].f = stoi(temp);
            temp = "";
        }
        count++;
    }
    file.close();
}
void showClassPerformanceStats(MarksStruct marksArray[],int count){
    if (count==0){
        cout<<"No Student data available.\n";
        return ;
    }

    double sumQ1=0,sumQ2=0,sumQ3=0,sumM1=0,sumM2=0,sumF=0;
    double maxQ1=-1,maxQ2=-1,maxQ3=-1,maxM1=-1,maxM2=-1,maxF=-1; //Initializing with the lowest value possible
    double minQ1=101,minQ2=101,minQ3=101,minM1=101,minM2=101,minF=101; //Initializing with the highest value.
    
    for (int i=0;i<count;i++){        //displaying the average of each category
        sumQ1+=marksArray[i].quiz[0];
        sumQ2+=marksArray[i].quiz[1];
        sumQ3+=marksArray[i].quiz[2];
        sumM1+=marksArray[i].m1;
        sumM2+=marksArray[i].m2;
        sumF+=marksArray[i].f;
        
        //calculating the maximums of every category
        if (marksArray[i].quiz[0]>maxQ1){
            maxQ1=marksArray[i].quiz[0];
        }
        if (marksArray[i].quiz[1]>maxQ2){
            maxQ2=marksArray[i].quiz[1];
        }
        if (marksArray[i].quiz[2]>maxQ3){
            maxQ3=marksArray[i].quiz[2];
        }
        if (marksArray[i].m1>maxM1){
            maxM1=marksArray[i].m1;
        }
        if (marksArray[i].m2>maxM2){
            maxM2=marksArray[i].m2;
        }
        if (marksArray[i].f>maxF){
            maxF=marksArray[i].f;
        }
        //calculating the minimums of each category
        if (marksArray[i].quiz[0]<minQ1){
            minQ1=marksArray[i].quiz[0];
        }
        if (marksArray[i].quiz[1]<minQ2){
            minQ2=marksArray[i].quiz[1];
        }
        if (marksArray[i].quiz[2]<minQ3){
            minQ3=marksArray[i].quiz[2];
        }
        if (marksArray[i].m1<minM1){
            minM1=marksArray[i].m1;
        }
        if (marksArray[i].m2<minM2){
            minM2=marksArray[i].m2;
        }
        if (marksArray[i].f<minF){
            minF=marksArray[i].f;
        }
        
    }
        cout<<fixed<<setprecision(2);
        cout<<"Total Students: "<<count<<endl
            <<"Quiz 1 -> Average: "<<sumQ1/count<<" | Max: "<<maxQ1<<" | Min: "<<minQ1<<endl
            <<"Quiz 2 -> Average: "<<sumQ2/count<<" | Max: "<<maxQ2<<" | Min: "<<minQ2<<endl
            <<"Quiz 3 -> Average: "<<sumQ3/count<<" | Max: "<<maxQ3<<" | Min: "<<minQ3<<endl
            <<"Mid -> Average: "<<sumM1/count<<" | Max: "<<maxM1<<" | Min: "<<minM1<<endl
            <<"Assignment -> Average: "<<sumM2/count<<" | Max: "<<maxM2<<" | Min: "<<minM2<<endl
            <<"Final -> Average: "<<sumF/count<<" | Max: "<<maxF<<" | Min: "<<minF<<endl;
    
}

void addChangesToStudentFile(string studentsFile, Student students[], int noOfStudents) {
    fstream file(studentsFile, ios::out);
    if (!file.is_open())
    {
        cout << "Error in opening file while writing student data" << endl;
        exit(1);
    }
    for (int i = 0; i < noOfStudents; i++) {
        // using backslash t for partition
        file << students[i].name << "\t" << students[i].rollNum << "\t" << students[i].section << '\n';
    }
    file.close();
}
void deleteFromStudentFile(string studentsFile, string marksFile, Student students[], MarksStruct marks[], int noOfStudents, string rNum, string quizFile, string midsFile, string finalsFile) {
    fstream file(studentsFile, ios::out);
    fstream markfile(marksFile, ios::out);
    if (!file.is_open())
    {
        cout << "Error in opening file while writing student data" << endl;
        file.close();
        exit(1);
    }
    if (!markfile.is_open())
    {
        cout << "Error in opening file while writing student data" << endl;
        markfile.close();
        exit(1);
    }
    for (int i = 0; i < noOfStudents; i++) {
        // using backslash t for partition
        if (students[i].rollNum == rNum) continue;
        file << students[i].name << "\t" << students[i].rollNum << "\t" << students[i].section << '\n';
    }
    file.close();
    addStudentMarksWithoutPrompting(marksFile, rNum, quizFile, midsFile, finalsFile, marks, noOfStudents);
}

void updateStudentData(Student students[], MarksStruct marks[], string studentsFile, string marksFile, int& noOfStudents) {
    int choice;
    do{
        cout << "What do you want to update / delete from?" << endl;
        cout << setw(60) << setfill('-') << " " << setfill(' ') << endl;
        cout << '|' << setw(51) << left
        << "\t1. Students Information" << right << '|' << endl
        << '|' << setw(51) << left 
        << "\t2. Marks of a Student" << right << '|' << endl
        << setw(60) << setfill('-') << " " << setfill(' ') << endl
        <<"Enter Choice: ";
        cin >> choice;
        if(choice<0||choice>2)
            cout<<"Enter Valid Option 1 or 2\n";
    }while(choice<0||choice>2);
    if (choice == 1) {
        cout << " Do you want to:" << endl;
        cout << setw(60) << setfill('-') << " " << setfill(' ') << endl;
        cout << '|' << setw(51) << left
        << "\t1. Change Student Data" << '|' << endl
        << '|' << setw(51) << left
        << "\t2. Delete Student" << right << '|' << endl;
        cout << setw(60) << setfill('-') << " " << setfill(' ') << endl
            <<"Enter Choice: ";
        cin >> choice;
        if (choice == 1) {
            cin.ignore();
            beginDeleteQuery:
            cout << "Enter the Roll Number of the Student (In 25L-0123 Format): ";
            string rNum;
            cin >> rNum;
            if (!validateRollNum(rNum)) goto beginDeleteQuery;
            if (!doesStudentExist(studentsFile, rNum)) {
                cout << "Student does not exist!" << endl;
                goto beginDeleteQuery;
            }
            int idx;
            int markIdx;
            for (int i = 0; i < noOfStudents; i++) {
                if (students[i].rollNum == rNum) {
                    idx = i;
                }
            }
            for (int i = 0; i < noOfStudents; i++) {
                if (marks[i].rollNum == rNum) {
                    markIdx = i;
                }
            }

            do{
                cout << "What do you want to change?" << endl;
                cout << setw(60) << setfill('-') << " " << setfill(' ') << endl
                << '|' << setw(51) << left
                << "\t1. Name of Student " << right << '|' << endl
                << '|' << setw(51) << left
                << "\t2. Section of Student " << right << '|' << endl
                << '|' << setw(51) << left
                << "\t3. RollNum of Student " << right << '|' << endl;
                cout << setw(60) << setfill('-') << " " << setfill(' ') << endl
                    <<"Enter Choice: ";
                cin >> choice;
                if (choice<0||choice>3)
                    cout<<"Invalid Input.\n";
            }while(choice<0||choice>3);
            if (choice == 3) {
                cin.ignore();
                inputRollNum:
                string newRollNum;
                do{
                    cout << "Enter new Roll Number: ";
                    
                    getline(cin, newRollNum);
                }while(!validateRollNum(newRollNum));

                if (doesStudentExist(studentsFile, newRollNum)) {
                    cout << "RollNum already occupied by another student!" << endl;
                    goto inputRollNum;
                } else {
                    if (students[idx].rollNum == rNum) {
                        students[idx].rollNum = newRollNum;
                        cout << "Roll Number changed succesfully!" << endl;
                    }
                }
            } else if (choice == 2) {
                cin.ignore();
                string newSection;
                do{
                    cout << "Enter New Section Name: ";
                    cin >> newSection;
                }while(!validateSection(newSection));
                if (students[idx].rollNum == rNum) {
                    students[idx].section = newSection;
                    cout << "Section changed sucessfully!" << endl;
                }
            } else if (choice == 1) {
                cin.ignore();
                string revisedName;
                do{
                    cout << "Enter revised Name: ";
                    cin.ignore();
                    getline(cin, revisedName);
                }while(!validateName(revisedName));
                
                if (students[idx].rollNum == rNum) {
                    students[idx].name = revisedName;
                    cout << "Name changed successfully!" << endl;
                }
            }
            cout << "REVISED STUDENT DATA"<< endl;
            calculateGrade(marks, noOfStudents);
            // for printing line
           displayLine();
            // line ends here
            // student data begins here
            displayStudentData(students[idx], marks[markIdx]);
            // student data ends here
            addChangesToStudentFile(studentsFile, students, noOfStudents);
        } else if (choice == 2) {
            cin.ignore();
            beginQuery:
            cout << "Enter Roll Number of student whose data you want deleted: ";
            string rNum;
            getline(cin, rNum);
            if (!validateRollNum(rNum)) {
                cout << "Invalid rollNumber" << endl;
                goto beginQuery;
            }
            if (!doesStudentExist) {
                cout << "Student does not exist!" << endl;
                goto beginQuery;
            } else {
                string quizFile = "quiz.txt";
                string midsFile = "mids.txt";
                string finalsFile = "final.txt";
                deleteFromStudentFile(studentsFile, marksFile, students, marks, noOfStudents, rNum, quizFile, midsFile, finalsFile);
                noOfStudents = loadDataInArray(studentsFile, students);
                loadMarksInArray(marksFile, marks);

                calculateGrade(marks, noOfStudents);

                sortArrays(students, marks, noOfStudents, studentsFile, marksFile, quizFile, midsFile, finalsFile);
                displayLine();
                int idx, markIdx;
                for (int i = 0; i < noOfStudents; i++) {
                    displayStudentData(students[i], marks[i]);
                }
            }
        }
    } else if (choice == 2) {
        cin.ignore();
        changeQuery:
        cout << "Enter Roll Number of student whose marks you want to change: ";
        string rNum;
        getline(cin, rNum);
        if (!validateRollNum(rNum)) {
            cout << "Invalid rollNumber" << endl;
            goto changeQuery;
        }
        if (!doesStudentExist(studentsFile, rNum)) {
            cout << "Student does not exist!" << endl;
            goto changeQuery;
        }
        
        int idx;
        for (int i = 0; i < noOfStudents; i++) {
            if (marks[i].rollNum == rNum) {
                idx = i;
            }
        } 
        int input;
        do{
            cout << "Select what you want to change" << endl;
            cout << setw(60) << setfill('-') << " " << setfill(' ') << endl;
            cout << '|' << setw(51) << left
            << "\t1. Quiz marks" << right << '|' << endl
            << '|' << setw(51) << left
            <<  "\t2. Mids marks" << right << '|' << endl
            << '|' << setw(51) << left
            << "\t3. Final marks" << right << '|' << endl;
            cout << setw(60) << setfill('-') << " " << setfill(' ') << endl
                <<"Enter choice: ";
            cin >> input;
            if (input<0||input>3)
                cout<<"Invalid Input! \n";
        }while(input<0||input>3);
        if (input == 1) {
                do{
                    cout << "Which quiz?" << endl;
                    cout << setw(60) << setfill('-') << " " << setfill(' ') << endl;
                    cout << '|' << setw(51) << left
                    << "\t1. Quiz 1" << right << '|' << endl
                    << '|' << setw(51) << left
                    << "\t2. Quiz 2" << right << '|' << endl
                    << '|' << setw(51) << left
                    << "\t3. Quiz 3" << right << '|' << endl;
                    cout << setw(60) << setfill('-') << " " << setfill(' ') << endl
                        <<"Enter Choice: ";
                    cin >> input;
                    if (input<0||input>3)
                    cout<<"Invalid Input! \n";
            }while(input<0||input>3);
                cout << "Enter Quiz " << input - 1 << " marks: ";
                int newMarks;
                cin >> newMarks;
                
                marks[idx].quiz[input - 1] = newMarks;
            }
         else if (input == 2) {
            int midNum;
            do{
                cout << "Which Mid?" << endl;
                    cout << setw(60) << setfill('-') << " " << setfill(' ') << endl;
                    cout << '|' << setw(51) << left
                    << "\t1. Mid 1" << right << '|' << endl
                    << '|' << setw(51) << left
                    << "\t2. Mid 2" << right << '|' << endl;
                    cout << setw(60) << setfill('-') << " " << setfill(' ') << endl
                    <<"Enter Choice: ";
                    cin >> midNum;
                if (midNum<0||midNum>2)
                    cout<<"Invalid Input\n";
            }while(midNum<0||midNum>2);
            if (midNum == 1) {
                mid1markscheck:
                cout << "Enter marks of Mid " << midNum << ": ";
                int newMidMarks;
                cin >> newMidMarks;
                if (newMidMarks > 100 || newMidMarks < 0) {
                    cout << "Invalid marks" << endl;
                    goto mid1markscheck;
                }
                marks[idx].m1 = newMidMarks;
            } else if (midNum == 2) {
                mid2markscheck:
                cout << "Enter marks of Mid " << midNum << ": ";
                int newMidMarks;
                cin >> newMidMarks;
                if (newMidMarks > 100 || newMidMarks < 0) {
                    cout << "Invalid marks" << endl;
                    goto mid2markscheck;
                }
                marks[idx].m2 = newMidMarks;
            }
        } else if (input == 3) {
            finalmarkscheck:
            cout << "Enter marks of Final: ";
            int newFinalMarks;
            cin >> newFinalMarks;
            if (newFinalMarks > 100 || newFinalMarks < 0) {
                cout << "Invalid marks" << endl;
                goto finalmarkscheck;
            }
            marks[idx].f = newFinalMarks;
        }
        string quizFile = "quiz.txt";
        string midsFile = "mids.txt";
        string finalsFile = "final.txt";

        calculateGrade(marks, noOfStudents);
        sortArrays(students, marks, noOfStudents, studentsFile, marksFile, quizFile, midsFile, finalsFile);
    }
    string quizFile = "quiz.txt";
    string midsFile = "mids.txt";
    string finalsFile = "final.txt";
    addStudentMarksWithoutPrompting(marksFile, "-1", quizFile, midsFile, finalsFile, marks, noOfStudents);
    
}

void sortArrays(Student students[], MarksStruct marks[], int noOfStudents, string studentsFile, string marksFile, string quizFile, string midsFile, string finalsFile) {
    for (int i = 0; i < noOfStudents - 1; i++) {
        for (int j = 0; j < noOfStudents - i - 1; j++) {
            
            int total_j = marks[j].quiz[0] + marks[j].quiz[1] + marks[j].quiz[2]
                          + marks[j].m1 + marks[j].m2 + marks[j].f;

            int total_next = marks[j+1].quiz[0] + marks[j+1].quiz[1] + marks[j+1].quiz[2]
                             + marks[j+1].m1 + marks[j+1].m2 + marks[j+1].f;

            // Currently sorting in descending order
            if (total_next > total_j) {
                // swapping marks as well to prevent data corruption
                MarksStruct tempMarks = marks[j];
                marks[j] = marks[j+1];
                marks[j+1] = tempMarks;
            }
        }
    }
    for (int i = 0; i < noOfStudents; i++) {
        string rNum = marks[i].rollNum;
        int stIdx;
        for (int j = 0; j < noOfStudents; j++) {
            // find where the student with this rNum is located in the array/file
            if (students[j].rollNum == rNum) {
                stIdx = j;
            }
        }
        // put the student from that index to the index i which is the correct sorted idx
        Student temp = students[i];
        students[i] = students[stIdx];
        students[stIdx] = temp;
        // sorts the student array

    }
    // writes the sorted array to the files
    addStudentMarksWithoutPrompting(marksFile, "-1", quizFile, midsFile, finalsFile, marks, noOfStudents);
    addChangesToStudentFile(studentsFile, students, noOfStudents);
}

void calculateGrade(MarksStruct marks[], int noOfStudents) {
    float p;
    string g;
    for (int i = 0; i < noOfStudents; i++) {
        // calculating total marks each / 100
        int total = marks[i].quiz[0] + marks[i].quiz[1] + marks[i].quiz[2] + 
        marks[i].m1 + marks[i].m2 + marks[i].f;

        // calculating %
        p = (total / 600.0) * 100.0;
        marks[i].percentage = p;

        // grade calculation
        if (p >= 89.99) {
            g = "A+";
        } else if (p >= 84.99 && p < 89.99) {
            g = "A";
        } else if (p >= 79.99 && p < 84.99) {
            g = "B+";
        } else if (p >= 74.99 && p < 79.99) {
            g = "B";
        } else if (p >= 69.99 && p < 74.99) {
            g = "C";
        } else if (p >= 59.99 && p < 69.99) {
            g = "D";
        } else if (p > 50 && p < 59.99) {
            g = "E";
        } else if (p < 50) {
            g = "F";
        }
        marks[i].grade = g;
    }
}
bool validateRollNum(string rollNum){
    if (rollNum.length()!=8){
        cout<<"Roll Number must be 8 digits.(eg. 25L-0123)"<<endl;
        return false;
    }
    for (int i=0;i<2;i++){
        if (!isdigit(rollNum[i])){
            cout<<"Invalid RollNumber, First 2 Characters must be digits (eg.25L-0123)\n";
            return false;
        }
    }
    if (!isupper(rollNum[2])){
        cout<<"Invalid Roll Number, 3rd Character must be an uppercase letter.(eg. 25L-0123)\n";
        return false;
    }
    if (rollNum[3]!='-'){
        cout<<"Invalid Roll Number, 4th Character of the ID must be a hyphen (eg. 25L-0123)\n";
        return false;
    }
    for (int i=4;i<8;i++){
        if (!isdigit(rollNum[i])){
            cout<<"Invalid Roll Number, Characters after the hyphen must be digits.(eg. 25L-0123)\n";
            return false;
        }
    }
    return true;
}
bool validateSection(string section){
    if (section.length()!=6){
        cout<<"Section must be 6 character long (e.g. BCS-1F): \n";
        return false;
    }
    for (int i=0;i<3;i++){
        if (!isupper(section[i])){
            cout<<"Invalid Section. First three characters must be letters (e.g. BCS-1F)\n";
            return false;
        }
    }
    if (section[3]!='-'){
        cout<<"Invalid Section, 4th Character of the ID must be a hyphen (eg. BCS-1F)\n";
        return false;
    }
    if (!isdigit(section[4])){
        cout<<"Invalid Section. 5th charachter must be a digit (e.g. BCS-1F).\n";
        return false;
    }
    if (!isupper(section[5])){
        cout<<"Invalid Section. 6th character must be an uppercase letter (e.g. BCS-1F)\n";
        return false;
    }

    return true;
}
bool validateName(string name) {
    if (name.length() < 3) {
        cout << "Invalid, Name is too short (Minimum 3 characters).\n";
        return false;
    }
    for (int i = 0; i < name.length(); i++) {
        if (i == 0 && name[i] == ' ') {
             cout << "Invalid, Name cannot start with a space.\n";
             return false;
        }
        if (!isalpha(name[i]) && name[i] != ' ') {
            cout << "Invalid character '" << name[i] << "'. Names must contain alphabets only.\n";
            return false;
        }
    }
    return true;
}