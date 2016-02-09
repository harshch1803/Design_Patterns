#include<iostream>
#include<vector>
#include<string>

using namespace std;


//base class.
class EnemyShip
{
	private :
		//to store name of the ship.
		string m_name;
		
		//to store damage.
		float m_damage;
	
	public :
		
		//default constructor.
		EnemyShip();
		
		//display ship on the screen.
		string DisplayShip();
		
		//set name of the ship.
		void SetName(string name);
		
		//display name of the ship.
		string GetName();
		
		//set damage of the ship.
		void SetDamage(float damage);
		
		//display damage by the ship.
		float GetDamage();
};

//default constructor.
EnemyShip::EnemyShip()
{}

//display ship on the screen.
string EnemyShip :: DisplayShip()
{
	return ("A Ship is created on the Screen");
}

//set name of the ship.
void EnemyShip :: SetName(string name)
{
	m_name = name;
}

//display name of the ship.
string EnemyShip :: GetName()
{
	return (m_name);
}

//set damage by the ship.
void EnemyShip :: SetDamage(float damage)
{
	m_damage = damage;
}

//display damage.
float EnemyShip :: GetDamage()
{
	return (m_damage);
}

//subclass of base class EnemyShip.
class SmallShip : public EnemyShip 
{
	public : 
	
	//default constructor.
	SmallShip()
	{
		SetName("SmallShip");
		SetDamage(10.0f);
		cout<<DisplayShip()<<endl;
	}
	
};

//subclass of base class EnemyShip.
class BossShip : public EnemyShip
{
	public :
		
	//default constructor.
	BossShip()
	{
		SetName("BossShip");
		SetDamage(100.0f);
		cout<<DisplayShip()<<endl;
	}
};

//class EnemyFactory to build ships.
class EnemyFactory
{	
	public :
		
		//default constructor.
		EnemyFactory()
		{}
		
		//a pointer to the user defined ship.
		EnemyShip* MakeEnemy(string choice);
};


EnemyShip* EnemyFactory :: MakeEnemy(string choice)
{
	
	if(choice == "S" || choice == "s")
	{
		return(new SmallShip());
	}
		
		
	else if(choice == "B"  || choice == "b")
	{
		return(new BossShip());
	}
	
	else
	{
		cout<<"Please Enter the correct Letter next time"<<endl;
		return (NULL);
	}
	
}

//display ship details.
void DisplayShipDetails(EnemyShip *enemy);

int main()
{
	EnemyFactory *ef = new EnemyFactory();
	EnemyShip *e1;
	
	string choice ;
	cout<<"Enter S / B"<<endl;
	cin>>choice;
	
	e1 = ef->MakeEnemy(choice);
	
	if(e1 == NULL)
		cout<<"Such Type of Ship Doesn't exsist"<<endl;
		
	else
		DisplayShipDetails(e1);
		
	return 0;
}


void DisplayShipDetails(EnemyShip *enemy)
{
	cout<<"Type of Ship - "<<enemy->GetName()<<endl;
	cout<<"Attack Power - " <<enemy->GetDamage()<<endl;
}

