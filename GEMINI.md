# Proje Durum Raporu: C-ryptFile

**Tarih:** 30 Aralık 2025
**Proje Adı:** C-ryptFile (Eski adı: HuffLock)
**Tür:** CLI Tabanlı Simetrik Dosya Şifreleme Aracı

## 1. Proje Vizyonu ve Mantığı
C-ryptFile, dosya şifreleme işlemlerinde Huffman Algoritmasını kullanır ancak klasik sıkıştırmadan farklı bir yöntem izler:
- **Simetrik Anahtar:** Şifreleme anahtarı rastgele bir dosya değil, kullanıcının belirlediği **"Özel Bir Metin"**dir (Passphrase).
- **Ağaç Kaynağı:** Huffman Ağacı ve Kod Tablosu, şifrelenecek dosyadan değil, bu **"Özel Metin"**den üretilir.
- **Güvenlik:** Şifreli dosyayı çözmek isteyen kişi, aynı "Özel Metni" girmek zorundadır. Ağaç bu metinden tekrar üretilir ve şifre çözülür.

## 2. Çalışma Prensibi (Akış)
1.  **Girdi:** Kullanıcı bir işlem (`--sifrele`/`--coz`), bir `Dosya Yolu` ve bir `Anahtar Metin` girer.
2.  **Frekans Analizi (Anahtar):** Program, `Anahtar Metin` üzerindeki karakterlerin frekanslarını çıkarır.
3.  **Kapsam Kontrolü (Kritik Güvenlik Adımı):**
    - Şifrelenecek `Dosya` taranır.
    - Dosyadaki *her bir karakterin*, `Anahtar Metin` içinde geçip geçmediği kontrol edilir.
    - **HATA:** Eğer dosyada olup anahtarda olmayan bir karakter varsa (Örn: Anahtarda 'z' yok ama dosyada 'zebra' var), işlem durdurulur ve eksik karakterler kullanıcıya bildirilir.
4.  **Ağaç İnşası:** Kapsam onayı alınırsa, `Anahtar Metin` verileriyle Huffman Ağacı ve Kod Tablosu oluşturulur.
5.  **İşlem:** Dosya bu tabloya göre şifrelenir veya çözülür.

## 3. Mevcut Teknik Durum
- [x] Temel Huffman Ağacı yapısı (`struct Dugum`) ve `main.c` iskeleti hazır.
- [x] Frekans analizi ve Ağaç oluşturma algoritmaları çalışıyor.
- [x] Recursive fonksiyon ile karakterlerin 0-1 kodları üretilebiliyor.
- [x] Kodlar global bir `kod_tablosu` dizisinde saklanabiliyor.

## 4. Yapılacaklar Listesi (Roadmap)

### Aşama 1: CLI ve Dosya Okuma Altyapısı
- [ ] `main` fonksiyonunu `argc`/`argv` argümanlarını işleyecek hale getirmek.
- [ ] Sabit `Metin[]` dizisi yerine, gerçek dosya okuma (`fopen`, `fread`) işlemlerini entegre etmek.

### Aşama 2: Kapsam Kontrolü (Validation)
- [ ] Hedef dosyayı okuyup, içindeki karakterlerin Anahtar Metin'de olup olmadığını denetleyen fonksiyonun yazılması.
- [ ] Eksik karakterleri raporlayan hata mekanizması.

### Aşama 3: Şifreleme ve Bit Manipülasyonu
- [ ] Metin tabanlı "0101..." çıktısı yerine, bu bitleri 8'erli paketleyip (`Bitwise Operations`) binary dosyaya yazan fonksiyonun geliştirilmesi.

### Aşama 4: Deşifreleme (Çözme)
- [ ] Şifreli binary dosyayı okuyup, Huffman Ağacı üzerinde gezinerek orijinal metni geri oluşturan fonksiyon.

## 5. Notlar
- Türkçe karakter desteği (UTF-8) konusunda dikkatli olunmalı. `unsigned char` kullanımı kritik.
- Anahtar metin ne kadar uzun ve çeşitli karakter içerirse, şifreleme o kadar güçlü ve kapsamlı olur.
