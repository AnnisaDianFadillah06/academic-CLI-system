#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"
// Define maximum length for username, password, and role
#define MAX_LENGTH 50
// Define file names for Mahasiswa and Dosen data
#define FILE_MAHASISWA "datamahasiswa.txt"
#define FILE_DOSEN "datadosen.txt"
#define FILE_NILAI "nilaimahasiswa.txt"


// Function to read user data
void readUserData(User *users, int *numUsers) {
    FILE *file = fopen("fileuser.txt", "r");

    if (file == NULL) {
        // File doesn't exist, create it
        file = fopen("fileuser.txt", "w");
        if (file == NULL) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }
        fclose(file);

        // Open the file again for reading
        file = fopen("fileuser.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("No user data found. Create a new user.\n");

        // Add a new user to the file
        User newUser;
        printf("New User Username: ");
        scanf("%s", newUser.username);
        printf("New User Password: ");
        scanf("%s", newUser.password);
        printf("New User Role (0 for Mahasiswa, 1 for Pegawai TU, 2 for Dosen): ");
        scanf("%d", &newUser.role);

        // Add the new user to the file
        FILE *newFile = fopen("fileuser.txt", "a");
        if (newFile == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        fprintf(newFile, "%s¬%s¬%d\n", newUser.username, newUser.password, newUser.role);

        fclose(newFile);
    } else {
        // File is not empty, read user data
        fseek(file, 0, SEEK_SET);

        *numUsers = 0;
        char line[MAX_LENGTH * 3 + 3]; // Allow for maximum length of username, password, and role, plus delimiters and newline
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%49[^¬]¬%49[^¬]¬%d", users[*numUsers].username, users[*numUsers].password, &users[*numUsers].role) == 3) {
                (*numUsers)++;
            }
        }
    }

    fclose(file);
}

// Function to get user credentials (username and password)
void getUserCredentials(char *username, char *password) {
    // Get user input for username and password
    printf("Username: ");
    scanf("%s", username);

    // Note: Read the password as a string
    printf("Password: ");
    scanf("%s", password);
}

// AuthenticateUser function to return the index of authenticated user
int authenticateUser(User *users, int numUsers, char *username, char *password, UserRole *userRole) {
    int i;
    for (i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            *userRole = users[i].role;
            return i; // Return the index of authenticated user
        }
    }
    return -1; // Authentication failed, return -1
}

// Function to add a new user to the file with '|' delimiter
void addUserToFile(User *user) {
    FILE *file = fopen("fileuser.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s¬%s¬%d\n", user->username, user->password, user->role);

    fclose(file);
}

void readMahasiswaData(Mahasiswa *mahasiswa, int *numMahasiswa) {
    FILE *file = fopen(FILE_MAHASISWA, "r");

    if (file == NULL) {
        // File doesn't exist, create it
        file = fopen(FILE_MAHASISWA, "w");
        if (file == NULL) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }
        fclose(file);

        // Open the file again for reading
        file = fopen(FILE_MAHASISWA, "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) != 0) {
        // File is not empty, read Mahasiswa data
        fseek(file, 0, SEEK_SET);

        *numMahasiswa = 0;
        char line[MAX_LENGTH * 4 + 3];  // Allow for maximum length of username, password, nim, kelas, plus delimiters and newline
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%49[^¬]¬%49[^¬]¬%49[^¬]¬%49[^¬]", mahasiswa[*numMahasiswa].username, mahasiswa[*numMahasiswa].password, mahasiswa[*numMahasiswa].nim, mahasiswa[*numMahasiswa].kelas) == 4) {
                (*numMahasiswa)++;
            }
        }
    }

    fclose(file);
}


// Function to get the class choice from the user
char* getClassChoice() {
    int choice;
    char* className = NULL;

    do {
        printf("Choose your class:\n");
        printf("1. 1A-JTK\n");
        printf("2. 1B-JTK\n");
        printf("3. 1C-JTK\n");
        printf("Enter the number of your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                className = strdup("1A-JTK");
                break;
            case 2:
                className = strdup("1B-JTK");
                break;
            case 3:
                className = strdup("1C-JTK");
                break;
            default:
                printf("Invalid choice. Please choose again.\n");
        }
    } while (className == NULL); // Continue the loop until a valid choice is entered

    return className;
}

