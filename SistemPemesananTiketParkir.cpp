#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// Struktur untuk pengguna
struct Pengguna {
    char namaPengguna[50];
    char kataSandi[50];
};

// Kelas untuk tempat parkir
class TempatParkir {
public:
    int id;
    string lokasi;
    bool tersedia;

    TempatParkir(int id, string lokasi) : id(id), lokasi(lokasi), tersedia(true) {}
};

// Fungsi untuk mencetak garis horizontal
void cetakGaris() {
    cout << "=========================================" << endl;
}

// Fungsi untuk registrasi pengguna
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

// Fungsi untuk login pengguna
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

// Fungsi untuk mencari tempat parkir berdasarkan lokasi
vector<TempatParkir> cariTempatParkir(const vector<TempatParkir>& tempat, const string& lokasi) {
    vector<TempatParkir> hasil;
    for (const auto& tp : tempat) {
        if (tp.lokasi == lokasi && tp.tersedia) {
            hasil.push_back(tp);
        }
    }
    return hasil;
}
