################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/rs485/rs485.c 

C_DEPS += \
./Libraries/rs485/rs485.d 

OBJS += \
./Libraries/rs485/rs485.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/rs485/%.o Libraries/rs485/%.su Libraries/rs485/%.cyclo: ../Libraries/rs485/%.c Libraries/rs485/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/mx25lm51245g" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/buzzer" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/modbus" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/rs485" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/eeprom" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries" -I"/home/jozefh/Development/mcu/prj/DC8500/STM32CubeIDE/Source" -I../../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-rs485

clean-Libraries-2f-rs485:
	-$(RM) ./Libraries/rs485/rs485.cyclo ./Libraries/rs485/rs485.d ./Libraries/rs485/rs485.o ./Libraries/rs485/rs485.su

.PHONY: clean-Libraries-2f-rs485

