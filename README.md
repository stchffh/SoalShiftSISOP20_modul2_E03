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
- Proses dibawah ini merupakan proses daemon yang diperlukan agar program berjalan di background
```

pid_t pid, sid;

pid = fork();

if (pid < 0)
exit(EXIT_FAILURE);

if (pid > 0)
exit(EXIT_SUCCESS);

umask(0);

sid = setsid();
if (sid < 0)
exit(EXIT_FAILURE);

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
```
- Proses dibawah ini menggunakan fungsi `time` dan `localtime` untuk menentukan `current time` (untuk cek waktu setiap saat)
```
time_t timer = time(NULL);
struct tm *tm= localtime(&timer);
```
- Proses inisialisasi detik, menit, jam dengan nilai -1 agar inputan ( * ) yang diberikan oleh user dapat dideteksi dengan mudah
```
int hour,minute,second;
int sc,mn,hr= -1;
```
- Kondisi untuk memeriksa argumen yang diinputkan oleh user. Argumen yang masuk harus berjumlah 5 argumen
```
if (argc!= 5)
{
printf ("Argument tidak valid\n");
return 0;
}
```
- Kondisi untuk mendeteksi isi char pada kolom [1],[2],[3] pada urutan pertama. Fungsi `atoi` sendiri berfungsi untuk mengubah simbol ( * ) menjadi nilai integer
```
if (argv[1][0] !='*')
sc= atoi(argv[1]);
if (argv[2][0] !='*')
mn= atoi(argv[2]);
if (argv[3][0] !='*')
hr= atoi(argv[3]);
```
- Kondisi untuk memberi batasan kalau argumen waktu yang diinput harus sesuai dengan range waktu
```
if(hr > 23 || hr < -1 || mn > 59 || mn < -1 || sc > 59 || sc < -1)
{
printf("Range waktu salah\n");
return 0;
}
```
- Selanjutnya, masuk ke main program (program utama)
```
while (1)
{
time_t timer = time(NULL);
struct tm *tm= localtime(&timer);
```
- Untuk mengambil waktu file dijalankan dan menjalankan program sesuai waktu yang ditargetkan
```
hour= tm->tm_hour;
minute= tm->tm_min;
second= tm->tm_sec;
```
- Apabila waktu yang diinput memenuhi kondisi `cron` maka script akan berjalan
```
if ((hour== hr || hr== -1) &&
(minute== mn || mn== -1) &&
(second== sc || sc== -1))
```
- Agar dapat menerima argumen untuk program yang akan dieksekusi sebagai `NULL-terminated array pointer` ke `string`. Dan element terakhir dari array ini harus NULL
```
{
if (fork()==0) {
char *argexec[] = {"bash", argv[4], NULL};
execv("/bin/bash", argexec);
}
sleep(1);
}
}
}
```

### SOAL NOMOR DUA
+ [soal2.c](https://github.com/stchffh/SoalShiftSISOP20_modul2_E03/blob/master/soal2/soal2.c)

Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.

a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].

b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).

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
a). Untuk penjelasan dan penyelesaian soal bagian a, dapat dilihat dari code dibawah ini :
```
while(1)
{
t = time(NULL);
tm_t = localtime(&t);
char foldername[100];
strftime(foldername, 100, "%Y-%m-%d_%H:%M:%S", tm_t);

pid_t child;
child = fork();

int status;

	if (child < 0) 
      	exit(EXIT_FAILURE);

    	if (child == 0)
    	{ 
      		if (fork() == 0)
      		{
        	char *argv[] = {"mkdir", "-p", foldername, NULL};
        	execv("/bin/mkdir", argv);
      		}
```
- `strftime(foldername, 100, "%Y-%m-%d_%H:%M:%S", tm_t)` untuk input format tahun-bulan-hari jam:menit:detik ke string foldername
- `char *argv[] = {"mkdir", "-p", foldername, NULL};` proses untuk membuat direktori baru
- `execv("/bin/mkdir", argv);` merupakan path `mkdir` agar process sebelumnya dapat berjalan

