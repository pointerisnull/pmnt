#ifndef MODBUS_DRIVER_H
#define MODBUS_DRIVER_H

#include "../misc/typedefs.h"
#include "../misc/bitset.h"

#define MAX_FRAME_SIZE          256
#define MAX_DATA_SIZE           250
#define MAX_SLAVE_ADDRESSES     256
#define MAX_REGISTERS           256
#define MAX_COILS               1024

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
/*
The MODBUS protocol defines three PDUs. They are :
    MODBUS Request PDU, mb_req_pdu
    MODBUS Response PDU, mb_rsp_pdu
    MODBUS Exception Response PDU, mb_excep_rsp_pdu

The mb_req_pdu is defined as:
    mb_req_pdu = {function_code, request_data}, where
        function_code = [1 byte] MODBUS function code,
        request_data = [n bytes] This field is function code dependent and usually
         contains information such as variable references,
         variable counts, data offsets, sub-function codes etc.
    The mb_rsp_pdu is defined as:
        mb_rsp_pdu = {function_code, response_data}, where
        function_code = [1 byte] MODBUS function code
        response_data = [n bytes] This field is function code dependent and usually
         contains information such as variable references,
         variable counts, data offsets, sub-function codes, etc.
    The mb_excep_rsp_pdu is defined as:
        mb_excep_rsp_pdu = {exception-function_code, request_data}, where
        exception-function_code = [1 byte] MODBUS function code + 0x80
        exception_code = [1 byte] MODBUS Exception Code Defined in table

*/

typedef struct mb_pdu {
    byte_t func_code;
    word_t reg_addr;
    byte_t data[MAX_DATA_SIZE];
    size_t data_size;
} mb_pdu;

#pragma pack(push, 1) // Ensure data is packed together
struct mb_frame {
    byte_t address;
    mb_pdu pdu;
    crc16_t crc;
};
#pragma pack(pop)

struct mb_data_model {
    byte_t coils[MAX_COILS/8];
    byte_t discrete_inputs[MAX_COILS/8];
    word_t holding_registers[MAX_REGISTERS];
    word_t input_registers[MAX_REGISTERS];

} mb_data_model;

struct mb_master_node {
    // Address 0 - Broadcast address
    // Address 1->247 - Slave addresses
    // Address 248->255 - Reserved
    byte_t addresses[MAX_SLAVE_ADDRESSES];

    struct mb_data_model data;
};

struct mb_slave_node {
    byte_t addr;

    struct mb_data_model data;
};

mb_pdu gen_pdu(byte_t *data, size_t size);
mb_pdu assemble_pdu(byte_t func_code, word_t reg_addr, byte_t *data, size_t size);
struct mb_frame assemble_frame(byte_t address, mb_pdu *pdu);
crc16_t gen_crc(byte_t address, mb_pdu *pdu);

#endif