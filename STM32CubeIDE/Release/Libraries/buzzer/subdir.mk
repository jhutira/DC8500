################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/buzzer/buzzer.c 

C_DEPS += \
./Libraries/buzzer/buzzer.d 

OBJS += \
./Libraries/buzzer/buzzer.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/buzzer/%.o Libraries/buzzer/%.su Libraries/buzzer/%.cyclo: ../Libraries/buzzer/%.c Libraries/buzzer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/display" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/mx25lm51245g" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/buzzer" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/modbus" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/rs485" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/eeprom" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Source" -I../../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-buzzer

clean-Libraries-2f-buzzer:
	-$(RM) ./Libraries/buzzer/buzzer.cyclo ./Libraries/buzzer/buzzer.d ./Libraries/buzzer/buzzer.o ./Libraries/buzzer/buzzer.su

.PHONY: clean-Libraries-2f-buzzer

