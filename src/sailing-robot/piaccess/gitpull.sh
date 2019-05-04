#!/bin/bash
set -e

echo "Pushing to bareclone on the pi at ${SAIL_PI_IP:=192.168.43.59}..."
ssh pi@$SAIL_PI_IP 'cd ~/sailing-robot; git push bareclone master'

echo "Pulling from the pi..."
git pull pi@$SAIL_PI_IP:sailing-robot-bare master