b). Untuk penjelasan dan penyelesaian soal bagian b, dapat dilihat dari code dibawah ini :
```
else 
      		{
        	while ((wait(&status)) > 0);
        	for (int i = 0; i < 20; i++)
        	{
          	if (fork() == 0)
          	{
            	chdir(foldername);
            	time_t t2;
            	struct tm* tm_t2;
        
            	t2 = time(NULL);
            	tm_t2 = localtime(&t2);
        
            	int t = (int)time(NULL);
            	t = (t % 1000) + 100;
            
            	char donlot[100];
            	sprintf(donlot, "https://picsum.photos/%d", t);

            	char filename[100];
           	strftime(filename, 100, "%Y-%m-%d_%H:%M:%S", tm_t2);
            	char *argv[] = {"wget", donlot, "-qO", filename, NULL};
            	execv("/usr/bin/wget", argv);
          	}
          	sleep(5);
```
- `chdir(foldername);` untuk mengganti direktori
- `	sprintf(donlot, "https://picsum.photos/%d", t);` untuk mencetak string gambar yang sudah didownload
- `strftime(filename, 100, "%Y-%m-%d_%H:%M:%S", tm_t2);` untuk input format tahun-bulan-hari jam:menit:detik ke string filename
- `char *argv[] = {"wget", donlot, "-qO", filename, NULL};` untuk mendownload file gambar pada link yang tertera
- `execv("/usr/bin/wget", argv);` merupakan path `wget` agar process sebelumnya dapat berjalan
- `sleep(5);` perintah bahwa ada jeda 5 detik sebelum menjalankan process setelahnya

c). Untuk penjelasan dan penyelesaian soal bagian c, dapat dilihat dari code dibawah ini :
```
	}
        	char foldernamezip[150];
        	sprintf(foldernamezip, "%s.zip", foldername);
        	char *argv[] = {"zip", "-qrm", foldernamezip, foldername, NULL};
        	execv("/usr/bin/zip", argv);
      		}
    		}
    		else
      		sleep(30);
  	}
}	
```
- `sprintf(foldernamezip, "%s.zip", foldername);` untuk mencetak string pada folder zip
- `char *argv[] = {"zip", "-qrm", foldernamezip, foldername, NULL};` untuk mengzip folder yang berisi gambar yang telah didownload
- `execv("/usr/bin/zip", argv);` merupakan path `zip` agar process sebelumnya dapat berjalan 

d). Untuk penjelasan dan penyelesaian soal bagian d, dapat dilihat dari code dibawah ini :
```
void killfile(char mode[])
{
FILE *filee;
filee = fopen("killer.sh", "w");
fprintf(filee,"rm $0\n");
	if(strcmp(mode, "-a")==0) 
	fprintf(filee, "#!/bin/bash\nkill -9 -%d", getpid());
    	else if(strcmp(mode, "-b")==0) 
	fprintf(filee, "#!/bin/bash\nkill %d", getpid());
    
int status;
pid_t child_id;
child_id = fork();
    	if(child_id==0)
	{ 
        char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
    	}

fclose(filee);
}
```
- Proses killer :
```
FILE *filee;
filee = fopen("killer.sh", "w");
fprintf(filee,"rm $0\n");
	if(strcmp(mode, "-a")==0) 
	fprintf(filee, "#!/bin/bash\nkill -9 -%d", getpid());
    	else if(strcmp(mode, "-b")==0) 
	fprintf(filee, "#!/bin/bash\nkill %d", getpid());
  ```
  - Untuk menjalankan proses killer :
  ```
  if(child_id==0)
	{ 
        char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
    	}
 ```
 
