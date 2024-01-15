################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/30010_io.c \
../Src/ansi.c \
../Src/bullet.c \
../Src/drivers.c \
../Src/enemy.c \
../Src/fixedPoint.c \
../Src/graphics.c \
../Src/linkedList.c \
../Src/main.c \
../Src/menu.c \
../Src/nuke.c \
../Src/powerup.c \
../Src/sound.c \
../Src/spaceship.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f30x.c 

OBJS += \
./Src/30010_io.o \
./Src/ansi.o \
./Src/bullet.o \
./Src/drivers.o \
./Src/enemy.o \
./Src/fixedPoint.o \
./Src/graphics.o \
./Src/linkedList.o \
./Src/main.o \
./Src/menu.o \
./Src/nuke.o \
./Src/powerup.o \
./Src/sound.o \
./Src/spaceship.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f30x.o 

C_DEPS += \
./Src/30010_io.d \
./Src/ansi.d \
./Src/bullet.d \
./Src/drivers.d \
./Src/enemy.d \
./Src/fixedPoint.d \
./Src/graphics.d \
./Src/linkedList.d \
./Src/main.d \
./Src/menu.d \
./Src/nuke.d \
./Src/powerup.d \
./Src/sound.d \
./Src/spaceship.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG -DUSE_STDPERIPH_DRIVER=1 -c -I"/Users/david/Library/CloudStorage/OneDrive-DanmarksTekniskeUniversitet/Skole ting/1 sem/Programmeringsprojejkt/Projekt-GRP13/SPL/inc" -I"/Users/david/Library/CloudStorage/OneDrive-DanmarksTekniskeUniversitet/Skole ting/1 sem/Programmeringsprojejkt/Projekt-GRP13/Inc" -I"/Users/david/Library/CloudStorage/OneDrive-DanmarksTekniskeUniversitet/Skole ting/1 sem/Programmeringsprojejkt/Projekt-GRP13/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/30010_io.d ./Src/30010_io.o ./Src/ansi.d ./Src/ansi.o ./Src/bullet.d ./Src/bullet.o ./Src/drivers.d ./Src/drivers.o ./Src/enemy.d ./Src/enemy.o ./Src/fixedPoint.d ./Src/fixedPoint.o ./Src/graphics.d ./Src/graphics.o ./Src/linkedList.d ./Src/linkedList.o ./Src/main.d ./Src/main.o ./Src/menu.d ./Src/menu.o ./Src/nuke.d ./Src/nuke.o ./Src/powerup.d ./Src/powerup.o ./Src/sound.d ./Src/sound.o ./Src/spaceship.d ./Src/spaceship.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o ./Src/system_stm32f30x.d ./Src/system_stm32f30x.o

.PHONY: clean-Src

