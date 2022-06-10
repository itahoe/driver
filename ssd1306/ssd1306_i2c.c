/**
  * @file    ssd1306.c
  * @brief   Display Controller Driver
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "ssd1306.h"


/*******************************************************************************
* PRIVATE VARIABLES
*******************************************************************************/

/*******************************************************************************
* PRIVATE FUNCTIONS
*******************************************************************************/
static
void
ssd1306_reset( void )
{
    ssd1306_x_reset_force();
    ssd1306_x_delay_msec( 10 );
    ssd1306_x_reset_release();
    ssd1306_x_delay_msec( 100 );
}

/*******************************************************************************
*
*******************************************************************************/
void
ssd1306_init(                           ssd1306_t *         p,
                                        uint8_t *           buf,
                                        uint8_t *           gram )
{
    p->buf  = buf;
    p->gram = gram;

    ssd1306_reset();

    //ssd1306_x_cmd( 0x20, &(p->hw->mem_addr_mode), 1 );   //Set Memory Addressing Mode   
    //ssd1306_x_cmd( 0x10, (void *) NULL, 0 );   // 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode; 10,Page Addressing Mode (RESET); 11,Invalid

    //ssd1306_x_cmd( 0xB0, (void *) NULL, 0 );   //Set Page Start Address for Page Addressing Mode,0-7
    p->buf[ 0]  = 0x00; //Set Page Start Address for Page Addressing Mode,0-7
    p->buf[ 1]  = SSD1306_CMD_PAGE_START_ADDR; //Set Page Start Address for Page Addressing Mode,0-7
    p->len      = 2;
    ssd1306_x_write( p->buf, p->len );

    //#ifdef SSD1306_MIRROR_VERT
    //ssd1306_x_command( 0xC0 );   // Mirror vertically
    //#else
    //ssd1306_x_command( 0xC8 );   //Set COM Output Scan Direction
    //#endif

    //ssd1306_x_cmd( 0x00, (void *) NULL, 0 );   //---set low column address
    p->buf[ 0]  = 0x00; //Set Page Start Address for Page Addressing Mode,0-7
    p->buf[ 1]  = SSD1306_CMD_COLUMN_LO_START_ADDR; //Set Page Start Address for Page Addressing Mode,0-7
    p->len      = 2;
    ssd1306_x_write( p->buf, p->len );


    //ssd1306_x_cmd( 0x10, (void *) NULL, 0 );   //---set high column address
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = SSD1306_CMD_COLUMN_HI_START_ADDR;
    p->len      = 2;
    ssd1306_x_write( p->buf, p->len );


    //ssd1306_x_cmd( 0x40, (void *) NULL, 0 );   //--set start line address - CHECK
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = SSD1306_CMD_START_LINE_00;
    p->len      = 2;
    ssd1306_x_write( p->buf, p->len );

    //ssd1306_x_cmd( SSD1306_CMD_MUX_RATIO, &( p->hw->mux_ratio ), 1 );   //--set multiplex ratio(1 to 64) - CHECK
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = SSD1306_CMD_MUX_RATIO;
    p->len      = 2;
    ssd1306_x_write( p->buf, p->len );


    //ssd1306_x_cmd( 0xA4, (void *) NULL, 0 );   //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    //ssd1306_x_cmd( 0xD3, (void *) NULL, 0 );   //-set display offset - CHECK
    //ssd1306_x_cmd( 0x00, (void *) NULL, 0 );   //-not offset

    //ssd1306_x_cmd( 0xD5, (void *) NULL, 0 );   //--set display clock divide ratio/oscillator frequency
    //ssd1306_x_cmd( 0xF0, (void *) NULL, 0 );   //--set divide ratio
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = SSD1306_CMD_CLOCK_DIV_RATIO;
    p->buf[ 2]  = 0xF0;
    p->len      = 3;
    ssd1306_x_write( p->buf, p->len );

    //ssd1306_x_cmd( 0xD9, (void *) NULL, 0 );   //--set pre-charge period
    //ssd1306_x_cmd( 0x22, (void *) NULL, 0 );   //
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = SSD1306_CMD_PRECHARGE_PERIOD;
    p->buf[ 2]  = 0x22;
    p->len      = 3;
    ssd1306_x_write( p->buf, p->len );

    //ssd1306_x_cmd( 0xDA, (void *) NULL, 0 );   //--set com pins hardware configuration - CHECK
    //ssd1306_x_cmd( 0x12, (void *) NULL, 0 );
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = SSD1306_CMD_COM_PINS_CONFIG;
    p->buf[ 2]  = 0x12;
    p->len      = 3;
    ssd1306_x_write( p->buf, p->len );

    //ssd1306_x_cmd( 0xDB, (void *) NULL, 0 );   //--set vcomh
    //ssd1306_x_cmd( 0x20, (void *) NULL, 0 );   //0x20,0.77xVcc
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = SSD1306_CMD_VCOMH_DESELECT_LEVEL;
    p->buf[ 2]  = 0x20;
    p->len      = 3;
    ssd1306_x_write( p->buf, p->len );

    //ssd1306_x_cmd( 0x8D, (void *) NULL, 0 );   //--set DC-DC enable
    //ssd1306_x_cmd( 0x14, (void *) NULL, 0 );   //
    p->buf[ 0]  = 0x00;
    p->buf[ 1]  = 0x8D;
    p->buf[ 2]  = 0x14;
    p->len      = 3;
    ssd1306_x_write( p->buf, p->len );


    ssd1306_fill( p, SSD1306_COLOR_WHITE );
    ssd1306_update( p );

    p->x    = 0;
    p->y    = 0;
}

