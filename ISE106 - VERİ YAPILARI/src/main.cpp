#include "modul1/kayit.h"
#include "modul2/gunluk.h"
#include <iostream>
#include <string>

// ============================================================
// ARKADASLARA NOT - MODUL EKLEMEK ICIN ADIMLAR
// ============================================================
// 1. Kendi modulunuzun klasorunu olusturun: modul3/, modul4/ vs.
// 2. Klasorun icine iki dosya koyun: modul3.h ve modul3.cpp vs.
// 3. Asagida "BURAYA EKLE" yazan yerlere include ve kodunuzu ekleyin
// 4. Derlemek icin komutun sonuna kendi .cpp dosyanizi ekleyin:
//    g++ -std=c++11 main.cpp modul1/kayit.cpp modul2/gunluk.cpp modul3/stack.cpp -o banka
// ============================================================

// Modul 3 ve Modul 4'u yapan arkadas buraya kendi .h dosyasini eklesin:
// #include "modul3/stack.h"
// #include "modul4/queue.h"

// Modul 5, 6, 7, 8 icin ayni sekilde:
// #include "modul5/tree.h"
// #include "modul6/hash.h"
//
// #include "modul7/sikistirma.h"
// #include "modul8/performans.h"

using namespace std;

// ============================================================
// GLOBAL VERI YAPILARI
// ============================================================
// Butun moduller bu degiskenleri kullanir.
// Yeni bir modul eklerken kendi veri yapisini buraya ekleyin.
// ============================================================

Kayit* kayitListesi = NULL;     // Modul 1 - tek yonlu bagli liste
LogKaydi* gunlukListesi = NULL; // Modul 2 - cift yonlu dairesel bagli liste

// Modul 3 - Stack icin buraya ekle:
// Stack* islemStack = NULL;

// Modul 4 - Queue icin buraya ekle:
// Queue* talepQueue = NULL;

// Modul 5, 6, 7, 8 icin ayni sekilde buraya ekle.

// ============================================================
// ORNEK VERI
// ============================================================
// Sunum gunu bos sistemle gelmeyin!
// Kendi modulunuzun ornek verilerini de buraya ekleyin.
// ============================================================
void ornekVeriYukle() {
    // Modul 1 - ornek kayitlar
    kayitEkle(
        kayitListesi,
        1,
        "Vadesiz Hesap Acilisi",
        "Hesap",
        12.5,
        "2024-01-10",
        "yuksek",
        "Aktif",
        9.2,
        ""
    );
    kayitEkle(
        kayitListesi,
        2,
        "Konut Kredisi Basvurusu",
        "Kredi",
        340.0,
        "2023-06-15",
        "yuksek",
        "Islemde",
        7.8,
        "Limit kontrolu gerekli"
    );
    kayitEkle(
        kayitListesi, 3, "Doviz EFT Islemi", "Islem", 88.0, "2024-03-22", "orta", "Aktif", 8.5, ""
    );
    kayitEkle(
        kayitListesi,
        4,
        "Yatirim Fonu Alimi",
        "Yatirim",
        500.0,
        "2022-11-05",
        "orta",
        "Arsiv",
        6.0,
        ""
    );
    kayitEkle(
        kayitListesi,
        5,
        "Supheli Islem Raporu",
        "Guvenlik",
        999.9,
        "2024-04-01",
        "yuksek",
        "Islemde",
        4.1,
        "Acil inceleme!"
    );

    // Modul 2 - ornek loglar
    gunlukKaydiEkle(gunlukListesi, 1, "Ekle", "2024-01-10 09:00", "", "Vadesiz Hesap Acilisi");
    gunlukKaydiEkle(gunlukListesi, 2, "Ekle", "2023-06-15 14:30", "", "Konut Kredisi Basvurusu");
    gunlukKaydiEkle(gunlukListesi, 3, "Ekle", "2024-03-22 11:15", "", "Doviz EFT Islemi");
    gunlukKaydiEkle(gunlukListesi, 2, "Guncelle", "2024-03-25 16:00", "Aktif", "Islemde");
    gunlukKaydiEkle(gunlukListesi, 5, "Ekle", "2024-04-01 08:45", "", "Supheli Islem Raporu");

    // Modul 3'u yapan arkadas kendi ornek verilerini buraya eklesin.
    // Modul 4'u yapan arkadas kendi ornek verilerini buraya eklesin.

    cout << "[SISTEM] Ornek veriler yuklendi." << endl;
}