// Function to add a new Mahasiswa to the file
void addMahasiswaToFile(Mahasiswa *mahasiswa) {
    FILE *file = fopen(FILE_MAHASISWA, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s¬%s¬%s¬%s\n", mahasiswa->username, mahasiswa->password, mahasiswa->nim, mahasiswa->kelas);

    fclose(file);
}

// Function to read Dosen data
void readDosenData(Dosen *dosen, int *numDosen) {
    FILE *file = fopen(FILE_DOSEN, "r");

    if (file == NULL) {
        // File doesn't exist, create it
        file = fopen(FILE_DOSEN, "w");
        if (file == NULL) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }
        fclose(file);

        // Open the file again for reading
        file = fopen(FILE_DOSEN, "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) != 0) {
        // File is not empty, read Dosen data
        fseek(file, 0, SEEK_SET);

        *numDosen = 0;
        char line[MAX_LENGTH * 4 + 3]; // Allow for maximum length of username, password, kodeDosen, kodeMatkul, plus delimiters and newline
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%49[^¬]¬%49[^¬]¬%49[^¬]¬%49[^¬]", dosen[*numDosen].username, dosen[*numDosen].password, dosen[*numDosen].kodeDosen, dosen[*numDosen].kodeMatkul) == 4) {
                (*numDosen)++;
            }
        }
    }

    fclose(file);
}

