// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials

#include "monitor.h"
#include "descriptor_tables.h"

struct multiboot;

int main(struct multiboot *mboot_ptr)
{
  // All our initialisation calls will go in here.
  init_video();
  init_descriptor_tables();
  monitor_write("Hello, world!\n");
  unsigned int test = 32;
  monitor_write_dec(test);
  monitor_write("\n");
  asm volatile ("int $0x3");
  asm volatile ("int $0x4");
}
