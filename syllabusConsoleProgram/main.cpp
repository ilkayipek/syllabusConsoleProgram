#include <iostream>
#include "Kullanici.h"
#include "Ders.h"
#include "Gun.h"
#include "Bolum.h"
#include "SaatAraligi.h"
#include "DersSaatleri.h"
#include "OgrencininAldigiDersler.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <string>
#include <mysql.h>
#include <mysqld_error.h>
#include <clocale>
#include <conio.h>



using namespace std;


Kullanici girisYapanKullanici;
Kullanici yeniKullanici;

DersSaatleri dersSaati;
OgrencininAldigiDersler ogrAlinanDers;


OgrencininAldigiDersler ogrAldigiDersler[30];
int index = 0;
const int NOSIZE = 10;
stringstream ss;


vector<Ders>::iterator itDers;
vector<Ders> listofders;

vector<Bolum>::iterator itBolum;
vector<Bolum> listofbolum;


vector<OgrencininAldigiDersler> listofalinacakDersler;
vector<OgrencininAldigiDersler>::iterator itAlinacakDers;
vector<OgrencininAldigiDersler> listofalinanDersler;
vector<OgrencininAldigiDersler> listofyeniEklenenDersler;

vector<OgrencininAldigiDersler>::iterator itOgrVerilenDersler;
vector<OgrencininAldigiDersler> listofOgrVerilenDersler;

vector<Ders>::iterator itAlinanDersler;


vector<Gun>::iterator itGun;
vector<SaatAraligi>::iterator itSaatAraligi;
vector<Kullanici>::iterator itKullanici;
vector<Kullanici> listofkullanici;

vector<DersSaatleri>::iterator itDersSaatleri;
vector<DersSaatleri> listOfDersSaatleri;
vector<Gun> listOfGun;
vector<SaatAraligi> listOfSaatAraligi;


Ders *ders = new Ders;
Kullanici *kullanici = new Kullanici;
DersSaatleri *dersSaatleri = new DersSaatleri;
Bolum *bolum = new Bolum;
OgrencininAldigiDersler *ogrenciAldigiDersler = new OgrencininAldigiDersler;
Gun *gun = new Gun;
SaatAraligi *saatAraligi = new SaatAraligi;
bool dersEklenecek = false;




MYSQL_RES *result;
MYSQL_ROW row;
MYSQL* connection;
MYSQL* obj;
const char* query;

void BoslukBirak(){
	cout << "                       ";
}
void isimeGoreBosluk(int x){
	for(int i=0;i<x;i++){
	cout<<" ";
	}
}

void SecilenDersiSil(OgrencininAldigiDersler gelenDers){
	int bulunanId=0;
	ss << "SELECT tbl_DersSaatleri.dersSaatleriId FROM tbl_OgrencininAldigiDersler,tbl_DersSaatleri,tbl_Ders,tbl_Gun,tbl_SaatAraligi,tbl_Kullanici where tbl_OgrencininAldigiDersler.dersSaatleriId=tbl_DersSaatleri.dersSaatleriId AND tbl_OgrencininAldigiDersler.ogrenciId=tbl_Kullanici.kullaniciId AND tbl_DersSaatleri.dersId=tbl_Ders.dersId AND tbl_DersSaatleri.gunId=tbl_Gun.gunId AND tbl_DersSaatleri.saatAraligiId=tbl_SaatAraligi.saatAralikId AND tbl_Kullanici.kullaniciId = "<< girisYapanKullanici.id <<" AND tbl_Gun.gunAdi = '"<< gelenDers.dersinGunu <<"' AND tbl_SaatAraligi.saatAraligi = '"<< gelenDers.saatAraligi <<"' AND tbl_Ders.dersAdi = '"<< gelenDers.dersAdi <<"'";
	string b = ss.str();
	
	query=b.c_str();
	if(!(mysql_query(connection,query))){

	} else {
		cout << mysql_error(obj);
	}
	
	result = mysql_store_result(connection);
	while(row = mysql_fetch_row(result)){
		bulunanId = atoi(row[0]);
	}
	//cout << "bulunanid= "<< bulunanId << "\n sqlsorgusu: " << b;
	
	ss.str("");
	
	
	ss << "DELETE FROM tbl_OgrencininAldigiDersler WHERE dersSaatleriId="<< bulunanId;
	b = ss.str();
	
	query=b.c_str();
	mysql_query(connection,query);
	
	//cout << "\n" << b;
	
	ss.str("");

	cout << "Ders baþarýyla çýkarýldý.";
	system("PAUSE");
	
	
	
	
	
}

