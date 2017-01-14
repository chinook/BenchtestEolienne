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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=source/DataAcq.cpp source/Ds1338.cpp source/Interrupts.cpp source/Setup.cpp source/SkadiFunctions.cpp source/SourceTemplate.cpp source/StateFunctions.cpp source/StateMachine.cpp source/main.cpp SDCardUtilities.cpp source/SDMMC.c source/fileio.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/source/DataAcq.o ${OBJECTDIR}/source/Ds1338.o ${OBJECTDIR}/source/Interrupts.o ${OBJECTDIR}/source/Setup.o ${OBJECTDIR}/source/SkadiFunctions.o ${OBJECTDIR}/source/SourceTemplate.o ${OBJECTDIR}/source/StateFunctions.o ${OBJECTDIR}/source/StateMachine.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/SDCardUtilities.o ${OBJECTDIR}/source/SDMMC.o ${OBJECTDIR}/source/fileio.o
POSSIBLE_DEPFILES=${OBJECTDIR}/source/DataAcq.o.d ${OBJECTDIR}/source/Ds1338.o.d ${OBJECTDIR}/source/Interrupts.o.d ${OBJECTDIR}/source/Setup.o.d ${OBJECTDIR}/source/SkadiFunctions.o.d ${OBJECTDIR}/source/SourceTemplate.o.d ${OBJECTDIR}/source/StateFunctions.o.d ${OBJECTDIR}/source/StateMachine.o.d ${OBJECTDIR}/source/main.o.d ${OBJECTDIR}/SDCardUtilities.o.d ${OBJECTDIR}/source/SDMMC.o.d ${OBJECTDIR}/source/fileio.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/source/DataAcq.o ${OBJECTDIR}/source/Ds1338.o ${OBJECTDIR}/source/Interrupts.o ${OBJECTDIR}/source/Setup.o ${OBJECTDIR}/source/SkadiFunctions.o ${OBJECTDIR}/source/SourceTemplate.o ${OBJECTDIR}/source/StateFunctions.o ${OBJECTDIR}/source/StateMachine.o ${OBJECTDIR}/source/main.o ${OBJECTDIR}/SDCardUtilities.o ${OBJECTDIR}/source/SDMMC.o ${OBJECTDIR}/source/fileio.o

