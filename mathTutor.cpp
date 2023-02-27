/*
Program : Math Tutor
Programmer : Ajharul Islam Aunik
Date : 12/15/22
Description : This 'mathTutor.cpp' program file includes all the functions necessary and their detailed operations to execute the main function, resulting in playing the game.
*/
#include <cstdlib>   // seeds the pseudo-random number generator
#include <fstream>   // for using input/output streams
#include <iomanip>   // to manipulate the output
#include <iostream>  // for basic inputs and outputs
#include <limits>    // it defines a numeric_limits class template
#include <stdexcept> // provides standard exception classes
#include <string>    // for storing and manipulating string data
#include <vector>    // allows to create vectors of any data type to store information
// The using namespace std; statement tells the compiler to make all the names
// from the std namespace available in the current scope, so that one don't have
// to qualify the names with the std:: prefix every time.
using namespace std;
// global variables
const int MAX_ATTEMPTS = 3;
enum operatorType
{ // use enumeration to set constant vales for the integers
  ADDITION = 0,
  SUBTRACTION = 1,
  MULTIPLICATION = 2,
  DIVISION = 3
};
enum attempts
{ // use enumeration to set constant vales for the integers
  // //DEBBIE: OH, I now see what you are doing with your ENUM and
  // it's completely acceptible
  FirstAttempt = 1,
  SecondAttempt = 2,
  ThirdAttempt = 3
};
const vector<char> mathOperators = {'+', '-', '*', '/'};
const string FILE_NAME =
    "gameInfo.txt"; // file to display saved current game elements