void DersEklemeYap(int id){
	
	ss << "UPDATE tbl_Kullanici set dersProgramiDurumu = 1 where kullaniciId = " << id;
	girisYapanKullanici.dersProgramiDurumu=1;
	string b = ss.str();
	query=b.c_str();
	mysql_query(connection,query);
	ss.str("");
	
	for (itAlinacakDers = listofyeniEklenenDersler.begin(); itAlinacakDers != listofyeniEklenenDersler.end(); ++itAlinacakDers){
		int dersSaatiId=0;
		ss << "SELECT tbl_DersSaatleri.dersSaatleriId FROM tbl_DersSaatleri,tbl_Ders,tbl_Gun,tbl_SaatAraligi where tbl_DersSaatleri.dersId=tbl_Ders.dersId and tbl_DersSaatleri.gunId=tbl_Gun.gunId and tbl_DersSaatleri.saatAraligiId=tbl_SaatAraligi.saatAralikId and tbl_SaatAraligi.saatAraligi='"<< itAlinacakDers -> saatAraligi <<"' and tbl_Gun.gunAdi='"<< itAlinacakDers -> dersinGunu <<"' and tbl_Ders.dersAdi = '"<< itAlinacakDers -> dersAdi <<"' and tbl_DersSaatleri.dersSaatleriSection = "<< itAlinacakDers -> section;
		string b = ss.str();
		
		query=b.c_str();
		if(!(mysql_query(connection,query))){
		//cout << "Kullanici insert edildi.";
		} else {
			cout << "Insert edilirken hata";
		}
		
		result = mysql_store_result(connection);
		while(row = mysql_fetch_row(result)){
			dersSaatiId = atoi(row[0]);
		}
		
		ss.str("");
		ss << "INSERT INTO tbl_OgrencininAldigiDersler(dersSaatleriId,ogrenciId) values (" << dersSaatiId <<","<< girisYapanKullanici.id <<")";
		b = ss.str();
		query=b.c_str();
		mysql_query(connection,query);
		
		ss.str("");
	}

	
	
	cout << "Baþarýyla ders programý seçildi.";
	
}

void dersAdiYazdir(){
	
	cout << itAlinacakDers -> dersAdi;
	
}

void SqlBaglantisi(){
	
	const char* host="185.126.219.150";
	const char* id="gorevlyoruz";
	const char* password="KeUKyTboGeTB4sO";
	const char* dbName="gorevlyoruz_DersProgrami";
	const int port = 3306;
	
	
	

	if(!(obj=mysql_init(0)))
	{
		cout<<"Hata: MYSQL nesnesi olusturulamadý\n\n";
	}
	connection = mysql_real_connect(obj,host,id,password,dbName,port,NULL, 0);
    if(!connection)
    {
    	cout<<mysql_error(obj) << "\n\n";
	}
	else
	{
		cout<<"SQL'e baglanti saglandi\n\n";
	}
	
}

void yeniKullaniciKayitYap(){
	
	//int bolumId = kullanici->bolumu;
	
	ss << "INSERT INTO tbl_Kullanici (kullaniciTipi,dersProgramiDurumu,KullaniciAdi,KullaniciSoyadi,kullaniciSifre,kullaniciBolumu,kullaniciSinifi,kullaniciNo) VALUES (" << kullanici->kullaniciTipi <<","<< kullanici->dersProgramiDurumu <<",'"<< kullanici->adi <<"','"<< kullanici->soyadi <<"','"<< kullanici->sifre <<"',"<< kullanici->bolumu <<",'"<< kullanici->sinifi <<"','"<< kullanici->kullaniciNo <<"')";
	string b = ss.str();
	query = b.c_str();
	//cout << b;
	if(!(mysql_query(connection,query))){
		//cout << "Kullanici insert edildi.";
	} else {
		cout << "Insert edilirken hata";
	}
	
	ss.str("");
	
	
}

//yapýldý
void OgrencininAldigiDersleriBul(){
	
	
	ss.str("");
	listofalinanDersler.clear();
	listofalinacakDersler.clear();
	//HATA ALINAN YER....
	listofalinanDersler = ogrenciAldigiDersler->ogrencininAldigiDersleriBul(girisYapanKullanici.id);
	listofalinacakDersler = ogrenciAldigiDersler->ogrencininAldigiDersleriBul(girisYapanKullanici.id);
	
	
	
	/*ss << "select tbl_Kullanici.kullaniciId,tbl_Kullanici.kullaniciAdi,tbl_Kullanici.kullaniciSoyadi,tbl_Ders.dersAdi,tbl_SaatAraligi.saatAraligi,tbl_Gun.gunAdi,tbl_DersSaatleri.dersSaatleriSection,tbl_Ders.dersKredisi,tbl_Gun.gunId from tbl_OgrencininAldigiDersler,tbl_SaatAraligi,tbl_Gun,tbl_Kullanici,tbl_DersSaatleri,tbl_Ders WHERE tbl_OgrencininAldigiDersler.dersSaatleriId=tbl_DersSaatleri.dersSaatleriId AND tbl_OgrencininAldigiDersler.ogrenciId=tbl_Kullanici.kullaniciId AND tbl_DersSaatleri.dersId=tbl_Ders.dersId AND tbl_DersSaatleri.gunId=tbl_Gun.gunId AND tbl_DersSaatleri.saatAraligiId=tbl_SaatAraligi.saatAralikId and tbl_Kullanici.kullaniciId=" << girisYapanKullanici.id << " order by tbl_SaatAraligi.saatAralikId asc,tbl_Gun.gunId";
	string b = ss.str();
	query = b.c_str();
	//cout << b << endl;
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		
		if(mysql_num_rows(result) > 0){
			while(row = mysql_fetch_row(result)){
				ogrAldigiDersler->kullaniciId=atoi(row[0]);
				ogrAldigiDersler->kullaniciAdi=row[1];
				ogrAldigiDersler->kullaniciSoyadi=row[2];
				ogrAldigiDersler->dersAdi=row[3];
				ogrAldigiDersler->saatAraligi=row[4];
				ogrAldigiDersler->dersinGunu=row[5];
				ogrAldigiDersler->section=atoi(row[6]);
				ogrAldigiDersler->kredi=atoi(row[7]);
				
				listofalinanDersler.push_back(*ogrAldigiDersler);
				listofalinacakDersler.push_back(*ogrAldigiDersler);
				
			}
		}
		
	} else {
		cout<<mysql_error(connection);
	}
	ss.str("");*/

	
	
	
}

