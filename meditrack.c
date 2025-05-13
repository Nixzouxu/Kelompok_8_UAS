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

// --- Fungsi Linked List ---
// Menambahkan obat baru ke Linked List dan Min Heap
void addMedicine(MedicineNode** head, Medicine med, MinHeap* heap) {
    // Membuat node baru untuk Linked List
    MedicineNode* newNode = (MedicineNode*)malloc(sizeof(MedicineNode));
    newNode->med = med;
    newNode->next = *head;
    *head = newNode;
    // Menambahkan ke Min Heap
    addToHeap(heap, med.expiry, med.name);
    printf("\nObat %s berhasil ditambahkan.\n", med.name);
    printf("Tekan Enter untuk kembali...");
    getchar(); // Menangkap Enter
    getchar(); // Menunggu input Enter
}

// Menampilkan semua obat dalam inventori
void showMedicines(MedicineNode* head) {
    // Menampilkan header tabel
    printf("\nDaftar Inventori:\n");
    printf("------------------------------------\n");
    printf("Nama\t\tStok\tKadaluwarsa\n");
    printf("------------------------------------\n");
    // Melintasi Linked List untuk menampilkan setiap obat
    while (head) {
        printf("%-15s %d\t%s\n", head->med.name, head->med.stock, head->med.expiry);
        head = head->next;
    }
    printf("------------------------------------\n");
    printf("Tekan Enter untuk kembali...");
    getchar(); // Menangkap Enter
    getchar(); // Menunggu input Enter
}

// Memperbarui stok obat berdasarkan nama
void updateStock(MedicineNode* head, char* name, int quantity) {
    // Mencari obat berdasarkan nama
    while (head) {
        if (strcmp(head->med.name, name) == 0) {
            // Memperbarui stok dan menampilkan pesan
            head->med.stock += quantity;
            printf("Stok diperbarui: %s, Stok Baru: %d\n", name, head->med.stock);
            return;
        }
        head = head->next;
    }
    // Jika obat tidak ditemukan
    printf("Obat %s tidak ditemukan.\n", name);
}

// --- Fungsi Min Heap ---
// Membuat Min Heap baru
MinHeap* createHeap(int capacity) {
    // Alokasi memori untuk heap
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->nodes = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Menambahkan tanggal kadaluwarsa ke Min Heap
void addToHeap(MinHeap* heap, char* expiry, char* name) {
    // Jika heap penuh, abaikan
    if (heap->size == heap->capacity) return;
    // Tambahkan node baru di akhir heap
    int index = heap->size++;
    strcpy(heap->nodes[index].expiry, expiry);
    strcpy(heap->nodes[index].name, name);
    // Perbaiki struktur heap dengan membandingkan ke atas
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (strcmp(heap->nodes[parent].expiry, heap->nodes[index].expiry) <= 0) break;
        // Tukar node dengan parent
        HeapNode temp = heap->nodes[index];
        heap->nodes[index] = heap->nodes[parent];
        heap->nodes[parent] = temp;
        index = parent;
    }
}

// Mengambil obat dengan kadaluwarsa terdekat
HeapNode getNearestExpiry(MinHeap* heap) {
    // Jika heap kosong, kembalikan node kosong
    if (heap->size == 0) {
        HeapNode empty = {"", ""};
        return empty;
    }
    // Kembalikan node di root (kadaluwarsa terdekat)
    return heap->nodes[0];
}

