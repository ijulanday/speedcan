#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "esc_glue.h"
#include "ESCVelocityProtocol.h"
#include "ESCPackets.h"

//TODO: write defines for stuff

#ifndef SPEEDCAN_H
#define SPEEDCAN_H

void packetToCANmessage(ESCPacket_t pkt, CAN_message_t* msg);
void messageToESCpacket(CAN_message_t msg, ESCPacket_t* pkt);
void broadcastRPMcommand(double RPM, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>* can);
void broadcastPWMcommand(uint16_t PWM, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>* can);
void writeRPMcommand(double RPM, uint8_t address, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>* can);
void writePWMcommand(double PWM, uint8_t address, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>* can);
void incomingMessageHandler();
void printMsg(CAN_message_t msg);
void printStatus();
void printErrorsAndWarnings();

extern CAN_message_t esc_message;
extern ESCPacket_t esc_packet;
extern ESC_StatusBits_t statusBits;
extern ESC_WarningBits_t warningBits;
extern ESC_ErrorBits_t errorBits;

typedef struct {
    uint8_t mode;
    uint16_t command;
    uint16_t rpm;
    uint16_t voltage;
    int16_t current; 
    uint16_t dutyCycle;
    int8_t escTemperature;
    uint8_t motorTemperature;
} ESCdata;

extern ESCdata escData;

#endif