// Function to add a new Dosen to the file
void addDosenToFile(Dosen *dosen) {
    FILE *file = fopen(FILE_DOSEN, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s¬%s¬%s¬%s\n", dosen->username, dosen->password, dosen->kodeDosen, dosen->kodeMatkul);

    fclose(file);
}

// Function to display the Mahasiswa menu
void displayMahasiswaMenu() {
    printf("Menu Mahasiswa\n");
    // Add logic specific to the Mahasiswa menu if needed
}

// Function to display the Pegawai TU menu
void displayPegawaiTuMenu() {
    printf("Menu Pegawai TU\n");

    // Allow inputting a new user
    User newUser;
    printf("New User Role (0 for Mahasiswa, 1 for Pegawai TU, 2 for Dosen): ");
    scanf("%d", &newUser.role);

    if (newUser.role == MAHASISWA) {
        // If the new user is a Mahasiswa, add to Mahasiswa data
        Mahasiswa newMahasiswa;

		// Input username and password for newUser
		printf("New User Username: ");
		scanf("%s", newUser.username);
		
		// Consume the newline character left in the buffer
		getchar();
		
		// Note: Read the password as a string
		printf("New User Password: ");
		scanf("%s", newUser.password);
		
		// Consume the newline character left in the buffer
		getchar();


        // Copy username and password to newMahasiswa
        strcpy(newMahasiswa.username, newUser.username);
        strcpy(newMahasiswa.password, newUser.password);

        // Input the rest of the Mahasiswa data
        printf("NIM: ");
        scanf("%s", newMahasiswa.nim);
        getchar();


        // Get the class choice from the user
        strcpy(newMahasiswa.kelas, getClassChoice());

        // Add both newUser and newMahasiswa to their respective files
        addMahasiswaToFile(&newMahasiswa);
        addUserToFile(&newUser);
    } else if (newUser.role == DOSEN) {
        // If the new user is a Mahasiswa, add to Mahasiswa data
        Dosen newDosen;

        // Input username and password for newUser
        printf("New User Username: ");
        scanf("%s", newUser.username);
        // Note: Read the password as a string
        printf("New User Password: ");
        scanf("%s", newUser.password);

        // Copy username and password to newMahasiswa
        strcpy(newDosen.username, newUser.username);
        strcpy(newDosen.password, newUser.password);
        // If the new user is a Dosen, add to Dosen data
        printf("Kode Dosen: ");
        scanf("%s", newDosen.kodeDosen);
        printf("Kode Matkul: ");
        scanf("%s", newDosen.kodeMatkul);
        addDosenToFile(&newDosen);
        addUserToFile(&newUser);
    } else {
        // For other roles, add to the common user data
        printf("New User Username: ");
        scanf("%s", newUser.username);
        // Note: Read the password as a string
        printf("New User Password: ");
        scanf("%s", newUser.password);
        addUserToFile(&newUser);
    }
}

void trimWhitespace(char *str) {
    int start = 0, end = strlen(str) - 1;

    // Find the start of non-whitespace characters
    while (isspace((unsigned char)str[start]))
        start++;

    // Find the end of non-whitespace characters
    while ((end >= start) && isspace((unsigned char)str[end]))
        end--;

    // Shift the characters to the beginning of the string
    int shift = 0;
    while (start + shift <= end)
        str[shift] = str[start + shift++];

    // Null-terminate the trimmed string
    str[shift] = '\0';
}

void displayMahasiswaData(const char *className) {
    Mahasiswa mahasiswa[MAX_LENGTH];
    int numMahasiswa, i;

    readMahasiswaData(mahasiswa, &numMahasiswa);

    printf("Mahasiswa data for class %s:\n", className);
    printf("%-16s%-16s\n", "NIM", "Nama");

    int found = 0;

    for (i = 0; i < numMahasiswa; i++) {
        char trimmedKelas[MAX_LENGTH];
        strcpy(trimmedKelas, mahasiswa[i].kelas);
        trimWhitespace(trimmedKelas);

        if (strcmp(trimmedKelas, className) == 0) {
            printf("%-16s%-16s\n", mahasiswa[i].nim, mahasiswa[i].username);
            found = 1;
        }
    }

    if (!found) {
        printf("No data found for class %s\n", className);
    }
}

Mahasiswa getMahasiswaInfo(char nim[], Mahasiswa *mahasiswa, int numMahasiswa) {
	readMahasiswaData(mahasiswa, &numMahasiswa);
    // Search for Mahasiswa based on NIM
    int i;
    for (i = 0; i < numMahasiswa; i++) {
        if (strcmp(mahasiswa[i].nim, nim) == 0) {
            return mahasiswa[i];
        }
    }

    // If Mahasiswa with the given NIM is not found, initialize an empty Mahasiswa structure
    Mahasiswa notFoundMahasiswa;
    strcpy(notFoundMahasiswa.username, "");
    strcpy(notFoundMahasiswa.kelas, "");

    return notFoundMahasiswa;
}

void displayMahasiswaInfo(char nim[], Mahasiswa mahasiswas[], int numMahasiswa) {

    Mahasiswa foundMahasiswa = getMahasiswaInfo(nim, mahasiswas, numMahasiswa);

    // Display Mahasiswa information
    if (strcmp(foundMahasiswa.nim, "") != 0) {
        printf("Found Mahasiswa:\n");
        printf("Nama: %s\n", foundMahasiswa.username);
        printf("Kelas: %s\n", foundMahasiswa.kelas);
    } else {
        printf("Mahasiswa with NIM %s not found.\n", nim);
    }
}

int findMahasiswaIndexByNIM(char nim[], Mahasiswa mahasiswas[], int numMahasiswa) {
	readMahasiswaData(mahasiswas, &numMahasiswa);
	int i;
    for (i = 0; i < numMahasiswa; i++) {
        if (strcmp(mahasiswas[i].nim, nim) == 0) {
            return i;  // Found the Mahasiswa with the given NIM
        }
    }
    return -1;  // Mahasiswa not found
}

int findNilaiMahasiswaIndexByNIM(Dosen dosens[], char username[], char nim[], NilaiMahasiswa nilaiMahasiswas[], int numMahasiswa) {
	char loggedInKodeMatkul[MAX_LENGTH];
	
    int j, numDosen, i;
	
    // Mendapatkan kodeMatkul dari Dosen yang sedang login
    for (j = 0; j < numDosen; j++) {
        if (strcmp(dosens[j].username, username) == 0) {
            strcpy(loggedInKodeMatkul, dosens[j].kodeMatkul);
        }
    }
    sanitizeString(loggedInKodeMatkul);
    readNilaiMahasiswaData(nilaiMahasiswas, loggedInKodeMatkul, &numMahasiswa);

    for (i = 0; i < numMahasiswa; i++) {
        if (strcmp(nilaiMahasiswas[i].nim, nim) == 0) {
            return i;  // Found the Mahasiswa with the given NIM
        }
    }

    return -1;  // Mahasiswa not found
}

void sanitizeString(char *str) {
    size_t len = strlen(str);

    // Remove trailing newline characters
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }

    // Replace invalid characters
    while (*str) {
        if (*str == '/' || *str == '\\' || *str == ':' || *str == '.') {
            *str = '_';
        }
        str++;
    }
}

