#!/bin/bash

# helper functions
################################################################################

# run command x, wait some time, run command y
function run_x_wait_y
{
    mosquitto_pub -h 10.0.0.254 -t "commands/" -m "$1"
    sleep $3
    mosquitto_pub -h 10.0.0.254 -t "commands/" -m "$2"
}


# commands
################################################################################

alias shutdown="ssh -t prova@10.0.0.254 sudo poweroff"
alias get_ip="nmap -sP 10.0.0.*"
alias nucleo_upload="scp /data/git-repos/EVA/firmware/nucleo_pid/.pio/build/nucleo_l432kc/firmware.bin prova@10.0.0.254:/media/prova/NODE_L432KC"

function help
{
    echo "commands:"
    echo "  shutdown"
    echo "  gui"
    echo "  watch"
    echo "   - sensors"
    echo "   - commands"
    echo "   - components"
    echo "   - debug"
    echo "  get_ip"
    echo "  arm"
    echo "   - calibrate"
    echo "   - up"
    echo "   - down"
    echo "   - rotate_ccw"
    echo "   - rotate_cw"
    echo "   - open_claw"
    echo "   - close_claw"
    echo "  nucleo_upload"
}

function gui
{
    cd /data/git-repos/EVA/gui && workon eva && python3 main.py
    read -p "Premere invio per chiudere..."
    deactivate
}

function watch
{
    mosquitto_sub -h 10.0.0.254 -t "$1/"
}

function arm
{

    if [[ $1 == "calibrate" ]]; then
    
        mosquitto_pub -h 10.0.0.254 -t commands/ -m TORQUE_OFF
        read -p "Muovi il braccio fino al livello più basso che vuoi ottenere (invio per continuare) "
        mosquitto_pub -h 10.0.0.254 -t commands/ -m TORQUE_ON
        read -p "Il led dovrebbe diventare giallo (invio per continuare) "
        mosquitto_pub -h 10.0.0.254 -t commands/ -m START_CALIBRATION
        read -p "Il led dovrebbe diventare verde. Il braccio si può ora usare (invio per chiudere) "
    
    elif [[ $1 == "up" ]]; then

        run_x_wait_y "SHOULDER_UP" "STOP_SHOULDER" $2
    
    elif [[ $1 == "down" ]]; then

        run_x_wait_y "SHOULDER_DOWN" "STOP_SHOULDER" $2
    
    elif [[ $1 == "rotate_ccw" ]]; then

        run_x_wait_y "ROTATE WRIST CCW" "STOP WRIST" $2
    
    elif [[ $1 == "rotate_cw" ]]; then

        run_x_wait_y "ROTATE WRIST CW" "STOP WRIST" $2
    
    elif [[ $1 == "open_claw" ]]; then

        run_x_wait_y "OPEN NIPPER" "STOP NIPPER" $2
    
    elif [[ $1 == "close_claw" ]]; then

        run_x_wait_y "CLOSE NIPPER" "STOP NIPPER" $2
        
   fi
}

# prompt
################################################################################

source ~/.bashrc
export PS1="\033[01;32meva\033[0m> "
echo "(© PoliTOcean 2023) Eva command-line interface"
echo "Type \"help\" to get a list of commands"
