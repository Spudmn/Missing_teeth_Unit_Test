/*      FreeEMS - Unit Test Example

        Copyright 2012 Aaron Keith

        This file is part of the FreeEMS project.

        FreeEMS software is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        FreeEMS software is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/


 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define SBIT(name, addr, bit)  volatile unsigned char  name
#define SFR(name)        volatile unsigned char  name
#define SFR16(name)      volatile unsigned short name


#ifdef FREEEMS_C
#define EXTERN
#else
#define EXTERN extern
#endif


#define ATOMIC_END()
#define ATOMIC_START()

// TODO these flags are used for coreSettingsA and it is not clear that they are dual purpose, fix this...
/* State variables : 0 = false (don't forget to change the init mask to suit!) */
EXTERN unsigned char coreStatusA;	/* Each bit represents the state of some core parameter, masks below */
/* Bit masks for coreStatusA */ // TODO needs a rename as does coresetingsA
#define FUEL_PUMP_PRIME BIT0 /* 0 */
#define STAGED_REQUIRED BIT1 /* 1 Fire the staged injectors */
#define CALC_FUEL_IGN   BIT2 /* 2 Fuel and ignition require calculation (i.e. variables have been updated) */
#define FORCE_READING   BIT3 /* 3 Flag to force ADC sampling at low rpm/stall */
#define BENCH_TEST_ON   BIT4 /* 4 Bench test running TEMPORARY */
#define COREA05         BIT5 /* 5 */
#define COREA06         BIT6 /* 6 */
//#define COREA07         BIT7 /* 7 Currently used for dual stop byte hack... */

#define CLEAR_FUEL_PUMP_PRIME NBIT0 /* */
#define STAGED_NOT_REQUIRED   NBIT1 /*  9 Do not fire the staged injectors */
#define CLEAR_CALC_FUEL_IGN   NBIT2 /* 10 Fuel and ignition don't require calculation */
#define CLEAR_FORCE_READING   NBIT3 /* 11 Clear flag to force ADC sampling at low rpm/stall */
#define CLEAR_BENCH_TEST_ON   NBIT4

SFR(TCTL4); /* (B,A) 33,22,11,00 */
SFR(TFLG);
SFR(PORTB);
SFR16(TC0);
SFR(PTIT);
SFR(TFLGOF);

/* Individual bits WARNING, do not not these for notted versions, use the notted ones below instead : http://supp.iar.com/Support/?note=12582&from=search+result */
#define BIT0        0x01      /*  1st bit =     1 */
#define BIT1        0x02      /*  2nd bit =     2 */
#define BIT2        0x04      /*  3rd bit =     4 */
#define BIT3        0x08      /*  4th bit =     8 */
#define BIT4        0x10      /*  5th bit =    16 */
#define BIT5        0x20      /*  6th bit =    32 */
#define BIT6        0x40      /*  7th bit =    64 */
#define BIT7        0x80      /*  8th bit =   128 */

#define BIT0_16     0x0001    /*  1st bit =     1 */
#define BIT1_16     0x0002    /*  2nd bit =     2 */
#define BIT2_16     0x0004    /*  3rd bit =     4 */
#define BIT3_16     0x0008    /*  4th bit =     8 */
#define BIT4_16     0x0010    /*  5th bit =    16 */
#define BIT5_16     0x0020    /*  6th bit =    32 */
#define BIT6_16     0x0040    /*  7th bit =    64 */
#define BIT7_16     0x0080    /*  8th bit =   128 */

#define BIT8_16     0x0100    /*  9th bit =   256 */
#define BIT9_16     0x0200    /* 10th bit =   512 */
#define BIT10_16    0x0400    /* 11th bit =  1024 */
#define BIT11_16    0x0800    /* 12th bit =  2048 */
#define BIT12_16    0x1000    /* 13th bit =  4096 */
#define BIT13_16    0x2000    /* 14th bit =  8192 */
#define BIT14_16    0x4000    /* 15th bit = 16384 */
#define BIT15_16    0x8000    /* 16th bit = 32768 */

