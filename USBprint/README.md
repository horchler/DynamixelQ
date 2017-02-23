USBprint
==========
#####A Library for fast convenient ```printf```-style printing with the [OpenCM9.04 microcontroller](http://support.robotis.com/en/product/auxdevice/controller/opencm9.04.htm)
######Version 1.1, 4-28-15######
#####Download Repository: [ZIP Archive](https://github.com/horchler/USBprint/archive/master.zip)#####

Features and benefits of ```printf```-style functions vs. the default ```SerialUSB.print```
 - The ability to convert and transmit multiple values all at once results in faster communication.
 - Better floating point conversions.
 - More data types and conversions are supported.
 - More readable code.
 
Current limitations
 - Examples and testing needed.

Installation
 1. Quit the ROBOTIS_OpenCM IDE application.
 2. Download and expand the [ZIP archive of the DynamixelQ repository](https://github.com/horchler/USBprint/archive/master.zip). Rename the resultant folder *USBprint*.
 3. Locate the *libraries* folder for the ROBOTIS_OpenCM IDE and place the *USBprint* folder there. On OS X, this folder is in *Documents/ROBOTIS/*. On Windows, it is located at *Documents\ROBOTIS\* (or possibly *My Documents\ROBOTIS\*).
 4. Relaunch the ROBOTIS_OpenCM IDE. "USBprint" should now appear under *File > Examples* and *Sketch > Import Library...*.

--------

How to read from and write to Dynamixels at high speed using OpenCM9.04
 - Increase baud rate between microcontroller and servos (though this can be done in software, it's much safer using the Windows-only [Dynamixel Wizard](http://support.robotis.com/en/software/roboplus/dynamixel_monitor.htm) that is part of [RoboPlus](http://support.robotis.com/en/software/roboplus_main.htm)).
 - [Update the firmware](http://www.robotis.com/xe/download_en/1132559) of all of your actuators to make sure that it is current and consistent.
 - Decrease the [return delay time](http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Actuator_Address_05).
 - Minimize read and write operations by reading and writing across multiple registers and using the SYNC_WRITE-based functions.
 - Remove unnecessary overhead from code.

How to write from OpenCm9.04 to PC via USB at high speed
 - Minimize number of individual USB serial write operations.
 - Use the fast print functions in USBprint.
 - Increase baud rate between microcontroller and computer.
 - Reduce the [USB latency time](http://robosavvy.com/forum/viewtopic.php?p=8967#p8967) (Windows).
 - Send encoded (compressed) data and decompress later on PC.
 
--------

Another version of this library specific to [TI Tiva C (Stellaris) series LaunchPad microcontrollers](http://www.ti.com/ww/en/launchpad/launchpads-connected.html), is [available separately](https://github.com/horchler/USBprint).

--------

Andrew D. Horchler, *horchler @ gmail . com*, [biorobots.case.edu](http://biorobots.case.edu/)  
Created: 8-24-14, Revision: 1.1, 4-28-15  
&nbsp;  

--------

Copyright &copy; 2015&ndash;2017, Andrew D. Horchler  
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Case Western Reserve University nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ANDREW D. HORCHLER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.