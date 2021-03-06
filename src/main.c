// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials

#include "multiboot.h"
#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"
#include "kheap.h"
#include "initrd.h"
#include "fs.h"

extern u32int placement_address;
extern fs_node_t *fs_root;

int main(struct multiboot *mboot_ptr)
{
    // All our initialisation calls will go in here.
    init_video();
    monitor_write("Hello! Welcome to Organix!\n\n");

    // Start all descriptor tables (GDT, IRQ, etc.)
    monitor_write("Initialising descriptor tables     : ");
    init_descriptor_tables();
    monitor_write("Done!\n");

/**
    // Find the location of our initial ramdisk.
    // ASSERT(mboot_ptr->mods_count > 0);
    monitor_write("Seeking location of initial ramdisk: ");
    u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
    u32int initrd_end = *((u32int*)(mboot_ptr->mods_addr + 4));
    monitor_write("Done!\n");
    // Don't trample our module with placement accesses, please!
    placement_address = initrd_end;
**/
    // Start paging.
    monitor_write("Initialising paging                : ");
    initialise_paging();
    monitor_write("Done!\n");

/**
    // Initialise the initial ramdisk, and set it as the filesystem root.
    monitor_write("Initialising init ramdisk          : ");
    fs_root = initialise_initrd(initrd_location);
    monitor_write("Done!\n");

    int i = 0;
    struct dirent *node = 0;
    while ( (node = readdir_fs(fs_root, i)) != 0)
    {
        monitor_write("Found file ");
        monitor_write(node->name);
        fs_node_t *fsnode = finddir_fs(fs_root, node->name);

        if ((fsnode->flags&0x7) == FS_DIRECTORY)
            monitor_write("\n\t(directory)\n");
        else
        {
            monitor_write("\n\t contents: \"");
            char buf[256];
            u32int sz = read_fs(fsnode, 0, 256, buf);
            int j;
            for (j = 0; j < sz; j++)
                monitor_put(buf[j]);

            monitor_write("\"\n");
        }
        i++;
    }
**/

}