void OgrencininDersProgramiTamamlandi(int id){
	ss << "UPDATE tbl_Kullanici set dersProgramiDurumu = 1 where kullaniciId = " << id;
	girisYapanKullanici.dersProgramiDurumu=1;
	string b = ss.str();
	query=b.c_str();
	mysql_query(connection,query);
	ss.str("");
	
	for (itAlinacakDers = listofalinacakDersler.begin(); itAlinacakDers != listofalinacakDersler.end(); ++itAlinacakDers){
		int dersSaatiId=0;
		ss << "SELECT tbl_DersSaatleri.dersSaatleriId FROM tbl_DersSaatleri,tbl_Ders,tbl_Gun,tbl_SaatAraligi where tbl_DersSaatleri.dersId=tbl_Ders.dersId and tbl_DersSaatleri.gunId=tbl_Gun.gunId and tbl_DersSaatleri.saatAraligiId=tbl_SaatAraligi.saatAralikId and tbl_SaatAraligi.saatAraligi='"<< itAlinacakDers -> saatAraligi <<"' and tbl_Gun.gunAdi='"<< itAlinacakDers -> dersinGunu <<"' and tbl_Ders.dersAdi = '"<< itAlinacakDers -> dersAdi <<"' and tbl_DersSaatleri.dersSaatleriSection = "<< itAlinacakDers -> section;
		string b = ss.str();
		
		query=b.c_str();
		if(!(mysql_query(connection,query))){
		//cout << "Kullanici insert edildi.";
		} else {
			cout << "Insert edilirken hata";
		}
		
		result = mysql_store_result(connection);
		while(row = mysql_fetch_row(result)){
			dersSaatiId = atoi(row[0]);
		}
		
		ss.str("");
		ss << "INSERT INTO tbl_OgrencininAldigiDersler(dersSaatleriId,ogrenciId) values (" << dersSaatiId <<","<< girisYapanKullanici.id <<")";
		b = ss.str();
		query=b.c_str();
		mysql_query(connection,query);
		
		ss.str("");
	}

	
	
	cout << "Baþarýyla ders programý seçildi.";
}

//yapýldý
void GunVeSaatleriAta(){
	
	/*
	ss << "SELECT * FROM tbl_Gun";
	string b = ss.str();
	query = b.c_str();
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		while(row = mysql_fetch_row(result)){
			gun -> id = atoi(row[0]);
			gun -> gunAdi = row[1];

			listOfGun.push_back(*gun);
		}
	} else {
		cout << "Hata gun" << endl;
	}
	ss.str("");*/
	
	
	listOfGun = gun->gunleriBul();
	
	
	
	
	/*ss << "SELECT * FROM tbl_SaatAraligi";
	string b = ss.str();
	query = b.c_str();
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		while(row = mysql_fetch_row(result)){
			saatAraligi -> id = atoi(row[0]);
			saatAraligi -> saatAraligi = row[1];

			listOfSaatAraligi.push_back(*saatAraligi);
		}
	} else {
		cout << "Hata saat araligi" << endl;
	}
	ss.str("");*/
	
	listOfSaatAraligi = saatAraligi->saatAraliklariniBul();
	
	
	
	
}

