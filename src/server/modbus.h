#ifndef MODBUS_DRIVER_H
#define MODBUS_DRIVER_H

#include "../misc/typedefs.h"
#include "../misc/bitset.h"

#define MAX_FRAME_SIZE          256
#define MAX_DATA_SIZE           252
#define MAX_SLAVE_ADDRESSES     256

enum MB_FUNCTIONS {
    FUNC01 = 0x1, // Read coils
    FUNC02 = 0x2, // Read discrete inputs
    FUNC03 = 0x3, // Read holding registers
    FUNC04 = 0x4, // Read input registers
    FUNC05 = 0x5, // Write single coil
    FUNC06 = 0x6, // Write single register
    FUNC15 = 0xF, // Write multiple coils
    FUNC16 = 0x10 // Write multiple registers
};

enum MB_EXCEPTIONS {
    ILLEGAL_FUNCTION    = 1,
    ILLEGAL_DATA_ADDR   = 2,
    ILLEGAL_DATA_VALUE  = 3,
    SERVER_DEV_FAILURE  = 4,
    ACK                 = 5,
    SERVER_BUSY         = 6,
    NEG_ACK             = 7,
    MEM_PARITY_ERR      = 8,
    GATEWAY_UNAVAIL     = 10,
    GATEWAY_RESP_FAIL   = 11
};

#pragma pack(push, 1) // Ensure data is packed together
struct mb_RTU_frame {
    byte_t address;
    byte_t function_code;
    byte_t data[MAX_DATA_SIZE];
    crc16_t crc;
};
#pragma pack(pop)

#pragma pack(push, 1) // Ensure data is packed together
struct mb_RTU_ascii_frame {
    char start;
    char address[2];
    char function_code[2];
    char data[MAX_DATA_SIZE*2];
    char lrc[2];
    char end[2]
};
#pragma pack(pop)

#pragma pack(push, 1) // Ensure data is packed together
struct mb_TCP_frame {
    word_t transaction_id;
    word_t protocol_id;
    word_t length; // Number of remaining bytes in this frame
    byte_t unit_id; // Slave address
    byte_t function_code;
    byte_t data[MAX_DATA_SIZE];
};
#pragma pack(pop)

struct mb_master_node {
    // Address 0 - Broadcast address
    // Address 1->247 - Slave addresses
    // Address 248->255 - Reserved
    byte_t addresses[MAX_SLAVE_ADDRESSES];
};


#endif