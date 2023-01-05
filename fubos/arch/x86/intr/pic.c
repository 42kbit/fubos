#include <asm/x86.h>
#include <asm/pic.h>
#include <asm/isr.h>

void init_irq(void){
	pic_remap_irq();
}

/* delay in 1-4 micros,
 * on old machines gives pic time to process stuff */
static inline void io_wait(void){
	outb(0x80, 0);
}

void pic_remap_irq (void){
	/* save masks */
	u8	mask_pic1 = inb(PIC1_DATA),
		mask_pic2 = inb(PIC2_DATA);

	/* send init command for master???? */
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	/* same magic for slave */
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	/* specify location where to remap master 
	 * IRQ0 = 32 */
	outb(PIC1_DATA, IRQ(0));
	io_wait();

	/* specify location where to remap slave 
	 * IRQ8 = 40 */
	outb(PIC2_DATA, IRQ(8));
	io_wait();

	/* tell master that slave (0b0000 0100),
	 * is on index 3 (IRQ(2)) */
	outb(PIC1_DATA, 4);
	io_wait();

	/* tell slave its cascade (0b0000 0010) */
	outb(PIC2_DATA, 2);
	io_wait();

	/* wtf?? */
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	/* restore masks */
	outb(PIC1_DATA, mask_pic1);
	io_wait();
	outb(PIC2_DATA, mask_pic2);
	io_wait();
}

void pic_send_eoi (u8 irq){
	if (irq >= 8)
		outb(PIC2_COMMAND, PIC_EOI);
	outb(PIC1_COMMAND, PIC_EOI);
}
