# Sisop-3-2024-MH-IT19
# Laporan Resmi Sistem Operasi Modul 1 Kelompok IT19

Anggota Kelompok IT19 : 
1. Riskiyatul Nur Oktarani (5027231013)
2. Aswalia Novitriasari (5027231012)
3. Benjamin Khawarizmi Habibi (5027231078)

# SOAL SHIFT NOMOR 2
Max Verstappen 🏎️ seorang pembalap F1 dan programer memiliki seorang adik bernama Min Verstappen (masih SD) sedang menghadapi tahap paling kelam dalam kehidupan yaitu perkalian matematika, Min meminta bantuan Max untuk membuat kalkulator perkalian sederhana (satu sampai sembilan). Sembari Max nguli dia menyuruh Min untuk belajar perkalian dari web (referensi) agar tidak bergantung pada kalkulator.
(Wajib menerapkan konsep pipes dan fork seperti yang dijelaskan di modul Sisop. Gunakan 2 pipes dengan diagram seperti di modul 3).

a. Sesuai request dari adiknya Max ingin nama programnya dudududu.c. Sebelum program parent process dan child process, ada input dari user berupa 2 string. Contoh input: tiga tujuh. 

b. Pada parent process, program akan mengubah input menjadi angka dan melakukan perkalian dari angka yang telah diubah. Contoh: tiga tujuh menjadi 21. 

c. Pada child process, program akan mengubah hasil angka yang telah diperoleh dari parent process menjadi kalimat. Contoh: `21` menjadi “dua puluh satu”.

d. Max ingin membuat program kalkulator dapat melakukan penjumlahan, pengurangan, dan pembagian, maka pada program buatlah argumen untuk menjalankan program : 

perkalian	: ./kalkulator -kali

penjumlahan	: ./kalkulator -tambah

pengurangan	: ./kalkulator -kurang

pembagian	: ./kalkulator -bagi

Beberapa hari kemudian karena Max terpaksa keluar dari Australian Grand Prix 2024 membuat Max tidak bersemangat untuk melanjutkan programnya sehingga kalkulator yang dibuatnya cuma menampilkan hasil positif jika bernilai negatif maka program akan print “ERROR” serta cuma menampilkan bilangan bulat jika ada bilangan desimal maka dibulatkan ke bawah.

e. Setelah diberi semangat, Max pun melanjutkan programnya dia ingin (pada child process) kalimat akan di print dengan contoh format : 
perkalian	: “hasil perkalian tiga dan tujuh adalah dua puluh satu.”

penjumlahan	: “hasil penjumlahan tiga dan tujuh adalah sepuluh.”

pengurangan	: “hasil pengurangan tujuh dan tiga adalah empat.”

pembagian	: “hasil pembagian tujuh dan tiga adalah dua.”

Max ingin hasil dari setiap perhitungan dicatat dalam sebuah log yang diberi nama histori.log. Pada parent process, lakukan pembuatan file log berdasarkan data yang dikirim dari child process. 

Format: [date] [type] [message]

Type: KALI, TAMBAH, KURANG, BAGI

Ex:

[10/03/24 00:29:47] [KALI] tujuh kali enam sama dengan empat puluh dua.

[10/03/24 00:30:00] [TAMBAH] sembilan tambah sepuluh sama dengan sembilan belas.

[10/03/24 00:30:12] [KURANG] ERROR pada pengurangan.

# PENYELESAIAN