void OgrenciMenusu() {
	listofalinacakDersler.clear();
	OgrencininAldigiDersleriBul();
	int dersSecim = -1;
	bool alinanDersSecimi = 1;
	cout << "Hosgeldiniz: " << girisYapanKullanici.adi << " " << girisYapanKullanici.soyadi << endl;
	int dersGunIndex=0;

	if (girisYapanKullanici.dersProgramiDurumu == 0) {
		cout << "\nDers programiniz olusturulmadi.";
		//cin >> girisYapanKullanici.sinifi;
		
		
		
		system("CLS");

		do
		{
			alinanDersSecimi = 1;
			index = 0;
			cout << "Dersler:\n";
			
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

			
			for (itDers = listofders.begin(); itDers != listofders.end(); ++itDers) {
				index++;
				
        		cout << index << "-) " << itDers->dersAdi;
        		for(int i=0; i<60-(itDers->dersAdi.length());i++){
					cout << " ";
				}
        		cout << itDers->kredisi << " kredi \t" << itDers->section <<  ". section \t"  << itDers->saatAraligi << "\t" << itDers->dersGunu << " günü" << endl;
        		
        		
        	}
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


			
			cout << "\n\nAlinan Dersler:\n";
			
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			index = 0;
			
			for (itAlinacakDers = listofalinacakDersler.begin(); itAlinacakDers != listofalinacakDersler.end(); ++itAlinacakDers) {
				index++;
				
				cout << index << "-) " << itAlinacakDers->dersAdi;
        		for(int i=0; i<60-(itAlinacakDers->dersAdi.length());i++){
					cout << " ";
				}
				cout << itAlinacakDers->kredi << " kredi \t" << itAlinacakDers->section <<  ". section \t"  << itAlinacakDers->saatAraligi << "\t" << itAlinacakDers->dersinGunu << " günü" << endl;
	
			}
			
			for (itAlinacakDers = listofyeniEklenenDersler.begin(); itAlinacakDers != listofyeniEklenenDersler.end(); ++itAlinacakDers) {
				index++;
				
				cout << index << "-) " << itAlinacakDers->dersAdi;
        		for(int i=0; i<60-(itAlinacakDers->dersAdi.length());i++){
					cout << " ";
				}
				cout << itAlinacakDers->kredi << " kredi \t" << itAlinacakDers->section <<  ". section \t"  << itAlinacakDers->saatAraligi << "\t" << itAlinacakDers->dersinGunu << " günü" << endl;
	
			}
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


			
			cout << "\nLutfen alinacak dersleri seciniz. Ders secimi bittiginde 0'a basiniz." << endl;
			do
			{
				cin >> dersSecim;
				if (!dersSecim) {
					break;
				}

				if (dersSecim > listofders.size() || dersSecim < 0) {
					cout << "Hatali secim!" << endl;
				}
				else {
					index = 0;

					for (itAlinacakDers = listofalinacakDersler.begin(); itAlinacakDers != listofalinacakDersler.end(); ++itAlinacakDers)
					{

						if ((listofders[dersSecim - 1].dersAdi == itAlinacakDers[0].dersAdi) || ( listofders[dersSecim - 1].dersGunu == itAlinacakDers[0].dersinGunu && listofders[dersSecim - 1].saatAraligi == itAlinacakDers[0].saatAraligi ) ) {
							system("CLS");
							cout << "Bu dersin baska section'unu sectiniz veya çakýþan ders seçtiniz!" << endl;
							alinanDersSecimi = 0;
							break;

						}
						index++;
					}
					index = 0;
					if (alinanDersSecimi) {
						system("CLS");
						if (dersSecim != 0 && dersSecim > 0) {
							
							if(dersEklenecek){
								ogrenciAldigiDersler -> kullaniciId = girisYapanKullanici.id;
								ogrenciAldigiDersler -> kullaniciAdi = girisYapanKullanici.adi;
								ogrenciAldigiDersler -> kullaniciSoyadi = girisYapanKullanici.soyadi;
								ogrenciAldigiDersler -> dersAdi = listofders[dersSecim - 1].dersAdi;
								
								ogrenciAldigiDersler -> saatAraligi = listofders[dersSecim - 1].saatAraligi;
								ogrenciAldigiDersler -> dersinGunu = listofders[dersSecim - 1].dersGunu;
								ogrenciAldigiDersler -> section = listofders[dersSecim - 1].section;
								ogrenciAldigiDersler -> kredi = listofders[dersSecim - 1].kredisi;	
								
								listofyeniEklenenDersler.push_back(*ogrenciAldigiDersler);
							} 
							else {
								ogrenciAldigiDersler -> kullaniciId = girisYapanKullanici.id;
								ogrenciAldigiDersler -> kullaniciAdi = girisYapanKullanici.adi;
								ogrenciAldigiDersler -> kullaniciSoyadi = girisYapanKullanici.soyadi;
								ogrenciAldigiDersler -> dersAdi = listofders[dersSecim - 1].dersAdi;
								
								ogrenciAldigiDersler -> saatAraligi = listofders[dersSecim - 1].saatAraligi;
								ogrenciAldigiDersler -> dersinGunu = listofders[dersSecim - 1].dersGunu;
								ogrenciAldigiDersler -> section = listofders[dersSecim - 1].section;
								ogrenciAldigiDersler -> kredi = listofders[dersSecim - 1].kredisi;	
								
								listofalinacakDersler.push_back(*ogrenciAldigiDersler);
							}
							

						}
					}

					

					index = 0;
					break;
				}
			} while (true);
			
			

		
		} while (dersSecim!=0);
		cout << "Ders secim islemi basariyla tamamlandi!."<< endl;
		
		if(dersEklenecek){
			DersEklemeYap(girisYapanKullanici.id);
			listofyeniEklenenDersler.clear();
			dersEklenecek=false;
		}
		else {
			OgrencininDersProgramiTamamlandi(girisYapanKullanici.id);
			listofalinacakDersler.clear();
		}
		
		system("PAUSE");
		
		OgrenciMenusu();

	}
	else {
		
		system("CLS");
		
		int kullaniciSecimi=0;
		int dersGunIndex=0;
		int adCount = 0;
		int satirAraligi= 23;
		
		cout << "Ders programi zaten sectiniz. Ders programiniz þu þekildedir. \n \n";
		int boyut = listofalinanDersler.size();
		cout << "\t\t";
		for (itGun = listOfGun.begin(); itGun != listOfGun.end(); ++itGun) {
			adCount = itGun -> gunAdi.size();
			cout << itGun -> gunAdi ;	
			isimeGoreBosluk(satirAraligi - adCount);
		}
		for (itSaatAraligi = listOfSaatAraligi.begin(); itSaatAraligi != listOfSaatAraligi.end(); ++itSaatAraligi) {
			cout << "\n\n\n " << itSaatAraligi -> saatAraligi << "\t";
			
			
			for (itAlinacakDers = listofalinanDersler.begin(); itAlinacakDers != listofalinanDersler.end(); ++itAlinacakDers) {
			if(itAlinacakDers -> saatAraligi == itSaatAraligi -> saatAraligi){
				// && itAlinacakDers -> dersinGunu == dersGunIndex
				if(itAlinacakDers -> dersinGunu == "Pazartesi" && itAlinacakDers -> saatAraligi == itSaatAraligi -> saatAraligi){
					cout << itAlinacakDers -> dersAdi;
					 adCount = itAlinacakDers -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itAlinacakDers[0].dersAdi != listofalinanDersler.at(boyut-1).dersAdi)
						++itAlinacakDers;
				} else {
					BoslukBirak();
				}
				
				if(itAlinacakDers -> dersinGunu == "Sali" && itAlinacakDers -> saatAraligi == itSaatAraligi -> saatAraligi){
				cout << itAlinacakDers -> dersAdi;
					 adCount = itAlinacakDers -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itAlinacakDers[0].dersAdi != listofalinanDersler.at(boyut-1).dersAdi)
						++itAlinacakDers;
				} else {
					BoslukBirak();
				}
				
				if(itAlinacakDers -> dersinGunu == "Carsamba" && itAlinacakDers -> saatAraligi == itSaatAraligi -> saatAraligi){
					cout << itAlinacakDers -> dersAdi;
					 adCount = itAlinacakDers -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itAlinacakDers[0].dersAdi != listofalinanDersler.at(boyut-1).dersAdi)
						++itAlinacakDers;
				} else {
					BoslukBirak();
				}
				
				if(itAlinacakDers -> dersinGunu == "Persembe" && itAlinacakDers -> saatAraligi == itSaatAraligi -> saatAraligi){
					cout << itAlinacakDers -> dersAdi;
					 adCount = itAlinacakDers -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itAlinacakDers[0].dersAdi != listofalinanDersler.at(boyut-1).dersAdi)
						++itAlinacakDers;
				} else {
					BoslukBirak();
				}
				
				if(itAlinacakDers -> dersinGunu == "Cuma" && itAlinacakDers -> saatAraligi == itSaatAraligi -> saatAraligi){
					cout << itAlinacakDers -> dersAdi;
					 adCount = itAlinacakDers -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itAlinacakDers[0].dersAdi != listofalinanDersler.at(boyut-1).dersAdi)
						++itAlinacakDers;
				} else {
					BoslukBirak();
				}
				break;
				itAlinacakDers = listofalinanDersler.end();
				
				
			}
			
			
		}
			
			//bura:
			dersGunIndex++;
		}
		
		
		cout<<"\n\n";
		int silinecekDersId=0;
		cout<<"1-Ders ekle\n";
		cout<<"2-Ders sil\n";
		cout<<"0-Çýkýþ\n";
		
		cin >> kullaniciSecimi;
		
		switch(kullaniciSecimi){
			
		case 0:
			
			break;
		
		case 1:
			girisYapanKullanici.dersProgramiDurumu = 0;
			dersEklenecek=true;
			OgrenciMenusu();
			//seçilen ders ekleme yapýlýrken if ile kontrol edilecek
			
			break;
			
			
		case 2:
			
			
			listofalinacakDersler.clear();
			OgrencininAldigiDersleriBul();
			
			cout << "\n\nAlinan Dersler:\n";
			
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			index = 0;
			
			for (itAlinacakDers = listofalinacakDersler.begin(); itAlinacakDers != listofalinacakDersler.end(); ++itAlinacakDers) {
				index++;
				
				cout << index << "-) " << itAlinacakDers->dersAdi;
        		for(int i=0; i<60-(itAlinacakDers->dersAdi.length());i++){
					cout << " ";
				}
				cout << itAlinacakDers->kredi << " kredi \t" << itAlinacakDers->section <<  ". section \t"  << itAlinacakDers->saatAraligi << "\t" << itAlinacakDers->dersinGunu << " günü" << endl;
	
			}
			
			cout << "Silinecek dersi seçiniz: ";
			cin >> silinecekDersId;
			
			
			SecilenDersiSil(listofalinacakDersler.at(silinecekDersId-1));
			OgrenciMenusu();
			
			break;
			
			
		default:
			cout << "Hatalý secim !";
			system("PAUSE");
			system("CLS");
			OgrenciMenusu();
			
			break;	
			
			
		}
		system("CLS");
			
		
	}

}

