#include <iostream>
#include <string>
#include <vector>
using namespace std;


class SaatAraligi {
public:
	int id;
	string saatAraligi;
	
	vector<SaatAraligi> saatAraliklariniBul();

	SaatAraligi() {
		id = 0;
		saatAraligi = "09:00-11:00";
	}
	
};
