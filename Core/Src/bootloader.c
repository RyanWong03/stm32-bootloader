#include "bootloader.h"

void bootloader_main() {
    jump_to_app();
}

/**
  * @brief  Reads the app's SP and reset handler value from its vector table, performs a basic check on both values,
  * disables interrupts and uninitializes peripherals, and jumps to the app.
  * @retval None
  */
void jump_to_app() {

}