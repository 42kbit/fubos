#ifndef __H_VGA_H
#define __H_VGA_H

#include <fubos/ints.h>

#define VGA_WIDTH	80
#define VGA_HEIGHT	25

#define VGA_BUFFER_LEN	(VGA_WIDTH * VGA_HEIGHT)

struct vga_node {
	u8 c;
	u8 color;
};

#endif /* __H_VGA_H */
