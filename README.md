# 🐍 C++ Snake Game (SFML 3.0)

> **50 Hét - 50 Nyelv Kihívás: 3. Hét (C++)**

Ez a projekt a klasszikus "Snake" (Kígyós) játék modern, objektumorientált megvalósítása C++ nyelven. A grafikus megjelenítésért az ipari szabványú **SFML (Simple and Fast Multimedia Library)** felel.

---

## 🎮 Játékmenet
A játék célja a lehető legtöbb "gyümölcsöt" (piros kocka) megenni anélkül, hogy a falnak vagy a saját farkunknak ütköznénk.

* **Irányítás:** Nyilak (Fel, Le, Jobbra, Balra).
* **Pontszerzés:** Minden gyümölcs 1 pontot ér.
* **Nehezítés:** Minden 10. pont után a kígyó felgyorsul!
* **Game Over:** Falnak vagy önmagunknak ütközés esetén a kígyó "kiszürkül", és a játék megáll.
* **Újrakezdés:** Nyomd meg az `ENTER`-t.

---

## 🛠️ Technológiák
A projekt során a C++ modern elemeit használtam:
* **OOP (Objektum Orientált Programozás):** A kígyó logikája egy külön `Snake` struct-ban (osztályban) van enkapszulálva.
* **STL (Standard Template Library):** A kígyó testét `std::vector` tárolja, ami dinamikusan növekszik.
* **SFML 3.0:** 2D grafika és ablakkezelés.
* **State Management:** A játék állapotait (Fut, Game Over) logikai változók vezérlik.

---

## 🚀 Telepítés és Futtatás (Visual Studio)

Mivel ez a projekt külső könyvtárat (SFML) használ, a beüzemelés kicsit összetettebb, mint egy egyszerű "Hello World".

### 1. Előfeltételek
* Visual Studio 2022 (C++ Desktop Development csomaggal).
* **SFML 3.0.0** (vagy újabb) letöltése és kicsomagolása.

### 2. Konfiguráció
A `main.cpp` lefordításához be kell állítani a Visual Studiót:
* **Include Directories:** `C:\SFML\include` hozzáadása.
* **Library Directories:** `C:\SFML\lib` hozzáadása.
* **Linker Input:** `sfml-graphics-d.lib`, `sfml-window-d.lib`, `sfml-system-d.lib`.
* **C++ Standard:** C++17 vagy újabb (`/std:c++17`).

### 3. Futtatás
A sikeres fordítás (Build) után másold a `.dll` fájlokat (`sfml-graphics-d-3.dll` stb.) a `bin` mappából a keletkezett `.exe` mellé.