/*******************************************************************************
* CONFIG
*******************************************************************************/

/*******************************************************************************
* CMD
*******************************************************************************/
void
ssd1306_set_contrast(                   uint8_t             arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) SSD1306_CMD_CONTRAST, arg };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_sleep(              const   bool                arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) (arg ?  SSD1306_CMD_DISPLAY_ON : SSD1306_CMD_DISPLAY_OFF) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_mirror_v(           const   bool                arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) (arg ?  SSD1306_CMD_COM_SCAN_REMAPPED : SSD1306_CMD_COM_SCAN_NORMAL) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_mirror_h(           const   bool                arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) (arg ?  SSD1306_CMD_SEGMENT_REMAP_TO_127 : SSD1306_CMD_SEGMENT_REMAP_TO_0) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_inverse(            const   bool                arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) (arg ?  SSD1306_CMD_COLOR_INVERSE : SSD1306_CMD_COLOR_NORMAL) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_addr_mode(          const   ssd1306_addr_mode_t mode )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) SSD1306_CMD_MEM_ADDR_MODE, (uint8_t) mode };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_page_start_addr(    const   uint8_t             arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) (SSD1306_CMD_PAGE_START_ADDR + arg) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_column_lo_start_addr(   const   uint8_t             arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) (SSD1306_CMD_COLUMN_LO_START_ADDR + arg) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_column_hi_start_addr(   const   uint8_t             arg )
{
    uint8_t     buf[]   = { 0x00, (uint8_t) (SSD1306_CMD_COLUMN_HI_START_ADDR + arg) };
    ssd1306_x_write( buf, sizeof(buf) );
}


/*******************************************************************************
* PUBLIC FUNCTIONS
*******************************************************************************/
/*
void
ssd1306_cmd(                            
                                        ssd1306_t *         p,
                                        //uint8_t *           buf,
                                        ssd1306_cmd_t       cmd,
                                        uint8_t *           arg,
                                        size_t              arglen )
{
    p->len      = 2;
    *(p->buf++) = 0x00;
    *(p->buf++) = (uint8_t) cmd;

    while( arglen-- )
    {
        *(p->buf++) = *arg++;
        p->len++;
    }

    ssd1306_x_write( p->buf, p->len );
}
*/
/*******************************************************************************
* OPERATE
*******************************************************************************/
void
ssd1306_fill(                           ssd1306_t *     p,
                                const   ssd1306_color_t color )
{
    //for( int i = 0; i < sizeof(ssd1306_buffer); i++ )
    for( int i = 0; i < p->conf->buf_sizeof - 1; i++ )
    {
        p->gram[ i ] = (color == SSD1306_COLOR_BLACK ) ? 0x00 : 0xFF;
    }
}


