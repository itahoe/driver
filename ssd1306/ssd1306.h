/**
  * @file    ssd1306.h
  * @brief   Display Controller Driver
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef SSD1306_H
#define SSD1306_H


#include "ssd1306_fonts.h"
#include <string.h>
#include <stdbool.h>


/*******************************************************************************
* GLOBAL CONSTANTS
*******************************************************************************/
#define SSD1306_SEG_MAX                 128
#define SSD1306_COM_MAX                 64

#define SSD1306_COL_MAX                 128
#define SSD1306_PAGE_MAX                8
#define SSD1306_PIXEL_PER_PAGE          8


//#define SSD1306_INIT_091_128x32         0x00,0xA8,0x3F,0xD3,0x00,0x40,0xA0,0xC0,0xDA,0x02,0x81,0x7F,0xA4,0xD5,0x00,0x8D,0x14,0xAF,0x00,0x10,0x20,0x02,0x21,0x00,0x7F,0xB0,0xA6,
#define SSD1306_INIT_WEO012832F         0x00,0xA8,0x3F,0xD3,0x00,0x40,0xA0,0xC0,0xDA,0x02,0x81,0x7F,0xA4,0xD5,0x00,0x8D,0x14,0xAF,0x00,0x10,0x20,0x02,0x21,0x00,0x7F,0xB0,0xA6,

#define SSD1306_INIT_091_128x32         0x00,\
                                        SSD1306_CMD_MUX_RATIO,0x3F,\
                                        SSD1306_CMD_DISPLAY_OFFSET,0x00,\
                                        SSD1306_CMD_START_LINE0,\
                                        SSD1306_CMD_SEGMENT_REMAP | 0x00,\
                                        SSD1306_CMD_COM_SCAN_DIRECTION | 0x00,\
                                        SSD1306_CMD_CONFIG_COM_PINS,0x02,\
                                        SSD1306_CMD_CONTRAST,0x7F,\
                                        SSD1306_CMD_ENTIRE_DISPLAY_ON,\
                                        SSD1306_CMD_INVERSE_NONE,\
                                        SSD1306_CMD_CF_CLKDIV_OSCFREQ,0x80,\
                                        SSD1306_CMD_CHARGE_PUMP,0x14,\
                                        SSD1306_CMD_DISPLAY_ON,\
/*
                                        \
                                        SSD1306_CMD_ADDR_COLUMN_LO_START,\
                                        SSD1306_CMD_ADDR_COLUMN_HI_START,\
                                        SSD1306_CMD_ADDR_MODE,SSD1306_ADDR_MODE_PAGE,\
                                        SSD1306_CMD_ADDR_COLUMN,0x00,0x7F,\
                                        SSD1306_CMD_ADDR_GRAM_PAGE0,
*/

