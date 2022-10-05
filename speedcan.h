#pragma once

#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <list>
#include "velocity_sdk/esc_glue.h"
#include "velocity_sdk/ESCVelocityProtocol.h"
#include "velocity_sdk/ESCPackets.h"

#define ESC_COMM_TIMEOUT    1500
#define CAN_IFACE           CAN3

void packetToCANmessage(ESCPacket_t pkt, CAN_message_t* msg);
void messageToESCpacket(CAN_message_t msg, ESCPacket_t* pkt);
void broadcastRPMcommand(double RPM, FlexCAN_T4<CAN_IFACE, RX_SIZE_256, TX_SIZE_16>* can);
void broadcastPWMcommand(uint16_t PWM, FlexCAN_T4<CAN_IFACE, RX_SIZE_256, TX_SIZE_16>* can);
void broadcastEnableCommand(FlexCAN_T4<CAN_IFACE, RX_SIZE_256, TX_SIZE_16>* can);
void writeRPMcommand(double RPM, uint8_t address, FlexCAN_T4<CAN_IFACE, RX_SIZE_256, TX_SIZE_16>* can);
void writePWMcommand(double PWM, uint8_t address, FlexCAN_T4<CAN_IFACE, RX_SIZE_256, TX_SIZE_16>* can);
void escIncomingMessageHandler();
void printMsg(CAN_message_t msg);
void printStatus();
void printErrorsAndWarnings();
void canSniff(const CAN_message_t &msg);

extern CAN_message_t esc_message;
extern ESCPacket_t esc_packet;
extern ESC_StatusBits_t statusBits;
extern ESC_WarningBits_t warningBits;
extern ESC_ErrorBits_t errorBits;

typedef struct {
    uint8_t lastId;
    uint8_t mode;
    uint16_t command;
    uint16_t rpm;
    uint16_t voltage;
    int16_t current; 
    uint16_t dutyCycle;
    int8_t escTemperature;
    uint8_t motorTemperature;
    uint16_t powerUsage;
    uint8_t maxTemperature; 
    uint8_t maxFetTemperature;
    uint8_t maxMotorTemperature;
    uint8_t maxRippleVoltage;
    float maxBatteryCurrent;
    float maxRegenCurrent;
    uint16_t totalStarts;
    uint16_t failedStarts;
    uint32_t escRunTime;
    uint32_t motorRunTime;
    uint32_t desyncEvents;
    float fetTemperature;
    uint16_t pwmFrequency;
    uint16_t timingAdvance;
    uint32_t averageCurrent;
} ESCdata;

extern ESCdata escData;
