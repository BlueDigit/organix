# organix
An introduction to OS development

5th April 2017:

This simple UNIX-clone OS is an approach of OS development based on James Molloy's
tutorial 'aims to take you through programming a simple UNIX-clone OS' that
I have choose to follow in order to understand the basics concepts of POSIX and UNIX.

If you are reading this, you should take a look to this very good web site :

http://www.jamesmolloy.co.uk/tutorial_html/

For now, the project is just a school work and a simple verbatim of James Molloy's
work. But, if you are interested in developing the subject, don't hesitate to
contact me.

This readme could possibly change during the next weeks.


#Setup:

0. Remember that https://www.gnu.org/software/software.html is your friend !
1. Download GRUB (bootloader) : https://www.gnu.org/software/grub/
2. Install NASM : sudo apt-get install nasm
3. Install BOCHS (x86 emulator) : sudo apt-get install bochs
   You should then follow this steps :
   1) Create a disk image for the emulator.
         cd /opt/local/share/bochs
         sudo bximage (prompts will guide you)
         sudo chmod 777 <diskimg-name>

    2) Remove the current 'ata0-master:' statement in /opt/local/share/bochs/bochsrc.txt
       and replace it with the 'ata0-master:' string displayed at the end of the bximage
       process.

    3) Format the disk image using FreeDOS (http://bochs.sourceforge.net/diskimages.html)
       according to the bochs documentation. (http://bochs.sourceforge.net/)

    4) Now start bochs from the command line.

#Launch GRUB 2
0.After make and update_image.sh
1.Launch the OS with qemu:
  '''
  sudo qemu -drive file=organix.img,index=0,media=disk,format=raw
  '''
2.When grub2 is started:
  '''
  set root=(hd0,msdos1)
  chainloader --force (hd0,msdos1)/kernel
  boot
  '''

#External resources:
  http://www.jamesmolloy.co.uk/tutorial_html/
  https://www.gnu.org/software/grub/manual/grub.html
  http://www.osdever.net/bkerndev/index.php
  https://01.org/linuxgraphics/gfx-docs/drm/index.html
  https://01.org/linuxgraphics/gfx-docs/drm/process/coding-style.html
  http://www.eecg.toronto.edu/~amza/www.mindsec.com/files/x86regs.html
  http://www.cs.virginia.edu/~evans/cs216/guides/x86.html
  https://littleosbook.github.io/
  https://github.com/berkus/jamesm-tutorials
  http://bochs.sourceforge.net/doc/docbook/user/bochsrc.html
  http://www.markomedia.com.au/load-kernel-and-boot-your-system-with-grub2/
  http://www.pbm.com/~lindahl/real.programmers.html
  http://stackoverflow.com/questions/12982020/compiling-to-32-bit-using-make
  https://doc.ubuntu-fr.org/qemu
  https://github.com/roscopeco/mink
  https://roscopeco.com/
  https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-828-operating-system-engineering-fall-2012/
