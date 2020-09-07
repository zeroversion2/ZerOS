#include <kernel/system.h>
#include <stdio.h>

extern void isr0();

void setup_isrs() {
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    //isr0();
    //asm("intw 0");
}

unsigned char *exception_messages[] = {
    "Division by Zero",
    "Debug",
    "Non Maskable Interrupt"
};

void fault_handler(struct regs *r) {
    if (r->int_no < 32) {
        printf(exception_messages[r->int_no]);
        printf(" Exception. System Halted!\n");
        for (;;);
    }
}