// ============================================================
// MODUL 1 MENUSU
// ============================================================
// Her islemden sonra diger moduller otomatik tetiklenir.
// "BAGLANTI" yazan satirlara bak.
//
// Modul 3'u yapan arkadas (Stack):
//   "BAGLANTI -> Modul 3" satirlarinin basindaki // isaretini sil
//   stackPush() fonksiyon adini kendi yazdiginla degistir
//
// Modul 6'yi yapan arkadas (Hash):
//   "BAGLANTI -> Modul 6" satirlarinin basindaki // isaretini sil
//
// Modul 7'yi yapan arkadas (Sikistirma):
//   "BAGLANTI -> Modul 7" satirlarinin basindaki // isaretini sil
// ============================================================
void modul1Menu() {
    int secim;
    do {
        cout << "\n--- MODUL 1: ANA KAYIT YONETIMI ---" << endl;
        cout << "1.  Kayit Ekle" << endl;
        cout << "2.  ID'ye Gore Sil" << endl;
        cout << "3.  Basliga Gore Guncelle" << endl;
        cout << "4.  Tarihe Gore Listele" << endl;
        cout << "5.  ID'ye Gore Ara" << endl;
        cout << "6.  Toplam Kayit Sayisi" << endl;
        cout << "7.  Boyuta Gore Sirala" << endl;
        cout << "8.  En Eski 10 Kayit" << endl;
        cout << "9.  Kritik Not Ekle" << endl;
        cout << "10. Kritik Kayitlari Listele" << endl;
        cout << "0.  Geri" << endl;
        cout << "Secim: ";
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            int id;
            string baslik, kategori, tarih, oncelik, durum, not_;
            float boyut, puan;

            cout << "ID               : ";
            cin >> id;
            cin.ignore();
            cout << "Baslik           : ";
            getline(cin, baslik);
            cout << "Kategori         : ";
            getline(cin, kategori);
            cout << "Boyut (KB)       : ";
            cin >> boyut;
            cin.ignore();
            cout << "Tarih(YYYY-AA-GG): ";
            getline(cin, tarih);
            cout << "Oncelik(dusuk/orta/yuksek): ";
            getline(cin, oncelik);
            cout << "Durum(Aktif/Islemde/Arsiv): ";
            getline(cin, durum);
            cout << "Puan (0-10)      : ";
            cin >> puan;
            cin.ignore();
            cout << "Kritik Not       : ";
            getline(cin, not_);

            // MODUL 1 - kayit listesine ekle
            kayitEkle(kayitListesi, id, baslik, kategori, boyut, tarih, oncelik, durum, puan, not_);

            // BAGLANTI -> Modul 2: her ekleme otomatik loglanir
            gunlukKaydiEkle(gunlukListesi, id, "Ekle", tarih + " 00:00", "", baslik);

            // BAGLANTI -> Modul 3 (Stack): asagidaki satirin basindaki // sil
            // stackPush(islemStack, id, "Ekle", baslik);

            // BAGLANTI -> Modul 6 (Hash): asagidaki satirin basindaki // sil
            // hashGuncelle(hashTablosu, id, kategori, oncelik, puan);

        } else if (secim == 2) {
            int id;
            cout << "Silinecek ID: ";
            cin >> id;
            cin.ignore();

            // Log icin silmeden once eski degeri al
            Kayit* k = idyeGoreAra(kayitListesi, id);
            string eskiBaslik = (k != NULL) ? k->baslik : "";

            // MODUL 1 - sil
            bool basarili = idyeGoreSil(kayitListesi, id);

            if (basarili) {
                // BAGLANTI -> Modul 2: silme otomatik loglanir
                gunlukKaydiEkle(gunlukListesi, id, "Sil", "2025-01-01 00:00", eskiBaslik, "");

                // BAGLANTI -> Modul 3 (Stack): asagidaki satirin basindaki // sil
                // stackPush(islemStack, id, "Sil", eskiBaslik);
            }

        } else if (secim == 3) {
            string baslik, durum, oncelik;
            float puan;
            cout << "Guncellenecek Baslik        : ";
            getline(cin, baslik);
            cout << "Yeni Durum                  : ";
            getline(cin, durum);
            cout << "Yeni Oncelik                : ";
            getline(cin, oncelik);
            cout << "Yeni Puan                   : ";
            cin >> puan;
            cin.ignore();

            // Log icin eski degeri al
            Kayit* p = kayitListesi;
            string eskiDurum = "";
            while (p != NULL) {
                if (p->baslik == baslik) {
                    eskiDurum = p->durum;
                    break;
                }
                p = p->sonraki;
            }

            // MODUL 1 - guncelle
            bool basarili = basligaGoreGuncelle(kayitListesi, baslik, durum, oncelik, puan);
            if (basarili) {
                // BAGLANTI -> Modul 2: guncelleme otomatik loglanir
                gunlukKaydiEkle(gunlukListesi, 0, "Guncelle", "2025-01-01 00:00", eskiDurum, durum);

                // BAGLANTI -> Modul 3 (Stack): asagidaki satirin basindaki // sil
                // stackPush(islemStack, 0, "Guncelle", eskiDurum);

                // BAGLANTI -> Modul 6 (Hash): asagidaki satirin basindaki // sil
                // hashGuncelle(hashTablosu, 0, "", oncelik, puan);
            }

        } else if (secim == 4) {
            zamanDamgasiIleListele(kayitListesi);

        } else if (secim == 5) {
            int id;
            cout << "Aranacak ID: ";
            cin >> id;
            Kayit* k = idyeGoreAra(kayitListesi, id);
            if (k != NULL)
                kayitYazdir(k);
            else
                cout << "[HATA] Bulunamadi." << endl;

        } else if (secim == 6) {
            toplamKayitSayisi(kayitListesi);

        } else if (secim == 7) {
            boyutaGoreSirala(kayitListesi);

        } else if (secim == 8) {
            enEski10Kayit(kayitListesi);

        } else if (secim == 9) {
            int id;
            string not_;
            cout << "ID        : ";
            cin >> id;
            cin.ignore();
            cout << "Kritik Not: ";
            getline(cin, not_);

            bool basarili = kritikNotEkle(kayitListesi, id, not_);

            if (basarili) {
                // BAGLANTI -> Modul 2: not ekleme otomatik loglanir
                gunlukKaydiEkle(gunlukListesi, id, "Guncelle", "2025-01-01 00:00", "", not_);

                // BAGLANTI -> Modul 7 (Sikistirma): asagidaki satirin basindaki // sil
                // sikistirmaKontrol(kayitListesi, id);
            }

        } else if (secim == 10) {
            kritikKayitlariListele(kayitListesi);

        } else if (secim != 0) {
            cout << "[HATA] Gecersiz secim." << endl;
        }

    } while (secim != 0);
}