//yapýldý
void ogretmeninVerdigiDersleriBul(){ 
	
	
	listofOgrVerilenDersler = ogrAldigiDersler -> ogretmeninVerdigiDersleriBul(girisYapanKullanici.id);
	/*
    ss << "select tbl_Ders.dersAdi,tbl_SaatAraligi.saatAraligi,tbl_Gun.gunAdi from tbl_SaatAraligi,tbl_Kullanici,tbl_DersSaatleri,tbl_Ders,tbl_Gun WHERE tbl_DersSaatleri.dersId=tbl_Ders.dersId AND tbl_DersSaatleri.gunId=tbl_Gun.gunId AND tbl_DersSaatleri.saatAraligiId=tbl_SaatAraligi.saatAralikId and tbl_Kullanici.kullaniciId="<<girisYapanKullanici.id<<" and tbl_Kullanici.kullaniciId=tbl_Ders.dersOgretimGorevlisi order by tbl_SaatAraligi.saatAralikId asc,tbl_Gun.gunId";
    
    string b = ss.str();
    query = b.c_str();
    if(!(mysql_query(connection,query))){
        result = mysql_store_result(connection);
        
        if(mysql_num_rows(result) > 0){
            while(row = mysql_fetch_row(result)){
                ogrAldigiDersler->dersAdi=row[0];
                ogrAldigiDersler->saatAraligi=row[1];
                ogrAldigiDersler->dersinGunu=row[2];

                
                listofOgrVerilenDersler.push_back(*ogrAldigiDersler);
            }
        }
        
    } else {
        cout<<mysql_error(connection);
    }
    ss.str("");*/
    
    
}

