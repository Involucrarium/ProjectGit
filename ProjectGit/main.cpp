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
	int position;
	bool cylinder[6] = { 0,0,0,0,0,0, };



public:
	Revolver(int position) {
		this->position = position;
	}

	int spin() {
		cout << "Spin";
		Sleep(777);
		cout << ".";
		Sleep(777);
		cout << ".";
		Sleep(777);
		cout << ".";
		srand((unsigned int)time(NULL));
		int num = (rand() % (5 - 0 + 1)) + 0;
		cout << "chamber no. " << num;
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
		cout << "All rounds loaded...\n";
	}
public:
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

public:
	Spiel(int anzahlSpieler) {
		this->anzahlSpieler = anzahlSpieler;
		string name = "";
		for (int i = 0; i < anzahlSpieler; i++) {
			cout << "Namen eintragen: " << "\n";
			getline(cin, name);
			spielerliste.push_back(Spieler(name, true));
			name = "";
		}
		Revolver boomstick(0);
		// reihenfolge shufflen
		auto rng = default_random_engine{};
		shuffle(begin(spielerliste), end(spielerliste), rng);

		int versuche = 0;
		int imKreis = 0;
		bool gameOver = false;
		boomstick.laden(1);
		int position = 0;
		while (!gameOver) {
			for (int i = 0; i < anzahlSpieler; i++) {
				if (versuche == 5 || spielerliste.size() == 1) {
					gameOver = true;
					break;
				}
				if (imKreis == anzahlSpieler) {
					imKreis = 0;
					i = 0;
				}
				Sleep(1000);
				cout << "\n" << spielerliste.at(i).getName() << " pulls the trigger... \n";
				Sleep(1000);
				spielerliste.at(i).setAlive(boomstick.pullTrigger(position));
				position++;
				versuche++;
				imKreis++;
				if (!spielerliste.at(i).getAlive()) {
					spielerliste.erase(spielerliste.begin() + i);
					anzahlSpieler--;
					imKreis--;
				}
			}
		}
		cout << "Game Over, Survivor/s: \n";
		for (int i = 0; i < spielerliste.size(); i++) {
			cout << spielerliste.at(i).getName() << "\n";
		}
	}
};

int main() {
	/*Revolver revolver1(0);
	cout << "How many rounds should be loaded? \n";
	int rounds;
	cin >> rounds;
	revolver1.laden(rounds);
	revolver1.pullTrigger();
	*/

	Spiel neuesSpiel(2);
	system("pause");
	return 0;
}