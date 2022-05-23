/**
  * @file    tm1637.c
  * @brief   TM1637 7-segment display driver
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "stm32.h"
#include "tm1637.h"


/*******************************************************************************
* PRIVATE DEFINES
*******************************************************************************/
#define TM1637_CMD_WRITE        0x22
#define TM1637_CMD_WRITE_AUTO   0x02
#define TM1637_CMD_READ         0x62
#define TM1637_CMD_READ_AUTO    0x42

/*******************************************************************************
* PRIVATE CONSTANTS
*******************************************************************************/
static  uint8_t const   encode[16]  = TM1637_ENC_TBL16;

/*******************************************************************************
* PRIVATE FUNCTIONS
*******************************************************************************/

/*******************************************************************************
* PUBLIC FUNCTIONS
*******************************************************************************/
void
tm1637_init( void )
{
    tm1637_x_stop_cond();

    tm1637_display_fill( ENC_ALL );
    tm1637_set_brightness( TM1637_BRIGHTNESS_MAX );
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void
tm1637_display_clear( void )
{
    tm1637_display_fill( ENC_NONE );
}


void
tm1637_display_fill(    uint8_t     d )
{
    tm1637_x_write_byte( 1, 1, TM1637_CMD_WRITE_AUTO );

    tm1637_x_write_byte( 1, 0, TM1637_ADDR_0 );
    tm1637_x_write_byte( 0, 0, d );
    tm1637_x_write_byte( 0, 0, d );
    tm1637_x_write_byte( 0, 0, d );
    tm1637_x_write_byte( 0, 0, d );
    tm1637_x_write_byte( 0, 0, d );
    tm1637_x_write_byte( 0, 1, d );
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void
tm1637_set_brightness(                   tm1637_brightness_t    d )
{
    tm1637_x_write_byte( 1, 1, d );
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void
tm1637_set_digit(                   const   tm1637_addr_t   addr,
                                    const   uint8_t         d )
{
    tm1637_x_write_byte( 1, 1, TM1637_CMD_WRITE );

    tm1637_x_write_byte( 1, 0, addr );
    tm1637_x_write_byte( 0, 1, encode[d & 0xF]);
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void
tm1637_string(                          char *      str,
                                        size_t      len )
{
    //tm1637_x_write_byte( 1, 1, d );
}

void
tm1637_write_string(                    char *              s )
{

}
