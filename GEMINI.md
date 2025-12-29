# Proje Durum Raporu ve Devam Kılavuzu

**Tarih:** 22 Aralık 2025
**Proje:** HuffLock (Kişisel Dosya Şifreleme Aracı)
**Dil:** C

## 1. Mevcut Durum
Şu anda Huffman algoritmasının ilk aşaması olan **Frekans Analizi** kısmını tamamladık.
- `src/main.c` dosyası içerisinde verilen bir metnin ("Merhaba benim adım...") harf analizini yapabiliyoruz.
- Türkçe karakterlerin negatif index hatasına yol açmaması için `(unsigned char)` dönüşümünü öğrendik ve uyguladık.
- Sonuçları ekrana yazdırmayı başardık.

### Son Çalışan Kod (`src/main.c`)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int frekans[256] = {0};
  char Metin[] = "Merhaba benim adım Emir Bera Soğuk";
  int i = 0;
  while (Metin[i] != '\0') {
    frekans[(unsigned char)Metin[i]]++;
    i++;
  }
  for (int j = 0; j < 256; j++) {
    if (frekans[j] > 0) {
      printf("%c --> %d\n", j, frekans[j]);
    }
  }
  return 0;
}
```

## 2. Öğrenilen Konular (Teorik & Pratik)
Bugünkü oturumda şu konuları pekiştirdik:
1.  **Struct & Typedef:** Veri yapılarını tanımlama (`struct Dugum`).
2.  **Malloc & Free:** Dinamik bellek yönetimi.
3.  **Bağlı Liste (Linked List):** Pointerlar ile düğümleri birbirine bağlama ve döngüyle gezme.
4.  **Ağaç (Tree) & Recursion:** Ağaç yapısını kurma ve özyinelemeli (recursive) fonksiyonlarla gezme.
5.  **Dizi İndeksleme:** `char` tipinin dizi indisi olarak kullanılırken `unsigned char` yapılması gerektiği.

## 3. Bir Sonraki Adım (Roadmap)
Bir sonraki oturumda **Huffman Ağacını İnşa Etme** aşamasına geçeceğiz.

**Yapılacaklar Listesi:**
1.  [ ] `src/main.c` dosyasına `struct Dugum` yapısını tekrar ekle.
    ```c
typedef struct Dugum {
    char karakter;
    int frekans;
    struct Dugum *sol;
    struct Dugum *sag;
} Dugum;
    ```
2.  [ ] Frekansı 0'dan büyük olan her karakter için bellekte (`malloc` ile) yeni bir `Dugum` oluştur.
3.  [ ] Bu düğümleri bir dizi (Array) veya Öncelik Kuyruğu (Priority Queue) içinde sakla.
4.  [ ] **Huffman Algoritması:** En az frekansa sahip iki düğümü seçip birleştirme mantığını kur.

## 4. Notlar
- UTF-8 karakterler (ğ, ş, ı) terminalde bazen garip semboller veya çoklu byte olarak görünebilir, bu şifreleme mantığını bozmaz.
- Hedefimiz önce çalışan bir prototip yapmak, sonra kodları `.h` dosyalarına ayırarak modüler hale getirmek.
