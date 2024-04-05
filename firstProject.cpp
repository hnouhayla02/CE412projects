#include <iostream>
#include <random>
#include <queue>
#include <unordered_map>
using namespace std;


int PSI= 100;
const double lifeExpecMEAN= 55.0;
const double lifeExpecSTDV= 10.0;
const int lifeExpecMIN= 25;
const int lifeExpecMAX= 80;





class Politician 
{

    public:

    int age;
    string level;
    int expYears;





//level elligibility




};
//calculate PSI
int returnPSI(int something){
//PSI Calculation
int PSI = 100;
 if(unfilledPositionFound)
{
   PSI -=5;
}
 if(reelectingConsulFound) 
{
   PSI -=10;
}

 return PSI; 
}


//Updating the levels
string updateLevel(Politician p)
{
    if(p.level == "Quaestor" && p.expYears== 30)
    {
        p.level="Aedile";
    }
    if(p.level == "Aedile" && p.expYears== 30)
    {
        p.level="Praetor";
    }
    if(p.level == "Praetor" && p.expYears== 30)
    {
        p.level="Consul";
    }
   

   return p.level;
}