```
int stringkeint(char *str) {
    if (strcmp(str, "satu") == 0) return 1;
    else if (strcmp(str, "dua") == 0) return 2;
    else if (strcmp(str, "tiga") == 0) return 3;
    else if (strcmp(str, "empat") == 0) return 4;
    else if (strcmp(str, "lima") == 0) return 5;
    else if (strcmp(str, "enam") == 0) return 6;
    else if (strcmp(str, "tujuh") == 0) return 7;
    else if (strcmp(str, "delapan") == 0) return 8;
    else if (strcmp(str, "sembilan") == 0) return 9;
    else return -1;
}


void ubahkata(int num, char *kata) { //untuk mengubah angka menjadi huruf
    char *ones[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    char *teens[] = {"sepuluh", "sebelas", "dua belas", "tiga belas", "empat belas", "lima belas", "enam belas", "tujuh belas", "delapan belas", "sembilan belas"};
    char *tens[] = {"", "dua puluh", "tiga puluh", "empat puluh", "lima puluh", "enam puluh", "tujuh puluh", "delapan puluh", "sembilan puluh"};

    if (num >= 1 && num <= 9) {
        strcpy(kata, ones[num]);
    } else if (num >= 10 && num <= 19) {
	strcpy(kata, teens[num - 10]);
    } else if (num >= 20 && num <= 99) {
        int ten = num / 10;
        int one = num % 10;
        if (one == 0) {
            strcpy(kata, tens[ten]);
        } else {
            sprintf(kata, "%s %s", tens[ten], ones[one]);
        }
    }
}
```
kode diatas adalah kode untuk mengubah angka menjadi sebuah kata 

```
int pipe_parent_to_child[2];
    int pipe_child_to_parent[2];

    if (pipe(pipe_parent_to_child) == -1 || pipe(pipe_child_to_parent) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        close(pipe_parent_to_child[0]);
        close(pipe_child_to_parent[1]);

        char input[20];
        printf("Masukkan dua angka (dalam kata): ");
        fgets(input, sizeof(input), stdin);
        strtok(input, "\n");

        char *token = strtok(input, " ");
        int num1 = stringkeint(token);
	token = strtok(NULL, " ");
        int num2 = stringkeint(token);

        int result;
        if (strcmp(argv[1], "-kali") == 0) {
            result = num1 * num2;
        } else if (strcmp(argv[1], "-tambah") == 0) {
            result = num1 + num2;
        } else if (strcmp(argv[1], "-kurang") == 0) {
            result = num1 - num2;
            if (result < 0) {
                printf("ERROR pada pengurangan.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            if (num2 == 0) {
                printf("ERROR: Pembagian dengan nol\n");
                exit(EXIT_FAILURE);
            }
            result = num1 / num2;
            if (result < 0) {
                printf("ERROR pada pembagian.\n");
                exit(EXIT_FAILURE);
            }
        }

        write(pipe_parent_to_child[1], &result, sizeof(result));

        char message[200];
        read(pipe_child_to_parent[0], message, sizeof(message));
        printf("%s\n", message);

        close(pipe_parent_to_child[1]);
        close(pipe_child_to_parent[0]);
```
kode diatas untuk proses parents

```
close(pipe_parent_to_child[1]);
        close(pipe_child_to_parent[0]);

        int result;
        read(pipe_parent_to_child[0], &result, sizeof(result));

        char kata[100];
        ubahkata(result, kata);

        char message[150];
        if (strcmp(argv[1], "-kali") == 0) {
            sprintf(message, "hasil perkalian %d dan %d adalah %s.", num1, num2, kata);
        } else if (strcmp(argv[1], "-tambah") == 0) {
            sprintf(message, "hasil penjumlahan %d dan %d adalah %s.", num1, num2, kata);
        } else if (strcmp(argv[1], "-kurang") == 0) {
            sprintf(message, "hasil pengurangan %d dan %d adalah %s.", num1, num2, kata);
        } else {
            sprintf(message, "hasil pembagian %d dan %d adalah %s.", num1, num2, kata);
        }

        write(pipe_child_to_parent[1], message, sizeof(message));
        close(pipe_parent_to_child[0]);
        close(pipe_child_to_parent[1]);

        exit(EXIT_SUCCESS);
    }
```
kode diatas untuk proses child

# REVISI

untuk revisi nya saya menambahkan kode berikut pada child proses

