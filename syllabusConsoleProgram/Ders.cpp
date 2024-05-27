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
vector<Ders> Ders::dersleriBul() {
	
	const char* host="185.126.219.150";
	const char* id="gorevlyoruz";
	const char* password="KeUKyTboGeTB4sO";
	const char* dbName="gorevlyoruz_DersProgrami";
	const int port = 3306;
	
	vector<Ders> listofders;
	Ders *ders = new Ders;
	
	stringstream ss;
	MYSQL* connection;
	MYSQL* obj;

	MYSQL_RES *result;
	MYSQL_ROW row;
	
	const char* query;
	listofders.clear();
	

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
		//cout<<"SQL'e baglanti saglandi\n\n";
	}
	
	
	
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
	ss.str("");

	return listofders;
	
}





