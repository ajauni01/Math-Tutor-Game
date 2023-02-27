#include <vector> //for generating string
/*
The using namespace std; statement tells the compiler to make all the names
from the std namespace available in the current scope, so that one don't have
to qualify the names with the std:: prefix every time.
*/
using namespace std;
// header guard
#ifndef MATHTUTOR_H
#define MATHTUTOR_H
// all the prototypes for all the functions
// Display the header & features using the displayGameHeader() function
void DisPlayGameHeader();
// Greet the user
void GreetUser();
// Non - integer data handler & user input
int GetNumericValue();
// prompt the user to make a choice
int UserChoice();
// Create questions function and return leftRandNum, Choice, & rightRandNum
vector<int> CreateQuestions(int choice);
// correct answer function
int GetCorrectAnswer(const vector<int> &rowNum);
// generates questions
void AskMathQuestions(int choice, vector<vector<int>> &mathQuestions);
// displays the whole report
void DisplayStatusReport(const vector<vector<int>> &mathQuestions);
// Saves current game to a text filr
void SaveCurrentGame(const vector<vector<int>> &mathQuestions);
// load previous game after saving it first
void LoadPreviousGame(vector<vector<int>> mathQuestions);
#endif // end of header guard