```
char input[20];
        printf("Masukkan dua angka (dalam kata): ");
        fgets(input, sizeof(input), stdin);
        strtok(input, "\n");

        char *token = strtok(input, " ");
        int num1 = stringkeint(token);
        token = strtok(NULL, " ");
 int num2 = stringkeint(token);

```

berikut kode child yang sudah direvisi, awalnya string awal yang dimasukkan tidak berubah menjadi angka 

# Dokumentasi

untuk hasil tambah

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/7bbc55e3-ea39-434b-a52d-c0324bc97215)

untuk hasil kali

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/9a036fbd-9501-41a6-aac5-331869e99da6)

untuk hasil kurang

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/13723bde-204c-4900-bf52-ea4759476f3a)

untuk hasil kurang jika angka pertama yang dimasukin lebih kecil

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/bb9db322-517d-46d0-ae3d-99c93b9a5fa0)

untuk hasil bagi

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/7d1e093f-befe-4bb8-b9c5-9a8c99bb37fb)

untuk hasil bagi jika hasil tidak pas maka akan dibulatkan ke angka didepannya

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/0fb0b6b8-46f3-4249-bb3e-3edce43bf19a)

untuk hasil bagi jika angka pertama yang dimasukin lebih kecil

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/173e85f1-15ab-42c6-8d06-a7fb48d892bb)

berikut kode untuk membuat histori log

```
// Log the result
        FILE *filelog = fopen("histori.log", "a");
        if (filelog != NULL) {
            char pesanlog[100];
            time_t now = time(NULL);
            struct tm *tm_info = localtime(&now);
            strftime(pesanlog, sizeof(pesanlog), "[%d/%m/%y %H:%M:%S]", tm_info);
            fprintf(filelog, "%s [%s] %s\n", pesanlog, argv[1] + 1, message);
            fclose(filelog);
        } else {
            perror("fopen");
        }
```
berikut adalah isi dari histori log

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/e147c7cb-0aaf-4bfb-a1a3-c681b6a4f4b0)

dibawah ini adalah hasil jika tidak ditambah kali kurang bagi atau tambah

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/a2b8ab07-c390-4150-9391-2172c155b1bb)

# SOAL 3
Shall Leglerg🥶 dan Carloss Signs 😎 adalah seorang pembalap F1 untuk tim Ferrari 🥵. Mobil F1 memiliki banyak pengaturan, seperti penghematan ERS, Fuel, Tire Wear dan lainnya. Pada minggu ini ada race di sirkuit Silverstone. Malangnya, seluruh tim Ferrari diracun oleh Super Max Max pada hari sabtu sehingga seluruh kru tim Ferrari tidak bisa membantu Shall Leglerg🥶 dan Carloss Signs 😎 dalam race. Namun, kru Ferrari telah menyiapkan program yang bisa membantu mereka dalam menyelesaikan race secara optimal. Program yang dibuat bisa mengatur pengaturan - pengaturan dalam mobil F1 yang digunakan dalam balapan. Programnya ber ketentuan sebagai berikut:
Pada program actions.c, program akan berisi function function yang bisa di call oleh paddock.c
Action berisikan sebagai berikut:
Gap [Jarak dengan driver di depan (float)]: Jika Jarak antara Driver dengan Musuh di depan adalah < 3.5s maka return Gogogo, jika jarak > 3.5s dan 10s return Push, dan jika jarak > 10s maka return Stay out of trouble.
Fuel [Sisa Bensin% (string/int/float)]: Jika bensin lebih dari 80% maka return Push Push Push, jika bensin di antara 50% dan 80% maka return You can go, dan jika bensin kurang dari 50% return Conserve Fuel.
Tire [Sisa Ban (int)]: Jika pemakaian ban lebih dari 80 maka return Go Push Go Push, jika pemakaian ban diantara 50 dan 80 return Good Tire Wear, jika pemakaian di antara 30 dan 50 return Conserve Your Tire, dan jika pemakaian ban kurang dari 30 maka return Box Box Box.
Tire Change [Tipe ban saat ini (string)]: Jika tipe ban adalah Soft return Mediums Ready, dan jika tipe ban Medium return Box for Softs.

		Contoh:
		[Driver] : [Fuel] [55%]
		[Paddock]: [You can go]

