#!/bin/bash

export PATH=/root/hakoniwa-core/impl/asset/client/build/cpp:${PATH}
cd /root/workspace 

bash config/create_config.bash park_ride00 eth0

cd proxy

bash hakoniwa_proxy.bash
