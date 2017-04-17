// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials

#include "monitor.h"

struct multiboot;

int main(struct multiboot *mboot_ptr)
{
  // All our initialisation calls will go in here.
  init_video();
  monitor_write("Hello, world!");
}
