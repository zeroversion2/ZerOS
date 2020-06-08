#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <kernel/paging.h>

extern void* boot_page_directory;

uint32_t page_directory[1024]__attribute__((aligned(4096)));
uint32_t page_table[1024]__attribute__((aligned(4096)));

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

void setup_paging() {
    size_t size = 0x10000;
    for (size_t i = 0; i < size / 4096; i++)
    {
        page_table[i] = page_table_entry((void*) (i * 4096), false, false, SV, true, true);
        //printf("%d\n", page_table);
    }
    page_directory[0] = page_directory_entry(page_table, K, false, false, SV, true, true);

    asm volatile("  movl %0, %%ecx;\
                    movl %%ecx, %%cr3;"
                    : 
                    : "a" (page_directory)
                    : "ecx");

    printf("%d", &boot_page_directory);

    // asm volatile("  movl %cr0, %ecx;\
    //                 or $0x80010000, %ecx;\
    //                 mov %ecx, %cr0");
}