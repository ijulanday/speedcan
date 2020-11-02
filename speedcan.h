#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "esc_glue.h"
#include "ESCVelocityProtocol.h"
#include "ESCPackets.h"
 
#ifndef SPEEDCAN_H
#define SPEEDCAN_H
 
void packetToCANmessage(ESCPacket_t pkt, CAN_message_t* msg);
void messageToESCpacket(CAN_message_t msg, ESCPacket_t* pkt);
void broadcastRPMcommand(double RPM, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>* can);
void incomingMessageHandler();
void printMsg(CAN_message_t msg);
void printStatus();
void printErrorsAndWarnings();

extern CAN_message_t message_speedcan;
extern ESCPacket_t packet;
extern ESC_StatusBits_t statusBits;
extern ESC_WarningBits_t warningBits;
extern ESC_ErrorBits_t errorBits;

extern uint8_t mode;
extern uint16_t command;
extern uint16_t rpm;
extern uint16_t voltage;
extern int16_t current; 
extern uint16_t dutyCycle;
extern int8_t escTemperature;
extern uint8_t motorTemperature;

#endif