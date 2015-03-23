DynamixelQ
==========
#####A Library to control ROBOTIS [Dynamixel smart servo actuators](http://www.robotis.com/xe/dynamixel_en) using the [OpenCM9.04 microcontroller](http://support.robotis.com/en/product/auxdevice/controller/opencm9.04.htm)
######Version 1.1, 10-23-14######
#####Download Repository: [ZIP Archive](https://github.com/horchler/DynamixelQ/archive/master.zip)#####

Based on [```Dynamixel.cpp```](https://github.com/robotis-pandora/ROBOTIS-OpenCM/blob/master/OpenCM_ide/processing-head/hardware/robotis/cores/robotis/Dynamixel.cpp) and [```Dynamixel.h```](https://github.com/robotis-pandora/ROBOTIS-OpenCM/blob/master/OpenCM_ide/processing-head/hardware/robotis/cores/robotis/Dynamixel.h) from version 1.0.2 the [ROBOTIS_OpenCM IDE](http://support.robotis.com/en/software/robotis_opencm.htm).

Features and benefits vs. the default library
 - Higher baud rates (up to 3 Mbps for MX series) available directly.
 - Added efficient overloaded array versions of functions to read and write across multiple registers.
 - Emulated [SYNC_READ](http://support.robotis.com/en/product/dynamixel_pro/communication/instruction_status_packet.htm)-based functions.
 - Improved [SYNC_WRITE](http://support.robotis.com/en/product/dynamixel/communication/dxl_instruction.htm#SYNC_WRITE)-based functions.
 - ```#define``` for baud rates and [Dynamixel addresses](http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table).
 - Added functions that automatically check if register addresses are bytes, words, or invalid.
 - Functions redesigned to use strict byte and word input arguments to catch errors at compile time.
 - Added [fast, flexible ```printf```-style functions](https://github.com/horchler/DynamixelQ/blob/master/USBprint) to replace ```SerialUSB.print```.
 - Cleaned up code to improve readability and use consistent style: removed code for boards other than OpenCM9.04 and actuators other than AX and MX series, Removed debug code and code related to 2.0 protocol.
 - Fixed [checksum bug](http://www.robotis.com/xe/?mid=qna_en&document_srl=1140665&comment_srl=1144814&rnd=1144814#comment_1144814).
 - Many other optimizations and improvements.
 
Current limitations
 - Only MX-64, AX-12, and AX-18 actuators have been specifically tested.
 - Using AX and MX series actuators together is currently not supported. 
 - Some higher-level functions, have been removed (see [```DXL_Utils.h```](https://github.com/horchler/DynamixelQ/blob/master/DynamixelQ/DXL_Utils.h)). Improved versions of these will be added in the future. 
 - More and better examples needed.

Installation
 1. Quit the ROBOTIS_OpenCM IDE application.
 2. Download and expand the [ZIP archive of the DynamixelQ repository](https://github.com/horchler/DynamixelQ/archive/master.zip). In the resultant *DynamixelQ-master* folder there two libraries: *DynamixelQ* and *USBprint*.
 3. Locate the *Libraries* folder for the ROBOTIS_OpenCM IDE and place the *DynamixelQ* and *USBprint* library folders there. On OS X, this folder is in *Documents/ROBOTIS/*. On Windows, it is located at *Documents\ROBOTIS\* (or possibly *My Documents\ROBOTIS\*).
 4. Relaunch the ROBOTIS_OpenCM IDE. "DynamixelQ" should now appear under *File > Examples* and *Sketch > Import Library...*.

--------

How to read from and write to Dynamixels at high speed using the OpenCM9.04
 - Increase baud rate between microcontroller and servos (though this can be done in software, it's much safer using the Windows-only [Dynamixel Wizard](http://support.robotis.com/en/software/roboplus/dynamixel_monitor.htm) that is part of [RoboPlus](http://support.robotis.com/en/software/roboplus_main.htm)).
 - [Update the firmware](http://www.robotis.com/xe/download_en/1132559) of all of your actuators to make sure that it is current and consistent.
 - Decrease the [return delay time](http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Actuator_Address_05).
 - Minimize read and write operations by reading and writing across multiple registers and using the SYNC_WRITE-based functions.
 - Remove unnecessary overhead from code.

How to write from the OpenCM9.04 to PC via USB at high speed
 - Minimize number of individual USB serial write operations.
 - Use the [fast ```printf```-style functions](https://github.com/horchler/DynamixelQ/blob/master/USBprint) included with DynamixelQ.
 - Increase baud rate between microcontroller and computer.
 - Reduce the [USB latency time](http://robosavvy.com/forum/viewtopic.php?p=8967#p8967) (Windows).
 - Send encoded (compressed) data and decompress later on PC.
 
--------

Acknowledgment of support: This material is based upon work supported by the [National Science Foundation](http://www.nsf.gov/) under [Grant No.&nbsp;1065489](http://www.nsf.gov/awardsearch/showAward.do?AwardNumber=1065489). Disclaimer: Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.  
&nbsp;  

Copyright &copy; 2014, Andrew D. Horchler  
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Case Western Reserve University nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ANDREW D. HORCHLER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.