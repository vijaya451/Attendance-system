# ⏱️ RTC-Based Attendance Logging System (LPC21xx)

## 📌 Overview

This project implements a **Real-Time Clock (RTC) based Attendance Logging System** using the **LPC21xx ARM7 microcontroller**.
It combines **I2C communication**, **UART interrupt handling**, and **LCD interfacing** to display real-time date/time and log attendance data entered via serial communication.

---

## 🎯 Key Features

* 📡 I2C communication with RTC (DS1307/DS3231)
* ⏰ Real-time clock display (Time, Date, Day)
* 🖥️ 16x2 LCD interface for live display
* ⌨️ UART interrupt-based user input
* 📝 Attendance logging via serial terminal
* 🔁 Continuous real-time updates

---

## 🧰 Technologies Used

* Embedded C
* LPC21xx (ARM7TDMI)
* I2C Protocol
* UART Communication (Interrupt-driven)
* LCD Interfacing (16x2)

---

## 🏗️ System Architecture

```id="arch1"
User (Serial Terminal)
        │
        ▼
UART0 (Interrupt)
        │
        ▼
LPC21xx MCU ─── I2C ─── RTC Module
        │
        ▼
      LCD Display
```

---

## 📁 Project Structure

```id="proj2"
├── main.c                  # Main application logic
├── i2c.c                   # I2C driver (init, read, write)
├── uart_interrupt.c        # UART interrupt handler
├── lcd.c                   # LCD driver functions
├── delay.c                 # Delay utilities
├── header.h                # Common declarations
```

---

## 🔄 Working Principle

### 🕒 RTC Initialization

* Time and date are set using I2C write operations.
* RTC registers are configured during startup.

### 📊 Real-Time Display

* Continuously reads:

  * Hours, Minutes, Seconds
  * Date, Month, Year
  * Day of the week
* Displays formatted output on LCD.

### ⌨️ Attendance Input

* User enters data via UART terminal.
* UART interrupt captures input character-by-character.
* On pressing **Enter (`\r`)**:

  * Input is stored as a string
  * `flag` is triggered

### 💾 Attendance Logging

* Captured input is:

  * Displayed via UART
  * Temporarily acknowledged on LCD ("Attendance saved")

---

## 🚀 How to Run

1. **Compile** the project using Keil uVision (or ARM toolchain).
2. **Flash** the binary to LPC21xx board.
3. Connect:

   * RTC module via I2C (P0.2 → SCL, P0.3 → SDA)
   * 16x2 LCD to GPIO
4. Open Serial Terminal:

   * Baud Rate: 9600
   * 8 Data Bits, No Parity, 1 Stop Bit
5. Observe real-time clock on LCD.
6. Enter attendance data via terminal and press Enter.

---

## 📟 Sample Output

### LCD Display

```id="lcd1"
12:20:30PM
29/11/25 MON
```

### UART Output

```id="uart1"
John123
Attendance saved
```

---

## ⚠️ Limitations

* Attendance data is not stored permanently
* No authentication mechanism
* Single-user input handling
* RTC time set manually in code

---

## 🔮 Future Enhancements

* 💾 EEPROM/Flash-based attendance storage
* 🔐 Add password/RFID authentication
* 📊 Timestamp-based logging
* ☁️ IoT/cloud integration for remote monitoring
* 📁 Export logs via UART or SD card

---

## 🧠 Key Learning Outcomes

* Low-level I2C protocol handling using registers
* Interrupt-driven UART communication
* RTC interfacing and BCD data handling
* Embedded system modular design

---

## 👨‍💻 Author

**Modem Vijaya**

---

## 📜 License

This project is intended for educational and learning purposes.
