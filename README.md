RTC-Based Attendance Logging System (LPC21xx + Linux)
Overview

This project implements a Real-Time Clock (RTC) based Attendance Logging System using the LPC21xx ARM7 microcontroller, integrated with a Linux-based host system for persistent data storage.

The embedded system handles real-time clock management, user input, and display, while the Linux application receives attendance data via serial communication and stores it in files.

Key Features
I2C communication with RTC (DS1307/DS3231)
Real-time clock display (time, date, day)
16x2 LCD interface for live system status
UART interrupt-driven input handling
Serial communication between microcontroller and Linux system
File-based attendance logging on Linux
Continuous real-time operation
Technologies Used
Embedded C
LPC21xx (ARM7TDMI)
I2C Protocol
UART Communication (Interrupt-driven)
LCD Interfacing
Linux System Programming (POSIX APIs such as open, read, write)
System Architecture

The system is divided into two main components:

Embedded System (LPC21xx):

Reads and maintains real-time data using RTC
Accepts user input via UART
Displays information on LCD
Sends attendance data over serial communication

Linux Host System:

Receives serial data via /dev/ttyUSB0
Processes incoming attendance records
Stores validated data into log files
Project Structure
Embedded Side
main.c – Main application logic
i2c.c – RTC communication driver
uart_interrupt.c – UART interrupt handling
lcd.c – LCD interface functions
delay.c – Timing utilities
header.h – Common definitions
Linux Side
serial_logger.c – Serial data reader and logger
data.txt – Authorized user database
attendance_log.txt – Stored attendance records
Working Principle
1. RTC Initialization

The RTC module is configured via I2C during startup. Time and date values are written to RTC registers.

2. Real-Time Monitoring

The microcontroller continuously reads time, date, and day from the RTC and displays them on the LCD.

3. Attendance Input

User input is received via UART. An interrupt service routine captures incoming data character-by-character. When the Enter key is pressed, the input is stored and flagged for processing.

4. Data Transmission

The microcontroller transmits the attendance data through UART at a fixed baud rate (9600). This data is sent to the connected Linux system via a USB-to-UART interface.

5. Data Reception on Linux

The Linux application opens the serial device (/dev/ttyUSB0) and configures it using termios settings. It continuously reads incoming data from the microcontroller.

6. Data Processing and Storage

The received data is:

Compared with entries in data.txt
Validated as a known user
Logged into attendance_log.txt with timestamp
Marked as IN or OUT based on previous entries
How to Run
Embedded Setup
Compile the firmware using Keil uVision or an ARM toolchain
Flash the program to the LPC21xx microcontroller
Connect RTC via I2C (SCL, SDA pins)
Connect LCD to GPIO
Connect UART to USB-to-Serial converter
Linux Setup
Connect the USB-UART device

Verify the device using:

ls /dev/ttyUSB*

Compile the logger:

gcc serial_logger.c -o logger

Run the application:

./logger
Sample Output

LCD Display

12:20:30 PM
29/11/25 MON

Log File

John123 in-time Tue Apr 28 10:00:00
John123 out-time Tue Apr 28 18:00:00
Limitations
No internal storage on the microcontroller
Depends on Linux system for data persistence
Basic validation without authentication
Single-device communication
Future Enhancements
Add EEPROM or flash storage for standalone operation
Integrate RFID or authentication mechanisms
Implement timestamp synchronization
Enable cloud or IoT-based logging
Support SD card or network-based storage
Key Learning Outcomes
Embedded and Linux system integration using UART
I2C-based RTC interfacing
Interrupt-driven UART communication
Serial communication handling in Linux
Hybrid system design combining firmware and host application