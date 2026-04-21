#ifndef GUNLUK_H
#define GUNLUK_H

#include <string>
using namespace std;

struct LogKaydi {
    int kayitId;       // Hangi kayda yapıldı
    string islemTuru;  // "Ekle" / "Sil" / "Guncelle" / "Dequeue"
    string tarihSaat;  // "YYYY-AA-GG SS:DD"
    string eskiDeger;  // Değişmeden önceki değer (silme/güncelle için)
    string yeniDeger;  // Değişiklik sonrası değer
    LogKaydi* onceki;  // Geri git
    LogKaydi* sonraki; // İleri git
};

// 1. Günlük kaydı ekle
void gunlukKaydiEkle(
    LogKaydi*& bas, int kayitId, const string& islemTuru, const string& tarihSaat,
    const string& eskiDeger, const string& yeniDeger
);

// 2. Belirli kayıt ID'ye ait tüm işlemleri listele
void kayitIdIslemleriListele(LogKaydi* bas, int kayitId);

// 3. Belirli tarih aralığındaki işlemler
void tarihAraligiListele(LogKaydi* bas, const string& baslangic, const string& bitis);

// 4. Günlük raporu oluştur (tür bazlı özet + kritik analiz)
void gunlukRaporOlustur(LogKaydi* bas);

// 5. İşlem türüne göre listele
void islemTuruneGoreListele(LogKaydi* bas, const string& islemTuru);

// Yardımcı: Güncel tarih-saat string'i döner
string simdi();

// Yardımcı: Log düğümü yazdır
void logYazdir(const LogKaydi* l);

// Yardımcı: Belleği temizle
void gunlukTemizle(LogKaydi*& bas);

// Modül 2 Ana Menüsü
void modul2Menu(LogKaydi*& bas);

#endif // GUNLUK_H
