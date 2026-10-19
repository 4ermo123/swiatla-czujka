
#define RED_1 2
#define GREEN_1 6
#define RED_2 3
#define GREEN_2 7
#define RED_3 4
#define GREEN_3 8
#define RED_4 5
#define GREEN_4 9

// 0 = prawo, 1 = góra, 2 = lewo, 3 = dół
const byte redPins[4]   = {RED_1, RED_2, RED_3, RED_4};
const byte greenPins[4] = {GREEN_1, GREEN_2, GREEN_3, GREEN_4};
const byte pirPins[4]   = {10, 11, 12, 13};

bool kolejka[4] = {false, false, false, false};
bool poprzedniPIR[4] = {false, false, false, false};

const unsigned long CZAS_ZIELONEGO = 5000;
const unsigned long CZAS_CZERWONEGO = 1000;

int aktywny = -1;
int normalnyNastepny = 0;

unsigned long czasZmiany = 0;

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(pirPins[i], INPUT);
  }

  wszystkieCzerwone();
  czasZmiany = millis();
}

void loop() {
  odczytajCzujniki();

  unsigned long teraz = millis();

  // Koniec aktualnego zielonego
  if (aktywny != -1 &&
      teraz - czasZmiany >= CZAS_ZIELONEGO) {

    wszystkieCzerwone();

    // Zwykły cykl przesuwa się dalej od kierunku,
    // który właśnie zakończył zielone.
    normalnyNastepny = (aktywny + 1) % 4;

    aktywny = -1;
    czasZmiany = teraz;
  }

  // Po przerwie wybieramy następny kierunek
  if (aktywny == -1 &&
      teraz - czasZmiany >= CZAS_CZERWONEGO) {

    int wybrany = -1;

    // Najpierw sprawdzamy, czy czujnik zmienił kolejkę.
    // Szukamy oczekującego kierunku zgodnie z normalnym cyklem.
    for (byte krok = 0; krok < 4; krok++) {
      int i = (normalnyNastepny + krok) % 4;

      if (kolejka[i]) {
        wybrany = i;
        break;
      }
    }

    // Jeśli nikt nie czeka, światła działają normalnie.
    if (wybrany == -1) {
      wybrany = normalnyNastepny;
    }

    kolejka[wybrany] = false;

    wlaczZielone(wybrany);
    aktywny = wybrany;
    czasZmiany = teraz;
  }
}

void odczytajCzujniki() {
  for (byte i = 0; i < 4; i++) {
    bool stanPIR = digitalRead(pirPins[i]) == HIGH;

    if (stanPIR && !poprzedniPIR[i]) {
      kolejka[i] = true;
    }

    poprzedniPIR[i] = stanPIR;
  }
}

void wlaczZielone(byte i) {
  wszystkieCzerwone();
  digitalWrite(redPins[i], LOW);
  digitalWrite(greenPins[i], HIGH);
}

void wszystkieCzerwone() {
  for (byte i = 0; i < 4; i++) {
    digitalWrite(redPins[i], HIGH);
    digitalWrite(greenPins[i], LOW);
  }
}
