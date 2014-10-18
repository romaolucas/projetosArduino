#Be careful! This script will delete some ttyUSB0X according to your ttyACMX
regex='ttyACM([0-9]+)'
for line in $(ls /dev/)
do
    if [[ $line =~ $regex ]]
    then    
        n="${BASH_REMATCH[1]}"
        (ls /dev/ | grep --quiet ttyUSB$n) && sudo rm /dev/ttyUSB0$n
        sudo ln -s "/dev/"$line /dev/ttyUSB0$n
    fi
done
