#pragma once
#include <string>
#include <vector>
#include "Hayvan.h"

// Suru genelini (hayvan listesini) yonetir: kayit, silme, gunluk kilo
// artisi girisi, asi/saglik takibi ve dosyaya kaydetme/yukleme.
class HayvanKayit {
public:
	HayvanKayit();

	void run();                  // 1. Hayvan Kayit
	void sil();                  // 2. Hayvan Silme
	void gunlukKiloArtisiGir();  // 3. Gunluk Et Artisi
	void asiVeSaglikMenusu();    // 5. Asi ve Saglik Durumu
	void listele() const;        // Kayitli tum hayvanlari ozet listele

	Hayvan* bul(const std::string& kupeNo);
	int hayvanSayisi() const;

	std::vector<Hayvan>& getHayvanlar();
	const std::vector<Hayvan>& getHayvanlar() const;

	void dosyadanYukle();
	void dosyayaKaydet() const;

private:
	std::vector<Hayvan> hayvanlar;
	static const std::string DOSYA_ADI;
};
