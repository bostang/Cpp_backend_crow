# C++ Simple API Backend dengan Crow

Proyek ini adalah contoh sederhana dari backend API RESTful yang dibuat menggunakan C++ dan framework web ringan Crow. API ini mengelola daftar pengguna sederhana dalam memori.

## Fitur API

API ini menyediakan endpoint berikut:

- `GET /`: Mengembalikan pesan sambutan sederhana.

- `GET /users`: Mengembalikan daftar semua pengguna dalam format JSON.

- `GET /users/<int>`: Mengembalikan data pengguna spesifik berdasarkan ID dalam format JSON.

- `POST /users`: Menambahkan pengguna baru ke daftar. Membutuhkan nama pengguna di dalam body request dalam format JSON (`{"name": "nama_pengguna"}`).

## Prasyarat

Untuk mengompilasi dan menjalankan proyek ini, Anda membutuhkan:

- Kompilator C++ yang mendukung standar C++17 (misalnya `g++`).

- Library dependensi Crow: `Boost`, `Asio`, dan `OpenSSL` (terutama untuk fitur SSL, tapi tetap direkomendasikan).

Anda dapat menginstal dependensi ini di Ubuntu/Debian dengan perintah:

```bash
sudo apt-get update
sudo apt-get install libboost-all-dev libasio-dev libjsoncpp-dev
```

## Instalasi dan Kompilasi

**Langkah 1**. Clone repositori ini:

```bash
git clone --recurse-submodules <URL_REPOSITORI_ANDA>
cd Cpp_backend_crow
```

Jika Anda sudah melakukan `git clone` tanpa `--recurse-submodules`, jalankan: `git submodule update --init --recursive`.

**Langkah 2**. Pindah ke direktori proyek:

```bash
cd <direktori-proyek-anda>
```

**Langkah 3**. Kompilasi proyek:

```bash
g++ -std=c++17 -o api_server src/main.cpp -I Crow/include -lboost_system -lboost_thread -lpthread
```

## Cara Menjalankan

Setelah kompilasi berhasil, jalankan program:

```bash
./api_server
```

Server akan mulai berjalan di `http://localhost:8080`.

## Penggunaan API

Anda bisa menggunakan curl untuk menguji endpoint-nya:

- Dapatkan semua pengguna:

```bash
curl http://localhost:8080/users
```

- Dapatkan pengguna dengan ID 1:

```bash
curl http://localhost:8080/users/1
```

- Tambahkan pengguna baru:

```bash
curl -X POST -H "Content-Type: application/json" -d '{"name": "David"}' http://localhost:8080/users
```
