#include <iostream>
#include <string>

using namespace std;

struct Perhiasan {
    string jenis;
    string nama;
    double berat; 
    double harga;
};

void tambahPerhiasan(Perhiasan* daftarPerhiasan[], int &jumlahPerhiasan);
void tampilkanSemuaPerhiasan(Perhiasan* daftarPerhiasan[], int jumlahPerhiasan);
void ubahPerhiasan(Perhiasan* daftarPerhiasan[], int jumlahPerhiasan);
void hapusPerhiasan(Perhiasan* daftarPerhiasan[], int &jumlahPerhiasan);
int menu();
void jalankanMenu(Perhiasan* daftarPerhiasan[], int &jumlahPerhiasan);

const int MAX_PERHIASAN = 100; 

int main() {
    Perhiasan* daftarPerhiasan[MAX_PERHIASAN];
    int jumlahPerhiasan = 0;
    jalankanMenu(daftarPerhiasan, jumlahPerhiasan);
    return 0;
}

int menu() {
    int pilihan;
    cout << "\nMenu:" << endl;
    cout << "1. Tambah Data Perhiasan" << endl;
    cout << "2. Tampilkan Semua Data Perhiasan" << endl;
    cout << "3. Ubah Data Perhiasan" << endl;
    cout << "4. Hapus Data Perhiasan" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;
    return pilihan;
}

void jalankanMenu(Perhiasan* daftarPerhiasan[], int &jumlahPerhiasan) {
    char ulang;
    do {
        switch (menu()) {
            case 1:
                tambahPerhiasan(daftarPerhiasan, jumlahPerhiasan);
                break;
            case 2:
                tampilkanSemuaPerhiasan(daftarPerhiasan, jumlahPerhiasan);
                break;
            case 3:
                tampilkanSemuaPerhiasan(daftarPerhiasan, jumlahPerhiasan);
                cout << "Masukkan indeks perhiasan yang ingin diubah: ";
                ubahPerhiasan(daftarPerhiasan, jumlahPerhiasan);
                break;
            case 4:
                tampilkanSemuaPerhiasan(daftarPerhiasan, jumlahPerhiasan);
                hapusPerhiasan(daftarPerhiasan, jumlahPerhiasan);
                break;
            case 5:
                cout << "Program selesai." << endl;
                return;
            default:
                cout << "Pilihan tidak valid." << endl;
        }

        cout << "\nApakah Anda ingin menambahkan/mengubah/menghapus data lainnya? (Y/N): ";
        cin >> ulang;
    } while (ulang == 'Y' || ulang == 'y');
}

void tambahPerhiasan(Perhiasan* daftarPerhiasan[], int &jumlahPerhiasan) {
    if (jumlahPerhiasan >= MAX_PERHIASAN) {
        cout << "Kapasitas daftar perhiasan penuh." << endl;
        return;
    }

    Perhiasan* perhiasan = new Perhiasan;
    cout << "Jenis (Gelang/Kalung/Cincin): ";
    cin >> perhiasan->jenis;
    cout << "Nama Perhiasan: ";
    cin >> perhiasan->nama;
    cout << "Berat (gram): ";
    cin >> perhiasan->berat;
    cout << "Harga (Rp): ";
    cin >> perhiasan->harga;

    daftarPerhiasan[jumlahPerhiasan] = perhiasan;
    jumlahPerhiasan++;
    cout << "Data perhiasan berhasil ditambahkan." << endl;
}

void tampilkanSemuaPerhiasan(Perhiasan* daftarPerhiasan[], int jumlahPerhiasan) {
    if (jumlahPerhiasan == 0) {
        cout << "Daftar perhiasan kosong." << endl;
    } else {
        cout << "Daftar Perhiasan:" << endl;
        for (int i = 0; i < jumlahPerhiasan; ++i) {
            cout << "Indeks: " << i << ", Jenis: " << daftarPerhiasan[i]->jenis << ", Nama: " << daftarPerhiasan[i]->nama << ", Berat: " << daftarPerhiasan[i]->berat << " gram, Harga: Rp" << daftarPerhiasan[i]->harga << endl;
        }
    }
}

void ubahPerhiasan(Perhiasan* daftarPerhiasan[], int jumlahPerhiasan) {
    if (jumlahPerhiasan == 0) {
        cout << "Daftar perhiasan kosong." << endl;
        return;
    }

    int indeks;
    cin >> indeks;
    if (indeks < 0 || indeks >= jumlahPerhiasan) {
        cout << "Indeks tidak valid." << endl;
        return;
    }

    cout << "Jenis (Gelang/Kalung/Cincin): ";
    cin >> daftarPerhiasan[indeks]->jenis;
    cout << "Nama Perhiasan: ";
    cin >> daftarPerhiasan[indeks]->nama;
    cout << "Berat (gram): ";
    cin >> daftarPerhiasan[indeks]->berat;
    cout << "Harga (Rp): ";
    cin >> daftarPerhiasan[indeks]->harga;
    cout << "Data perhiasan berhasil diubah." << endl;
}

void hapusPerhiasan(Perhiasan* daftarPerhiasan[], int &jumlahPerhiasan) {
    if (jumlahPerhiasan == 0) {
        cout << "Daftar perhiasan kosong." << endl;
        return;
    }

    int indeks;
    cout << "Masukkan indeks perhiasan yang ingin dihapus: ";
    cin >> indeks;
    if (indeks < 0 || indeks >= jumlahPerhiasan) {
        cout << "Indeks tidak valid." << endl;
        return;
    }

    delete daftarPerhiasan[indeks];
    for (int i = indeks; i < jumlahPerhiasan - 1; ++i) {
        daftarPerhiasan[i] = daftarPerhiasan[i + 1];
    }
    jumlahPerhiasan--;
    cout << "Data perhiasan berhasil dihapus." << endl;
}