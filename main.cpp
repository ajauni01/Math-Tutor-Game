/*
Program : Math Tutor
Programmer : Ajharul Islam Aunik
*/
#include "mathTutor.h" // header file
#include <iostream>    // for basic inputs and outputs
#include <stdexcept>   // // If an error occurs, throw an exception
#include <string>      //for generating string
#include <vector>      // this preprocessor directive tells the compiler to include the contents of the<vector>

using namespace std;
// main function
int main()
{
  int option;                    // store user's input
  string garbageCollector = "?"; // to get anything still in the input buffer
  vector<vector<int>>
      mathQuestions; // 2D vector to store game information//DEBBIE: blank
  // line after this; also srand should be done here too
  DisPlayGameHeader(); // display the math tutor banner
  GreetUser();         // welcomes the user
  // Process the user choice using while loop
  while ((option = UserChoice()))
  {
    switch (option)
    {
    case 1: // addition
    case 2: // subtraction
    case 3: // multiplication
    case 4: // division
      // call the AskMathQuestions function while passing the option and 2D
      // vector mathQuestions arguments
      AskMathQuestions(option - 1, mathQuestions);
      break;
    case 5:
      DisplayStatusReport(
          mathQuestions); // call the DisplayStatusReport function and pass the
      // 2D vector argument
      break;
    case 6:
      try
      {
        SaveCurrentGame(mathQuestions); //// call the SaveCurrentGame function
        /// and pass the 2D vector argument
      }
      catch (
          runtime_error &excpt)
      { // catch the run time error for any exception
        cout << endl;
        cout << excpt.what() << endl; // show the exception to the user
        cout << "Program did NOT end normally: Error -4" << endl;
        return -4;
      }
      break;
    case 7:
      try
      {
        LoadPreviousGame(mathQuestions); // call the loadPreviousGame function
        // and pass the 2D vector argument
      }
      catch (
          runtime_error &excpt)
      { // catch the run time error for any exception
        cout << endl;
        cout << excpt.what() << endl; // show the exception to the user
        cout << "Program did NOT end normally: Error -4" << endl;
        return -4;
      }
      break;
    case 8:
      mathQuestions
          .clear(); // clear the 2D vector elements if the user chooses option 8
      cout << " Game Reset"
           << endl; // Display the Game Reset message to the user
      break;
    default: // to handle any exception
      cout << " INVALID CHOICE " << option << endl;
      cout << " Program ended with an error of -1" << endl;
      cout << " Please contact Ajharul Islam Aunik." << endl;
      return -1;
    }
    cout << endl;
    getline(cin, garbageCollector); // clear anything still in the input buffer
    cout << " Please press the enter key to continue.";
    getline(cin, garbageCollector); // //wait until the user presses a key
    cout << endl;
  }
  cout << endl;
  cout << " SORRY TO SEE YOU GO! GOOD BYE"
       << endl; // if the user choose option zero
  return 0;
} // end of main function