#pragma once
#include <string>
#include <vector>

struct YemTuru {
	std::string ad;
	double stokKg;
	double fiyatKg; // TL / kg maliyet

	std::string dosyaSatirinaCevir() const;
	static YemTuru dosyaSatirindanOku(const std::string& satir);
};

class HayvanKayit; // ileri bildirim (tuketim hayvana da islenir)

// Yem turlerini, stok miktarlarini ve tuketimi yonetir.
class YemStok {
public:
	void run(HayvanKayit& kayit); // 4. Tuketilen Yem Miktari ve Stok Durumu

	void stokDurumuGoster() const;
	double toplamTuketilenKg() const;
	double toplamYemMaliyeti() const;

	void dosyadanYukle();
	void dosyayaKaydet() const;

	const std::vector<YemTuru>& getYemler() const;

private:
	void yeniYemTuruEkle();
	void stokEkle();
	void tuketimGir(HayvanKayit& kayit);
	YemTuru* yemBul(const std::string& ad);

	std::vector<YemTuru> yemler;
	double toplamTuketim = 0.0;
	double toplamMaliyet = 0.0;
	static const std::string DOSYA_ADI;
};
