# Memory Map

## Overview
The STM32F446RE has 512 KB of flash, split into 8 sectors. This project
divides it into a bootloader area and an application area.

## Layout
| Region      | Start address | End address | Size   | Sectors |
|-------------|---------------|-------------|--------|---------|
| Bootloader  | 0x0800_0000   | 0x0800_FFFF | 64 KB  | 0-3     |
| Application | 0x0801_0000   | 0x0807_FFFF | 448 KB | 4-7     |

## Why this layout
Vendor bootloaders are small (Silicon Labs recommends reserving 16-24 KB on
some of its devices), so 64 KB leaves ample room to grow. The application
starts at 0x0801_0000, the first address of sector 4. Flash can only be erased
one whole sector at a time, so starting the application on a sector boundary
means updating it never erases part of the bootloader.

## Sources
- STM32F446 reference manual, RM0390, Table 4 (flash module organization)
- [Silicon Labs: memory space for bootloading](https://docs.silabs.com/connect-stack/latest/bootloader-fundamentals/03-memory-space-for-bootloading)