// Display the header & features using the displayGameHeader() function
void DisPlayGameHeader()
{
  cout << "-------------------------------------------" << endl;
  cout << "| MATH TUTOR |" << endl;
  cout << "! You've come to the right place to CHILL !" << endl;
  cout << " ------------------------------------------ " << endl;
  return;
}
// Greet the user
// to read by formating them like I did mine
void GreetUser()
{
  string userName = "?"; // string variable to store the user name
  cout << endl;
  cout << " PLEASE ENTER YOUR NAME: "; // prompt the user to input his
  // name
  getline(cin, userName); // get the user name
  cout << " Welcome " << userName << "!" << endl
       << endl; // welcome the user
  return;
} // end of GreetUser function
// Non - integer data handler & gets user answer to a question
int GetNumericValue()
{
  int userInput = 0;
  while (!(cin >> userInput))
  {              // User choice validation
    cin.clear(); // clear the error flag on cin
    cin.ignore(numeric_limits<streamsize>::max(),
               '\n'); // ignore the max input, up to '\n'
    // Prompt the user to enter an integer if an input is a non-integer
    cout << " Invalid input. Please enter a number: ";
  } // end of while loop
  return userInput;
} // end of data getNumericValue() function
// function to show the menu to the user and prompts him/her to make a choice
int UserChoice()
{
  int choice = 0; // store user's choice
  cout << " Alright!Let's get the fun begin!!!" << endl;
  cout << " You get 3 CHANCES to provide a correct answer! Sounds "
          "Good, Huh?"
       << endl;
  cout << endl;
  // show the game menu to the user
  cout << " ------------";
  cout << " GAME MENU ";
  cout << " ------------" << endl;
  cout << " ---------------------------------------" << endl
       << endl;
  cout << " 1 = (+) ADDITION " << endl;
  cout << " 2 = (-) SUBTRACTION " << endl;
  cout << " 3 = (x) MULTIPLICATION" << endl;
  cout << " 4 = (/) DIVISION " << endl;
  cout << " --------------------------" << endl;
  cout << " 5 = STATUS REPORT " << endl;
  cout << " 6 = SAVE CURRNET GAME " << endl;
  cout << " 7 = LOAD PREVIOUS GAME " << endl;
  cout << " 8 = RESET GAME " << endl;
  cout << " --------------------------" << endl;
  cout << " 0 = QUIT " << endl;
  cout << " --------------------------" << endl
       << endl;
  while (true)
  { // keeps looping until the user chooses a proper option
    // Prompts the user to enter a choice
    cout << " WHAT ARE YOU WAITING FOR? ENTER A CHOICE, BUDDY: ";
    choice = GetNumericValue(); // call the GetNumericValue() function to handle
    // any non integer input & gets the user choice
    if (choice >= 0 && choice <= 8)
      break;
    // Display the error message if the user enters a non-valid choice
    cout << " INVALID INPUT. PLEASE TRY AGAIN" << endl;
    cout << endl;
  }
  return choice; // returns user's chosen option from the menu
}
// Create questions function and return leftRandNum, Choice, & rightRandNum
vector<int> CreateQuestions(int choice)
{
  // Declare the variables
  int leftRandNum = 0;
  int rightRandNum = 0;
  int tempValue = 0; // to temporarily store a value if leftRandNum is less than
  // the rightRandNum
  // Seed random numbers with current time.
  srand(time(0));
  leftRandNum = rand() % 10 + 1;  // to generate a random number from 1 to 10
  rightRandNum = rand() % 10 + 1; // to generate a random number from 1 to 10
  // To make sure that LeftRandNum is always biggger than RightRandNum
  if (leftRandNum < rightRandNum)
  {
    tempValue = leftRandNum;
    leftRandNum = rightRandNum;
    rightRandNum = tempValue;
  }
  if (choice == DIVISION)
  { // to avoid fraction
    leftRandNum *= rightRandNum;
  }
  return {
      leftRandNum, choice,
      rightRandNum}; // return randomly generated leftRandNum, chosen math
                     // operative, randomly generated rightRandNum as a vector
}
// correct answer function
int GetCorrectAnswer(const vector<int> &rowNum)
{
  int correctAnswer = 0;           // store the correct answer
  int leftRandNum = rowNum.at(0);  // get the leftRandNum from the row number
  int operatorType = rowNum.at(1); // get the operatorType from the row number
  int rightRandNum = rowNum.at(2); // get the rightRandNum from the row number
  switch (operatorType)
  {
  case ADDITION:
    correctAnswer = leftRandNum + rightRandNum;
    break;
  case SUBTRACTION:
    correctAnswer = leftRandNum - rightRandNum;
    break;
  case MULTIPLICATION:
    correctAnswer = leftRandNum * rightRandNum;
    break;
  case DIVISION:
    correctAnswer = leftRandNum / rightRandNum;
    break;
  default:
    cout << "Unable to get the correct answer: -2 error code" << endl;
    cout << "Invalid Math Operator Type " << operatorType << endl;
    exit(-2);
  }
  return correctAnswer; // return an integer
}
void AskMathQuestions(int choice, vector<vector<int>> &mathQuestions)
{
  // Store the chosen math operator type
  char operatorType = mathOperators.at(choice);
  int numCorrect = 0;
  int numIncorrect = 0;
  int userAnswer = 0;
  int numQuestions = 0;
  vector<int> rowNum =
      CreateQuestions(choice); // store question elements in the rowNum vector
  int correctAnswer = GetCorrectAnswer(
      rowNum); // get the correct answer by calling the GetCorrectAnswer
  // function & passing the row number as parameter.
  int quesNum = mathQuestions.size() +
                1; // keeps track of the number of questions asked to the user
  for (int j = 1; j <= MAX_ATTEMPTS;
       ++j)
  { // provides the user three opportunities to answer the
    cout << endl;
    cout << " |--------";
    switch (j)
    {
    case FirstAttempt:
      cout << " 1st Attempt";
      break;
    case SecondAttempt:
      cout << " 2nd Attempt";
      break;
    case ThirdAttempt:
      cout << " 3rd Attempt";
      break;
    }
    cout << " ------------|";
    cout << endl
         << endl;
    cout << " #" << quesNum << " WHAT IS " << rowNum.at(0) << operatorType
         << rowNum.at(2) << "?";
    // call the non-integer handler function to verify integer and get the
    // user answer
    userAnswer = GetNumericValue();
    if (userAnswer == correctAnswer)
    {
      rowNum.push_back(
          j); // j refers to the number of attempts needed to give the correct
      // answer. we need this information to show in the status report
      cout << " Awesome! Your answer is correct. Hip hip hurra!" << endl;
      cout << endl;
      break;
    } // end of if block
    else
    {
      cout << " Opps! Your answer is incorrect!" << endl;
      if (j == MAX_ATTEMPTS)
      {
        rowNum.push_back(
            0); // 0 refers to incorrect answers after three attempts
        cout << "The correct answer is " << correctAnswer << endl;
        break;
      }
    } // end of else block
    cout << "You have"
         << " " << MAX_ATTEMPTS - j << " "
         << "attempts left" << endl;
    cout << endl;
  } // end of inner for loop
  mathQuestions.push_back(rowNum);
} // end of ask math questions function
// function to show the current game details to the user
void DisplayStatusReport(const vector<vector<int>> &mathQuestions)
{
  if (mathQuestions.empty())
  { // Use the empty() function to check if the 2D
    // vector contains nothing
    cout << endl;
    cout << " NO INFORMATION TO SHOW!" << endl;
    return; // return to the main menu
  }
  int leftRandNum = 0;
  int operatorRandNum = 0;
  char mathOperator = '?';
  int rightRandNum = 0;
  int correctAnswer = 0;
  int totalAttempt = 0;
  int totalQuestions = mathQuestions.size();
  int countCorrect = 0;
  int countIncorrect = 0;
  int percent = 0;
  vector<int> rowNum;
  cout << endl;
  cout << endl;
  cout << " |--------------"
       << "STATUS REPORT"
       << "-----------------|" << endl;
  cout << endl;
  cout << " QUESTIONS ATTEMPTS" << endl;
  cout << endl;
  for (int i = 0; i < mathQuestions.size(); ++i)
  {
    leftRandNum = mathQuestions.at(i).at(0);
    operatorRandNum = mathQuestions.at(i).at(1);
    char mathOperator = mathOperators.at(operatorRandNum);
    rightRandNum = mathQuestions.at(i).at(2);
    correctAnswer = GetCorrectAnswer(mathQuestions.at(i));
    totalAttempt = mathQuestions.at(i).at(3);
    // print the variables
    cout << setw(10) << right << leftRandNum << " " << mathOperator << " "
         << setw(4) << left << rightRandNum << "=" << setw(3) << right
         << correctAnswer;
    if (totalAttempt == 0)
    {                   // if the user is unable to provide correct answer
      ++countIncorrect; // after three attempts
      cout << " Incorrect" << endl;
    }
    else
    {
      cout << setw(10) << right << totalAttempt << endl;
      ++countCorrect;
    }
  } // end of 2D vector
  // show the summary to the user
  cout << endl;
  cout << endl;
  cout << " ---HERE IS YOUR SUMMARY---" << endl;
  cout << endl;
  // show total questions asked to the user
  cout << " Total Questions Asked : " << totalQuestions << endl;
  // show total correct answer
  cout << " Total Correct Answers : " << countCorrect << endl;
  // show total incorrecr answer
  cout << " Total Incorrect Answers : " << countIncorrect << endl;
  // show total percent of correct answer
  percent = (countCorrect * 100) / totalQuestions;
  cout << " Percentage of Correct Answer : " << percent << "%" << endl;
  cout << endl;
  cout << " |--------------------------------------------|" << endl;
  // end of summary
} // end of display status report function
void SaveCurrentGame(const vector<vector<int>> &mathQuestions)
{
  cout << endl;
  cout << " Saving your game. Please wait...." << endl
       << endl;
  if (mathQuestions.empty())
  { // Use the empty() function to check if the 2D
    // vector contains nothing
    cout << endl;
    cout << " No questions to save!" << endl;
    return; // return to the main menu
  }
  ofstream fileOutput;        // output file stream handler
  fileOutput.open(FILE_NAME); // open the file
  if (!fileOutput
           .is_open())
  { // throw runtime_error if the file cannot be opened
    throw runtime_error("could not open file" + FILE_NAME + " waiting");
  }
  for (int i = 0; i < mathQuestions.size();
       ++i)
  { // run for loop to write extracted information into a text file
    fileOutput << mathQuestions.at(i).at(0) << " " << mathQuestions.at(i).at(1)
               << " " << mathQuestions.at(i).at(2) << " "
               << mathQuestions.at(i).at(3) << endl;
  }
  fileOutput.close(); // close the output file
  cout << " Saved " << mathQuestions.size() << " Questions "
       << " to " << FILE_NAME << endl;
  cout << endl;
  cout << " Game successfully saved!" << endl;
} // end of save current game function
void LoadPreviousGame(vector<vector<int>> mathQuestions)
{
  // In order to load the previous game, the user must choose save the current
  // game (option 6) first, then choose load previous game (option 7).
  // Otherwise, the load previous game function may show the wrong question
  int leftRandNum = 0;
  int mathType = 0;
  int rightRandNum = 0;
  int attempts = 0;
  char operatorType = '?';
  ifstream inPutFile;        // input stream file handle
  mathQuestions.clear();     // make sure vectors are empty before loading the file
  inPutFile.open(FILE_NAME); // open the file
  if (!inPutFile.is_open())
  {
    cout << "No previous game to load!" << endl;
    return;
  }
  // while loop to read information from a file and put them into interger
  // variables
  cout << endl;
  cout << " Loading your previous games. Please wait...." << endl;
  while (inPutFile >> leftRandNum >> mathType >> rightRandNum >> attempts)
  {
    mathQuestions.push_back({leftRandNum, mathType, rightRandNum, attempts});
  }
  if (!inPutFile.eof())
  { // throw run time error if the file cannot be opened
    throw runtime_error("Something went wrong with the file " + FILE_NAME +
                        " file.");
  }
  inPutFile.close(); // close the file
  cout << endl;
  cout << " " << mathQuestions.size() << " questions loaded "
       << " from " << FILE_NAME << endl; // display confirmation to the user
  cout << endl;
  cout << " Previous game loaded successfully!" << endl;
} // end of load previous game function