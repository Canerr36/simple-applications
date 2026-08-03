#include "headers.h"




class MainMenu {
public:
	void run() {

		std::cout << "=================================\n";
		std::cout << "       Otel Uygulaması       \n";
		std::cout << "=================================\n\n";

		std::cout << "\n\t -- Otel -- \n";
		std::cout << "\t1. Oda Rezervasyonu \n";
		std::cout << "\t2. Oda Boşaltma \n";
		std::cout << "\t3. Dolu oda sayısı \n";
		std::cout << "\t4. Oda Raporu \n";
		std::cout << "\t5. Toplam Gelir \n";
		std::cout << "\t6. Çıkış \n";
		std::cout << "Seçimini Gir -> ";

	}
};



int main() {
	setlocale(LC_ALL, "Turkish");
	int secim;
	OdaRezervasyonu b1;
	OdaTahliyeBosaltma b2;
	DoluOdaSayısı b3;
	OdaDurumRaporu b4;
	ToplamGelir b5;


	MainMenu mainMenu;

	do
	{
		mainMenu.run();
		std::cin >> secim;

		switch (secim) {
		case 1:
			b1.run();
			break;
		case 2:
			b2.run();
			break;
		case 3:
			b3.run();
			break;
		case 4:
			b4.run();
			break;
		case 5:
			b5.run();
			break;
		case 6:
			break;
		default:"Hatalı Giriş Yaptınız!! 1-6 arası seçim yapınız "; break;
		}

	} while (secim != 6);

	return 0;
}



