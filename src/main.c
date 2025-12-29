#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dugum {
  int frekans;
  int yukseklik;
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

int main() {
  int Frekans[256] = {0};
  char Metin[] = "Merhaba benim adım Emir Bera Soğuk";
  int i = 0;

  while (Metin[i] != '\0') {
    Frekans[(unsigned char)Metin[i]]++;
    i++;
  }
  for (int j = 0; j < 256; j++) {
    if (Frekans[j] > 0) {
      dugum_olustur(Frekans[j], (char)j);
      printf("Düğüm Oluşturuldu:\n%c :\n Frekansı: %d\n", (char)j, Frekans[j]);
    }
  }
  return 0;
}