void OgretmenMenusu() {
	system("CLS");
	ogretmeninVerdigiDersleriBul();	
	int dersGunIndex=0;
	int adCount = 0;
	int satirAraligi= 23;
	cout << "\n Öðretmen menüsüne hoþ geldiniz... \n \n Ders programýz: \n \n";
	int boyut = listofOgrVerilenDersler.size();
	cout << "\t\t";
	
	for (itGun = listOfGun.begin(); itGun != listOfGun.end(); ++itGun) {
		adCount = itGun -> gunAdi.size();
		cout << itGun -> gunAdi ;	
		isimeGoreBosluk(satirAraligi - adCount);
	}
	for (itSaatAraligi = listOfSaatAraligi.begin(); itSaatAraligi != listOfSaatAraligi.end(); ++itSaatAraligi) {
		cout << "\n\n\n " << itSaatAraligi -> saatAraligi << "\t";
		
		for (itOgrVerilenDersler = listofOgrVerilenDersler.begin(); itOgrVerilenDersler != listofOgrVerilenDersler.end(); ++itOgrVerilenDersler) {
			if(itOgrVerilenDersler -> saatAraligi == itSaatAraligi -> saatAraligi){
				// && itOgrVerilenDersler -> dersinGunu == dersGunIndex
				if(itOgrVerilenDersler -> dersinGunu == "Pazartesi"){
					cout << itOgrVerilenDersler -> dersAdi;
					 adCount = itOgrVerilenDersler -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itOgrVerilenDersler[0].dersAdi != listofOgrVerilenDersler.at(boyut-1).dersAdi)
						++itOgrVerilenDersler;
				} else {
					BoslukBirak();
				}
				
				if(itOgrVerilenDersler -> dersinGunu == "Sali"){
				cout << itOgrVerilenDersler -> dersAdi;
					 adCount = itOgrVerilenDersler -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itOgrVerilenDersler[0].dersAdi != listofOgrVerilenDersler.at(boyut-1).dersAdi)
						++itOgrVerilenDersler;
				} else {
					BoslukBirak();
				}
				
				if(itOgrVerilenDersler -> dersinGunu == "Carsamba"){
					cout << itOgrVerilenDersler -> dersAdi;
					 adCount = itOgrVerilenDersler -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itOgrVerilenDersler[0].dersAdi != listofOgrVerilenDersler.at(boyut-1).dersAdi)
						++itOgrVerilenDersler;
				} else {
					BoslukBirak();
				}
				
				if(itOgrVerilenDersler -> dersinGunu == "Persembe"){
					cout << itOgrVerilenDersler -> dersAdi;
					 adCount = itOgrVerilenDersler -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itOgrVerilenDersler[0].dersAdi != listofOgrVerilenDersler.at(boyut-1).dersAdi)
						++itOgrVerilenDersler;
				} else {
					BoslukBirak();
				}
				
				if(itOgrVerilenDersler -> dersinGunu == "Cuma"){
					cout << itOgrVerilenDersler -> dersAdi;
					 adCount = itOgrVerilenDersler -> dersAdi.size();
					isimeGoreBosluk(satirAraligi - adCount);
					if(itOgrVerilenDersler[0].dersAdi != listofOgrVerilenDersler.at(boyut-1).dersAdi)
						++itOgrVerilenDersler;
				} else {
					BoslukBirak();
				}
				break;
				itOgrVerilenDersler = listofOgrVerilenDersler.end();
				
				
			}
			
			
		}
		
		//bura:
		dersGunIndex++;
	}
	
	
	
	cout<<"\n\n";
	system("PAUSE");
	system("CLS");
		
		
		
}

