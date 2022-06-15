//////////////////////////////////////////////////////////////////////////////////////////
//
//    Demo code for the MAX30001
//
//    This example plots live ECG data via the Arduino Plotter.
//
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

MAX30001 myMAXChip;


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
      Serial.println("Max30001 read ID success.");
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
    myMAXChip.max30001Begin();   // Run initialization
}

void loop()
{
    myMAXChip.getEcgSamples();   // Read the ECG sample and store it to myMAXChip.ecgdata

    Serial.println(myMAXChip.ecgdata);
    delay(8);
}
