#ifndef KAYIT_H
#define KAYIT_H

#include <string>
using namespace std;

// ─────────────────────────────────────────────
//  Banka Hesap/İşlem Kaydı — Tek Yönlü Bağlı Liste Düğümü
// ─────────────────────────────────────────────
struct Kayit {
    int id;           // Benzersiz kayıt numarası
    string baslik;    // Örn: "Vadeli Hesap Açılışı", "EFT İşlemi"
    string kategori;  // Örn: "Hesap", "Kredi", "Yatırım", "Sigorta"
    float boyut;      // İşlem tutarı (KB/MB yerine burada TL olarak da kullanılabilir)
    string tarih;     // Oluşturulma tarihi: "YYYY-AA-GG"
    string oncelik;   // "dusuk" / "orta" / "yuksek"
    string durum;     // "Aktif" / "Islemde" / "Arsiv"
    float ortPuan;    // Müşteri memnuniyet puanı (0-10)
    string kritikNot; // Örn: "Şüpheli işlem!", "Limit aşımı"
    Kayit* sonraki;   // Sonraki düğümün adresi
};

// ─────────────────────────────────────────────
//  Fonksiyon Prototipleri
// ─────────────────────────────────────────────

// 1. Kayıt ekle (listeye yeni düğüm ekler)
void kayitEkle(
    Kayit*& bas, int id, const string& baslik, const string& kategori, float boyut,
    const string& tarih, const string& oncelik, const string& durum, float ortPuan,
    const string& kritikNot
);

// 2. ID'ye göre sil
bool idyeGoreSil(Kayit*& bas, int id);

// 3. Başlığa göre güncelle
bool basligaGoreGuncelle(
    Kayit* bas, const string& baslik, const string& yeniDurum, const string& yeniOncelik,
    float yeniPuan
);

// 4. Zaman damgası ile listele (tarihe göre)
void zamanDamgasiIleListele(Kayit* bas);

// 5. ID'ye göre ara
Kayit* idyeGoreAra(Kayit* bas, int id);

// 6. Toplam kayıt sayısı
int toplamKayitSayisi(Kayit* bas);

// 7. Boyuta göre küçükten büyüğe sırala (bubble sort)
void boyutaGoreSirala(Kayit*& bas);

// 8. En eski 10 kayıt
void enEski10Kayit(Kayit* bas);

// 9. Kritik not ekle (ID'ye göre bulup notu günceller)
bool kritikNotEkle(Kayit* bas, int id, const string& not_);

// 10. Kritik kayıtları listele (kritikNot dolu olanlar)
void kritikKayitlariListele(Kayit* bas);

// Yardımcı: Listeyi bellek temizle
void listeTemizle(Kayit*& bas);

// Yardımcı: Tek kayıt yazdır
void kayitYazdir(const Kayit* k);

// Modül 1 Ana Menüsü
void modul1Menu(Kayit*& bas);

#endif // KAYIT_H
