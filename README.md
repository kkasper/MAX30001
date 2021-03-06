# MAX30001 Complete biopotential and bioimpedence AFE
#### This code has been adapted under fair use from the MAX30003 Breakout Board library by [Protocentral](https://protocentral.com/). For original code, [see their Git repo](https://github.com/Protocentral/protocentral_max30003).

![MAX30001 Complete biopotential and bioimpedence AFE](assets/max30001developmentkit.png)

General Description taken from the [MAX30001 Datasheet](https://datasheets.maximintegrated.com/en/ds/MAX30001.pdf).

The MAX30001 is a complete, biopotential and bioimpedance (BioZ), analog front-end (AFE) solution for wearable applications. It offers high performance for clinical and fitness applications, with ultra-low power for long battery life. The MAX30001 is a single biopotential channel providing electrocardiogram (ECG) waveforms, heart rate and pacemaker edge detection, and a single bioimpedance channel capable of measuring respiration.

The biopotential and bioimpedance channels have ESD protection, EMI filtering, internal lead biasing, DC leadsoff detection, ultra-low-power, leads-on detection during standby mode, and extensive calibration voltages for builtin self-test. Soft power-up sequencing ensures no large transients are injected into the electrodes. Both channels also have high input impedance, low noise, high CMRR, programmable gain, various low-pass and high-pass filter options, and a high resolution analog-to-digital converter. The biopotential channel is DC coupled, can handle large electrode voltage offsets, and has a fast recovery mode to quickly recover from overdrive conditions, such as defibrillation and electro-surgery. The bioimpedance channel includes integrated programmable current drive, works with common electrodes, and has the flexibility for 2 or 4 electrode measurements. The bioimpedance channel also has AC lead off detection.

# Repository Contents

* **/software** - Arduino library and example sketches

# Wiring the chip to your Arduino

| MAX30001 pin label | MAX30001 pin number | Arduino Connection | Pin Function |
| :---------------- | :---------------: | :---------------: | :---------------: |
| POCI/SDO     		 | E03              | D12               |  Peripheral out        |             
| PICO/SDI		     | E04              | D11               |  Peripheral in         |
| SCLK     		     | E05              | D13               |  Serial clock     |
| CSB    		     | E06              | D07               |  Chip select |
| FCLK     		  	 | D05              | --                |  External clock (32KHz) |
| INT1      		 | D02              | D02               |  Interrupt        |
| INT2       		 | E02              | --                |  Interrupt        |
| OVDD, DVDD, AVDD   | D03, D06, E01    | Supply 3V3        |  Board which supports 3.3V and 1.8V |
| OVDD, DVDD, AVDD   | D03, D06, E01    | Supply 5V         |  5V               |
| AGND, DGND    	 | B02, B04, C03, C04, D04, C05 | Gnd   |  Ground           |


# Running the Arduino Sketches

If you have correctly installed the libraries, the example sketches should now be available from within Arduino.

[Download the latest Arduino library release (v1.1.0) for this chip here.](https://github.com/kkasper/MAX30001/releases/download/v1.1.0/max30001_arduino.zip)

Open up your Arduino IDE and run any Arduino sketch (.ino) file in the examples that you downloaded. Your Arduino should now be programmed to send data over  USB-UART. Default baud rate is 115200.

*Warning:
When connecting electrodes to the body, it is advised to disconnect any mains power source from the Arduino. For example, if you are using an Arduino powered through a laptop, disconnecting the laptop from any charger or wall outlet would be a safer option.*


License Information
===================

![License](license_mark.svg)

This product is open source! Software is open source and licensed under the following licenses:


Software
--------

**All software is released under the MIT License(http://opensource.org/licenses/MIT).**

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Documentation
-------------
**All documentation is released under [Creative Commons Share-alike 4.0 International](http://creativecommons.org/licenses/by-sa/4.0/).**
![CC-BY-SA-4.0](https://i.creativecommons.org/l/by-sa/4.0/88x31.png)

You are free to:

* Share ??? copy and redistribute the material in any medium or format
* Adapt ??? remix, transform, and build upon the material for any purpose, even commercially.
The licensor cannot revoke these freedoms as long as you follow the license terms.

Under the following terms:

* Attribution ??? You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
* ShareAlike ??? If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

Please check [*LICENSE.md*](LICENSE.md) for detailed license descriptions.
