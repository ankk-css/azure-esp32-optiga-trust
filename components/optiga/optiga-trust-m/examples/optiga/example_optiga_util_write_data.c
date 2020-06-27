/**
* \copyright
* MIT License
*
* Copyright (c) 2020 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
* \endcopyright
*
* \author Infineon Technologies AG
*
* \file example_optiga_util_write_data.c
*
* \brief   This file provides the example for writing data/metadata to OPTIGA using
*          #optiga_util_write_data and #optiga_util_write_metadata.
*
* \ingroup grOptigaExamples
*
* @{
*/

#include "optiga/optiga_util.h"
#include "optiga_example.h"

/**
 * Sample Trust Anchor
 */
static const uint8_t trust_anchor [] = {
    //00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F
    0x30, 0x82, 0x02, 0x7E, 0x30, 0x82, 0x02, 0x05, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x09, 0x00,
    0x9B, 0x0C, 0x24, 0xB4, 0x5E, 0x7D, 0xE3, 0x73, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE,
    0x3D, 0x04, 0x03, 0x02, 0x30, 0x74, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
    0x02, 0x44, 0x45, 0x31, 0x21, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x18, 0x49, 0x6E,
    0x66, 0x69, 0x6E, 0x65, 0x6F, 0x6E, 0x20, 0x54, 0x65, 0x63, 0x68, 0x6E, 0x6F, 0x6C, 0x6F, 0x67,
    0x69, 0x65, 0x73, 0x20, 0x41, 0x47, 0x31, 0x1B, 0x30, 0x19, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x0C,
    0x12, 0x4F, 0x50, 0x54, 0x49, 0x47, 0x41, 0x28, 0x54, 0x4D, 0x29, 0x20, 0x54, 0x72, 0x75, 0x73,
    0x74, 0x20, 0x58, 0x31, 0x25, 0x30, 0x23, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x1C, 0x49, 0x6E,
    0x66, 0x69, 0x6E, 0x65, 0x6F, 0x6E, 0x20, 0x54, 0x65, 0x73, 0x74, 0x20, 0x53, 0x65, 0x72, 0x76,
    0x65, 0x72, 0x20, 0x52, 0x6F, 0x6F, 0x74, 0x20, 0x43, 0x41, 0x30, 0x1E, 0x17, 0x0D, 0x31, 0x36,
    0x31, 0x30, 0x31, 0x34, 0x30, 0x33, 0x35, 0x38, 0x33, 0x36, 0x5A, 0x17, 0x0D, 0x34, 0x31, 0x31,
    0x30, 0x30, 0x38, 0x30, 0x33, 0x35, 0x38, 0x33, 0x36, 0x5A, 0x30, 0x74, 0x31, 0x0B, 0x30, 0x09,
    0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x44, 0x45, 0x31, 0x21, 0x30, 0x1F, 0x06, 0x03, 0x55,
    0x04, 0x0A, 0x0C, 0x18, 0x49, 0x6E, 0x66, 0x69, 0x6E, 0x65, 0x6F, 0x6E, 0x20, 0x54, 0x65, 0x63,
    0x68, 0x6E, 0x6F, 0x6C, 0x6F, 0x67, 0x69, 0x65, 0x73, 0x20, 0x41, 0x47, 0x31, 0x1B, 0x30, 0x19,
    0x06, 0x03, 0x55, 0x04, 0x0B, 0x0C, 0x12, 0x4F, 0x50, 0x54, 0x49, 0x47, 0x41, 0x28, 0x54, 0x4D,
    0x29, 0x20, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x58, 0x31, 0x25, 0x30, 0x23, 0x06, 0x03, 0x55,
    0x04, 0x03, 0x0C, 0x1C, 0x49, 0x6E, 0x66, 0x69, 0x6E, 0x65, 0x6F, 0x6E, 0x20, 0x54, 0x65, 0x73,
    0x74, 0x20, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x20, 0x52, 0x6F, 0x6F, 0x74, 0x20, 0x43, 0x41,
    0x30, 0x76, 0x30, 0x10, 0x06, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x05, 0x2B,
    0x81, 0x04, 0x00, 0x22, 0x03, 0x62, 0x00, 0x04, 0x7B, 0x2E, 0xE6, 0xFB, 0xBD, 0x6F, 0x40, 0x0F,
    0x41, 0x9F, 0xE5, 0xF0, 0x8C, 0x97, 0x21, 0xB0, 0x07, 0xB5, 0xBB, 0xD2, 0xB8, 0x5A, 0x14, 0x3B,
    0x75, 0x54, 0x7E, 0xEA, 0xFE, 0xF2, 0x8D, 0x5A, 0xB8, 0x54, 0xE0, 0xC8, 0xAD, 0xED, 0xF1, 0xD5,
    0x8B, 0x97, 0xBA, 0x02, 0x3E, 0xD9, 0x25, 0xE0, 0x00, 0x86, 0x17, 0x35, 0xE6, 0xE6, 0xD9, 0x12,
    0x0F, 0x8A, 0x21, 0x1C, 0x62, 0xFA, 0xCE, 0xF6, 0x9E, 0xB1, 0xF8, 0x8C, 0xA3, 0xDC, 0x52, 0x04,
    0x83, 0xEB, 0xA0, 0xB3, 0xFA, 0xB0, 0xCA, 0x02, 0x30, 0xB1, 0xFE, 0x53, 0x4E, 0xAD, 0xFB, 0xE0,
    0x88, 0x05, 0x86, 0x4E, 0x5E, 0x67, 0xEB, 0x7B, 0xA3, 0x63, 0x30, 0x61, 0x30, 0x1D, 0x06, 0x03,
    0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04, 0x14, 0x91, 0x4A, 0x4B, 0x07, 0x58, 0xB2, 0xC6, 0x4B, 0x37,
    0xFD, 0x91, 0x62, 0xD8, 0x8A, 0x17, 0x28, 0xAA, 0x94, 0x18, 0x62, 0x30, 0x1F, 0x06, 0x03, 0x55,
    0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x91, 0x4A, 0x4B, 0x07, 0x58, 0xB2, 0xC6, 0x4B,
    0x37, 0xFD, 0x91, 0x62, 0xD8, 0x8A, 0x17, 0x28, 0xAA, 0x94, 0x18, 0x62, 0x30, 0x0F, 0x06, 0x03,
    0x55, 0x1D, 0x13, 0x01, 0x01, 0xFF, 0x04, 0x05, 0x30, 0x03, 0x01, 0x01, 0xFF, 0x30, 0x0E, 0x06,
    0x03, 0x55, 0x1D, 0x0F, 0x01, 0x01, 0xFF, 0x04, 0x04, 0x03, 0x02, 0x02, 0x04, 0x30, 0x0A, 0x06,
    0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x03, 0x67, 0x00, 0x30, 0x64, 0x02, 0x30,
    0x20, 0x1C, 0x7A, 0x21, 0x50, 0x50, 0xC9, 0x15, 0x1C, 0xC5, 0x14, 0x8D, 0x46, 0x5C, 0xA6, 0xD3,
    0x81, 0xCE, 0x57, 0x06, 0x1A, 0xAE, 0x39, 0x10, 0x27, 0x51, 0x42, 0xEF, 0xCD, 0x64, 0x75, 0x99,
    0xDE, 0x0D, 0x3D, 0x01, 0x47, 0x69, 0xFC, 0x93, 0x6D, 0x99, 0xC7, 0xF0, 0xF8, 0x8C, 0xAA, 0xD1,
    0x02, 0x30, 0x68, 0xC3, 0x27, 0xD9, 0x0F, 0x52, 0xAD, 0x3A, 0xA8, 0xDB, 0xF8, 0x53, 0x11, 0x1D,
    0xF1, 0x30, 0x6B, 0x39, 0xF3, 0x3F, 0xEF, 0x65, 0x61, 0xBE, 0xC4, 0xDD, 0x19, 0x11, 0x1E, 0x83,
    0xF9, 0xE8, 0x3F, 0x41, 0x97, 0x45, 0xFC, 0x61, 0xE0, 0x06, 0xD0, 0xE6, 0xF7, 0x5C, 0x9F, 0xE2,
    0x57, 0xC2,
    };

