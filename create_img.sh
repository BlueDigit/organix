#!/bin/bash
set -x
#trap read debug

# Create the actual disk image - 20MB
dd if=/dev/zero of=organix.img count=20 bs=1048576

# Make the partition table, partition and set it bootable.
parted --script organix.img mklabel msdos mkpart p ext2 1 20 set 1 boot on

# Map the partitions from the image file
kpartx -a organix.img

# sleep a sec, wait for kpartx to create the device nodes
sleep 1

# Make an ext2 filesystem on the first partition.
mkfs.ext2 /dev/mapper/loop0p1

# Make the mount-point
mkdir -p /mnt/organix
mkdir -p /mnt/organix/boot

# Mount the filesystem via loopback
mount /dev/mapper/loop0p1 /mnt/organix

# Create a device map for grub
echo "(hd0) /dev/loop0" > /mnt/organix/device.map

# Use grub2-install to actually install Grub. The options are:
#   * No floppy polling.
#   * Use the device map we generated in the previous step.
#   * Include the basic set of modules we need in the Grub image.
#   * Install grub into the filesystem at our loopback mountpoint.
#   * Install the MBR to the loopback device itself.
grub-install  --no-floppy                                                      \
              --grub-mkdevicemap=/mnt/organix/device.map                      \
              --modules="biosdisk part_msdos ext2 configfile normal multiboot"\
              --root-directory=/mnt/organix                                   \
              --boot-directory=/mnt/organix/boot                              \
              /dev/loop0

# Copy the grub config file
cp -r grub/* /mnt/organix/boot/grub

# Copy the kernel to boot on
cp -r src/kernel /mnt/organix/boot

# Unmount the loopback
umount /mnt/organix

# Unmap the image
kpartx -d organix.img
