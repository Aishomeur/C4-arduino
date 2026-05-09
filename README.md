# Arduino C4 Prop

This repository contains the code and wiring schematics for a decorative C4 explosive prop powered by an Arduino.

<p align="center">
  <img width="397" alt="front c4" src="https://github.com/user-attachments/assets/205b4830-1a5d-4ec8-9984-a87441142da1" />
  <img width="394" alt="c4 back" src="https://github.com/user-attachments/assets/040bcd7a-9bf4-490e-8115-98bea0e306fc" />
</p>

---

##  Input/Output Mapping

| Pin | Function | Description |
| :--- | :--- | :--- |
| **A0** | Row 1 | Keypad Row 1 |
| **A1** | Row 2 | Keypad Row 2 |
| **A2** | Row 3 | Keypad Row 3 |
| **A3** | Row 4 | Keypad Row 4 |
| **A4** | SDA | I2C Data for LCD |
| **A5** | SCL | I2C Clock for LCD |
| **D2** | Wire YLW | Yellow Cuttable Wire |
| **D3** | Wire BLK | Black Cuttable Wire |
| **D4** | Wire RED | Red Cuttable Wire |
| **D5** | Col 1 | Keypad Column 1 |
| **D6** | Col 2 | Keypad Column 2 |
| **D7** | Col 3 | Keypad Column 3 |
| **D8** | Buzzer | Audio Feedback |
| **D9** | LED | Status Indicator |

---

##  Keypad Pinout

**Face Layout:**
`C2` - `R1` - `C1` - `R4` - `C3` - `R3` - `R2`

---

##  Hardware Used

| Component | Description |
| :--- | :--- |
| **Controller** | [Arduino Uno Clone](https://fr.aliexpress.com/item/1005006010855361.html) |
| **Display** | [LCD I2C 16x2 Display](https://fr.aliexpress.com/item/1005006100081942.html) |
| **Input** | [Keypad 4x3 (Matrix)](https://fr.aliexpress.com/item/1005006823463315.html) |
| **Switch** | [Red Power Switch with LED](https://fr.aliexpress.com/item/1005005545990245.html) |
| **PCB** | [Blank PCB 90x150mm](https://fr.aliexpress.com/item/1005006221341250.html) |
| **Connectors** | [3P Terminal Blocks](https://fr.aliexpress.com/item/33008181029.html) & [2x5P Ribbon Connectors](https://fr.aliexpress.com/item/1005007307830993.html) |
| **Cabling** | [Ribbon Cable](https://fr.aliexpress.com/item/1005004762590129.html) |
| **Insulation** | [Kapton Tape](https://fr.aliexpress.com/item/1005004804215032.html) |
| **Labels** | [Sticker Paper](https://fr.aliexpress.com/item/1005006822328276.html) |

> **Tip:** An [Arduino Starter Kit](https://www.aliexpress.com/item/3256810175749203.html) is useful for sourcing various wires, resistors, and diodes in one package.

---
**Disclaimer:** This is a prop for cosplay and cinematic purposes only.
