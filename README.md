# EN2533 Advanced Robotics Project

Welcome to our project where we have designed a robot to perform complex tasks with high precision. Our robot excels in various functions such as line-following, obstacle avoidance, ramp navigation, and sound detection.

## Navigation Links:
- [Highlights](#-highlights)
- [Robot Overview](#robot-overview)
  - [Sensor Suite](#sensor-suite)
  - [Actuation Mechanisms](#actuation-mechanisms)
  - [Power Supply](#power-supply)
  - [Additional Hardware](#additional-hardware)
  - [Robotic Arm CAD Design](#robotic-arm-cad-design)
- [Team Effort](#team-effort)
- [Lessons Learned](#lessons-learned)
- [Future Plans](#future-plans)

## 🚀 Highlights:
- **Path Navigation and Obstacle Evasion:** The robot adeptly maneuvers through predefined paths, accurately handling black and white tracks using eight IR sensors and avoiding obstacles with the help of two ultrasonic sensors.
- **Ramp Climbing & Object Handling:** Demonstrates its proficiency in ascending ramps and relocating lightweight objects with precision.
- **Sound Recognition:** Equipped with a microphone, the robot halts movement in response to auditory signals.

## Robot Overview:
Our robot features an extensive array of sensors and control interfaces, designed to handle a variety of challenges seamlessly.

### Sensor Suite
- **TCS34725 RGB Color Sensor:** For detecting colored objects.
- **Uxel Sound Detection Module:** Uses a microphone for sound-triggered responses.
- **4 IR Sensors:** Utilized to accurately detect 90-degree turns.
- **Gyroscope:** Adjusts speed for efficient ramp climbing.
- **Ultrasonic Sensors:** Employed for obstacle avoidance.
- **MAX9814 Microphone Amplifier Module:** Detects sound for auditory response tasks.
- **Ultrasonic Sensor:** Used specifically for the guard robot functionality.

### Actuation Mechanisms
- **Continuous Rotation SG90 Servo Motor Plastic Wheel Full Set (360 degrees):** This popular 9g servo motor is ideal for gripping mechanisms due to its ability to rotate continuously in 360 degrees.
- **Servo Motor Plastic Wheel MG995 Full Set (180 degrees):** This high-speed standard servo motor, capable of rotating approximately 180 degrees, is used for lifting applications and vertical movements.

### Power Supply
- **3300mAh LiPo Battery**

### Additional Hardware
- **N20 Standard 15mm High Universal Wheel**
- **MD0085 - L298N Motor Driver Module for Arduino (Normal)**
- **6V Buck Down Converter**
- **Battery Status Indicator**

### Robotic Arm CAD Design
The arm includes a gripper, distance sensor, and color sensor, all controlled by two servo motors. The gripper operates via a small servo motor (SG90), providing horizontal movement, while a larger servo motor (MG995) manages vertical movement. Sensors on the gripper enhance the arm's capabilities.

## Team Effort:
We appreciate the dedication and teamwork from all members, which was crucial for the success of this project.

## Lessons Learned:
- Understanding the importance of flexibility and problem-solving in robotics.
- Recognizing the advantages of advanced sensor integration for performance enhancement.
- Implementing PID controllers for more precise motor control.
- Enhancing the stability and reliability of the robot through refined mechanical design.

## Future Plans:
We aim to further refine our robot and participate in additional competitions, continuously pushing the limits of robotics.

<!-- Uncomment the following section when you have the images ready -->
<!--
## Photo Gallery:
![Robot Photo 1](image1.jpg "Robot Photo 1")
![Robot Photo 2](image2.jpg "Robot Photo 2")
![Robot Photo 3](image3.jpg "Robot Photo 3")
![Robot Photo 4](image4.jpg "Robot Photo 4")
-->
