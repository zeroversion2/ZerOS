global idt_load
extern idtr
idt_load:
    lidt [idtr]
    ret