e). Untuk penjelasan dan penyelesaian soal bagian e, code sama seperti soal d, hanya saja untuk soal ini menggunakan strcmp untuk mencek apakah inputan -a atau -b
jika -a akan langsung di kill sedangkan -b dikill tanpa menggunakan -9
jadi proses kill berjalan secara bertahap.


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
a). Untuk penjelasan dan penyelesaian soal bagian a, dapat dilihat dari code dibawah ini :
```
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main (){
    pid_t anak;
    int tanda;

    anak = fork();
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
 - `anak = fork();` digunakan agar dapat membuat proses baru
 - `char *buat[] = {"mkdir","-p","/home/oktarizka156/modul2/indomie", (char *)NULL};` merupakan child process untuk membuat direktori baru pada path `/home/oktarizka156/modul2` yang dinamakan `indomie` 
- `execv("/bin/mkdir", buat);`  merupakan path `mkdir` agar process sebelumnya dapat berjalan
- `while(wait(&tanda) > 0);` perintah yang menandakan bahwa process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu
- `sleep(5);` perintah bahwa ada jeda 5 detik sebelum menjalankan process setelahnya
- `char *buat[] = {"mkdir", "-p", "/home/oktarizka156/modul2/sedaap", (char *)NULL};` merupakan parent process untuk membuat direktori baru pada path `/home/oktarizka156/modul2` yang dinamakan `sedaap`

b). Untuk penjelasan dan penyelesaian soal bagian b, dapat dilihat dari code dibawah ini :
```
 else{
            while(wait(&tanda)>0);
            anak=fork();
            if(anak==0){
                char *buat[] = {"unzip","/home/oktarizka156/Downloads/jpg.zip","-d","/home/oktarizka156/modul2",(char *)NULL};
                execv("/usr/bin/unzip",buat);}
```
- `char *buat[] = {"unzip","/home/oktarizka156/Downloads/jpg.zip","-d","/home/oktarizka156/modul2",(char *)NULL};` perintah untuk mengunzip file `jpg.zip` yang ada pada path `/home/oktarizka156/Downloads` menuju direktori `modul2`
- ` execv("/usr/bin/unzip",buat);` merupakan path `unzip` agar process sebelumnya dapat berjalan

c). Untuk penjelasan dan penyelesaian soal bagian c, dapat dilihat dari code dibawah ini :
```
else{
                while(wait(&tanda)>0);
                anak=fork();
                if(anak==0){
                    char *buat[] = {"find","/home/oktarizka156/modul2/jpg/","-type","f","-exec","/bin/mv","-t","/home/oktarizka156/modul2/sedaap","{}",";",(char *)NULL};
                    execv("/usr/bin/find",buat);}
                else{
                    while(wait(&tanda)>0);
                    anak=fork();
                    if(anak == 0){
                        char *buat[] = {"find","/home/oktarizka156/modul2/jpg/","-mindepth","1","-type","d","-exec","/bin/mv","-t","/home/oktarizka156/modul2/indomie","{}",";",(char *)NULL};
                        execv("/usr/bin/find",buat);}
```
- `char *buat[] = {"find","/home/oktarizka156/modul2/jpg/","-type","f","-exec","/bin/mv","-t","/home/oktarizka156/modul2/sedaap","{}",";",(char *)NULL};` perintah untuk memindahkan file pada direktori `jpg` pada `modul2` kedalam direktori `sedaap`
- `execv("/usr/bin/find",buat);` merupakan path `find` agar process sebelumnya dapat berjalan
- ` char *buat[] = {"find","/home/oktarizka156/modul2/jpg/","-mindepth","1","-type","d","-exec","/bin/mv","-t","/home/oktarizka156/modul2/indomie","{}",";",(char *)NULL};` perintah untuk memindahkan direktori yang ada pada direktori `jpg` pada `modul2` kedalam direktori `indomie`

d). Untuk penjelasan dan penyelesaian soal bagian d, dapat dilihat pada code dibawah ini :
```
else{
                        while(wait(&tanda)>0);
                        anak=fork();
                        if(anak==0){
                            char *buat[] = {"find","/home/oktarizka156/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba1.txt","'\'",";",(char *)NULL};
                            execv("/usr/bin/find",buat);}
                        else{
                            while(wait(&tanda)>0);
                            sleep(3);
                            char *buat[] = {"find","/home/oktarizka156/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba2.txt","'\'",";",(char *)NULL};
                            execv("/usr/bin/find",buat);}
```
- `char *buat[] = {"find","/home/oktarizka156/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba1.txt","'\'",";",(char *)NULL};` perintah untuk membuat file `coba1.txt` pada direktori `indomie`
- `sleep(3);` perintah bahwa ada jeda 3 detik sebelum process dijalankan
- `char *buat[] = {"find","/home/oktarizka156/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba2.txt","'\'",";",(char *)NULL};` perintah untuk membuat file `coba2.txt` pada direktori `indomie`
       
