// ESCDefines.h was generated by ProtoGen version 3.2.a

/*
 * Copyright Currawong Engineering Pty Ltd
 * www.currawongeng.com
 * all rights reserved
 */
 

#ifndef _ESCDEFINES_H
#define _ESCDEFINES_H

// Language target is C, C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file
 */

#include <stdbool.h>
#include "ESCVelocityProtocol.h"

/*!
 * The *status* of the ESC is represented using these status bits. ESC system
 * functionality can be quickly determined using these bits
 */
typedef struct
{
    bool    hwInhibit;        //!< Set if hardware inhibit is active (ESC is disabled)
    bool    swInhibit;        //!< Set if software inhibit is active (ESC is disabled)
    bool    afwEnabled;       //!< Set if Active Freewheeling is currently active
    uint8_t direction;        //!< 0 = Motor direction is FORWARDS, 1= Motor direction is REVERSE
    bool    timeout;          //!< Set if the ESC command timeout period has elapsed (and the ESC is in STANDBY mode)
    bool    starting;         //!< Set if ESC is in starting mode (Cleared if ESC is stopped or running)
    uint8_t commandSource;    //!< 0 = most recent command from CAN, 1 = most recent command from PWM
    bool    running;          //!< Set if ESC is running
    bool    anyWarnings;      //!< Warning active - refer to the PKT_ESC_WARNINGS_ERRORS packet
    bool    anyErrors;        //!< Error active - refer to the PKT_ESC_WARNINGS_ERRORS packet
    bool    spinning;         //!< Set if the motor is spinning (even if it is not being driven)
    bool    spinningReversed; //!< Set if motor is spinning opposite to configured rotation direction
    bool    foldback;         //!< Set if motor duty cycle is being limited due to ESC protection settings
    bool    syncing;          //!< Set if the ESC is attempting to sync with the motor
    bool    debug;            //!< Set if the ESC is in debug mode (factory use only)
}ESC_StatusBits_t;

//! return the minimum encoded length for the ESC_StatusBits_t structure
#define getMinLengthOfESC_StatusBits_t() (3)

//! return the maximum encoded length for the ESC_StatusBits_t structure
#define getMaxLengthOfESC_StatusBits_t() (3)

//! Encode a ESC_StatusBits_t into a byte array
void encodeESC_StatusBits_t(uint8_t* data, int* bytecount, const ESC_StatusBits_t* user);

//! Decode a ESC_StatusBits_t from a byte array
int decodeESC_StatusBits_t(const uint8_t* data, int* bytecount, ESC_StatusBits_t* user);

/*!
 * The *warning* bits enumerate various system warnings/errors of which the
 * user (or user software) should be made aware. These *warning* bits are
 * transmitted in the telemetry packets such that user software is aware of any
 * these *warning* conditions and can poll the ESC for particular packets if
 * any further information is needed. The ESC will continue to function in the
 * case of a *warning* state
 */
typedef struct
{
    bool reserved;           //!< Reserved for future use. Field is encoded constant.
    bool overspeed;          //!< Set if the ESC motor speed exceeds the configured warning threshold
    bool overcurrent;        //!< Set if the ESC motor current (positive or negative) exceeds the configured warning threshold
    bool escTemperature;     //!< Set if the internal ESC temperature is above the warning threshold
    bool motorTemperature;   //!< Set if the motor temperature is above the warning threshold
    bool undervoltage;       //!< Set if the input voltage is below the minimum threshold
    bool overvoltage;        //!< Set if the input voltage is above the maximum threshold
    bool invalidPWMsignal;   //!< Set if hardware PWM input is enabled but invalid
    bool demagAngle;         //!< Set if the motor demag angle exceeds the maximum threshold
    bool advanceLimit;       //!< Set if the auto-advance exceeds 25 degrees
    bool longDemag;          //!< Set if the measured demag pulse is exceptionally long
    bool missedZeroCrossing; //!< Set if a zero-crossing measurement was missed
    bool spinningReversed;   //!< Motor is spinning in the wrong direction
    bool commSpeedLimit;     //!< Motor has reached maximum allowable commutation speed
}ESC_WarningBits_t;

//! return the minimum encoded length for the ESC_WarningBits_t structure
#define getMinLengthOfESC_WarningBits_t() (2)

//! return the maximum encoded length for the ESC_WarningBits_t structure
#define getMaxLengthOfESC_WarningBits_t() (2)

