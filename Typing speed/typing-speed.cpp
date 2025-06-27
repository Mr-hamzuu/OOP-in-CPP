#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstring>
using namespace std;

class filing {
protected:
    char sentence[90];

public:
    filing() {
        sentence[0] = '\0'; 
    }

    void loadsentance(string file) {
        ifstream infile(file, ios::binary);
        if (!infile) {
            cout << "Error opening file for reading.\n";
            return;
        }


        infile.seekg(0, ios::end);
        int filesize = infile.tellg();
        int total = filesize / 90;
        if (total == 0) {
            cout << "No sentence found in file.\n";
            return;
        }

        srand(time(NULL));
        int index = rand() % total;

        infile.seekg(index * 90, ios::beg);
        infile.read((char*)sentence, sizeof(sentence));
        sentence[89] = '\0';

        infile.close();
    }


};

class typing : public filing
{
    string userinput;
    double timetaken;
    int correct, incorrect;
    int charcount;
    int wordscount;
    double speed;
    double Accuracy;

public:
    typing() : userinput(""), timetaken(0.0), correct(0), charcount(0), wordscount(1), speed(0.0), Accuracy(0.0), incorrect(0) {}

    void input(string file)
    {
        loadsentance(file);
        time_t start;
        time_t end;

        cout << "Sentance : \033[1;33m" << sentence << "\033[0m" << endl;
        start = time(0);
        cin.ignore();
        getline(cin, userinput);
        end = time(0);
        timetaken = difftime(end, start);
        charcount = userinput.length();
    }
    void compare()
    {
        correct = 0;
        incorrect = 0;
        wordscount = 0;
        for (int i = 0; i < userinput.length() && i < strlen(sentence); i++)
        {
            if (userinput[i] == sentence[i])
            {
                correct++;
            }
            else
            {
                incorrect++;
            }
            if (userinput[i] == ' ')
            {
                wordscount++;
            }
        }
        speed = (charcount / timetaken) * 60;

        Accuracy = (double(correct) / double(strlen(sentence))) * 100;
    }
    void display() const
    {
        cout << "\033[1;32m-----------------------------------------------------------------" << endl;
        cout << setw(40) << "PERFORMANCE SUMMARY" << endl;
        cout << "-----------------------------------------------------------------\033[0m" << endl;
        cout << "\033[1;37mSentance : " << sentence << endl;
        cout << "Your Input : " << userinput << endl;
        cout << "Character Typed : " << charcount << endl;
        cout << "Words Typed : " << wordscount << endl;
        cout << "Typing Speed : " << speed << " character/min" << endl;
        cout << "Accuracy : " << Accuracy << "%" << endl;
        cout << "Correct : " << correct << endl;
        cout << "\033[1;31mMistakes : " << incorrect << "\033[0m" << endl;
    }
};

void option1()
{
    int choice;
    char c;
    typing t;
    do
    {

        cout << "\033[1;36m-----------------------------------------------------------------" << endl;
        cout << setw(50) << "SELECT TYPING TEST DIFFICULTY" << endl;
        cout << "-----------------------------------------------------------------\033[0m" << endl;
        cout << "\033[1;33m1. Easy     (Short, simple sentences) " << endl;
        cout << "2. Medium   (Moderate length and vocabulary) " << endl;
        cout << "3. Hard     (Long, complex, punctuation-heavy sentences)\033[0m" << endl;
        cout << "\033[1;31m4. Exit\033[0m" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");

            t.input("easy.bin");
            t.compare();
            t.display();
            break;
        case 2:
            system("cls");
            t.input("medium.bin");
            t.compare();
            t.display();
            break;
        case 3:
            system("cls");
            t.input("hard.bin");
            t.compare();
            t.display();
            break;
        case 4:
            exit(1);
        default:
            break;
        }
        cout << "\033[1;36mDo you want to continue (Y/N)\033[0m" << endl;
        cin >> c;
    } while (c == 'Y' || c == 'y');
}

void option2()
{
    cout << "\033[1;32m------------------- INSTRUCTIONS -------------------" << endl;
    cout << "\033[1;35m1. A sentence will appear on the screen." << endl;
    cout << "2. Type the sentence exactly as shown and press Enter." << endl;
    cout << "3. Your typing speed and accuracy will be calculated." << endl;
    cout << "4. Try to minimize mistakes for better results." << endl;
    cout << "\033[1;32m----------------------------------------------------\033[0m" << endl;
    cout << "Press Enter to return to the main menu..." << endl;
}
int main()
{
    while (true)
    {

        int choice;
        cout << "\033[1;32m-----------------------------------------------------------------" << endl;
        cout << setw(50) << "\033[1;32mTYPING SPEED TEST" << endl;
        cout << "-----------------------------------------------------------------\033[0m" << endl;
        cout << "\033[1;37m1. Start Typing Test " << endl;
        cout << "2. View Instruction " << endl;
        cout << "\033[1;31m3. Exit \033[0m" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            option1();
            break;
        case 2:

            option2();
            getchar();
            break;
        case 3:
            exit(1);
        default:
            cout << "Invalid option " << endl;
            break;
        }
    }

 
    return 0;
}



// | ANSI Code    | Color          | Example Output                     |
// | ------------ | -------------- | ---------------------------------- |
// | `\033[1;30m` | Gray / Black   | `cout << "\033[1;30mText\033[0m";` |
// | `\033[1;31m` | Red            | `cout << "\033[1;31mText\033[0m";` |
// | `\033[1;32m` | Green          | `cout << "\033[1;32mText\033[0m";` |
// | `\033[1;33m` | Yellow         | `cout << "\033[1;33mText\033[0m";` |
// | `\033[1;34m` | Blue           | `cout << "\033[1;34mText\033[0m";` |
// | `\033[1;35m` | Magenta        | `cout << "\033[1;35mText\033[0m";` |
// | `\033[1;36m` | Cyan           | `cout << "\033[1;36mText\033[0m";` |
// | `\033[1;37m` | White (Bright) | `cout << "\033[1;37mText\033[0m";` |
// | `\033[0m`    | Reset          | `cout << "\033[0mText";`           |











// int main() {
//     const char* sentences[] = {
//         "Always be honest in your words.",
//         "The quick brown fox jumps over the lazy dog.",
//         "Practice typing every day to improve.",
//         "Computers can be fun to use for learning.",
//         "He walked across the park to get home.",
//         "Reading books helps expand your mind.",
//         "The keyboard is an essential tool for writing.",
//         "She quickly typed the answer before time ran out.",
//         "Good habits lead to a successful life.",
//         "Learning a new skill takes time and effort."
//     };

//     ofstream out("medium.bin", ios::binary);
//     if (!out) {
//         cout << "Failed to open file.\n";
//         return 1;
//     }

//     for (int i = 0; i < 10; i++) {
//         char buffer[90] = {0}; 
//         strncpy(buffer, sentences[i], 89);
//         out.write(buffer, 90); // Write fixed block
//     }

//     out.close();
//     cout << "easy.bin created successfully with fixed-size records.\n";
//     return 0;
// }