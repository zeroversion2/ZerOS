#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <kernel/paging.h>
#include <kernel/asm.h>

extern uint32_t page_directory[1024];
extern uint32_t* page_table1;

//uint32_t page_directory[1024]__attribute__((aligned(4096)));
uint32_t page_table2[1024]__attribute__((aligned(4096)));

uint32_t page_offset = 0xC0000000;

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
    uint32_t page_address,
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
    size_t size = 0x400000;
    uint32_t offset = 0xFD000000;
    for (size_t i = 0; i < size / 4096; i++)
    {
        page_table2[i] = page_table_entry(i * 4096 + offset, false, false, SV, true, true);
    }
    // printf("%h\n", page_directory[768]);
    // printf("%h\n", ((uint32_t)page_table2 - 0xC0000000));
    //halt();
    //page_directory[0] = page_directory_entry((void*)page_table_pa, K, false, false, SV, true, true);
    page_directory[1012] = page_directory_entry((void*)((uint32_t)page_table2 - 0xC0000000), K, false, false, SV, true, true);
    page_directory[1023] = 0;    
}