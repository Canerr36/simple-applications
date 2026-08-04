#include "HayvanKayit.h"
#include "Girdi.h"
#include <iostream>
#include <fstream>
#include <algorithm>

const std::string HayvanKayit::DOSYA_ADI = "hayvanlar.txt";

HayvanKayit::HayvanKayit() {
}

Hayvan* HayvanKayit::bul(const std::string& kupeNo) {
	for (auto& h : hayvanlar) {
		if (h.getKupeNo() == kupeNo) return &h;
	}
	return nullptr;
}

int HayvanKayit::hayvanSayisi() const {
	return static_cast<int>(hayvanlar.size());
}

std::vector<Hayvan>& HayvanKayit::getHayvanlar() {
	return hayvanlar;
}

const std::vector<Hayvan>& HayvanKayit::getHayvanlar() const {
	return hayvanlar;
}

void HayvanKayit::run() {
	std::cout << "\n\t Hayvan Kayit \n\n";

	std::string kupeNo = Girdi::metinOku("Kupe Numarasini Giriniz : ");

	if (bul(kupeNo) != nullptr) {
		std::cout << "Bu kupe numarasi zaten kayitli! Islem iptal edildi.\n";
		return;
	}

	std::string cinsi = Girdi::metinOku("Cinsini Giriniz         : ");
	double girisKilo = Girdi::ondalikOku("Giris Kilosunu Giriniz (kg) : ");

	hayvanlar.push_back(Hayvan(kupeNo, cinsi, girisKilo));
	std::cout << "Hayvan basariyla kaydedildi. Toplam hayvan sayisi: " << hayvanlar.size() << "\n";

	dosyayaKaydet();
}

void HayvanKayit::sil() {
	if (hayvanlar.empty()) {
		std::cout << "\nKayitli hayvan bulunmuyor.\n";
		return;
	}

	listele();
	std::string kupeNo = Girdi::metinOku("\nSilinecek hayvanin kupe numarasini giriniz : ");

	auto it = std::find_if(hayvanlar.begin(), hayvanlar.end(),
		[&](const Hayvan& h) { return h.getKupeNo() == kupeNo; });

	if (it == hayvanlar.end()) {
		std::cout << "Bu kupe numarasina sahip hayvan bulunamadi.\n";
		return;
	}

	hayvanlar.erase(it);
	std::cout << "Hayvan kaydi silindi.\n";
	dosyayaKaydet();
}

void HayvanKayit::gunlukKiloArtisiGir() {
	if (hayvanlar.empty()) {
		std::cout << "\nKayitli hayvan bulunmuyor. Once hayvan kaydi yapiniz.\n";
		return;
	}

	listele();
	std::string kupeNo = Girdi::metinOku("\nKilo artisi girilecek hayvanin kupe numarasi : ");

	Hayvan* h = bul(kupeNo);
	if (h == nullptr) {
		std::cout << "Bu kupe numarasina sahip hayvan bulunamadi.\n";
		return;
	}

	double artis = Girdi::ondalikOku("Gunluk kilo artisini giriniz (kg) : ");
	h->gunlukKiloArtisiEkle(artis);

	std::cout << "Kayit eklendi. Guncel kilo: " << h->getGuncelKilo()
		<< " kg (giristen bu yana toplam artis: " << h->toplamKiloArtisi() << " kg)\n";

	dosyayaKaydet();
}