void inputNilaiMahasiswa(Dosen dosens[], char username[], Mahasiswa mahasiswas[], int numMahasiswa, NilaiMahasiswa nilaiMahasiswas[], int *numNilai, int numDosen) {
    char nim[MAX_LENGTH];
    char loggedInKodeMatkul[MAX_LENGTH];
    int j, nilai, i;
	
    // Mendapatkan kodeMatkul dari Dosen yang sedang login
    for (j = 0; j < numDosen; j++) {
        if (strcmp(dosens[j].username, username) == 0) {
            strcpy(loggedInKodeMatkul, dosens[j].kodeMatkul);
             // Sanitize kodeMatkul (remove invalid characters)
            for (i = 0; loggedInKodeMatkul[i] != '\0'; i++) {
                if (loggedInKodeMatkul[i] == '/' || loggedInKodeMatkul[i] == '\\' || loggedInKodeMatkul[i] == ':' || loggedInKodeMatkul[i] == '.') {
                    loggedInKodeMatkul[i] = '_';  // Replace invalid characters with underscores or another valid character
                }
            }
            break; // Keluar dari loop setelah Dosen ditemukan
        }
    }

    printf("Input NIM: ");
    scanf("%s", nim);
    displayMahasiswaInfo(nim, mahasiswas, numMahasiswa);

    // Setelah mendapatkan kodeMatkul, Anda dapat menggunakannya dalam pemrosesan lebih lanjut
    sprintf(nilaiMahasiswas[*numNilai].kodeMatkul, "%s", loggedInKodeMatkul);

     for (i = 0; i < numMahasiswa; i++) {
        if (strcmp(mahasiswas[i].nim, nim) == 0) {
            // Directly copy the Mahasiswa information without setting it again
            strcpy(nilaiMahasiswas[*numNilai].kelas, mahasiswas[i].kelas);
            strcpy(nilaiMahasiswas[*numNilai].username, mahasiswas[i].username);

            // Panggil fungsi untuk mengecek dan menyimpan nilai ke file
            
            
            // Update the nilai field
            printf("Input Nilai: ");
            scanf("%d", &nilai);
            nilaiMahasiswas[*numNilai].nilai = nilai;
           simpanNilai(dosens, username, nim, nilaiMahasiswas, loggedInKodeMatkul, numNilai, mahasiswas[i]);


            break; // Keluar dari loop setelah Mahasiswa ditemukan
        }
    }

    // Perbarui jumlah nilai
    (*numNilai)++;
}
void readNilaiMahasiswaData(NilaiMahasiswa nilaiMahasiswas[], char kodeMatkul[], int *numNilai) {
	FILE *file;
    char namaFile[MAX_LENGTH];
    sanitizeString(kodeMatkul);
    
    // Membuat nama file berdasarkan kodeMatkul
    sprintf(namaFile, "nilai%s.txt", kodeMatkul);

    printf("Trying to open file: %s\n", namaFile);

    file = fopen(namaFile, "r");  // Open in append mode
    if (file == NULL) {
        // Jika file belum ada, buat file baru untuk ditulis
        file = fopen(namaFile, "w");
        if (file == NULL) {
            // Gagal membuka atau membuat file, tampilkan pesan kesalahan
            perror("Error opening/creating file");
            exit(EXIT_FAILURE);
        }
    }

    *numNilai = 0;  // Initialize the count of NilaiMahasiswa

    // Assuming the file format is: nim username kelas kodeMatkul nilai
    while (fscanf(file, "%s %s %s %s %d", nilaiMahasiswas[*numNilai].nim,
                                     nilaiMahasiswas[*numNilai].username,
                                     nilaiMahasiswas[*numNilai].kelas,
                                     nilaiMahasiswas[*numNilai].kodeMatkul,
                                     &nilaiMahasiswas[*numNilai].nilai) == 5) {
        (*numNilai)++;  // Increment the count of NilaiMahasiswa
    }

    fclose(file);
}
void simpanNilai(Dosen dosens[], char username[], char nim[], NilaiMahasiswa nilai[], char kodeMatkul[], int *numNilai, Mahasiswa mahasiswa) {
    FILE *file;
    char namaFile[MAX_LENGTH];
    sanitizeString(kodeMatkul);
    int numMahasiswa;
    
    // Membuat nama file berdasarkan kodeMatkul
    sprintf(namaFile, "nilai%s.txt", kodeMatkul);

    printf("Trying to open file: %s\n", namaFile);

    file = fopen(namaFile, "a+");  // Open in append mode
    if (file == NULL) {
        // Jika file belum ada, buat file baru untuk ditulis
        file = fopen(namaFile, "w");
        if (file == NULL) {
            // Gagal membuka atau membuat file, tampilkan pesan kesalahan
            perror("Error opening/creating file");
            exit(EXIT_FAILURE);
        }
    }

    int mahasiswaIndex = findNilaiMahasiswaIndexByNIM(dosens, username, nim, nilai, numMahasiswa);


    if (mahasiswaIndex != -1) {
            // Jika NIM ditemukan, update nilai
        fseek(file, 0, SEEK_SET); // Move to the beginning of the file
        int i;
        for (i = 0; i < *numNilai; i++) {
            if (strcmp(nilai[i].nim, nim) == 0) {
                fprintf(file, "%s %s %s %s %d\n", nim, mahasiswa.username, mahasiswa.kelas, kodeMatkul, nilai[i].nilai);
            } else {
                // Preserve other records
                fprintf(file, "%s %s %s %s %d\n",
                        nilai[i].nim, nilai[i].username, nilai[i].kelas,
                        nilai[i].kodeMatkul, nilai[i].nilai);
            }
        }
    }else{
        fseek(file, 0, SEEK_END);
        sanitizeString(mahasiswa.kelas);
        fprintf(file, "%s %s %s %s %d\n", nim, mahasiswa.username, mahasiswa.kelas, kodeMatkul, nilai);
    }

    // Menutup file
    fclose(file);

    printf("Nilai berhasil disimpan.\n");
}

