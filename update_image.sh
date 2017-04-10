#!/bin/bash
set -x
trap read debug

dd if=/dev/zero of=/floppy.img bs=1024 count=1440 #create disk img
losetup /dev/loop1 /floppy.img # create and attach a loopback device to the image
mkfs /dev/loop1 # create a file system

modprobe dm_mod
kpartx -va /floppy.img
# normally you now would mount /dev/loop0p1 directly. BUT
# grub specialists didn't manage to work with loop partitions other than /dev/loop[0-9]
#losetup -v -f --show /dev/mapper/control
mount /dev/loop1 /mnt
mkdir -p /mnt/boot/grub

# change into chrooted environment. all remaining work will be done from here. this differs from the howto above.
LANG=C chroot /mnt /bin/bash
set -o vi
mount -t sysfs sysfs /sys
mount -t proc  proc  /proc
# avoid grub asking questions
cat << ! | debconf-set-selections -v
grub2   grub2/linux_cmdline                select
grub2   grub2/linux_cmdline_default        select
grub-pc grub-pc/install_devices_empty      select yes
grub-pc grub-pc/install_devices            select
!
apt-get -y install grub-pc
# don't setup device.map prior to this point. It will be overwritten by grub-pc install
#corrected the /mnt/boot/grub/device.map to /boot/grub/device.map
cat > /boot/grub/device.map << !
(hd0)   /dev/loop0
(hd0,1) /dev/loop1
!
# install here to fill /boot/grub for grub-mkconfig (update-grub)
grub-install /dev/loop0
# generate /boot/grub/grub.cfg
update-grub

#sudo losetup /dev/loop0 floppy.img
#sudo mount /dev/loop0 /mnt
#sudo cp src/kernel /mnt/kernel
#sudo umount /dev/loop0
#sudo losetup -d /dev/loop0
