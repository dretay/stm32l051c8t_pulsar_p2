# Pulsar P2 

> New PCB, PCB Carrier, and firmware for the restoration of a the world's first digital watch.

In 1972 Hamilton released the Pulsar P2, the world's first commercially available digital watch. This watch featured a distinctive "dot" led display and did nothing more than display the time. As technology moved on LED-based watches fell out of favor due to their high energy usage and were replaced by much more efficient LCD-based watches. As a result most of these early watches were thrown into drawers and left for decades unused with their old batteries still installed. Over time the batteries would leak gas and corrosive acids that destroyed the watch's PCB and rendered it non-functional. This project documents my restoration of a non-functional Pulsar P2 by harvesting the original LED panel and inserting it into a modern redesigned PCB.  

### Main Features

- Very low idle current consumption <img src="https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/pics/IMG_5709.jpg" align="right" width="208">
  - The watch sleeps at 5uA of power consumption, with most of that (4uA) coming from the crystal oscillator. 
  - Highly efficient LED driving - the segments are charlieplex'd and there is a built-in ambient light sensor to control the brightness. When displaying time the consumption is between 20mA and 50mA. 
  - Worst-case battery life of 4 hours (display always on) and best-case life of 4.5 years (display never turned on)

### Build Instructions

#### PCB Design

The PCB was designed in Altium CircuitMaker. You can download the project [here](https://circuitmaker.com/Projects/Details/Andrew-Tayman/Pulsar-P2-Board) if you want to edit it yourself or you can grab the Gerber and Drill files that were uploaded [here](https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/resources/Pulsar%20P2%20Layout.zip). If you want you can also just put in an OshPark order yourself [here](https://oshpark.com/shared_projects/0NyVLPPb).

![](https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/pics/IMG_5688.jpg)

*I'll do my best to keep the static resources up-to-date, but for best results you should pull the project directly out of CircuitMaker. **Note**: I ended up ditching the crystal and using an oscillator for the RTC... a newer design needs to be spun that incorporates that.* 

#### PCB Carrier

One idea I had but haven't had the time to fully execute was to replace the old Pulsar PCB carrier with a newer CNC milled version. The original watch used an obsolete #355 watch battery. These are no longer manufactured, and you must now use #357 batteries with spacers. These spacers can cause issues if not precisely made due to them binding to the battery or putting too much pressure on the watch case and causing incorrect seals. Furthermore #357 batteries have a smaller capacity than the original #357 (due to their smaller size) and thus must be changed more frequently. I modeled out the original PCB carrier as a 3D rendering, which should allow me to change the battery to either support a #355 natively or to swap it out entirely for a higher-capacity (and rechargeable) battery like  a CR2032. You can download the STL files for this carrier [here](https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/resources/pulsar_p2_carrier.stl) or get the raw design itself by going [here](https://a360.co/2O2gdrLSetting). 

<img src="https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/pics/p2%20plate%20v8%20top.png" >
<img src="https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/pics/p2%20plate%20v8%20bottom.png" >


#### Source code 

This project makes use of a few reusable libraries I wrote to help handle some common needs: 

- The [Timer](https://github.com/dretay/stm32_timer) library helps implement a simple software-based scheduling / timer solution without needing to incorporate a heavy RTOS library. 
- The [PushButton](https://github.com/dretay/stm32_pushbutton) library is a software-based button debouncing solution that helps organize button actions and provides higher-level abstractions like "long push" and "double push."

Beyond these libraries the project itself was built in STM32CubeIDE. The software coordinates actions through logic defined in [Application.c](https://github.com/dretay/stm32l051c8t_pulsar_p2/blob/master/Core/Src/Application.c).  

#### Energy Usage

A major challenge with this project was getting energy usage as low as possible and characterizing the watch's behavior under different levels of battery charge. I used a Keithley 2450 SourceMeter to build a discharge model for the two LR44 batteries I was using to power the watch. I fixed the batteries together with a clamp with a small strip of aluminum on each side. I then used some kelvin clips to connect the batteries to the sourcemeter so I could characterize them.

<img src="https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/pics/IMG_5713.jpg" >
<img src="https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/pics/IMG_5711.jpg" >

I was then able to load the resulting model into a Keithley 2281s Battery Simulator and ensure proper behavior a lower battery charge levels.
![](https://github.com/dretay/stm32l051c8t_pulsar_p2/raw/master/pics/IMG_5748.jpg)

- https://www.microchip.com/DevelopmentTools/ProductDetails/ATATMEL-ICE)
