# Arduino Motor Control with MPU6050 and Encoder Feedback

This project demonstrates an Arduino-based motor control system that adjusts motor speed and direction based on the tilt angle read from an MPU6050 sensor. It also tracks encoder pulses to monitor motor movement, displaying real-time data on an LCD.

## 🧰 Components Used

- Arduino UNO
- MPU6050 Accelerometer + Gyroscope
- L298N Motor Driver
- DC Motor with Encoder
- 16x2 LCD (connected via parallel interface)
- External Power Supply for Motor
- Jumper Wires

## 📦 Pin Configuration

| Component       | Arduino Pin |
|----------------|-------------|
| LCD RS         | 7           |
| LCD EN         | 8           |
| LCD D4-D7      | 4, 5, 6, 9  |
| MPU6050 (I2C)  | A4 (SDA), A5 (SCL) |
| L298N ENA      | 10 (PWM)    |
| L298N IN1      | 11          |
| L298N IN2      | 12          |
| Encoder A      | 3 (Interrupt) |
| Encoder B      | 13          |

## ⚙️ How It Works

- The MPU6050 measures the tilt angle of the system.
- The angle is converted into motor speed and direction using `map()` and `constrain()`.
- The L298N motor driver adjusts the motor based on the mapped speed.
- An encoder tracks the motor's movement, incrementing or decrementing `encoderCount`.
- A 16x2 LCD shows both the tilt angle and encoder count in real-time.

## 🛠️ Setup Instructions

1. Wire up the components according to the pin table.
2. Upload the Arduino code from `main.ino` to your board using the Arduino IDE.
3. Open Serial Monitor (9600 baud) to debug if needed.
4. Tilt the MPU6050 and observe the motor response and LCD output.

## 🖥️ Display Example

Angle: -12.45 Enc: 128



## 📌 Notes

- Make sure the MPU6050 is properly powered (3.3V or 5V depending on module).
- If the motor does not respond correctly, verify the direction pins (IN1/IN2).
- Adjust the angle-to-speed mapping as necessary to fit your motor specs.

## 🔗 License

MIT License

## ✨ Author

Developed by [Your Name]. Contributions and suggestions are welcome!
