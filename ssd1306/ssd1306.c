/**
  * @file    ssd1306.c
  * @brief   SSD1306 Display Controller Driver
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "ssd1306.h"


/*******************************************************************************
* Fundamental
*******************************************************************************/
void
ssd1306_set_contrast(                   const   uint8_t         arg )
{
    uint8_t     cmd     = SSD1306_CMD_CONTRAST;
    uint8_t     buf[] = { 0x00, cmd, arg };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_entire_display_on(          const   bool            arg )
{
    uint8_t cmd     = SSD1306_CMD_ENTIRE_DISPLAY_ON | (arg ? 0x00 : 0x01);
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_inverse(                    const   bool            arg )
{
    uint8_t cmd     = arg ? SSD1306_CMD_INVERSE_ON : SSD1306_CMD_INVERSE_NONE;
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_set_display_on(         const   bool                    arg )
{
    uint8_t cmd     = arg ? SSD1306_CMD_DISPLAY_ON : SSD1306_CMD_DISPLAY_OFF;
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

/*******************************************************************************
* Scrolling
*******************************************************************************/
void
ssd1306_scroll_hright(          const   uint8_t                 page_start,
                                const   uint8_t                 page_end,
                                const   ssd1306_scroll_speed_t  speed )
{
    uint8_t cmd     = SSD1306_CMD_SCROLL_HRIGHT;
    uint8_t buf[]   = { 0x00, cmd, 0x00, page_start, speed, page_end, 0x00, 0xFF };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_scroll_hleft(           const   uint8_t                 page_start,
                                const   uint8_t                 page_end,
                                const   ssd1306_scroll_speed_t  speed )
{
    uint8_t cmd     = SSD1306_CMD_SCROLL_HLEFT;
    uint8_t buf[]   = { 0x00, cmd, 0x00, page_start, speed, page_end, 0x00, 0xFF };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_scroll_vhright(         const   uint8_t                 page_start,
                                const   uint8_t                 page_end,
                                const   ssd1306_scroll_speed_t  speed,
                                const   uint8_t                 voffset )
{
    uint8_t cmd     = SSD1306_CMD_SCROLL_VHRIGHT;
    uint8_t buf[]   = { 0x00, cmd, 0x00, page_start, speed, page_end, voffset };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_scroll_vhleft(          const   uint8_t                 page_start,
                                const   uint8_t                 page_end,
                                const   ssd1306_scroll_speed_t  speed,
                                const   uint8_t                 voffset )
{
    uint8_t cmd     = SSD1306_CMD_SCROLL_VHLEFT;
    uint8_t buf[]   = { 0x00, cmd, 0x00, page_start, speed, page_end, voffset };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_scroll_stop( void )
{
    uint8_t cmd     = SSD1306_CMD_SCROLL_STOP;
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_scroll_start( void )
{
    uint8_t cmd     = SSD1306_CMD_SCROLL_START;
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_scroll_varea(           const   uint8_t             rows_num_fixed,
                                const   uint8_t             rows_num_scroll )
{
    uint8_t cmd     = SSD1306_CMD_VSCROLL_AREA;
    uint8_t buf[]   = { 0x00, cmd, rows_num_fixed, rows_num_scroll };
    ssd1306_x_write( buf, sizeof(buf) );
}

/*******************************************************************************
* Addressing Setting
*******************************************************************************/
void
ssd1306_addr_column_lo_start(   const   uint8_t             arg )
{
    uint8_t cmd     = SSD1306_CMD_ADDR_COLUMN_LO_START + arg;
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_addr_column_hi_start(   const   uint8_t             arg )
{
    uint8_t cmd     = SSD1306_CMD_ADDR_COLUMN_HI_START + arg;
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_addr_mode(              const   ssd1306_addr_mode_t mode )
{
    uint8_t cmd     = SSD1306_CMD_ADDR_MODE;
    uint8_t buf[]   = { 0x00, cmd, (uint8_t) mode };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_addr_column(            const   uint8_t             addr_start,
                                const   uint8_t             addr_end )
{
    uint8_t cmd     = SSD1306_CMD_ADDR_COLUMN;
    uint8_t buf[]   = { 0x00, cmd, addr_start, addr_end };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_addr_page_setup(        const   uint8_t             page_start,
                                const   uint8_t             page_end )
{
    //This command is only for horizontal or vertical addressing mode.

    uint8_t cmd     = SSD1306_CMD_ADDR_PAGE_SETUP;
    uint8_t     buf[]   = { 0x00, cmd, page_start, page_end };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_addr_gram_page(         const   uint8_t             arg )
{
    uint8_t cmd     = SSD1306_CMD_ADDR_GRAM_PAGE0 + (arg & 0x7);
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

/*******************************************************************************
* Hardware Configuration
*******************************************************************************/
void
ssd1306_hw_start_line(          const   uint8_t             line )
{
    uint8_t cmd     = SSD1306_CMD_START_LINE0 + (line & 0x3F);
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_hw_hmirror(             const   bool                arg )
{
    uint8_t cmd     = SSD1306_CMD_SEGMENT_REMAP | (arg ? 0x01 : 0x00);
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_hw_mux_ratio(           const   uint8_t             ratio )
{
    uint8_t cmd     = SSD1306_CMD_MUX_RATIO;
    uint8_t buf[]   = { 0x00, cmd, ratio };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_hw_vmirror(             const   bool                arg )
{
    uint8_t cmd     = SSD1306_CMD_COM_SCAN_DIRECTION | (arg ? 0x08: 0x00);
    uint8_t buf[]   = { 0x00, cmd };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_hw_vshift(              const   uint8_t             offset )
{
    uint8_t cmd     = SSD1306_CMD_DISPLAY_OFFSET;
    uint8_t buf[]   = { 0x00, cmd, offset };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_hw_com_pins(            const   bool                seq,
                                const   bool                remap )
{
    uint8_t cmd     = SSD1306_CMD_CONFIG_COM_PINS;
    uint8_t buf[]   = { 0x00, cmd, 0x02 | (seq ? 0x10 : 0x00) | (remap ? 0x20 : 0x00) };
    ssd1306_x_write( buf, sizeof(buf) );
}

/*******************************************************************************
* Timing & Driving Scheme Setting
*******************************************************************************/
void
ssd1306_cfg_clkdiv_freq(        const   uint8_t             clk_div,
                                const   uint8_t             osc_freq )
{
    uint8_t cmd     = SSD1306_CMD_CF_CLKDIV_OSCFREQ;
    uint8_t buf[]   = { 0x00, cmd, ((osc_freq & 0xF) << 4) | (clk_div & 0xF) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_cfg_precharge_period(   const   uint8_t             phase1,
                                const   uint8_t             phase2 )
{
    uint8_t cmd     = SSD1306_CMD_PRECHARGE_PERIOD;
    uint8_t buf[]   = { 0x00, cmd, ((phase2 & 0xF) << 4) | (phase1 & 0xF) };
    ssd1306_x_write( buf, sizeof(buf) );
}

void
ssd1306_cfg_vcomh_desel_level(  const   uint8_t             level )
{
    uint8_t cmd     = SSD1306_CMD_VCOMH_DESELECT_LEVEL;
    uint8_t buf[]   = { 0x00, cmd, (level & 0x7) << 4 };
    ssd1306_x_write( buf, sizeof(buf) );
}


/*******************************************************************************
* Charge Pump
*******************************************************************************/
/**
  * @brief  Charge Pump Setting
  * @note   The Charge Pump must be enabled by the following command:
  *         8Dh; Charge Pump Setting
  *         14h; Enable Charge Pump
  *         AFh; Display ON
  * @param  Enable/Disable.
  * @retval None.
  */
void
ssd1306_charge_pump_enable(     const   bool                enable )
{
    uint8_t cmd     = SSD1306_CMD_CHARGE_PUMP;
    uint8_t buf[]   = { 0x00, cmd, enable ? 0x14 : 0x10 };
    ssd1306_x_write( buf, sizeof(buf) );
}



/*******************************************************************************
* RAW
*******************************************************************************/
void
ssd1306_cmd_raw(                const   uint8_t             cmd,
                                const   uint8_t             arg )
{
    uint8_t buf[]   = { 0x00, cmd, arg };
    ssd1306_x_write( buf, sizeof(buf) );
}


/*******************************************************************************
* GUI
*******************************************************************************/
void
ssd1306_draw_pxl(                       uint8_t *           gram, 
                                const   uint8_t             x,      //horizontal position
                                const   uint8_t             y,      //vertical position
                                const   int                 color )
{
    size_t  width   = 128;
/*
    if( x >= p->conf->width || y >= p->conf->height )
    {
        return;
    }
*/
    if( color )
    {
        gram[x + (y / 8) * width] |= 1 << (y % 8);
    }
    else
    {
        gram[x + (y / 8) * width] &= ~(1 << (y % 8));
    }
}

// Draw 1 char to the screen buffer
// c            => char om weg te schrijven
// Font         => Font waarmee we gaan schrijven
// color        => Black or White
static
char
ssd1306_putchar(                        uint8_t *           gram,
                                        uint8_t             x,
                                        uint8_t             y,
                                const   ssd1306_font_t *    font,
                                const   char                c )
{
    uint32_t        i, b, j;

/*
    if( p->conf->width  <= (p->x + p->font->width) ||
        p->conf->height <= (p->y + p->font->height)     )
    {
        return 0;
    }
*/

    for( i = 0; i < font->height; i++ )
    {
        b   = font->data[(c - 32) * font->height + i];

        for( j = 0; j < font->width; j++ )
        {
            ssd1306_draw_pxl( gram, x + j, (y + i), (b << j) & 0x8000 ? 1 : 0 );
            //if( (b << j) & 0x8000 )
            //{
            //    ssd1306_draw_pxl( gram, x + j, (y + i), 0 );
            //}
        }
    }

    x   += font->width;

    return( c );
}

char *
ssd1306_putstr(                         uint8_t *           gram,
                                        uint8_t             x,
                                        uint8_t             y,
                                const   ssd1306_font_t *    font,
                                        char *              str )
{
    while( *str )
    {
        if( ssd1306_putchar( gram+1, x, y, font, *str ) != *str )
        {
            //return( str );
            break;
        }
        
        str++;
        x   += font->width;
    }

    for( uint8_t page = y / SSD1306_PIXEL_PER_PAGE; page < SSD1306_PAGE_MAX; page++ )
    //for( uint8_t page = y * SSD1306_PIXEL_PER_PAGE; page < 1; page++ )
    {
        ssd1306_addr_gram_page( page );
        gram[ SSD1306_COL_MAX * page ] = 0x40;
        ssd1306_x_write( &gram[ SSD1306_COL_MAX * page ], 1 + SSD1306_COL_MAX );
    }

    return( str );
}







/*******************************************************************************
* INIT
*******************************************************************************/
/*
void
ssd1306_init(                           ssd1306_t *         p )
{
    ssd1306_x_reset();

    ssd1306_hw_mux_ratio( 63 );
    ssd1306_hw_vshift( 0 );
    ssd1306_hw_start_line( 0 );
    ssd1306_hw_hmirror( false );
    ssd1306_hw_vmirror( false );
    ssd1306_hw_com_pins( false, false );
    ssd1306_set_contrast( 127 );
    ssd1306_set_entire_display_on( true );
    //ssd1306_cfg_clkdiv_freq( 0, 8 );
    ssd1306_cfg_clkdiv_freq( 0, 0 );
    ssd1306_cmd_raw( 0x8D, 0x14 );
    ssd1306_set_display_on( true );
    //ssd1306_cfg_precharge_period( 2, 2 );
    //ssd1306_cfg_vcomh_desel_level( 2 );

    ssd1306_addr_column_lo_start( 0 );
    ssd1306_addr_column_hi_start( 0 );
    ssd1306_addr_mode( SSD1306_ADDR_MODE_PAGE );
    ssd1306_addr_column( 0, 127 );
    ssd1306_addr_gram_page( 0 );

    ssd1306_set_inverse( false );


    ssd1306_fill( p, SSD1306_COLOR_BLACK );
    ssd1306_update( p );

    p->x    = 0;
    p->y    = 0;
}
*/

/*******************************************************************************
* OPERATE
*******************************************************************************/

/*
void
ssd1306_fill(                           ssd1306_t *     p,
                                const   ssd1306_color_t color )
{
    //for( int i = 0; i < sizeof(ssd1306_buffer); i++ )
    for( int i = 0; i < p->conf->buf_sizeof - 1; i++ )
    {
        p->gram[ i ] = color;
    }
}
*/
/*
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
*/

// Draw 1 char to the screen buffer
// c            => char om weg te schrijven
// Font         => Font waarmee we gaan schrijven
// color        => Black or White
/*
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
*/
/*
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
*/
/*******************************************************************************
*
*******************************************************************************/
/*
void
ssd1306_set_position(                           ssd1306_t *     p,
                                        const   uint8_t         x,
                                        const   uint8_t         y )
{
    p->x    = x;
    p->y    = y;
}
*/
/*
void
ssd1306_set_color(                              ssd1306_t *         p,
                                        const   ssd1306_color_t     color )
{
    p->color    = color;
}
*/
/*
void
ssd1306_set_font(                               ssd1306_t *         p,
                                        const   ssd1306_font_t *    font )
{
    p->font = font;
}
*/

/*******************************************************************************
*
*******************************************************************************/
/*
void
ssd1306_update(                         ssd1306_t *     p )
{
    for( uint8_t i = 0; i < 8; i++ )
    {
        ssd1306_addr_gram_page( i );
        //ssd1306_addr_column_lo_start( 0 );
        //ssd1306_addr_column_hi_start( 0 );
        //ssd1306_hw_start_line( 0 );

        //p->gram[ 0]  = 0x40;
        p->gram[ p->conf->width*i ] = 0x40;
        ssd1306_x_write( &p->gram[ p->conf->width*i ], 1 + p->conf->width );
        //ssd1306_x_write( p->gram, p->conf->buf_sizeof );
    }
}
*/
