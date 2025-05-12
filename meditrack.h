// File header untuk MediTrack
// Berisi pustaka, struktur, dan deklarasi fungsi yang diperlukan

// Pustaka standar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // Untuk Sleep di Windows
#else
#include <unistd.h> // Untuk usleep di Linux/Mac
#endif

// Struktur untuk menyimpan data obat
typedef struct {
    char name[50];      // Nama obat
    int stock;          // Jumlah stok
    char expiry[11];    // Tanggal kadaluwarsa (format: YYYY-MM-DD)
} Medicine;

// Node untuk Linked List penyimpanan obat
typedef struct MedicineNode {
    Medicine med;       // Data obat
    struct MedicineNode* next; // Pointer ke node berikutnya
} MedicineNode;

// Node untuk Min Heap berdasarkan tanggal kadaluwarsa
typedef struct {
    char expiry[11];    // Tanggal kadaluwarsa
    char name[50];      // Nama obat
} HeapNode;

typedef struct {
    HeapNode* nodes;    // Array untuk menyimpan node heap
    int size;           // Jumlah elemen saat ini
    int capacity;       // Kapasitas maksimum heap
} MinHeap;

// Node untuk Queue permintaan obat
typedef struct RequestObat {
    char medName[50];   // Nama obat yang diminta
    int quantity;       // Jumlah yang diminta
    struct RequestObat* next; // Pointer ke node berikutnya (perbaikan di sini)
} RequestObat;

typedef struct {
    RequestObat* front; // Depan antrian
    RequestObat* rear;  // Belakang antrian
} Queue;

// Deklarasi fungsi
void displayHeader();
void showLoading();
void clearScreen();
void addMedicine(MedicineNode** head, Medicine med, MinHeap* heap);
void showMedicines(MedicineNode* head);
void updateStock(MedicineNode* head, char* name, int quantity);
MinHeap* createHeap(int capacity);
void addToHeap(MinHeap* heap, char* expiry, char* name);
HeapNode getNearestExpiry(MinHeap* heap);
Queue* createQueue();
void addRequest(Queue* queue, char* medName, int quantity);
void processRequest(Queue* queue, MedicineNode* head);
#include "meditrack.h" // Ganti jika nama file header berbeda

int main() {
    MedicineNode* head = NULL;          // Linked list obat
    MinHeap* heap = createHeap(100);    // Heap untuk tanggal kadaluwarsa
    Queue* queue = createQueue();       // Queue permintaan obat

    int choice;
    do {
        clearScreen();
        displayHeader();
        printf("\nMenu:\n");
        printf("1. Tambah Obat\n");
        printf("2. Lihat Daftar Obat\n");
        printf("3. Tambah Permintaan Obat\n");
        printf("4. Proses Permintaan Obat\n");
        printf("5. Lihat Obat Kadaluwarsa Terdekat\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        getchar(); // Buang newline

        if (choice == 1) {
            Medicine med;
            printf("Nama obat: ");
            fgets(med.name, sizeof(med.name), stdin);
            med.name[strcspn(med.name, "\n")] = 0;

            printf("Stok: ");
            scanf("%d", &med.stock);
            getchar();

            printf("Tanggal kadaluwarsa (YYYY-MM-DD): ");
            fgets(med.expiry, sizeof(med.expiry), stdin);
            med.expiry[strcspn(med.expiry, "\n")] = 0;

            addMedicine(&head, med, heap);
            showLoading();

        } else if (choice == 2) {
            showMedicines(head);
            printf("\nTekan ENTER untuk kembali ke menu...");
            getchar();

        } else if (choice == 3) {
            char name[50];
            int qty;

            printf("Nama obat: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            printf("Jumlah permintaan: ");
            scanf("%d", &qty);
            getchar();

            addRequest(queue, name, qty);
            printf("Permintaan telah ditambahkan!\n");
            sleep(1);

        } else if (choice == 4) {
            processRequest(queue, head);
            printf("\nTekan ENTER untuk kembali ke menu...");
            getchar();

        } else if (choice == 5) {
            if (heap->size > 0) {
                HeapNode nearest = getNearestExpiry(heap);
                printf("Obat kadaluwarsa terdekat:\n");
                printf("Nama : %s\n", nearest.name);
                printf("Kedaluwarsa : %s\n", nearest.expiry);
            } else {
                printf("Heap kosong.\n");
            }
            printf("\nTekan ENTER untuk kembali ke menu...");
            getchar();
        }

    } while (choice != 0);

    printf("Terima kasih telah menggunakan MediTrack!\n");
    return 0;
}

