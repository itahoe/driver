/**
  * @file    tm1637.c
  * @brief   TM1637 7-segment display driver
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <ctype.h>
#include "stm32.h"
#include "tm1637.h"
//#include "tm1637_x_i2c.h"

extern  const   uint8_t tm1637_x_addr[TM1637_CHNL_MAX];

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
    tm1637_display_fill( ENC_BLANK );
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
tm1637_write_string(                    char *              s )
{
    uint8_t     symb[ TM1637_CHNL_MAX ];
    size_t      cnt;


    for( cnt = 0; cnt < TM1637_CHNL_MAX; cnt++ )
    {
        if( *s == NULL )
        {
            break;
        }

        if( isdigit( *s ) )
        {
            symb[cnt]    = encode[ (*s-'0') & 0xF ];

            if( *(++s) == '.' )
            {
                symb[cnt]   |= SEG_H;
                s++;
            }
        }
        else if( isspace( *s ) )
        {
            symb[cnt]    = ENC_BLANK;
            s++;
        }

    }

    for( int i = 0; i < cnt; i++ )
    {
        tm1637_x_write_byte( 1, 1, TM1637_CMD_WRITE );
        tm1637_x_write_byte( 1, 0, tm1637_x_addr[i] );
        tm1637_x_write_byte( 0, 1, symb[i]  );
    }
}
