# Proje Durum Raporu ve Devam Kılavuzu

**Tarih:** 22 Aralık 2025
**Proje:** HuffLock (Kişisel Dosya Şifreleme Aracı)
**Dil:** C

## 1. Mevcut Durum
- Frekans analizi tamamlandı.
- `struct Dugum` yapısı oluşturuldu.
- `malloc` kullanılarak her karakter için dinamik olarak düğüm oluşturma (node creation) mantığı `src/main.c` içerisinde başarıyla uygulandı.
- Fonksiyonlar arası pointer (adres) alışverişi ve `printf` ile adres/veri takibi yapıldı.

## 2. Öğrenilen Konular (Teorik & Pratik)
1.  **Malloc & Pointer:** Bellekten yer ayırma ve bu yerin adresini fonksiyondan döndürme.
2.  **Struct Erişimi:** Pointer üzerinden `->` operatörü ile yapı elemanlarına (frekans, karakter) erişim.
3.  **Fonksiyon Tipleri:** Geriye değer döndürmeyen (`void`) ile adres döndüren (`Dugum*`) fonksiyonlar arasındaki fark.
4.  **Hata Ayıklama:** C dilindeki scope (kapsam) ve tip uyuşmazlığı hatalarını manuel olarak düzeltme.

## 3. Bir Sonraki Adım (Roadmap)
Bir sonraki oturumda bu düğümleri bir araya toplayıp ağacı öreceğiz.

**Yapılacaklar Listesi:**
1.  [ ] Oluşturulan düğümleri bir `Dugum*` dizisinde (veya öncelik kuyruğunda) sakla.
2.  [ ] **Sıralama:** Düğüm dizisini frekanslara göre küçükten büyüğe sırala.
3.  [ ] **Birleştirme:** En küçük iki düğümü alıp yeni bir "ebeveyn" düğüm oluşturma mantığını kur.

## 4. Notlar
- UTF-8 karakterler (ğ, ş, ı) terminalde bazen garip semboller veya çoklu byte olarak görünebilir, bu şifreleme mantığını bozmaz.
- Hedefimiz önce çalışan bir prototip yapmak, sonra kodları `.h` dosyalarına ayırarak modüler hale getirmek.
