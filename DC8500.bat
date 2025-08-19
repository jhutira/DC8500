arm-none-eabi-objcopy -O ihex --only-section=ExtFlashSection DC8500.elf  "DC8500_extFlash.hex"
arm-none-eabi-objcopy -O ihex --remove-section=ExtFlashSection DC8500.elf DC8500_internal.hex

