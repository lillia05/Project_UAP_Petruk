#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

struct Pengguna {
    char namaPengguna[50];
    char kataSandi[50];
};

class TempatParkir {
public:
    int id;
    string lokasi;
    bool tersedia;

    TempatParkir(int id, string lokasi) : id(id), lokasi(lokasi), tersedia(true) {}
};

void cetakGaris() {
    cout << "=========================================" << endl;
}

void daftarPengguna(const char* namaBerkas) {
    Pengguna pengguna;
    cout << "Masukkan nama pengguna: ";
    cin >> pengguna.namaPengguna;
    cout << "Masukkan kata sandi: ";
    cin >> pengguna.kataSandi;

    ofstream keluarBerkas(namaBerkas, ios::app);
    keluarBerkas.write(reinterpret_cast<char*>(&pengguna), sizeof(Pengguna));
    keluarBerkas.close();
}

bool masukPengguna(const char* namaBerkas) {
    Pengguna pengguna;
    char namaPengguna[50];
    char kataSandi[50];

    cout << "Masukkan nama pengguna: ";
    cin >> namaPengguna;
    cout << "Masukkan kata sandi: ";
    cin >> kataSandi;

    ifstream masukBerkas(namaBerkas, ios::in);
    while (masukBerkas.read(reinterpret_cast<char*>(&pengguna), sizeof(Pengguna))) {
        if (strcmp(pengguna.namaPengguna, namaPengguna) == 0 && strcmp(pengguna.kataSandi, kataSandi) == 0) {
            masukBerkas.close();
            return true;
        }
    }

    masukBerkas.close();
    return false;
}

vector<TempatParkir> cariTempatParkir(const vector<TempatParkir>& tempat, const string& lokasi) {
    vector<TempatParkir> hasil;
    for (const auto& tp : tempat) {
        if (tp.lokasi == lokasi && tp.tersedia) {
            hasil.push_back(tp);
        }
    }
    return hasil;
}

void konfirmasiPemesanan(TempatParkir& tempat, const string& lokasi) {
    tempat.tersedia = false;
    cetakGaris();
    cout << "=        SISTEM PEMESANAN PARKIR        =" << endl;
    cetakGaris();
    cout << "Pemesanan dikonfirmasi ID: " << tempat.id << " di " << lokasi << endl;
}

string generateBarcode(int id) {
    return "BARCODE_" + to_string(id); 
}

void cetakStrukParkir(const TempatParkir& tempat, const string& lokasi) {
    ofstream keluarBerkas("struk_parkir.txt");
    string barcode = generateBarcode(tempat.id);

    keluarBerkas << "ID Tempat Parkir: " << tempat.id << endl;
    keluarBerkas << "Lokasi: " << lokasi << endl;
    keluarBerkas << "Status: " << (tempat.tersedia ? "Tersedia" : "Dipesan") << endl;
    keluarBerkas << "Barcode: " << barcode << endl;
    keluarBerkas.close();

    cout << "Struk dicetak dengan barcode: " << barcode << endl;
    cetakGaris();
    cout << endl;
}

void menuSetelahCetakStruk() {
    int pilihan;
    cout << "=  1. Kembali ke menu utama\n";
    cetakGaris();
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    while (pilihan != 1) {
        cout << "Pilihan tidak valid. Masukkan 1 untuk kembali ke menu utama: ";
        cin >> pilihan;
    }
}

vector<TempatParkir> cari(const vector<TempatParkir>& tempat, const string& lokasi, int awal, int akhir) {
    if (awal > akhir) {
        return {};
    }

    int tengah = awal + (akhir - awal) / 2;
    vector<TempatParkir> hasilKiri = cari(tempat, lokasi, awal, tengah - 1);
    vector<TempatParkir> hasilKanan = cari(tempat, lokasi, tengah + 1, akhir);

    vector<TempatParkir> hasil = hasilKiri;
    if (tempat[tengah].lokasi == lokasi && tempat[tengah].tersedia) {
        hasil.push_back(tempat[tengah]);
    }
    hasil.insert(hasil.end(), hasilKanan.begin(), hasilKanan.end());

    return hasil;
}

void tampilkanLokasi(const vector<string>& lokasiParkir) {
    cout << "=        SISTEM PEMESANAN PARKIR        =" << endl;
    cetakGaris();
    cout << "=  Lokasi parkir yang tersedia:\n";
    for (size_t i = 0; i < lokasiParkir.size(); ++i) {
        cout << "=  " << i + 1 << ". " << lokasiParkir[i] << endl;
    }
}

int main() {
    const char* namaBerkasPengguna = "pengguna.dat";
    vector<TempatParkir> tempatParkir;
    vector<string> lokasiParkir = {"Lokasi A", "Lokasi B", "Lokasi C"};

    for (const auto& lokasi : lokasiParkir) {
        for (int i = 1; i <= 10; ++i) {
            tempatParkir.emplace_back(i, lokasi);
        }
    }
int pilihan;
    while (true) {
        cetakGaris();
        cout << "=\t      SELAMAT DATANG\t        =" << endl;
        cetakGaris();
        cout << "=  1. Daftar\t\t\t        =" << endl;
        cout << "=  2. Masuk\t\t\t        =" << endl;
        cout << "=  3. Keluar\t\t\t        =" << endl;
        cetakGaris();
        cout << "= Masukkan Pilihan : ";
        cin >> pilihan;
        cetakGaris();

        if (pilihan == 1) {
            daftarPengguna(namaBerkasPengguna);
            cout << "### Registrasi berhasil ###\n" << endl;
        } else if (pilihan == 2) {
            if (masukPengguna(namaBerkasPengguna)) {
                cout << "### Masuk berhasil ###\n" << endl;
