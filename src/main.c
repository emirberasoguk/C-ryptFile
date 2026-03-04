#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Dugum {
  int frekans;
  char karakter;
  struct Dugum *sag;
  struct Dugum *sol;
} Dugum;

Dugum *dugum_olustur(int a, char b) {
  Dugum *temp = (Dugum *)malloc(sizeof(Dugum));
  temp->karakter = b;
  temp->frekans = a;
  temp->sag = NULL;
  temp->sol = NULL;
  return temp;
}
char *kod_tablosu[256];

// Huffman ağacını serbest bırakan fonksiyon
void agac_free(Dugum *kok) {
    if (kok == NULL) {
        return;
    }
    agac_free(kok->sol);
    agac_free(kok->sag);
    free(kok);
}

Dugum *agac_olusturucu(Dugum *kese1, Dugum *kese2) {
  Dugum *yeni = (Dugum *)malloc(sizeof(Dugum));
  yeni->frekans = kese1->frekans + kese2->frekans;
  yeni->sag = kese2;
  yeni->sol = kese1;
  return yeni;
}

void kod_olusturucu(Dugum *kök, int derinlik, char kod[]) {
  if (kök->sol == NULL && kök->sag == NULL) {
    kod[derinlik] = '\0';
    // printf("Harf:%c\t%s\n", kök->karakter, kod); // DEBUG
    unsigned char index = (unsigned char)kök->karakter;
    if (kod_tablosu[index] != NULL) { // Daha önce tahsis edilmişse serbest bırak
        free(kod_tablosu[index]);
    }
    kod_tablosu[index] = (char *)malloc(strlen(kod) + 1);
    strcpy(kod_tablosu[index], kod);
  }
  if (kök->sol != NULL) {
    kod[derinlik] = '0';
    kod_olusturucu(kök->sol, derinlik + 1, kod);
  }
  if (kök->sag != NULL) {
    kod[derinlik] = '1';
    kod_olusturucu(kök->sag, derinlik + 1, kod);
  }
}

void kapsam_kontrolu(const char *dosya_yolu, const char *anahtar) {
    FILE *dosya = fopen(dosya_yolu, "r");
    if (dosya == NULL) {
        perror("Hata: Dosya açılamadı");
        exit(1);
    }

    bool anahtar_karakterleri[256] = {false};
    int i = 0;
    while (anahtar[i] != '\0') {
        anahtar_karakterleri[(unsigned char)anahtar[i]] = true;
        i++;
    }

    int ch;
    while ((ch = fgetc(dosya)) != EOF) {
        if (!anahtar_karakterleri[ch]) {
            fprintf(stderr, "Hata: '%c' karakteri anahtar metinde bulunmuyor.\n", ch);
            fprintf(stderr, "Güvenlik nedeniyle işlem durduruldu. Lütfen anahtar metninizi güncelleyin.\n");
            fclose(dosya);
            exit(1);
        }
    }

    fclose(dosya);
    printf("Kapsam kontrolü başarılı. Dosyadaki tüm karakterler anahtar metinde mevcut.\n");
}

void sifrele_dosya(const char *giris_dosyasi_yolu, const char *anahtar) {
    FILE *giris_dosyasi = fopen(giris_dosyasi_yolu, "r");
    if (giris_dosyasi == NULL) {
        perror("Hata: Giriş dosyası açılamadı");
        exit(1);
    }

    char cikis_dosyasi_yolu[256];
    sprintf(cikis_dosyasi_yolu, "%s.huff", giris_dosyasi_yolu);

    FILE *cikis_dosyasi = fopen(cikis_dosyasi_yolu, "wb"); // Binary write mode
    if (cikis_dosyasi == NULL) {
        perror("Hata: Çıkış dosyası oluşturulamadı");
        fclose(giris_dosyasi);
        exit(1);
    }

    // Dolgu bilgisi için yer tutucu yaz (1 byte)
    fputc(0, cikis_dosyasi); 

    unsigned char current_byte = 0;
    int bit_count = 0;
    int ch;

    while ((ch = fgetc(giris_dosyasi)) != EOF) {
        char *kod = kod_tablosu[(unsigned char)ch];
        if (kod == NULL) {
            fprintf(stderr, "Hata: '%c' karakteri için Huffman kodu bulunamadı. (Bu durum kapsam kontrolü tarafından engellenmiş olmalıydı)\n", ch);
            fclose(giris_dosyasi);
            fclose(cikis_dosyasi);
            exit(1);
        }

        for (int i = 0; kod[i] != '\0'; i++) {
            int current_bit_position = 7 - bit_count;
            if (kod[i] == '1') {
                current_byte |= (1 << current_bit_position);
            }
            bit_count++;

            if (bit_count == 8) {
                fputc(current_byte, cikis_dosyasi);
                current_byte = 0;
                bit_count = 0;
            }
        }
    }

    // Kalan bitleri işle ve dolgu ekle
    int padding_bits = 0;
    if (bit_count > 0) {
        padding_bits = 8 - bit_count;
        current_byte <<= padding_bits; // Kalan bitleri sıfırlarla doldur
        fputc(current_byte, cikis_dosyasi);
    }
    
    // Dolgu bilgisini dosyanın başına yaz
    fseek(cikis_dosyasi, 0, SEEK_SET);
    fputc(padding_bits, cikis_dosyasi);


    fclose(giris_dosyasi);
    fclose(cikis_dosyasi);
    printf("Dosya başarıyla şifrelendi: %s\n", cikis_dosyasi_yolu);
}

