# Muscle Bot
Arduino powered robot that communicates with the user via Bluetooth and moves from hand movements.
- This was designed during the UCLA Hardware Hackathon IdeaHacks hosted by Theta Tau and IEEE.

### Use
The muscle sensor was the main item that we wanted to use on this project.
We would place it and it's sensors on our hand to detect eletrcic pulses from contracting muscles.
That would be a trigger to the machine to be prepared to recieve a gesture as a movement in a certain direction.

# Team
This project was designed and developed by:
- David James
- Alex Chen
- Noah Molloy
- Ryan Jacobs

![hardware](https://github.com/dj-2805/muscleBot/blob/master/sensorBoard.jpg)

# Hardware Used
1. Sensor Board
    - Arduino Nano
    - Accelerometer (ADXL345)
    - Bluetooth Modem (BC417)
    - MyoWare Muscle Sensor
2. Bot
    - Arduino Nano
    - Bluetooth Modem (BC417)
    - motors (2-4)
    - relays
    - etc.



![muscleBot](https://github.com/dj-2805/muscleBot/blob/master/muscleBot.jpg)



# Repository Structure
- The arduino sketches are located in the 'arduinoCode' directory. It has the code we used with the given hardware
- Furthermore, the data that was analyzed is in the 'data' folder. The data folder also has a requirements.txt file if one chooses to run a virtual environment for the python code used
