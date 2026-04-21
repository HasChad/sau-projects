#include "kayit.h"
#include <algorithm> // sort için
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// ─────────────────────────────────────────────
//  Yardımcı: Tek kayıt yazdır
// ─────────────────────────────────────────────
void kayitYazdir(const Kayit* k) {
    cout << "--------------------------------------" << endl;
    cout << "ID         : " << k->id << endl;
    cout << "Baslik     : " << k->baslik << endl;
    cout << "Kategori   : " << k->kategori << endl;
    cout << "Boyut(KB)  : " << fixed << setprecision(2) << k->boyut << endl;
    cout << "Tarih      : " << k->tarih << endl;
    cout << "Oncelik    : " << k->oncelik << endl;
    cout << "Durum      : " << k->durum << endl;
    cout << "Ort.Puan   : " << k->ortPuan << endl;
    if (!k->kritikNot.empty())
        cout << "Kritik Not : " << k->kritikNot << endl;
    cout << "--------------------------------------" << endl;
}

// ─────────────────────────────────────────────
//  1. Kayıt Ekle — başa ekle (O(1))
// ─────────────────────────────────────────────
void kayitEkle(
    Kayit*& bas, int id, const string& baslik, const string& kategori, float boyut,
    const string& tarih, const string& oncelik, const string& durum, float ortPuan,
    const string& kritikNot
) {

    // Aynı ID'den var mı kontrol et
    if (idyeGoreAra(bas, id) != nullptr) {
        cout << "[HATA] Bu ID zaten kayitli: " << id << endl;
        return;
    }

    Kayit* yeni = new Kayit();
    yeni->id = id;
    yeni->baslik = baslik;
    yeni->kategori = kategori;
    yeni->boyut = boyut;
    yeni->tarih = tarih;
    yeni->oncelik = oncelik;
    yeni->durum = durum;
    yeni->ortPuan = ortPuan;
    yeni->kritikNot = kritikNot;
    yeni->sonraki = bas; // eski başı arkaya al
    bas = yeni;          // yeni düğüm baş oldu

    cout << "[BASARI] Kayit eklendi. ID: " << id << endl;
}

// ─────────────────────────────────────────────
//  2. ID'ye Göre Sil
// ─────────────────────────────────────────────
bool idyeGoreSil(Kayit*& bas, int id) {
    if (bas == nullptr) {
        cout << "[HATA] Liste bos." << endl;
        return false;
    }

    // Baştaki düğüm silinecekse
    if (bas->id == id) {
        Kayit* silinecek = bas;
        bas = bas->sonraki;
        delete silinecek;
        cout << "[BASARI] ID " << id << " silindi." << endl;
        return true;
    }

    // Ortada/sonda ara
    Kayit* onceki = bas;
    Kayit* simdiki = bas->sonraki;
    while (simdiki != nullptr) {
        if (simdiki->id == id) {
            onceki->sonraki = simdiki->sonraki;
            delete simdiki;
            cout << "[BASARI] ID " << id << " silindi." << endl;
            return true;
        }
        onceki = simdiki;
        simdiki = simdiki->sonraki;
    }

    cout << "[HATA] ID bulunamadi: " << id << endl;
    return false;
}

// ─────────────────────────────────────────────
//  3. Başlığa Göre Güncelle
// ─────────────────────────────────────────────
bool basligaGoreGuncelle(
    Kayit* bas, const string& baslik, const string& yeniDurum, const string& yeniOncelik,
    float yeniPuan
) {
    Kayit* simdiki = bas;
    bool bulundu = false;

    while (simdiki != nullptr) {
        if (simdiki->baslik == baslik) {
            simdiki->durum = yeniDurum;
            simdiki->oncelik = yeniOncelik;
            simdiki->ortPuan = yeniPuan;
            cout << "[BASARI] '" << baslik << "' guncellendi." << endl;
            bulundu = true;
        }
        simdiki = simdiki->sonraki;
    }

    if (!bulundu)
        cout << "[HATA] Baslik bulunamadi: " << baslik << endl;

    return bulundu;
}