/*******************************************************************************
*
*******************************************************************************/
typedef enum    ssd1306_cmd_e
{
    SSD1306_CMD_CONTRAST                = 0x81,
    //SSD1306_CMD_ENTIRE_DISPLAY_OFF      = 0xA4,
    SSD1306_CMD_ENTIRE_DISPLAY_ON       = 0xA4,
    SSD1306_CMD_INVERSE_NONE            = 0xA6,
    SSD1306_CMD_INVERSE_ON              = 0xA7,
    SSD1306_CMD_DISPLAY_OFF             = 0xAE,
    SSD1306_CMD_DISPLAY_ON              = 0xAF,
    SSD1306_CMD_SCROLL_HRIGHT           = 0x26,
    SSD1306_CMD_SCROLL_HLEFT            = 0x27,
    SSD1306_CMD_SCROLL_VHRIGHT          = 0x29,
    SSD1306_CMD_SCROLL_VHLEFT           = 0x2A,
    SSD1306_CMD_SCROLL_STOP             = 0x2E,
    SSD1306_CMD_SCROLL_START            = 0x2F,
    SSD1306_CMD_VSCROLL_AREA            = 0xA3,
    SSD1306_CMD_ADDR_COLUMN_LO_START    = 0x00,
    //SSD1306_CMD_COLL_00_START_ADDR      = 0x00,
    //SSD1306_CMD_COLL_01_START_ADDR      = 0x01,
    //SSD1306_CMD_COLL_02_START_ADDR      = 0x02,
    //SSD1306_CMD_COLL_03_START_ADDR      = 0x03,
    //SSD1306_CMD_COLL_04_START_ADDR      = 0x04,
    //SSD1306_CMD_COLL_05_START_ADDR      = 0x05,
    //SSD1306_CMD_COLL_06_START_ADDR      = 0x06,
    //SSD1306_CMD_COLL_07_START_ADDR      = 0x07,
    //SSD1306_CMD_COLL_08_START_ADDR      = 0x08,
    //SSD1306_CMD_COLL_09_START_ADDR      = 0x09,
    //SSD1306_CMD_COLL_10_START_ADDR      = 0x0A,
    //SSD1306_CMD_COLL_11_START_ADDR      = 0x0B,
    //SSD1306_CMD_COLL_12_START_ADDR      = 0x0C,
    //SSD1306_CMD_COLL_13_START_ADDR      = 0x0D,
    //SSD1306_CMD_COLL_14_START_ADDR      = 0x0E,
    //SSD1306_CMD_COLL_15_START_ADDR      = 0x0F,
    SSD1306_CMD_ADDR_COLUMN_HI_START    = 0x10,
    //SSD1306_CMD_COLH_00_START_ADDR      = 0x10,
    //SSD1306_CMD_COLH_01_START_ADDR      = 0x11,
    //SSD1306_CMD_COLH_02_START_ADDR      = 0x12,
    //SSD1306_CMD_COLH_03_START_ADDR      = 0x13,
    //SSD1306_CMD_COLH_04_START_ADDR      = 0x14,
    //SSD1306_CMD_COLH_05_START_ADDR      = 0x15,
    //SSD1306_CMD_COLH_06_START_ADDR      = 0x16,
    //SSD1306_CMD_COLH_07_START_ADDR      = 0x17,
    //SSD1306_CMD_COLH_08_START_ADDR      = 0x18,
    //SSD1306_CMD_COLH_09_START_ADDR      = 0x19,
    //SSD1306_CMD_COLH_10_START_ADDR      = 0x1A,
    //SSD1306_CMD_COLH_11_START_ADDR      = 0x1B,
    //SSD1306_CMD_COLH_12_START_ADDR      = 0x1C,
    //SSD1306_CMD_COLH_13_START_ADDR      = 0x1D,
    //SSD1306_CMD_COLH_14_START_ADDR      = 0x1E,
    //SSD1306_CMD_COLH_15_START_ADDR      = 0x1F,
    SSD1306_CMD_ADDR_MODE               = 0x20,
    SSD1306_CMD_ADDR_COLUMN             = 0x21,
    SSD1306_CMD_ADDR_PAGE_SETUP         = 0x22,
    SSD1306_CMD_ADDR_GRAM_PAGE0         = 0xB0,
    //SSD1306_CMD_PAGE0_START_ADDR        = 0xB0,
    //SSD1306_CMD_PAGE1_START_ADDR        = 0xB1,
    //SSD1306_CMD_PAGE2_START_ADDR        = 0xB2,
    //SSD1306_CMD_PAGE3_START_ADDR        = 0xB3,
    //SSD1306_CMD_PAGE4_START_ADDR        = 0xB4,
    //SSD1306_CMD_PAGE5_START_ADDR        = 0xB5,
    //SSD1306_CMD_PAGE6_START_ADDR        = 0xB6,
    //SSD1306_CMD_PAGE7_START_ADDR        = 0xB7,
    SSD1306_CMD_START_LINE0             = 0x40,
    SSD1306_CMD_SEGMENT_REMAP           = 0xA0,
    //SSD1306_CMD_SEGMENT_REMAP_TO_127    = 0xA1,
    SSD1306_CMD_MUX_RATIO               = 0xA8,
    SSD1306_CMD_COM_SCAN_DIRECTION      = 0xC0,
    //SSD1306_CMD_COM_SCAN_NORMAL         = 0xC0,
    //SSD1306_CMD_COM_SCAN_REMAPPED       = 0xC8,
    SSD1306_CMD_DISPLAY_OFFSET          = 0xD3,
    SSD1306_CMD_CONFIG_COM_PINS         = 0xDA,
    SSD1306_CMD_CF_CLKDIV_OSCFREQ       = 0xD5,
    SSD1306_CMD_PRECHARGE_PERIOD        = 0xD9,
    SSD1306_CMD_VCOMH_DESELECT_LEVEL    = 0xDB,
    SSD1306_CMD_NOP                     = 0xE3,
    SSD1306_CMD_CHARGE_PUMP             = 0x8D,
} ssd1306_cmd_t;

