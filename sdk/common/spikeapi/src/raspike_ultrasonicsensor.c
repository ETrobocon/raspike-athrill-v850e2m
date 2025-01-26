#include <stdio.h>
#include "raspike_device.h"
#include "ev3_vdev.h"
#include "sil.h"
#include "ultrasonicsensor.h"
  
pup_device_t *pup_ultrasonic_sensor_get_device(pbio_port_id_t port)
{
  pup_device_t  *pdev = create_device_by_portid(port,DEVICE_TYPE_ULTRASONIC);

  return pdev;    
}


int32_t pup_ultrasonic_sensor_distance(pup_device_t *pdev)
{
	uint32_t data;
	const uint32_t *addr;
	addr = (const uint32_t *)EV3_SENSOR_ADDR_ULTRASONIC;
  data = sil_rew_mem(addr);
  return (int32_t)data;
}


bool pup_ultrasonic_sensor_presence(pup_device_t *pdev)
{
  // Not supported
  return false;
}

pbio_error_t pup_ultrasonic_sensor_light_set(pup_device_t *pdev, 
                                             int32_t bv1, int32_t bv2, int32_t bv3, int32_t bv4)
{
  // Not supported
  return PBIO_SUCCESS;
}  


pbio_error_t pup_ultrasonic_sensor_light_on(pup_device_t *pdev)
{
  // Not supported
  return PBIO_SUCCESS;
}
 
pbio_error_t pup_ultrasonic_sensor_light_off(pup_device_t *pdev)
{
  // Not supported
  return PBIO_SUCCESS;
}
