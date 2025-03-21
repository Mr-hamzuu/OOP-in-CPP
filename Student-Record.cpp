#include <iostream>
#include <fstream>
using namespace std;

class Data
{
    int id, age;
    string name, depart;
    float gpa;

public:
    void addstudent()
    {
        ofstream onfile;
        onfile.open("Details.txt", ios::app);
        cout << "Id : ";
        cin >> id;
        cout << "Name : ";
        cin.ignore();
        getline(cin, name);
        cout << "Department : ";
        getline(cin, depart);
        cout << "Gpa : ";
        cin >> gpa;
        onfile << id << "|" << name << "|" << depart << "|" << gpa << endl;
        onfile.close();
    }
    void Display() const
    {
        ifstream infile;
        int i;
        float g;
        string n, d;

        infile.open("Details.txt");
        while (infile >> i)
        {
            infile.ignore();
            getline(infile, n, '|');
            getline(infile, d, '|');
            infile >> g;
            infile.ignore();
            cout << "ID : " << i << " | " << "Name : " << n << " | " << "Department : " << d << " | " << "GPA : " << g << endl;
        }
        infile.close();
    }
    void search(int id)
    {
        if (this->id == id)
        {
            cout << "Id : " << this->id << endl;
            cout << "Name : " << name << endl;
            cout << "Department : " << depart << endl;
            cout << "Gpa" << gpa << endl;
        }
    }
    void update(int searchID)
    {
        ifstream infile("Details.txt"); 
        ofstream newfile("student.txt"); 

        if (!infile || !newfile)
        {
            cout << "Error in file opening" << endl;
            return;
        }

        int fileID;
        string fileName, fileDept;
        float fileGPA;
        bool found = false;

        while (infile >> fileID)
        {
            infile.ignore();
            getline(infile, fileName, '|');
            getline(infile, fileDept, '|');
            infile >> fileGPA;
            infile.ignore();

            if (fileID == searchID)
            {
                found = true;
                cout << "Enter new details for ID " << searchID << endl;
                cout << "New Name: ";
                cin.ignore(); 
                getline(cin, fileName);
                cout << "New Department: ";
                getline(cin, fileDept);
                cout << "New GPA: ";
                cin >> fileGPA;
            }

            newfile << fileID << "|" << fileName << "|" << fileDept << "|" << fileGPA << endl;
        }

        infile.close();
        newfile.close();

        remove("Details.txt");
        rename("student.txt", "Details.txt");

        if (found)
            cout << "Record successfully updated!" << endl;
        else
            cout << "Student not found!" << endl;
    }

    void Delete(string id)
    {
        ofstream newfile;
        newfile.open("student.txt");
        ifstream infile("Details.txt");
        string i, n, d, g;
        bool found = false;
        if (!newfile || !infile)
        {
            cout << "Error in file opening" << endl;
        }
        else
        {
            while (getline(infile, i, '|') && getline(infile, n, '|') && getline(infile, d, '|') && getline(infile, g, '|'))
            {
                if (id != i)
                {
                    newfile << i << " | " << n << " | " << d << " | " << g << endl;
                }
                else
                {
                    found = true;
                }
            }
        }
        infile.close();
        newfile.close();
        remove("Details.txt");
        rename("student.txt", "Details.txt");
        if (found)
        {
            cout << "Record is sucessfully deleted" << endl;
        }
        else
        {
            cout << "Student is not found\n";
        }
    }
};
class student
{
    Data s[50];
    int count;

public:
    student()
    {
        count = 0;
    }

    void add()
    {
        if (count >= 50)
        {
            cout << "Database is Full" << endl;
        }
        else
        {
            s[count].addstudent();
            count++;
        }
    }
    void show()
    {
        s[0].Display();
    }
    void search()
    {
        int id;
        cout << "Enter id : ";
        cin >> id;
        for (int i = 0; i < count; i++)
        {
            s[i].search(id);
        }
    }
    void update()
    {
        int id;
        cout << "Enter student id you want to update the data : ";
        cin >> id;
        s[0].update(id);
    }
    void Delete()
    {
        string id;
        cout << "Enter id : ";
        cin >> id;
        for (int i = 0; i < count; i++)
        {
            s[i].Delete(id);
        }
    }
};
int main()
{
    student s;
    int choice;
    while (true)
    {
        cout << "1.Add student\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Exit\nEnter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            s.add();
            break;
        case 2:
            s.show();
            break;
        case 3:
            s.search();
            break;
        case 4:
            s.update();
            break;
        case 5:
            s.Delete();
            break;
        case 6:
            exit(1);
            break;

        default:
            break;
        }
    }

    return 0;
}
