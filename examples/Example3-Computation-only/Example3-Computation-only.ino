//////////////////////////////////////////////////////////////////////////////////////////
//
//    Demo code for the MAX30001
//
//    This example utilizes an interrupt to collect heart rate and rr interval data.
//    Recordings are transmitted out through the Arduino serial port.
//
//    Arduino connections:
//
//  |MAX30001 pin label| Pin Function         |Arduino Connection|
//  |----------------- |:--------------------:|-----------------:|
//  | POCI             | Peripheral Out       |  D12             |
//  | PICO             | Peripheral In        |  D11             |
//  | SCLK             | Serial Clock         |  D13             |
//  | CS               | Chip Select          |  D7              |
//  | VCC              | Digital VDD          |  +5V             |
//  | GND              | Digital Gnd          |  Gnd             |
//  | FCLK             | 32K CLOCK            |  -               |
//  | INT1             | Interrupt1           |  02              |
//  | INT2             | Interrupt2           |  -               |
//
//    This software is licensed under the MIT License(http://opensource.org/licenses/MIT).
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//   NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#include<SPI.h>
#include "Max30001.h"

#define INT_PIN 02

MAX30001 myMAXChip;


bool rtorIntrFlag = false;
uint8_t statusReg[3];

void rtorInterruptHndlr(){
  rtorIntrFlag = true;
}

void enableInterruptPin(){
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), rtorInterruptHndlr, CHANGE);
}

void setup()
{
    Serial.begin(115200);
    pinMode(MAX30001_CS_PIN, OUTPUT);
    digitalWrite(MAX30001_CS_PIN, HIGH); // Disable SPI communication

    SPI.begin();
    SPI.setBitOrder(MSBFIRST);          // See datasheet for SPI communication settings
    SPI.setDataMode(SPI_MODE0);

    bool ret = myMAXChip.max30001ReadInfo();
    if(ret == true){
      Serial.println("Max30001 ID Success");
    }
    else{
      while(ret == false){
        // Stay here until the issue is fixed.
        ret = myMAXChip.max30001ReadInfo();
        Serial.println("Failed to read ID, please make sure all the pins are properly connected.");
        delay(10000);
      }
    }

    Serial.println("Running initialization...");
    myMAXChip.max30001BeginRtoRMode();
    enableInterruptPin();                       // Enable Arduino interrupt
    myMAXChip.max30001RegRead(STATUS, statusReg);
}

void loop()
{
    if(rtorIntrFlag){
      rtorIntrFlag = false;
      myMAXChip.max30001RegRead(STATUS, statusReg);

      if(statusReg[1] & RTOR_INTR_MASK){
        myMAXChip.getHRandRR();   // Store HR to myMAXChip.heartRate and rr to myMAXChip.RRinterval.
        Serial.print("Heart Rate: ");
        Serial.println(myMAXChip.heartRate);

        Serial.print("RR interval: ");
        Serial.println(myMAXChip.RRinterval);
      }
    }
}