typedef enum    ssd1306_scroll_speed_e
{
    SSD1306_SCROLL_SPEED_5              = 0x00,
    SSD1306_SCROLL_SPEED_64             = 0x01,
    SSD1306_SCROLL_SPEED_128            = 0x02,
    SSD1306_SCROLL_SPEED_256            = 0x03,
    SSD1306_SCROLL_SPEED_3              = 0x04,
    SSD1306_SCROLL_SPEED_4              = 0x05,
    SSD1306_SCROLL_SPEED_25             = 0x06,
    SSD1306_SCROLL_SPEED_2              = 0x07,
} ssd1306_scroll_speed_t;

typedef enum    ssd1306_addr_mode_e
{
    SSD1306_ADDR_MODE_HORIZONTAL        = 0x00,
    SSD1306_ADDR_MODE_VERTICAL          = 0x01,
    SSD1306_ADDR_MODE_PAGE              = 0x02,
} ssd1306_addr_mode_t;

typedef enum    ssd1306_color_e
{
    SSD1306_COLOR_BLACK     = 0x00,
    SSD1306_COLOR_WHITE     = 0xFF,
} ssd1306_color_t;
/*
typedef struct
{
    size_t      i2c_addr;
    size_t      width;
    size_t      height;
    size_t      buf_sizeof;
    bool        mirror_v;
    bool        mirror_h;
} ssd1306_conf_t;
*/
/*
typedef struct
{
    const   ssd1306_conf_t *    conf;
            uint8_t *           gram;
            ssd1306_color_t     color;
    const   ssd1306_font_t *    font;
            uint16_t            x;
            uint16_t            y;
} ssd1306_t;
*/
/*******************************************************************************
* FUNCTION PROTOTYPES
*******************************************************************************/
void    ssd1306_x_write( uint8_t *, size_t );
void    ssd1306_x_reset( void );
void    ssd1306_x_delay_msec( const uint32_t );

void    ssd1306_set_contrast( uint8_t );
void    ssd1306_set_entire_display_on( const bool );
void    ssd1306_set_inverse( const bool );
void    ssd1306_set_display_on( const bool );

void    ssd1306_scroll_hright( const uint8_t, const uint8_t, const ssd1306_scroll_speed_t );
void    ssd1306_scroll_hleft( const uint8_t, const uint8_t, const ssd1306_scroll_speed_t );
void    ssd1306_scroll_vhright( const uint8_t, const uint8_t, const ssd1306_scroll_speed_t, const uint8_t );
void    ssd1306_scroll_vhleft( const uint8_t, const uint8_t, const ssd1306_scroll_speed_t, const uint8_t );
void    ssd1306_scroll_stop( void );
void    ssd1306_scroll_start( void );
void    ssd1306_scroll_varea( const uint8_t, const uint8_t );

void    ssd1306_addr_column_lo_start( const uint8_t );
void    ssd1306_addr_column_hi_start( const uint8_t );
void    ssd1306_addr_mode( const ssd1306_addr_mode_t );
void    ssd1306_addr_column( const uint8_t, const uint8_t );
void    ssd1306_addr_page_setup( const   uint8_t, const uint8_t );
void    ssd1306_addr_gram_page( const uint8_t );

void    ssd1306_hw_start_line( const uint8_t );
void    ssd1306_hw_hmirror( const bool );
void    ssd1306_hw_mux_ratio( const uint8_t );
void    ssd1306_hw_vmirror( const bool );
void    ssd1306_hw_vshift( const uint8_t );
void    ssd1306_hw_com_pins( const bool, const bool );

void    ssd1306_cfg_clkdiv_freq( const uint8_t, const uint8_t );
void    ssd1306_cfg_precharge_period( const uint8_t, const uint8_t );
void    ssd1306_cfg_vcomh_desel_level( const uint8_t );

void    ssd1306_charge_pump_enable( const bool );

void    ssd1306_cmd_raw( const uint8_t, const uint8_t );


//void    ssd1306_init( ssd1306_t * );

//GUI
char *  ssd1306_putstr( uint8_t *, uint8_t, uint8_t, const ssd1306_font_t *, char * );



//void    ssd1306_update( ssd1306_t * );
//void    ssd1306_set_position( ssd1306_t *, const uint8_t, const uint8_t );
//void    ssd1306_draw_pixel( ssd1306_t *, const uint8_t, const uint8_t, const ssd1306_color_t );
//void    ssd1306_fill( ssd1306_t *, const ssd1306_color_t );
//char    ssd1306_putc( ssd1306_t *, const char );
//char    ssd1306_puts( ssd1306_t *, const char * );
//void    ssd1306_set_font( ssd1306_t *, const ssd1306_font_t * );
//void    ssd1306_set_color( ssd1306_t *, const ssd1306_color_t );


#endif	//SSD1306_H
