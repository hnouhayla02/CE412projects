#include <iostream>
#include <random>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

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


bool unfilledPositionFound(unordered_map<string, int>& )
{
     
}

bool reelectingConsulFound()
{


}



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
string updateLevel(Politician& p)
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



int simulateLifeExpec()
{
    #include <cstdlib> // for rand()

// Function to simulate the life expectancy of a politician
int simulateLifeExpectancy() {
    // Simulate life expectancy within a reasonable range, for example, between 60 and 90 years


    // Generate a random number within the specified range
    int lifeExpectancy = lifeExpecMIN + rand() % (lifeExpecMAX - lifeExpecMIN + 1);

    return lifeExpectancy;
}


}

void simulateAnnualElections();

void updateAgesAndRemovePoliticians(queue<Politician>& candidates);

void generateNewCandidates();

void printResluts(queue<Politician>& candidates, unordered_map<string, int>& officePositions, int finalePSI);


bool unfilledPositionFound(unordered_map<string, int>& officePositions) {
    for (auto& pair : officePositions) {
        if (pair.second > 0) {
            return true; // Unfilled position found
        }
    }
    return false; // No unfilled positions
}

// Function to check if there is a consul being re-elected within 10 years
bool reelectingConsulFound(queue<Politician>& candidates) {
    int consulCount = 0;
    while (!candidates.empty()) {
        if (candidates.front().level == "Consul") {
            consulCount++;
            if (consulCount > 1) {
                return true; // Consul re-elected within 10 years found
            }
        }
        candidates.pop();
    }
    return false; // No consul re-elected within 10 years
}

// Function to calculate the Political Stability Index (PSI)
int calculatePSI(unordered_map<string, int>& officePositions) {
    int psi = 100; // Starting PSI
    for (auto& pair : officePositions) {
        if (pair.second > 0) {
            psi -= 5; // Penalty for each unfilled position
        }
    }
    if (reelectingConsulFound(candidates)) {
        psi -= 10; // Additional penalty for re-electing a Consul within 10 years
    }
    return psi;
}

// Function to update the level of a politician
string updateLevel(Politician& p) {
    if (p.level == "Quaestor" && p.age >= 36) {
        return "Aedile"; // Promote Quaestor to Aedile if age requirement is met
    } else if (p.level == "Aedile" && p.age >= 39) {
        return "Praetor"; // Promote Aedile to Praetor if age requirement is met
    } else if (p.level == "Praetor" && p.age >= 42) {
        return "Consul"; // Promote Praetor to Consul if age requirement is met
    } else {
        return p.level; // No level change
    }
}

// Function to simulate the annual election process and career progression
void simulateAnnualElections(queue<Politician>& candidates, unordered_map<string, int>& officePositions) {
    while (!candidates.empty()) {
        Politician p = candidates.front();
        candidates.pop();
        if (officePositions[p.level] > 0) {
            officePositions[p.level]--; // Fill the office position
            p.level = updateLevel(p); // Update politician's level
            candidates.push(p); // Push politician back into the queue
        }
    }
}

// Function to update the ages of politicians and remove those who have surpassed their life expectancy
void updateAgesAndRemovePoliticians(queue<Politician>& candidates) {
    int candidateCount = candidates.size();
    for (int i = 0; i < candidateCount; ++i) {
        Politician p = candidates.front();
        candidates.pop();
        p.age++; // Increment politician's age
        if (p.age <= simulateLifeExpec()) {
            candidates.push(p); // Push politician back into the queue if still within life expectancy
        }
    }
}

// Function to generate new candidates for the election
void generateNewCandidates(queue<Politician>& candidates) {
    int influx = 15 + rand() % 6; // Annual Influx of New Candidates
    for (int i = 0; i < influx; ++i) {
        Politician p;
        p.age = 30; // Minimum age for Quaestor
        p.level = "Quaestor"; // New candidates start as Quaestor
        candidates.push(p);
    }
}

// Function to print the final results
void printResults(queue<Politician>& candidates, unordered_map<string, int>& officePositions, int finalPSI) {
    cout << "End-of-Simulation PSI: " << finalPSI << endl;

    cout << "Annual Fill Rate:" << endl;
    cout << "Quaestor: " << (20 - officePositions["Quaestor"]) / 200.0 * 100 << "%" << endl;
    cout << "Aedile: " << (10 - officePositions["Aedile"]) / 200.0 * 100 << "%" << endl;
    cout << "Praetor: " << (8 - officePositions["Praetor"]) / 200.0 * 100 << "%" << endl;
    cout << "Consul: " << (2 - officePositions["Consul"]) / 200.0 * 100 << "%" << endl;

    // Age distribution of politicians in different offices
    // You would need to collect age information from the 'candidates' queue
    // and then calculate the distribution for each office level.
}


int main() 
{
    





    return 0;
}
