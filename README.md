<p align="center">
  <img src="https://user-images.githubusercontent.com/2729145/183217657-21d63a3a-55eb-4e9c-9434-33947db0be48.png" height="250" />
  <br/><br/>
</p>
<hr/>

# Light-emitting integrated ukulele tuner
Ukulele with an integrated light emitting tuner

## About
This project aims to integrate a tuner composed of LEDs into a ukulele. For this purpose, the main frequency at which the different strings emit has been analyzed and converted into (absence of) light. 

## Material
Apart from the ukulele, the following material is needed:
<br><br>
![IMG_20200708_124404](https://user-images.githubusercontent.com/2729145/183245124-7ddda60c-f84c-440a-b890-eb8aa21af302.jpg)
* <a href="https://www.adafruit.com/product/1586">Adafruit Neopixel ring (24 pixels)</a> or equivalent
* Microphone with analog output (basically any one will do the job)
* <a href="https://www.sparkfun.com/products/13664">SparkFun SAMD21 Mini Breakout</a> or any Arduino M0 equivalent
* USB connector (optional)
* Perma-proto for soldering

## Connections
Assuming a basic knowledge of electronics, the connections are very simple. Connect the microphone to input pin A0 and the LED ring to digital output pin 2. Everything is powered at 5 V.

## Using Ukelele Tuner LEDs
Before inserting the electronics into the ukulele, it is recommended to upload the main.ino sketch and do a test. If everything works correctly, insert all the electronics inside the ukulele, with the microphone pointing to the center hole.


To see the construction process and instructions for use, see the video below:
<br><br>
[![thumb](https://user-images.githubusercontent.com/2729145/183290124-38bd8b7d-1fdf-4945-a2cd-00a9a4e9f02f.jpg)](https://www.youtube.com/watch?v=tkv0iWnMZ8c)
