#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

#define MULTIBOOT_KERNEL_MAGIC      0x2BADB002
#define MULTIBOOT_HEADER_MAGIC      0x1BADB002
#define MULTIBOOT_MMAP_FREE_MEMORY  1
#define MULTIBOOT_MMAP_RESERVED     2
#define MULTIBOOT_MMAP_ACPI         3
#define MULTIBOOT_MMAP_HIBERNATION  4
#define MULTIBOOT_MMAP_BAD_CELL     5
#define MAX_MODULES                 10 // Temporary, maybe move module loading after heap init and store there if I need a more robust modules impl

struct multiboot_header {
  uint32_t flags;
   uint32_t mem_lower;
   uint32_t mem_upper;
   uint32_t boot_device;
   uint32_t cmdline;
   uint32_t mods_count;
   uint32_t mods_addr;
   uint32_t num;
   uint32_t size;
   uint32_t addr;
   uint32_t shndx;
   uint32_t mmap_length;
   uint32_t mmap_addr;
   uint32_t drives_length;
   uint32_t drives_addr;
   uint32_t config_table;
   uint32_t boot_loader_name;
   uint32_t apm_table;
   uint32_t vbe_control_info;
   uint32_t vbe_mode_info;
   uint32_t vbe_mode;
   uint32_t vbe_interface_seg;
   uint32_t vbe_interface_off;
   uint32_t vbe_interface_len;
} __attribute__ ((packed));

typedef struct {
   uint16_t attributes;
   uint8_t  winA, winB;
   uint16_t granularity;
   uint16_t winsize;
   uint16_t segmentA, segmentB;
   uint32_t realFctPtr;
   uint16_t pitch;

   uint16_t Xres, Yres;
   uint8_t  Wchar, Ychar, planes, bpp, banks;
   uint8_t  memory_model, bank_size, image_pages;
   uint8_t  reserved0;

   uint8_t  red_mask, red_position;
   uint8_t  green_mask, green_position;
   uint8_t  blue_mask, blue_position;
   uint8_t  rsv_mask, rsv_position;
   uint8_t  directcolor_attributes;

   uint32_t physbase;
   uint32_t reserved1;
   uint16_t reserved2;
} __attribute__ ((packed)) vbe_info_t;

typedef struct {
   unsigned long mod_start;
   unsigned long mod_end;
   unsigned long string;
   unsigned long reserved;
} module_t;

typedef struct {
   uint32_t size;
   uint32_t base_addr_low;
   uint32_t base_addr_high;
   //uint32_t length_low;
   //uint32_t length_high;
   uint64_t length;
   uint32_t type;
} __attribute__ ((packed)) mboot_memmap_t;

typedef struct {
   mboot_memmap_t* entries;
   uint32_t length;
   uint32_t total_memory;
} mmap_data_t;

char* MULTIBOOT_MMAP_TYPES[6];
module_t mods[MAX_MODULES];
struct multiboot_header* mbt;

void multiboot_init(struct multiboot_header *mbt);
void load_mmap();
void load_modules();
void print_mmap();
void print_modules();
module_t* get_module(char* string);

#endif