void displayDosenMenu(Dosen dosens[], int numDosen, char username[], Mahasiswa mahasiswas[], int numMahasiswa, NilaiMahasiswa nilaiMahasiswas[], int numNilai) {

    int j;

    // Rest of your code for checking Dosen data
    for (j = 0; j < numDosen; j++) {
        if (strcmp(dosens[j].username, username) == 0) {
            // Now you have the kodeMatkul for the logged-in Dosen
            printf("Logged in as Dosen with kodeMatkul: %s\n", dosens[j].kodeMatkul);
            break;
        }
    }

    char className[MAX_LENGTH];
    printf("Menu Dosen\n");
    printf("1. Input Nilai Mahasiswa\n");
    printf("2. Lihat Jadwal Dosen\n");
    // Add other menu options as needed
    int choice; // Declare classChoice here in a broader scope
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        // Get the class choice from the user using getClassChoice function
        char* classChoice = getClassChoice();

        // Set className based on classChoice
        if (classChoice != NULL) {
            printf("Selected class: %s\n", classChoice); // For debugging
            strcpy(className, classChoice);
            free(classChoice); // Free the allocated memory
            displayMahasiswaData(className);
            NilaiMahasiswa nilaiMahasiswas[MAX_LENGTH];
    		int numNilai = 0;
            inputNilaiMahasiswa(dosens, username, mahasiswas, numMahasiswa, nilaiMahasiswas, &numNilai, numDosen);
        }
        else {
            generateRandomSchedule(dosens, numDosen);
        }
        break;
    }
    }
}  


