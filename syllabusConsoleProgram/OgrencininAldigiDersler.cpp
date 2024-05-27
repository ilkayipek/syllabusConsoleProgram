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

vector<OgrencininAldigiDersler> OgrencininAldigiDersler::ogrencininAldigiDersleriBul(int gelenId) {
	
	
	const char* host="185.126.219.150";
	const char* id="gorevlyoruz";
	const char* password="KeUKyTboGeTB4sO";
	const char* dbName="gorevlyoruz_DersProgrami";
	const int port = 3306;
	
	OgrencininAldigiDersler *ogrenciAldigiDersler = new OgrencininAldigiDersler;
	
	vector<OgrencininAldigiDersler> listofalinanDersler;
	stringstream ss;
	MYSQL* connection;
	MYSQL* obj;

	MYSQL_RES *result;
	MYSQL_ROW row;
	
	const char* query;
	listofalinanDersler.clear();
	
	
	
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
	
	
	ss << "select tbl_Kullanici.kullaniciId,tbl_Kullanici.kullaniciAdi,tbl_Kullanici.kullaniciSoyadi,tbl_Ders.dersAdi,tbl_SaatAraligi.saatAraligi,tbl_Gun.gunAdi,tbl_DersSaatleri.dersSaatleriSection,tbl_Ders.dersKredisi,tbl_Gun.gunId from tbl_OgrencininAldigiDersler,tbl_SaatAraligi,tbl_Gun,tbl_Kullanici,tbl_DersSaatleri,tbl_Ders WHERE tbl_OgrencininAldigiDersler.dersSaatleriId=tbl_DersSaatleri.dersSaatleriId AND tbl_OgrencininAldigiDersler.ogrenciId=tbl_Kullanici.kullaniciId AND tbl_DersSaatleri.dersId=tbl_Ders.dersId AND tbl_DersSaatleri.gunId=tbl_Gun.gunId AND tbl_DersSaatleri.saatAraligiId=tbl_SaatAraligi.saatAralikId and tbl_Kullanici.kullaniciId=" << gelenId << " order by tbl_SaatAraligi.saatAralikId asc,tbl_Gun.gunId";
	string b = ss.str();
	query = b.c_str();
	//cout << b << endl;
	if(!(mysql_query(connection,query))){
		result = mysql_store_result(connection);
		
		if(mysql_num_rows(result) > 0){
			while(row = mysql_fetch_row(result)){
				ogrenciAldigiDersler->kullaniciId=atoi(row[0]);
				ogrenciAldigiDersler->kullaniciAdi=row[1];
				ogrenciAldigiDersler->kullaniciSoyadi=row[2];
				ogrenciAldigiDersler->dersAdi=row[3];
				ogrenciAldigiDersler->saatAraligi=row[4];
				ogrenciAldigiDersler->dersinGunu=row[5];
				ogrenciAldigiDersler->section=atoi(row[6]);
				ogrenciAldigiDersler->kredi=atoi(row[7]);
				
				listofalinanDersler.push_back(*ogrenciAldigiDersler);
				
			}
		}
		
	} else {
		cout<<mysql_error(connection);
	}
	ss.str("");
	
	
	
	return listofalinanDersler;
	

}

vector<OgrencininAldigiDersler> OgrencininAldigiDersler::ogretmeninVerdigiDersleriBul(int gelenId) {
	
	
	const char* host="185.126.219.150";
	const char* id="gorevlyoruz";
	const char* password="KeUKyTboGeTB4sO";
	const char* dbName="gorevlyoruz_DersProgrami";
	const int port = 3306;
	
	OgrencininAldigiDersler *ogrAldigiDersler = new OgrencininAldigiDersler;
	
	vector<OgrencininAldigiDersler> listofOgrVerilenDersler;
	stringstream ss;
	MYSQL* connection;
	MYSQL* obj;

	MYSQL_RES *result;
	MYSQL_ROW row;
	
	const char* query;
	listofOgrVerilenDersler.clear();
	
	
	
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
	
	
	
	ss.str("");
	ss << "select tbl_Ders.dersAdi,tbl_SaatAraligi.saatAraligi,tbl_Gun.gunAdi from tbl_SaatAraligi,tbl_Kullanici,tbl_DersSaatleri,tbl_Ders,tbl_Gun WHERE tbl_DersSaatleri.dersId=tbl_Ders.dersId AND tbl_DersSaatleri.gunId=tbl_Gun.gunId AND tbl_DersSaatleri.saatAraligiId=tbl_SaatAraligi.saatAralikId and tbl_Kullanici.kullaniciId="<< gelenId <<" and tbl_Kullanici.kullaniciId=tbl_Ders.dersOgretimGorevlisi order by tbl_SaatAraligi.saatAralikId asc,tbl_Gun.gunId";
    
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
    ss.str("");
	
	
	return listofOgrVerilenDersler;
	
	
	
	
}


