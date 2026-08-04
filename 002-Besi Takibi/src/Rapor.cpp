#include "Rapor.h"
#include "HayvanKayit.h"
#include "YemStok.h"
#include "Sabitler.h"
#include <iostream>
#include <iomanip>

void Rapor::aySonuRaporuOlustur(const HayvanKayit& kayit, const YemStok& stok) {
	const auto& hayvanlar = kayit.getHayvanlar();

	std::cout << "\n\t========== AY SONU RAPORU ==========\n\n";

	if (hayvanlar.empty()) {
		std::cout << "Kayitli hayvan bulunmuyor. Rapor olusturulamadi.\n";
		return;
	}

	double toplamKiloArtisi = 0.0;
	int hastaSayisi = 0, tedaviSayisi = 0;

	std::cout << std::fixed << std::setprecision(2);
	std::cout << "KupeNo\t\tCinsi\t\tGirisKilo\tGuncelKilo\tArtis\t\tSaglik\n";
	for (const auto& h : hayvanlar) {
		std::cout << h.getKupeNo() << "\t\t" << h.getCinsi() << "\t\t"
			<< h.getGirisKilo() << "\t\t" << h.getGuncelKilo() << "\t\t"
			<< h.toplamKiloArtisi() << "\t\t" << saglikDurumuMetni(h.getSaglikDurumu()) << "\n";

		toplamKiloArtisi += h.toplamKiloArtisi();
		if (h.getSaglikDurumu() == SaglikDurumu::Hasta) ++hastaSayisi;
		if (h.getSaglikDurumu() == SaglikDurumu::TedaviAltinda) ++tedaviSayisi;
	}

	double tahminiEtGeliri = toplamKiloArtisi * Sabitler::ETKG_FIYAT;
	double toplamYemMaliyeti = stok.toplamYemMaliyeti();
	double tahminiNetKar = tahminiEtGeliri - toplamYemMaliyeti;

	std::cout << "\n-------------------------------------\n";
	std::cout << "Toplam Hayvan Sayisi        : " << hayvanlar.size() << "\n";
	std::cout << "Toplam Kilo Artisi (Suru)   : " << toplamKiloArtisi << " kg\n";
	std::cout << "Et Kg Fiyati                : " << Sabitler::ETKG_FIYAT << " TL\n";
	std::cout << "Tahmini Et Geliri           : " << tahminiEtGeliri << " TL\n";
	std::cout << "Toplam Yem Tuketimi         : " << stok.toplamTuketilenKg() << " kg\n";
	std::cout << "Toplam Yem Maliyeti         : " << toplamYemMaliyeti << " TL\n";
	std::cout << "Tahmini Net Kar/Zarar       : " << tahminiNetKar << " TL\n";
	std::cout << "-------------------------------------\n";

	if (hastaSayisi > 0 || tedaviSayisi > 0) {
		std::cout << "DIKKAT: " << hastaSayisi << " hasta, " << tedaviSayisi
			<< " tedavi altinda hayvan var!\n";
	}
	std::cout << "=====================================\n";
}
