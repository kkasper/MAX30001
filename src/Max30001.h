//////////////////////////////////////////////////////////////////////////////////////////
//
//  Demo code for the MAX30001 breakout board
//
//  Copyright (c) 2021 Kevin Kasper
//
//  This software is licensed under the MIT License(http://opensource.org/licenses/MIT).
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//  For information on how to use, visit https://github.com/Protocentral/protocentral-max30001-arduino
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef Max30001.h
#define Max30001.h

#include <Arduino.h>

#define WREG 0x00
#define RREG 0x01

#define   NO_OP           0x00
#define   STATUS          0x01
#define   EN_INT          0x02
#define   EN_INT2         0x03
#define   MNGR_INT        0x04
#define   MNGR_DYN        0x05
#define   SW_RST          0x08
#define   SYNCH           0x09
#define   FIFO_RST        0x0A
#define   INFO            0x0F
#define   CNFG_GEN        0x10
#define   CNFG_CAL        0x12
#define   CNFG_EMUX       0x14
#define   CNFG_ECG        0x15
#define   CNFG_BMUX       0x17
#define   CNFG_BIOZ       0x18
#define   CNFG_PACE       0x1A
#define   CNFG_RTOR1      0x1D
#define   CNFG_RTOR2      0x1E
#define   ECG_FIFO_BURST  0x20
#define   ECG_FIFO        0x21
#define   BIOZ_FIFO_BURST 0x22
#define   BIOZ_FIFO       0x23
#define   RTOR            0x25
#define   PACE0_BURST     0x30
#define   PACE0_A         0x31
#define   PACE0_B         0x32
#define   PACE0_C         0x33
#define   PACE1_BURST     0x34
#define   PACE1_A         0x35
#define   PACE1_B         0x36
#define   PACE1_C         0x37
#define   PACE2_BURST     0x38
#define   PACE2_A         0x39
#define   PACE2_B         0x3A
#define   PACE2_C         0x3B
#define   PACE3_BURST     0x3C
#define   PACE3_A         0x3D
#define   PACE3_B         0x3E
#define   PACE3_C         0x3F
#define   PACE4_BURST     0x40
#define   PACE4_A         0x41
#define   PACE4_B         0x42
#define   PACE4_C         0x43
#define   PACE5_BURST     0x44
#define   PACE5_A         0x45
#define   PACE5_B         0x46
#define   PACE5_C         0x47
#define   NO_OP           0x7F

#define MAX30001_CS_PIN   7
#define CLK_PIN           6
#define RTOR_INTR_MASK    0x04

typedef enum
{
  SAMPLINGRATE_128 = 128, 
  SAMPLINGRATE_256 = 256, 
  SAMPLINGRATE_512 = 512
}sampRate;

class MAX30001
{
  public:
  	unsigned int heartRate;
  	unsigned int RRinterval;
  	signed long ecgdata;
    signed long biozdata;

    void max30001Begin();
    void max30001BeginRtorMode();
    void max30001SwReset(void);
    void getHRandRR(void);
    void getEcgSamples(void);
    void getBioZSamples(void);
    bool max30001ReadInfo(void);
    void max30001SetsamplingRate(uint16_t samplingRate);
    void max30001RegRead(uint8_t Reg_address, uint8_t * buff);

  private:

    void max30001ReadData(int num_samples, uint8_t * readBuffer);

    void max30001Synch(void);
    void max30001RegWrite (unsigned char WRITE_ADDRESS, unsigned long data);
};

#endif
