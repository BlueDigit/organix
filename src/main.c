// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials

#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"

int main(struct multiboot *mboot_ptr)
{
  // All our initialisation calls will go in here.
  init_video();
  init_descriptor_tables();
  initialise_paging();

  monitor_write("Hello! Welcome to a paging capable kernel!\n");

  u32int *ptr = (u32int*)0xA0000000;
  u32int do_page_fault = *ptr;

  return 0;
}
