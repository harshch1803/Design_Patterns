#include<iostream>

using namespace std;


//Interface 
class FlyingType
{
	public :
		//constructor
		FlyingType();
		
		//pure abstract method to be overriden.
		virtual string Fly() const = 0;
	
};

//Default constructor.
FlyingType :: FlyingType()
{}

//subclass of the interface FlyingType.
class ItFlys : public FlyingType
{
	public : 
		//Default constructor.
		ItFlys();
		
		//method which overrides superclass method.
		virtual string Fly() const ;
};

//Default constructor.
ItFlys :: ItFlys()
{}

//Overriding method.
string ItFlys :: Fly() const 
{
	return ("Yes , I Can Fly");
}

//another subclass of the interface FlyingType.
class CantFly : public FlyingType
{
	public :
		//Default constructor.
		CantFly();
		
		//overriding method.
		virtual string Fly() const;
};

//Default constructor.
CantFly :: CantFly()
{}

//Overriding method.
string CantFly :: Fly() const
{
	return ("No , I Cannot Fly");
}

//Main Base Class.
class Animal
{
	private :
		//to store name.
		string m_name;
		
		//to store weight.
		float m_weight;
		
	public :
		 //default constructor.
		 Animal();
		 
		 //get name from the user.
		 void GetName(string name);
		 
		 //get weight from the user.
		 void GetWeight(float weight);
		 
		 //abstract method.
		 virtual string MakeNoise();
		 
		 //to check if the animal flies.
		 string CanItFly();
		 
		 //to change flying ability of the animal.
		 void SetFlyingAbility(FlyingType *newFlyType);
		 
		 //Object of the interface(class) FlyingType. 
		 FlyingType *m_flyingtype;
};

//default constructor.
Animal :: Animal():
	m_name("NULL"),m_weight(0.0f){}
	
//get and print nameof the animal.
void Animal :: GetName(string name)
{
	m_name = name;
	cout<< "\nMy Name is "<<m_name<<endl;
}
	
//get weight of the animal.
void Animal :: GetWeight(float weight)
{
	if(weight>0)
	{
		m_weight = weight;
	}
	
	else 
	{
		cout<<"Weight has to be Greater than Zero"<<endl;
	}
}

//abstract method with default argument.
string Animal :: MakeNoise()
{
	return("I Don't make any Noise");
}

//to print if the animal can fly or not.
string Animal :: CanItFly()
{
	//calls Fly() function to print the message.
	return (m_flyingtype->Fly());
}

//to change flying ability of an animal.
void Animal :: SetFlyingAbility(FlyingType  *newFlyType)
{
	//clears the memory it is currently pointing to.
	delete m_flyingtype;
	
	//points to the new memory location.
	m_flyingtype = newFlyType;
}

//subclass of Animal class.
class Dog : public Animal 
{
	public :
		//default constructor.
		Dog();
		
		//overriding method.
		string MakeNoise();
};	

Dog :: Dog()
{
	//set the object of FlyingType datatype to CantFly datatype using Polymorphism.
	m_flyingtype = new CantFly();
}

//overriding method.
string Dog :: MakeNoise()
{
	return("Woof Woof");
}

//subclass of Animal class.
class Bird : public Animal
{
	public :
		//default constructor.
		Bird();
		
		//overrriding method.
		string MakeNoise();
	
};

//defualt constructor.
Bird :: Bird()
{
	//set the object of FlyingType datatype to ItFlys datatype using Polymorphism.
	m_flyingtype  = new ItFlys();
}

//overriding method.
string Bird :: MakeNoise()
{
	return("Chew Chew");
}

int main()
{
	//set object of Animal datatype to Dog datatype using Polymorphism.
	Animal *d1 = new Dog();
	
	d1->GetName("Potter");
	d1->GetWeight(25.0f);
	cout<<d1->MakeNoise()<<endl;
	cout<<"Flying Status  - "<<d1->m_flyingtype->Fly()<<endl;
	
	cout<<"\nThe Dog became a Super Dog"<<endl;
	
	d1->SetFlyingAbility(new ItFlys());
	cout<<d1->m_flyingtype->Fly()<<endl;
	
	//set object of Animal datatype to Bird datatype using Polymorphism.
	Animal *b1 = new Bird();
	b1->GetName("Rey");
	b1->GetWeight(25.0f);
	cout<<b1->MakeNoise()<<endl;
	cout<<"Flying Status  - "<<b1->m_flyingtype->Fly()<<endl;
	
	
	
	return 0;
}

