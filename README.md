# SoalShiftSISOP20_modul2_E03
# SoalShiftSISOP20_modul2_E03
Praktikum Sistem Operasi Modul 2

Kelompok E3
- Sitti Chofifah                  05111840000039
- Oktarizka Asviananda Nursanty   05111840000156

### SOAL NOMOR SATU
+ [soal1.c](https://github.com/stchffh/SoalShiftSISOP20_modul2_E03/blob/master/soal1/soal1.c)

1. Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
  i. Detik: 0-59 atau * (any value)
  ii. Menit: 0-59 atau * (any value)
  iii. Jam: 0-23 atau * (any value)
  iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()
Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

### PENJELASAN :

### SOAL NOMOR DUA
+ [soal2.c](https://github.com/stchffh/SoalShiftSISOP20_modul2_E03/blob/master/soal2/soal2.c)

2. Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.
a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].
b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah

detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk

menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.
e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()

### PENJELASAN :

### SOAL NOMOR TIGA
+ [soal3.c](https://github.com/stchffh/SoalShiftSISOP20_modul2_E03/blob/master/soal3/soal3.c)

3. Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.
c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.
d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.
(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk

### PENJELASAN :
a). Untuk penjelasan soal bagian a, dapat dilihat dari code dibawah ini :
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main (){
    pid_t anak;
    int tanda;

    anak = fork();
    
    if (anak < 0){
     exit (EXIT_FAILURE);}

    if (anak == 0){
        char *buat[] = {"mkdir","-p","/home/oktarizka156/modul2/indomie", (char *)NULL};
        execv("/bin/mkdir", buat);}
    else{
        while(wait(&tanda) > 0);
        anak = fork();
        if (anak == 0){
            sleep(5);
            char *buat[] = {"mkdir", "-p", "/home/oktarizka156/modul2/sedaap", (char *)NULL};
            execv("/bin/mkdir", buat);}
 ```
 - `    pid_t anak;` untuk mendeklarasikan
        
