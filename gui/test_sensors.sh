#!/bin/bash

while true; do
    LC_NUMERIC="en_US.UTF-8"
    
    # Define range and frequency for sinusoidal variation
    roll_range=5  # Range for roll variation
    pitch_range=2 # Range for pitch variation
    yaw_range=30  # Range for yaw variation
    frequency=0.1 # Frequency of sinusoidal variation (adjust as needed)

    # Calculate sinusoidal variations for roll, pitch, and yaw
    time=$(date +%s.%N)
    roll=$(awk -v time="$time" -v range="$roll_range" -v freq="$frequency" 'BEGIN{print range * sin(2 * 3.14159 * freq * time)}')
    pitch=$(awk -v time="$time" -v range="$pitch_range" -v freq="$frequency" 'BEGIN{print range * sin(2 * 3.14159 * freq * time)}')
    yaw=$(awk -v time="$time" -v range="$yaw_range" -v freq="$frequency" 'BEGIN{print range * sin(2 * 3.14159 * freq * time)}')

    # Randomize other values
    pidState=$(shuf -i 0-2 -n 1)
    armed=$(shuf -i 0-1 -n 1)
    depth=$(awk -v min=0 -v max=100 'BEGIN{srand(); print min+rand()*(max-min)/100}')
    tempInt=$(awk -v min=20 -v max=30 'BEGIN{srand(); print min+rand()*(max-min)}')
    tempExt=$(awk -v min=10 -v max=20 'BEGIN{srand(); print min+rand()*(max-min)}')

    # Create the JSON string
    json_data=$(printf '{"pidState":%d, "armed":%d, "depth":%.2f, "yaw":%.2f, "roll":%.2f, "pitch":%.2f, "tempInt":%.2f, "tempExt":%.2f}' \
                  "$pidState" "$armed" "$depth" "$yaw" "$roll" "$pitch" "$tempInt" "$tempExt")

    # Publish to Mosquitto
    mosquitto_pub -t 'gui/' -h 127.0.0.1 -m "$json_data"
    
    # Sleep for 0.1 second
    sleep 0.0001
done