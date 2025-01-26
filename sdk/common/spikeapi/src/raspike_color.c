#include <stdio.h>
#include "raspike_device.h"
#include "colorsensor.h"
#include "ev3_vdev.h"
#include "sil.h"


pup_device_t *pup_color_sensor_get_device(pbio_port_id_t port)
{
  pup_device_t  *pdev = create_device_by_portid(port,DEVICE_TYPE_COLOR);

  return pdev;    

}


pup_color_hsv_t pup_color_sensor_color(pup_device_t *pdev, bool surface)
{
  /* TODO */
  pup_color_hsv_t hsv = {0, 0, 0};

  return hsv;
}


pup_color_rgb_t pup_color_sensor_rgb(pup_device_t *pdev)
{
  const uint32_t *addr;
  pup_color_rgb_t rgb;
  ENSURE_VALID_DEVICE(pdev);

  addr = (const uint32_t *)EV3_SENSOR_ADDR_RGB_R(0);
  rgb.r = (int32_t)sil_rew_mem(addr);
  addr = (const uint32_t *)EV3_SENSOR_ADDR_RGB_G(0);
  rgb.g = (int32_t)sil_rew_mem(addr);
  addr = (const uint32_t *)EV3_SENSOR_ADDR_RGB_B(0);
  rgb.b = (int32_t)sil_rew_mem(addr);

  return rgb;
}


pup_color_hsv_t pup_color_sensor_hsv(pup_device_t *pdev, bool surface)
{
  const uint32_t *addr;
  pup_color_hsv_t hsv;
  ENSURE_VALID_DEVICE(pdev);

  addr = (const uint32_t *)SPIKE_SENSOR_HSV_ADDR_H;
  hsv.h = (int32_t)sil_rew_mem(addr);
  addr = (const uint32_t *)SPIKE_SENSOR_HSV_ADDR_S;
  hsv.s = (int32_t)sil_rew_mem(addr);
  addr = (const uint32_t *)SPIKE_SENSOR_HSV_ADDR_V;
  hsv.v = (int32_t)sil_rew_mem(addr);
  return hsv;

}

int32_t pup_color_sensor_reflection(pup_device_t *pdev)
{
  int32_t data;
  const uint32_t *addr;
  ENSURE_VALID_DEVICE(pdev);

  addr = (const uint32_t *)EV3_SENSOR_ADDR_REFLECT(0);
  data = (int32_t)sil_rew_mem(addr);

  return data;

}


int32_t pup_color_sensor_ambient(pup_device_t *pdev)
{
	int32_t data;
	const uint32_t *addr;
  ENSURE_VALID_DEVICE(pdev); 

  addr = (const uint32_t *)EV3_SENSOR_ADDR_AMBIENT(0);
  data = (int32_t)sil_rew_mem(addr);
  return data;  
}

pbio_error_t pup_color_sensor_light_set(pup_device_t *pdev, 
                                             int32_t bv1, int32_t bv2, int32_t bv3)
{
  /* Not Support*/
  return PBIO_SUCCESS;
}

pbio_error_t pup_color_sensor_light_on(pup_device_t *pdev)
{
  /* Not Support*/
  return PBIO_SUCCESS;
}

pbio_error_t pup_color_sensor_light_off(pup_device_t *pdev)
{
  /* Not Support*/
  return PBIO_SUCCESS;
}

/* TODO: RasPike Limitation size must be less than 3 */
pup_color_hsv_t *pup_color_sensor_detectable_colors(int32_t size, pup_color_hsv_t *colors)
{
  /* Not Support */
  return 0; /* TODO */

}
