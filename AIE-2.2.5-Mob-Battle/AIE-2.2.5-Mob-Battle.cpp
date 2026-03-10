
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

struct AttackData {

	string Name;			// Attack's name
	int Dmg;				// Base damage of the attack
	int Acc;				// Accuracy (chance to hit)
	float HitVul;			// Vulnerability (decreases enemy accuracy if hit)
	float MissVul;			// Vulnerability (increases enemy accuracy if missed)
	string SpecialText;		// Gives special text like if a move isn't an attacking move

	void SpecialEffect() {}

};

struct Mob {

	string MobType;					// This is the mob's name
	int Health;						// Current health
	float Agility;					// Agility affects how well it dodges attacks and does not change
	float Vulnerability = 1;		// Vulnerability is a changing value that affects how likely an enemy hit is to land
	vector<AttackData> AttackList;	// This is a list of all the mob's moves

};

void Fight(Mob& User, Mob& Target) {

	AttackData* Chosen = &(User.AttackList[rand() % User.AttackList.size()]);			// Randomly picks an attack stored in the mob's AttackList vector
	cout << User.MobType << " used " << Chosen->Name << endl;
	Sleep(100);

	if (rand() % 100 < Chosen->Acc * Target.Vulnerability) {			// Calculates whether attack landed, influenced by target's vulnerability

		int Damage = Chosen->Dmg + rand() % 21;			// Slightly randomises the damage by adding 0–20 to look more natural
		Target.Health -= Damage;
		User.Vulnerability = Chosen->HitVul;			// Adjusts own vulnerability, usually to be higher, but can be made lower depending on the attack

		if (Chosen->SpecialText == "") {
			cout << "Success!" << endl;
			Sleep(20);
			cout << User.MobType << " hit " << Target.MobType << " for " << Damage << " health!" << endl;
		}
		else {
			cout << Chosen->SpecialText << endl;
		}

	}
	else {

		User.Vulnerability = Chosen->MissVul;			
		if (Chosen->SpecialText != "") {				// Gives "It failed" text as an alternative for attacks with unique hit text
			cout << "It failed." << endl;
		}
		else if (Chosen->MissVul < 0.75) {				// Adjusts own vulnerability, usually to be lower, but can be made higher depending on the attack	
			cout << User.MobType << " missed." << endl;
		}
		else {											// Just some extra text to indicate to the opponent if a miss left the user especially vulnerable
			cout << User.MobType << " missed and became unsteady!" << endl;	
		}

	}



}


int main()
{
    
	srand(time(0));				// This int is just to waste the first random number pull, because the
	int RandBurn = rand();		// randomness feels like it scales too obviously with time otherwise.
								
}

