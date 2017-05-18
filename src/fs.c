//
// fs.c
// File system managerment procedures.
// Based on JamesM's kernel tutorial.
//

#include "fs.h"

fs_node_t *fs_root = 0; // The root of the filesystem.