Pada paddock.c program berjalan secara daemon di background, bisa terhubung dengan driver.c melalui socket RPC.
Program paddock.c dapat call function yang berada di dalam actions.c.
Program paddock.c tidak keluar/terminate saat terjadi error dan akan log semua percakapan antara paddock.c dan driver.c di dalam file race.log

Format log:
[Source] [DD/MM/YY hh:mm:ss]: [Command] [Additional-info]
ex :
[Driver] [07/04/2024 08:34:50]: [Fuel] [55%]
[Paddock] [07/04/2024 08:34:51]: [Fuel] [You can go]

Program driver.c bisa terhubung dengan paddock.c dan bisa mengirimkan pesan dan menerima pesan serta menampilan pesan tersebut dari paddock.c sesuai dengan perintah atau function call yang diberikan.
Jika bisa digunakan antar device/os (non local) akan diberi nilai tambahan.
untuk mengaktifkan RPC call dari driver.c, bisa digunakan in-program CLI atau Argv (bebas) yang penting bisa send command seperti poin B dan menampilkan balasan dari paddock.c
		
		ex:
Argv: 
./driver -c Fuel -i 55% 
in-program CLI:
Command: Fuel
Info: 55%

# SOAL 4
Lewis Hamilton 🏎 seorang wibu akut dan sering melewatkan beberapa episode yang karena sibuk menjadi asisten. Maka dari itu dia membuat list anime yang sedang ongoing (biar tidak lupa) dan yang completed (anime lama tapi pengen ditonton aja). Tapi setelah Lewis pikir-pikir malah kepikiran untuk membuat list anime. Jadi dia membuat file (harap diunduh) dan ingin menggunakan socket yang baru saja dipelajarinya untuk melakukan CRUD pada list animenya. 
Client dan server terhubung melalui socket. 
client.c di dalam folder client dan server.c di dalam folder server
Client berfungsi sebagai pengirim pesan dan dapat menerima pesan dari server.
Server berfungsi sebagai penerima pesan dari client dan hanya menampilkan pesan perintah client saja.  
Server digunakan untuk membaca myanimelist.csv. Dimana terjadi pengiriman data antara client ke server dan server ke client.
Menampilkan seluruh judul
Menampilkan judul berdasarkan genre
Menampilkan judul berdasarkan hari
Menampilkan status berdasarkan berdasarkan judul
Menambahkan anime ke dalam file myanimelist.csv
Melakukan edit anime berdasarkan judul
Melakukan delete berdasarkan judul
Selain command yang diberikan akan menampilkan tulisan “Invalid Command”
Karena Lewis juga ingin track anime yang ditambah, diubah, dan dihapus. Maka dia membuat server dapat mencatat anime yang dihapus dalam sebuah log yang diberi nama change.log.
Format: [date] [type] [massage]
Type: ADD, EDIT, DEL
Ex:
[29/03/24] [ADD] Kanokari ditambahkan.
[29/03/24] [EDIT] Kamis,Comedy,Kanokari,completed diubah menjadi Jumat,Action,Naruto,completed.
[29/03/24] [DEL] Naruto berhasil dihapus.

Koneksi antara client dan server tidak akan terputus jika ada kesalahan input dari client, cuma terputus jika user mengirim pesan “exit”. Program exit dilakukan pada sisi client

