#include <iostream>
#include <random>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;

int PSI= 100;
const double lifeExpecMEAN =55.0;
const double lifeExpecSTDV =10.0;
const int lifeExpecMIN= 25;
const int lifeExpecMAX =80;

class Politician {
public:
    int age;
    string level;
    int expYears;
};

bool unfilledPositionFound(unordered_map<string, int>& officePositions);
bool reelectingConsulFound(queue<Politician>& candidates);
int calculatePSI(queue<Politician>& candidates, unordered_map<string, int>& officePositions);
string updateLevel(Politician& p);
void simulateAnnualElections(queue<Politician>& candidates, unordered_map<string, int>& officePositions);
void updateAgesAndRemovePoliticians(queue<Politician>& candidates);
void generateNewCandidates(queue<Politician>& candidates);
void printResults(queue<Politician>& candidates, unordered_map<string, int>& officePositions, int finalPSI);

int simulateLifeExpec() {
    // Generate a random life expectancy within the specified range
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return lifeExpecMIN + rand() % (lifeExpecMAX - lifeExpecMIN + 1);
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize the simulation
    queue<Politician> candidates;
    unordered_map<string, int> officePositions = {
        {"Quaestor", 20},
        {"Aedile", 10},
        {"Praetor", 8},
        {"Consul", 2}
    };

    // Simulate the 200-year period
    for (int year = 0; year < 200; year++) {
        // Simulate the annual election process
        simulateAnnualElections(candidates, officePositions);

        // Update ages and remove politicians who have surpassed their life expectancy
        updateAgesAndRemovePoliticians(candidates);

        // Generate new candidates
        generateNewCandidates(candidates);
    }

    // Calculate the final PSI
    int finalPSI = calculatePSI(candidates, officePositions);

    // Print the results
    printResults(candidates, officePositions, finalPSI);

    return 0;
}


bool unfilledPositionFound(unordered_map<string, int>& officePositions) {
    for (auto& pair : officePositions) {
        if (pair.second > 0) {
            return true; // Unfilled position found
        }
    }
    return false; // No unfilled positions
}

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

int calculatePSI(queue<Politician>& candidates, unordered_map<string, int>& officePositions) {
    int psi = 100; // Starting PSI
    
    if (unfilledPositionFound(officePositions)) {
        psi -= 5; // Penalty for each unfilled position
    }
    
    if (reelectingConsulFound(candidates)) {
        psi -= 10; // Additional penalty for re-electing a Consul within 10 years
    }

    return psi;
}

string updateLevel(Politician& p) {
    if (p.level == "Quaestor" && p.age >= 36) {
        return "Aedile"; // Promote Quaestor to Aedile if(age requirement is met)
    } else if (p.level == "Aedile" && p.age >= 39) {
        return "Praetor"; // Promote Aedile to Praetor if(age requirement is met)
    } else if (p.level == "Praetor" && p.age >= 42) {
        return "Consul"; // Promote Praetor to Consul if(age requirement is met)
    } else {
        return p.level; // No level change
    }
}

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

void generateNewCandidates(queue<Politician>& candidates) {
    int influx = 15 + rand() % 6; // Annual Influx of New 
    for (int i = 0; i < influx; ++i) {
        Politician p;
        p.age = 30; // Minimum age for Quaestor
        p.level = "Quaestor"; // New candidates start as Quaestor
        candidates.push(p);
    }
}

void printResults(queue<Politician>& candidates, unordered_map<string, int>& officePositions, int finalPSI) {
    cout << "End-of-Simulation PSI: " << finalPSI << endl;

    cout << "Annual Fill Rate:" << endl;
    cout << "Quaestor: " << (20 - officePositions["Quaestor"]) / 200.0 * 100 << "%" << endl;
    cout << "Aedile: " << (10 - officePositions["Aedile"]) / 200.0 * 100 << "%" << endl;
    cout << "Praetor: " << (8 - officePositions["Praetor"]) / 200.0 * 100 << "%" << endl;
    cout << "Consul: " << (2 - officePositions["Consul"]) / 200.0 * 100 << "%" << endl;

   
}


