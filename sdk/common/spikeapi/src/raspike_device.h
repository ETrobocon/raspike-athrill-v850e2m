#ifndef __RASPIKE_DEVICE_H_
#define __RASPIKE_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "spike/pup_device.h"

// For Simulator 
#define PORT_TO_RASPIKE(port) ((RasPikePort)(port - PBIO_PORT_ID_A))
#define ENSURE_VALID_DEVICE(port) 


// Device type
#define DEVICE_TYPE_MOTOR (0x01)
#define DEVICE_TYPE_COLOR (0x02)
#define DEVICE_TYPE_ULTRASONIC (0x03)
#define DEVICE_TYPE_FORCE (0x04)

typedef unsigned char RasPikePort;

struct _pup_device_t
{
  RasPikePort port_id;
  unsigned char device_type;
  unsigned char direction; // for motor
  int32_t power; // for motor
};

pup_device_t* get_device_by_portid(pbio_port_id_t portid);
pup_device_t* create_device_by_portid(pbio_port_id_t portid, unsigned char device_type);
#define RP_PORT_NUMBER (6)
  
#ifdef __cplusplus
}
#endif

  
#endif /* !__RASPIKE_DEVICE_H_ */