void HayvanKayit::asiVeSaglikMenusu() {
	if (hayvanlar.empty()) {
		std::cout << "\nKayitli hayvan bulunmuyor. Once hayvan kaydi yapiniz.\n";
		return;
	}

	int secim;
	do {
		std::cout << "\n\t -- Asi ve Saglik Durumu --\n";
		std::cout << "\t1. Hayvana Asi Ekle\n";
		std::cout << "\t2. Saglik Durumunu Guncelle\n";
		std::cout << "\t3. Hayvan Detayini Goster\n";
		std::cout << "\t4. Suru Saglik Ozeti\n";
		std::cout << "\t0. Ana Menuye Don\n";
		secim = Girdi::tamSayiOku("\tSeciminiz -> ");

		switch (secim) {
		case 1: {
			listele();
			std::string kupeNo = Girdi::metinOku("\nKupe numarasi : ");
			Hayvan* h = bul(kupeNo);
			if (h == nullptr) {
				std::cout << "Hayvan bulunamadi.\n";
				break;
			}
			std::string asiAdi = Girdi::metinOku("Asi adi : ");
			h->asiEkle(asiAdi);
			std::cout << "Asi kaydedildi.\n";
			dosyayaKaydet();
			break;
		}
		case 2: {
			listele();
			std::string kupeNo = Girdi::metinOku("\nKupe numarasi : ");
			Hayvan* h = bul(kupeNo);
			if (h == nullptr) {
				std::cout << "Hayvan bulunamadi.\n";
				break;
			}
			std::cout << "1-Saglikli  2-Hasta  3-Tedavi Altinda\n";
			int durum = Girdi::tamSayiOku("Yeni saglik durumu : ");
			if (durum < 1 || durum > 3) {
				std::cout << "Gecersiz secim.\n";
				break;
			}
			h->saglikDurumuGuncelle(static_cast<SaglikDurumu>(durum - 1));
			std::cout << "Saglik durumu guncellendi: " << saglikDurumuMetni(h->getSaglikDurumu()) << "\n";
			dosyayaKaydet();
			break;
		}
		case 3: {
			listele();
			std::string kupeNo = Girdi::metinOku("\nKupe numarasi : ");
			Hayvan* h = bul(kupeNo);
			if (h == nullptr) {
				std::cout << "Hayvan bulunamadi.\n";
				break;
			}
			h->bilgileriYazdir();
			break;
		}
		case 4: {
			int hasta = 0, tedavi = 0, saglikli = 0;
			for (const auto& h : hayvanlar) {
				switch (h.getSaglikDurumu()) {
				case SaglikDurumu::Saglikli: ++saglikli; break;
				case SaglikDurumu::Hasta: ++hasta; break;
				case SaglikDurumu::TedaviAltinda: ++tedavi; break;
				}
			}
			std::cout << "\nSaglikli       : " << saglikli << "\n";
			std::cout << "Hasta          : " << hasta << "\n";
			std::cout << "Tedavi Altinda : " << tedavi << "\n";
			break;
		}
		case 0:
			break;
		default:
			std::cout << "Hatali Giris Yaptiniz!\n";
		}

	} while (secim != 0);
}

void HayvanKayit::listele() const {
	if (hayvanlar.empty()) {
		std::cout << "Kayitli hayvan bulunmuyor.\n";
		return;
	}

	std::cout << "\nKupeNo\t\tCinsi\t\tGuncelKilo\tSaglik\n";
	for (const auto& h : hayvanlar) {
		std::cout << h.getKupeNo() << "\t\t" << h.getCinsi() << "\t\t"
			<< h.getGuncelKilo() << " kg\t" << saglikDurumuMetni(h.getSaglikDurumu()) << "\n";
	}
}

void HayvanKayit::dosyayaKaydet() const {
	std::ofstream dosya(DOSYA_ADI);
	if (!dosya.is_open()) {
		std::cout << "Uyari: Hayvan verileri dosyaya kaydedilemedi.\n";
		return;
	}
	for (const auto& h : hayvanlar) {
		dosya << h.dosyaSatirinaCevir() << "\n";
	}
}

void HayvanKayit::dosyadanYukle() {
	std::ifstream dosya(DOSYA_ADI);
	if (!dosya.is_open()) return; // ilk calistirmada dosya olmayabilir, sorun degil

	hayvanlar.clear();
	std::string satir;
	while (std::getline(dosya, satir)) {
		if (satir.empty()) continue;
		hayvanlar.push_back(Hayvan::dosyaSatirindanOku(satir));
	}
}
