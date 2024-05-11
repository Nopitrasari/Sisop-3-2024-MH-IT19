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

