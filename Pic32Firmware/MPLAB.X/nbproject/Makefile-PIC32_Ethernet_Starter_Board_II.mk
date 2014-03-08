#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-PIC32_Ethernet_Starter_Board_II.mk)" "nbproject/Makefile-local-PIC32_Ethernet_Starter_Board_II.mk"
include nbproject/Makefile-local-PIC32_Ethernet_Starter_Board_II.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32_Ethernet_Starter_Board_II
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../main.c ../usb_config.c ../USB/usb_host.c "../USB/Android Host Driver/usb_host_android.c" ../led.c ../button.c ../command.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/usb_config.o ${OBJECTDIR}/_ext/1360907413/usb_host.o ${OBJECTDIR}/_ext/1341520085/usb_host_android.o ${OBJECTDIR}/_ext/1472/led.o ${OBJECTDIR}/_ext/1472/button.o ${OBJECTDIR}/_ext/1472/command.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/usb_config.o.d ${OBJECTDIR}/_ext/1360907413/usb_host.o.d ${OBJECTDIR}/_ext/1341520085/usb_host_android.o.d ${OBJECTDIR}/_ext/1472/led.o.d ${OBJECTDIR}/_ext/1472/button.o.d ${OBJECTDIR}/_ext/1472/command.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/usb_config.o ${OBJECTDIR}/_ext/1360907413/usb_host.o ${OBJECTDIR}/_ext/1341520085/usb_host_android.o ${OBJECTDIR}/_ext/1472/led.o ${OBJECTDIR}/_ext/1472/button.o ${OBJECTDIR}/_ext/1472/command.o

# Source Files
SOURCEFILES=../main.c ../usb_config.c ../USB/usb_host.c ../USB/Android Host Driver/usb_host_android.c ../led.c ../button.c ../command.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-PIC32_Ethernet_Starter_Board_II.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c   
	
${OBJECTDIR}/_ext/1472/usb_config.o: ../usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/usb_config.o.d" -o ${OBJECTDIR}/_ext/1472/usb_config.o ../usb_config.c   
	
${OBJECTDIR}/_ext/1360907413/usb_host.o: ../USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_host.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_host.o ../USB/usb_host.c   
	
${OBJECTDIR}/_ext/1341520085/usb_host_android.o: ../USB/Android\ Host\ Driver/usb_host_android.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1341520085 
	@${RM} ${OBJECTDIR}/_ext/1341520085/usb_host_android.o.d 
	@${RM} ${OBJECTDIR}/_ext/1341520085/usb_host_android.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1341520085/usb_host_android.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1341520085/usb_host_android.o.d" -o ${OBJECTDIR}/_ext/1341520085/usb_host_android.o "../USB/Android Host Driver/usb_host_android.c"   
	
${OBJECTDIR}/_ext/1472/led.o: ../led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/led.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/led.o.d" -o ${OBJECTDIR}/_ext/1472/led.o ../led.c   
	
${OBJECTDIR}/_ext/1472/button.o: ../button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/button.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/button.o.d" -o ${OBJECTDIR}/_ext/1472/button.o ../button.c   
	
${OBJECTDIR}/_ext/1472/command.o: ../command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/command.o.d" -o ${OBJECTDIR}/_ext/1472/command.o ../command.c   
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c   
	
${OBJECTDIR}/_ext/1472/usb_config.o: ../usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/usb_config.o.d" -o ${OBJECTDIR}/_ext/1472/usb_config.o ../usb_config.c   
	
${OBJECTDIR}/_ext/1360907413/usb_host.o: ../USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_host.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_host.o ../USB/usb_host.c   
	
${OBJECTDIR}/_ext/1341520085/usb_host_android.o: ../USB/Android\ Host\ Driver/usb_host_android.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1341520085 
	@${RM} ${OBJECTDIR}/_ext/1341520085/usb_host_android.o.d 
	@${RM} ${OBJECTDIR}/_ext/1341520085/usb_host_android.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1341520085/usb_host_android.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1341520085/usb_host_android.o.d" -o ${OBJECTDIR}/_ext/1341520085/usb_host_android.o "../USB/Android Host Driver/usb_host_android.c"   
	
${OBJECTDIR}/_ext/1472/led.o: ../led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/led.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/led.o.d" -o ${OBJECTDIR}/_ext/1472/led.o ../led.c   
	
${OBJECTDIR}/_ext/1472/button.o: ../button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/button.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/button.o.d" -o ${OBJECTDIR}/_ext/1472/button.o ../button.c   
	
${OBJECTDIR}/_ext/1472/command.o: ../command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32_ETHERNET_STARTER_KIT -I".." -I"../Include" -MMD -MF "${OBJECTDIR}/_ext/1472/command.o.d" -o ${OBJECTDIR}/_ext/1472/command.o ../command.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}              -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=3000
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=3000
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32_Ethernet_Starter_Board_II
	${RM} -r dist/PIC32_Ethernet_Starter_Board_II

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
