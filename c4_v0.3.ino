#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Buzzer, LED
const int buzzerPin = 8;
const int ledPin = 9;

// Fils de déconnexion
const int wirePins[3] = { 4, 3, 2 };

// Clavier matriciel 4x3
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = { A0, A1, A2, A3 };
byte colPins[COLS] = { 5, 6, 7 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables de configuration
int timeDigits[4] = { 0, 2, 3, 0 };
int cursorIndex = 0;
bool timeSet = false;
bool codeSet = false;
bool gameActive = false;

String secretCode = "";
String enteredCode = "";

unsigned long gameDuration = 150000;
unsigned long startTime;
unsigned long starHashTime = 0;
const unsigned long disableHoldTime = 10000;

unsigned long lastBlinkTime = 0;
bool cursorVisible = true;
bool needRedraw = true;

bool victoireParFilsActive = false;
int ordreFils[3] = { 0, 1, 2 };
int filIndex = 0;
bool filTriggered[3] = { false, false, false };

// ----------- SETUP -----------
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i < 3; i++) pinMode(wirePins[i], INPUT_PULLUP);

  // Titre
  lcd.setCursor(0, 0);
  lcd.print("C4 PROP");
  delay(1000);
  lcd.clear();


  // --- MENU ---
  lcd.setCursor(0, 0);
  lcd.print("1: Wire mode ON");
  lcd.setCursor(0, 1);
  lcd.print("2: Wire mode OFF");

  char key = 0;
  while (key != '1' && key != '2') {
    key = keypad.getKey();
    if (key == '1') {
      victoireParFilsActive = true;
      lcd.clear();
      lcd.print("Wire mode: ON");
    } else if (key == '2') {
      victoireParFilsActive = false;
      lcd.clear();
      lcd.print("Wire mode: OFF");
    }
    delay(500);
  }
  delay(1000);
  lcd.clear();

  // --- Ordre des fils si activé ---
  if (victoireParFilsActive) {
    lcd.setCursor(0, 0);
    lcd.print("1:Red 2:Blk 3:Ylw");


    String ordreInput = "";
    while (ordreInput.length() < 3) {
      char key = keypad.getKey();
      if (key >= '1' && key <= '3') {
        if (ordreInput.indexOf(key) == -1) {
          ordreInput += key;
          lcd.setCursor(0, 1);
          lcd.print("-> " + ordreInput + "    ");
        }
      } else if (key == '*') {
        ordreInput = "";
        lcd.setCursor(0, 1);
        lcd.print("->             ");
      }
    }

    // Convertir en index
    for (int i = 0; i < 3; i++) {
      ordreFils[i] = ordreInput[i] - '1';  // '1' => 0, etc.
    }
    
    delay(1000);
    lcd.clear();
    lcd.print("Order set");
    delay(1000);
    lcd.clear();
  }
}