void coz_dosya(const char *giris_dosyasi_yolu, const char *anahtar, Dugum *huffman_koku) {
    FILE *giris_dosyasi = fopen(giris_dosyasi_yolu, "rb"); // Binary read mode
    if (giris_dosyasi == NULL) {
        perror("Hata: Şifreli dosya açılamadı");
        exit(1);
    }

    // Çıkış dosyası adı oluştur
    char cikis_dosyasi_yolu[256];
    // .huff uzantısını kaldır
    strncpy(cikis_dosyasi_yolu, giris_dosyasi_yolu, sizeof(cikis_dosyasi_yolu) - 1);
    cikis_dosyasi_yolu[sizeof(cikis_dosyasi_yolu) - 1] = '\0'; // Null-terminate
    char *nokta_ptr = strrchr(cikis_dosyasi_yolu, '.');
    if (nokta_ptr != NULL && strcmp(nokta_ptr, ".huff") == 0) {
        *nokta_ptr = '\0';
    } else {
        // Eğer uzantı .huff değilse veya yoksa, varsayılan bir isim ekleyebiliriz
        strcat(cikis_dosyasi_yolu, ".txt"); // Örn: orjinal_dosya.txt
    }
    

    FILE *cikis_dosyasi = fopen(cikis_dosyasi_yolu, "w");
    if (cikis_dosyasi == NULL) {
        perror("Hata: Çıkış dosyası oluşturulamadı");
        fclose(giris_dosyasi);
        exit(1);
    }

    int padding_bits = fgetc(giris_dosyasi); // İlk byte dolgu bilgisi

    Dugum *mevcut_dugum = huffman_koku;
    int byte_oku;
    long total_bytes; // Toplam dosya boyutu (padding byte dahil)

    fseek(giris_dosyasi, 0, SEEK_END);
    total_bytes = ftell(giris_dosyasi);
    fseek(giris_dosyasi, 1, SEEK_SET); // Dolgu bilgisini atla ve veri okumaya başla

    long data_bytes_count = total_bytes - 1; // Number of actual data bytes (excluding padding byte)
    long current_data_byte_index = 0; // 0-based index for the data bytes currently being processed

    while (current_data_byte_index < data_bytes_count) { // Loop for each data byte
        byte_oku = fgetc(giris_dosyasi); // Read the current data byte
        if (byte_oku == EOF) { // Should not happen if data_bytes_count is correct
            fprintf(stderr, "Hata: Beklenenden önce dosya sonu.\n");
            break;
        }

        // Only for the last data byte, apply padding logic
        bool is_last_data_byte = (current_data_byte_index == data_bytes_count - 1);

        printf("DEBUG Decrypt: Okunan Bayt (decimal): %d (index: %ld)\n", byte_oku, current_data_byte_index); // DEBUG
        printf("DEBUG Decrypt: Okunan Bayt (hex): %02X (index: %ld)\n", (unsigned char)byte_oku, current_data_byte_index); // DEBUG
        for (int i = 7; i >= 0; i--) {
            // Son veri baytında ve dolgu bitleri ise atla
            if (is_last_data_byte && i < padding_bits) {
                printf("DEBUG Decrypt: Dolgu bitleri atlanıyor. Bit Pozisyonu: %d\n", i); // DEBUG
                break;
            }

            int bit = (byte_oku >> i) & 1; // Biti al (soldan sağa)
            printf("DEBUG Decrypt:   Bit: %d (pos: %d) -> ", bit, i); // DEBUG

            if (bit == 0) {
                mevcut_dugum = mevcut_dugum->sol;
                printf("SOL\n"); // DEBUG
            } else {
                mevcut_dugum = mevcut_dugum->sag;
                printf("SAG\n"); // DEBUG
            }

            if (mevcut_dugum->sol == NULL && mevcut_dugum->sag == NULL) { // Yaprak düğüm
                printf("DEBUG Decrypt: Yaprak Düğüm Ulaşıldı. Karakter: %c\n", mevcut_dugum->karakter); // DEBUG
                fputc(mevcut_dugum->karakter, cikis_dosyasi);
                mevcut_dugum = huffman_koku; // Ağacın köküne geri dön
            }
        }
        current_data_byte_index++;
    }

    fclose(giris_dosyasi);
    fclose(cikis_dosyasi);
    printf("Dosya başarıyla çözüldü: %s\n", cikis_dosyasi_yolu);
}


