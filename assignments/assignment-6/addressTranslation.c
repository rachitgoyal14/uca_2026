#include <stdio.h>
#include <stdint.h>

void address_translation(uint32_t virtual_address);

void address_translation(uint32_t virtual_address) {
    uint32_t page_number = 0;
    uint32_t offset = 0;

    // right shift by 12 bits => drops the lower 12 bits (offset part)
    // leaves us with only the upper 20 bits => the page number
    page_number = virtual_address >> 12;

    // 0xFFF = 0000 1111 1111 1111 in binary (lower 12 bits set)
    // ANDing with this mask keeps only the lower 12 bits => the offset
    // upper bits get zeroed out since anything & 0 = 0
    offset = virtual_address & 0xFFF;

    printf("[1A] Addr: 0x%08X -> Page: %u (0x%X), Offset: %u (0x%X)\n",
           virtual_address, page_number, page_number, offset, offset);
}

int main() {

    // test inputs from the assignment
    uint32_t test_addrs[] = {0x00000000, 0x00000FFF, 0x00001000, 0x00003A2C};
    int n = sizeof(test_addrs) / sizeof(test_addrs[0]);

    for (int i = 0; i < n; i++)
        address_translation(test_addrs[i]);

    return 0;
}