#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define PINK "\033[95m"
#define GREY "\033[90m"
#define RESET "\033[0m"

void clearScreen() {
    system("cls");
}

struct Pengguna {
    char namaPengguna[50];
    char kataSandi[50];
};

class TempatParkir {
private:
    char id[10];
    bool tersedia;
    bool isMotor;

public:
    TempatParkir(const char* id, bool isMotor) {
        strcpy(this->id, id);
        this->tersedia = true;
        this->isMotor = isMotor;
    }

    const char* getId() const {
        return id;
    }

    bool getTersedia() const {
        return tersedia;
    }

    bool getIsMotor() const {
        return isMotor;
    }

    void pesan() {
        tersedia = false;
    }

    void lepas() {
        tersedia = true;
    }
};

class SistemParkir {
private:
    vector<Pengguna> penggunas;
    vector<TempatParkir> tempatParkirA;
    vector<TempatParkir> tempatParkirB;
    vector<TempatParkir> tempatParkirC;
    list<string> riwayat;
    queue<string> antrianPengguna;
    stack<string> tumpukanUndo;
    bool masuk;
    bool isMotor;
    char lokasiSaatIni;

    void muatTempatParkir() {
        const char* ids[] = {
            "B01", "B02", "B03", "B04", "B05", "B06", "B07", "B08", "B09", "B10",
            "T01", "T02", "T03", "T04", "T05", "T06", "T07", "T08", "T09", "T10",
            "T11", "T12", "T13", "T14", "T15", "T16", "T17", "T18", "T19", "T20",
            "B11", "B12", "B13", "B14", "B15", "B16", "B17", "B18", "B19", "B20"
        };

        bool isMotor[] = {
            false, false, false, false, false, false, false, false, false, false,
            true, true, true, true, true, true, true, true, true, true,
            true, true, true, true, true, true, true, true, true, true,
            false, false, false, false, false, false, false, false, false, false
        };

        for (int i = 0; i < 40; i++) {
            tempatParkirA.push_back(TempatParkir(ids[i], isMotor[i]));
            tempatParkirB.push_back(TempatParkir(ids[i], isMotor[i]));
            tempatParkirC.push_back(TempatParkir(ids[i], isMotor[i]));
        }
    }

vector<TempatParkir>& dapatkanTempatParkir() {
    if (lokasiSaatIni == 'A') {
        return tempatParkirA;
    } else if (lokasiSaatIni == 'B') {
        return tempatParkirB;
    } else if (lokasiSaatIni == 'C') {
        return tempatParkirC;
    } else {
        static vector<TempatParkir> tempatKosong;
        cout << RED << "Lokasi tidak valid!" << RESET << endl;
        return tempatKosong;
    }
}

    template <typename T, typename Predicate>
    T* temukanItem(vector<T>& koleksi, Predicate predikat) {
        auto it = find_if(koleksi.begin(), koleksi.end(), predikat);
        return (it != koleksi.end()) ? &(*it) : nullptr;
    }

    TempatParkir* temukanTempatParkirTersedia(vector<TempatParkir>& tempatParkir, int rendah, int tinggi) {
        if (rendah > tinggi) return nullptr;

        int tengah = rendah + (tinggi - rendah) / 2;
        if (tempatParkir[tengah].getTersedia() && ((isMotor && tempatParkir[tengah].getIsMotor()) || (!isMotor && !tempatParkir[tengah].getIsMotor()))) {
            return &tempatParkir[tengah];
        }

        TempatParkir* hasilKiri = temukanTempatParkirTersedia(tempatParkir, rendah, tengah - 1);
        if (hasilKiri != nullptr) return hasilKiri;

        return temukanTempatParkirTersedia(tempatParkir, tengah + 1, tinggi);
    }

public:
    SistemParkir() {
        muatTempatParkir();
        masuk = false;
        isMotor = false;
        lokasiSaatIni = 'A'; lokasiSaatIni = 'B'; lokasiSaatIni = 'C';
    }

    bool daftarPengguna(const char* namaPengguna, const char* kataSandi) {
        for (const Pengguna& pengguna : penggunas) {
            if (strcmp(pengguna.namaPengguna, namaPengguna) == 0) {
                return false;
            }
        }

        Pengguna penggunaBaru;
        strcpy(penggunaBaru.namaPengguna, namaPengguna);
        strcpy(penggunaBaru.kataSandi, kataSandi);
        penggunas.push_back(penggunaBaru);
        return true;
    }

    bool masukPengguna(const char* namaPengguna, const char* kataSandi) {
        for (const Pengguna& pengguna : penggunas) {
            if (strcmp(pengguna.namaPengguna, namaPengguna) == 0 && strcmp(pengguna.kataSandi, kataSandi) == 0) {
                masuk = true;
                return true;
            }
        }
        return false;
    }

