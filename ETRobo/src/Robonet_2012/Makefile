# Target specific macros
TARGET = 2012_blue
NXTOSEK_ROOT = ../..

# nxtway_gs_balancer library desiged for NXTway-GS two wheeled self-balancing robot
USER_INC_PATH= $(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer
USER_LIB = nxtway_gs_balancer

# using NXT standard tires (not Motorcycle tires)
#USER_DEF = NXT_STD_TIRE

# User application source
TARGET_SOURCES := \
	AngularVelocity.c \
	BalanceControl.c \
	balancer_param.c \
	BlindRunning.c \
	Bluetooth.c \
	CommandValue.c \
	CourseBrightness.c \
	JudgeBrightness.c \
	JudgeDirection.c \
	JudgeMarker.c \
	JudgeMethod.c \
	JudgeMileage.c \
	JudgeSeesaw.c \
	JudgeSonar.c \
	JudgeStepCapture.c \
	JudgeTail.c\
	LineTrace.c \
	Log.c \
	MotorCount.c \
	OperationMethod.c \
	PDControlParameter.c \
	Pwm.c \
	RunningMachine.c \
	RunningPositionInfo.c \
	ScreenDetectionRunning.c \
	SeesawPass.c \
	SonarData.c \
	StepCapture.c \
	Strategy.c \
	TailControl.c \
	TailRunning.c \
	Robonet.c 

# OSEK OIL file
TOPPERS_OSEK_OIL_SOURCE := ./nxt.oil

# below part should not be modified
O_PATH ?= build
include $(NXTOSEK_ROOT)/ecrobot/ecrobot.mak
