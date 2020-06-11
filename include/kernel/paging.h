#include <stdbool.h>

#ifndef KERNEL_INCLUDE_PAGING
#define KERNEL_INCLUDE_PAGING

enum page_size_t {K,M};
enum page_priviledge_t {SV,U};
uint32_t page_offset;

uint32_t page_directory_entry(
    void* page_table_address,
    enum page_size_t page_size,
    bool cache_disabled,
    bool write_through,
    enum page_priviledge_t page_priviledge,
    bool rw,
    bool present
);

uint32_t page_table_entry(
    uint32_t page_address,
    bool cache_disabled,
    bool write_through,
    enum page_priviledge_t page_priviledge,
    bool rw,
    bool present
);

#endif