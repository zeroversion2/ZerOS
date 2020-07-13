#include <stdint.h>
#include <string.h>

struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
}__attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtr;

extern void idt_load();

void idt_set_gate(uint8_t num, unsigned long base, uint16_t selector, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;

    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].flags = flags;
}

void setup_idt() {
    idtr.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtr.base = &idt;

    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_load();
}