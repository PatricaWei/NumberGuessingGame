// NumberGame_v5.cpp

#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

static int hostNum = 0;

class GamePlayer
{
private:
   static const int WINNING_PRICE = 5000000;
   static const int TICKET_PRICE = 100000;
   static const int MAX_NUM = 1000000;
   int ticketCount;
   int numToTry;
   string operatorPhrase;

   int winningPrice = WINNING_PRICE;
   int ticketPrice = TICKET_PRICE;

public:
   GamePlayer();
   bool setTicketCount(int num);
   bool setNumToTry(int num);
   bool setOperatorPhrase(string operatorPhrase);

   int getTicketCount();
   int getNumToTry();
   string getOperatorPhrase();
   void decreaseTicketCount();

   void askQuestion();

};

class GamePlayerUtilities
{
public:
   static string getOperationKey(string str);
   static int extractIntStr(string const & str);

private:
   static bool containSubStr(string str, string keyWord);
};

void playGame(int sortedArray[], int first, int last,
              int hostKey, GamePlayer player)
{
   int playerKey = player.getNumToTry();
   string operation = player.getOperatorPhrase();

   if (first > last)
   {
      cout << "Game is over. You lost." << endl << endl;
      return;
   }
   if (player.getTicketCount() < 0) // ticket is decresed before reaches here
   {
      cout << "You run out of ticket to play. You lost." << endl << endl;
      return;
   }

   if (hostKey == sortedArray[playerKey])
   {
      cout << "\n   Congratulations! You win!!!!   "  << endl;
      cout << "   You Have Earned 5 Million Dollars!" << endl;
      cout << "   Number of ticket left: "
      << to_string(player.getTicketCount()) << endl << endl;
   }
   else if (hostKey < sortedArray[playerKey])
   {
      if (operation.compare("great") == 0)
      {
         cout << "No. " << endl;
      }
      else if (operation.compare("less") == 0)
      {
         cout << "Yes. " << endl;
      }
      else
         cout << "No." << endl;

      player.askQuestion();
      player.decreaseTicketCount();

      playGame(sortedArray, first, playerKey - 1, hostKey, player);
   }
   else
   {
      if (operation.compare("less") == 0)
      {
         cout << "No. " << endl;
      }
      else if (operation.compare("great") == 0)
      {
         cout << "Yes. " << endl;
      }
      else
         cout << "No." << endl;

      player.askQuestion();
      player.decreaseTicketCount();

      playGame(sortedArray, playerKey + 1, last, hostKey, player);
   }
}

void fillArray(int array[], int size)
{
   for (int i = 0; i < size; i++)
   {
      array[i] = i;
   }
}

int main(int argc, const char * argv[])
{
   int *sortedNumArray;
   int const LENGTH = 1000000;
   sortedNumArray = new int[LENGTH];
   fillArray(sortedNumArray, LENGTH);

   GamePlayer player;

   // generate a number in [0, 1000000]
   hostNum = rand() % (LENGTH + 1);
   cout << "A number is selected for you to guess. ";
   cout << "You may start the game now. \n" << endl;

   player.askQuestion();
   player.decreaseTicketCount();

   playGame(sortedNumArray, 0, LENGTH, hostNum, player);
}


GamePlayer::GamePlayer()
{
   string numOfTicketStr;
   int    numOfTicket;

   do
   {
      cout << "\nPurchase your ticket before playing the game." << endl;
      cout << "\nHow many ticket you like to buy?" << endl;
      getline(cin, numOfTicketStr);
      istringstream(numOfTicketStr) >> numOfTicket;

   } while (!setTicketCount(numOfTicket));

   int ticketExpenseInt = numOfTicket * TICKET_PRICE;
   string ticketExpenseStr = to_string(ticketExpenseInt);

   cout << "You have spent $" << ticketExpenseStr << " for " << numOfTicketStr
   << " tickets. " << endl << endl;
}

bool GamePlayer::setTicketCount(int num)
{
   if (num < 0 || num > WINNING_PRICE / TICKET_PRICE)
      return false;
   this->ticketCount = num;
   return true;
}
bool GamePlayer::setNumToTry(int num)
{
   if (num < 0 || num > MAX_NUM)
      return false;
   this->numToTry = num;
   return true;
}
bool GamePlayer::setOperatorPhrase(string operatorPhrase)
{
   if (operatorPhrase.compare("great") == 0 ||
       operatorPhrase.compare("big") == 0 ||
       operatorPhrase.compare("less") == 0 ||
       operatorPhrase.compare("small") == 0)
   {
      this->operatorPhrase = operatorPhrase;
      return true;
   }
   else
   {
      return false;
   }

}

