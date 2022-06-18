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
uint8_t cur_ecg_gain  = 20;

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

    cur_ecg_gain = myMAXChip.max30001GetEcgGain();
}

void loop()
{
    myMAXChip.getEcgSample();   // Read the ECG FIFO store ADC reading to myMAXChip.ecgData structure
    long raw_ecg_adc = myMAXChip.ecgData.value;
    double formatted_ecg_data = (raw_ecg_adc * 1000) / (pow(2, 17) * cur_ecg_gain);  // Vref = 1000 mV by default

    Serial.println(formatted_ecg_data);
    delay(8);
}

void printEcgSample()
{
    long raw_ecg_adc = myMAXChip.ecgData.value;
    double formatted_ecg_data = (raw_ecg_adc * 1000) / (pow(2, 17) * cur_ecg_gain);  // See datasheet for equation
    Serial.print("ECG reading (mV): ");
    Serial.println(formatted_ecg_data);
    Serial.print("ETAG[2:0]: ");
    Serial.println(myMAXChip.ecgData.e_tag);
    Serial.print("PTAG[2:0]: ");
    Serial.println(myMAXChip.ecgData.p_tag);
}

