# Gesture_Controlled_Robot_Arm
# MPU6050 Servo Control Project

This project uses an Arduino with an MPU6050 sensor to control two servo motors (Spin and Claw) based on gyroscope readings. The Spin servo rotates based on the Y-axis gyroscope data, while the Claw servo opens or closes based on the Z-axis gyroscope data. The project also outputs gyroscope readings to the Serial Monitor and controls an LED on pin 13 for activity indication.

## Hardware Requirements
- **Arduino Board** (e.g., Arduino Uno)
- **MPU6050 Sensor**: A 6-axis accelerometer and gyroscope sensor.
- **Servo Motors**:
  - Spin servo connected to pin 9.
  - Claw servo connected to pin 6.
- **LED**: Connected to pin 13 (optional, for activity indication).
- **Wires** and a breadboard for connections.

## Software Requirements
- **Arduino IDE**: For uploading the code to the Arduino.
- **Libraries**:
  - `Wire.h`: For I2C communication with the MPU6050.
  - `Servo.h`: For controlling the servo motors.

Install these libraries via the Arduino IDE Library Manager if not already included.

## Setup Instructions
1. **Connect the Hardware**:
   - Connect the MPU6050 to the Arduino:
     - VCC to 5V
     - GND to GND
     - SCL to A5 (or SCL pin on your Arduino)
     - SDA to A4 (or SDA pin on your Arduino)
   - Connect the Spin servo to pin 9 and the Claw servo to pin 6.
   - Ensure the servos are powered appropriately (external power may be required for stable operation).
   - Optionally, connect an LED to pin 13 for visual feedback.

2. **Upload the Code**:
   - Open the Arduino IDE.
   - Copy and paste the provided code into a new sketch.
   - Upload the sketch to your Arduino board.

3. **Monitor Output**:
   - Open the Serial Monitor (set to 9600 baud) to view gyroscope data and servo actions.

## Code Functionality
- **Initialization**:
  - Initializes I2C communication and the MPU6050 sensor.
  - Attaches the Spin servo to pin 9 (initially set to 90 degrees) and the Claw servo to pin 6 (initially set to 0 degrees).
- **MPU6050 Configuration**:
  - Configures the MPU6050 to wake up (disables sleep mode).
  - Sets the gyroscope to ±250°/s and accelerometer to ±2g.
- **Main Loop**:
  - Reads gyroscope data (X, Y, Z axes) from the MPU6050.
  - Prints gyroscope data to the Serial Monitor.
  - Blinks an LED on pin 13 when non-zero gyroscope data is detected.
  - **Spin Servo Control** (based on gyroY):
    - If `gyroY > 20000` and `SpinDegree = 90`, rotates the Spin servo to 0°.
    - If `gyroY < -20000` and `SpinDegree = 0`, rotates the Spin servo to 90°.
    - If `gyroY > 10000` and `SpinDegree = 180`, rotates the Spin servo to 90°.
    - If `gyroY < -20000` and `SpinDegree = 90`, rotates the Spin servo to 180°.
  - **Claw Servo Control** (based on gyroZ):
    - If `gyroZ > 30000`, opens the Claw servo to 90°.
    - If `gyroZ < -30000`, closes the Claw servo to 0°.
- **Servo Movement**:
  - Servo movements are implemented with a 5-degree step increment/decrement and a 30ms delay for smooth transitions.

## Usage
- Tilt the MPU6050 sensor to generate gyroscope data.
- Observe the Serial Monitor for real-time gyroscope readings and servo action logs (e.g., "Claw Open", "Claw Close", or letters "a", "b", "c", "d" for Spin servo movements).
- The Spin servo adjusts its position based on Y-axis tilt, and the Claw servo opens or closes based on Z-axis tilt.

## Notes
- Ensure the MPU6050 is properly calibrated and placed on a stable surface during initialization to avoid erroneous readings.
- Adjust the `gyroY` and `gyroZ` thresholds (e.g., 20000, 10000, 30000) if the servo responses are too sensitive or not responsive enough.
- The code uses delays (`delay(100)` and `delay(30)`) for simplicity, which may affect responsiveness in complex applications. Consider non-blocking approaches for advanced use cases.

## Troubleshooting
- **No Serial Output**: Verify the baud rate (9600) in the Serial Monitor and check USB connections.
- **Servos Not Moving**: Confirm servo connections, power supply, and pin assignments (9 for Spin, 6 for Claw).
- **Erratic MPU6050 Readings**: Check I2C connections and ensure the MPU6050 address is correct (0x68).

