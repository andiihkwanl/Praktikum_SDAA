#include <iostream>
#include <string>

using namespace std;

struct Perhiasan {
    string jenis;
    string nama;
    double berat;
    double harga;
};

struct Node {
    Perhiasan data;
    Node* next;
};

void tambahPerhiasan(Node* &head);
void tampilkanSemuaPerhiasan(Node* head);
void ubahPerhiasan(Node* head);
void hapusPerhiasan(Node* &head);
void pushPerhiasan(Node* &head);
void popPerhiasan(Node* &head);
void enqueuePerhiasan(Node* &head);
void dequeuePerhiasan(Node* &head);
int menu();
void jalankanMenu(Node* &head);

int main() {
    Node* head = nullptr;  
    jalankanMenu(head);
    return 0;
}

int menu() {
    int pilihan;
    cout << "\nMenu:" << endl;
    cout << "1. Tambah Data Perhiasan" << endl;
    cout << "2. Tampilkan Semua Data Perhiasan" << endl;
    cout << "3. Ubah Data Perhiasan" << endl;
    cout << "4. Hapus Data Perhiasan" << endl;
    cout << "5. Push ke Stack" << endl;
    cout << "6. Pop dari Stack" << endl;
    cout << "7. Enqueue ke Queue" << endl;
    cout << "8. Dequeue dari Queue" << endl;
    cout << "9. Keluar" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;
    return pilihan;
}

void jalankanMenu(Node* &head) {
    char ulang;
    do {
        switch (menu()) {
            case 1:
                tambahPerhiasan(head);
                break;
            case 2:
                tampilkanSemuaPerhiasan(head);
                break;
            case 3:
                tampilkanSemuaPerhiasan(head);
                ubahPerhiasan(head);
                break;
            case 4:
                tampilkanSemuaPerhiasan(head);
                hapusPerhiasan(head);
                break;
            case 5:
                pushPerhiasan(head);
                break;
            case 6:
                popPerhiasan(head);
                break;
            case 7:
                enqueuePerhiasan(head);
                break;
            case 8:
                dequeuePerhiasan(head);
                break;
            case 9:
                cout << "Program selesai." << endl;
                return;
            default:
                cout << "Pilihan tidak valid." << endl;
        }

        cout << "\nApakah Anda ingin menambahkan/mengubah/menghapus data lainnya? (Y/N): ";
        cin >> ulang;
    } while (ulang == 'Y' || ulang == 'y');
}

void tambahPerhiasan(Node* &head) {
    Node* newNode = new Node;  
    cout << "Jenis (Gelang/Kalung/Cincin): ";
    cin >> newNode->data.jenis;
    cout << "Nama Perhiasan: ";
    cin >> newNode->data.nama;
    cout << "Berat (gram): ";
    cin >> newNode->data.berat;
    cout << "Harga (Rp): ";
    cin >> newNode->data.harga;

    newNode->next = nullptr; 

    if (head == nullptr) {
        head = newNode;  
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode; 
    }

    cout << "Data perhiasan berhasil ditambahkan." << endl;
}

void tampilkanSemuaPerhiasan(Node* head) {
    if (head == nullptr) {
        cout << "Daftar perhiasan kosong." << endl;
    } else {
        Node* temp = head;
        int indeks = 0;
        cout << "Daftar Perhiasan:" << endl;
        while (temp != nullptr) {
            cout << "Indeks: " << indeks 
                 << ", Jenis: " << temp->data.jenis 
                 << ", Nama: " << temp->data.nama 
                 << ", Berat: " << temp->data.berat 
                 << " gram, Harga: Rp" << temp->data.harga << endl;
            temp = temp->next;
            indeks++;
        }
    }
}

void ubahPerhiasan(Node* head) {
    if (head == nullptr) {
        cout << "Daftar perhiasan kosong." << endl;
        return;
    }

    int indeks;
    cout << "Masukkan indeks perhiasan yang ingin diubah: ";
    cin >> indeks;

    Node* temp = head;
    for (int i = 0; i < indeks; ++i) {
        if (temp == nullptr) {
            cout << "Indeks tidak valid." << endl;
            return;
        }
        temp = temp->next;
    }

    if (temp != nullptr) {
        cout << "Jenis (Gelang/Kalung/Cincin): ";
        cin >> temp->data.jenis;
        cout << "Nama Perhiasan: ";
        cin >> temp->data.nama;
        cout << "Berat (gram): ";
        cin >> temp->data.berat;
        cout << "Harga (Rp): ";
        cin >> temp->data.harga;
        cout << "Data perhiasan berhasil diubah." << endl;
    } else {
        cout << "Indeks tidak valid." << endl;
    }
}

void hapusPerhiasan(Node* &head) {
    if (head == nullptr) {
        cout << "Daftar perhiasan kosong." << endl;
        return;
    }

    int indeks;
    cout << "Masukkan indeks perhiasan yang ingin dihapus: ";
    cin >> indeks;

    if (indeks == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Data perhiasan berhasil dihapus." << endl;
        return;
    }

    Node* temp = head;
    for (int i = 0; i < indeks - 1; ++i) {
        if (temp == nullptr || temp->next == nullptr) {
            cout << "Indeks tidak valid." << endl;
            return;
        }
        temp = temp->next;
    }

    Node* nodeToDelete = temp->next;
    if (nodeToDelete != nullptr) {
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
        cout << "Data perhiasan berhasil dihapus." << endl;
    } else {
        cout << "Indeks tidak valid." << endl;
    }
}

void pushPerhiasan(Node* &head) {
    Node* newNode = new Node;
    cout << "Jenis (Gelang/Kalung/Cincin): ";
    cin >> newNode->data.jenis;
    cout << "Nama Perhiasan: ";
    cin >> newNode->data.nama;
    cout << "Berat (gram): ";
    cin >> newNode->data.berat;
    cout << "Harga (Rp): ";
    cin >> newNode->data.harga;

    newNode->next = head; 
    head = newNode;

    cout << "Data perhiasan berhasil ditambahkan ke stack." << endl;
}

void popPerhiasan(Node* &head) {
    if (head == nullptr) {
        cout << "Stack kosong." << endl;
    } else {
        Node* temp = head;
        head = head->next;
        cout << "Data perhiasan '" << temp->data.nama << "' telah dihapus dari stack." << endl;
        delete temp;
    }
}

void enqueuePerhiasan(Node* &head) {
    Node* newNode = new Node;
    cout << "Jenis (Gelang/Kalung/Cincin): ";
    cin >> newNode->data.jenis;
    cout << "Nama Perhiasan: ";
    cin >> newNode->data.nama;
    cout << "Berat (gram): ";
    cin >> newNode->data.berat;
    cout << "Harga (Rp): ";
    cin >> newNode->data.harga;

    newNode->next = nullptr;  

    if (head == nullptr) {
        head = newNode;  
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode; 
    }

    cout << "Data perhiasan berhasil ditambahkan ke queue." << endl;
}


void dequeuePerhiasan(Node* &head) {
    if (head == nullptr) {
        cout << "Queue kosong." << endl;
    } else {
        Node* temp = head;
        head = head->next;
        cout << "Data perhiasan '" << temp->data.nama << "' telah dihapus dari queue." << endl;
        delete temp;
    }
}