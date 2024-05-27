#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Kullanici{
	public:
		int id;
		string adi;
		string soyadi;
		bool kullaniciTipi; //0=ogrenci    1=ogretmen
		string kullaniciNo;
		string sifre;
		int bolumu;
		string sinifi;
		bool dersProgramiDurumu;
		

		vector<Kullanici> kullanicilariBul();

		Kullanici() {
			id = 0;
			adi = "isim1";
			soyadi = "soyad1";
			kullaniciTipi = 0;
			kullaniciNo = "123123";
			sifre = "123";
			bolumu = 0;
			sinifi = "-";
			dersProgramiDurumu = 0;
		}
};
