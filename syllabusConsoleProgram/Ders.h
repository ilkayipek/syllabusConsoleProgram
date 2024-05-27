#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Ders {
public:
	int dersId;                 
	string dersAdi;         
	int section;            
	string saatAraligi;
	string dersGunu;     
	int kredisi;            
	string ogretimGorevlisi;



	vector<Ders> dersleriBul();
	
	Ders() {
		dersId = 0;
		dersAdi = "";
		section = 0;
		saatAraligi = "";
		kredisi = 0;
		dersGunu = "";
		ogretimGorevlisi = "";
	}

	
	
};
