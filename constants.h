#pragma once

#define VOUT_MODE_VAL 0x17

#define PAGE                    0x00
#define OPERATION               0x01
#define ON_OFF_CONFIG           0x02
#define CLEAR_FAULTS            0x03
#define PAGE_PLUS_WRITE         0x05
#define PAGE_PLUS_READ          0x06
#define WRITE_PROTECT           0x10
#define STORE_USER_ALL          0x15
#define RESTORE_USER_ALL        0x16
#define CAPABILITY              0x19
#define MFR_COMPARE_USER_ALL    0xF0
#define SMBALERT_MASK           0x1B
#define VOUT_MODE               0x20
#define VOUT_COMMAND            0x21
#define VOUT_MAX                0x24
#define VOUT_MARGIN_HIGH        0x25
#define VOUT_MARGIN_LOW         0x26
#define VOUT_OV_FAULT_LIMIT     0x40
#define VOUT_OV_FAULT_RESPONSE  0x41
#define VOUT_OV_WARN_LIMIT      0x42
#define VOUT_UV_WARN_LIMIT      0x43
#define VOUT_UV_FAULT_LIMIT     0x44
#define VOUT_UV_FAULT_RESPONSE  0x45
#define IOUT_OC_FAULT_LIMIT     0x46
#define IOUT_OC_WARN_LIMIT      0x4A
#define OT_FAULT_LIMIT          0x4F
#define OT_WARN_LIMIT           0x51
#define UT_FAULT_LIMIT          0x53
#define UT_WARN_LIMIT           0x52
#define VIN_OV_FAULT_LIMIT      0x55
#define VIN_OV_WARN_LIMIT       0x57
#define VIN_UV_WARN_LIMIT       0x58
#define VIN_UV_FAULT_LIMIT      0x59
#define TON_DELAY               0x60
#define TON_RISE                0x61
#define TON_MAX_FAULT_LIMIT     0x62
#define TON_MAX_FAULT_RESPONSE  0x63
#define TOFF_DELAY              0x64
#define TOFF_FALL               0x65
#define TOFF_MAX_WARN_LIMIT     0x66
#define IIN_OC_WARN_LIMIT       0x5D
#define STATUS_BYTE             0x78
#define STATUS_WORD             0x79
#define STATUS_VOUT             0x7A
#define STATUS_IOUT             0x7B
#define STATUS_INPUT            0x7C
#define STATUS_TEMP             0X7D
#define STATUS_CML              0x7E
#define STATUS_MFR_SPECIFIC     0x80
#define STATUS_FANS_1_2         0x81
#define READ_VIN                0x88
#define READ_IIN                0x89
#define READ_VOUT               0x8B
#define READ_IOUT               0x8C
#define READ_TEMPERATURE_1      0x8D    
#define READ_ITEMP              0x8E
#define READ_FAN_SPEED_1        0x90
#define READ_FAN_SPEED_2        0x91
#define READ_DUTY_CYCLE         0x94    // Controllers only, sans LTC3884
#define READ_POUT               0x96
#define READ_PIN                0x97
#define MFR_MODEL               0x9A    // LTC388X only
#define MFR_REVISION            0x9B
#define MFR_DATE                0x9D
#define PMBUS_REVISION          0x98
#define USER_DATA_03            0xB3    // Not LTC2978/A
#define USER_DATA_04            0xB4    // Not LTC2978/A
#define MFR_EE_UNLOCK           0xBD
#define MFR_EE_ERASE            0xBE
#define MFR_EE_DATA             0xBF
#define MFR_CONFIG_LTC2974      0xD0
#define MFR_CONFIG_ALL          0xD1
#define MFR_WATCHDOG_T_FIRST    0xE2
#define MFR_WATCHDOG_T          0xE3
#define MFR_PADS                0xE5
#define MFR_SPECIAL_ID          0xE7
#define MFR_FAULT_LOG_STORE     0xEA
#define MFR_FAULT_LOG_RESTORE   0xEB
#define MFR_FAULT_LOG_CLEAR     0xEC
#define MFR_READ_IIN            0xED    // LTC3880
#define MFR_FAULT_LOG_STATUS    0xED    // LTC297X only
#define MFR_FAULT_LOG           0xEE
#define MFR_COMMON              0xEF
#define MFR_SPARE_0             0xF7    // LTC2978/A
#define MFR_SPARE_1             0xF8    // LTC2978A
#define MFR_SPARE_2             0xF9    // LTC2978/A
#define MFR_SPARE_3             0xFA    // LTC2978A
#define MFR_TEMP_1_GAIN         0xF8
#define MFR_EEPROM_STATUS       0xF1    // LTC388X only
#define MFR_RAIL_ADDRESS        0xFA    // Controllers only
#define MFR_RESET               0xFD


