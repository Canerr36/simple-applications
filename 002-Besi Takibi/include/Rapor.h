#pragma once

class HayvanKayit;
class YemStok;

// Suru ve yem verilerini birlestirerek ay sonu ozet raporu uretir.
class Rapor {
public:
	static void aySonuRaporuOlustur(const HayvanKayit& kayit, const YemStok& stok);
};
