
#include "ESCVelocityProtocol.h"

#include "esc_glue.h"


//! \return the packet data pointer from the packet
uint8_t* getESCVelocityPacketData(void* pkt)
{
    ESCPacket_t *packet = (ESCPacket_t*) pkt;

    return packet->data;
}

//! \return the packet data pointer from the packet, const
const uint8_t* getESCVelocityPacketDataConst(const void* pkt)
{
    return (const uint8_t*) getESCVelocityPacketData((void*) pkt);
}

//! Complete a packet after the data have been encoded
void finishESCVelocityPacket(void* pkt, int size, uint32_t packetID)
{
    ESCPacket_t *packet = (ESCPacket_t*) pkt;

    // Record the size of the packet (in bytes)
    packet->len = (uint8_t) size;

    // Convert the provided packet ID to a can frame ID

    /*
     * Note: The CAN frame ID aligns with the Piccolo message spec.
     * 0x07 = Actuator group
     * 0x00 = message identifier (will be overwritten)
     * 0x20 = ESC device type
     * 0x00 = device address (will need to be overwritten)
     */

    uint32_t id = 0x07002000;

    id |= ((packetID & 0xFF) << 16);

    packet->frameId = id;

    // You may wish to perform other functions here too,
    // whenever a packet is encoded to memory
}

//! \return the size of a packet from the packet header
int getESCVelocityPacketSize(const void* pkt)
{
    ESCPacket_t *packet = (ESCPacket_t*) pkt;

    return (int) packet->len;
}

//! \return the ID of a packet from the packet header
uint32_t getESCVelocityPacketID(const void* pkt)
{
    ESCPacket_t *packet = (ESCPacket_t*) pkt;

    // Extract the message identifier from the CAN frame ID

    return (uint32_t) ((packet->frameId >> 16) & 0xFF);
}