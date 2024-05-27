#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Gun {
public:
	int id;
	string gunAdi;
	
	vector<Gun> gunleriBul();

	Gun() {
		id = 0;
		gunAdi = "Pazartesi";
	}
	
};
