#include <iostream>
#include <string>
#include <vector>

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

void tambahPerhiasan(Node*& head);
void tampilkanSemuaPerhiasan(Node* head);
Node* mergeSort(Node* head);
Node* merge(Node* left, Node* right);
Node* quickSort(Node* head, Node* end);
Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd);
Node* getTail(Node* head);
int menu();
void jalankanMenu(Node*& head);
int fibonacciSearch(vector<double>& arr, double x);
int jumpSearch(vector<double>& arr, double x);
int boyerMooreSearch(const string& text, const string& pattern);

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
    cout << "5. Cari Harga (Fibonacci Search)" << endl;
    cout << "6. Cari Harga (Jump Search)" << endl;
    cout << "7. Cari Nama Perhiasan (Boyer-Moore)" << endl;
    cout << "8. Keluar" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;
    return pilihan;
}

void jalankanMenu(Node*& head) {
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
            case 5: {
                vector<double> hargaList;
                Node* temp = head;
                while (temp != nullptr) {
                    hargaList.push_back(temp->data.harga);
                    temp = temp->next;
                }
                double target;
                cout << "Masukkan harga yang dicari: ";
                cin >> target;
                int result = fibonacciSearch(hargaList, target);
                if (result != -1)
                    cout << "Harga ditemukan di indeks " << result << "." << endl;
                else
                    cout << "Harga tidak ditemukan." << endl;
                break;
            }
            case 6: {
                vector<double> hargaList;
                Node* temp = head;
                while (temp != nullptr) {
                    hargaList.push_back(temp->data.harga);
                    temp = temp->next;
                }
                double target;
                cout << "Masukkan harga yang dicari: ";
                cin >> target;
                int result = jumpSearch(hargaList, target);
                if (result != -1)
                    cout << "Harga ditemukan di indeks " << result << "." << endl;
                else
                    cout << "Harga tidak ditemukan." << endl;
                break;
            }
            case 7: {
                string targetNama;
                cout << "Masukkan nama perhiasan yang dicari: ";
                cin >> targetNama;
                Node* temp = head;
                int indeks = 0;
                bool found = false;
                while (temp != nullptr) {
                    if (boyerMooreSearch(temp->data.nama, targetNama) != -1) {
                        cout << "Nama ditemukan pada indeks " << indeks << " (Nama: " << temp->data.nama << ")." << endl;
                        found = true;
                        break;
                    }
                    temp = temp->next;
                    indeks++;
                }
                if (!found)
                    cout << "Nama perhiasan tidak ditemukan." << endl;
                break;
            }
            case 8:
                cout << "Program selesai." << endl;
                return;
            default:
                cout << "Pilihan tidak valid." << endl;
        }

        cout << "\nApakah Anda ingin melanjutkan? (Y/N): ";
        cin >> ulang;
    } while (ulang == 'Y' || ulang == 'y');
}

void tambahPerhiasan(Node*& head) {
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

Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->data.harga <= right->data.harga) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

Node* mergeSort(Node* head) {
    if (!head || !head->next) {
        return head;
    }

    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;

    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);

    return merge(left, right);
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = nullptr;
    Node* curr = head;
    Node* tail = pivot;

    while (curr != pivot) {
        if (curr->data.harga > pivot->data.harga) {
            if ((*newHead) == nullptr) (*newHead) = curr;
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) prev->next = curr->next;
            Node* tmp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = tmp;
        }
    }

    if ((*newHead) == nullptr) (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node* newHead = nullptr;
    Node* newEnd = nullptr;

    Node* pivot = partition(head, end, &newHead, &newEnd);
    if (newHead != pivot) {
        Node* tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

Node* quickSort(Node* head, Node* end) {
    return quickSortRecur(head, end);
}

int fibonacciSearch(vector<double>& arr, double x) {
    int n = arr.size();
    int fibMMm2 = 0; 
    int fibMMm1 = 1; 
    int fibM = fibMMm2 + fibMMm1; 

    
    
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    
    while (fibM > 1) {
        
        int i = min(offset + fibMMm2, n - 1);

        
        
        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }

        
        
        else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }

        
        else return i;
    }

    
    if (fibMMm1 && arr[offset + 1] == x) return offset + 1;

   
    return -1;
}

int jumpSearch(vector<double>& arr, double x) {
    int n = arr.size();
    int step = 0;
    int prev = 0;

    
    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += 1; 
        if (prev >= n) return -1;
    }

    
    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) return -1;
    }

    
    if (arr[prev] == x) return prev;

    return -1; 
}

int boyerMooreSearch(const string& text, const string& pattern) {
    int m = pattern.size();
    int n = text.size();

    if (m > n) {
        return -1;
    }

    vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }
        if (j < 0) {
            return shift;
        } else {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }
    return -1;
}