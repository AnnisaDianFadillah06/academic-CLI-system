#include <stdio.h>
#include "header.h"

void processFile(const char *filename, const char *targetNIM) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    NilaiMahasiswa nilaiMahasiswa;

    while (fscanf(file, "%s %s %s %s %d", nilaiMahasiswa.nim, nilaiMahasiswa.username, nilaiMahasiswa.kelas, nilaiMahasiswa.kodeMatkul, &nilaiMahasiswa.nilai) == 5) {
        if (strcmp(nilaiMahasiswa.nim, targetNIM) == 0) {
        printf("+-----------------------------------------------------+\n");
    	printf("         Kode Matkul: %s, Nilai: %d\n", nilaiMahasiswa.kodeMatkul, nilaiMahasiswa.nilai);
    	printf("+-----------------------------------------------------+\n\n");
        }
    }

    fclose(file);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

char* getLoggedInNimMahasiswa(Mahasiswa mahasiswas[], int numMahasiswa, char username[]) {
	int i;
    for (i = 0; i < numMahasiswa; i++) {
        if (strcmp(mahasiswas[i].username, username) == 0) {
            return mahasiswas[i].nim;
        }
    }
    return NULL; // Return NULL if not found
}

void mainMenu() {
	printf("Menu Mahasiswa\n");
    printf("1. Lihat Nilai\n");
    printf("2. Lihat Jadwal\n");
}

void optionMenu(Mahasiswa mahasiswas[], int numMahasiswa, char username[]) {
    int choice;

    do {
        printf("Option Menu\n");
        printf("1. Back to Main Menu\n");
        printf("2. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Kembali ke menu utama
                displayMahasiswaMenu(mahasiswas, numMahasiswa, username);
                break;
            case 2:
                // Logout
                printf("Logging out...\n");
                // Implementasikan logika untuk logout jika diperlukan
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 2);  // Loop hingga logout
}

// Function to display the Mahasiswa menu
void displayMahasiswaMenu(Mahasiswa mahasiswas[], int numMahasiswa, char username[]) {
    char* loggedInNIMMahasiswa = getLoggedInNimMahasiswa(mahasiswas, numMahasiswa, username);

    if (loggedInNIMMahasiswa != NULL) {
        printf("NIM Mahasiswa yang sedang login: %s\n", loggedInNIMMahasiswa);
    } else {
        printf("Mahasiswa dengan username %s tidak ditemukan.\n", username);
    };

    clearScreen();
    mainMenu();

    int choice; // Declare classChoice here in a broader scope
    printf("Enter your choice: ");
    scanf("%d", &choice);

    clearScreen();

    switch (choice) {
        case 1: {
            char* loggedInNIMMahasiswa = getLoggedInNimMahasiswa(mahasiswas, numMahasiswa, username);
            if (loggedInNIMMahasiswa != NULL) {
                const char *fileNames[] = {"nilaiAgama.txt", "nilaiDDP.txt", "nilaiIndonesia.txt", "nilaiInggris.txt", "nilaiMTK.txt", "nilaiPancasila.txt", "nilaiProyek.txt", "nilaiPTIK.txt"};
                int i;
                // Iterasi melalui file-file dan proses nilai
                for (i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); ++i) {
                    processFile(fileNames[i], loggedInNIMMahasiswa);
                    // printf("Processing file: %s\n", fileNames[i]);
                }
            } else {
                printf("Mahasiswa dengan NIM %s belum memiliki nilai.\n", username);
            }
            optionMenu(mahasiswas, numMahasiswa, username);  // Panggil fungsi optionMenu setelah selesai melihat nilai
            break;
        }
        case 2: {
            displayJadwal("jadwal.txt");
            optionMenu(mahasiswas, numMahasiswa, username);  // Panggil fungsi optionMenu setelah selesai melihat jadwal
            break;
        }
        case 3: {
        	clearScreen();
        	main();
            break;
        }
        default:
            printf("Invalid choice.\n");
    }
}

// Function to display the Pegawai TU menu