// ============================================================
// MODUL 2 MENUSU
// ============================================================
// Loglar zaten otomatik duser, bu menuden manuel de eklenebilir.
//
// Modul 8'i yapan arkadas (Performans):
//   "BAGLANTI -> Modul 8" satirlarinin basindaki // sil
// ============================================================
void modul2Menu() {
    int secim;
    do {
        cout << "\n--- MODUL 2: OPERASYON GUNLUGU ---" << endl;
        cout << "1. Manuel Log Ekle" << endl;
        cout << "2. Kayit ID'ye Gore Listele" << endl;
        cout << "3. Tarih Araligina Gore Listele" << endl;
        cout << "4. Gunluk Raporu" << endl;
        cout << "5. Islem Turune Gore Listele" << endl;
        cout << "0. Geri" << endl;
        cout << "Secim: ";
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            int id;
            string tur, tarih, eski, yeni;
            cout << "Kayit ID  : ";
            cin >> id;
            cin.ignore();
            cout << "Islem Turu (Ekle/Sil/Guncelle/Dequeue): ";
            getline(cin, tur);
            cout << "Tarih/Saat (YYYY-AA-GG SS:DD)         : ";
            getline(cin, tarih);
            cout << "Eski Deger: ";
            getline(cin, eski);
            cout << "Yeni Deger: ";
            getline(cin, yeni);
            gunlukKaydiEkle(gunlukListesi, id, tur, tarih, eski, yeni);

            // BAGLANTI -> Modul 8 (Performans): asagidaki satirin basindaki // sil
            // performansKaydet("Modul2-LogEkle");

        } else if (secim == 2) {
            int id;
            cout << "Kayit ID: ";
            cin >> id;
            kayitIdIslemleriListele(gunlukListesi, id);

        } else if (secim == 3) {
            string bas_, bitis;
            cout << "Baslangic (YYYY-AA-GG): ";
            cin >> bas_;
            cout << "Bitis     (YYYY-AA-GG): ";
            cin >> bitis;
            tarihAraligiListele(gunlukListesi, bas_, bitis);

        } else if (secim == 4) {
            gunlukRaporOlustur(gunlukListesi);

            // BAGLANTI -> Modul 8 (Performans): asagidaki satirin basindaki // sil
            // performansKaydet("Modul2-Rapor");

        } else if (secim == 5) {
            string tur;
            cout << "Islem Turu (Ekle/Sil/Guncelle/Dequeue): ";
            getline(cin, tur);
            islemTuruneGoreListele(gunlukListesi, tur);

        } else if (secim != 0) {
            cout << "[HATA] Gecersiz secim." << endl;
        }

    } while (secim != 0);
}

