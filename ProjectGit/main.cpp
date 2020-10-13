#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;


class Revolver {

	bool cylinder[6] = { 0, 0, 0, 0, 0, 0 };
public:
	int spin() {
		cout << "Spin...";
		Sleep(1000);
		srand((unsigned int)time(NULL));
		int num = 0;
		num = (rand() %
			(5 - 0 + 1)) + 0;
		cout << "chamber " << num << "\n";
		return num;
	}

	void laden(int anzahlPatronen) {
		bool loaded;
		cout << "Es werden " << anzahlPatronen << " geladen \n";
		for (int i = 0; i < anzahlPatronen; i++) {
			int chamber = 0;
			loaded = false;
			do {
				chamber = spin();
				if (cylinder[chamber] == 0) {
					cylinder[chamber] = 1;
					loaded = true;
					cout << "round loaded...\n";
				}
				else {
					cout << "Chamber is already loaded, new chamber...\n";
				}
			} while (!loaded);
		}
		cout << "All rounds loaded...\n";
	}
public:
	void pullTrigger() {
		if (cylinder[spin()] == true) {
			cout << "rip\n";
		}
		else {
			cout << "lucky..\n";
		}
	}
};

int main() {
	Revolver revolver1;
	cout << "How many rounds should be loaded? \n";
	int rounds;
	cin >> rounds;
	revolver1.laden(rounds);
	revolver1.pullTrigger();

	system("pause");
	return 0;
}