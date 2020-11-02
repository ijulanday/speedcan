#include "speedcan.h"

CAN_message_t message_speedcan;
ESCPacket_t packet;
ESC_StatusBits_t statusBits;
ESC_WarningBits_t warningBits;
ESC_ErrorBits_t errorBits;

uint8_t mode;
uint16_t command;
uint16_t rpm;
uint16_t voltage;
int16_t current; 
uint16_t dutyCycle;
int8_t escTemperature;
uint8_t motorTemperature;

void packetToCANmessage(ESCPacket_t pkt, CAN_message_t* msg) {
    msg->len = pkt.len;
    int i;
    for (i = 0; i < msg->len; i++) {
        msg->buf[i] = pkt.data[i];
    }
    msg->flags.extended = true;
    msg->id = pkt.frameId;
}

void messageToESCpacket(CAN_message_t msg, ESCPacket_t* pkt) {
  pkt->len = msg.len;
  int i;
  for (i = 0; i < pkt->len; i++) {
    pkt->data[i] = msg.buf[i];
  }
  pkt->frameId = msg.id;
}

// broadcasts RPM command packet on a provided CAN interface
void broadcastRPMcommand(double RPM, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>* can) {
  encodeESC_RPMCommandPacket(&packet, RPM);
  packetToCANmessage(packet, &message_speedcan);
  message_speedcan.id |= 0xFF;
  can->write(message_speedcan);
}

// broadcasts PWM command on a provided CAN interface
void broadcastPWMcommand(uint16_t PWM, FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>* can) {
  encodeESC_PWMCommandPacket(&packet, PWM);
  packetToCANmessage(packet, &message_speedcan);
  message_speedcan.id |= 0xFF;
  can->write(message_speedcan);
} //TODO: figure out how to reduce PWM deadzone

void incomingMessageHandler() {
  messageToESCpacket(message_speedcan, &packet);
  switch (packet.frameId | 0xFF) {
    case 0x78020FF:   // StatusA              (0x80)
      decodeESC_StatusAPacket(&packet, &mode, &statusBits, &command, &rpm);
      break;
    case 0x78120FF:   // StatusB              (0x81)
      decodeESC_StatusBPacket(&packet, &voltage, &current, &dutyCycle, &escTemperature, &motorTemperature);
      break;
    case 0x78620FF:   // WarningErrorStatus   (0x86)
      decodeESC_WarningErrorStatusPacket(&packet, &warningBits, &errorBits);
      printErrorsAndWarnings();
      break;
    case 0x78720FF:   // MotorStatusFlags     (0x87)
      // meh
      break;
  }
}

void printMsg(CAN_message_t msg) {
  Serial.print("message ID: "); Serial.println(msg.id, HEX);
  Serial.print("message len: "); Serial.println(msg.len);
  Serial.print("message data: ");
  for (int i = 0; i < msg.len; i++) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  }
  Serial.println("");
}

void printStatus() {
  Serial.println(" === ESC status === ");
  if (statusBits.hwInhibit) 
    Serial.println("HARDWARE INHIBITED -- MUST CONNECT HW ENABLE PIN");
  if (statusBits.swInhibit) 
    Serial.println("SOFTWARE INHIBITED -- SEND ENABLE PACKET");
  if (statusBits.anyWarnings)
    Serial.println("There are WARNINGS that need attention!");
  if (statusBits.anyErrors)
    Serial.println("There are ERRORS that need attention!");
  if (statusBits.running)
    Serial.println("Motor is running on ESC ");

  Serial.print("Voltage: "); Serial.println(voltage);
  Serial.print("Current: "); Serial.println(current);
}

void printErrorsAndWarnings() {
  if (warningBits.overspeed)          Serial.println("WARNING: ESC motor speed exceeds the configured warning threshold");
  if (warningBits.overcurrent)        Serial.println("WARNING: ESC motor current (positive or negative) exceeds the configured warning threshold");
  if (warningBits.escTemperature)     Serial.println("WARNING: internal ESC temperature is above the warning threshold");
  if (warningBits.motorTemperature)   Serial.println("WARNING: motor temperature is above the warning threshold");
  if (warningBits.undervoltage)       Serial.println("WARNING: input voltage is below the minimum threshold");
  if (warningBits.overvoltage)        Serial.println("WARNING: input voltage is above the maximum threshold");
  if (warningBits.invalidPWMsignal)   Serial.println("WARNING: hardware PWM input is enabled but invalid");
  if (warningBits.demagAngle)         Serial.println("WARNING: motor demag angle exceeds the maximum threshold");
  if (warningBits.advanceLimit)       Serial.println("WARNING: auto-advance exceeds 25 degrees");
  if (warningBits.longDemag)          Serial.println("WARNING: measured demag pulse is exceptionally long");
  if (warningBits.missedZeroCrossing) Serial.println("WARNING: Set if a zero-crossing measurement was missed");
  if (warningBits.spinningReversed)   Serial.println("WARNING: Motor is spinning in the wrong direction");
  if (warningBits.commSpeedLimit)     Serial.println("WARNING: Motor has reached maximum allowable commutation speed");

  if (errorBits.failedStart)     Serial.println("ERROR: Set if the ESC failed to start the motor");
  if (errorBits.commutation)     Serial.println("ERROR: Lost commutation");
  if (errorBits.hallSensor)      Serial.println("ERROR: Set if hall sensor error detected");
  if (errorBits.overcurrent)     Serial.println("ERROR: Current exceeded hard-limit");
  if (errorBits.overtemperature) Serial.println("ERROR: Temperature exceeded hard-limit");
  if (errorBits.overspeed)       Serial.println("ERROR: Motor commutation speed exceeded hard-limit");
  if (errorBits.demag)           Serial.println("ERROR: Motor stopped due to high demag angle");
}   