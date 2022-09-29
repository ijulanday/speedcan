/* 
 * This file contains glue logic which takes the protocol files
 * (which are auto-generated using the Protogen tool)
 * and provides the required encode / decode layer.
 * 
 * Note: For a particular application these glue functions can be adjusted as required.
 */

#ifndef _ESC_GLUE_H_
#define _ESC_GLUE_H_

// Define a simple structure for packet data representation

#include <stdint.h>

typedef struct
{

    // While a CAN frame cannot exceed 8 bytes,
    // some packets are transmitted over multiple frames.
    // data length is set to 256 here to support this. 
    uint8_t data[256];

    //! CAN frame identifier
    //! Note: Velocity CAN frames are 29-bit (extended ID)
    uint32_t frameId;

    //! Packet length
    uint8_t len;

} ESCPacket_t;


#endif //_ESC_GLUE_H_
