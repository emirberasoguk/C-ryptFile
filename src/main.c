#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dugum {
  int frekans;
  int veri;
  int yukseklik;
  struct Dugum *sag;
  struct Dugum *sol;
} Dugum;

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
      (Dugum *)malloc(Frekans) printf("%c --> %d\n", j, Frekans[j]);
    }
  }
  return 0;
}