// ----------- LOOP PRINCIPALE -----------
void loop() {
  unsigned long currentTime = millis();

  // 1. Choix du temps
  if (!timeSet) {
    if (millis() - lastBlinkTime > 500) {
      cursorVisible = !cursorVisible;
      lastBlinkTime = millis();
      needRedraw = true;
    }

    char key = keypad.getKey();
    if (key) {
      needRedraw = true;

      if (key == '*') {
        if (cursorIndex > 0) cursorIndex--;
      } else if (key == '#') {
        if (cursorIndex < 3) cursorIndex++;
        else {
          int minutes = timeDigits[0] * 10 + timeDigits[1];
          int seconds = timeDigits[2] * 10 + timeDigits[3];
          gameDuration = (minutes * 60 + seconds) * 1000UL;
          timeSet = true;
          lcd.clear();
          lcd.print("Time set !");
          delay(1000);
          lcd.clear();
        }
      } else if (key >= '0' && key <= '9') {
        timeDigits[cursorIndex] = key - '0';
        if (cursorIndex < 3) cursorIndex++;
      }
    }

    if (needRedraw) {
      displayTimeSetup();
      needRedraw = false;
    }
    return;
  }

  // 2. Entrée du code secret
  if (!codeSet) {
    lcd.setCursor(0, 0);
    lcd.print("Set code:      ");
    lcd.setCursor(0, 1);
    lcd.print(secretCode + "       ");
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        if (secretCode.length() > 0 && secretCode.length() <= 7) {
          codeSet = true;
          gameActive = true;
          startTime = millis();
          lcd.clear();
          lcd.print("Code set !");
          delay(1000);
          lcd.clear();
        }
      } else if (key == '*') {
        secretCode = "";
      } else {
        if (secretCode.length() < 7) {
          secretCode += key;
        }
      }
    }
    return;
  }

  // 3. JEU EN COURS
  if (gameActive) {
    unsigned long elapsed = currentTime - startTime;
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    int timeLeft = (gameDuration - elapsed) / 1000;
    lcd.print(timeLeft);
    lcd.print("s     ");

    // --- Synchronisation Buzzer et LED ---
    if (elapsed % 1000 < 50) {
      tone(buzzerPin, 5000, 125);
    }
    if (elapsed % 1000 < 125) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    // -------------------------------------

    if (elapsed >= gameDuration) {
      gameOver(false);
      return;
    }

    // === Gestion de victoire par fils ===
    if (victoireParFilsActive) {
      int currentWire = ordreFils[filIndex];
      if (!filTriggered[currentWire] && digitalRead(wirePins[currentWire]) == HIGH) {
        filTriggered[currentWire] = true;
        filIndex++;

        if (filIndex == 3) {
          gameOver(true);
          return;
        }
      }

      // Mauvais fil déconnecté
      for (int i = 0; i < 3; i++) {
        if (!filTriggered[i] && digitalRead(wirePins[i]) == HIGH && i != ordreFils[filIndex]) {
          gameOver(false);
          return;
        }
      }
    }

    // Désactivation * + #
    if (keypad.isPressed('*') && keypad.isPressed('#')) {
      if (starHashTime == 0) starHashTime = currentTime;
      else if (currentTime - starHashTime >= disableHoldTime) {
        gameOver(true);
        return;
      }
    } else {
      starHashTime = 0;
    }

    // Code utilisateur
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        if (enteredCode == secretCode) {
          gameOver(true);
        } else {
          lcd.setCursor(0, 1);
          lcd.print("ERROR      ");
          enteredCode = "";
          delay(1000);
        }
      } else if (key == '*') {
        enteredCode = "";
        lcd.setCursor(0, 1);
        lcd.print("DELETE...      ");
      } else {
        if (enteredCode.length() < 7) {
          enteredCode += key;
          lcd.setCursor(0, 1);
          lcd.print("Code: " + enteredCode + "     ");
        }
      }
    }
  }
}

// ----------- Affichage configuration du temps -----------
void displayTimeSetup() {
  lcd.setCursor(0, 0);
  lcd.print("Time configure:");

  lcd.setCursor(0, 1);
  for (int i = 0; i < 4; i++) {
    if (i == cursorIndex && cursorVisible) {
      lcd.print('_');
    } else {
      lcd.print(timeDigits[i]);
    }
    if (i == 1) lcd.print(":");
  }
  lcd.print("   ");
}

// ----------- Fin de partie -----------
void gameOver(bool win) {
  gameActive = false;
  lcd.clear();
  if (win) {
    digitalWrite(ledPin, HIGH);
    while (true) {
      lcd.print("**--Disarmed--**");
      delay(500);
      lcd.clear();
      lcd.print("--**Disarmed**--");
      delay(500);
      lcd.clear();
    }
  } else {
    tone(buzzerPin, 5000, 2000);
    digitalWrite(ledPin, HIGH);
    while (true) {
      lcd.print("**  KABOOM !  **");
      delay(500);
      lcd.clear();
      lcd.print("  **KABOOM !**  ");
      delay(500);
      lcd.clear();
    }
  }
}
