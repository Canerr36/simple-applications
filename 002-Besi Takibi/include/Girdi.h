#pragma once
#include <string>

// Hatali (sayi yerine harf girilmesi gibi) girislerde programin sonsuz
// donguye girmesini / cokmesini engelleyen ortak okuma fonksiyonlari.
namespace Girdi {
	int tamSayiOku(const std::string& mesaj);
	double ondalikOku(const std::string& mesaj);
	std::string metinOku(const std::string& mesaj);
}
