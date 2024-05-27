#include <iostream>
#include <string>
using namespace std;


class DersSaatleri {
public:
	int id;
	int dersId;
	int gunId;
	int saatAraligiId;
	int	section;
	

	void dersinOlacagiGunleriListele();

	DersSaatleri() {
		id = 0;
		dersId = 0;
		gunId = 0;
		section = 0;
		saatAraligiId = 0;
	}
};
