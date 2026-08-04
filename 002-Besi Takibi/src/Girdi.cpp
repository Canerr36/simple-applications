#include "Girdi.h"
#include <iostream>
#include <limits>
#include <cstdlib>

namespace Girdi {

	int tamSayiOku(const std::string& mesaj) {
		int deger;
		while (true) {
			std::cout << mesaj;
			if (std::cin >> deger) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return deger;
			}
			if (std::cin.eof()) {
				std::cout << "\nGiris sonlandi. Program kapatiliyor...\n";
				std::exit(0);
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Gecersiz deger! Lutfen bir tam sayi girin.\n";
		}
	}

	double ondalikOku(const std::string& mesaj) {
		double deger;
		while (true) {
			std::cout << mesaj;
			if (std::cin >> deger) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return deger;
			}
			if (std::cin.eof()) {
				std::cout << "\nGiris sonlandi. Program kapatiliyor...\n";
				std::exit(0);
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Gecersiz deger! Lutfen bir sayi girin (orn: 12.5).\n";
		}
	}

	std::string metinOku(const std::string& mesaj) {
		std::string deger;
		std::cout << mesaj;
		std::getline(std::cin, deger); // bosluk iceren isimlere (orn. "Sap Agzi Asi") izin verir
		return deger;
	}

}
