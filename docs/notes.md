# Notes

## 2026-11-17: repo setup
- Moved CubeIDE workspace out of repo (.metadata was getting committed).
- Bootloader project at repo root, demo app in app/.

## 2026-11-20: memory map and demo app
- Bootloader flash 64 KB (0x08000000), app starts at 0x08010000 (sector 4).
- Empty bootloader scaffold: 5.3 KB flash.
- App's .project was empty, so Build was grayed out; fixed by copying the
  bootloader's .project and renaming it.
- App's VECT_TAB_OFFSET = 0x10000, linker FLASH origin 0x8010000.