#ifndef PIC_H  // If PIC_H is NOT defined
#define PIC_H   // Define PIC_H

void PIC_remap(int offset1, int offset2);
void PIC_send_EOI(uint8_t IRQline);
void PIC_mask_IRQ(uint8_t IRQline);
void PIC_unmask_IRQ(uint8_t IRQline);

#endif