#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("Harf:%c\t%s\n", kök->karakter, kod);
    unsigned char index = (unsigned char)kök->karakter;
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

int main(int argc, char *argv[]) {
  if (argc != 4 ||
      ((strcmp(argv[1], "--sifrele") != 0 && strcmp(argv[1], "--coz") != 0))) {
    printf("Hatalı argüman kullanımı");
    return 1;
  }
  int derinlik;
  char olusan_kod[256];
  Dugum *kese[256];
  int Frekans[256] = {0};
  char *anahtar = argv[3];
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

  for (int l = 0; l < indeks - 1; l++) {
    for (int k = 0; k < indeks - 1 - l; k++) {
      if (kese[k]->frekans > kese[k + 1]->frekans) {
        temp = kese[k];
        kese[k] = kese[k + 1];
        kese[k + 1] = temp;
      }
    }
  }

  while (indeks > 1) {
    kese[0] = agac_olusturucu(kese[0], kese[1]);
    for (int i = 1; indeks > i; i++) {
      kese[i] = kese[i + 1];
    }
    indeks--;
    for (int a = 0; a < indeks - 1; a++) {
      for (int b = 0; b < indeks - 1 - a; b++) {
        if (kese[b]->frekans > kese[b + 1]->frekans) {
          temp = kese[b];
          kese[b] = kese[b + 1];
          kese[b + 1] = temp;
        }
      }
    }
  }
  printf("Kök Düğümün Frekansı:%d", kese[0]->frekans);
  kod_olusturucu(kese[0], 0, olusan_kod);
  printf("-----Şifrelenmiş Metin-----\n");
  for (int i = 0; anahtar[i] != '\0'; i++) {
    printf("%s", kod_tablosu[(unsigned char)anahtar[i]]);
  }
  return 0;
}
