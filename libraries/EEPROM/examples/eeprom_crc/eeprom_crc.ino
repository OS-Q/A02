/*******************************************************************************
****版本：V1.0.0
****平台：stm8s
****日期：2021-05-20
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include <Arduino.h>
#include <EEPROM.h>

unsigned long eeprom_crc(void);

void setup()
{
  //Start serial
  Serial_begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Print length of data to run CRC on.
  Serial_print_s("EEPROM length: ");
  Serial_println_u(EEPROM_length());

  //Print the result of calling eeprom_crc()
  Serial_print_s("CRC32 of EEPROM data: 0x");
  Serial_println_ub(eeprom_crc(), HEX);
  Serial_print_s("\n\nDone!");
}

void loop()
{
  /* Empty loop */
}

unsigned long eeprom_crc(void) {

static  const unsigned long crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
  };

  unsigned long crc = ~0UL;

  for (int index = 0 ; index < EEPROM_length()  ; ++index) {
    crc = crc_table[(crc ^ EEPROM_cell[index]) & 0x0f] ^ (crc >> 4);
    crc = crc_table[(crc ^ (EEPROM_cell[index] >> 4)) & 0x0f] ^ (crc >> 4);
    crc = ~crc;
  }
  return crc;
}

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
