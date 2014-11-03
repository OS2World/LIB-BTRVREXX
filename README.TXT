I place this code in the public domain, and make absolutely no 
representations about its reliability or suitability.  That being said, 
it would appear from initial testing that BTRVREXX.DLL does indeed 
function correctly as a REXX external function providing an interface to
Btrieve 5.10a for OS/2 (BTRCALLS.DLL) under OS/2 2.1.

The file TEST.CMD demonstrates the use of the DLL with a simple call. 
Note that BTRVREXX is a "dumb" interface to BTRCALLS.  All parameters 
used by BTRCALLS must be allocated by the REXX caller and are passed 
through as-is in both directions by BTRVREXX.  The caller is completely 
responsible for deciphering the character-string results into meaningful
information.

The function entry point BTRV requires six parameters, all of which 
represent parameters to BTRCALL itself.  The first and sixth parameters 
(operation code and key number, respectively) are expected to be numeric
constants, and the remaining four parameters are expected to be 
character-string names of REXX variables that the REXX caller has 
preallocated with the proper length and contents.  These four variables 
are the position block (which will need to be a global variable for 
proper Btrieve operation), data buffer, data buffer length, and key 
buffer (which should be allocated as 255 bytes, the maximum Btrieve key 
length).  The data buffer can by up to 32000 bytes in length.

Compiled with CSet++

If you have any comments about this interface, please contact me on 
CompuServe at 70304,1316.  In particular, I would of course appreciate 
receiving any corrected or improved versions!

        Gary Kopp
        8-21-93
