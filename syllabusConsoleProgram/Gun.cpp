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



vector<Gun> Gun::gunleriBul() {
	
	const char* host="185.126.219.150";
	const char* id="gorevlyoruz";
	const char* password="KeUKyTboGeTB4sO";
	const char* dbName="gorevlyoruz_DersProgrami";
	const int port = 3306;
	
	vector<Gun> listOfGun;
	Gun *gun = new Gun;
	stringstream ss;
	MYSQL* connection;
	MYSQL* obj;

	MYSQL_RES *result;
	MYSQL_ROW row;
	
	const char* query;
	listOfGun.clear();
	

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
	ss.str("");

	return listOfGun;
	
	
}





