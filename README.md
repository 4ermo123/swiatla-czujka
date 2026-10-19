
# 🚦 Inteligentna sygnalizacja świetlna z czujnikami PIR

## 📌 Opis projektu

Projekt przedstawia system czterokierunkowej sygnalizacji świetlnej sterowanej za pomocą mikrokontrolera Arduino oraz czterech czujników ruchu PIR.

System obsługuje cztery kierunki ruchu: prawo, górę, lewo i dół. Każdy kierunek posiada niezależną sygnalizację świetlną (czerwoną i zieloną) oraz przypisany czujnik ruchu.

Podstawowym zadaniem programu jest realizacja standardowego cyklu zmiany świateł z uwzględnieniem wykrytego ruchu. Jeżeli czujnik PIR wykryje ruch, odpowiedni kierunek zostaje dodany do kolejki oczekujących. Podczas wyboru kolejnego zielonego światła program uwzględnia oczekujące zgłoszenia, zachowując kolejność zgodną z normalnym cyklem.

## ⚙️ Funkcjonalności

- Obsługa czterech kierunków ruchu.
- Sterowanie ośmioma diodami LED: czterema czerwonymi i czterema zielonymi.
- Obsługa czterech czujników ruchu PIR.
- Wykrywanie zbocza narastającego sygnału z czujnika PIR.
- Zapamiętywanie zgłoszeń w kolejce dla każdego kierunku.
- Uwzględnianie oczekujących zgłoszeń podczas wyboru kolejnego kierunku.
- Automatyczne przełączanie świateł bez użycia funkcji `delay()`.
- Wykorzystanie funkcji `millis()` do odmierzania czasu, dzięki czemu program może jednocześnie odczytywać czujniki.

## 🛠️ Wykorzystane komponenty

- Arduino lub kompatybilny mikrokontroler.
- 4 czujniki ruchu PIR.
- 4 czerwone diody LED.
- 4 zielone diody LED.
- Rezystory ograniczające prąd diod LED.
- Płytka stykowa i przewody połączeniowe.

## 🔌 Konfiguracja pinów

### Diody LED

| Kierunek | Czerwona dioda | Zielona dioda |
| --- | --- | --- |
| Prawo | D2 | D6 |
| Góra | D3 | D7 |
| Lewo | D4 | D8 |
| Dół | D5 | D9 |

### Czujniki PIR

| Kierunek | Pin Arduino |
| --- | --- |
| Prawo | D10 |
| Góra | D11 |
| Lewo | D12 |
| Dół | D13 |

> **Uwaga:** Kierunki są kodowane indeksami tablic od `0` do `3`. Indeksy te odpowiadają kolejno: prawo, góra, lewo i dół.

## ⏱️ Parametry czasowe

Wartości czasowe są zdefiniowane na początku programu:

```
const unsigned long CZAS_ZIELONEGO = 5000;
const unsigned long CZAS_CZERWONEGO = 1000;
```

| Parametr | Wartość | Opis |
| --- | --- | --- |
| `CZAS_ZIELONEGO` | 5000 ms | Czas świecenia zielonego światła |
| `CZAS_CZERWONEGO` | 1000 ms | Czas przerwy z czerwonym światłem przed następnym zielonym |

Obie wartości można zmienić w zależności od wymagań projektu.

## 🧠 Zasada działania

1. **Inicjalizacja** – program konfiguruje piny wejściowe i wyjściowe, a następnie ustawia wszystkie kierunki na czerwone światło.
2. **Odczyt czujników** – w każdej iteracji pętli `loop()` sprawdzany jest stan wszystkich czujników PIR.
3. **Rejestrowanie zgłoszeń** – wykrycie przejścia sygnału PIR ze stanu `LOW` do `HIGH` powoduje dodanie danego kierunku do kolejki.
4. **Zakończenie zielonego światła** – po upływie 5 sekund aktualne zielone światło zostaje wyłączone.
5. **Przerwa bezpieczeństwa** – przez 1 sekundę wszystkie kierunki mają czerwone światło.
6. **Wybór kolejnego kierunku** – program sprawdza kolejkę, zaczynając od kierunku wyznaczonego przez standardowy cykl.
7. **Włączenie zielonego światła** – wybrany kierunek otrzymuje zielone światło, a jego zgłoszenie zostaje usunięte z kolejki.

Jeżeli żaden kierunek nie oczekuje w kolejce, sygnalizacja kontynuuje standardowy cykl.

## 📂 Struktura projektu

```
.
├── README.md
└── sygnalizacja.ino
```

Plik `sygnalizacja.ino` zawiera główny program sterujący sygnalizacją świetlną.

## 🚀 Uruchomienie projektu

1. Podłącz diody LED i czujniki PIR do pinów zgodnie z tabelami.
2. Upewnij się, że każda dioda LED ma odpowiedni rezystor ograniczający prąd.
3. Otwórz plik `sygnalizacja.ino` w Arduino IDE.
4. Wybierz odpowiednią płytkę oraz port komunikacyjny.
5. Skompiluj program i wgraj go na mikrokontroler.
6. Po uruchomieniu sprawdź, czy sygnalizacja przełącza światła, a wykrycie ruchu rejestruje zgłoszenie dla właściwego kierunku.

## ⚠️ Uwagi techniczne

- Wyjścia sterujące diodami są aktywne stanem `HIGH` dla światła czerwonego i stanem `HIGH` dla światła zielonego. W danym kierunku program włącza tylko jedną z tych diod.
- Czujniki PIR mogą wymagać czasu na stabilizację po włączeniu zasilania.
- Zmienna `poprzedniPIR[]` służy do wykrywania zmiany stanu czujnika, a `kolejka[]` przechowuje informację o oczekującym zgłoszeniu.
- Wielokrotne wykrycie ruchu w tym samym kierunku nie tworzy wielu zgłoszeń, ponieważ kolejka jest reprezentowana przez tablicę wartości logicznych.
- Program jest projektem demonstracyjnym i nie powinien być stosowany jako rzeczywisty system sterowania ruchem drogowym bez odpowiednich zabezpieczeń i walidacji.

## 🔮 Możliwe rozszerzenia

- Dodanie sygnału żółtego.
- Wprowadzenie różnych czasów zielonego światła dla poszczególnych kierunków.
- Dodanie wyświetlacza pokazującego aktualny stan sygnalizacji.
- Rozbudowanie kolejki o priorytety lub liczbę zgłoszeń.
- Dodanie trybu nocnego z krótszym cyklem.
- Implementacja komunikacji z komputerem przez port szeregowy w celu monitorowania działania systemu.

## 📄 Licencja

Projekt edukacyjny. Sposób wykorzystania i ewentualna licencja mogą zostać określone przez autora repozytorium.