int GamePlayer::getTicketCount()
{
   return ticketCount;
}
int GamePlayer::getNumToTry()
{
   return numToTry;
}
string GamePlayer::getOperatorPhrase()
{
   return operatorPhrase;
}

bool GamePlayerUtilities::containSubStr(string str, string keyWord)
{
   transform(str.begin(), str.end(), str.begin(), ::tolower);

   return (str.find(keyWord) != string::npos);
}


string GamePlayerUtilities::getOperationKey(string str)
{
   string operationKey = "";

   if (containSubStr(str, "great") || containSubStr(str, "big"))
      return "great";
   else if (containSubStr(str, "less") || containSubStr(str, "small"))
      return "less";
   else
      return "";
}

int GamePlayerUtilities::extractIntStr(string const & str)
{
   size_t const n = str.find_first_of("0123456789");
   string numStr;
   int playerNumInt;

   if (n != string::npos)
   {
      size_t const m = str.find_first_not_of("0123456789", n);
      numStr = str.substr(n, m != string::npos ? m - n : m);
      istringstream(numStr) >> playerNumInt;
      return playerNumInt;
   }
   return -1;
}

void GamePlayer::askQuestion()
{
   string playerQuestionStr = "";

   cout << "Ask a question, please." << endl;
   getline(cin, playerQuestionStr);

   int numberToTry =
   GamePlayerUtilities::extractIntStr(playerQuestionStr);
   string comparisionWord =
   GamePlayerUtilities::getOperationKey(playerQuestionStr);

   setNumToTry(numberToTry);
   setOperatorPhrase(comparisionWord);
}

void GamePlayer::decreaseTicketCount()
{
   this->ticketCount--;
}


/*-------The Reason Why I Choose to Play This Game  --------------------------

 As a player, I accept the rules of the game and choose to play it.

 Since I know the number I am guessing is between 0 to one million, if I try
 it sequencially, the worst case will take me one million and one tries to
 find that number. However, if I ask smart questions and adjust my choices
 accordingly, it will take me at most 20 tries to find it. 

 I will put the one million and one numbers into an sorted array. Each time
 I am going to pick the median number from that array and ask this question:
 "Is that number greater than 'the median'"? Depends on the "Yes or No" answer,
 I will throw away half of the numbers and keep the other half as the new input.
 Then I will find the median of this list and ask question again. It will take
 me at most 20 tries to narrow down the list into one number. 
 
 This is because one million is roughly 2^20.
 
 If I am lucky, one of the median I pick is that number, then I am done.
 So, I am guaranteed to win if I buy 20 tickets.

 I spent $2,000,000 and guaranted to earn $5,000,000 back. It is worth doing.

 -----------------------------------------------------------------------------*/


/*-----------------------      OUTPUT       ----------------------------

 Purchase your ticket before playing the game.

 How many ticket you like to buy?
 20
 You have spent $2000000 for 20 tickets.

 A number is selected for you to guess. You may start the game now.

 Ask a question, please.
 is it greater than 500000?
 No.
 Ask a question, please.
 is it greater than 250000?
 No.
 Ask a question, please.
 is it greater than 125000?
 No.
 Ask a question, please.
 is it greater 62500?
 No.
 Ask a question, please.
 is it great than 31250?
 No.
 Ask a question, please.
 is it great than 15625?
 No.
 Ask a question, please.
 is it great than 7813?
 No.
 Ask a question, please.
 is it great than 3907?
 No.
 Ask a question, please.
 is it great than 1954?
 No.
 Ask a question, please.
 is it great than 977?
 No.
 Ask a question, please.
 is it great than 489?
 No.
 Ask a question, please.
 is it great than 245?
 No.
 Ask a question, please.
 is it great than 123?
 No.
 Ask a question, please.
 is it great than 62?
 No.
 Ask a question, please.
 is it great than 31?
 Yes.
 Ask a question, please.
 is it great than 46?
 No.
 Ask a question, please.
 is it great than 38?
 Yes.
 Ask a question, please.
 is it great than 42?
 No.
 Ask a question, please.
 is it great than 40?
 Yes.
 Ask a question, please.
 it is 41.

 Congratulations! You win!!!!
 You Have Earned 5 Million Dollars!
 Number of ticket left: 0
 
 Press any key to continue . . .
 ------------------------------------------------------------------------*/
