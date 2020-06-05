#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <kernel/paging.h>

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