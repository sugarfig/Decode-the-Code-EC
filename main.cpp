//Author: Erica Carballo
//Project name: Decode the Code
//Description: Game that allows the user to attempt to decode a given message.
//Last Changed: August 30, 2020

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int ROW_SIZE = 13, COL_SIZE = 2;

void openFile(ifstream& messagesFile);
//Will open the input files.
//Input is the input file.

void fillVectorCodedMessages(ifstream& messagesFile, vector<string>& messagesVector);
//Will fill a vector with coded messages from the file.
//Input is the file and empty vector.

void displayCodedMessage(vector<string> messagesVector, int index);
//Will display the coded message.
//Input is the messages vector.

void displayMenu();
//Will display the menu options.

void getUserInput(string& userInput);
//Will get user input.
//Input will be user input.

string makeUpper(const string& s);
//Will make string upper case.
//Input is string.

bool checkInput(string userInput);
//Will validate user input.
//Input is the user input.
//Output is boolean that says if user input is valid or not.

void checkForMenuChar(string userInput, vector<string> messagesVector, int& index, bool& decodedMessageValid);
//Will check if user chose something from the menu or attempted to decode the message.
//Input is the user input and coded message.

void choiceOne();
//Will display the hint to decode the message.

void choiceTwo(vector<string> messagesVector, int& index);
//Will give a new message to decode.
//Input is the message.

void choiceThree(vector<string> messagesVector, int index);
//Will decode the message and display decoded message to the user.
//Input is the message.
//Output is the decoded message.

void choiceFour();
//Quits the program.

char decodeMessage(char alph);
//Will decode character.
//Input is coded character.
//Output is decoded character.

int main()
{
    ifstream messagesFile;
    vector<string> messagesVector;
    int index;
    string userInput;
    bool decodedMessageValid;

    index = 0;

    cout << "Decode the message:" << endl << endl;

    openFile(messagesFile);
    fillVectorCodedMessages(messagesFile, messagesVector);
    messagesFile.close();

    //TEST TO SEE IF VECTOR WORKS.
    /*for (int index = 0; index < messagesVector.size(); index++)
    {
      cout << messagesVector[index] << endl;
    }*/

    displayCodedMessage(messagesVector, index);
    displayMenu();
    getUserInput(userInput);
    checkForMenuChar(userInput, messagesVector, index, decodedMessageValid);

    while (!decodedMessageValid)
    {
        cout << "You have not decoded the message.\n\n";
        displayMenu();
        getUserInput(userInput);
        checkForMenuChar(userInput, messagesVector, index, decodedMessageValid);
    }

    if (decodedMessageValid)
    {
        cout << "Congratulations ! You have decoded the message successfully !\n";
    }


    cout << "Thank you for playing.\n\n"
         << "This is the end of the program.\n";

    return 0;
}

void openFile(ifstream& messagesFile)
{
    messagesFile.open("Messages.txt");
    if (messagesFile.fail())
    {
        cout << "The Messages.txt file failed to open.";
        exit(1);
    }
}

void fillVectorCodedMessages(ifstream& messagesFile, vector<string>& messagesVector)
{
    string temp;

    while(!messagesFile.eof())
    {
        getline(messagesFile, temp);
        messagesVector.push_back(temp);
    }
}

void displayCodedMessage(vector<string> messagesVector, int index)
{
    cout << messagesVector[index] << endl << endl;
}

void displayMenu()
{
    cout << "Press 1 if you would like a hint." << endl
         << "Press 2 if you would like a new message." << endl
         << "Press 3 if you would like the answer to this message." << endl
         << "Press 4 if you would like to quit the program.\n" << endl;
}

void getUserInput(string& userInput)
{
    bool valid;

    getline(cin, userInput);
    userInput = makeUpper(userInput);

    valid = checkInput(userInput);

    while(!valid)
    {
        cout << "Invalid input. Please decode the message or choose\n"
             << "an option from the menu: ";
        getline(cin, userInput);
        userInput = makeUpper(userInput);
        cout << userInput;
        valid = checkInput(userInput);
    }
}
//Author: Erica Carballo
string makeUpper(const string& s) //will make string upper case.
{
    string temp;
    temp = s;

    for(int i = 0; i < s.length( ); i++)
    {
        temp[i] = toupper(s[i]);
    }

    return temp;
}

bool checkInput(string userInput)
{
    bool valid;
    valid = true;

    for (int i = 0; i < userInput.length(); i++) // Goes through each character inputted and checks if it is valid input.
    {
        if (((userInput.at(i) > '4') && (userInput.at(i) < 'A')) || ((userInput.at(i) <= '0') && (userInput.at(i) != ' ')))
        {
            valid = false;
            break;
        }
        else
        {
            valid = true;
        }
    }

    return valid;
}

