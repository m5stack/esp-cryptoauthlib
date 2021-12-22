/*
 * Copyright 2018 Espressif Systems (Shanghai) PTE LTD
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <driver/i2c.h>
#include "esp_err.h"
#include "esp_log.h"
#include "cryptoauthlib.h"
#include "i2c_manager.h"
#include "core2foraws_common.h"

const char* TAG = "ATECC608_HAL";

ATCA_STATUS status;

/** \brief method to change the bus speec of I2C
 * \param[in] iface  interface on which to change bus speed
 * \param[in] speed  baud rate (typically 100000 or 400000)
 */
ATCA_STATUS hal_i2c_change_baud(ATCAIface iface, uint32_t speed)
{
        //ESP_LOGD(TAG, "Baudrate Changed");
        return ATCA_SUCCESS;
}

/** \brief
    - this HAL implementation assumes you've included the START Twi libraries in your project, otherwise,
    the HAL layer will not compile because the START TWI drivers are a dependency *
 */

/** \brief hal_i2c_init manages requests to initialize a physical interface.  it manages use counts so when an interface
 * has released the physical layer, it will disable the interface for some other use.
 * You can have multiple ATCAIFace instances using the same bus, and you can have multiple ATCAIFace instances on
 * multiple i2c buses, so hal_i2c_init manages these things and ATCAIFace is abstracted from the physical details.
 */

/** \brief initialize an I2C interface using given config
 * \param[in] hal - opaque ptr to HAL data
 * \param[in] cfg - interface configuration
 * \return ATCA_SUCCESS on success, otherwise an error code.
 */
ATCA_STATUS hal_i2c_init( ATCAIface iface, ATCAIfaceCfg *cfg )
{
    // ESP_LOGE( TAG, "ATECC608 ADDRESS: 0x%x", cfg->atcai2c.address );
    esp_err_t err = i2c_manager_init( COMMON_I2C_INTERNAL );
    if (err != ESP_OK) {
        return ATCA_COMM_FAIL;
    } else {
        return ATCA_SUCCESS;
    }
}

/** \brief HAL implementation of I2C post init
 * \param[in] iface  instance
 * \return ATCA_SUCCESS
 */
ATCA_STATUS hal_i2c_post_init( ATCAIface iface )
{
    return ATCA_SUCCESS;
}

/** \brief HAL implementation of I2C send
 * \param[in] iface         instance
 * \param[in] word_address  device transaction type
 * \param[in] txdata        pointer to space to bytes to send
 * \param[in] txlength      number of bytes to send
 * \return ATCA_SUCCESS on success, otherwise an error code.
 */
ATCA_STATUS hal_i2c_send( ATCAIface iface, uint8_t address, uint8_t *txdata, int txlength )
{
    esp_err_t err = ESP_FAIL;
    // ESP_LOGE( TAG, "SEND ATECC608 ADDRESS: 0x%x", address );
    err = i2c_manager_write( COMMON_I2C_INTERNAL, address >> 1, I2C_NO_REG, txdata, txlength );
    
    ESP_LOGD( TAG, "txdata: %p , txlength: %d error: %s", txdata, txlength, esp_err_to_name( err ) );

    if ( err == ESP_OK)
    {
        return ATCA_SUCCESS;
    }

    return ATCA_COMM_FAIL;
}

/** \brief HAL implementation of I2C receive function
 * \param[in]    iface          Device to interact with.
 * \param[in]    address        Device address
 * \param[out]   rxdata         Data received will be returned here.
 * \param[in,out] rxlength      As input, the size of the rxdata buffer.
 *                              As output, the number of bytes received.
 * \return ATCA_SUCCESS on success, otherwise an error code.
 */
ATCA_STATUS hal_i2c_receive( ATCAIface iface, uint8_t address, uint8_t *rxdata, uint16_t *rxlength )
{
    esp_err_t err = ESP_FAIL;
    // ESP_LOGE( TAG, "RECEIVE ATECC608 ADDRESS: 0x%x", address );
    if ( ( NULL == rxlength ) || ( NULL == rxdata ) )
    {
        return ATCA_TRACE( ATCA_INVALID_POINTER, "NULL pointer encountered" );
    }
    
    err = i2c_manager_read( COMMON_I2C_INTERNAL, address >> 1, I2C_NO_REG, rxdata, *rxlength );

    if ( err == ESP_OK )
    {
        return ATCA_SUCCESS;
    }

    return ATCA_COMM_FAIL;
}

/** \brief manages reference count on given bus and releases resource if no more refences exist
 * \param[in] hal_data - opaque pointer to hal data structure - known only to the HAL implementation
 * \return ATCA_SUCCESS on success, otherwise an error code.
 */
ATCA_STATUS hal_i2c_release( void *hal_data )
{
    // i2c_free_device(atecc608_device);
    return ATCA_SUCCESS;
}

/** \brief Perform control operations for the kit protocol
 * \param[in]     iface          Interface to interact with.
 * \param[in]     option         Control parameter identifier
 * \param[in]     param          Optional pointer to parameter value
 * \param[in]     paramlen       Length of the parameter
 * \return ATCA_SUCCESS on success, otherwise an error code.
 */
ATCA_STATUS hal_i2c_control( ATCAIface iface, uint8_t option, void *param, size_t paramlen )
{
    ( void )param;
    ( void )paramlen;

    if ( iface && iface->mIfaceCFG )
    {
        if ( ATCA_HAL_CHANGE_BAUD == option )
        {
            return hal_i2c_change_baud( iface, *( uint32_t * )param );
        }
        else
        {
            return ATCA_UNIMPLEMENTED;
        }
    }
    return ATCA_BAD_PARAM;
}