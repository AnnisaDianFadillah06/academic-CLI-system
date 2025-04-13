#pragma once
#ifndef header_h
#define header_h

// Define maximum length for username, password, and role
#define MAX_LENGTH 50
#define BARIS 12
#define KOLOM 3
#define PANJANG_KATA 50
#define MAX_DOSEN 50

// Define maximum length for username, password, and role
#define MAX_LENGTH 50
#define MAX_MATKUL 12
#define MAX_MATKUL_MHS 
// Define file names for Mahasiswa and Dosen data
#define FILE_MAHASISWA "datamahasiswa.txt"
#define FILE_DOSEN "datadosen.txt"

// Define user roles
typedef enum {
    MAHASISWA,
    PEGAWAI_TU,
    DOSEN
} UserRole;

// Structure to hold user information
typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    UserRole role;
} User;



// Structure for Mahasiswa
typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char nim[MAX_LENGTH];
    char kelas[MAX_LENGTH];
} Mahasiswa;

// Structure for Dosen
typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char kodeDosen[MAX_LENGTH];
    char kodeMatkul[MAX_LENGTH];
} Dosen;

typedef struct {
    char nim[MAX_LENGTH];
    char username[MAX_LENGTH];
    char kelas[MAX_LENGTH];
	char kodeMatkul[MAX_LENGTH];
    int nilai;
} NilaiMahasiswa;

typedef struct {
    char hari[10];       
    char kelas[5];     
    char dosen[50];
    char kodeMatkul[50];
} Jadwal;

// Function to read user data
void readUserData(User *users, int *numUsers);

// Function to get user credentials (username and password)
void getUserCredentials(char *username, char *password);

int authenticateUser(User *users, int numUsers, char *username, char *password, UserRole *userRole);

// Function to add a new user to the file with '¬' delimiter
void addUserToFile(User *user);

// Function to read Mahasiswa data
void readMahasiswaData(Mahasiswa *mahasiswa, int *numMahasiswa);

// Function to add a new Mahasiswa to the file
void addMahasiswaToFile(Mahasiswa *mahasiswa);

// Function to read Dosen data
void readDosenData(Dosen *dosen, int *numDosen);

// Function to add a new Dosen to the file
void addDosenToFile(Dosen *dosen);

// Function to display the Pegawai TU menu
void displayPegawaiTuMenu();

// Function to display the Dosen menu
//void displayDosenMenu();
//void displayDosenMenu(Dosen dosens[], int numDosen, char username[]);
void displayDosenMenu(Dosen dosens[], int numDosen, char username[], Mahasiswa mahasiswas[], int numMahasiswa, NilaiMahasiswa nilaiMahasiswas[], int numNilai);

char* getClassChoice();
void displayMahasiswaData(const char className[]);
void inputNilaiMahasiswa(Dosen dosens[], char username[], Mahasiswa mahasiswas[], int numMahasiswa, NilaiMahasiswa nilaiMahasiswas[], int *numNilai, int numDosen);
int findNilaiMahasiswaIndexByNIMAndDosen(char nim[], char username[], Dosen dosens[], int numDosen, NilaiMahasiswa nilaiMahasiswas[], int numNilai, char loggedInKodeMatkul[]);
void createNewStudentGrade(const char nim[], const char username[], const Mahasiswa mahasiswa, const char loggedInKodeMatkul[], NilaiMahasiswa nilaiMahasiswas[], int *numNilai);
void updateStudentGrade(NilaiMahasiswa *nilaiMahasiswas, int numNilai, const char nim[], const char loggedInKodeMatkul[], int newNilai);
void readNilaiMahasiswa(NilaiMahasiswa *nilaiMahasiswas, int *numNilai);
NilaiMahasiswa getNilaiMahasiswaInfo(char nim[], NilaiMahasiswa *nilaiMahasiswas, int numMahasiswa);
void saveNilaiMahasiswaToFile(NilaiMahasiswa nilaiMahasiswas[], int numNilai);
void displayMahasiswaData(const char *className);
Mahasiswa getMahasiswaInfo(char nim[], Mahasiswa *mahasiswa, int numMahasiswa);
void displayMahasiswaInfo(char nim[], Mahasiswa mahasiswas[], int numMahasiswa);
void readNilaiMahasiswaData(NilaiMahasiswa nilaiMahasiswas[], char kodeMatkul[], int *numNilai) ;

void simpanNilai(char nim[], int newNilai, char kodeMatkul[], int *numNilai, Mahasiswa mahasiswa);


void displayMahasiswaMenu(Mahasiswa mahasiswas[], int numMahasiswa, char username[]);
char* getLoggedInNimMahasiswa(Mahasiswa mahasiswas[], int numMahasiswa, char username[]);
void optionMenu(Mahasiswa mahasiswas[], int numMahasiswa, char username[]);


void generateRandomSchedule(Dosen* dosen, int numDosen, const char* namaFile);
bool isDosenAlreadyScheduled(Jadwal jadwal[3][3], int dayIndex, const char* dosen);
bool isDosenAlreadyScheduledInAllClasses(Jadwal jadwal[3][3], const char* dosen);
void displayJadwal(const char* namaFile);
#endif