# PENYELESAIAN
- client.c
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 50535
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char message_buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Main loop to continuously send and receive messages until "exit" command
    while (1) {
        printf("Enter message: ");
        fgets(message_buffer, BUFFER_SIZE, stdin);

        // Send message to server
        send(client_socket, message_buffer, strlen(message_buffer), 0);

        // Exit if message is "exit"
        if (strcmp(message_buffer, "exit\n") == 0) {
            printf("Exiting...\n");
            break;
        }

        // Receive response from server
        memset(message_buffer, 0, sizeof(message_buffer));
        read(client_socket, message_buffer, BUFFER_SIZE);
        printf("Server response: %s\n", message_buffer);
    }

    // Close client socket
    close(client_socket);
    return 0;
}
```
server.c 
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <curl/curl.h>

#define PORT 50535
#define BUFFER_SIZE 1024
#define LOG_FILE "change.log"

// Function to download file using libcurl
int download_file(const char *url, const char *filename) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Failed to perform request: %s\n", curl_easy_strerror(res));
            fclose(fp);
            curl_easy_cleanup(curl);
            return 0;
        }
        fclose(fp);
        curl_easy_cleanup(curl);
        return 1;
    }
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread;

    // Read client message
    valread = read(client_socket, buffer, BUFFER_SIZE);
    printf("Client message: %s\n", buffer);
    fflush(stdout); // Force writing output to terminal

    // Process client message
    if (strcmp(buffer, "exit\n") == 0) {
        printf("Closing connection with client\n");
        close(client_socket);
        return;
    } else if (strcmp(buffer, "download\n") == 0) {
        // Download file using libcurl
        char *url = "https://drive.google.com/uc?export=download&id=10p_kzuOgaFY3WT6FVPJIXFbkej2s9f50";
        char *filename = "myanimelist.csv";
        int success = download_file(url, filename);
        if (success) {
            printf("File downloaded successfully\n");
            // Respond to client
            char *response = "File downloaded successfully";
            send(client_socket, response, strlen(response), 0);
        } else {
            fprintf(stderr, "Failed to download file\n");
            // Respond to client
            char *response = "Failed to download file";
            send(client_socket, response, strlen(response), 0);
        }
    } else {
        // Respond to client
        char *response = "Message received";
        send(client_socket, response, strlen(response), 0);
    }

    // Log the client message
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file != NULL) {
        time_t current_time;
        time(&current_time);
        fprintf(log_file, "[%s] %s\n", asctime(localtime(&current_time)), buffer);
        fclose(log_file);
    } else {
        printf("Failed to open log file\n");
        fflush(stdout); // Force writing output to terminal
    }
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind server socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);
    fflush(stdout); // Force writing output to terminal

    // Accept client connections and handle messages
    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        handle_client(client_socket);
    }

    return 0;
}
```
# REVISI 
code client.c revisi 
```
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> // Fungsi untuk sistem POSIX (seperti close)
#include <arpa/inet.h> // Fungsi untuk manipulasi alamat internet
#include <sys/socket.h> // Fungsi untuk manipulasi soket

#define SERVER_PORT 50535 // Port server yang akan dihubungi oleh klien
#define BUFFER_SIZE 1024 // Ukuran buffer untuk pesan

int main() {
    int client_socket; // Variabel untuk menyimpan file descriptor dari soket klien
    struct sockaddr_in server_address; // Struktur untuk menyimpan informasi alamat server
    char message_buffer[BUFFER_SIZE] = {0}; // Buffer untuk menyimpan pesan yang dikirimkan oleh pengguna atau diterima dari server

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed"); // Cetak pesan kesalahan jika gagal membuat soket
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported"); // Cetak pesan kesalahan jika gagal mengonversi alamat IP
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed"); // Cetak pesan kesalahan jika gagal terhubung ke server
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Main loop to continuously send and receive messages until "exit" command
    while (1) {
        printf("Enter message: ");
        fgets(message_buffer, BUFFER_SIZE, stdin); // Baca pesan dari pengguna

        // Send message to server
        send(client_socket, message_buffer, strlen(message_buffer), 0);

        // Exit if message is "exit"
        if (strcmp(message_buffer, "exit\n") == 0) {
            printf("Exiting...\n");
            break;
        }

        // Receive response from server
        memset(message_buffer, 0, sizeof(message_buffer)); // Bersihkan buffer sebelum menerima respons
        read(client_socket, message_buffer, BUFFER_SIZE); // Terima respons dari server
        printf("Server response: %s\n", message_buffer); // Cetak respons dari server
    }

    // Close client socket
    close(client_socket);
    return 0;
}
```
Code server.c revisi 
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <curl/curl.h>

