# Proje Durum Raporu ve Devam Kılavuzu

**Tarih:** 30 Aralık 2025
**Proje:** HuffLock (Kişisel Dosya Şifreleme Aracı)

## 1. Mevcut Durum
- Frekans analizi ve dinamik düğüm oluşturma tamamlandı.
- **Sıralama:** `Dugum* kese[256]` dizisi Bubble Sort ile frekanslara göre küçükten büyüğe sıralanıyor.
- **Ağaç İnşası:** En küçük iki düğümün birleştirilip (`agac_olusturucu`), listenin sola kaydırılması ve her adımda yeniden sıralanmasıyla Huffman Ağacı başarıyla kuruldu.
- **Doğrulama:** Kök düğümün frekansının metindeki toplam byte sayısına eşit olduğu gözlemlendi.

## 2. Öğrenilen Konular
1.  **Pointer Dizileri:** Adresleri bir listede tutup yönetme.
2.  **Sıralama Algoritmaları:** Bubble Sort'un pointerlar üzerindeki uygulaması.
3.  **Algoritmik Düşünce:** Diziyi kaydırma (shifting) ve eleman yönetimi.
4.  **Veri Yapıları:** Bir ağacın (tree) tabandan tavana doğru nasıl inşa edildiği.

## 3. Bir Sonraki Adım (Roadmap)
1.  [ ] **Kod Üretimi:** Oluşturulan ağacı recursive bir fonksiyonla dolaşarak her karakter için '0' ve '1' dizilerini oluşturmak.
2.  [ ] **Kod Tablosu:** Bu bit dizilerini bir tabloda (map) saklamak.
3.  [ ] **Şifreleme:** Orijinal metni bu yeni bit dizileriyle temsil ederek "sıkıştırma/şifreleme" işlemini başlatmak.

## 4. Notlar
- UTF-8 karakterler nedeniyle beklenen 34 karakter yerine 36 byte sonucu alındı, bu normaldir ve sistemin byte bazlı doğru çalıştığını gösterir.
- Bir sonraki aşamada "Recursion" (Özyineleme) kavramına odaklanılacak.