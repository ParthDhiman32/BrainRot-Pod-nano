# BrainRot-Pod-nano
BrainRot Pod Nano is an overengineered Embedded system project wth complex PCB and beautiful CAD enclosure mainly made for playing meme sounds and also can work as a mini music player   

# Motivation to create this and Outline of features
okay so this sounds like a really dumb project but the thing is this is a really good project infact this project will help me sharpen my PCB and CAD skills to a even newer level Because i will try my best to Make this project as polished as possible like i want to make this project as perfect as it could be 
I wanted to make a project to see what level are my skills are at.

My goals for this project are to mainly have a Beauitiful! PCB which is really pleasing to an engineers eyes and to also design an enclosure which encapsulates the beauty of the PCB while itself mantaining a really Smooth Sleek and Matte design 

This project will have a shitload of features ranging from a rotatory encoder to adjust the volume to a SD card module to load your songs to and even a AUX Jack because..WHY NOT!!! 

I want to mantain a sleek design like how apple iPODs used to be like and also make my own UI and UX for this project and Many tactile buttons for feedback maybe i'll even add a vibrating motor for haptic feedback

# Main Components Used:
1.  ESP32-S3-WROOM-1 Module 
2.  PCM5102A - Audio DAC
3.  MAX98357A - Audio Amplifer 
4.  TP4056 - Li-Po charger IC 
5.  DW01A - Battery Protection IC 
6.  FS83205A - Power Mosfet 
7.  ME6211 - LDO Regulator 
8.  AO3400 - BacLight Switch for TFT 
9.  1.54" SPI TFT display
10. Li-Po battery - 1100mAh 3.7V
11. Speaker - 3W 4Ω dynamic speaker
12. Rotary Encoder SMD
13. Tactile Buttons SMD 
14. USB C connector - 16 pin tactile receptacle 
15. Audio Jack - PJ-320A 3.5mm Stereo Audio Jack
16. SD Card slot - Push Pull SD card slot 
17. Battry connector - JST battery connector 
18. A lot of passive resistors 
19. A lot of passive capacitors 
20. M2 screws 

## Reason for selection of each part 
 1. ESP32-S3-WROOM-1 Module - this specific module was selected because it has 8MB of PSRAM which acts as the DMA audio buffer also because it has more than enough processing power and as it also has wifi and bluetooth i can add these features later to my project 

 2. PCM5102A - Normally audio DACs require bulky DC blocking Capacitors but as this IC has a negative voltage rail which produces ground centered Audio this eliminates the need of those bulky DC Blosking capacitors 

 3. MAX93857A - this is an Mono Class-D audio amplifer IC (amp for short) and it shares the common I2C bus as the DAC and also it will shut off automatically when the Audio jack / AUX will be connected 

 4. TP4056 - This is a very common Typical Li-Po battery chargin IC no need for more explanation

 5. DW01A - This is a battery protection IC which is paired with TP4056 which provides Short Circuit and overload protection to the battery 

 6. AP2112K-3.3 - This is a ultra low dropout power regulator meaning it will extract maximum voltage from the Lipo battery before it drops out it drops out around 3.55V unlike older inefficient AMS117 which dropout at around 4.3V

 7. ME6211 - efficiently converts the 5V from the power system to 3V3 volts the entire circuitry works on

 8. AO3400 - This is a simple PWM switch which will be used to control the intensity of Backlight of the 2.8" TFT Display 

 9.  1.54" SPI TFT display - Very high quality display with vivid range of colours and no grainy text 

 10. 1100mAh Li-Po battery provied long enough battery life that if optmized could give all day long runtime 
 
 11. 3W 4Ω dynamic speaker - Loud enough speaker and also can be driven Efficiently by our Audio amplifier circuitry 

 12. Rotary Encoder - To simply control the Volume 

 13. Tactile Buttons - Buttons with 5-20N of actuation force so that it gives a premium click! feel 

 14. USB C connector - for charging the battery and flashing / Updating the firmware 

 15. Audio Jack - Only to connect external wired earphones

 16. SD Card slot - Ti store Songs / MEME sounds 

 17. Battery Connector - A JST batter connector to prevent accidental rever polatiy connections 

 18. 19.  resistors and capacitors - Do i even need to explain why this is needed 

 20. M2 screws are small enough to be screwed and not be noticed easily


# PCB Schematics

## Complete Schematic

<p align="center">
  <img width="1052" alt="Complete Schematic" src="https://github.com/user-attachments/assets/e8e12aa7-618d-458a-bd11-26b736392d84"/>
</p>

---

## Complete PCB

### Op-Amps & Audio Circuit

<p align="center">
  <img width="426" alt="Audio Amplifier" src="https://github.com/user-attachments/assets/b457c876-4948-420e-acca-de8562314e02"/>
</p>

<p align="center">
  <img width="1567" alt="Audio System Schematic" src="https://github.com/user-attachments/assets/4ade0fef-741f-4a1d-83b0-fd7e671f20ef"/>
</p>

---

## Power System

<p align="center">
  <img width="1156" alt="Power System" src="https://github.com/user-attachments/assets/1bcf577f-b104-4161-95c2-969ad5b410ee"/>
</p>

---

## ESP32 & Peripheral Connections

<p align="center">
  <img width="1251" alt="ESP32 and Peripheral Connections" src="https://github.com/user-attachments/assets/c1364b28-a919-431d-87ab-01136a201906"/>
</p>

# CAD DESIGN 
<img width="1920" height="631" alt="BrainRot_Pod_Nano_PCB_assembly v11" src="https://github.com/user-attachments/assets/dafb6c94-1a0f-472f-9377-422ec5d3b662" />

<img width="1920" height="631" alt="BrainRot_Pod_Nano_PCB_assembly v11 V2" src="https://github.com/user-attachments/assets/0c3ac997-7222-4533-b176-f05aabd56887" />

<img width="1920" height="631" alt="BrainRot_Pod_Nano_PCB_assembly v11 V3" src="https://github.com/user-attachments/assets/aa9a9872-7c2c-4d2d-8531-9632df669f40" />

