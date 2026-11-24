# stm32-bootloader

A custom bootloader for STM32, written in C, that updates firmware over UART and only boots an application it has verified.

> **Status:** Bootloader jumps to the application; next up: image header and CRC check.

## What it will do

On every reset, the bootloader runs first:

1. It checks whether a valid application is stored in flash.
2. If there is one, it jumps to it.
3. If not, it waits for a new application image from a PC over UART, writes it to flash, verifies it, and then boots it.

## Planned features

- [x] Jump from the bootloader to a separate application
- [ ] Image header with a CRC32 check, so a corrupted or incomplete image is never run
- [ ] Firmware update over UART with a simple framed protocol
- [ ] Host tool on the PC to send firmware images
- [ ] Recovery from an interrupted update (the bootloader stays in update mode until a good image arrives)
- [ ] Stretch: firmware update over CAN
- [ ] Stretch: A/B application slots with rollback

## Hardware

- Board: NUCLEO-F446RE (STM32F446RE, 512 KB flash, 128 KB RAM)
- Programming and debugging: on-board ST-LINK
- Host link: UART through the ST-LINK virtual COM port

## Toolchain

- STM32CubeIDE (GCC ARM toolchain)

## Build and flash

*To be added once the first version runs on the board.*

## Documentation

Design notes and documents will be added in `docs/` as features are completed.

## License

MIT