// ─────────────────────────────────────────────
//  4. Zaman Damgası ile Listele (tarihe göre sıralı — kopya vektör kullan)
// ─────────────────────────────────────────────
void zamanDamgasiIleListele(Kayit* bas) {
    if (bas == nullptr) {
        cout << "[BILGI] Liste bos." << endl;
        return;
    }

    // Vektöre al, tarihe göre sırala
    vector<Kayit*> v;
    Kayit* p = bas;
    while (p != nullptr) {
        v.push_back(p);
        p = p->sonraki;
    }

    sort(v.begin(), v.end(), [](Kayit* a, Kayit* b) {
        return a->tarih < b->tarih; // "YYYY-AA-GG" string karşılaştırması
    });

    cout << "\n=== KAYITLAR (Tarihe Gore) ===" << endl;
    for (auto k : v)
        kayitYazdir(k);
}

// ─────────────────────────────────────────────
//  5. ID'ye Göre Ara
// ─────────────────────────────────────────────
Kayit* idyeGoreAra(Kayit* bas, int id) {
    Kayit* simdiki = bas;
    while (simdiki != nullptr) {
        if (simdiki->id == id)
            return simdiki;
        simdiki = simdiki->sonraki;
    }
    return nullptr;
}

// ─────────────────────────────────────────────
//  6. Toplam Kayıt Sayısı
// ─────────────────────────────────────────────
int toplamKayitSayisi(Kayit* bas) {
    int sayac = 0;
    Kayit* p = bas;
    while (p != nullptr) {
        sayac++;
        p = p->sonraki;
    }
    cout << "[BILGI] Toplam kayit sayisi: " << sayac << endl;
    return sayac;
}

// ─────────────────────────────────────────────
//  7. Boyuta Göre Küçükten Büyüğe Sırala (Bubble Sort — listenin kendisini sıralar)
// ─────────────────────────────────────────────
void boyutaGoreSirala(Kayit*& bas) {
    if (bas == nullptr || bas->sonraki == nullptr)
        return;

    bool degisimOldu;
    do {
        degisimOldu = false;
        Kayit* p = bas;
        while (p->sonraki != nullptr) {
            if (p->boyut > p->sonraki->boyut) {
                // Sadece veriyi taşı, pointer'ı değil
                swap(p->id, p->sonraki->id);
                swap(p->baslik, p->sonraki->baslik);
                swap(p->kategori, p->sonraki->kategori);
                swap(p->boyut, p->sonraki->boyut);
                swap(p->tarih, p->sonraki->tarih);
                swap(p->oncelik, p->sonraki->oncelik);
                swap(p->durum, p->sonraki->durum);
                swap(p->ortPuan, p->sonraki->ortPuan);
                swap(p->kritikNot, p->sonraki->kritikNot);
                degisimOldu = true;
            }
            p = p->sonraki;
        }
    } while (degisimOldu);

    cout << "[BASARI] Liste boyuta gore sirarlandi." << endl;
    zamanDamgasiIleListele(bas); // sıralı hali göster
}

// ─────────────────────────────────────────────
//  8. En Eski 10 Kayıt
// ─────────────────────────────────────────────
void enEski10Kayit(Kayit* bas) {
    vector<Kayit*> v;
    Kayit* p = bas;
    while (p != nullptr) {
        v.push_back(p);
        p = p->sonraki;
    }

    sort(v.begin(), v.end(), [](Kayit* a, Kayit* b) { return a->tarih < b->tarih; });

    cout << "\n=== EN ESKI 10 KAYIT ===" << endl;
    int limit = min((int)v.size(), 10);
    for (int i = 0; i < limit; i++)
        kayitYazdir(v[i]);
}

// ─────────────────────────────────────────────
//  9. Kritik Not Ekle
// ─────────────────────────────────────────────
bool kritikNotEkle(Kayit* bas, int id, const string& not_) {
    Kayit* k = idyeGoreAra(bas, id);
    if (k == nullptr) {
        cout << "[HATA] ID bulunamadi: " << id << endl;
        return false;
    }
    k->kritikNot = not_;
    cout << "[BASARI] Kritik not eklendi. ID: " << id << endl;
    return true;
}

// ─────────────────────────────────────────────
//  10. Kritik Kayıtları Listele
// ─────────────────────────────────────────────
void kritikKayitlariListele(Kayit* bas) {
    cout << "\n=== KRITIK KAYITLAR ===" << endl;
    Kayit* p = bas;
    bool bulundu = false;
    while (p != nullptr) {
        if (!p->kritikNot.empty()) {
            kayitYazdir(p);
            bulundu = true;
        }
        p = p->sonraki;
    }
    if (!bulundu)
        cout << "[BILGI] Hic kritik not bulunamadi." << endl;
}

