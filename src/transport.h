//
// Created by Andrey Popikov on 11.01.2020.
//

#ifndef HAP_OVER_BLE_TRANSPORT_H
#define HAP_OVER_BLE_TRANSPORT_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum OpCode : uint8_t {
    Characteristic_Signature_Read = 0x01,
    Characteristic_Write = 0x02,
    Characteristic_Read = 0x03,
    Characteristic_Timed_Write = 0x04,
    Characteristic_Execute_Write = 0x05,
    Service_Signature_Read = 0x06,
    Characteristic_Configuration = 0x07,
    Protocol_Configuration = 0x08
};

enum Params : uint8_t {
    Value = 0x01,
    Additional_Authorization_Data = 0x02,
    Origin = 0x03,
    Characteristic_Type = 0x04,
    Characteristic_Instance_ID = 0x05,
    Service_Type = 0x06,
    Service_Instance_ID = 0x07,
    TTL = 0x08,
    Return_Response = 0x09,
    HAP_Characteristic_Properties_Descriptor = 0x0A,
    GATT_User_Description_Descriptor = 0x0B,
    GATT_Presentation_Format_Descriptor = 0x0C,
    GATT_Valid_Range = 0x0D,
    HAP_Step_Value_Descriptor = 0x0E,
    HAP_Service_Properties = 0x0F,
    HAP_Linked_Services = 0x10,
    HAP_Valid_Values_Descriptor = 0x11,
    HAP_Valid_Values_Range_Descriptor = 0x12
};

typedef struct {
    enum Params type; // see HAP_Param_* defs for values
    uint8_t length;
    char *data;
} tlv8;

tlv8 read_tlv8(char *data) {
    tlv8 result;
    result.type = data[0];
    result.length = data[1];
    result.data = malloc(sizeof(char) * result.length);
    memcpy(result.data, &data[2], result.length);
    return result;
}

uint16_t read_tlv8_array(char *data, uint16_t data_length, tlv8 **result) {
    uint16_t i = 0;
    uint16_t count = 0;
    // count all records
    while (i <= data_length) {
        uint8_t l = data[i + 1];
        i += l;
        count++;
    }
    // parse
    uint16_t offset = 0;
    result = malloc(sizeof(tlv8 *) * count);
    for (i = 0; i < count; i++) {
        uint8_t l = data[offset + 1];
        (*result[i]) = read_tlv8(&data[offset]);
        offset += 2 + l;
    }
    return i;
}

typedef struct {
    unsigned int fragment : 1; // 0 - first fragment (or no fragmentation at all),
    // 1 - continuation
    unsigned int r6 : 1;
    unsigned int r5 : 1;
    unsigned int iid_size : 1; // 0 - 16-bit IID, 1 - 64-bit IID
    unsigned int type : 3;     // 000 - request, 001 - response
    unsigned int r0 : 1;

} pdu_control_field;

typedef struct {
    uint16_t length;
    char *body;
} pdu_body;

typedef struct {
    pdu_control_field control;
    enum OpCode op_code; // see HAP_OP_CODE_* defs for values
    uint8_t tid;
    uint16_t char_id;
    pdu_body body;
} hap_request;

typedef struct {
    pdu_control_field control;
    uint8_t tid;
    uint8_t status;
    pdu_body body;
} hap_response;

extern void tx();

extern void rx();

#endif // HAP_OVER_BLE_TRANSPORT_H
