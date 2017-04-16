// common.h -- Defines typedefs and some global functions.
// From JamesM's kernel development tutorials

#ifndef COMMON_H
#define COMMON_H

// Some nice typedefs, to standardize sizes accross platforms
// Written for 32-bit x86

// unsigned
typedef unsigned int            u32int;
typedef unsigned short          u16int;
typedef unsigned char           u8int;

// signed
typedef          int            s32int;
typedef          short          s16int;
typedef          char           s8int;

// I/O bus functions --> ASM calls
void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

#endif