// --- Fungsi Queue ---
// Membuat antrian baru
Queue* createQueue() {
    // Alokasi memori untuk antrian
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Menambahkan permintaan obat ke antrian
void addRequest(Queue* queue, char* medName, int quantity) {
    // Membuat node baru untuk permintaan
    RequestObat* newNode = (RequestObat*)malloc(sizeof(RequestObat));
    strcpy(newNode->medName, medName);
    newNode->quantity = quantity;
    newNode->next = NULL;
    // Jika antrian kosong, node menjadi front dan rear
    if (!queue->rear) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // Tambahkan node di belakang antrian
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("\nPermintaan ditambahkan: %s, Jumlah: %d\n", medName, quantity);
    printf("Tekan Enter untuk kembali...");
    getchar(); 
    getchar(); // Menunggu input Enter
}

// Memproses permintaan pertama dari antrian
void processRequest(Queue* queue, MedicineNode* head) {
    // Jika antrian kosong, tampilkan pesan
    if (!queue->front) {
        printf("\nTidak ada permintaan di antrian.\n");
        printf("Tekan Enter untuk kembali...");
        getchar(); 
        getchar(); // Menunggu input Enter
        return;
    }
    // Ambil permintaan dari depan antrian
    RequestObat* temp = queue->front;
    printf("\nMemproses permintaan: %s, Jumlah: %d\n", temp->medName, temp->quantity);
    // Kurangi stok obat
    updateStock(head, temp->medName, -temp->quantity);
    // Pindah ke node berikutnya dan bebaskan memori
    queue->front = queue->front->next;
    if (!queue->front) queue->rear = NULL;
    free(temp);
    printf("Tekan Enter untuk kembali...");
    getchar(); 
    getchar(); // Menunggu input Enter
}

// Program utama
int main() {
    // Menampilkan efek loading saat program dimulai
    clearScreen();
    showLoading();
    // Inisialisasi struktur data
    MedicineNode* head = NULL; // Linked List untuk obat
    MinHeap* heap = createHeap(100); // Min Heap untuk kadaluwarsa
    Queue* queue = createQueue(); // Queue untuk permintaan
    int choice;
    do {
        // Membersihkan layar sebelum menampilkan menu
        clearScreen();
        // Menampilkan header dan menu
        displayHeader();
        printf("\nPilih Menu:\n");
        printf("1. Tambah Obat\n");
        printf("2. Lihat Semua Obat\n");
        printf("3. Lihat Obat Terdekat Kadaluwarsa\n");
        printf("4. Tambah Permintaan Obat\n");
        printf("5. Proses Permintaan Obat\n");
        printf("6. Keluar\n");
        printf("\nMasukkan pilihan: ");
        scanf("%d", &choice);
        clearScreen(); // Membersihkan layar setelah input
        switch (choice) {
            case 1: {
                // Menambahkan obat baru
                Medicine med;
                printf("Masukkan Nama Obat: ");
                scanf("%s", med.name);
                printf("Masukkan Stok: ");
                scanf("%d", &med.stock);
                printf("Masukkan Kadaluwarsa (YYYY-MM-DD): ");
                scanf("%s", med.expiry);
                addMedicine(&head, med, heap);
                break;
            }
            case 2:
                // Menampilkan semua obat
                showMedicines(head);
                break;
            case 3: {
                // Menampilkan obat dengan kadaluwarsa terdekat
                HeapNode nearest = getNearestExpiry(heap);
                if (strlen(nearest.expiry) > 0) {
                    printf("\nKadaluwarsa Terdekat:\n");
                    printf("------------------------------------\n");
                    printf("Obat: %s\nTanggal: %s\n", nearest.name, nearest.expiry);
                    printf("------------------------------------\n");
                } else {
                    printf("\nTidak ada obat di inventori.\n");
                }
                printf("Tekan Enter untuk kembali...");
                getchar(); // Menangkap Enter
                getchar(); // Menunggu input Enter
                break;
            }
            case 4: {
                // Menambahkan permintaan obat
                char name[50];
                int quantity;
                printf("Masukkan Nama Obat: ");
                scanf("%s", name);
                printf("Masukkan Jumlah: ");
                scanf("%d", &quantity);
                addRequest(queue, name, quantity);
                break;
            }
            case 5:
                // Memproses permintaan obat
                processRequest(queue, head);
                break;
            case 6:
                // Keluar dari program
                printf("\nTerima kasih telah menggunakan MediTrack!\n");
                break;
            default:
                // Menangani pilihan tidak valid
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                printf("Tekan Enter untuk kembali...");
                getchar(); // Menangkap Enter
                getchar(); // Menunggu input Enter
        }
    } while (choice != 6);

    // Membersihkan memori
    while (head) {
        MedicineNode* temp = head;
        head = head->next;
        free(temp);
    }
    free(heap->nodes);
    free(heap);
    while (queue->front) {
        RequestObat* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }
    free(queue);
    return 0;
}
