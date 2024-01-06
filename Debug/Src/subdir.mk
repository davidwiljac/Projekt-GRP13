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
../Src/main.c \
../Src/nuke.c \
../Src/powerup.c \
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
./Src/main.o \
./Src/nuke.o \
./Src/powerup.o \
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
./Src/main.d \
./Src/nuke.d \
./Src/powerup.d \
./Src/spaceship.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG -DUSE_STDPERIPH_DRIVER=1 -c -I"C:/Users/Loren/OneDrive - Danmarks Tekniske Universitet/DTU/1. semester/Programmeringsprojekt 30010/Projekt-GRP13/SPL/inc" -I"C:/Users/Loren/OneDrive - Danmarks Tekniske Universitet/DTU/1. semester/Programmeringsprojekt 30010/Projekt-GRP13/Inc" -I"C:/Users/Loren/OneDrive - Danmarks Tekniske Universitet/DTU/1. semester/Programmeringsprojekt 30010/Projekt-GRP13/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/30010_io.d ./Src/30010_io.o ./Src/ansi.d ./Src/ansi.o ./Src/bullet.d ./Src/bullet.o ./Src/drivers.d ./Src/drivers.o ./Src/enemy.d ./Src/enemy.o ./Src/main.d ./Src/main.o ./Src/nuke.d ./Src/nuke.o ./Src/powerup.d ./Src/powerup.o ./Src/spaceship.d ./Src/spaceship.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o ./Src/system_stm32f30x.d ./Src/system_stm32f30x.o

.PHONY: clean-Src

