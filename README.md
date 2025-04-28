# Sosyal Ağ Analiz Sistemi (C Dili)

Bu proje, sosyal ağdaki kullanıcılar ve arkadaşlık ilişkilerini modelleyerek çeşitli analizler yapmayı amaçlamaktadır.

## Özellikler

- Kullanıcı ve arkadaşlık ilişkilerini dosyadan okuma
- İlişki ağı oluşturma
- Depth-First Search (DFS) ile belirli mesafedeki arkadaşları bulma
- Ortak arkadaş analizi
- Topluluk (community) tespiti
- Etki alanı (reachability) hesaplama
- Kullanıcı kimlikleri için Binary Search Tree (BST) kullanımı

## Kullanım

1. `veriseti.txt` dosyasını oluşturun:
    ```
    USER 101
    USER 102
    USER 103
    USER 104
    USER 105
    FRIEND 101 102
    FRIEND 101 103
    FRIEND 102 104
    FRIEND 103 104
    FRIEND 104 105
    ```

2. C programını derleyin:
    ```
    gcc -o sosyal_ag sosyal_ag.c
    ```

3. Programı çalıştırın:
    ```
    ./sosyal_ag
    ```

## Gereksinimler

- C derleyicisi (gcc, clang, vs)
- Temel C kütüphaneleri (stdio.h, stdlib.h, string.h)

## Notlar

- BST yapısı kullanılarak kullanıcılar hızlıca aranabilmektedir.
- Etki alanı hesaplaması, bir kullanıcının kaç kişiye ulaşabileceğini gösterir.
- Topluluklar, bağlı bileşenler şeklinde belirlenmiştir.

## Yazar
- [Senin Adın] - [Ödev / Proje Dönemi]