int main(int argc, char *argv[]) {
  if (argc != 4 ||
      ((strcmp(argv[1], "--sifrele") != 0 && strcmp(argv[1], "--coz") != 0))) {
    printf("Kullanım:\n");
    printf("  %s --sifrele <dosya_adı> \"<anahtar metin>\"\n", argv[0]);
    printf("  %s --coz <dosya_adı.huff> \"<anahtar metin>\"\n", argv[0]);
    return 1;
  }
  
  char *islem = argv[1];
  char *dosya_yolu = argv[2];
  char *anahtar = argv[3];

  // kod_tablosu'nu NULL ile başlat
  for (int k = 0; k < 256; k++) {
      kod_tablosu[k] = NULL;
  }

  // Huffman ağacı oluşturma kısmı
  Dugum *kese[256];
  int Frekans[256] = {0};
  
  int i = 0;
  while (anahtar[i] != '\0') {
    Frekans[(unsigned char)anahtar[i]]++;
    i++;
  }

  int indeks = 0;

  for (int j = 0; j < 256; j++) {
    if (Frekans[j] > 0) {
      kese[indeks] = dugum_olustur(Frekans[j], (char)j);
      indeks++;
    }
  }

  Dugum *temp;

  // Sıralama (Bubble Sort)
  for (int l = 0; l < indeks - 1; l++) {
    for (int k = 0; k < indeks - 1 - l; k++) {
      if (kese[k]->frekans > kese[k + 1]->frekans) {
        temp = kese[k];
        kese[k] = kese[k + 1];
        kese[k + 1] = temp;
      }
    }
  }

  Dugum *agac_kokleri = NULL;
  
  if (indeks > 0) {
      while (indeks > 1) {
        // En düşük iki frekanslı düğümü al
        Dugum *sol = kese[0];
        Dugum *sag = kese[1];
        
        // Yeni bir iç düğüm oluştur
        Dugum *yeni_dugum = agac_olusturucu(sol, sag);
        
        // İlk iki düğümü listeden çıkar
        for (int k = 0; k < indeks - 2; k++) {
            kese[k] = kese[k+2];
        }
        indeks -= 2;
        
        // Yeni düğümü listeye ekle
        kese[indeks] = yeni_dugum;
        indeks++;

        // Listeyi tekrar sırala
        for (int l = 0; l < indeks - 1; l++) {
          for (int k = 0; k < indeks - 1 - l; k++) {
            if (kese[k]->frekans > kese[k + 1]->frekans) {
              temp = kese[k];
              kese[k] = kese[k + 1];
              kese[k + 1] = temp;
            }
          }
        }
      }
      agac_kokleri = kese[0];
  } else {
      fprintf(stderr, "Hata: Huffman ağacı oluşturulamadı. Anahtar metinde yeterli karakter yok.\n");
      // Belleği temizle
      for (int k = 0; k < 256; k++) {
          if (kod_tablosu[k] != NULL) {
              free(kod_tablosu[k]);
              kod_tablosu[k] = NULL;
          }
      }
      return 1;
  }
  
  if (agac_kokleri != NULL) {
      char olusan_kod[256];
      kod_olusturucu(agac_kokleri, 0, olusan_kod);
  } else {
      fprintf(stderr, "Hata: Huffman ağacı oluşturulamadı (kod tablosu için).\n");
      // Belleği temizle (kod tablosu için zaten yapıldı, ağaç için)
      agac_free(agac_kokleri);
      for (int k = 0; k < 256; k++) {
          if (kod_tablosu[k] != NULL) {
              free(kod_tablosu[k]);
              kod_tablosu[k] = NULL;
          }
      }
      return 1;
  }
  

  if (strcmp(islem, "--sifrele") == 0) {
      printf("Şifreleme işlemi başlatılıyor...\n");
      sifrele_dosya(dosya_yolu, anahtar);

  } else { // --coz
      printf("Şifre çözme işlemi başlatılıyor...\n");
      coz_dosya(dosya_yolu, anahtar, agac_kokleri);
  }

  // Belleği temizle
  for (int k = 0; k < 256; k++) {
      if (kod_tablosu[k] != NULL) {
          free(kod_tablosu[k]);
          kod_tablosu[k] = NULL;
      }
  }
  agac_free(agac_kokleri);


  return 0;
}
