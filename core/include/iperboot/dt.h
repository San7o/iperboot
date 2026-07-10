// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#ifndef DT_H
#define DT_H

//
// Device Tree
// -----------
//
// The Devicetree Blob (DTB) format is a flat binary encoding of devicetree data
// within a single, linear, pointerless data structure. I contains a small
// header, followed by three variable sized sections:
//
// - the memory reservation block
// - the structure block
// - the strings block
//
// This implementation is based on the device tree specification v0.4.
//
//  https://github.com/devicetree-org/devicetree-specification/releases/tag/v0.4
//

// Header
// ------

struct fdt_header {
  // 0xD00DFEED (bit-endian)
  uint32_t magic;

  // The total size of the devicetree data structure
  uint32_t totalsize;
  
  // Offsets in bytes from the beginning for the header
  uint32_t off_dt_struct;
  uint32_t off_dt_strings;
  uint32_t off_mem_rsvmap;
  
  uint32_t version;
  uint32_t last_comp_version;

  // The physical ID of the system's boot CPU
  uint32_t boot_cpuid_phys;
  
  uint32_t size_dt_strings;
  uint32_t size_dt_struct;
};

// Memory Reservation Block
// ------------------------
//
// The memory reservation block provides the program with a list of areas in
// physical memory which are reserved; that is, which shall not be used for
// general memory allocations. These regions do not overlap each other.
//
// The list terminates with an entry where both address and size are equal to 0.
//

struct fdt_reserve_entry {
  // Physical address of a reserved memory region
  uint64_t address;
  uint64_t size;
};

// Structure Block
// ---------------
//
// THe structure block describes the structure and contents of the devicetree
// itself. It is composed of a sequence of tokens with data.
//

// TODO

#endif // DT_H
