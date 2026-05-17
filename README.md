# Arduino C4 Prop

This project is an interactive C4 explosive prop powered by an Arduino. It features a countdown timer, a secret defusal code, and an optional "wire-cutting" mode for realistic gameplay.

<p align="center">
  <img height="400" alt="front c4" src="https://github.com/user-attachments/assets/205b4830-1a5d-4ec8-9984-a87441142da1" />
  <img height="400" alt="c4 back" src="https://github.com/user-attachments/assets/040bcd7a-9bf4-490e-8115-98bea0e306fc" />
</p>

---

##  Game Modes & Logic

The code follows a specific sequence to prepare and play the game:

### 1. Setup Phase
*   **Wire Mode Toggle:** Upon startup, the screen asks to enable or disable "Wire Mode".
*   **Sequence Setting:** If Wire Mode is ON, you must define the cutting order (e.g., 1:Red, 2:Black, 3:Yellow).
*   **Timer Configuration:** Set the countdown duration (Minutes:Seconds) using the keypad.
*   **Secret Code:** Enter a defusal code (up to 7 digits). Press `#` to confirm.

### 2. Active Game (The Countdown)
Once the code is set, the timer starts. The LED and Buzzer will pulse every second. There are three ways to interact:

*   **Keypad Defusal:** Enter the correct secret code and press `#` to disarm.
*   **Wire Cutting (If enabled):** Wires must be disconnected in the **exact order** defined during setup. 
    *   *Success:* Disconnecting all wires in order disarms the prop.
    *   *Failure:* Disconnecting the wrong wire or the wrong order triggers an immediate "KABOOM".
*   ** ~~Emergency Override:** Holding both `*` and `#` for 10 seconds will force the prop to disarm.~~ Dosn't work.

### 3. End Game
*   **Disarmed:** The screen flashes "Disarmed" and the LED stays ON.
*   **Explosion:** If the timer reaches zero or the wrong wire is cut, the buzzer emits a long tone and the screen displays "KABOOM!".

---

##  Input/Output Mapping

| Pin | Function | Description |
| :--- | :--- | :--- |
| **A0-A3** | Rows 1-4 | Keypad Row Inputs |
| **A4 / A5** | SDA / SCL | I2C Communication for LCD |
| **D2** | Wire YLW | Yellow Cuttable Wire (Input Pullup) |
| **D3** | Wire BLK | Black Cuttable Wire (Input Pullup) |
| **D4** | Wire RED | Red Cuttable Wire (Input Pullup) |
| **D5-D7** | Cols 1-3 | Keypad Column Inputs |
| **D8** | Buzzer | Audio Feedback |
| **D9** | LED | Status Visual Indicator |

---

##  Keypad Pinout
**Connector Face:** `C2` - `R1` - `C1` - `R4` - `C3` - `R3` - `R2`

---

##  Hardware List

| Component | Link |
| :--- | :--- |
| **Controller** | [Arduino Uno Clone](https://fr.aliexpress.com/item/1005006010855361.html) |
| **Display** | [LCD I2C 16x2](https://fr.aliexpress.com/item/1005006100081942.html) |
| **Input** | [Keypad 4x3](https://fr.aliexpress.com/item/1005006823463315.html) |
| **Switch** | [Power Switch with LED](https://fr.aliexpress.com/item/1005005545990245.html) |
| **PCB & Tape** | [Blank PCB](https://fr.aliexpress.com/item/1005006221341250.html) / [Kapton Tape](https://fr.aliexpress.com/item/1005004804215032.html) |
| **Wiring** | [Ribbon Cable](https://fr.aliexpress.com/item/1005004762590129.html) / [2x5P Connectors](https://fr.aliexpress.com/item/1005007307830993.html) |

> **Note:** For small components (resistors, diodes), an [Arduino Starter Kit](https://www.aliexpress.com/item/3256810175749203.html) is highly recommended.

> **Tip:** You can salvage components from old electronic devices to populate your PCB.

---
The C4 Label was made by Richard Moore where you can find it on his blog https://blog.radboogie.com/make-your-own-csgo-c4-prop-part-2-hardware/
*Disclaimer: This is a non-functional prop intended for airsoft, cosplay, or cinematic use only.*
