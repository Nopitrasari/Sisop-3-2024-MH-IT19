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
```
berikut adalah isi dari histori log

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/e147c7cb-0aaf-4bfb-a1a3-c681b6a4f4b0)

dibawah ini adalah hasil jika tidak ditambah kali kurang bagi atau tambah

![image](https://github.com/Nopitrasari/Sisop-3-2024-MH-IT19/assets/151911480/a2b8ab07-c390-4150-9391-2172c155b1bb)









