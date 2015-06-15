#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/EasyDSSBuffers.o \
	${OBJECTDIR}/g7712aac.o \
	${OBJECTDIR}/libfaac/aacquant.o \
	${OBJECTDIR}/libfaac/backpred.o \
	${OBJECTDIR}/libfaac/bitstream.o \
	${OBJECTDIR}/libfaac/channels.o \
	${OBJECTDIR}/libfaac/fft.o \
	${OBJECTDIR}/libfaac/filtbank.o \
	${OBJECTDIR}/libfaac/frame.o \
	${OBJECTDIR}/libfaac/huffman.o \
	${OBJECTDIR}/libfaac/kiss_fft/kiss_fft.o \
	${OBJECTDIR}/libfaac/kiss_fft/kiss_fftr.o \
	${OBJECTDIR}/libfaac/ltp.o \
	${OBJECTDIR}/libfaac/midside.o \
	${OBJECTDIR}/libfaac/psychkni.o \
	${OBJECTDIR}/libfaac/tns.o \
	${OBJECTDIR}/libfaac/util.o \
	${OBJECTDIR}/libg7112aac.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L${AVS_ROOT}/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${AVS_ROOT}/lib/libg7112aac.${CND_DLIB_EXT}

${AVS_ROOT}/lib/libg7112aac.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${AVS_ROOT}/lib
	${LINK.cc} -o ${AVS_ROOT}/lib/libg7112aac.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -lboost_thread -lpthread -lrt -lboost_system -shared -fPIC

${OBJECTDIR}/EasyDSSBuffers.o: EasyDSSBuffers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I${AVS_ROOT}/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EasyDSSBuffers.o EasyDSSBuffers.cpp

${OBJECTDIR}/g7712aac.o: g7712aac.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I${AVS_ROOT}/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/g7712aac.o g7712aac.cpp

${OBJECTDIR}/libfaac/aacquant.o: libfaac/aacquant.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/aacquant.o libfaac/aacquant.c

${OBJECTDIR}/libfaac/backpred.o: libfaac/backpred.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/backpred.o libfaac/backpred.c

${OBJECTDIR}/libfaac/bitstream.o: libfaac/bitstream.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/bitstream.o libfaac/bitstream.c

${OBJECTDIR}/libfaac/channels.o: libfaac/channels.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/channels.o libfaac/channels.c

${OBJECTDIR}/libfaac/fft.o: libfaac/fft.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/fft.o libfaac/fft.c

${OBJECTDIR}/libfaac/filtbank.o: libfaac/filtbank.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/filtbank.o libfaac/filtbank.c

${OBJECTDIR}/libfaac/frame.o: libfaac/frame.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/frame.o libfaac/frame.c

${OBJECTDIR}/libfaac/huffman.o: libfaac/huffman.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/huffman.o libfaac/huffman.c

${OBJECTDIR}/libfaac/kiss_fft/kiss_fft.o: libfaac/kiss_fft/kiss_fft.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac/kiss_fft
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/kiss_fft/kiss_fft.o libfaac/kiss_fft/kiss_fft.c

${OBJECTDIR}/libfaac/kiss_fft/kiss_fftr.o: libfaac/kiss_fft/kiss_fftr.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac/kiss_fft
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/kiss_fft/kiss_fftr.o libfaac/kiss_fft/kiss_fftr.c

${OBJECTDIR}/libfaac/ltp.o: libfaac/ltp.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/ltp.o libfaac/ltp.c

${OBJECTDIR}/libfaac/midside.o: libfaac/midside.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/midside.o libfaac/midside.c

${OBJECTDIR}/libfaac/psychkni.o: libfaac/psychkni.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/psychkni.o libfaac/psychkni.c

${OBJECTDIR}/libfaac/tns.o: libfaac/tns.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/tns.o libfaac/tns.c

${OBJECTDIR}/libfaac/util.o: libfaac/util.c 
	${MKDIR} -p ${OBJECTDIR}/libfaac
	${RM} "$@.d"
	$(COMPILE.c) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libfaac/util.o libfaac/util.c

${OBJECTDIR}/libg7112aac.o: libg7112aac.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -I${AVS_ROOT}/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libg7112aac.o libg7112aac.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${AVS_ROOT}/lib/libg7112aac.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
