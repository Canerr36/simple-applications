#pragma once
#include <string>
#include <vector>

enum class SaglikDurumu {
	Saglikli,
	Hasta,
	TedaviAltinda
};

std::string saglikDurumuMetni(SaglikDurumu durum);

// Tek bir besi hayvanini (kupe numarasi, cinsi, kilo, asi ve saglik
// gecmisi, yem tuketimi) temsil eder.
class Hayvan {
public:
	Hayvan();
	Hayvan(const std::string& kupeNo, const std::string& cinsi, double girisKilo);

	// Kilo takibi
	void gunlukKiloArtisiEkle(double artisKg);
	double toplamKiloArtisi() const;
	double getGuncelKilo() const;
	int gunlukKayitSayisi() const;

	// Asi / saglik
	void asiEkle(const std::string& asiAdi);
	void saglikDurumuGuncelle(SaglikDurumu durum);
	SaglikDurumu getSaglikDurumu() const;
	const std::vector<std::string>& getAsilar() const;

	// Yem
	void yemTuketimiEkle(double miktarKg);
	double getToplamYemTuketimi() const;

	// Temel bilgiler
	const std::string& getKupeNo() const;
	const std::string& getCinsi() const;
	double getGirisKilo() const;

	void bilgileriYazdir() const;

	// Basit dosya serilestirme (tek satir, '|' ile ayrilmis alanlar)
	std::string dosyaSatirinaCevir() const;
	static Hayvan dosyaSatirindanOku(const std::string& satir);

private:
	std::string kupeNo;
	std::string cinsi;
	double girisKilo;
	double guncelKilo;
	std::vector<double> gunlukArtislar;
	std::vector<std::string> asilar;
	SaglikDurumu saglik;
	double toplamYem;
};
