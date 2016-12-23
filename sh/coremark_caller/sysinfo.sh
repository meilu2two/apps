#!/bin/bash
# lightweight script collect system information

echo "Script to collect system information: $0"

echo "Info@: -------------------- cat /etc/hostname --------------------"
cat /etc/hostname
echo -e

echo "Info@: -------------------- uname -a --------------------"
uname -a
echo -e

echo "Info@: -------------------- ifconfig --------------------"
ifconfig
echo -e

echo "Info@: -------------------- iwconfig --------------------"
iwconfig
echo -e

echo "Info@: -------------------- df -h --------------------"
df -h
echo -e

echo "Info@: -------------------- ls -al /sys/class/tty/tty*/device/driver --------------------"
ls -al /sys/class/tty/tty*/device/driver
echo -e

echo "Info@: -------------------- lsmod --------------------"
lsmod
echo -e

echo "Info@: -------------------- lsusb --------------------"
lsusb
echo -e

echo "Info@: -------------------- lspci --------------------"
lspci
echo -e

echo "Info@: -------------------- lspci -v --------------------"
lspci -v
echo -e

echo "Info@: -------------------- lscpu --------------------"
lscpu
echo -e

echo "Info@: -------------------- cat /proc/cpuinfo --------------------"
cat /proc/cpuinfo
echo -e

echo "Info@: -------------------- lshw -short --------------------"
lshw -short
echo -e

echo "Info@: -------------------- lshw --------------------"
lshw
echo -e

echo "Info@: -------------------- dmesg --------------------"
dmesg
echo -e

exit 0