void checkForMenuChar(string userInput, vector<string> messagesVector, int& index, bool& decodedMessageValid)
{
    char userChoice;
    char decodedAlph, userAlph;
    decodedMessageValid = false;
    string message;
    message = messagesVector[index];

    for (int i = 0; i < userInput.length(); i++)
    {
        if ((userInput.at(i) <= '4') && (userInput.at(i) > '0'))
        {
            userChoice = userInput.at(i);
            switch (userChoice)
            {
                case '1':
                    choiceOne();
                    break;
                case '2':
                    choiceTwo(messagesVector, index);
                    break;
                case '3':
                    choiceThree(messagesVector, index);
                    break;
                case '4':
                    choiceFour();
                    break;
            }
            decodedMessageValid = false;
        }
        else
        {
            userAlph = userInput.at(i);
            decodedAlph = decodeMessage(message.at(i));

            if (userAlph == decodedAlph)
            {
                decodedMessageValid = true;
            }
            else
            {
                decodedMessageValid = false;
            }
        }
    }
}

void choiceOne()
{
    char hint[ROW_SIZE][COL_SIZE], alph, alph2;
    int cols;
    alph = 'A';
    alph2 = 'Z';
    cols = 1;

    cout << "You found a key to decode the message!\n"
         << "Your hint is:\n";

    for (int rows = 0; rows < ROW_SIZE; rows++)
    {
        while(cols < COL_SIZE)
        {
            hint[rows][cols] = alph;
            cout << hint[rows][cols] << " = ";
            cols++;
            hint[rows][cols] = alph2;
            cout << hint[rows][cols] << endl;
        }
        alph++;
        alph2--;
        cols = 1;

    }

}

void choiceTwo(vector<string> messagesVector, int& index)
{
    cout << "Your new message to decode is:\n";
    index++;
    displayCodedMessage(messagesVector, index);
}

void choiceThree(vector<string> messagesVector, int index)
{
    char newAlph;
    string message;
    message = messagesVector[index];

    for (int i = 0; i < message.length(); i++)
    {
        newAlph = decodeMessage(message.at(i));
        cout << newAlph;
    }
    cout << endl << endl;
}

void choiceFour()
{
    cout << "\nThank you for playing.\n\n"
         << "This is the end of the program.\n";
    exit(1);
}

char decodeMessage(char alph)
{
    char newAlph;

    switch(alph)
    {
        case 'A':
            newAlph = 'Z';
            break;
        case 'B':
            newAlph = 'Y';
            break;
        case 'C':
            newAlph = 'X';
            break;
        case 'D':
            newAlph = 'W';
            break;
        case 'E':
            newAlph = 'V';
            break;
        case 'F':
            newAlph = 'U';
            break;
        case 'G':
            newAlph = 'T';
            break;
        case 'H':
            newAlph = 'S';
            break;
        case 'I':
            newAlph = 'R';
            break;
        case 'J':
            newAlph = 'Q';
            break;
        case 'K':
            newAlph = 'P';
            break;
        case 'L':
            newAlph = 'O';
            break;
        case 'M':
            newAlph = 'N';
            break;
        case 'N':
            newAlph = 'M';
            break;
        case 'O':
            newAlph = 'L';
            break;
        case 'P':
            newAlph = 'K';
            break;
        case 'Q':
            newAlph = 'J';
            break;
        case 'R':
            newAlph = 'I';
            break;
        case 'S':
            newAlph = 'H';
            break;
        case 'T':
            newAlph = 'G';
            break;
        case 'U':
            newAlph = 'F';
            break;
        case 'V':
            newAlph = 'E';
            break;
        case 'W':
            newAlph = 'D';
            break;
        case 'X':
            newAlph = 'C';
            break;
        case 'Y':
            newAlph = 'B';
            break;
        case 'Z':
            newAlph = 'A';
            break;
        default:
            newAlph = ' ';
            break;
    }

    return newAlph;
}

/*Sample Dialogue
Decode the message:

GSV ORKH GSV GVVGS GSV GRK LU GSV GLMTFV

Press 1 if you would like a hint.
Press 2 if you would like a new message.
Press 3 if you would like the answer to this message.
Press 4 if you would like to quit the program.

1
You found a key to decode the message!
Your hint is:
A = Z
B = Y
C = X
D = W
E = V
F = U
G = T
H = S
I = R
J = Q
K = P
L = O
M = N
You have not decoded the message.

Press 1 if you would like a hint.
Press 2 if you would like a new message.
Press 3 if you would like the answer to this message.
Press 4 if you would like to quit the program.

2
Your new message to decode is:
RIRHS DIRHG DZGXS

You have not decoded the message.

Press 1 if you would like a hint.
Press 2 if you would like a new message.
Press 3 if you would like the answer to this message.
Press 4 if you would like to quit the program.

irish wrist watch
Congratulations ! You have decoded the message successfully !
Thank you for playing.

This is the end of the program.*/
