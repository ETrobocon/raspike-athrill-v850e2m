# raspike-athrill-v850e2m

TOPPERS/EV3RT for Athrill (v850e2m ver.)  
ETロボコン用Fork(SPIKE APIバージョン)
2025年ETロボコン実行委員会

本リポジトリは
https://github.com/toppers/ev3rt-athrill-v850e2m
をETロボコンで使用するシミュレータ用にSPIKE-API対応したものです。

# 使い方
(2025/2/2時点。etrobo環境への統合後は変更になる予定です）
ETロボコン実行委員会が提供しているetrobo環境を使用するのが簡単です。

https://github.com/ETrobocon/etrobo
にしたがって、ETロボコンの環境を作成してください。

作成されたetrobo環境の直下に本リポジトリをcloneします(ev3rt-athrill-v850e2mやworkspaceなどがあるディレクトリと同じ並び)。
以下、$はコマンドプロンプトとです。

```$ git clone --recursive https://github.com/ETrobocon/raspike-athrill-v850e2m.git```

作成されたraspike-athrill-v850e2m/sdk/workspaceの下に移動します。

コマンドプロンプトでシミュレータを立ち上げます。
```$ sim```
動作確認はサンプル用コースで行っています。

その後、サンプルプログラム(sample_c5_spike)をコンパイルします。
```$ make img=sample_c5_spike```

make startで起動します。
```$　make start```
これで右エッジでのライントレース(PD制御)が行われます。

止める時はctl+cで止めます。

# APIの対応
本環境では
https://spike-rt.github.io/spike-rt/en/html/index.html
で定義されているSPIKEのAPIが使えます。ただし、Simulator環境のため、以下の制限があります。

⚪︎：対応　△：一部仕様制限/動作上の違いあり　×：空関数を提供（コンパイルは通るが動作せず、固定値を返す）

| |SPIKE API|対応EV3 API|EV3 Sim対応|Simulator制限|
|:----|:----|:----|:----|:----|
|Battery|hub_battery_get_voltage |ev3_battery_voltage_mV|×|固定値を返す|
| |hub_battery_get_current|ev3_battery_current_mA|×|固定値を返す|
|Bluetooth|hub_bluetooth_enable_advertising|-| | |
| |hub_bluetooth_disable_advertising|-| | |
| |hub_bluetooth_is_connected|-| | |
|Botton|hub_button_is_pressed|ev3_button_is_pressed|○|SPIKEの対応しているものだけ対応|
|Display|hub_display_orientation|-|×| |
| |hub_display_off|-|×| |
| |hub_display_pixel |-|×| |
| |hub_display_image|-|×| |
| |hub_display_number |-|×| |
| |hub_display_char |-|×| |
| |hub_display_text |-|×| |
| |hub_display_text_scroll|-|×| |
|IMU|hub_imu_init|-|○| |
| |hub_imu_get_acceleration| |○| |
| |hub_imu_get_angular_velocity| |○| |
| |hub_imu_get_temperature| |×| |
|Light|hub_light_on_hsv| |×| |
| |hub_light_on_color| |×|右の値のみ設定可能|
| |hub_light_off| |×| |
|Speaker|hub_speaker_set_volume| |×| |
| |hub_speaker_play_tone| |×| |
|System|hub_system_shutdown|-|×| |
|ColorSensor|pup_color_sensor_get_device|ev3_sensor_config|○| |
| |pup_color_sensor_rgb|ev3_color_sensor_get_rgb_raw|○| |
| |pup_color_sensor_hsv|-|△|surfaceの値は無視される|
| |pup_color_sensor_reflection|ev3_color_sensor_get_reflect|○| |
| |pup_color_sensor_ambient|ev3_color_sensor_get_ambient|○| |
| |pup_color_sensor_light_set |-|×| |
| |pup_color_sensor_light_on |-|×| |
| |pup_color_sensor_light_off|-|×| |
| |pup_color_sensor_color| |△|BLACK,BLUE,GREEN,YELLOW,RED,WHITE,BROWNだけサポート。Detectableには影響されない。surfaceの値は無視される。2025/2/2時点では未実装|
| |pup_color_sensor_detectable_colors|-|×| |
|ForceSensor|pup_force_sensor_get_device|ev3_sensor_config|○| |
| |pup_force_sensor_force | |×| |
| |pup_force_sensor_distance | |×| |
| |pup_force_sensor_pressed|ev3_touch_sensor_is_pressed|△|touchedと同じ動作。forceは無視される|
| |pup_force_sensor_touched| |○| |
|Motor|pup_motor_get_device |ev3_motor_config|○| |
| |pup_motor_setup|(ev3_motor_reset_counts)|○| |
| |pup_motor_reset_count | |○| |
| |pup_motor_get_count| |○| |
| |pup_motor_get_speed| |△|speedの維持はされず、get_powerと同じ挙動を行う|
| |pup_motor_set_speed | |△|speedの維持はされず、set_powerと同じ挙動を行う|
| |pup_motor_get_power | |○| |
| |pup_motor_set_power | |○| |
| |pup_motor_stop| |○| |
| |pup_motor_brake| |○| |
| |pup_motor_hold | |○| |
| |pup_motor_is_stalled| |×| |
| |pup_motor_set_duty_limit| |×| |
| |pup_motor_restore_duty_limit | |×| |
|Ultrasonic Sensor|pup_ultrasonic_sensor_get_device| |○| |
| |pup_ultrasonic_sensor_distance| |○| |
| |pup_ultrasonic_sensor_presence| |×| |
| |pup_ultrasonic_sensor_light_set | |×| |
| |pup_ultrasonic_sensor_light_on| |×| |
| |pup_ultrasonic_sensor_light_off| |×| |


## Windows+WSLでのIP Addressの設定
Windows環境ではWindowsとWSL間で通信させるためにsdk/common/device_config.txtのIPアドレスを修正する必要があります。

```ip route | grep 'default via' | grep -o -E '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}'```

で取得できるIPを
DEBUG_FUNC_VDEV_TX_IPADDR
として設定する必要があります。

## Note

- TOPPERS/ASP3 kernel was employed instead of HRP3.
- This repo has been distributed under [TOPPERS License](http://toppers.jp/en/license.html)


