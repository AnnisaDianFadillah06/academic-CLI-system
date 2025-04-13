#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

int main() {
	User users[MAX_LENGTH];
	Dosen dosens[MAX_LENGTH]; // Add this array to store Dosen data
	Mahasiswa mahasiswas[MAX_LENGTH];
	NilaiMahasiswa nilaiMahasiswas[MAX_LENGTH];
	int numUsers, numDosen, numMahasiswa, numNilai;
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	UserRole userRole;
    
    // Read user data from the file
    readUserData(users, &numUsers);

    // Get user credentials
    getUserCredentials(username, password);

    // Authenticate user
    int authenticatedUserIndex = authenticateUser(users, numUsers, username, password, &userRole);

    if (authenticatedUserIndex != -1) {
    	system("cls");
        // Call the appropriate menu based on user role
        switch (userRole) {
            case MAHASISWA:
            	readMahasiswaData(mahasiswas, &numMahasiswa);
                 displayMahasiswaMenu(mahasiswas, numMahasiswa, username);
                break;
            case PEGAWAI_TU:
                displayPegawaiTuMenu();
                break;
            case DOSEN:
                // Read Dosen data
                readDosenData(dosens, &numDosen);
                displayDosenMenu(dosens, numDosen, username, mahasiswas, &numMahasiswa, nilaiMahasiswas, numNilai);
                break;
        }
    } else {
        printf("Authentication failed\n");
    }

    return 0;
}

