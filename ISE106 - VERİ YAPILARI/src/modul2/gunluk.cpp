#include "gunluk.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
using namespace std;

// ─────────────────────────────────────────────
//  Yardımcı: Güncel tarih-saat
// ─────────────────────────────────────────────
string simdi() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", now);
    return string(buf);
}

// ─────────────────────────────────────────────
//  Yardımcı: Log düğümü yazdır
// ─────────────────────────────────────────────
void logYazdir(const LogKaydi* l) {
    cout << "--------------------------------------" << endl;
    cout << "Kayit ID    : " << l->kayitId << endl;
    cout << "Islem Turu  : " << l->islemTuru << endl;
    cout << "Tarih/Saat  : " << l->tarihSaat << endl;
    if (!l->eskiDeger.empty())
        cout << "Eski Deger  : " << l->eskiDeger << endl;
    if (!l->yeniDeger.empty())
        cout << "Yeni Deger  : " << l->yeniDeger << endl;
    cout << "--------------------------------------" << endl;
}

// ─────────────────────────────────────────────
//  1. Günlük Kaydı Ekle — sona ekle (dairesel yapıyı korur)
//
//  Yapı görünümü (3 düğüm):
//  bas → [A] ⇄ [B] ⇄ [C] ⇄ (bas'a döner)
// ─────────────────────────────────────────────
void gunlukKaydiEkle(
    LogKaydi*& bas, int kayitId, const string& islemTuru, const string& tarihSaat,
    const string& eskiDeger, const string& yeniDeger
) {
    LogKaydi* yeni = new LogKaydi();
    yeni->kayitId = kayitId;
    yeni->islemTuru = islemTuru;
    yeni->tarihSaat = tarihSaat;
    yeni->eskiDeger = eskiDeger;
    yeni->yeniDeger = yeniDeger;

    if (bas == nullptr) {
        // İlk düğüm: kendine bağlı (dairesel)
        yeni->onceki = yeni;
        yeni->sonraki = yeni;
        bas = yeni;
    } else {
        // Son düğüm = bas->onceki (dairesel yapı sayesinde O(1))
        LogKaydi* son = bas->onceki;
        son->sonraki = yeni;
        yeni->onceki = son;
        yeni->sonraki = bas; // son düğüm başa bağlanır
        bas->onceki = yeni;  // baş geriye yeni düğümü gösterir
    }

    cout << "[LOG] Kayit edildi → " << islemTuru << " | ID: " << kayitId << endl;
}

// ─────────────────────────────────────────────
//  2. Belirli Kayıt ID'ye Ait Tüm İşlemleri Listele
// ─────────────────────────────────────────────
void kayitIdIslemleriListele(LogKaydi* bas, int kayitId) {
    if (bas == nullptr) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }

    cout << "\n=== ID " << kayitId << " ICIN TUM ISLEMLER ===" << endl;
    LogKaydi* p = bas;
    bool bulundu = false;
    do {
        if (p->kayitId == kayitId) {
            logYazdir(p);
            bulundu = true;
        }
        p = p->sonraki;
    } while (p != bas); // dairesel: başa dönünce dur

    if (!bulundu)
        cout << "[BILGI] Bu ID icin islem bulunamadi." << endl;
}

// ─────────────────────────────────────────────
//  3. Tarih Aralığındaki İşlemler
//  baslangic / bitis formatı: "YYYY-AA-GG"
// ─────────────────────────────────────────────
void tarihAraligiListele(LogKaydi* bas, const string& baslangic, const string& bitis) {
    if (bas == nullptr) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }

    cout << "\n=== " << baslangic << " ile " << bitis << " ARASI ISLEMLER ===" << endl;
    LogKaydi* p = bas;
    bool bulundu = false;
    do {
        // tarihSaat "YYYY-AA-GG SS:DD" formatında → ilk 10 karakter tarih
        string tarih = p->tarihSaat.substr(0, 10);
        if (tarih >= baslangic && tarih <= bitis) {
            logYazdir(p);
            bulundu = true;
        }
        p = p->sonraki;
    } while (p != bas);

    if (!bulundu)
        cout << "[BILGI] Bu tarih araliginda islem bulunamadi." << endl;
}

