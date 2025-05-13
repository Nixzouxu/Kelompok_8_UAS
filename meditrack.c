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

// program utama
int main() {
    MedicineNode* head = NULL;
    MinHeap* heap = createHeap(100); // Kapasitas awal heap
    int choice;

    while (1) {
        clearScreen();
        displayHeader();
        printf("\nMenu Utama:\n");
        printf("1. Tambah Obat\n");
        printf("2. Tampilkan Inventori\n");
        printf("3. Perbarui Stok\n");
        printf("4. Lihat Obat Kadaluwarsa Terdekat\n");
        printf("5. Keluar\n");
        printf("Pilih opsi (1-5): ");
        scanf("%d", &choice);
        getchar(); // Mengonsumsi newline

        switch (choice) {
            case 1: {
                Medicine med;
                printf("\n--- Tambah Obat Baru ---\n");
                printf("Nama Obat: ");
                fgets(med.name, sizeof(med.name), stdin);
                med.name[strcspn(med.name, "\n")] = 0; // Hapus newline

                printf("Stok: ");
                scanf("%d", &med.stock);
                getchar();

                printf("Tanggal Kadaluwarsa (YYYY-MM-DD): ");
                fgets(med.expiry, sizeof(med.expiry), stdin);
                med.expiry[strcspn(med.expiry, "\n")] = 0;

                addMedicine(&head, med, heap);
                break;
            }
            case 2:
                showMedicines(head);
                break;
            case 3: {
                char name[50];
                int qty;
                printf("\n--- Perbarui Stok Obat ---\n");
                printf("Nama Obat: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Jumlah Penambahan Stok: ");
                scanf("%d", &qty);
                getchar();

                updateStock(head, name, qty);
                printf("Tekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 4: {
                HeapNode soon = getNearestExpiry(heap);
                if (strcmp(soon.name, "") == 0) {
                    printf("\nTidak ada data obat dalam heap.\n");
                } else {
                    printf("\nObat dengan kadaluwarsa terdekat:\n");
                    printf("Nama: %s\n", soon.name);
                    printf("Kadaluwarsa: %s\n", soon.expiry);
                }
                printf("Tekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 5:
                printf("\nTerima kasih telah menggunakan MediTrack!\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Tekan Enter untuk coba lagi...");
                getchar();
        }
    }

    return 0;
}

