# C-ryptFile: Simetrik Dosya Şifreleme Aracı | Symmetric File Encryption Tool

C-ryptFile, Huffman kodlaması prensiplerini kullanarak kişisel dosyalarınızı bir "Anahtar Metin" (Passphrase) aracılığıyla şifrelemek için tasarlanmış, C tabanlı bir terminal uygulamasıdır.

C-ryptFile is a C-based terminal utility designed to encrypt personal files using a "Passphrase" based on customized Huffman coding principles.

---

## Özellikler (Features)

### TR

- **Simetrik Anahtar (Passphrase):** Şifreleme, kullanıcının belirlediği özel bir cümleden üretilen Huffman ağacına dayanır. Anahtar dosyası taşıma zorunluluğunu ortadan kaldırır.
- **Kapsam Kontrolü (Coverage Check):** Şifrelenecek dosyadaki tüm karakterlerin anahtar metinde bulunmasını zorunlu kılarak güvenliği artırır.
- **Terminal Entegrasyonu:** Linux terminaline özel kısayollar ile her yerden hızlı erişim.
- **Binary Sıkıştırma:** Şifreleme işlemi sırasında veriyi bit seviyesinde paketleyerek gerçek bir güvenlik ve depolama verimliliği sağlar.

### EN

- **Symmetric Passphrase:** Encryption is based on a Huffman tree generated from a user-defined private sentence. Eliminates the need for carrying key files.
- **Coverage Check:** Enhances security by requiring all characters in the target file to be present in the passphrase.
- **Terminal Integration:** Seamless access via custom Linux terminal shortcuts and aliases from any directory.
- **Binary Compression:** Packs data at the bit level during encryption, ensuring true security and storage efficiency.

---

## Kullanım (Usage)

### Şifreleme (Encrypt)
```bash
c-ryptfile --sifrele dosya.txt "gizli anahtar cümlem"
```

### Şözme (Decrypt)
```bash
c-ryptfile --coz dosya.huff "gizli anahtar cümlem"
```

---

## Teknolojiler (Technologies)

- **Language:** C
- **Platform:** Linux
- **Core Algorithm:** Huffman Coding (Symmetric Key Implementation)