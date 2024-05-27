#include <iostream>
#include <string>
#include <vector>
using namespace std;


class OgrencininAldigiDersler {
public:
	int kullaniciId;
	string kullaniciAdi;
	string kullaniciSoyadi;
	string dersAdi;
	string saatAraligi;
	string dersinGunu;
	int section;
	int kredi;
	

	vector<OgrencininAldigiDersler> ogrencininAldigiDersleriBul(int gelenId);
	vector<OgrencininAldigiDersler> ogretmeninVerdigiDersleriBul(int gelenId);

	OgrencininAldigiDersler() {
		kullaniciId = 0;
		kullaniciAdi = "";
		kullaniciSoyadi = "";
		dersAdi = "";
		saatAraligi = "";
		dersinGunu = "";
		section=0;
		kredi=0;
	}
};