void
ssd1306_draw_pixel(                 ssd1306_t *             p, 
                                    const   uint8_t         x,      //horizontal position
                                    const   uint8_t         y,      //vertical position
                                    const   ssd1306_color_t color )
{
    if( x >= p->conf->width || y >= p->conf->height )
    {
        return;
    }

    if( color == SSD1306_COLOR_WHITE )
    {
        p->gram[x + (y / 8) * p->conf->width] |= 1 << (y % 8);
    }
    else
    {
        p->gram[x + (y / 8) * p->conf->width] &= ~(1 << (y % 8));
    }
}


// Draw 1 char to the screen buffer
// c            => char om weg te schrijven
// Font         => Font waarmee we gaan schrijven
// color        => Black or White
char
ssd1306_putc(                                   ssd1306_t *     p,
                                        const   char            c )
{
    uint32_t        i, b, j;


    if( p->conf->width  <= (p->x + p->font->width) ||
        p->conf->height <= (p->y + p->font->height)     )
    {
        return 0;
    }

    for( i = 0; i < p->font->height; i++ )
    {
        b   = p->font->data[(c - 32) * p->font->height + i];

        for( j = 0; j < p->font->width; j++ )
        {
            if( (b << j) & 0x8000 )
            {
                ssd1306_draw_pixel( p, p->x + j, (p->y + i), (ssd1306_color_t)  p->color );
            }
            else
            {
                ssd1306_draw_pixel(p, p->x + j, (p->y + i), (ssd1306_color_t) !(p->color) );
            }
        }
    }

    p->x    += p->font->width;

    return( c );
}


char
ssd1306_puts(                                   ssd1306_t *     p,
                                        const   char *          str )
{
    

    while( *str )
    {
        if( ssd1306_putc( p, *str ) != *str )
        {
            return( *str );
        }
        
        str++;
    }
    
    return( *str );
}

/*******************************************************************************
*
*******************************************************************************/
void
ssd1306_set_position(                           ssd1306_t *     p,
                                        const   uint8_t         x,
                                        const   uint8_t         y )
{
    p->x    = x;
    p->y    = y;
}


void
ssd1306_set_color(                              ssd1306_t *         p,
                                        const   ssd1306_color_t     color )
{
    p->color    = color;
}


void
ssd1306_set_font(                               ssd1306_t *         p,
                                        const   ssd1306_font_t *    font )
{
    p->font = font;
}

/*******************************************************************************
*
*******************************************************************************/
void
ssd1306_update(                         ssd1306_t *     p )
{
    uint8_t     buf[ 8];
    size_t      len;

    for( uint8_t i = 0; i < 8; i++ )
    {
        //ssd1306_x_cmd( 0xB0 + i, (void *) NULL, 0 );
        buf[ 0]  = 0x00;
        buf[ 1]  = (uint8_t) SSD1306_CMD_PAGE_START_ADDR + i;
        len      = 2;
        ssd1306_x_write( buf, len );

        //ssd1306_set_page_start_addr( p, i );


        //ssd1306_x_cmd( 0x00, (void *) NULL, 0 );
        buf[ 0]  = 0x00;
        buf[ 1]  = (uint8_t) SSD1306_CMD_COLUMN_LO_START_ADDR;
        len      = 2;
        ssd1306_x_write( buf, len );

        //ssd1306_x_cmd( 0x10, (void *) NULL, 0 );
        buf[ 0]  = 0x00;
        buf[ 1]  = (uint8_t) SSD1306_CMD_COLUMN_HI_START_ADDR;
        len      = 2;
        ssd1306_x_write( buf, len );

        //ssd1306_x_data( &p->buf[ p->conf->width*i ], p->conf->width );
        p->gram[ 0]  = 0x40;
        ssd1306_x_write( &p->gram[ p->conf->width*i ], 1 + p->conf->width );
        //ssd1306_x_write( p->gram, p->conf->buf_sizeof );
    }
}
