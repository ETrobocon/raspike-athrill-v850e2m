#include <stdio.h>
#include <string.h>

#include "raspike_device.h"
#include "ev3_vdev.h"
#include "sil.h"
#include "motor.h"



pup_motor_t *pup_motor_get_device(pbio_port_id_t port)
{
  pup_device_t  *pdev = create_device_by_portid(port,DEVICE_TYPE_MOTOR);

  return (pup_motor_t*)pdev;    
}

pbio_error_t pup_motor_setup(pup_motor_t *motor, pup_direction_t positive_direction, bool reset_count)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  pdev->direction = positive_direction; 
  if ( reset_count ) {
    return pup_motor_reset_count(motor);
  }
  return PBIO_SUCCESS;

}

pbio_error_t pup_motor_reset_count(pup_motor_t *motor)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  int index = pdev->port_id;
  sil_wrw_mem((uint32_t*)EV3_MOTOR_ADDR_INX(index), 0U);
	sil_wrw_mem((uint32_t*)EV3_MOTOR_ADDR_INX(EV3_MOTOR_INX_RESET_ANGLE_A+index), 1U);
	return PBIO_SUCCESS;
}

int32_t pup_motor_get_count(pup_motor_t *motor)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  int index = pdev->port_id;
  return sil_rew_mem( (const uint32_t *)EV3_SENSOR_MOTOR_ADDR_INX(index));
}

int32_t pup_motor_get_speed(pup_motor_t *motor)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  return pdev->power;
}  

pbio_error_t pup_motor_set_speed(pup_motor_t *motor, int speed)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  pdev->power = speed;
  if ( pdev->direction == PUP_DIRECTION_COUNTERCLOCKWISE ) {
    speed = -speed;
  }
  sil_wrw_mem((uint32_t*)EV3_MOTOR_ADDR_INX(pdev->port_id+EV3_MOTOR_INX_POWER_TOP), speed);
  return PBIO_SUCCESS;
}

int32_t pup_motor_get_power(pup_motor_t *motor)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  return pdev->power;
}

pbio_error_t pup_motor_set_power(pup_motor_t *motor, int power)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  pdev->power = power;
  if ( pdev->direction == PUP_DIRECTION_COUNTERCLOCKWISE ) {
      power = -power;
  }
  sil_wrw_mem((uint32_t*)EV3_MOTOR_ADDR_INX(pdev->port_id+EV3_MOTOR_INX_POWER_TOP), power);
  return PBIO_SUCCESS;
}

pbio_error_t pup_motor_stop(pup_motor_t *motor)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  pdev->power = 0;
  pup_motor_set_power(motor, 0);
  return PBIO_SUCCESS;

}


pbio_error_t pup_motor_brake(pup_motor_t *motor)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  pdev->power = 0;
  pup_motor_set_power(motor, 0);
  sil_wrw_mem((uint32_t*)EV3_MOTOR_ADDR_INX(pdev->port_id+EV3_MOTOR_INX_STOP_TOP), false);  
  return PBIO_SUCCESS;
}

pbio_error_t pup_motor_hold(pup_motor_t *motor)
{
  pup_device_t *pdev = (pup_device_t*)motor;
  ENSURE_VALID_DEVICE(pdev);
  pdev->power = 0;
  pup_motor_set_power(motor, 0);
  sil_wrw_mem((uint32_t*)EV3_MOTOR_ADDR_INX(pdev->port_id+EV3_MOTOR_INX_STOP_TOP), true);  
  return PBIO_SUCCESS;
}

bool pup_motor_is_stalled(pup_motor_t *motor)
{
  // Not supported
  return false;
}

int32_t pup_motor_set_duty_limit(pup_motor_t *motor, int duty_limit)
{
  /* Not supported*/
  return 0;
}


void pup_motor_restore_duty_limit(pup_motor_t *motor, int old_value)
{
  /* Not supported*/
  return;
}