/* Individual bits NOTTED : http://supp.iar.com/Support/?note=12582&from=search+result */
#define NBIT0       0xFE      /*  1st bit =     1 */
#define NBIT1       0xFD      /*  2nd bit =     2 */
#define NBIT2       0xFB      /*  3rd bit =     4 */
#define NBIT3       0xF7      /*  4th bit =     8 */
#define NBIT4       0xEF      /*  5th bit =    16 */
#define NBIT5       0xDF      /*  6th bit =    32 */
#define NBIT6       0xBF      /*  7th bit =    64 */
#define NBIT7       0x7F      /*  8th bit =   128 */

#define NBIT0_16    0xFFFE    /*  1st bit =     1 */
#define NBIT1_16    0xFFFD    /*  2nd bit =     2 */
#define NBIT2_16    0xFFFB    /*  3rd bit =     4 */
#define NBIT3_16    0xFFF7    /*  4th bit =     8 */
#define NBIT4_16    0xFFEF    /*  5th bit =    16 */
#define NBIT5_16    0xFFDF    /*  6th bit =    32 */
#define NBIT6_16    0xFFBF    /*  7th bit =    64 */
#define NBIT7_16    0xFF7F    /*  8th bit =   128 */

#define NBIT8_16    0xFEFF    /*  9th bit =   256 */
#define NBIT9_16    0xFDFF    /* 10th bit =   512 */
#define NBIT10_16   0xFBFF    /* 11th bit =  1024 */
#define NBIT11_16   0xF7FF    /* 12th bit =  2048 */
#define NBIT12_16   0xEFFF    /* 13th bit =  4096 */
#define NBIT13_16   0xDFFF    /* 14th bit =  8192 */
#define NBIT14_16   0xBFFF    /* 15th bit = 16384 */
#define NBIT15_16   0x7FFF    /* 16th bit = 32768 */


/* Common macro definitions across the project */
/* Booleans from http://c2.com/cgi/wiki?CeePreprocessorStatements */
#define FALSE (0!=0) // Note, this evaluates to 0 on this platform
#define TRUE  !FALSE // Note, this evaluates to 1 on this platform


/* 8 bit values */
#define ZEROS 0x00
#define ONES  0xFF

/* 16 bit values */
#define ZEROS16 0x0000
#define ONES16  0xFFFF

/* Halves and Maxes */
#define LONGHALF  0x80000000UL /* 2147483648 */ // Ned IS awesome! ;-)
#define LONGMAX   0xFFFFFFFFUL /* 4294967295 */
#define SHORTHALF 0x8000       /* 32768 */
#define SHORTMAX  0xFFFF       /* 65535 */

// Default to off
#ifndef DECODER_BENCHMARKS
#define DECODER_BENCHMARKS FALSE
#else
#undef DECODER_BENCMARKS
#define DECODER_BENCHMARKS TRUE
#endif





/** This macro turns a pin ON based on an enable flag, a port address and a pin
 * mask for that port. It is used to keep the code clean and free from ifdefs
 * whilst allowing a developer to turn on benchmarking outputs very easily. Note
 * that it gets optimised out due to the constant literal conditional required.
 */
#define DEBUG_TURN_PIN_ON(BENCHMARK_ENABLED, PIN_ON_MASK, PORT_ADDRESS)   \
if(BENCHMARK_ENABLED){                                                    \
        PORT_ADDRESS |= PIN_ON_MASK;                                          \
}                                                                         // End macro



/** This macro turns a pin OFF based on an enable flag, a port address and a pin
 * mask for that port. It is used to keep the code clean and free from ifdefs
 * whilst allowing a developer to turn on benchmarking outputs very easily. Note
 * that it gets optimised out due to the constant literal conditional required.
 */
