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









