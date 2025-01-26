#include <stdio.h>
#include "raspike_device.h"
#include "ev3_vdev.h"
#include "sil.h"
#include "pbio/color.h"
#include "pbio/error.h"
#include "pup/forcesensor.h"
  
pup_device_t *pup_force_sensor_get_device(pbio_port_id_t port)
{
  pup_device_t  *pdev = create_device_by_portid(port,DEVICE_TYPE_FORCE);

  return pdev;    
}


float pup_force_sensor_force(pup_device_t *pdev)
{
	uint32_t data ;
	uint32_t *addr;

  addr = (uint32_t *)EV3_SENSOR_ADDR_TOUCH_0;

	data = sil_rew_mem(addr);

  return (float)data;
}

float pup_force_sensor_distance(pup_device_t *pdev)
{
  // Not supported
  return 0.0;

}

bool pup_force_sensor_pressed(pup_device_t *pdev, float force)
{
  return pup_force_sensor_touched(pdev);

}

bool pup_force_sensor_touched(pup_device_t *pdev)
{
	uint32_t data ;
	uint32_t *addr;

  addr = (uint32_t *)EV3_SENSOR_ADDR_TOUCH_0;

	data = sil_rew_mem(addr);

  return data > 0;
}
