//////////////////////////////////////////////////////////////////////////////////////////
//
//    BioZ Demo code for the MAX30001
//
//    This example plots the BioZ through Arduino Plotter.
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

double bioz_cg_mags[] = {0, 8E-6, 16E-6, 32E-6, 48E-6, 64E-6, 80E-6, 96E-6};
double cur_cg_mag = 0;
uint8_t cur_bioz_gain = 10;

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
    myMAXChip.max30001Begin();   // Initialize MAX30001

    uint8_t regReadBuff[4];
    myMAXChip.max30001RegRead(CNFG_BIOZ, regReadBuff);
    uint8_t bioz_cgmag = regReadBuff[3] & 0x70;                 // CNFG_BIOZ[6:4] = CG_MAG[2:0]
    cur_cg_mag = bioz_cg_mags[bioz_cgmag];
    cur_bioz_gain = myMAXChip.max30001GetBioZGain();
}

void loop()
{
    myMAXChip.getBioZSample();   // Read the BioZ FIFO and store ADC reading to myMAXChip.biozdata structure
    long raw_bioz_adc = myMAXChip.biozData.value;
    double formatted_bioz_data = (raw_bioz_adc * 1) / (2^19 * cur_cg_mag * cur_bioz_gain); // Vref = 1V by default

    Serial.println(formatted_bioz_data);
    delay(8);
}

void printBioZSample()
{
    long raw_bioz_adc = myMAXChip.biozData.value;
    double formatted_bioz_data = (raw_bioz_adc * 1) / (2^19 * cur_cg_mag * cur_bioz_gain); // See datasheet for eq
    Serial.print("BioZ reading (Ohm): ");
    Serial.println(formatted_bioz_data);
    Serial.print("BTAG[2:0]: ");
    Serial.println(myMAXChip.biozData.b_tag);
}