// ============================================================
// MODUL 3 MENUSU - STACK
// ============================================================
// Bu menuyu Modul 3'u yapan arkadas dolduracak.
//
// Yapman gerekenler:
//   1. modul3/ klasoru ac, icine stack.h ve stack.cpp yaz
//   2. stack.h icine Stack struct'ini ve fonksiyon prototiplerini koy
//   3. stack.cpp icine fonksiyonlari yaz
//   4. Bu dosyanin en ustundeki #include "modul3/stack.h" satirinin // sil
//   5. Global degiskenler bolumundeki Stack* satirinin // sil
//   6. Modul 1 menusundeki "BAGLANTI -> Modul 3" satirlarinin // sil
//
// Stack struct ornegi (stack.h icine):
//   struct StackDugum {
//       int    kayitId;
//       string islemTuru;
//       string deger;
//       StackDugum* ust;   // bir ust eleman
//   };
//
// Fonksiyonlar (stack.h icine prototype, stack.cpp icine kod):
//   void stackPush(StackDugum*& tepe, int id, string tur, string deger);
//   void stackPop (StackDugum*& tepe);   // undo: Modul 1'e geri uygular
//   int  stackDerinlik(StackDugum* tepe);
//   void son10Goster(StackDugum* tepe);
//   void islemAnalizi(StackDugum* tepe); // en sik islem turu
// ============================================================
void modul3Menu() { cout << "[TODO] Modul 3 - Stack henuz eklenmedi." << endl; }

