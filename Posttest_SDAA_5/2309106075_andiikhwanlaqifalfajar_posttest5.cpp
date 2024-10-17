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
Node* mergeSort(Node* head);
Node* merge(Node* left, Node* right);
Node* quickSort(Node* head, Node* end);
Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd);
int menu();
void jalankanMenu(Node* &head);
Node* getTail(Node* head);

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
    cout << "3. Sort Ascending (Merge Sort)" << endl;
    cout << "4. Sort Descending (Quick Sort)" << endl;
    cout << "5. Keluar" << endl;
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
                head = mergeSort(head); 
                cout << "Data telah diurutkan secara ascending (Merge Sort)." << endl;
                tampilkanSemuaPerhiasan(head);
                break;
            case 4: {
                Node* tail = getTail(head);
                head = quickSort(head, tail); 
                cout << "Data telah diurutkan secara descending (Quick Sort)." << endl;
                tampilkanSemuaPerhiasan(head);
                break;
            }
            case 5:
                cout << "Program selesai." << endl;
                return;
            default:
                cout << "Pilihan tidak valid." << endl;
        }

        cout << "\nApakah Anda ingin melanjutkan? (Y/N): ";
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

    newNode->next = head;
    head = newNode;

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

Node* mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node* slow = head;
    Node* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;

    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);

    return merge(left, right);
}

Node* merge(Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node* result = nullptr;
    if (left->data.harga < right->data.harga) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

Node* quickSort(Node* head, Node* end) {
    if (head == nullptr || head == end) {
        return head;
    }

    Node* newHead = nullptr;
    Node* newEnd = nullptr;

    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSort(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSort(pivot->next, newEnd);

    return newHead;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = nullptr;
    Node* curr = head;
    Node* tail = pivot;

    while (curr != pivot) {
        if (curr->data.harga > pivot->data.harga) {
            if (*newHead == nullptr) {
                *newHead = curr;
            }
            prev = curr;
            curr = curr->next;
        } else {
            if (prev != nullptr) {
                prev->next = curr->next;
            }
            Node* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if (*newHead == nullptr) {
        *newHead = pivot;
    }

    *newEnd = tail;

    return pivot;
}