#define PORT 50535
#define BUFFER_SIZE 1024
#define LOG_FILE "change.log"
#define FILENAME "myanimelist.csv"
#define DOWNLOAD_URL "https://drive.google.com/uc?export=download&id=10p_kzuOgaFY3WT6FVPJIXFbkej2s9f50"

// Function to download file using wget
int download_file(const char *url, const char *filename) {
    char command[256];
    sprintf(command, "wget -O %s \"%s\"", filename, url);
    int result = system(command);
    return result == 0 ? 1 : 0;
}

// Function to read the content of a file
void read_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("Failed to open file for reading\n");
    }
}

// Function to log changes
void log_change(const char *type, const char *message) {
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file != NULL) {
        time_t current_time;
        time(&current_time);
        struct tm *local_time = localtime(&current_time);
        fprintf(log_file, "[%02d/%02d/%02d] [%s] %s\n", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year % 100, type, message);
        fclose(log_file);
    } else {
        printf("Failed to open log file\n");
        fflush(stdout); // Force writing output to terminal
    }
}

// Function to add new anime entry
void add_anime_entry(const char *entry) {
    FILE *file = fopen(FILENAME, "a");
    if (file) {
        fprintf(file, "%s\n", entry);
        fclose(file);
        // Log addition
        log_change("ADD", entry);
    } else {
        printf("Failed to open file for adding entry\n");
    }
}

// Function to edit anime entry
void edit_anime_entry(const char *old_entry, const char *new_entry) {
    FILE *file = fopen(FILENAME, "r+");
    if (file) {
        char line[BUFFER_SIZE];
        long int pos;
        while (fgets(line, BUFFER_SIZE, file)) {
            if (strstr(line, old_entry) == line) {
                pos = ftell(file) - strlen(line);
                fseek(file, pos, SEEK_SET);
                fprintf(file, "%s\n", new_entry);
                fclose(file);
                // Log edit
                log_change("EDIT", new_entry);
                return;
            }
        }
        printf("Anime entry not found for editing\n");
        fclose(file);
    } else {
        printf("Failed to open file for editing entry\n");
    }
}

