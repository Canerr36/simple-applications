#include "YemStok.h"
#include "HayvanKayit.h"
#include "Girdi.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

const std::string YemStok::DOSYA_ADI = "yem_stok.txt";

std::string YemTuru::dosyaSatirinaCevir() const {
	std::ostringstream oss;
	oss << ad << "|" << stokKg << "|" << fiyatKg;
	return oss.str();
}

YemTuru YemTuru::dosyaSatirindanOku(const std::string& satir) {
	std::vector<std::string> alanlar;
	std::stringstream ss(satir);
	std::string parca;
	while (std::getline(ss, parca, '|')) alanlar.push_back(parca);
	while (alanlar.size() < 3) alanlar.push_back("0");

	YemTuru y;
	y.ad = alanlar[0];
	y.stokKg = std::stod(alanlar[1]);
	y.fiyatKg = std::stod(alanlar[2]);
	return y;
}

YemTuru* YemStok::yemBul(const std::string& ad) {
	for (auto& y : yemler) {
		if (y.ad == ad) return &y;
	}
	return nullptr;
}

const std::vector<YemTuru>& YemStok::getYemler() const {
	return yemler;
}

double YemStok::toplamTuketilenKg() const {
	return toplamTuketim;
}

double YemStok::toplamYemMaliyeti() const {
	return toplamMaliyet;
}

void YemStok::yeniYemTuruEkle() {
	std::string ad = Girdi::metinOku("Yeni yem turunun adi : ");
	if (yemBul(ad) != nullptr) {
		std::cout << "Bu yem turu zaten tanimli.\n";
		return;
	}
	double baslangicStok = Girdi::ondalikOku("Baslangic stok miktari (kg) : ");
	double fiyat = Girdi::ondalikOku("Kg basina maliyet (TL) : ");

	YemTuru y;
	y.ad = ad;
	y.stokKg = baslangicStok;
	y.fiyatKg = fiyat;
	yemler.push_back(y);

	std::cout << "Yem turu tanimlandi.\n";
	dosyayaKaydet();
}

void YemStok::stokEkle() {
	if (yemler.empty()) {
		std::cout << "Once bir yem turu tanimlamalisiniz (1. secenek).\n";
		return;
	}
	stokDurumuGoster();
	std::string ad = Girdi::metinOku("\nStok eklenecek yem turu : ");
	YemTuru* y = yemBul(ad);
	if (y == nullptr) {
		std::cout << "Bu yem turu tanimli degil.\n";
		return;
	}
	double miktar = Girdi::ondalikOku("Eklenecek miktar (kg) : ");
	y->stokKg += miktar;
	std::cout << "Stok guncellendi. Yeni stok: " << y->stokKg << " kg\n";
	dosyayaKaydet();
}

void YemStok::tuketimGir(HayvanKayit& kayit) {
	if (yemler.empty()) {
		std::cout << "Once bir yem turu tanimlamalisiniz (1. secenek).\n";
		return;
	}
	if (kayit.hayvanSayisi() == 0) {
		std::cout << "Kayitli hayvan bulunmuyor. Once hayvan kaydi yapiniz.\n";
		return;
	}

	kayit.listele();
	std::string kupeNo = Girdi::metinOku("\nHangi hayvana yem verildi (kupe no) : ");
	Hayvan* h = kayit.bul(kupeNo);
	if (h == nullptr) {
		std::cout << "Hayvan bulunamadi.\n";
		return;
	}

	stokDurumuGoster();
	std::string ad = Girdi::metinOku("\nKullanilan yem turu : ");
	YemTuru* y = yemBul(ad);
	if (y == nullptr) {
		std::cout << "Bu yem turu tanimli degil.\n";
		return;
	}

	double miktar = Girdi::ondalikOku("Tuketilen miktar (kg) : ");
	if (miktar > y->stokKg) {
		std::cout << "Uyari: Stokta yeterli " << y->ad << " yok! Mevcut stok: "
			<< y->stokKg << " kg. Islem iptal edildi.\n";
		return;
	}

	y->stokKg -= miktar;
	toplamTuketim += miktar;
	toplamMaliyet += miktar * y->fiyatKg;
	h->yemTuketimiEkle(miktar);

	std::cout << "Yem tuketimi kaydedildi. Kalan " << y->ad << " stogu: " << y->stokKg << " kg\n";

	dosyayaKaydet();
	kayit.dosyayaKaydet();
}

void YemStok::stokDurumuGoster() const {
	if (yemler.empty()) {
		std::cout << "Henuz tanimli yem turu yok.\n";
		return;
	}
	std::cout << "\nYem Turu\tStok (kg)\tKg Fiyati (TL)\n";
	for (const auto& y : yemler) {
		std::cout << y.ad << "\t\t" << y.stokKg << "\t\t" << y.fiyatKg << "\n";
	}
	std::cout << "Toplam tuketilen yem (tum zamanlar) : " << toplamTuketim << " kg\n";
}

void YemStok::run(HayvanKayit& kayit) {
	int secim;
	do {
		std::cout << "\n\t -- Yem Stok Yonetimi --\n";
		std::cout << "\t1. Yeni Yem Turu Tanimla\n";
		std::cout << "\t2. Stoga Yem Ekle (Satin Alim)\n";
		std::cout << "\t3. Hayvana Yem Tuketimi Gir\n";
		std::cout << "\t4. Stok Durumunu Goster\n";
		std::cout << "\t0. Ana Menuye Don\n";
		secim = Girdi::tamSayiOku("\tSeciminiz -> ");

		switch (secim) {
		case 1: yeniYemTuruEkle(); break;
		case 2: stokEkle(); break;
		case 3: tuketimGir(kayit); break;
		case 4: stokDurumuGoster(); break;
		case 0: break;
		default: std::cout << "Hatali Giris Yaptiniz!\n";
		}

	} while (secim != 0);
}

void YemStok::dosyayaKaydet() const {
	std::ofstream dosya(DOSYA_ADI);
	if (!dosya.is_open()) {
		std::cout << "Uyari: Yem stok verileri kaydedilemedi.\n";
		return;
	}
	dosya << toplamTuketim << "|" << toplamMaliyet << "\n";
	for (const auto& y : yemler) {
		dosya << y.dosyaSatirinaCevir() << "\n";
	}
}

void YemStok::dosyadanYukle() {
	std::ifstream dosya(DOSYA_ADI);
	if (!dosya.is_open()) return;

	yemler.clear();
	std::string satir;
	bool ilkSatir = true;
	while (std::getline(dosya, satir)) {
		if (satir.empty()) continue;
		if (ilkSatir) {
			std::stringstream ilkSs(satir);
			std::string a, b;
			std::getline(ilkSs, a, '|');
			std::getline(ilkSs, b, '|');
			toplamTuketim = a.empty() ? 0.0 : std::stod(a);
			toplamMaliyet = b.empty() ? 0.0 : std::stod(b);
			ilkSatir = false;
			continue;
		}
		yemler.push_back(YemTuru::dosyaSatirindanOku(satir));
	}
}
