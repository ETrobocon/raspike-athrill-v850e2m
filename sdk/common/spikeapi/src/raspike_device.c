#include <stdio.h>
#include "raspike_device.h"
#include "spike/pup_device.h"
#include "spikeapi.h"

#define NUM_DEVICES RP_PORT_NUMBER

static pup_device_t device_table[NUM_DEVICES] = {0};

pup_device_t* get_device_by_portid(pbio_port_id_t portid) {
    RasPikePort port_id = PORT_TO_RASPIKE(portid);
    if (port_id < 0 || port_id >= NUM_DEVICES) {
        return NULL; // Invalid portid
    }
    if (device_table[port_id].port_id == 0) {
        return NULL; // Device not found
    }

    return &device_table[port_id];
}

pup_device_t* create_device_by_portid(pbio_port_id_t portid, unsigned char device_type) {
    RasPikePort port_id = PORT_TO_RASPIKE(portid);
    if (port_id < 0 || port_id >= NUM_DEVICES) {
        return NULL; // Invalid portid
    }
    if (device_table[port_id].port_id != 0) {
        return NULL; // Device already exists
    }

    device_table[port_id].port_id = port_id;
    device_table[port_id].device_type = device_type;
    return &device_table[port_id];
}