// Function to delete anime entry
void delete_anime_entry(const char *title) {
    FILE *file = fopen(FILENAME, "r+");
    if (file) {
        FILE *temp_file = fopen("temp.csv", "w");
        char line[BUFFER_SIZE];
        int found = 0;
        while (fgets(line, BUFFER_SIZE, file)) {
            if (strstr(line, title) != line) {
                fprintf(temp_file, "%s", line);
            } else {
                found = 1;
            }
        }
        fclose(file);
        fclose(temp_file);
        remove(FILENAME);
        rename("temp.csv", FILENAME);
        // Log deletion
        if (found) {
            log_change("DEL", title);
        } else {
            printf("Anime entry not found for deletion\n");
        }
    } else {
        printf("Failed to open file for deleting entry\n");
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread;

    // Read client message
    valread = read(client_socket, buffer, BUFFER_SIZE);
    printf("Client message: %s\n", buffer);
    fflush(stdout); // Force writing output to terminal

    // Process client message
    if (strcmp(buffer, "exit\n") == 0) {
        printf("Closing connection with client\n");
        close(client_socket);
        return;
    } else if (strcmp(buffer, "download\n") == 0) {
        // Download file using wget
        int success = download_file(DOWNLOAD_URL, FILENAME);
        if (success) {
            printf("File downloaded successfully\n");
            // Respond to client
            char *response = "File downloaded successfully";
            send(client_socket, response, strlen(response), 0);
        } else {
            fprintf(stderr, "Failed to download file\n");
            // Respond to client
            char *response = "Failed to download file";
            send(client_socket, response, strlen(response), 0);
        }
    } else if (strcmp(buffer, "read\n") == 0) {
        // Read the content of the downloaded file
        printf("File content:\n");
        read_file_content(FILENAME);
        // Respond to client
        char *response = "File content displayed on server terminal";
        send(client_socket, response, strlen(response), 0);
    } else if (strcmp(buffer, "add\n") == 0) {
        // Respond to client
        char *response = "Enter anime details in the format: title,genre,producer,status";
        send(client_socket, response, strlen(response), 0);
    } else if (strncmp(buffer, "add ", 4) == 0) {
        // Add anime entry
        add_anime_entry(buffer + 4); // Skip "add " part
        // Respond to client
        char *response = "Anime entry added successfully";
        send(client_socket, response, strlen(response), 0);
    } else if (strcmp(buffer, "edit\n") == 0) {
        // Respond to client
        char *response = "Enter old and new anime details in the format: old_title,old_genre,old_producer,old_status,new_title,new_genre,new_producer,new_status";
        send(client_socket, response, strlen(response), 0);
    } else if (strncmp(buffer, "edit ", 5) == 0) {
        // Parse old and new anime entries
        char *token = strtok(buffer + 5, ",");
        char old_entry[BUFFER_SIZE];
        strcpy(old_entry, token);
        char new_entry[BUFFER_SIZE];
        for (int i = 0; i < 3; i++) {
            token = strtok(NULL, ",");
            if (token == NULL) {
                printf("Invalid format for edit message\n");
                fflush(stdout); // Force writing output to terminal
                return;
            }
            strcat(new_entry, token);
            strcat(new_entry, ",");
        }
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Invalid format for edit message\n");
            fflush(stdout); // Force writing output to terminal
            return;
        }
        strcat(new_entry, token);
        // Edit anime entry
        edit_anime_entry(old_entry, new_entry);
        // Respond to client
        char *response = "Anime entry edited successfully";
        send(client_socket, response, strlen(response), 0);
    } else if (strncmp(buffer, "delete ", 7) == 0) {
        // Delete anime entry
        delete_anime_entry(buffer + 7); // Skip "delete " part
        // Respond to client
        char *response = "Anime entry deleted successfully";
        send(client_socket, response, strlen(response), 0);
    } else {
        // Respond to client
        char *response = "Message received";
        send(client_socket, response, strlen(response), 0);
    }
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind server socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);
    fflush(stdout); // Force writing output to terminal

    // Accept client connections and handle messages
    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        handle_client(client_socket);
    }

    return 0;
}
```
# DOKUMENTASI
berikut adalah output untuk membaca isi file : 

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/f4a4770b-3507-4888-bcb6-283398049408)

![Screenshot from 2024-05-11 20-36-07](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/6af21607-684f-42a1-b04f-cc7df4ed6ba8)

berikut output untuk menambahkan Kanokari :

![Screenshot from 2024-05-11 21-24-39](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/d673ecfb-8870-463a-a90a-973914a026ba)

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/81a020e9-5d3a-412e-ac23-77a740fe6169)

berikut output untuk Add :

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/79e258d6-3aba-46a9-b7bb-a6f00f638f02)

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/1a4814e6-526d-4e06-9fd0-b41226e71078)

berikut output untuk edit :

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/5a7af341-0241-4cde-a02c-965fdccb63bd)

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/4c7eeb72-e778-439a-af53-7be9d8915a0b)

berikut output untuk delete :

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/371f0ad0-1b34-4b20-8871-58af494dc74c)

isi change.log :

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151106171/67bd123d-0fbf-4fcf-8be1-ab0b6d51bdfe)

















