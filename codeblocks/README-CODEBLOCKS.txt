Building under Code::Blocks is only currently supported when using MingW/GCC
as the compiler, if you successfully build photon with any other compiler it
would be greatly appreciated if you'd contact me (cozman@users.sf.net).

Note on Code::Blocks without OpenAL

If you are attempting to compile via Code::Blocks without OpenAL you must open 
both photon.cbp and AudioTest.cbp and within the Compiler tab of the 
Project->Build Options dialog, select the #defines sub-tab and erase the line 
PHOTON_USE_OPENAL.
