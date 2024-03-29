/**
  * @file    ad7799.h
  * @brief   AD7799 driver header
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef AD7799_H
#define AD7799_H


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define AD7799_SPAN                     (1<<24)

#define AD7799_COMM_WEN                 (1 << 7)
#define AD7799_COMM_WRITE               (0 << 6)
#define AD7799_COMM_READ                (1 << 6)
#define AD7799_COMM_CREAD               (1 << 2)
#define AD7799_STS_READY                (1 << 7)
#define AD7799_STS_ERROR                (1 << 6)
#define AD7799_STS_NOREF                (1 << 5)
#define AD7799_STS_CH3                  (1 << 2)
#define AD7799_STS_CH2                  (1 << 1)
#define AD7799_STS_CH1                  (1 << 0)
#define AD7799_ID                       0x09
#define AD7799_ID_MASK                  0x0F


typedef struct  ad7799_reg_s
{
    union
    {
        uint16_t                u16;
        struct
        {
            uint16_t        rate:           4;
            uint16_t        mr4:            1;
            uint16_t        mr5:            1;
            uint16_t        mr6:            1;
            uint16_t        mr7:            1;
            uint16_t        mr8:            1;
            uint16_t        mr9:            1;
            uint16_t        mr10:           1;
            uint16_t        mr11:           1;
            uint16_t        psw:            1;
            uint16_t        mode:           3;
        };
    } mode;

    union
    {
        uint16_t                u16;
        struct
        {
            uint16_t        chnl:           3;
            uint16_t        con3:           1;
            uint16_t        buf_en:         1;
            uint16_t        ref_det:        1;
            uint16_t        con6:           1;
            uint16_t        con7:           1;
            uint16_t        gain:           3;
            uint16_t        con11:          1;
            uint16_t        unipolar:       1;
            uint16_t        burnout:        1;
            uint16_t        con14:          1;
            uint16_t        con15:          1;
        };
    } conf;

    uint8_t         id;

} ad7799_reg_t;


typedef struct  ad7799_s
{
        ad7799_reg_t            reg;
} ad7799_t;



typedef enum    ad7799_addr_e
{
        AD7799_REG_COMM                 = 0,    //WO, 8-bit
        AD7799_REG_STS                  = 0,    //RO, 8-bit
        AD7799_REG_MODE                 = 1,    //RW, 16-bit
        AD7799_REG_CONF                 = 2,    //RW, 16-bit
        AD7799_REG_DATA                 = 3,    //RO, 24-bit
        AD7799_REG_ID                   = 4,    //RO, 8-bit
        AD7799_REG_IO                   = 5,    //RO, 8-bit
        AD7799_REG_OFFSET               = 6,    //RW, 24-bit
        AD7799_REG_FULLSALE             = 7,    //RW, 24-bit
} ad7799_addr_t;


typedef enum    ad7799_mode_e
{
        AD7799_MODE_CONTINUOUS          = 0,
        AD7799_MODE_SINGLE              = 1,
        AD7799_MODE_IDLE                = 2,
        AD7799_MODE_POWERDOWN           = 3,
        AD7799_MODE_CAL_INT_ZERO        = 4,
        AD7799_MODE_CAL_INT_FULL        = 5,
        AD7799_MODE_CAL_SYS_ZERO        = 6,
        AD7799_MODE_CAL_SYS_FULL        = 7,
} ad7799_mode_t;

typedef enum    ad7799_rate_e
{
        AD7799_RATE_RESERVED            =  0,
        AD7799_RATE_470_Hz              =  1,
        AD7799_RATE_242_Hz              =  2,
        AD7799_RATE_123_Hz              =  3,
        AD7799_RATE_62_Hz               =  4,
        AD7799_RATE_50_Hz               =  5,
        AD7799_RATE_39_Hz               =  6,
        AD7799_RATE_33_2_Hz             =  7,
        AD7799_RATE_19_6_Hz             =  8,
        AD7799_RATE_16_7_Hz_REJ_50_Hz   =  9,
        AD7799_RATE_16_7_Hz             = 10,
        AD7799_RATE_12_5_Hz             = 11,
        AD7799_RATE_10_Hz               = 12,
        AD7799_RATE_8_33_Hz             = 13,
        AD7799_RATE_6_25_Hz             = 14,
        AD7799_RATE_4_17_Hz             = 15,
} ad7799_rate_t;

typedef enum    ad7799_gain_e
{
        AD7799_GAIN_1                   = 0,
        AD7799_GAIN_2                   = 1,
        AD7799_GAIN_4                   = 2,
        AD7799_GAIN_8                   = 3,
        AD7799_GAIN_16                  = 4,
        AD7799_GAIN_32                  = 5,
        AD7799_GAIN_64                  = 6,
        AD7799_GAIN_128                 = 7,
        AD7799_GAIN_MAX                 = 7,
        AD7799_GAIN_MASK                = 0x7,
} ad7799_gain_t;


typedef enum    ad7799_chnl_e
{
        AD7799_CHNL_AIN1P_AIN1M         = 0, //AIN1(+) - AIN1(-)
        AD7799_CHNL_AIN2P_AIN2M         = 1, //AIN2(+) - AIN2(-)
        AD7799_CHNL_AIN3P_AIN3M         = 2, //AIN3(+) - AIN3(-)
        AD7799_CHNL_AIN1M_AIN1M         = 3, //AIN1(-) - AIN1(-)
        AD7799_CHNL_AVDD_MONITOR        = 7, //AVDD Monitor
        AD7799_CHNL_MASK                = 0x7,
} ad7799_chnl_t;


/*******************************************************************************
* AD7799_X
*******************************************************************************/
extern  void    ad7799_x_miso_config_spi( void );
extern  void    ad7799_x_miso_config_gpio( void );
extern  uint8_t ad7799_x_xfer( uint8_t );
//extern  void    ad7799_x_enable( const bool );
extern  void    ad7799_x_nss_force( void );
extern  void    ad7799_x_nss_release( void );


/*******************************************************************************
* BASIC COMMUNICATION'S
*******************************************************************************/
uint16_t
ad7799_read(                    const   ad7799_addr_t           addr );

void
ad7799_write(                   const   ad7799_addr_t           addr,
                                const   uint16_t                data );

/*******************************************************************************
* ROUTINES
*******************************************************************************/
void
ad7799_reset( void );

uint8_t
ad7799_get_id( void );

void
ad7799_set_continuous_read_mode( void );

uint32_t
ad7799_get_data_single( void );

uint32_t
ad7799_get_data_continous( void );


#endif	// AD7799_H
