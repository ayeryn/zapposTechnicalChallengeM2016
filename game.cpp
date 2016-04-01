#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


//Rulebook - check
//1-player game - check
//publisher (github) - check
//multiple levels of difficulty - check

/* Kyle: (Java)Zig-Zag-Zoe wrapped in a story. Someone makes commentary throughout the game.*/
/* Manasa: (HTML and JS) Guess who it is. Get a blurred picture of a person and get points if answered it right*/
/*Kishan: (C#) Roll a ball: roll a ball into objects and get points if pick up objects */

string eWords [5] = {"university", "department", "incredible", "unbelievable", "spetacular"};
string mWords [5] = {"computer", "science", "longhorn", "cherry", "program"};
string hWords [5] = {"pink", "year", "oil", "zip", "numb"};
int chances;
bool hint;
int level;

void intro();

void easterEgg(){
	runGame(level);
}

string rightGuess(string tgt, string guess, char input){
  if(input == 'H') return guess;
  bool right = false;
  for(int i = 0; i<tgt.size(); i++){
    if(tgt[i] == input) {
      guess[i] = input;
      right = true;
    }
  }
  if(right){
    cout << "That was a good pick! Current word:" << endl;
    cout << guess << endl;
  }
  else {
    cout << "Wrong guess" << endl;
    chances--;
  }
    return guess;
}  

string giveHint(string tgt, string guess){
  char tmp;
  int ind;
  for(int i = 0; i<guess.size(); i++){
    if (guess[i] == '*'){
      guess [i] = tgt[i];
      tmp = tgt[i];
      ind = i;
      break;
    }
  }
  for(int i = ind+1; i<guess.size(); i++){
    if(tgt[i] == tmp) guess[i] = tmp;
  }
  cout<< "Your hint letter is "<< tmp <<". Current word: "<<endl;
  cout<<guess<<endl;
  return guess;	
}

void hangman(string tgt){
  bool avail [26];
  for(int i = 0; i<26; i++) avail[i] = true;
  string guess = "";
  for(int i = 0; i<tgt.size(); i++)
    guess += "*";
  cout<<guess<<endl;
  bool success = false;
  int count = 0;
  while(!success){
    count++;
    if(chances == 1) cout << "One more chance for wrong guess!"<<endl;
    if(chances == 0) {
      cout << "You lost :( Would you like another game? Y/N"<<endl;
      char newGame;
      cin >> newGame;
      if(newGame == 'Y') intro();
      else if(newGame == 'N' ) {
	cout << "Bye!"<<endl;
	return;
      }
      else cout << "Invalid input! Y/N?" << endl;
    }
    bool charSelected = false;
    char input;
    cout << "\nRound " << count << ": "<< endl;
    while(!charSelected){
      cout<<"Available letters:"<<endl;
      for(int i = 0; i<26; i++)
	if(avail[i]) cout << (char)(97+i) << ' ';
      cout << "\nPick a letter" << endl;
      cin >> input;
      if(input == 'H') {
	charSelected = true;
	if(hint){
	  guess = giveHint(tgt, guess);
	  hint = false;
	}
	else {
	  cout << "You already used your hint! Easter Egg hit! Game restarted!"<<endl;
	  easterEgg();
	  count--;
	}
      }
      else if((int)input < 97 || (int)input > 122 || !avail[(int)input-97]) cout << "Invalid input! Pick from given letters"<<endl<<endl;
      else charSelected = true;
    }
    if(input != 'H') avail[(int)input-97] = false;
    
    string tmp = rightGuess(tgt, guess, input);
    if(guess != tmp) guess = tmp;
    if(guess == tgt) success = true;
  }
  cout << "Congrats you have won! Another game? Y/N"<<endl;
  char newGame;
  cin >> newGame;
  if(newGame == 'Y') intro();
  else if(newGame == 'N' )cout << "Bye!"<<endl;
}


void runGame (int level){
  string tgt;
  srand (time(NULL));
  int ind = rand() % 5;
  if(level == 0) tgt = eWords[ind];
  else if(level == 1) tgt = mWords[ind];
  else tgt = hWords[ind];
  //cout << tgt << endl;
  hangman(tgt);
}



void intro(void){
  string user, diff;
  hint = true;
  cout << "Welcome to hangman! Please enter your name" <<endl;
  cin >> user;
  bool levelSelected = false;
  while (!levelSelected){
    cout << "\nHi " << user <<", choose the level you want to play"<<endl;
    cout << "Easy" <<endl;
    cout << "Medium" <<endl;
    cout << "Hard" << endl;
    cin >> diff;
    
    if (diff == "Easy" || diff == "easy" ){
      levelSelected = true;
      chances = 7;
      level = 0;
      runGame(level);
    }
    if (diff == "Medium" || diff == "medium"){
      levelSelected = true;
      chances = 5;
      level=1
      runGame (1);
    }
    if (diff == "Hard" || diff == "hard"){
      levelSelected = true;
      chances = 5;
      level=2;
      runGame(2);
    }
    else cout << "Invalid input! Please enter easy, medium, or hard" << endl;
  }
}

void rulebook(){
  cout<<"Rulebook:"<<endl;
  cout<<"This is a game of hangman without the man because we are nice people. There are three levels of difficulty:"<<endl; 
  cout<<"Easy: the word has MORE than 8 letters; use gets one hint; game ends after user's 7th wrong guess."<<endl;
  cout<<"Medium: words has MORE than 5 letters; there will be no hint; game ends after user's 5th wrong guess."<<endl;
  cout<<"Hard: words has LESS than 5 letters; there will be no hints; game ends after user's 5th wrong guess."<<endl<<endl;
  cout<<"To use your hint, enter 'H'. The program will not double-check your decision. Other than that, the program will let you know if your input is invalid and keeps asking until a valid input is provided."<<endl<<endl;
  cout<<"After a game ends, you will have a chance to start a new game ro exit. Enjoy the game!"<<endl<<endl;
}

int main(){
  rulebook();
  intro();	
  return 0;
}

