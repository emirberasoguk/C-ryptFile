# Proje Durum Raporu: C-ryptFile

**Tarih:** 30 Aralık 2025
**Proje Adı:** C-ryptFile (Eski adı: HuffLock)
**Tür:** CLI Tabanlı Simetrik Dosya Şifreleme Aracı

**Rol:** Öğretici, Mentor,Asistan.
**Kısıtlar:** Küçük kod blokları da dahil hiç kod yazılmayacak.

## 1. Proje Vizyonu ve Mantığı

C-ryptFile, dosya şifreleme işlemlerinde Huffman Algoritmasını kullanır ancak klasik sıkıştırmadan farklı bir yöntem izler:

- **Simetrik Anahtar:** Şifreleme anahtarı rastgele bir dosya değil, kullanıcının belirlediği **"Özel Bir Metin"**dir (Passphrase).
- **Ağaç Kaynağı:** Huffman Ağacı ve Kod Tablosu, şifrelenecek dosyadan değil, bu **"Özel Metin"**den üretilir.
- **Güvenlik:** Şifreli dosyayı çözmek isteyen kişi, aynı "Özel Metni" girmek zorundadır. Ağaç bu metinden tekrar üretilir ve şifre çözülür.

## 2. Çalışma Prensibi (Akış)

1. **Girdi:** Kullanıcı bir işlem (`--sifrele`/`--coz`), bir `Dosya Yolu` ve bir `Anahtar Metin` girer.
2. **Frekans Analizi (Anahtar):** Program, `Anahtar Metin` üzerindeki karakterlerin frekanslarını çıkarır.
3. **Kapsam Kontrolü (Kritik Güvenlik Adımı):**
    - Şifrelenecek `Dosya` taranır.
    - Dosyadaki *her bir karakterin*, `Anahtar Metin` içinde geçip geçmediği kontrol edilir.
    - **HATA:** Eğer dosyada olup anahtarda olmayan bir karakter varsa (Örn: Anahtarda 'z' yok ama dosyada 'zebra' var), işlem durdurulur ve eksik karakterler kullanıcıya bildirilir.
4. **Ağaç İnşası:** Kapsam onayı alınırsa, `Anahtar Metin` verileriyle Huffman Ağacı ve Kod Tablosu oluşturulur.
5. **İşlem:** Dosya bu tabloya göre şifrelenir veya çözülür.

## 3. Mevcut Teknik Durum

- [x] Temel Huffman Ağacı yapısı (`struct Dugum`) ve `main.c` iskeleti hazır.
- [x] Frekans analizi ve Ağaç oluşturma algoritmaları çalışıyor.
- [x] Recursive fonksiyon ile karakterlerin 0-1 kodları üretilebiliyor.
- [x] Kodlar global bir `kod_tablosu` dizisinde saklanabiliyor.

## 4. Yapılacaklar Listesi (Roadmap)

### Aşama 1: CLI ve Dosya Okuma Altyapısı

- [x] `main` fonksiyonunu `argc`/`argv` argümanlarını işleyecek hale getirmek. (Tamamlandı)
- [ ] Sabit `Metin[]` dizisi yerine, gerçek dosya okuma (`fopen`, `fread`) işlemlerini entegre etmek.
- [ ] Kapsam Kontrolü: Dosyadaki karakterlerin anahtar metinde olup olmadığını doğrulamak.

## 5. Mevcut Durum Notları

- **1 Ocak 2026:** `main` fonksiyonu `argc` ve `argv` alacak şekilde güncellendi.
- **2 Ocak 2026:** Sözdizimi hataları giderildi. Huffman ağacı artık doğrudan komut satırından gelen "Anahtar Metin" (`argv[3]`) üzerinden oluşturuluyor. Dinamik anahtar yapısı başarıyla kuruldu. Bir sonraki oturumda `argv[2]` ile dosya erişimi ve karakter kapsam kontrolü yapılacak.