//yapýldý
void kullanicilariAta() {
	
	listofkullanici = kullanici->kullanicilariBul();
	
	
/*
	ss << "SELECT * FROM tbl_Kullanici";
	string b = ss.str();
	query = b.c_str();
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		while(row = mysql_fetch_row(result)){
			kullanici -> id = atoi(row[0]);
			kullanici -> kullaniciTipi = atoi(row[1]);
			kullanici -> dersProgramiDurumu = atoi(row[2]);
			kullanici -> adi = row[3];
			kullanici -> soyadi = row[4];
			kullanici -> sifre = row[5];
			kullanici -> bolumu = atoi(row[6]);
			kullanici -> sinifi = atoi(row[7]);
			kullanici -> kullaniciNo = row[8];
			listofkullanici.push_back(*kullanici);
		}
	} else {
		cout << "Hata kullanici" << endl;
	}
	ss.str("");*/
	

}

void dersleriAta() {
	
	
	listofders = ders->dersleriBul();
	
	/*
	ss << "SELECT tbl_Ders.dersId,tbl_Ders.dersAdi,tbl_DersSaatleri.dersSaatleriSection,tbl_SaatAraligi.saatAraligi,tbl_Ders.dersKredisi,tbl_Kullanici.kullaniciId,tbl_Gun.gunAdi FROM tbl_Ders,tbl_SaatAraligi,tbl_DersSaatleri,tbl_Gun,tbl_Kullanici where tbl_SaatAraligi.saatAralikId=tbl_DersSaatleri.saatAraligiId and tbl_DersSaatleri.dersId=tbl_Ders.dersId and tbl_Ders.dersOgretimGorevlisi=tbl_Kullanici.kullaniciId and tbl_DersSaatleri.gunId = tbl_Gun.gunId order by tbl_Ders.dersAdi ASC,tbl_DersSaatleri.dersSaatleriSection ASC";
	string b = ss.str();
	query = b.c_str();
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		while(row = mysql_fetch_row(result)){
			ders -> dersId = atoi(row[0]);
			ders -> dersAdi = row[1];
			ders -> section = atoi(row[2]);
			ders -> saatAraligi = row[3];
			ders -> kredisi = atoi(row[4]);
			ders -> ogretimGorevlisi = atoi(row[5]);
			ders -> dersGunu = row[6];
						
			listofders.push_back(*ders);
		}
	} else {
		cout << "Hata ders" << endl;
	}
	ss.str("");*/
	
	

}

void listTemizle(){
	listofkullanici.clear();
	listofders.clear();
	listofalinacakDersler.clear();
	listOfDersSaatleri.clear();
	listofbolum.clear();
	listofalinanDersler.clear();
	listOfGun.clear();
	listOfSaatAraligi.clear();
	listofyeniEklenenDersler.clear();
	
}

void bolumleriBulupListele(){
	
	ss << "SELECT * FROM tbl_Bolum";
	string b = ss.str();
	query = b.c_str();
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		
		if(mysql_num_rows(result) > 0){
			while(row = mysql_fetch_row(result)){
				bolum->id=atoi(row[0]);
				bolum->bolumAdi = row[1];
				listofbolum.push_back(*bolum);
			}
		}
		
	} else {
		cout<<mysql_error(connection);
	}
	ss.str("");
	
	
	
	
			
	for (itBolum = listofbolum.begin(); itBolum != listofbolum.end(); ++itBolum) {
		cout << itBolum->id << "-) " << itBolum->bolumAdi << endl;
	}
	
	
	
}

void DersSaatleriniAta(){
	
	ss << "SELECT * FROM tbl_DersSaatleri";
	string b = ss.str();
	query = b.c_str();
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		
		if(mysql_num_rows(result) > 0){
			while(row = mysql_fetch_row(result)){
				dersSaatleri->id=atoi(row[0]);
				dersSaatleri->section = atoi(row[1]);
				dersSaatleri->dersId=atoi(row[2]);
				dersSaatleri->gunId=atoi(row[3]);
				dersSaatleri->saatAraligiId=atoi(row[4]);
				listOfDersSaatleri.push_back(*dersSaatleri);
			}
		}
		
	} else {
		cout<<mysql_error(connection);
	}
	ss.str("");
	
	
}

