#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "raspike_device.h"
#include "ev3_vdev.h"
#include "sil.h"
#include "color.h"
#include "error.h"
#include "hub/button.h"
#include "battery.h"
#include "speaker.h"

/* Battery */

uint16_t hub_battery_get_voltage(void)
{
  // 固定値を返す
  return 50;  
}

uint16_t hub_battery_get_current(void)
{
  // 固定値を返す
  return 50;  

}

/* Button */
pbio_error_t hub_button_is_pressed(hub_button_t *pressed)
{
		uint8_t data = sil_reb_mem((const uint8_t *)EV3_GPIO_BTN_ADDR);
    *pressed = 0;

    if ( data & EV3_GPIO_BTN_LEFT ) {
      *pressed |= HUB_BUTTON_LEFT;
    } 
    if ( data & EV3_GPIO_BTN_RIGHT ) {
      *pressed |= HUB_BUTTON_RIGHT;
    } 
    if ( data & EV3_GPIO_BTN_ENTER ) {
      *pressed |= HUB_BUTTON_CENTER;
    }
    if ( data & EV3_GPIO_BTN_BACK ) {
      *pressed |= HUB_BUTTON_BT;
    }
    return PBIO_SUCCESS;

}


/* Display */
pbio_error_t hub_display_orientation(uint8_t up)
{
  /* Not Support */
  return PBIO_SUCCESS;

}

pbio_error_t hub_display_off(void)
{
  /* Not Support */
  return PBIO_SUCCESS;
}


pbio_error_t hub_display_pixel(uint8_t row, uint8_t column, uint8_t brightness)
{
  /* Not Support */
  return PBIO_SUCCESS;
}


pbio_error_t hub_display_image(uint8_t* image)
{
  /* Not Support */
  return PBIO_SUCCESS;
}


pbio_error_t hub_display_number(const int8_t num)
{
  /* Not Support */
  return PBIO_SUCCESS;
}

pbio_error_t hub_display_char(const char c)
{
  /* Not Support */
  return PBIO_SUCCESS;
}

pbio_error_t hub_display_text(const char* text, uint32_t on, uint32_t off)
{
  /* Not Support */
  return PBIO_SUCCESS;
}

pbio_error_t hub_display_text_scroll(const char* text, uint32_t delay)
{
  /* Not Support */
  return PBIO_SUCCESS;

}


/* IMU */

pbio_error_t hub_imu_init(void)
{
  /* hub_imu_init is automatically called on spike.
     so, just return OK */

  return PBIO_SUCCESS;
}

void hub_imu_get_acceleration(float accel[3])
{
  uint32_t data;
  uint32_t *addr;

  addr = (uint32_t *)SPIKE_SENSOR_IMU_ADDR_ACCELARATION_X;
  data = sil_rew_mem(addr);
  memcpy(accel,&data,sizeof(float));
  addr = (uint32_t *)SPIKE_SENSOR_IMU_ADDR_ACCELARATION_Y;
  data = sil_rew_mem(addr);
  memcpy(accel+1,&data,sizeof(float));
  addr = (uint32_t *)SPIKE_SENSOR_IMU_ADDR_ACCELARATION_Z;
  data = sil_rew_mem(addr);
  memcpy(accel+2,&data,sizeof(float));
  
}

void hub_imu_get_angular_velocity(float angv[3])
{
  int32_t data;
  uint32_t *addr;

  addr = (uint32_t *)SPIKE_SENSOR_IMU_ADDR_VELOCITY_X;
  data = sil_rew_mem(addr);
  memcpy(angv,&data,sizeof(float));
  addr = (uint32_t *)SPIKE_SENSOR_IMU_ADDR_VELOCITY_Y;
  data = sil_rew_mem(addr);
  memcpy(angv+1,&data,sizeof(float));
  addr = (uint32_t *)SPIKE_SENSOR_IMU_ADDR_VELOCITY_Z;
  data = sil_rew_mem(addr);
  memcpy(angv+2,&data,sizeof(float));

}


float hub_imu_get_temperature(void)
{
  // TODO:
  // Not Supported
  return 0.0;
}
  
/* Light */
pbio_error_t hub_light_on_hsv(const pbio_color_hsv_t *hsv)
{
  // Not Supported

  return PBIO_SUCCESS;
}

pbio_error_t hub_light_on_color(pbio_color_t color)
{
  uint8_t *addr = (uint8_t *)EV3_GPIO_LED_ADDR;
  uint8_t data = 0;  
  switch (color) {
    case PBIO_COLOR_BLACK:
      break;
    case PBIO_COLOR_BLUE:
      data = EV3_GPIO_LED_BLUE;
      break;
    case PBIO_COLOR_CYAN:
      break;
    case PBIO_COLOR_GREEN:
      data = EV3_GPIO_LED_GREEN;
      break;
    case PBIO_COLOR_ORANGE:
      break;
    case PBIO_COLOR_RED:
      data = EV3_GPIO_LED_RED;
      break;
    case PBIO_COLOR_WHITE:
      break;
    case PBIO_COLOR_YELLOW:
      data = EV3_GPIO_LED_YELLOW;
      break;
    default:
      break;
  }
  sil_wrb_mem(addr, data);
  return PBIO_SUCCESS;
}

pbio_error_t hub_light_off(void)
{
  uint8_t *addr = (uint8_t *)EV3_GPIO_LED_ADDR;
  uint8_t data = 0;  
  sil_wrb_mem(addr, data);
  return PBIO_SUCCESS;
}

void hub_speaker_set_volume(uint8_t volume)
{
  // Not Supported
}

void hub_speaker_play_tone(uint16_t frequency, int32_t duration)
{
  // Not Supported
}
  
  
void hub_speaker_stop(void)
{
  // Not Supported
}

  
/* System Command */
void hub_system_shutdown(void)
{


}

  
