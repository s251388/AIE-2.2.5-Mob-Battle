
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <functional>

using namespace std;


struct AttackData {

	string Name;			// Attack's name
	int Dmg;				// Base damage of the attack
	int Acc;				// Accuracy (chance to hit)
	float HitVul;			// Modifies openness if attack lands
	float MissVul;			// Modifies openness if attack misses
	string SpecialText;		// Gives special text like if a move isn't an attacking move

};

struct Mob {

	string MobName;					// This is the mob's name
	int Health;						// Current health
	vector<AttackData> AttackList;	// This is a list of all the mob's moves
	float Openness = 1;				// Steadiness is a changing value that affects how likely an enemy hit is to land

};


void Fight(Mob& User, Mob& Target) {

	AttackData* Chosen = &(User.AttackList[rand() % User.AttackList.size()]);			// Randomly picks an attack stored in the mob's AttackList vector
	cout << User.MobName << " used " << Chosen->Name << endl;
	Sleep(500);

	if (rand() % 100 < Chosen->Acc * Target.Openness) {			// Calculates whether attack landed, influenced by target's Posture

		int Damage = Chosen->Dmg;
			if (Chosen->Dmg > 0) {
				Damage += rand() % 21;			// Slightly randomises the damage by adding 0–20 to look more natural
			}
		
		Target.Health -= Damage;
		User.Openness = Chosen->HitVul;			// Adjusts own openness, usually to be higher, but can be made lower depending on the attack

		if (Chosen->SpecialText == "") {
			cout << "Success!" << endl;
			cout << User.MobName << " hit " << Target.MobName << " for " << Damage << " health!" << endl;
		}
		else {
			cout << User.MobName << Chosen->SpecialText << endl;
		}

	}
	else {

		User.Openness = Chosen->MissVul;			
		if (Chosen->SpecialText != "") {				// Gives "It failed" text as an alternative for attacks with unique hit text
			cout << "It failed." << endl;
		}
		else if (Chosen->MissVul < 1.25f) {				// Adjusts own openness, usually to be lower, but can be made higher depending on the attack	
			cout << User.MobName << " missed." << endl;
		}
		else {											// Just some extra text to indicate to the opponent if a miss left the user especially vulnerable
			cout << User.MobName << " missed and became unsteady!" << endl;	
		}

	}



}


int main()
{
    
	srand(time(0));				// This int is just to waste the first random number pull, because the
	int RandBurn = rand();		// randomness feels like it scales too obviously with time otherwise.
				
	// AttackData Name{		"Name",			Dmg,	Acc,	HitVul,	MissVul,	"SpecialText"};
	AttackData Scratch{		"Scratch",		30,		70,		1,		1.2f,		""};
	AttackData Punch{		"Punch",		40,		60,		1,		1.3f,		""};
	AttackData RockThrow{	"Rock Throw",	10,		80,		1,		1,			""};
	AttackData Thrash{		"Thrash",		70,		50,		0.7f,	1.5f,		""};
	AttackData SwordSlash{	"Sword Slash",	100,	80,		1,		1.1f,		""};
	AttackData SteadyBlow{	"Steady Blow",	50,		90,		0.5f,	1,			""};
	AttackData Focus{		"Focus",		0,		100,	0.2f,	0.9f,		" steadied itself"};
	AttackData Caution{		"Caution",		0,		80,		0.0f,	1.8f,		" prepared to dodge the opponent"};
	AttackData Shield{		"Shield",		0,		100,	0.5f,	1,			" readied their shield"};
	AttackData Lunge{		"Lunge",		50,		70,		0.8f,	1.6f,		""};
	AttackData Earthquake{	"Earthquake",	1,		100,	0.4f,	0.7f,		" made the ground shake violently"};
	AttackData Fireball{	"Fireball",		80,		70,		1,		1,			""};
	AttackData Thunder{		"Thunder",		150,	80,		1.3f,	1.3f,		""};
	AttackData DenseFog{	"Dense Fog",	0,		200,	0.5f,	1,			" cloaks the area in a dense fog"};
	AttackData SharpRoot{	"Sharp Root",	100,	80,		1,		1,			""};

	// Typically an attack that is easier to connect into another attack (like swinging claws or a sword) doesn't punish a miss as hard


				//	Name,		Health,		Attacklist
	Mob Knight{		"Knight",	1000,		{Punch, SteadyBlow, SwordSlash, Shield, Lunge, Caution} };
	Mob Mage{		"Mage",		800,		{Focus, Earthquake, Fireball, Thunder, DenseFog} };
	Mob Bandit{		"Bandit",	800,		{Punch, SwordSlash, Lunge, Caution, RockThrow} };
	Mob Goblin{		"Goblin",	600,		{Scratch, Punch, RockThrow, Thrash, Lunge} };
	Mob Ent{		"Ent",		2000,		{Earthquake, DenseFog, SharpRoot} };
	Mob Basilisk{	"Basilisk",	1500,		{Focus, Lunge, Thrash} };


	string Response;
	bool Swap = false;


	vector<Mob> Order {Knight, Mage, Bandit, Goblin, Ent, Basilisk};

	Mob* FighterA = &Order[rand() % 6];
	Mob* FighterB = &Order[0];
	do {
		FighterB = &Order[rand() % 6];
	} while (FighterA == FighterB);

	cout << "==============================\n" << FighterA->MobName << "     vs     " << FighterB->MobName << endl;

	do {

		cout << "==============================" << endl;
		cout << FighterA->MobName << ": " << FighterA->Health << "HP" << endl << FighterB->MobName << ": " << FighterB->Health << "HP\n" << endl;

		if (Swap == true) {
			Fight(*FighterA, *FighterB);
		}
		else {
			Fight(*FighterB, *FighterA);
		}

		Swap = !Swap;

		Sleep(1000);

	} while (FighterA->Health > 0 && FighterB->Health > 0);

	string Winner;

	if (FighterA->Health > 0) {
		Winner = FighterA->MobName;
	}
	else {
		Winner = FighterB->MobName;
	}

	cout << "\n	*# " << Winner << " wins! #*" << endl;

}