/**
 * Sample metadata
 */
static const uint8_t metadata [] = {
    //Metadata tag in the data object
    0x20, 0x05,
        //Read tag in the metadata
        0xD1, 0x03,
            //LcsO < Operation
            0xE1 , 0xFB, 0x03,
};

/**
 * Callback when optiga_util_xxxx operation is completed asynchronously
 */
static volatile optiga_lib_status_t optiga_lib_status;
//lint --e{818} suppress "argument "context" is not used in the sample provided"
static void optiga_util_callback(void * context, optiga_lib_status_t return_status)
{
    optiga_lib_status = return_status;
    if (NULL != context)
    {
        // callback to upper layer here
    }
}

/**
 * The below example demonstrates write data/metadata functionalities
 *
 * Example for #optiga_util_write_data and #optiga_util_write_metadata
 *
 */
void example_optiga_util_write_data(void)
{
    uint16_t optiga_oid;
    uint16_t offset;

    optiga_lib_status_t return_status = !OPTIGA_LIB_SUCCESS;
    optiga_util_t * me = NULL;
    OPTIGA_EXAMPLE_LOG_MESSAGE(__FUNCTION__);

    do
    {
        /**
         * 1. Create OPTIGA Util Instance
         */
        me = optiga_util_create(0, optiga_util_callback, NULL);
        if (NULL == me)
        {
            break;
        }

        /**
         * Write Trust Anchor to a Trust Anchor object (e.g. E0E8)
         * using optiga_util_write_data with no shielded connection protection.
         *
         * Use Erase and Write (OPTIGA_UTIL_ERASE_AND_WRITE) option,
         * to clear the remaining data in the object
         */
        optiga_oid = 0xE0E8;
        offset = 0x00;

        OPTIGA_UTIL_SET_COMMS_PROTECTION_LEVEL(me, OPTIGA_COMMS_NO_PROTECTION);

        optiga_lib_status = OPTIGA_LIB_BUSY;
        return_status = optiga_util_write_data(me,
                                               optiga_oid,
                                               OPTIGA_UTIL_ERASE_AND_WRITE,
                                               offset,
                                               trust_anchor,
                                               sizeof(trust_anchor));

        WAIT_AND_CHECK_STATUS(return_status, optiga_lib_status);

        /**
         *
         * Write metadata to Trust Anchor to a Trust Anchor object (e.g. E0E8)
         * using optiga_util_write_metadata.
         *
         * Sample metadata: write "Read" access condition as LcsO < Operational
         *
         */
        optiga_lib_status = OPTIGA_LIB_BUSY;
        return_status = optiga_util_write_metadata(me,
                                                   0xE0E8,
                                                   metadata,
                                                   sizeof(metadata));

        WAIT_AND_CHECK_STATUS(return_status, optiga_lib_status);
        return_status = OPTIGA_LIB_SUCCESS;

    } while (FALSE);
    OPTIGA_EXAMPLE_LOG_STATUS(return_status);
    
    if (me)
    {
        //Destroy the instance after the completion of usecase if not required.
        return_status = optiga_util_destroy(me);
        if(OPTIGA_LIB_SUCCESS != return_status)
        {
            //lint --e{774} suppress This is a generic macro
            OPTIGA_EXAMPLE_LOG_STATUS(return_status);
        }
    }
}

/**
* @}
*/
