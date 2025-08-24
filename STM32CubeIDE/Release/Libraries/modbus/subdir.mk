################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/modbus/modbus.c \
../Libraries/modbus/modbus_server_rtu.c \
../Libraries/modbus/modbus_server_tcp.c 

C_DEPS += \
./Libraries/modbus/modbus.d \
./Libraries/modbus/modbus_server_rtu.d \
./Libraries/modbus/modbus_server_tcp.d 

OBJS += \
./Libraries/modbus/modbus.o \
./Libraries/modbus/modbus_server_rtu.o \
./Libraries/modbus/modbus_server_tcp.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/modbus/%.o Libraries/modbus/%.su Libraries/modbus/%.cyclo: ../Libraries/modbus/%.c Libraries/modbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/display" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/mx25lm51245g" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/buzzer" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/modbus" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/rs485" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/eeprom" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Source" -I../../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-modbus

clean-Libraries-2f-modbus:
	-$(RM) ./Libraries/modbus/modbus.cyclo ./Libraries/modbus/modbus.d ./Libraries/modbus/modbus.o ./Libraries/modbus/modbus.su ./Libraries/modbus/modbus_server_rtu.cyclo ./Libraries/modbus/modbus_server_rtu.d ./Libraries/modbus/modbus_server_rtu.o ./Libraries/modbus/modbus_server_rtu.su ./Libraries/modbus/modbus_server_tcp.cyclo ./Libraries/modbus/modbus_server_tcp.d ./Libraries/modbus/modbus_server_tcp.o ./Libraries/modbus/modbus_server_tcp.su

.PHONY: clean-Libraries-2f-modbus