// ─────────────────────────────────────────────
//  Yardımcı: Belleği temizle
// ─────────────────────────────────────────────
void listeTemizle(Kayit*& bas) {
    while (bas != nullptr) {
        Kayit* silinecek = bas;
        bas = bas->sonraki;
        delete silinecek;
    }
}

// ─────────────────────────────────────────────
//  Modül 1 Ana Menüsü
// ─────────────────────────────────────────────
void modul1Menu(Kayit*& bas) {
    int secim;
    do {
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║    MODUL 1 - ANA KAYIT YONETIMI      ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║  1. Kayit Ekle                       ║" << endl;
        cout << "║  2. ID'ye Gore Sil                   ║" << endl;
        cout << "║  3. Basliga Gore Guncelle            ║" << endl;
        cout << "║  4. Zaman Damgasi ile Listele        ║" << endl;
        cout << "║  5. ID'ye Gore Ara                   ║" << endl;
        cout << "║  6. Toplam Kayit Sayisi              ║" << endl;
        cout << "║  7. Boyuta Gore Sirala               ║" << endl;
        cout << "║  8. En Eski 10 Kayit                 ║" << endl;
        cout << "║  9. Kritik Not Ekle                  ║" << endl;
        cout << "║ 10. Kritik Kayitlari Listele         ║" << endl;
        cout << "║  0. Ana Menuye Don                   ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        cout << "Seciminiz: ";
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            int id;
            string baslik, kategori, tarih, oncelik, durum, not_;
            float boyut, puan;
            cout << "ID           : ";
            cin >> id;
            cin.ignore();
            cout << "Baslik       : ";
            getline(cin, baslik);
            cout << "Kategori     : ";
            getline(cin, kategori);
            cout << "Boyut (KB)   : ";
            cin >> boyut;
            cin.ignore();
            cout << "Tarih(YYYY-AA-GG): ";
            getline(cin, tarih);
            cout << "Oncelik(dusuk/orta/yuksek): ";
            getline(cin, oncelik);
            cout << "Durum(Aktif/Islemde/Arsiv): ";
            getline(cin, durum);
            cout << "Ort. Puan    : ";
            cin >> puan;
            cin.ignore();
            cout << "Kritik Not   : ";
            getline(cin, not_);
            kayitEkle(bas, id, baslik, kategori, boyut, tarih, oncelik, durum, puan, not_);

        } else if (secim == 2) {
            int id;
            cout << "Silinecek ID : ";
            cin >> id;
            idyeGoreSil(bas, id);

        } else if (secim == 3) {
            string baslik, durum, oncelik;
            float puan;
            cin.ignore();
            cout << "Guncellenecek Baslik : ";
            getline(cin, baslik);
            cout << "Yeni Durum           : ";
            getline(cin, durum);
            cout << "Yeni Oncelik         : ";
            getline(cin, oncelik);
            cout << "Yeni Puan            : ";
            cin >> puan;
            basligaGoreGuncelle(bas, baslik, durum, oncelik, puan);

        } else if (secim == 4) {
            zamanDamgasiIleListele(bas);

        } else if (secim == 5) {
            int id;
            cout << "Aranacak ID : ";
            cin >> id;
            Kayit* k = idyeGoreAra(bas, id);
            if (k)
                kayitYazdir(k);
            else
                cout << "[HATA] Kayit bulunamadi." << endl;

        } else if (secim == 6) {
            toplamKayitSayisi(bas);

        } else if (secim == 7) {
            boyutaGoreSirala(bas);

        } else if (secim == 8) {
            enEski10Kayit(bas);

        } else if (secim == 9) {
            int id;
            string not_;
            cout << "ID          : ";
            cin >> id;
            cin.ignore();
            cout << "Kritik Not  : ";
            getline(cin, not_);
            kritikNotEkle(bas, id, not_);

        } else if (secim == 10) {
            kritikKayitlariListele(bas);

        } else if (secim != 0) {
            cout << "[HATA] Gecersiz secim." << endl;
        }

    } while (secim != 0);
}
