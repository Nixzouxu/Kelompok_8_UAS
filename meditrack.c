// Program utama MediTrack
// Mengimpor definisi dan deklarasi dari file header
#include "meditrack.h"

// Fungsi untuk menampilkan header program
void displayHeader() {
    // Menampilkan judul program dengan border
    printf("\n========================================\n");
    printf("  MediTrack: Inventory & Expiry Analyzer  \n");
    printf("========================================\n");
}

// Fungsi untuk menampilkan efek loading  
void showLoading() {
    // Menampilkan animasi loading dengan titik
    printf("Memuat sistem ");
    for (int i = 0; i < 4; i++) {
        printf(".");
        fflush(stdout); // Memastikan teks ditampilkan langsung
        #ifdef _WIN32
            Sleep(500); // Jeda 500ms di Windows
        #else
            usleep(500000); // Jeda 500ms di Linux/Mac
        #endif
    }
    printf("\n");
}

// Fungsi untuk membersihkan layar
void clearScreen() {
    // Memilih perintah berdasarkan sistem operasi
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
