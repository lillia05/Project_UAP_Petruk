#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>

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

void clearScreen() {
    system("cls");
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
    clearScreen();
    cout << "=========================================" << endl;
    cout << "=        SISTEM PEMESANAN PARKIR        =" << endl;
    cout << "=========================================" << endl;
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

   clearScreen();
    cout << "=========================================" << endl;
    cout << "=        SISTEM PEMESANAN PARKIR        =" << endl;
    cout << "=========================================" << endl;
    cout << "Struk dicetak dengan barcode: " << barcode << endl;
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
    clearScreen();
    cout << "=========================================" << endl;
    cout << "=        SISTEM PEMESANAN PARKIR        =" << endl;
    cout << "=========================================" << endl;
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
        clearScreen();
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

                cetakGaris();
                tampilkanLokasi(lokasiParkir);

                int lokasiPilihan;
                cetakGaris();
                cout << "Masukkan nomor lokasi tempat parkir: ";
                cin >> lokasiPilihan;
                cetakGaris();

                if (lokasiPilihan < 1 || lokasiPilihan > lokasiParkir.size()) {
                    cout << "Pilihan lokasi tidak valid." << endl;
                } else {
                    string lokasi = lokasiParkir[lokasiPilihan - 1];

                    clearScreen();

                    vector<TempatParkir> tempatTersedia = cari(tempatParkir, lokasi, 0, tempatParkir.size() - 1);
                    if (!tempatTersedia.empty()) {
                        cetakGaris();
                        cout << "=        SISTEM PEMESANAN PARKIR        =" << endl;
                        cetakGaris();
                        cout << "=  Tempat parkir tersedia di " << lokasi << ":\n";
                        for (const auto& tp : tempatTersedia) {
                            cout << "=  ID Tempat: " << tp.id << endl;
                        }

                        int idTempat;
                        cetakGaris();
                        cout << "=  Masukkan ID tempat untuk memesan: ";
                        cin >> idTempat;
                        cetakGaris();

                        bool found = false;
                        for (auto& tp : tempatParkir) {
                            if (tp.id == idTempat && tp.tersedia) {
                                konfirmasiPemesanan(tp, lokasi);
                                cetakStrukParkir(tp, lokasi);
                                menuSetelahCetakStruk();
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            cout << "ID Tempat tidak valid atau sudah dipesan." << endl;
                        }
                    } else {
                        cout << "Tidak ada tempat parkir tersedia di " << lokasi << endl;
                    }
                }
            } else {
                cout << "!!! Masuk gagal. Nama pengguna atau kata sandi salah. !!!\n" << endl;
            }
        } else if (pilihan == 3) {
            cout << "Keluar dari program." << endl;
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
    return 0;
}
