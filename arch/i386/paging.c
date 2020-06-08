#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <kernel/paging.h>
#include <kernel/asm.h>

extern uint32_t* page_directory;
extern uint32_t* page_table1;

//uint32_t page_directory[1024]__attribute__((aligned(4096)));
//uint32_t page_table[1024]__attribute__((aligned(4096)));

struct page_directory_entry_s {
    uint16_t page_table_address_upper;
    enum page_size_t page_size : 1;
    bool cache_disabled : 1;
    bool write_through : 1;
    enum page_priviledge_t page_priviledge : 1;
    bool rw : 1;
    bool present : 1;
}__attribute__((packed));

uint32_t page_directory_entry(
    void* page_table_address,
    enum page_size_t page_size,
    bool cache_disabled,
    bool write_through,
    enum page_priviledge_t page_priviledge,
    bool rw,
    bool present
) {
    uint32_t entry = (uint32_t) page_table_address;
    entry |= page_size << 7;
    entry |= cache_disabled << 4;
    entry |= write_through << 3;
    entry |= page_priviledge << 2;
    entry |= rw << 1;
    entry |= present;
    return entry;
}

uint32_t page_table_entry(
    void* page_address,
    bool cache_disabled,
    bool write_through,
    enum page_priviledge_t page_priviledge,
    bool rw,
    bool present
) {
    uint32_t entry = (uint32_t) page_address;
    entry |= cache_disabled << 4;
    entry |= write_through << 3;
    entry |= page_priviledge << 2;
    entry |= rw << 1;
    entry |= present;
    return entry;
}

void set_page_directory(void*);

void setup_paging() {
    uint32_t page_directory_pa = (uint32_t)page_directory - 0xC0000000;
    uint32_t page_table_pa = (uint32_t)page_table1 - 0xC0000000;

    //halt();

    // asm volatile("  movl %cr0, %ecx;\
    //                 andl $0x80000001, %ecx;\
    //                 movl %ecx, %cr0");

    //halt();

    // for(int i = 0; i < 1024; i++)
    // {
    //     page_directory[i] = page_directory_entry(NULL, K, false, false, SV, true, false);
    // }

    // halt();

    size_t size = 0x10000;
    for (size_t i = 0; i < size / 4096; i++)
    {
        page_table1[i] = page_table_entry((void*) (i * 4096), false, false, SV, true, true);
        //printf("%d\n", page_table);
    }
    //halt();
    //page_directory[0] = page_directory_entry((void*)page_table_pa, K, false, false, SV, true, true);
    page_directory[768] = page_directory_entry((void*)page_table_pa, K, false, false, SV, true, true);

    
    //halt();

    //halt();

    // asm volatile("  movl %0, %%ecx;\
    //                 movl %%ecx, %%cr3;"
    //                 : 
    //                 : "r" (page_directory_pa)
    //                 : "ecx");

    halt();

    // set_page_directory((void*)page_directory_pa);

    //asm volatile("mov $64, %ebx");
    //halt();
    //write_eax(69);
    //asm volatile("higherhalf:");
    //write_eax(420);
    //halt();

    // asm volatile("  movl %cr0, %ecx;\
    //                 andl $0x80000000, %ecx;\
    //                 movl %ecx, %cr0");

    // halt();

    //printf("helo\ntest");

    
}