#define DEBUG_TURN_PIN_OFF(BENCHMARK_ENABLED, PIN_OFF_MASK, PORT_ADDRESS) \
if(BENCHMARK_ENABLED){                                                    \
        PORT_ADDRESS &= PIN_OFF_MASK;                                         \
}                                                                         // End macro



#define FLAG_AND_INC_FLAGGABLE(x)
#define OUTPUT_COARSE_BBS()
#define SCHEDULE_ECT_OUTPUTS(x)



/// Important "always send" stuff for datalogging
typedef struct {
        // To be improved MAJORLY:
        unsigned char tempClock;      ///< Incremented once per log sent, to be moved to a char
        unsigned char spareChar;      ///< Unused at this time.

        // All flags! Pair keeps things sane for hacky apps that think everything is 16 bit.
        unsigned char coreStatusA;     ///< Duplicated, migrate here, remove global var
        unsigned char decoderFlags;    ///< Various decoder state flags
        unsigned short flaggableFlags; ///< Flags to go with our flaggables struct.
        // counter flags once counter mechanism implemented

        // These things should only exist once in memory, and should be grouped in a struct, perhaps this one
        unsigned char currentEvent;          ///< Which input event was last to come in
        unsigned char syncLostWithThisID;    ///< A unique identifier for the reason behind a loss of sync
        unsigned char syncLostOnThisEvent;   ///< Where in the input pattern it all went very badly wrong
        unsigned char syncCaughtOnThisEvent; ///< Where in the input pattern that things started making sense
        unsigned char syncResetCalls;        ///< Sum of sync losses and state clears
        unsigned char primaryTeethSeen;      ///< Free running counters for number of input events, useful at lower RPM
        unsigned char secondaryTeethSeen;    ///< @copydoc primaryTeethSeen

        // Likewise these too
        unsigned char serialOverrunErrors;         ///< Incremented when an overrun occurs due to high interrupt load, not a fault, just a fact of life at high RPM
        unsigned char serialHardwareErrors;     ///< Sum of noise, parity, and framing errors
        unsigned char serialAndCommsCodeErrors; ///< Sum of checksum, escape mismatches, starts inside, and over/under length
        unsigned short inputEventTimeTolerance;    ///< Required to tune noise rejection over RPM TODO add to LT1 and MissingTeeth

        // replace highest first to avoid hassles for offset based dave/mtx...
        unsigned short zsp10; ///< Spare US variable
        unsigned short zsp9;  ///< Spare US variable

        unsigned short zsp8;  ///< Spare US variable
        unsigned short zsp7;  ///< Spare US variable
        unsigned short zsp6;  ///< Spare US variable
        unsigned short zsp5;  ///< Spare US variable
        unsigned short zsp4;  ///< Spare US variable
        unsigned short zsp3;  ///< Spare US variable
        // Do we want these recorded at log assembly time, or at recording of ADC time, or at calculation of vars (core and/or deriv) or at enabling of scheduling, or all of the above?
        unsigned short clockInMilliSeconds; ///< Migrate to start of all large datalogs once analysed
        unsigned short clockIn8thsOfAMilli; ///< Migrate to start of all large datalogs once analysed
} KeyUserDebug;

EXTERN KeyUserDebug KeyUserDebugs;    ///< Formalised key logging vars in one place

/// Use this block to manage the various clocks kept.
typedef struct {
        /* Real Time and other Clocks (all require init to zero) */
        unsigned short realTimeClockMain;      ///< Variable to count RTI executions, 0.125ms exactly
        unsigned short realTimeClockMillis;    ///< Variable to count milliseconds exactly
        unsigned short realTimeClockTenths;    ///< Variable to count tenths of a second exactly
        unsigned short realTimeClockSeconds;   ///< Variable to count seconds exactly
        unsigned short realTimeClockMinutes;   ///< Variable to count minutes exactly

        unsigned short millisToTenths;         ///< Roll-over variable for counting tenths
        unsigned short tenthsToSeconds;        ///< Roll-over variable for counting seconds
        unsigned short secondsToMinutes;       ///< Roll-over variable for counting minutes

        unsigned short timeoutADCreadingClock; ///< Timeout clock/counter for synced ADC readings
} Clock;


