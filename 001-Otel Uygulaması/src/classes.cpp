#include "headers.h"


// otel özellikleri
std::string* customer_name[100], * custome_lastname[100];
int sum = 0, BirKisilikOda, IkiKisilikOda, GunSayisi;							

enum Status {
	emty_room, full_room
}rooms[20];



			 			




void OdaRezervasyonu::run() {
	int number, i = 1, j = 13;			// 1 den 12 ye kadar olan odalar 1 kiþilik, 13 den 20 ye kadar olan odalar 2 kiþilik
	
	std::string name, lastname;
	std::cout << "\n\t -- Lütfen Bir Oda Tipi Seçin -- \n";
	std::cout << "\n\t -- 1 Kiþilik Oda (600 TL) -- \n";
	std::cout << "\n\t -- 2 Kiþilik Oda (1000 TL) -- \n";
	std::cout << "Oda Seçimini Girin -> ";
	std::cin >> number;
	switch (number) {
	case 1:for (; i <= 12; i++) {
		if (rooms[i] != full_room) {
			rooms[i] = full_room;
			std::cout << "Adýnýz :";
			std::cin >> name;
			std::cout << "Soyadýnýz :";
			std::cin >> lastname;
			std::cout << "Kaç gün kalacaksýnýz :";
			std::cin >> GunSayisi;
			sum += GunSayisi * 600;
			BirKisilikOda++;
			customer_name[i] = new std::string;		// dinamik yer ayýrýyoruz
			*customer_name[i] = name;
			custome_lastname[i] = new std::string;
			*custome_lastname[i] = lastname;
			std::cout << "Rezervasyon Baþarýlý Bir Þekilde Oluþturuldu \n\n";
			break;
		}
	}
		  if (i == 12) {
			  std::cout << "Rezervasyon Baþarýlý Bir Þekilde Oluþturuldu \n\n";
		  }

		  break;
	case 2:for (; j <= 20; j++) {
		if (rooms[j] != full_room) {
			rooms[j] = full_room;
			std::cout << "Adýnýz :";
			std::cin >> name;
			std::cout << "Soyadýnýz :";
			std::cin >> lastname;
			std::cout << "Kaç gün kalacaksýnýz :";
			std::cin >> GunSayisi;
			sum += GunSayisi * 1000;
			IkiKisilikOda++;
			customer_name[j] = new std::string;		// dinamik yer ayýrýyoruz
			*customer_name[j] = name;
			custome_lastname[j] = new std::string;
			*custome_lastname[j] = lastname;
			std::cout << "Rezervasyon Oluþturumluþtur \n";
			break;
		}
	}
		  if (i == 20) {
			  std::cout << "Bütün iki kiþilik Odalar Dolu\n";
		  }break;
	default:"Yanlýþ bir seçim yaptýnýz\n";
	}
}



void OdaTahliyeBosaltma::run() {
	int secim,odaNo;
	std::cout << "\t1. Oda Kontrol  --\n";
	std::cout << "\t2. Oda Boþaltma --\n";
	std::cout << "Seçiminiz ->";
	std::cin >> secim;
	

	switch (secim) {
	case 1:

		std::cout << "\t Oda Numarasýný Giriniz ->";
		std::cin >> odaNo;
		if (rooms[secim] == full_room) {
			std::cout << "\nSeçilen Oda Dolu\n\n";
		}
		else
		{
			std::cout << "Seçilen Oda Boþ\n\n";
		}
		break;

	case 2:
		std::cout << "\t Boþaltmak Ýstediðiniz Oda Numarasý ->";
		std::cin >> odaNo;
		
		if (rooms[odaNo] == 0) {
			std::cout << "Bu Oda Zaten Boþ\n";
		}
		else
		{
			rooms[odaNo] = emty_room;
			std::cout << "Oda Baþarýlý Bir Þekilde Boþaltýldý \n";
		}
		break;
	default:std::cout << "Hatalý Giriþ Yaptýnýz Lütfen Tekrar Deneyiniz \n";

	}

}



void DoluOdaSayýsý::run() {
	std::cout << "\t Bir Kiþilik Oda :" << BirKisilikOda << " Tanesi Dolu\n";
	std::cout << "\t Ýki Kiþilik Oda :" << IkiKisilikOda << " Tanesi Dolu\n\n";
}



void OdaDurumRaporu::run() {
	int odaNo;
	std::cout << "\t - Hangi Odanýn Bilgilerini Ýstersiniz -\n";
	std::cout << "\t Seçiminiz ->";
	std::cin >> odaNo;
	


	std::cout << "Kiþi Adý    :" << *customer_name[odaNo] << "\n";
	std::cout << "Kiþi Soyadý :" << *custome_lastname[odaNo] << "\n";
	if (odaNo < 13) {
	std::cout << "Kaldýðý Oda : Bir Kiþilik\n";
	}
	else
	{
	std::cout << "Kaldýðý Oda : Ýki Kiþilik\n";
	}
	std::cout << "Kalacaðý Gün Sayýsý :" << GunSayisi << "\n\n";



}




void ToplamGelir::run() {
	std::cout << "\t Tolpam Gelir :" << sum << " Tl\n\n";
}








