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

#ifndef MOCK_VARS_H_
#define MOCK_VARS_H_

/// Use this block to manage the execution count of various functions loops and ISRs etc. TODO break this up into smaller chunks
typedef struct {
        // Scheduling
        unsigned char normalSchedule;                  ///< times events were scheduled normally.
        unsigned char timerStretchedToSchedule;        ///< times timer needed to be extended to prevent not scheduling.

        // Decoder scheduling
        unsigned char pinScheduledToGoHigh;            ///< Behaviour chosen from decoder based on register and pin state.
        unsigned char pinScheduledAlready;             ///< @copydoc pinScheduledToGoHigh
        unsigned char pinScheduledToSelfSchedule;      ///< @copydoc pinScheduledToGoHigh
        unsigned char pinScheduledAgainToStayOn;       ///< @copydoc pinScheduledToGoHigh

        unsigned char pinScheduledToToggleError;       ///< @copydoc pinScheduledToGoHigh
        unsigned char pinScheduledToDoNothing;         ///< @copydoc pinScheduledToGoHigh
        unsigned char pinScheduledFromCold;            ///< @copydoc pinScheduledToGoHigh
        unsigned char pinScheduledWithTimerExtension;  ///< @copydoc pinScheduledToGoHigh

        // Outputs, refactor to not say "injector" later.
        unsigned char injectorSwitchOns;               ///< number of times the injector switched on
        unsigned char injectorSwitchOffs;              ///< number of times the injector switched off to stay off
        unsigned char injectorTimerExtensions;         ///< number of times the injector ISR fired and rescheduled itself to fire and do nothing again
        unsigned char injectorTimerExtensionFinals;    ///< number of times the injector ISR fired and scheduled the injector to switch on

        unsigned char injectorSelfSchedules;           ///< number of times the injector switched off and scheduled itself again
        unsigned char injectorSelfScheduleExtensions;  ///< number of times the injector switched off and scheduled itself again with timer extension

        unsigned char syncedADCreadings;              ///< Incremented each time a synchronous ADC reading is taken
        unsigned char timeoutADCreadings;             ///< Incremented for each ADC reading in RTC because of timeout
        unsigned char calculationsPerformed;          ///< Incremented for each time the fuel and ign calcs are done

        unsigned char sparePadding;                    ///< Replace with something useful
} Counter;



/* For extracting 32 bit long time stamps from the overflow counter and timer registers */
typedef union { /* Declare Union http://www.esacademy.com/faq/docs/cpointers/structures.htm */
    unsigned short timeShorts[2];
    unsigned long timeLong;

} LongTime;


#endif /* MOCK_VARS_H_ */