// ============================================================
// MODUL 4 MENUSU - QUEUE
// ============================================================
// Bu menuyu Modul 4'u yapan arkadas dolduracak.
//
// Yapman gerekenler:
//   1. modul4/ klasoru ac, icine queue.h ve queue.cpp yaz
//   2. Bu dosyanin en ustundeki #include "modul4/queue.h" satirinin // sil
//   3. Global degiskenler bolumundeki Queue* satirinin // sil
//
// ONEMLI BAGLANTI - Dequeue yapilinca Modul 1'e kayit eklenir:
//   Talep t = dequeue(talepQueue);
//   kayitEkle(kayitListesi, t.id, t.baslik, ...);        // Modul 1'e ekle
//   gunlukKaydiEkle(gunlukListesi, t.id, "Dequeue", ...); // Modul 2'ye logla
//
// Queue struct ornegi (queue.h icine):
//   struct Talep {
//       int    talepId;
//       string kategori;
//       float  boyut;
//       string oncelik;
//       string talepZamani;
//       Talep* sonraki;
//   };
//   struct Queue {
//       Talep* on;    // ilk eleman
//       Talep* arka;  // son eleman
//   };
// ============================================================
void modul4Menu() { cout << "[TODO] Modul 4 - Queue henuz eklenmedi." << endl; }

// ============================================================
// MODUL 5, 6, 7, 8 MENUSU
// ============================================================
// Ilgili arkadaslar kendi modullerini yazacak.
// Genel kural ayni:
//   - kendi .h/.cpp dosyalarini yaz
//   - include ve global degiskeni buraya ekle
//   - asagidaki fonksiyonun icini doldur
//
// Modul 5 (Tree): kayitListesi uzerinde agac kurulur
//   Veri kaynagi: kayitListesi (Modul 1)
//
// Modul 6 (Hash): kayitListesi uzerinde hash tablosu kurulur
//   Veri kaynagi: kayitListesi (Modul 1)
//
// Modul 7 (Sikistirma): buyuk kayitlari sikistirir
//   Veri kaynagi: kayitListesi (Modul 1), boyutu buyuk olanlar
//
// Modul 8 (Performans): tum modullerden sure verisi alir
//   Tum modullerden veri alir, rapor uretir
// ============================================================
void modul5Menu() { cout << "[TODO] Modul 5 - Tree henuz eklenmedi." << endl; }
void modul6Menu() { cout << "[TODO] Modul 6 - Hash henuz eklenmedi." << endl; }
void modul7Menu() { cout << "[TODO] Modul 7 - Sikistirma henuz eklenmedi." << endl; }
void modul8Menu() { cout << "[TODO] Modul 8 - Performans henuz eklenmedi." << endl; }

// ============================================================
// ANA MENU
// ============================================================
int main() {
    cout << "========================================" << endl;
    cout << "  BANKA KURUMSAL OPERASYON SISTEMI      " << endl;
    cout << "========================================" << endl;

    ornekVeriYukle();

    int secim;
    do {
        cout << "\n======= ANA MENU =======" << endl;
        cout << "1. Modul 1 - Kayit Yonetimi" << endl;
        cout << "2. Modul 2 - Operasyon Gunlugu" << endl;
        cout << "3. Modul 3 - Stack" << endl;
        cout << "4. Modul 4 - Queue" << endl;
        cout << "5. Modul 5 - Tree" << endl;
        cout << "6. Modul 6 - Hash" << endl;
        cout << "7. Modul 7 - Sikistirma" << endl;
        cout << "8. Modul 8 - Performans" << endl;
        cout << "0. Cikis" << endl;
        cout << "Secim: ";
        cin >> secim;

        if (secim == 1)
            modul1Menu();
        else if (secim == 2)
            modul2Menu();
        else if (secim == 3)
            modul3Menu();
        else if (secim == 4)
            modul4Menu();
        else if (secim == 5)
            modul5Menu();
        else if (secim == 6)
            modul6Menu();
        else if (secim == 7)
            modul7Menu();
        else if (secim == 8)
            modul8Menu();
        else if (secim != 0)
            cout << "[HATA] Gecersiz secim." << endl;

    } while (secim != 0);

    // Bellek temizligi
    // Her modul kendi temizlik satirini buraya ekler:
    listeTemizle(kayitListesi);
    gunlukTemizle(gunlukListesi);
    // stackTemizle(islemStack);
    // queueTemizle(talepQueue);

    cout << "[SISTEM] Cikis yapildi." << endl;
    return 0;
}
