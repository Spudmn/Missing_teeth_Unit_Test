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


#include "unity//unity_fixture.h"
#include <stdio.h>
#include <memory.h>
#include "Global.h"

#include "..//inc//FixedConfigs.h"
#include "../inc/syncLossIDs.h"

#include "Mock_Vars.h"

fixedConfig2 fixedConfigs2;
unsigned char coreStatusA;

Counter Counters;

//TODO make this volatile?
/* ECT IC extension variable (init not required, don't care where it is, only differences between figures) */
unsigned short timerExtensionClock; /* Increment for each overflow of the main timer, allows finer resolution and longer time period */
/* section 10.3.5 page 290 68hc11 reference manual e.g. groups.csail.mit.edu/drl/courses/cs54-2001s/pdf/M68HC11RM.pdf */


// RPM - need some sort of state to say not to use these first time through...
 unsigned short ticksPerDegree0; // to be replaced with logging scheme for teeth.
 unsigned short ticksPerDegree1; // to be replaced with logging scheme for teeth.
 unsigned short* ticksPerDegree; // final output variable, probably move into inputVars struct?
 unsigned short* ticksPerDegreeRecord; // intermediate storage variable, do something with this?

KeyUserDebug KeyUserDebugs;    ///< Formalised key logging vars in one place

//Mock Vars for decoderInterface.h


 unsigned long lastEventTimeStamp;
 unsigned long lastPrimaryEventTimeStamp;
 unsigned long lastSecondaryEventTimeStamp;
 unsigned short lastTicksPerDegree;
 unsigned short lastPrimaryTicksPerDegree;
 unsigned short lastSecondaryTicksPerDegree;
 unsigned long skipEventFlags;
 unsigned char numberScheduled; /// @todo TODO remove DEBUG

 extern const unsigned char numberOfRealEvents ;


//Mock Vars and functions that are not tested

Clock Clocks;

typedef unsigned char ADCBuffer;
ADCBuffer *ADCBuffers;

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
///Mock functions

#define SET_SYNC_LEVEL_TO(SYNC_LEVEL) Mock_Set_Sync_Level(SYNC_LEVEL)

void Mock_Set_Sync_Level(unsigned char SYNC_LEVEL)
{
  UnityPrint("Set Sync to  ");

  if (SYNC_LEVEL == CRANK_SYNC)        UnityPrint("CRANK_SYNC");

  UNITY_OUTPUT_CHAR('\n');

  KeyUserDebugs.decoderFlags |= SYNC_LEVEL;                         \
  KeyUserDebugs.syncCaughtOnThisEvent = KeyUserDebugs.currentEvent;

}


void sampleEachADC(ADCBuffer *Arrays)
{

}

void perDecoderReset();

void resetToNonRunningState(unsigned char uniqueLossID)
{


        UnityPrint("resetToNonRunningState ");
        UnityPrintNumber(uniqueLossID);

        if (uniqueLossID == 105)        UnityPrint("VRWiringBackwardNarrowWideMatchedPairPlusMask");
        if (uniqueLossID == 123)        UnityPrint("ExtraToothWideNarrowNarrowWidePlusMask");
        if (uniqueLossID == 76)         UnityPrint("VRWiringBackwardMatchedPairWideNarrowPlusMask");

        UNITY_OUTPUT_CHAR('\n');


        perDecoderReset();

}



#include "../src/MissingTeeth-Crank-8minus1.c"

const unsigned char numberOfRealEvents = NUMBER_OF_REAL_EVENTS;  // This needs to be here because NUMBER_OF_REAL_EVENTS
                                                                 //  is declared in MissingTeeth.h






//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////  Helper Functions



void Show_Number(unsigned char Num)
{

	UnityPrint("Tooth ");
	UnityPrintNumber(Num);
	UnityPrint(" ");

	UNITY_OUTPUT_CHAR('\n');

}

void Show_Peroid(void)
{

	UnityPrintNumber(lastInterEventPeriod);
	UNITY_OUTPUT_CHAR(' ');
	if ((KeyUserDebugs.decoderFlags & CRANK_SYNC)) UnityPrint(" Crank Sync ");
	UnityPrint(" KeyUserDebugs.currentEvent ");
	UnityPrintNumber(	KeyUserDebugs.currentEvent);

	UNITY_OUTPUT_CHAR('\n');
	UNITY_OUTPUT_CHAR('\n');

}

void Do_One_Rev(void)
{

	Show_Number(1);
	TC0 += 100;
	PrimaryRPMISR(); //T1
	Show_Peroid();

	Show_Number(2);
	TC0 += 100;
	PrimaryRPMISR(); //T2
	Show_Peroid();

	Show_Number(3);
	TC0 += 100;
	PrimaryRPMISR(); //T3
	Show_Peroid();

	Show_Number(4);
	TC0 += 100;
	PrimaryRPMISR(); //T4
	Show_Peroid();

	Show_Number(5);
	TC0 += 100;
	PrimaryRPMISR(); //T5
	Show_Peroid();

	Show_Number(6);
	TC0 += 100;
	PrimaryRPMISR(); //T6
	Show_Peroid();

	Show_Number(7);
	TC0 += 100;
	PrimaryRPMISR(); //T7
	Show_Peroid();


	 // Show_Number(8);
	  TC0 += 100;
	  //PrimaryRPMISR(); //T8 missing
	  //Show_Peroid();

}


void Load_TC0(unsigned long BigNumber)
{

  TC0 = BigNumber & 0xFFFF;
  timerExtensionClock = BigNumber >> 16;
}


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// MissingTeeth Test Group

TEST_GROUP(MissingTeeth);

TEST_SETUP(MissingTeeth)  // This is run before the test begins
{
        ticksPerDegree = &ticksPerDegree0; // TODO temp, remove, maybe
        ticksPerDegreeRecord = &ticksPerDegree1; // TODO temp, remove, maybe

        fixedConfigs2.decoderSettings.accelerationInputEventTimeTolerance= ((100/(100 + 50.00)) * 1000);
        fixedConfigs2.decoderSettings.decelerationInputEventTimeTolerance= (((100 + 50.00)/100) * 1000);

        KeyUserDebugs.decoderFlags = 0;
}


TEST_TEAR_DOWN(MissingTeeth)  // This is run after the test has ended
{

}


TEST(MissingTeeth, ISR)  // This is the Test
{

  decoderInitPreliminary();
  TEST_ASSERT_EQUAL(TCTL4,0x02);
  TC0 = 100;
  Do_One_Rev();
  Do_One_Rev();
  Do_One_Rev();

}



TEST(MissingTeeth, Flat_Battery)  // This is the Test of real world number of a Mini cranked with a flat Battery
{
  decoderInitPreliminary();
  TEST_ASSERT_EQUAL(TCTL4,0x02);


  Load_TC0( 169773);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0(226150);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 267791);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 311035);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 370295);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 419945);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 458385);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 556724);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 605093);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 641290);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 678448);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 726175);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 769740);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 805616);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 891783);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 935988);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 970583);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1005819);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1050984);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1092626);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1128183);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1216591);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1262500);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1297500);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1333750);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1381250);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1425000);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1461250);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1547500);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1592500);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1627500);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1663750);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1710000);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1752500);
  PrimaryRPMISR();
  Show_Peroid();

  Load_TC0( 1788750);
  PrimaryRPMISR();
  Show_Peroid();

  }