int main(int argc, char** argv) {
	setlocale(0, "turkish");
	int kullaniciSecimi = 0;
	girisYapanKullanici = Kullanici();
	
	do
	{
		listTemizle();
		SqlBaglantisi();
		kullanicilariAta();
		dersleriAta();
		
		DersSaatleriniAta();
		GunVeSaatleriAta();
		bool girisYap = 0;
		girisYapanKullanici = Kullanici();
		cout << "Ders programi olusturma sistemi" << endl;
		cout << "0-Cikis" << endl;
		cout << "1-Kullanici girisi yap" << endl;
		cout << "2-Kayit ol" << endl;
		cin >> kullaniciSecimi;
		system("CLS");
		switch (kullaniciSecimi)
		{
		case 0:
			exit(0);
			break;
		case 1:
			cout << "Giris yapma" << endl;
			system("CLS");
			cout << "Kullanici no giriniz:.. " << endl;
			cin >> girisYapanKullanici.kullaniciNo;
			cout << "Sifreyi giriniz:.. " << endl;
			cin >> girisYapanKullanici.sifre;
			
			
			
			for (itKullanici = listofkullanici.begin(); itKullanici != listofkullanici.end(); ++itKullanici) {
				if(itKullanici[0].kullaniciNo == girisYapanKullanici.kullaniciNo && itKullanici[0].sifre == girisYapanKullanici.sifre){
					girisYapanKullanici = itKullanici[0];
					if (itKullanici[0].kullaniciTipi == 0) {
						OgrenciMenusu();
					}
					else {
						OgretmenMenusu();
					}
					girisYap = 1;
					break;
				}
				
			}
			

			system("CLS");
			if(!girisYap)
				cout << "Kullanici no veya sifre yanlis !\n\n" << endl;
			break;
		case 2:
			int girisTipi=0;
			int bolumTipi=0;
			cout << "Kayit olma" << endl;
			
			cout << "1-Ogretmen kaydi" << endl;
			cout << "2-Ogrenci kaydi" << endl;
			
			do{
				cin >> girisTipi;
				if(girisTipi==1){
					kullanici->kullaniciTipi =true;
					break;
				} else if (girisTipi==2){
					kullanici->kullaniciTipi =false;
					kullanici->dersProgramiDurumu=false;
					break;
				}
			}while(true);
			
			system("CLS");

			
			cout << "Adiniz..> ";
			cin >> kullanici -> adi;
			
			cout << "Soyadiniz..> ";
			cin >> kullanici -> soyadi;

			if (!kullanici->kullaniciTipi) {
				cout << "Sinifiniz..> ";
				cin >> kullanici->sinifi;
				
				
				bolumleriBulupListele();
				
				cin >> bolumTipi;
				kullanici->bolumu=bolumTipi;
			}
			
			
			
			do{
				
				cout << "Sifrenizi giriniz (Sifreniz en az 8 karakter olmali) \nSifrenizde kucuk, buyuk karakter ve mutlaka ozel karakter icermelidir (!,#,$,%,&,')) ..> " << endl;
				cin >> kullanici -> sifre;
				
				
				
				bool ozelKarakter = false;
				bool buyukKarakter = false;
				bool kucukKarakter = false;
				bool sekizKarakter = false;
				int ascii=0;
				
				if(kullanici[0].sifre.length() >= 8){
					sekizKarakter=true;
				}

				
				for(int i=0;i< kullanici[0].sifre.length();i++){
					ascii= kullanici[0].sifre[i];
					if(ascii <= 39 && ascii >=33)
						ozelKarakter=true;
					if(ascii <= 90 && ascii >=65)
						buyukKarakter=true;
					if(ascii <= 122 && ascii >=97)
						kucukKarakter=true;	
				}
				
				if(ozelKarakter && buyukKarakter && kucukKarakter && sekizKarakter)
					break;
				else{
					cout << "Lutfen sifre kurallarina uyarak sifre olusturunuz." << endl;
				}
				cin.get();
				
			}while(true);

			
			srand(time(0));


			kullanici->kullaniciNo = "1234567890";

			int i, r;
			int yeniOgrNo[NOSIZE];
			vector<int> digits;
			for (i = 0; i < NOSIZE; i++)
				digits.push_back(i);

			srand(time(0));
			for (i = 0; i < NOSIZE; i++)
			{
				r = rand() % (NOSIZE - i);
				yeniOgrNo[i] = digits[r];
				digits.erase(digits.begin() + r);
			}
			cout << "\n\n\nBasariyla kayit oldunuz. \nKullanici numaraniz: ";
			for (i = 0; i < NOSIZE; i++)
				cout << yeniOgrNo[i];

			cout << "\n";


			ostringstream os;

			
			for (int i = 0; i < NOSIZE; i++) {
				os << yeniOgrNo[i];
			}
			
			string str(os.str());




			kullanici->kullaniciNo = str;


			cout << "Sifreniz: " << kullanici[0].sifre << endl;
			cout << "Lutfen kullanici numaranizi ve sifrenizi not aliniz.\nDevam etmek icin herhangi bir tusa basiniz." << endl;

			

			listofkullanici.push_back(*kullanici);
			
			
			yeniKullaniciKayitYap();
		
			system("PAUSE");
			system("CLS");
			
			
			
			break;
		
		}
		

	} while (true);
	
	
	
	return 0;
}

