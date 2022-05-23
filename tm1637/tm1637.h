/**
  * @file    tm1637.h
  * @brief   TM1637 driver header
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef TM1637_H
#define TM1637_H


//#include <stdio.h>
#include <stdint.h>


/*******************************************************************************
* TM1637 interface is very similar to I2C, but has some difference:
* - TM1637 does not support device addressing
* - TM1637 IF provides a different bits order, LSB first (unlike MSB in I2C)
*******************************************************************************/


typedef enum    tm1637_brightness_e
{
    TM1637_BRIGHTNESS_0         = 0x01,
    TM1637_BRIGHTNESS_1         = 0x11,
    TM1637_BRIGHTNESS_2         = 0x91,
    TM1637_BRIGHTNESS_3         = 0x51,
    TM1637_BRIGHTNESS_4         = 0xD1,
    TM1637_BRIGHTNESS_5         = 0x31,
    TM1637_BRIGHTNESS_6         = 0xB1,
    TM1637_BRIGHTNESS_7         = 0x71,
    TM1637_BRIGHTNESS_MAX       = 0xF1,
} tm1637_brightness_t;

typedef enum    tm1637_addr_e
{
    TM1637_ADDR_0               = 0x03,
    TM1637_ADDR_1               = 0x83,
    TM1637_ADDR_2               = 0x43,
    TM1637_ADDR_3               = 0xC3,
    TM1637_ADDR_4               = 0x23,
    TM1637_ADDR_5               = 0xA3,
} tm1637_addr_t;


#define SEG_A                   0x80
#define SEG_B                   0x40
#define SEG_C                   0x20
#define SEG_D                   0x10
#define SEG_E                   0x08
#define SEG_F                   0x04
#define SEG_G                   0x02
#define SEG_H                   0x01

#define ENC_0                   (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define ENC_1                   (SEG_B|SEG_C)
#define ENC_2                   (SEG_A|SEG_B|SEG_D|SEG_E|SEG_G)
#define ENC_3                   (SEG_A|SEG_B|SEG_C|SEG_D|SEG_G)
#define ENC_4                   (SEG_B|SEG_C|SEG_F|SEG_G)
#define ENC_5                   (SEG_A|SEG_C|SEG_D|SEG_F|SEG_G)
#define ENC_6                   (SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define ENC_7                   (SEG_A|SEG_B|SEG_C)
#define ENC_8                   (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define ENC_9                   (SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G)
#define ENC_A                   (SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G)
#define ENC_B                   (SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define ENC_C                   (SEG_A|SEG_D|SEG_E|SEG_F)
#define ENC_D                   (SEG_B|SEG_C|SEG_D|SEG_E|SEG_G)
#define ENC_E                   (SEG_A|SEG_D|SEG_E|SEG_F|SEG_G)
#define ENC_F                   (SEG_A|SEG_E|SEG_F|SEG_G)
#define ENC_MINUS               (SEG_G)
#define ENC_POINT               (SEG_H)
#define ENC_NONE                (0)
#define ENC_ALL                 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G|SEG_H)

#define TM1637_ENC_TBL16_1      { ENC_0, ENC_1, ENC_2, ENC_3, ENC_4, ENC_5, ENC_6, ENC_7, ENC_8, ENC_9, ENC_A, ENC_B, ENC_C, ENC_D, ENC_E, ENC_F, }
#define TM1637_ENC_TBL16_2      { ENC_0, ENC_1, ENC_2, ENC_3, ENC_4, ENC_5, ENC_6, ENC_7, ENC_8, ENC_9, ENC_MINUS, ENC_NONE, ENC_NONE, ENC_NONE, ENC_NONE, ENC_NONE, }

#define TM1637_ENC_TBL16        TM1637_ENC_TBL16_2

/*******************************************************************************
* FUNCTIONS PROTOTYPE
*******************************************************************************/
void    tm1637_init( void );
void    tm1637_display_clear( void );
void    tm1637_display_fill( uint8_t );
void    tm1637_set_brightness( tm1637_brightness_t );
void    tm1637_set_digit( const tm1637_addr_t, const uint8_t );

void    tm1637_write_string( char * );

void    tm1637_x_stop_cond( void );
int     tm1637_x_write_byte( int, int, uint8_t );


#endif	// TM1637_H
