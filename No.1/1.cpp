#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
using namespace std;

int main() {
    system("cls");

    int n;
    string hewan;

    cout << "Masukkan jumlah pasien: ";
    cin >> n;
    getchar();

    struct Data {
        string nama;
        string jenis;
        string usia;
        int level;
    };

    Data* queue = new Data[n];

    cout << endl;
    for (int i = 0; i < n; i++) { 
        cout << "Pasien: " << i + 1 << endl;

        cout << "Nama hewan: ";
        getline(cin, queue[i].nama);
        
        cout << "Jenis hewan: ";
        getline(cin, queue[i].jenis);
        
        cout << "Umur: ";
        getline(cin, queue[i].usia);
        
        cout << "Tingkat darurat (1-5): ";
        cin >> queue[i].level;
        
        cout << endl;
        getchar();
    }

    // Sorting
    for (int i=0; i < n - 1; i++) {
        for (int j=0; j < n - i - 1; j++) {
            if (queue[j].level < queue[j + 1].level) {
                Data temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (char &c : queue[i].nama){
            c = toupper(c);
        }
        cout << i+1 << ". " << queue[i].nama << " (" << queue[i].usia << ") - Darurat " << queue[i].level << endl;
    }
}