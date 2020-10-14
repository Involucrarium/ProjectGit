#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <algorithm>
using namespace std;


class Revolver {
private:
	int position = 0;

public:
	Revolver() {}

	bool cylinder[6] = { 0,0,0,0,0,0 };

	int spin() {
		cout << "Spin";
		Sleep(777);
		cout << ".";
		Sleep(777);
		cout << ".";
		Sleep(777);
		cout << ". \n";
		Sleep(777);
		srand((unsigned int)time(NULL));
		int num = (rand() % (5 - 0 + 1)) + 0;
		cout << "Chamber no. " << num;
		return num;
	}

	void laden(int anzahlPatronen) {
		bool loaded;
		int chamber;
		cout << "Es werden " << anzahlPatronen << " geladen \n";
		for (int i = 0; i < anzahlPatronen; i++) {
			loaded = false;
			do {
				chamber = spin();
				if (cylinder[chamber] == 0) {
					cylinder[chamber] = 1;
					loaded = true;
					cout << " loaded...\n";
				}
				else {
					cout << " is already loaded, new chamber...\n";
				}
			} while (!loaded);
		}
	}

	bool pullTrigger(int position) {
		if (cylinder[position] == true) {
			cout << "peng \n";
			return false;
		}
		else {
			cout << "klick \n";
			return true;
		}
	}

	const int& getPosition() const {
		return this->position;
	}
};


class Spieler {
private:
	string name;
	bool alive;
public:
	Spieler(string name, bool alive) {
		this->name = name;
		this->alive = alive;
		cout << "Spieler " << name << " hinzugefügt.\n";
	}

	const string& getName() const {
		return this->name;
	}
	const bool& getAlive() const {
		return this->alive;
	}


	void setAlive(bool alive) {
		this->alive = alive;
	}

};
class Spiel {
private:
	int anzahlSpieler;
	vector<Spieler> spielerliste;
	Revolver boomstick;

public:

	Spiel(int anzahlSpieler) {
		this->anzahlSpieler = anzahlSpieler;
		string name = "";
		for (int i = 0; i < anzahlSpieler; i++) {
			cout << "Namen eintragen: " << "\n";
			getline(cin, name);
			this->spielerliste.push_back(Spieler(name, true));
			name = "";
		}

	}
	void play() {
		int i = 0;
		bool laden = true;
		int position = 0;
		boomstick.laden(1);
		while (spielerliste.size() > 1) {
			if (i >= spielerliste.size()) {
				i = 0;
			}
			Sleep(1000);
			cout << "\n" << spielerliste.at(i).getName() << " pulls the trigger... \n";
			Sleep(1000);
			spielerliste.at(i).setAlive(boomstick.pullTrigger(position));
			if (!spielerliste.at(i).getAlive()) {
				WeLostOne(position, i);
				position = -1;
				i = -1;
			}
			position++;
			i++;
		}
	}
	void WeLostOne(int position, int who) {
		// Spieler entfernen
		spielerliste.erase(spielerliste.begin() + who);	
		// Patronenhülse herausnehmen
		boomstick.cylinder[position] = false;	
		
		// Neuladen wenn noch Spieler übrig sind und Liste neu mischen
		if (spielerliste.size() > 1) {
			boomstick.laden(1);	
			shuffles(spielerliste);
		}
	}

	void printWinner() {
		cout << "Game Over, Survivor/s: \n";
		for (int i = 0; i < spielerliste.size(); i++) {
			cout << spielerliste.at(i).getName() << "\n";

		}
	}
		void shuffles(vector<Spieler> spielerliste) {
			auto rng = default_random_engine{};
			shuffle(begin(spielerliste), end(spielerliste), rng);
		}
};

	int main() {

		Spiel neuesSpiel(3);
		neuesSpiel.play();
		neuesSpiel.printWinner();

		system("pause");
		return 0;
	}
