#include <iostream>
#include <conio.h>
using namespace std;

//deklarasi struktur node
struct node {
    string judul;
    int tahun;
    int rating;
    node *next;
};

node *head = NULL;
node *tail = NULL;

//dekklarasi fungsi insert di node pertama/paling depan
void insertFirst( string j, int t, int r ) {
    node *newNode = new node;
    newNode -> judul = j;
    newNode -> tahun = t;
    newNode -> rating = r;
    newNode -> next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        newNode -> next = head;
        head = newNode;
    }
}

//deklarasi fungsi insert di node terakhir/paling belakang
void insertLast ( string j, int t, int r ) {
    node *newNode = new node;
    newNode -> judul = j;
    newNode -> tahun = t;
    newNode -> rating = r;
    newNode -> next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = head;
    } else {
        tail -> next = newNode;
        tail = newNode;
    }
}


//deklarasi fungsi insert setelah node yang ditentukan
void insertAfter ( string j, int t, int r, string check ) {
    if (head == NULL) {
        cout << "List kosong!" << endl;
        return;
    }

    node *newNode = new node;
    newNode -> judul = j;
    newNode -> tahun = t;
    newNode -> rating = r;
    newNode -> next = NULL;

    node *p = head;
    while (p != NULL && p -> judul != check) {
        p = p -> next;
    }

    if (p == NULL) {
        cout << "Film berjudul " << check << " tidak ditemukan!" << endl;
        getch(); 
        delete newNode;
    } else {
        newNode -> next = p -> next;
        p -> next = newNode;
        if (p == tail) {
            tail = newNode;
        }
    }

}

// Hapus node dengan nilai tertentu
void deleteMiddle(string judul) {
    if (head == NULL) {
        cout << "Tidak ada film!\n";
        return;
    }
    if (head->judul == judul) {
        node *temp = head;
        head = head->next;
        if (temp == tail) tail = NULL;
        delete temp;
        return;
    }
    node *p = head;
    while (p->next != NULL && p->next->judul != judul) {
        p = p->next;
    }
    if (p->next == NULL) {
        cout << "Film dengan judul " << judul << " tidak ditemukan!\n";
        getch();
    } else {
        node *temp = p->next;
        p->next = temp->next;
        if (temp == tail) tail = p;
        delete temp;
    }
}

//cetak linked list
void display() {
    node *temp = head;
    cout << "List Film: \n";
    while (temp != NULL) {
        cout << temp -> judul << "("<< temp -> tahun << ") - " << temp -> rating << endl;
        temp = temp -> next;
    }

    int count = 0;
    node *p = head;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    cout << "Jumlah film: " << count << endl;
}

int main () {
    system("cls");
    int pil, tahun, rating, jumlah, ulang;
    string judul;

    cout << "Masukkan jumlah film awal: ";
    cin >> jumlah;
    for (int i = 0; i < jumlah; i++) {
        getchar();
        cout << "Film " << i + 1 << ": "<< endl;
        cout << "Judul: ";
        getline(cin, judul);
        cout << "Tahun: "; cin >> tahun;
        cout << "Rating: "; cin >> rating;
        insertLast(judul, tahun, rating);
        cout << endl;
    }
    // Nampilin list film
    display();
    getch();

    // akan terus ulang (minimal sekali) sampai pilihan != 2
    do {
        system("cls");
        cout << endl;
        cout << "Menu pengaturan list film: " << endl;
        cout << "1. Tambah Film" << endl;
        cout << "2. Hapus Film" << endl;
        cout << "3. Tampilkan list Film" << endl;
        cout << "Pilihan Anda: "; cin >> pil;
        
        int pos;
        string check;
        switch (pil) {
            case 1:
                system("cls");
                cout << "Mau masukin di mana? (1. Depan, 2. Belakang, 3. Setelah film ...): ";
                cin >> pos;
                getchar();
                cout << "Judul: "; getline(cin, judul);
                cout << "Tahun: "; cin >> tahun;
                cout << "Rating: "; cin >> rating;
                getchar();
                switch(pos) {
                    case 1:
                        insertFirst(judul, tahun, rating);
                        break;
                    case 2:
                        insertLast(judul, tahun, rating);
                        break;
                    case 3:
                        cout << "Masukkan judul film tetangganya: ";
                        getline(cin, check);
                        insertAfter(judul, tahun, rating, check);
                        break;
                    default:
                        cout << "Pilihan invalid!" << endl;
                        break;
                }
                // getch();
                system("cls");
                display();
                break;
            case 2:
                cout << "Masukkan judul film yang ingin dihapus: ";
                getchar();
                getline(cin, judul);
                deleteMiddle(judul);
                cout << endl;
                system("cls");
                display();
                break;
            case 3:
                system("cls");
                display();
                break;
            default:
                cout << "Pilihan invalid!" << endl;
                break;
        }

        do {
            cout << "Mau udahan? (1. Ya / 2. Tidak)";
            cin >> ulang;
            if (ulang == 2) {
                continue;
            } else if (ulang == 1) {
                cout << "Sampai jumpa Harry!!" << endl;
                getch();
            } else {
                cout <<"Pilihan invalid!" << endl;
            }
        } while (ulang != 1 && ulang != 2);
    } while (ulang == 2);
    return 0;
}