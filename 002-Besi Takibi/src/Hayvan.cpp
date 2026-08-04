#include "Hayvan.h"
#include <iostream>
#include <sstream>

std::string saglikDurumuMetni(SaglikDurumu durum) {
	switch (durum) {
	case SaglikDurumu::Saglikli:      return "Saglikli";
	case SaglikDurumu::Hasta:         return "Hasta";
	case SaglikDurumu::TedaviAltinda: return "Tedavi Altinda";
	}
	return "Bilinmiyor";
}

Hayvan::Hayvan()
	: girisKilo(0.0), guncelKilo(0.0), saglik(SaglikDurumu::Saglikli), toplamYem(0.0) {
}

Hayvan::Hayvan(const std::string& kupeNo, const std::string& cinsi, double girisKilo)
	: kupeNo(kupeNo), cinsi(cinsi), girisKilo(girisKilo), guncelKilo(girisKilo),
	saglik(SaglikDurumu::Saglikli), toplamYem(0.0) {
}

void Hayvan::gunlukKiloArtisiEkle(double artisKg) {
	gunlukArtislar.push_back(artisKg);
	guncelKilo += artisKg;
}

double Hayvan::toplamKiloArtisi() const {
	return guncelKilo - girisKilo;
}

double Hayvan::getGuncelKilo() const {
	return guncelKilo;
}

int Hayvan::gunlukKayitSayisi() const {
	return static_cast<int>(gunlukArtislar.size());
}

void Hayvan::asiEkle(const std::string& asiAdi) {
	asilar.push_back(asiAdi);
}

void Hayvan::saglikDurumuGuncelle(SaglikDurumu durum) {
	saglik = durum;
}

SaglikDurumu Hayvan::getSaglikDurumu() const {
	return saglik;
}

const std::vector<std::string>& Hayvan::getAsilar() const {
	return asilar;
}

void Hayvan::yemTuketimiEkle(double miktarKg) {
	toplamYem += miktarKg;
}

double Hayvan::getToplamYemTuketimi() const {
	return toplamYem;
}

const std::string& Hayvan::getKupeNo() const {
	return kupeNo;
}

const std::string& Hayvan::getCinsi() const {
	return cinsi;
}

double Hayvan::getGirisKilo() const {
	return girisKilo;
}

void Hayvan::bilgileriYazdir() const {
	std::cout << "----------------------------------------\n";
	std::cout << "Kupe No        : " << kupeNo << "\n";
	std::cout << "Cinsi          : " << cinsi << "\n";
	std::cout << "Giris Kilosu   : " << girisKilo << " kg\n";
	std::cout << "Guncel Kilo    : " << guncelKilo << " kg\n";
	std::cout << "Toplam Artis   : " << toplamKiloArtisi() << " kg\n";
	std::cout << "Yem Tuketimi   : " << toplamYem << " kg\n";
	std::cout << "Saglik Durumu  : " << saglikDurumuMetni(saglik) << "\n";
	std::cout << "Asi Sayisi     : " << asilar.size();
	if (!asilar.empty()) {
		std::cout << " (";
		for (size_t i = 0; i < asilar.size(); ++i) {
			std::cout << asilar[i];
			if (i + 1 < asilar.size()) std::cout << ", ";
		}
		std::cout << ")";
	}
	std::cout << "\n----------------------------------------\n";
}

std::string Hayvan::dosyaSatirinaCevir() const {
	std::ostringstream oss;
	oss << kupeNo << "|" << cinsi << "|" << girisKilo << "|" << guncelKilo << "|"
		<< toplamYem << "|" << static_cast<int>(saglik) << "|";

	for (size_t i = 0; i < gunlukArtislar.size(); ++i) {
		oss << gunlukArtislar[i];
		if (i + 1 < gunlukArtislar.size()) oss << ",";
	}
	oss << "|";
	for (size_t i = 0; i < asilar.size(); ++i) {
		oss << asilar[i];
		if (i + 1 < asilar.size()) oss << ",";
	}
	return oss.str();
}

Hayvan Hayvan::dosyaSatirindanOku(const std::string& satir) {
	std::vector<std::string> alanlar;
	std::stringstream ss(satir);
	std::string parca;
	while (std::getline(ss, parca, '|')) {
		alanlar.push_back(parca);
	}
	while (alanlar.size() < 8) alanlar.push_back("");

	Hayvan h;
	h.kupeNo = alanlar[0];
	h.cinsi = alanlar[1];
	h.girisKilo = alanlar[2].empty() ? 0.0 : std::stod(alanlar[2]);
	h.guncelKilo = alanlar[3].empty() ? 0.0 : std::stod(alanlar[3]);
	h.toplamYem = alanlar[4].empty() ? 0.0 : std::stod(alanlar[4]);
	h.saglik = static_cast<SaglikDurumu>(alanlar[5].empty() ? 0 : std::stoi(alanlar[5]));

	if (!alanlar[6].empty()) {
		std::stringstream artisSs(alanlar[6]);
		std::string deger;
		while (std::getline(artisSs, deger, ',')) {
			if (!deger.empty()) h.gunlukArtislar.push_back(std::stod(deger));
		}
	}
	if (!alanlar[7].empty()) {
		std::stringstream asiSs(alanlar[7]);
		std::string deger;
		while (std::getline(asiSs, deger, ',')) {
			if (!deger.empty()) h.asilar.push_back(deger);
		}
	}
	return h;
}
