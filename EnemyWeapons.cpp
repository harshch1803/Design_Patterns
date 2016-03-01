#include<iostream>

using namespace std;

class ESWeapon
{
	public :
		virtual string toString() = 0;
};

class ESUFOGun : public ESWeapon
{
	public :
		virtual string toString()
		{
		
			return (" 10 Damage Points ");
		}	
};

class ESBossGun : public ESWeapon
{
	public :
		virtual string toString()
		{
		
			return (" 100 Damage Points ");
		}	
};

class ESEngine
{
	public :
		virtual string toString() = 0;
};

class ESUFOEngine : public ESEngine
{
	public :
		virtual string toString()
		{
			return (" 1000 Rpm ");
		}	
};

class ESBossEngine : public ESEngine
{
	public :
		virtual string toString()
		{
			return (" 8000 Rpm ");
		}	
};

class ESMissile
{
	public :
	virtual string toString() = 0;
};

class ESBossMissile : public ESMissile
{
	public :
	virtual string toString()
	{
		return (" It Has 10 Missiles ");
	}	
	
};

class EnemyShipFactory
{
	public :
		EnemyShipFactory(){}
		virtual ESWeapon* addGun() = 0;
		virtual ESEngine* addEngine() = 0;
		virtual ESMissile* addMissile()
		{ return NULL;}
	
};

class UFOEnemyShipFactory : public EnemyShipFactory
{
	public :
		UFOEnemyShipFactory(){}
		
		 virtual ESWeapon* addGun()
		 {
		 	return (new ESUFOGun());
		 }
		
		 virtual ESEngine* addEngine()
		 {
		 	return (new ESUFOEngine());
		 }
};

class UFOBossShipFactory : public EnemyShipFactory
{
	public :
		UFOBossShipFactory(){}
		
		 virtual ESWeapon* addGun()
		 {
		 	return (new ESBossGun());
		 }
		
		 virtual ESEngine* addEngine()
		 {
		 	return (new ESBossEngine());
		 }
		 
		 virtual ESMissile* addMissile()
		 {
		 	return (new ESBossMissile());
		 }
		 
};

class EnemyShip
{
	protected : 
		string m_name = "NULL" ;
		ESWeapon* pWeapon = NULL;
		ESEngine* pEngine = NULL;
		ESMissile* pMissile = NULL;
		
	public :
		void setName(string Name){ m_name = Name;}
		string getName(){return m_name;}
		virtual void makeShip() = 0;
		string toString()
		{
			string shipInfo; 
			shipInfo = "The " + m_name + " has a Top Speed of " + pEngine->toString() + " and a Damage Power of " + pWeapon->toString()+"\n";
			
			if(pMissile != NULL)
				shipInfo = shipInfo + pMissile->toString();
				
			return shipInfo; 
		}
};

class UFOBossShip : public EnemyShip
{
	private : 
		EnemyShipFactory* m_pShipfactory;
	public :
		UFOBossShip(EnemyShipFactory* pShipfactory)
		{
			m_pShipfactory = pShipfactory;
		}
		
		virtual void makeShip()
		{
			cout<<"Making The Enemy Ship "<<m_name<<endl;
			pWeapon = m_pShipfactory->addGun();
			pEngine = m_pShipfactory->addEngine();
			pMissile = m_pShipfactory->addMissile();
		}
		
};

class UFOEnemyShip : public EnemyShip
{
		private : 
		EnemyShipFactory* m_pShipfactory;
		
	public :
		UFOEnemyShip(EnemyShipFactory* pShipfactory)
		{
			m_pShipfactory = pShipfactory;
		}
		
		virtual void makeShip()
		{
			cout<<"Making The Enemy Ship "<<m_name<<endl;
			pWeapon = m_pShipfactory->addGun();
			pEngine = m_pShipfactory->addEngine();
		}
};

class EnemyShipBuilding
{
	
	protected :
		virtual EnemyShip* MakeNewShip(string shipType){}
		
	public :
		EnemyShipBuilding(){};
		EnemyShip* OrderTheShip(string shipType)
		{
			EnemyShip *enemyship = MakeNewShip(shipType);
			return enemyship;
		}
};

class UFOEnemyShipBuilding : public EnemyShipBuilding
{
	private :
		EnemyShip * m_enemyship = NULL;
	public :
		UFOEnemyShipBuilding(){}
		
		virtual EnemyShip* MakeNewShip(string shipType) 
		{
			if(shipType == "SMALL")
			{
				EnemyShipFactory* m_pShipPartsFactory = new UFOEnemyShipFactory();
				m_enemyship = new UFOEnemyShip(m_pShipPartsFactory);
				
				m_enemyship->setName("Battle Ship");
				m_enemyship->makeShip();
				
			}
				
			
			else if(shipType == "Boss")
			{
				EnemyShipFactory* m_pShipPartsFactory = new UFOBossShipFactory();
				m_enemyship = new UFOBossShip(m_pShipPartsFactory);
				
				m_enemyship->setName("Boss Ship");
				m_enemyship->makeShip();
				
			}
				
				
			else
			{
				cout<<"Enter The Name Correctly Next Time"<<endl;
			}
				
			cout<<m_enemyship->getName()<<endl;
			cout<<m_enemyship->toString()<<endl;
			
			return m_enemyship;
			
		}
};

int main()
{
	EnemyShipBuilding *MakeUFO = new UFOEnemyShipBuilding();
	EnemyShip* myShip = MakeUFO->OrderTheShip("Boss");
}
