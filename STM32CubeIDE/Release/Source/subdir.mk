################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/air_flap.c \
../Source/analog.c \
../Source/debug.c \
../Source/digital.c \
../Source/energy.c \
../Source/fireplace.c \
../Source/lambda_sen.c \
../Source/main_util.c \
../Source/modbus_bankreg.c \
../Source/pid_reg.c \
../Source/reg.c \
../Source/system.c \
../Source/uart_log.c \
../Source/variant.c 

C_DEPS += \
./Source/air_flap.d \
./Source/analog.d \
./Source/debug.d \
./Source/digital.d \
./Source/energy.d \
./Source/fireplace.d \
./Source/lambda_sen.d \
./Source/main_util.d \
./Source/modbus_bankreg.d \
./Source/pid_reg.d \
./Source/reg.d \
./Source/system.d \
./Source/uart_log.d \
./Source/variant.d 

OBJS += \
./Source/air_flap.o \
./Source/analog.o \
./Source/debug.o \
./Source/digital.o \
./Source/energy.o \
./Source/fireplace.o \
./Source/lambda_sen.o \
./Source/main_util.o \
./Source/modbus_bankreg.o \
./Source/pid_reg.o \
./Source/reg.o \
./Source/system.o \
./Source/uart_log.o \
./Source/variant.o 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o Source/%.su Source/%.cyclo: ../Source/%.c Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/display" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/mx25lm51245g" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/buzzer" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/modbus" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/rs485" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries/eeprom" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Libraries" -I"C:/Development/mcu/prj/DC8500/STM32CubeIDE/Source" -I../../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source

clean-Source:
	-$(RM) ./Source/air_flap.cyclo ./Source/air_flap.d ./Source/air_flap.o ./Source/air_flap.su ./Source/analog.cyclo ./Source/analog.d ./Source/analog.o ./Source/analog.su ./Source/debug.cyclo ./Source/debug.d ./Source/debug.o ./Source/debug.su ./Source/digital.cyclo ./Source/digital.d ./Source/digital.o ./Source/digital.su ./Source/energy.cyclo ./Source/energy.d ./Source/energy.o ./Source/energy.su ./Source/fireplace.cyclo ./Source/fireplace.d ./Source/fireplace.o ./Source/fireplace.su ./Source/lambda_sen.cyclo ./Source/lambda_sen.d ./Source/lambda_sen.o ./Source/lambda_sen.su ./Source/main_util.cyclo ./Source/main_util.d ./Source/main_util.o ./Source/main_util.su ./Source/modbus_bankreg.cyclo ./Source/modbus_bankreg.d ./Source/modbus_bankreg.o ./Source/modbus_bankreg.su ./Source/pid_reg.cyclo ./Source/pid_reg.d ./Source/pid_reg.o ./Source/pid_reg.su ./Source/reg.cyclo ./Source/reg.d ./Source/reg.o ./Source/reg.su ./Source/system.cyclo ./Source/system.d ./Source/system.o ./Source/system.su ./Source/uart_log.cyclo ./Source/uart_log.d ./Source/uart_log.o ./Source/uart_log.su ./Source/variant.cyclo ./Source/variant.d ./Source/variant.o ./Source/variant.su

.PHONY: clean-Source