// ─────────────────────────────────────────────
//  4. Günlük Raporu Oluştur
//  — İşlem türü bazlı frekans
//  — En çok işlem gören kayıt ID
//  — Kritik kayıt analizi (Sil/Guncelle sayısı)
// ─────────────────────────────────────────────
void gunlukRaporOlustur(LogKaydi* bas) {
    if (bas == nullptr) {
        cout << "[BILGI] Gunluk bos, rapor olusturulamadi." << endl;
        return;
    }

    map<string, int> turSayac; // islemTuru → adet
    map<int, int> idSayac;     // kayitId   → adet
    int toplamIslem = 0;

    LogKaydi* p = bas;
    do {
        turSayac[p->islemTuru]++;
        idSayac[p->kayitId]++;
        toplamIslem++;
        p = p->sonraki;
    } while (p != bas);

    cout << "\n╔══════════════════════════════════════╗" << endl;
    cout << "║         GUNLUK RAPORU                ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  Toplam Islem Sayisi : " << setw(15) << toplamIslem << " ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  ISLEM TURU          ADET            ║" << endl;

    for (auto& kv : turSayac)
        cout << "║  " << left << setw(20) << kv.first << setw(16) << right << kv.second << " ║"
             << endl;

    // En çok işlem gören ID
    int enCokId = -1, enCokAdet = 0;
    for (auto& kv : idSayac) {
        if (kv.second > enCokAdet) {
            enCokAdet = kv.second;
            enCokId = kv.first;
        }
    }
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  En Aktif Kayit ID  : " << setw(15) << enCokId << " ║" << endl;
    cout << "║  Islem Adedi        : " << setw(15) << enCokAdet << " ║" << endl;

    // Kritik analiz: Sil + Guncelle sayısı
    int kritikSayisi = turSayac["Sil"] + turSayac["Guncelle"];
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  Kritik Islem Sayisi: " << setw(15) << kritikSayisi << " ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
}

// ─────────────────────────────────────────────
//  5. İşlem Türüne Göre Listele
// ─────────────────────────────────────────────
void islemTuruneGoreListele(LogKaydi* bas, const string& islemTuru) {
    if (bas == nullptr) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }

    cout << "\n=== ISLEM TURU: " << islemTuru << " ===" << endl;
    LogKaydi* p = bas;
    bool bulundu = false;
    do {
        if (p->islemTuru == islemTuru) {
            logYazdir(p);
            bulundu = true;
        }
        p = p->sonraki;
    } while (p != bas);

    if (!bulundu)
        cout << "[BILGI] Bu turde islem bulunamadi: " << islemTuru << endl;
}

// ─────────────────────────────────────────────
//  Yardımcı: Belleği temizle
// ─────────────────────────────────────────────
void gunlukTemizle(LogKaydi*& bas) {
    if (bas == nullptr)
        return;

    // Dairesel listeyi kır, sonra sil
    LogKaydi* son = bas->onceki;
    son->sonraki = nullptr; // dairesel bağı kes

    LogKaydi* p = bas;
    while (p != nullptr) {
        LogKaydi* silinecek = p;
        p = p->sonraki;
        delete silinecek;
    }
    bas = nullptr;
}

// ─────────────────────────────────────────────
//  Modül 2 Ana Menüsü
// ─────────────────────────────────────────────
void modul2Menu(LogKaydi*& bas) {
    int secim;
    do {
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║    MODUL 2 - OPERASYON GUNLUGU       ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║  1. Gunluk Kaydi Ekle                ║" << endl;
        cout << "║  2. Kayit ID'ye Gore Listele         ║" << endl;
        cout << "║  3. Tarih Araligina Gore Listele      ║" << endl;
        cout << "║  4. Gunluk Raporu Olustur            ║" << endl;
        cout << "║  5. Islem Turune Gore Listele        ║" << endl;
        cout << "║  0. Ana Menuye Don                   ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        cout << "Seciminiz: ";
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            int id;
            string tur, eski, yeni;
            cout << "Kayit ID      : ";
            cin >> id;
            cin.ignore();
            cout << "Islem Turu (Ekle/Sil/Guncelle/Dequeue): ";
            getline(cin, tur);
            cout << "Eski Deger    : ";
            getline(cin, eski);
            cout << "Yeni Deger    : ";
            getline(cin, yeni);
            gunlukKaydiEkle(bas, id, tur, simdi(), eski, yeni);

        } else if (secim == 2) {
            int id;
            cout << "Kayit ID : ";
            cin >> id;
            kayitIdIslemleriListele(bas, id);

        } else if (secim == 3) {
            string bas_, bitis;
            cout << "Baslangic Tarihi (YYYY-AA-GG): ";
            cin >> bas_;
            cout << "Bitis Tarihi    (YYYY-AA-GG): ";
            cin >> bitis;
            tarihAraligiListele(bas, bas_, bitis);

        } else if (secim == 4) {
            gunlukRaporOlustur(bas);

        } else if (secim == 5) {
            string tur;
            cout << "Islem Turu (Ekle/Sil/Guncelle/Dequeue): ";
            cin.ignore();
            getline(cin, tur);
            islemTuruneGoreListele(bas, tur);

        } else if (secim != 0) {
            cout << "[HATA] Gecersiz secim." << endl;
        }

    } while (secim != 0);
}
