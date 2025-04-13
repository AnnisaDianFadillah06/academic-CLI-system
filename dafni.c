#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
#include <time.h>

#define MAX_LENGTH 50
#define FILE_DOSEN "datadosen.txt"

void generateRandomSchedule(Dosen* dosen, int numDosen, const char* namaFile) {
    if (numDosen == 0) {
        printf("Tidak ada data Dosen.\n");
        return;
    }

    FILE* file = fopen(namaFile, "w");
    if (file == NULL) {
        perror("Gagal membuka file");
        return;
    }

    fprintf(file, "+-----------------------------------------------------+\n");
    fprintf(file, "|                 JADWAL PERKULIAHAN                  |\n");
    fprintf(file, "+-----------------------------------------------------+");

    const char* daysOfWeek[] = { "SENIN", "SELASA", "RABU" };

    Jadwal jadwal[3][3];

    int i, k, j;
    for (i = 0; i < 3; ++i) {
        fprintf(file, "\n\n Hari : %s\n", daysOfWeek[i]);

        for (k = 0; k < 3; ++k) { 
            fprintf(file, "\n                         [%d]                          \n", k + 1);
            fprintf(file, "+-----------------+-----------------+-----------------+\n");
            fprintf(file, "|      Kelas      |      Dosen      |   Kode Matkul   |\n");
            fprintf(file, "+-----------------+-----------------+-----------------+\n");

            for (j = 0; j < 3; ++j) {
                sprintf(jadwal[i][j].kelas, "1%c", 'A' + j);

				int randomIndex;
				do {
				    randomIndex = rand() % numDosen;
				} while (isDosenAlreadyScheduled(jadwal, i, dosen[randomIndex].username) || isDosenAlreadyScheduledInAllClasses(jadwal, dosen[randomIndex].username));

                strcpy(jadwal[i][j].hari, daysOfWeek[i]);
                strcpy(jadwal[i][j].dosen, dosen[randomIndex].username);
                strcpy(jadwal[i][j].kodeMatkul, dosen[randomIndex].kodeMatkul);

                fprintf(file, "\n+-----------------+-----------------+-----------------+\n");
                fprintf(file, "         %s       |%17s|%17s|", jadwal[i][j].kelas, jadwal[i][j].dosen, jadwal[i][j].kodeMatkul);
            }

            if (k < 2) {
                fprintf(file, "\n+-----------------+-----------------+-----------------+\n");
            }
        }
    }
    fprintf(file, "\n+-----------------+-----------------+-----------------+\n");

    fclose(file);
}

bool isDosenAlreadyScheduled(Jadwal jadwal[3][3], int dayIndex, const char* dosen) {
    int i;
    for (i = 0; i < 3; ++i) {
        if (strcmp(jadwal[dayIndex][i].dosen, dosen) == 0) {
            return true;
        }
    }
    return false;
}

bool isDosenAlreadyScheduledInAllClasses(Jadwal jadwal[3][3], const char* dosen) {
    int i, j;
    for (i = 0; i < 3; ++i) {
        bool dosenScheduled = false;
        for (j = 0; j < 3; ++j) {
            if (strcmp(jadwal[i][j].dosen, dosen) == 0) {
                dosenScheduled = true;
                break;
            }
        }
        if (!dosenScheduled) {
            return false;
        }
    }
    return true;
}


void displayJadwal(const char* namaFile) {
    FILE* file = fopen(namaFile, "r");

    if (file == NULL) {
        perror("Gagal membuka file");
        return;
    }

    char line[100]; 
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void displayPegawaiTuMenu(Dosen dosens[], int numDosen) {
	clearScreen();
	
    printf("Menu Pegawai TU\n");
    printf("1. Input User\n");
    printf("2. Lihat Jadwal\n");
    printf("3. Logout\n");
        int choice; // Declare classChoice here in a broader scope
    printf("Input Pilihan Menu: ");
    scanf("%d", &choice);
    
    clearScreen();

    switch (choice) {
        case 1: {
        	newUser();
        	clearScreen();
			break;
        }
        case 2: {
			clearScreen();
			const char* namaFile = "jadwal.txt";
			displayJadwal(namaFile);
            break;
		}
		case 3: {
			clearScreen();
			main();
			break;
		}

    }
    
}