//Mocks for Decoder Interface

#define oneDegree 50U // Scaler for all scheduler and decoder angles, not tables etc. Suffix is necessary otherwise 8 bit is assumed. TODO Mount Messenger road to New Plymouth! Recommended Kim@bach with NAZZZ and Steve!
#define ticks_per_degree_multiplier (10 * oneDegree)

// unsigned long thisEventTimeStamp; recommended variable naming, may be enforced for/with macro use
// unsigned long thisInterEventPeriod; ditto
/// @todo TODO sync loss/gain semantics - how paranoid? under what circumstances? should we make it configurable whether a decoder that is in a situation where it would find sync if not synced, resets sync, or loses sync. Likewise, at initial sync gain time, should it go "prelim sync found" and only verify sync on the second lap around, or start firing events straight off the bat. Starting will suck if paranoid, but if there is noise at high load/rpm and events get mis-scheduled before sync is lost, that is serious. This is philosophical, and the reality is that you must assume that your signal is clean to some level and verified clean under lower risk conditions.
EXTERN unsigned long lastEventTimeStamp;
EXTERN unsigned long lastPrimaryEventTimeStamp;
EXTERN unsigned long lastSecondaryEventTimeStamp;
EXTERN unsigned short lastTicksPerDegree;
EXTERN unsigned short lastPrimaryTicksPerDegree;
EXTERN unsigned short lastSecondaryTicksPerDegree;
EXTERN unsigned long skipEventFlags;
EXTERN unsigned char numberScheduled; /// @todo TODO remove DEBUG

/// @todo Introduce the concept of sync level to schedule for if NOT synced
/// @todo and a way of deciding what to do in different sync states
/// @todo and proper dividers for pulsewidths
/// @todo and ability to lock pulsewidht/dwell for scheduling
/// @todo and generalise scheduling to all pins
/// @todo and provide a way of choosing a source of pulsewidth dwell or fuel duration
/// @todo and a way of allowing overly advanced scheduling instead of none, when its fuel
#define COMBUSTION_SYNC      BIT0 ///< Sync sufficient for Dizzy/Batch Injection
#define CRANK_SYNC           BIT1 ///< Sync sufficient for Wasted Spark/Semi-Sequential
#define CAM_SYNC             BIT2 ///< Sync sufficient for COP/CNP/Sequential
#define LAST_TIMESTAMP_VALID BIT3 ///< Set when first decoder ISR runs post a reset
#define LAST_PERIOD_VALID    BIT4 ///< Set when second decoder ISR runs post a reset
#define LAST_MATCH_VALID     BIT5 ///< Missing teeth style decoders set this when a valid match is found
#define LAST_TPD_VALID       BIT6 ///< Set once sync is found and we've stored a Ticks Per Degree value
#define DF_SPARE_7           BIT7
// WARNING: Entire flag var is cleared with loss of sync!


// MissingTeeth uses from 0x40 - 0x8D, below and above are free for all other decoders to use.

// Pair designations, possibly move this elsewhere to support defining the others as errors elsewhere too
#define FellThrough     64 // 0x40 The cracks, ie, no match
#define MatchedPair      4 // ~1:1
#define NarrowWide       6 // ~1:(N+1)
#define WideNarrow       7 // ~(N+1):1
#define NarrowBackward   8 // ~1:(N+2)/2
#define BackwardNarrow   5 // ~(N+2)/2:1
#define NarrowTooWide   65 // 0x41 1:>(N+1)
#define TooWideNarrow   66 // 0x42 >(N+1):1


#endif /* GLOBAL_H_ */
