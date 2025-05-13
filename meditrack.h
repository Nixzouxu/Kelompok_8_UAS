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
