# FreeEMS - TRUE DIY Engine Management

### Introduction

FreeEMS - The open source engine management system!

Please see [FreeEMS.org](http://freeems.org) for the most up to date information and links!

Before using FreeEMS read the [disclaimer](http://www.diyefi.org/disclaimer.htm)!

If you're wondering why this project was started have a look at [this page](http://www.diyefi.org/why.htm).

### Unit Testing

I don't clam to be an expert but I thought that I would post how I unit test embedded code.

I use GCC or MinGW (on windows) to run the tests.  I find this very useful, as debugging is easier and faster on a PC.  There is no need to flash the micro and some silicon vendors don't supply very good debug tools, if any.

I use unity, which can be found here http://throwtheswitch.org/white-papers/unity-intro.html

I take the unit C file that I want to test and include it in my test C file.  I use the “exclude from build” feature of eclipse to make sure the it doesn't get compiled twice.  I then write mock functions and variables that allow the unit to compile without errors.

Then write your tests and use the assert macros to check you get the results you want.  

I don't know how to use cmock.c yet and I am not sure if you need to have a separate executable for each unit or there is a way to test all units in one executable.   

I have put an example on https://github.com/Spudmn/Missing_teeth_Unit_Test

I hope you find this useful.