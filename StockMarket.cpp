#include<iostream>
#include<vector>

using namespace std;

//--------------------------------

//Observer abstract  Base class.
class Observer 
{
	public :
		
		//default constructor.
		Observer();
		
		//pure virtual function to be overriden.
		virtual void update(float msn,float appl,float goog) = 0;
};

//default constructor.
Observer :: Observer()
{}

//--------------------------------

//Subject (Publisher) abstract Base class.
class Subject
{		
	public :
	 
		//default constructor.
		Subject();
		
		//pure virtual function to be overriden.
		virtual void Register(Observer *newObserver) = 0;
		
		//pure virtual function to be overriden.
		virtual void Unregister(Observer *deleteObserver) = 0;
		
		//pure virtual function to be overriden.
		virtual void NotifyObserver() = 0;
	
};

//default constructor.
Subject :: Subject()
{}

//--------------------------------

//Sub class of Base class Subject.
class StockGrabber : public Subject
{
	private :
		//to store objects of Observer type.
		vector<Observer*> observers;
		
		//stock prices.
		float msnPrice = 0;
		float applPrice = 0;
		float googPrice = 0;
		
	public : 
		//default constructor.
		StockGrabber();
		
		//to register a new observer.
		virtual void Register(Observer *newObserver);

		//to remove an observer from the list.
		virtual void Unregister(Observer *deleteObserver);
		
		//notify observer on any change.
		virtual void NotifyObserver();
		
		//set the stock prices.
		void Set_msnPrice(float msn);
		void Set_applPrice(float appl);
		void Set_googPrice(float goog);
};

//default constructor.
StockGrabber ::StockGrabber()
{
}

//to register a new observer.
void StockGrabber :: Register(Observer *newObserver)
{
	//scan through the observer list.
	for(auto i=observers.begin();i!= observers.end();i++)
	{
		//check if the new observer already exsists in the list.
		if(*i == newObserver)
		{
			cout<<"The Observer already Exsists\n"<<endl;
			return;
		}
	}
	
	//if it doesn't add the observer to the list.
	observers.push_back(newObserver);
}

//to remove an observer from the list.
void StockGrabber :: Unregister(Observer *deleteObserver)
{
	//scan through the observer list.
	int i= 0;
	for (;i< observers.size();++i)
	{
		//check for the observer to be deleted.
		if(deleteObserver == observers[i])
		{
			cout<<"Observer - "<< i+1<<" removed from the list "<<endl;
			
			//remove the pointer from the observer list.
			observers.erase(observers.begin()+i);
			cout<<"The New Size is "<<observers.size()<<"\n\n";
			return;
		}
	}
	 
	 //if the observer is not present in the list, display the below message.
	 if(i == observers.size())
	{
		cout<<"Observer Doesn't Exsist\n"<<endl;
	}		
}

//notify observer on any change.
void StockGrabber :: NotifyObserver()
{
	//create an iterator.
	vector<Observer*> :: iterator i ;
	
	//notify all the observers regarding any change in stocks.
	for(i = observers.begin();i!= observers.end();i++)
	{
		(*i)->update(msnPrice,applPrice,googPrice);
	}
}

void StockGrabber :: Set_msnPrice(float msn)
{
	msnPrice = msn;
	NotifyObserver();
}

void StockGrabber :: Set_applPrice(float appl)
{
	applPrice = appl;
	NotifyObserver();
}

void StockGrabber :: Set_googPrice(float goog)
{
	googPrice = goog;
	NotifyObserver();
}

//--------------------------------

//subclass of base class Observer.
class StockObserver : public Observer
{
	private :
		
		//stock prices.
		float msnPrice;
		float applPrice;
		float googPrice;
		
		//observer ID to identify an observer.
		int ObserverID;
		
		//a pointer to the stockgrabber.
		Subject *stockgrabber;
	public :
		//to keep a count of the number of observers.
		static int ObserverCount;
		
		//paramaterized constructor.
		StockObserver(Subject *StockGrabber);
		
		//to update the stock prices of indiviual observer.
		virtual void update(float msn,float appl,float goog);
		
		//display stock prices of a given observer.
		void DisplayStock();
	
};

//initialize static int observercount.
int StockObserver :: ObserverCount = 0;

//paramaterized constructor.
StockObserver ::StockObserver(Subject *StockGrabber)
{
	//increment observercount for every new observer object created.
	ObserverCount +=1;
	
	//make the obsercount as the ID.
	ObserverID = ObserverCount;
	cout<<"Observer ID - "<<ObserverID<<endl;
	
	//pointer to the stockgrabber object.
	stockgrabber = StockGrabber;
	
	//register the new observer to the list.
	stockgrabber->Register(this);
}

//update the stock prices of indiviual observer.
void StockObserver :: update(float msn,float appl,float goog)
{
	msnPrice = msn;
	applPrice = appl;
	googPrice = goog;
	
	DisplayStock();
}

//display stock prices of a given observer.
void StockObserver :: DisplayStock()
{
	cout<< "Notification for Observer - "<<ObserverID<<"\n\n";
	cout<<"Microsoft's Stock - "<<msnPrice<<endl;
	cout<<"Apple's Stock - "<<applPrice<<endl;
	cout<<"Google's Stock - "<<googPrice<<"\n\n";
}

//--------------------------------

int main()
{
	StockGrabber *s1 = new StockGrabber();
	StockObserver *o1 = new StockObserver(s1);
	
	s1->Set_msnPrice(600.0f);
	s1->Set_applPrice(630.0f);
	s1->Set_googPrice(615.0f);
	
	StockObserver *o2 = new StockObserver(s1);
	
	s1->Set_msnPrice(600.0f);
	s1->Set_applPrice(630.0f);
	s1->Set_googPrice(615.0f);
	
	StockObserver *o3 = new StockObserver(s1);
	
	s1->Set_msnPrice(600.0f);
	s1->Set_applPrice(630.0f);
	s1->Set_googPrice(615.0f); 
	

	s1->Unregister(o2);
	
	s1->Set_googPrice(620.0f); 
	
	return 0;
}


