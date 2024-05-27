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

vector<Kullanici> Kullanici::kullanicilariBul() {
	
	
	const char* host="185.126.219.150";
	const char* id="gorevlyoruz";
	const char* password="KeUKyTboGeTB4sO";
	const char* dbName="gorevlyoruz_DersProgrami";
	const int port = 3306;
	
	Kullanici *kullanici = new Kullanici;
	vector<Kullanici> listofkullanici;
	stringstream ss;
	MYSQL* connection;
	MYSQL* obj;

	MYSQL_RES *result;
	MYSQL_ROW row;
	
	const char* query;
	listofkullanici.clear();
	
	
	
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
	ss.str("");
	
	
	return listofkullanici;
	

}





