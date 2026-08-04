#include <iostream>
#include "include.h"

class MainMenu {
public:
	void run() {
		std::cout << "\n\t -- Besi Takibi --\n";
		std::cout << "\t1. Hayvan Kayit \n";
		std::cout << "\t2. Hayvan Silme \n";
		std::cout << "\t3. Gunluk Et Artisi \n";
		std::cout << "\t4. Tuketilen Yem Miktari ve Stok Durumu \n";
		std::cout << "\t5. Asi ve Saglik Durumu \n";
		std::cout << "\t6. Ay Sonu Raporu \n";
		std::cout << "\t7. Cikis \n";
	}
};

int main() {

	MainMenu mainmenu;

	HayvanKayit b1;
	YemStok yemStok;

	// Program basinda daha onceki oturumdan kalan veriler yuklenir.
	b1.dosyadanYukle();
	yemStok.dosyadanYukle();

	int secim;

	do
	{
		mainmenu.run();

		secim = Girdi::tamSayiOku("Seciminiz ->");

		switch (secim) {
		case 1:
			b1.run();
			break;
		case 2:
			b1.sil();
			break;
		case 3:
			b1.gunlukKiloArtisiGir();
			break;
		case 4:
			yemStok.run(b1);
			break;
		case 5:
			b1.asiVeSaglikMenusu();
			break;
		case 6:
			Rapor::aySonuRaporuOlustur(b1, yemStok);
			break;
		case 7:
			b1.dosyayaKaydet();
			yemStok.dosyayaKaydet();
			std::cout << "Veriler kaydedildi. Programdan cikiliyor...\n";
			break;

		default:std::cout << "Hatali Giris Yaptiniz !\n";

		}

	} while (secim != 7);

	return 0;
}
