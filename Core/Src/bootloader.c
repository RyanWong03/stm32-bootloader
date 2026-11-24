#include "bootloader.h"

void disable_and_clear_interrupts();
void unitialize_peripherals();
bool jump_to_app();

/**
 * @brief Main bootloader function
 * @retval none
 * 
 */
void bootloader_main() {
  bool jump_status = jump_to_app();
  //TODO: Maybe print an error that app failed to jump, or illuminate red LED if possible (LED2 is only green I think).
}

/**
  * @brief  Reads the app's SP and reset handler value from its vector table, performs a basic check on both values,
  * disables interrupts and uninitializes peripherals, and jumps to the app.
  * @retval true for success; false for failure
  */
bool jump_to_app() {
  uint32_t app_sp = *(volatile uint32_t *)APP_START_ADDR;
  uint32_t app_rst_isr = *(volatile uint32_t *)(APP_START_ADDR + 4);

  //Quick basic sanity check to ensure the SP and reset handler value are within their correct address space
  if (app_sp < RAM_START_ADDR || app_sp > RAM_END_ADDR || app_rst_isr < APP_START_ADDR || app_rst_isr > FLASH_END_ADDR) {
    return false;
  }

  disable_and_clear_interrupts();
  unitialize_peripherals();

  __set_MSP(app_sp);
  ((void (*)(void))app_rst_isr)();

  return true;
}

/**
 * @brief Disables all interrupts and clears all pending interrupts
 * @retval none
 */
void disable_and_clear_interrupts() {
  __disable_irq();

  //Stop SysTick from raising new interrupts
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
  
  for (int i = 0; i < 8; i++) {
    //Disable NVIC interrupts
    NVIC->ICER[i] = 0xFFFFFFFF;
    //Clear pending NVIC IRQs
    NVIC->ICPR[i] = 0xFFFFFFFF;
  }

  //Clear pending SysTick & PendSV IRQs
  SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk | SCB_ICSR_PENDSVCLR_Msk;

  //Unsure if necessary; Cortex M4 generic user guide suggests this to ensure
  //subsequent instructions are not executed until these finish executing.
  __DSB();
  __ISB();
}

/**
 * @brief Uninitializes all peripherals initialized by bootloader.
 * @retval none
 * 
 */
void unitialize_peripherals() {}