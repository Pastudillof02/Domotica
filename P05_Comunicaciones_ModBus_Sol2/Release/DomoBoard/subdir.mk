################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\DomoBoard\ModbusDomoboard.cpp \
..\DomoBoard\domoBoard.cpp 

LINK_OBJ += \
.\DomoBoard\ModbusDomoboard.cpp.o \
.\DomoBoard\domoBoard.cpp.o 

CPP_DEPS += \
.\DomoBoard\ModbusDomoboard.cpp.d \
.\DomoBoard\domoBoard.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
DomoBoard\ModbusDomoboard.cpp.o: ..\DomoBoard\ModbusDomoboard.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	recipe.cpp.o.pattern
	@echo 'Finished building: $<'
	@echo ' '

DomoBoard\domoBoard.cpp.o: ..\DomoBoard\domoBoard.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	recipe.cpp.o.pattern
	@echo 'Finished building: $<'
	@echo ' '