# Source Files
SOURCEFILES=source/DataAcq.cpp source/Ds1338.cpp source/Interrupts.cpp source/Setup.cpp source/SkadiFunctions.cpp source/SourceTemplate.cpp source/StateFunctions.cpp source/StateMachine.cpp source/main.cpp SDCardUtilities.cpp source/SDMMC.c source/fileio.c


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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/source/SDMMC.o: source/SDMMC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/SDMMC.o.d 
	@${RM} ${OBJECTDIR}/source/SDMMC.o 
	@${FIXDEPS} "${OBJECTDIR}/source/SDMMC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/SDMMC.o.d" -o ${OBJECTDIR}/source/SDMMC.o source/SDMMC.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/fileio.o: source/fileio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/fileio.o.d 
	@${RM} ${OBJECTDIR}/source/fileio.o 
	@${FIXDEPS} "${OBJECTDIR}/source/fileio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/fileio.o.d" -o ${OBJECTDIR}/source/fileio.o source/fileio.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/source/SDMMC.o: source/SDMMC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/SDMMC.o.d 
	@${RM} ${OBJECTDIR}/source/SDMMC.o 
	@${FIXDEPS} "${OBJECTDIR}/source/SDMMC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/SDMMC.o.d" -o ${OBJECTDIR}/source/SDMMC.o source/SDMMC.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/fileio.o: source/fileio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/fileio.o.d 
	@${RM} ${OBJECTDIR}/source/fileio.o 
	@${FIXDEPS} "${OBJECTDIR}/source/fileio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/fileio.o.d" -o ${OBJECTDIR}/source/fileio.o source/fileio.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source/DataAcq.o: source/DataAcq.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/DataAcq.o.d 
	@${RM} ${OBJECTDIR}/source/DataAcq.o 
	@${FIXDEPS} "${OBJECTDIR}/source/DataAcq.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/DataAcq.o.d" -o ${OBJECTDIR}/source/DataAcq.o source/DataAcq.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/Ds1338.o: source/Ds1338.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Ds1338.o.d 
	@${RM} ${OBJECTDIR}/source/Ds1338.o 
	@${FIXDEPS} "${OBJECTDIR}/source/Ds1338.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/Ds1338.o.d" -o ${OBJECTDIR}/source/Ds1338.o source/Ds1338.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/Interrupts.o: source/Interrupts.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Interrupts.o.d 
	@${RM} ${OBJECTDIR}/source/Interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/source/Interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/Interrupts.o.d" -o ${OBJECTDIR}/source/Interrupts.o source/Interrupts.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/Setup.o: source/Setup.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Setup.o.d 
	@${RM} ${OBJECTDIR}/source/Setup.o 
	@${FIXDEPS} "${OBJECTDIR}/source/Setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/Setup.o.d" -o ${OBJECTDIR}/source/Setup.o source/Setup.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/SkadiFunctions.o: source/SkadiFunctions.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/SkadiFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/SkadiFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/source/SkadiFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/SkadiFunctions.o.d" -o ${OBJECTDIR}/source/SkadiFunctions.o source/SkadiFunctions.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/SourceTemplate.o: source/SourceTemplate.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/SourceTemplate.o.d 
	@${RM} ${OBJECTDIR}/source/SourceTemplate.o 
	@${FIXDEPS} "${OBJECTDIR}/source/SourceTemplate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/SourceTemplate.o.d" -o ${OBJECTDIR}/source/SourceTemplate.o source/SourceTemplate.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/StateFunctions.o: source/StateFunctions.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/source/StateFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/StateFunctions.o.d" -o ${OBJECTDIR}/source/StateFunctions.o source/StateFunctions.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/StateMachine.o: source/StateMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateMachine.o.d 
	@${RM} ${OBJECTDIR}/source/StateMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/source/StateMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/StateMachine.o.d" -o ${OBJECTDIR}/source/StateMachine.o source/StateMachine.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/main.o: source/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/main.o.d" -o ${OBJECTDIR}/source/main.o source/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SDCardUtilities.o: SDCardUtilities.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SDCardUtilities.o.d 
	@${RM} ${OBJECTDIR}/SDCardUtilities.o 
	@${FIXDEPS} "${OBJECTDIR}/SDCardUtilities.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/SDCardUtilities.o.d" -o ${OBJECTDIR}/SDCardUtilities.o SDCardUtilities.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/source/DataAcq.o: source/DataAcq.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/DataAcq.o.d 
	@${RM} ${OBJECTDIR}/source/DataAcq.o 
	@${FIXDEPS} "${OBJECTDIR}/source/DataAcq.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/DataAcq.o.d" -o ${OBJECTDIR}/source/DataAcq.o source/DataAcq.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/Ds1338.o: source/Ds1338.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Ds1338.o.d 
	@${RM} ${OBJECTDIR}/source/Ds1338.o 
	@${FIXDEPS} "${OBJECTDIR}/source/Ds1338.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/Ds1338.o.d" -o ${OBJECTDIR}/source/Ds1338.o source/Ds1338.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/Interrupts.o: source/Interrupts.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Interrupts.o.d 
	@${RM} ${OBJECTDIR}/source/Interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/source/Interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/Interrupts.o.d" -o ${OBJECTDIR}/source/Interrupts.o source/Interrupts.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/Setup.o: source/Setup.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/Setup.o.d 
	@${RM} ${OBJECTDIR}/source/Setup.o 
	@${FIXDEPS} "${OBJECTDIR}/source/Setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/Setup.o.d" -o ${OBJECTDIR}/source/Setup.o source/Setup.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/SkadiFunctions.o: source/SkadiFunctions.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/SkadiFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/SkadiFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/source/SkadiFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/SkadiFunctions.o.d" -o ${OBJECTDIR}/source/SkadiFunctions.o source/SkadiFunctions.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/SourceTemplate.o: source/SourceTemplate.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/SourceTemplate.o.d 
	@${RM} ${OBJECTDIR}/source/SourceTemplate.o 
	@${FIXDEPS} "${OBJECTDIR}/source/SourceTemplate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/SourceTemplate.o.d" -o ${OBJECTDIR}/source/SourceTemplate.o source/SourceTemplate.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/StateFunctions.o: source/StateFunctions.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o.d 
	@${RM} ${OBJECTDIR}/source/StateFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/source/StateFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/StateFunctions.o.d" -o ${OBJECTDIR}/source/StateFunctions.o source/StateFunctions.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/StateMachine.o: source/StateMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/StateMachine.o.d 
	@${RM} ${OBJECTDIR}/source/StateMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/source/StateMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/StateMachine.o.d" -o ${OBJECTDIR}/source/StateMachine.o source/StateMachine.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/source/main.o: source/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/main.o.d 
	@${RM} ${OBJECTDIR}/source/main.o 
	@${FIXDEPS} "${OBJECTDIR}/source/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/source/main.o.d" -o ${OBJECTDIR}/source/main.o source/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/SDCardUtilities.o: SDCardUtilities.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SDCardUtilities.o.d 
	@${RM} ${OBJECTDIR}/SDCardUtilities.o 
	@${FIXDEPS} "${OBJECTDIR}/SDCardUtilities.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/SDCardUtilities.o.d" -o ${OBJECTDIR}/SDCardUtilities.o SDCardUtilities.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../Documents/GitHub/ChinookCrabe/ChinookLib/ChinookLib.X/dist/default/debug/ChinookLib.X.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\Documents\GitHub\ChinookCrabe\ChinookLib\ChinookLib.X\dist\default\debug\ChinookLib.X.a      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)    -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../Documents/GitHub/ChinookCrabe/ChinookLib/ChinookLib.X/dist/default/production/ChinookLib.X.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\Documents\GitHub\ChinookCrabe\ChinookLib\ChinookLib.X\dist\default\production\ChinookLib.X.a      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/BenchtestTelemetry.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:
	cd /D ../../Documents/GitHub/ChinookCrabe/ChinookLib/ChinookLib.X && ${MAKE}  -f Makefile CONF=default


# Subprojects
.clean-subprojects:
	cd /D ../../Documents/GitHub/ChinookCrabe/ChinookLib/ChinookLib.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