//! Encode a ESC_WarningBits_t into a byte array
void encodeESC_WarningBits_t(uint8_t* data, int* bytecount, const ESC_WarningBits_t* user);

//! Decode a ESC_WarningBits_t from a byte array
int decodeESC_WarningBits_t(const uint8_t* data, int* bytecount, ESC_WarningBits_t* user);

/*!
 * The *error* bits enumerate critical system errors that will cause the ESC to
 * stop functioning until the error cases are alleviated
 */
typedef struct
{
    uint8_t failedStart;     //!< Set if the ESC failed to start the motor
    uint8_t commutation;     //!< Lost commutation
    uint8_t hallSensor;      //!< Set if hall sensor error detected
    uint8_t overcurrent;     //!< Current exceeded hard-limit
    uint8_t overtemperature; //!< Temperature exceeded hard-limit
    uint8_t overspeed;       //!< Motor commutation speed exceeded hard-limit
    uint8_t demag;           //!< Motor stopped due to high demag angle
}ESC_ErrorBits_t;

//! return the minimum encoded length for the ESC_ErrorBits_t structure
#define getMinLengthOfESC_ErrorBits_t() (2)

//! return the maximum encoded length for the ESC_ErrorBits_t structure
#define getMaxLengthOfESC_ErrorBits_t() (2)

//! Encode a ESC_ErrorBits_t into a byte array
void encodeESC_ErrorBits_t(uint8_t* data, int* bytecount, const ESC_ErrorBits_t* user);

//! Decode a ESC_ErrorBits_t from a byte array
int decodeESC_ErrorBits_t(const uint8_t* data, int* bytecount, ESC_ErrorBits_t* user);

/*!
 * These bits are used to determine which packets are automatically transmitted
 * as telemetry data by the ESC. Only the packets described here can be
 * configured as telemetry packets
 */
typedef struct
{
    bool statusA;         //!< If this bit is set, the STATUS_A packet will be transmitted at the configured rate
    bool statusB;         //!< If this bit is set, the STATUS_B packet will be transmitted at the configured rate
    bool statusC;         //!< If this bit is set, the STATUS_C packet will be transmitted at the configured rate
    bool accelerometer;   //!< If this bit is set, the ACCELEROMETER packet will be transmitted at the configured rate
    bool statusD;         //!< If this bit is set, the STATUS_D packet will be transmitted at the configured rate
    bool reservedTelemA;  //!< Reserved for future use
    bool piccoloDownlink; //!< If this bit is set, any STATUS_x packets selected for telemetry will be mirrored on the Piccolo Downlink packet group (0x14)
    bool reservedTelemC;  //!< Reserved for future use
}ESC_TelemetryPackets_t;

//! return the minimum encoded length for the ESC_TelemetryPackets_t structure
#define getMinLengthOfESC_TelemetryPackets_t() (1)

//! return the maximum encoded length for the ESC_TelemetryPackets_t structure
#define getMaxLengthOfESC_TelemetryPackets_t() (1)

//! Encode a ESC_TelemetryPackets_t into a byte array
void encodeESC_TelemetryPackets_t(uint8_t* data, int* bytecount, const ESC_TelemetryPackets_t* user);

//! Decode a ESC_TelemetryPackets_t from a byte array
int decodeESC_TelemetryPackets_t(const uint8_t* data, int* bytecount, ESC_TelemetryPackets_t* user);

/*!
 * These bits are used to select which debug packets are transmitted at
 * high-frequency by the ESC
 */
typedef struct
{
    bool ctrlLoopOutputs; //!< Control loop terms
    bool hallSensors;     //!< Hall sensor debug information
    bool commutation;     //!< Commutation debug information
    bool demag;           //!< Demag debug information
    bool pwmInput;        //!< PWM input debug information
}ESC_DebugPackets_t;

//! return the minimum encoded length for the ESC_DebugPackets_t structure
#define getMinLengthOfESC_DebugPackets_t() (2)

//! return the maximum encoded length for the ESC_DebugPackets_t structure
#define getMaxLengthOfESC_DebugPackets_t() (2)

//! Encode a ESC_DebugPackets_t into a byte array
void encodeESC_DebugPackets_t(uint8_t* data, int* bytecount, const ESC_DebugPackets_t* user);

//! Decode a ESC_DebugPackets_t from a byte array
int decodeESC_DebugPackets_t(const uint8_t* data, int* bytecount, ESC_DebugPackets_t* user);

#ifdef __cplusplus
}
#endif
#endif // _ESCDEFINES_H
