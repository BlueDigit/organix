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


Setup:

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


External resources:

  http://www.osdever.net/bkerndev/index.php
  https://01.org/linuxgraphics/gfx-docs/drm/index.html
  https://01.org/linuxgraphics/gfx-docs/drm/process/coding-style.html
