#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//singleton structure.
 class Singleton 
{
	private :
		//pointer to a static singleton object.
		static Singleton *FirstInstance;
		
		//array of letters stored in a vector.
		 vector<string> scrabbleLetters = {"a", "a", "a", "a", "a", "a", "a", "a", "a",
	    "b", "b", "c", "c", "d", "d", "d", "d", "e", "e", "e", "e", "e",
	    "e", "e", "e", "e", "e", "e", "e", "f", "f", "g", "g", "g", "h",
	    "h", "i", "i", "i", "i", "i", "i", "i", "i", "i", "j", "k", "l",
	    "l", "l", "l", "m", "m", "n", "n", "n", "n", "n", "n", "o", "o",
	    "o", "o", "o", "o", "o", "o", "p", "p", "q", "r", "r", "r", "r",
	    "r", "r", "s", "s", "s", "s", "t", "t", "t", "t", "t", "t", "u",
	    "u", "u", "u", "v", "v", "w", "w", "x", "y", "y", "z"}; 
		
		//pointer to the list which will act as the sack to draw out letters, in scrabble.
		list<string> *letterList = new list<string>();
		
		//default constructor.
		 Singleton ()
		{
			//shuffle the letters stored in the vector.
			random_shuffle(scrabbleLetters.begin(),scrabbleLetters.end());
			
			//add the letters to the sack.
			for(int i = 0; i < scrabbleLetters.size(); i++)
			{
				letterList->push_back(scrabbleLetters[i]);
			}
		}
			 
		
	public :
		//static function to create a static singleton object
		static Singleton *GetInstance()
		{
			//checks if the singleton object is already created.
			if(FirstInstance  == NULL)
			{
				FirstInstance = new Singleton();
			}
			
			return FirstInstance;
		}
			
		//a pointer to the letterList.
		list<string> *getLetterList()
		{
			return(FirstInstance->letterList); 
		}
		
		//a pointer to the list that will hold the player's letters.
		list<string> *getTiles(int howManyTiles)
		{
			//create a new list for the player to hold his/her letters.
			list<string> *tilesToSend = new list<string>();
			
			//check if the letters needed by the player are less than the letters in the sack(letterList).
			if(letterList->size() >= howManyTiles)
			{
				//take out one letter at a time from the sack(letterList).
				for(int i = 1 ; i<= howManyTiles ; i++)
				{
					//a pointer to the sack(letterList).
					list<string> *iter = FirstInstance->letterList;
					
					//get the first letter from the sack and add it to player's list.
					tilesToSend->push_back((*(*iter).begin()));
					
					//delete that letter from the sack(letterList).
					letterList->erase(letterList->begin());
				}
				
				return tilesToSend;
			}
			
			else 
			{
				cout<<"Not Enough Tiles"<<endl;
				return NULL;
			}
			
		}
};

Singleton* Singleton :: FirstInstance = NULL;


//player structure.
class Player 
{
	private : 
		//unique id for each player.
		static int playerID;
		
		//pointer to the list that will hold the player's letters.
		list<string> *playerTiles = NULL;
	
	public : 
		//default constructor.
		Player(){ playerID++;}
		
		//get the tiles from the sack.	
		void GetTiles(Singleton *s);
		
		//display all the tiles the player has.
		void displayTiles();
		
};

int Player :: playerID = 0;

void Player :: GetTiles(Singleton *s)
{
	//to store the number of letters.
	int tiles;
	
	cout<<"\nHow Many Tiles Do You Need <Player "<<playerID<<">"<<endl;
	cin>>tiles;
	
	//pointer to the list that will hold the player's letters.
	playerTiles = s->getTiles(tiles);
}

//display all the letters the player has.
void Player :: displayTiles()
{
	cout<<" \nPlayer " <<playerID<<" Tiles - "<<endl;
	
	//check if the player demanded valid number of tiles and then print them.
	if(playerTiles != NULL)
	{
		for(auto iter  = playerTiles->begin(); iter != playerTiles->end(); ++iter )
		{
			cout<<*iter<<endl;
		}
	}
	
	//if not print the below.
	else
	{
		cout<<"Cannot pick so many Tiles"<<endl;
	}
	
}

int main()
{
	//create a singleton object.
	Singleton *s1 = Singleton::GetInstance();
	list<string> *totalTiles = s1->getLetterList();
	
	//create a player object.
	Player *p1 = new Player();
	p1->GetTiles(s1);
	p1->displayTiles();
	
	//create another player object.
	Player *p2 = new Player();
	p2->GetTiles(s1);
	p2->displayTiles();
		
	return 0;
	
}
