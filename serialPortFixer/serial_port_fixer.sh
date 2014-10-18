#Be careful! This script will delete some ttyUSB0X according to your ttyACMX
if [ ! -f ./log_serial.txt ]
then
    touch log_serial.txt
fi

printf "\n\n---------------------\n" >> log_serial.txt
date=`date +%Y-%m-%d`
echo "script ran in $date" >> log_serial.txt

regex='ttyACM([0-9]+)'
for line in $(ls /dev/)
do
    if [[ $line =~ $regex ]]
    then    
        n="${BASH_REMATCH[1]}"
        (ls /dev/ | grep --quiet ttyUSB0$n) && sudo rm /dev/ttyUSB0$n && echo "/dev/ttyACM$n removed" >> log_serial.txt
        sudo ln -s "/dev/"$line /dev/ttyUSB0$n && echo "/dev/ttyACM$n ----> /dev/ttyUSB0$n" >> log_serial.txt
    fi
done
