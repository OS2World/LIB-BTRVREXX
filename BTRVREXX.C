#define _DLL
#define _MT
#define INCL_REXXSAA
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <rexxsaa.h>

RexxFunctionHandler BTRV;

extern USHORT _Far16 _Pascal BTRCALL(USHORT, PSZ, PSZ,
                     PUSHORT, PSZ, BYTE, CHAR);

ULONG BTRV(
     CHAR      *Name,           /* Name of the function         */
     ULONG     Argc,            /* Number of arguments          */
     RXSTRING  Argv[],          /* List of argument strings     */
     CHAR      *Queuename,      /* Current queue name           */
     RXSTRING  *Retstr)         /* Returned result string       */

/*
   ARGV[0] = operation (digits)
   ARGV[1] = name of posblock variable (-> 128 byte static area)
   ARGV[2] = name of databuf variable
   ARGV[3] = name of datalen variable (-> digits)
   ARGV[4] = name of keybuf variable
   ARGV[5] = keynum (digits)
*/

{

  USHORT operation;
  CHAR posblock[128];
  CHAR databuf[32000];
  USHORT datalen;
  CHAR keybuf[255];
  CHAR keynum;
  CHAR datalen_string[6];

  BYTE keylen = 255;
  USHORT rcs;
  ULONG rc;

  SHVBLOCK pos_var;
  SHVBLOCK data_var;
  SHVBLOCK len_var;
  SHVBLOCK key_var;

  if (Argc != 6)
        return 40;

  pos_var.shvnext = &data_var;
  pos_var.shvcode = RXSHV_SYFET;
  pos_var.shvret = (UCHAR)0;
  MAKERXSTRING(pos_var.shvname, Argv[1].strptr, Argv[1].strlength);
  MAKERXSTRING(pos_var.shvvalue, posblock, 128);
  pos_var.shvvaluelen = 128;
  data_var.shvnext = &len_var;
  data_var.shvcode = RXSHV_SYFET;
  data_var.shvret = (UCHAR)0;
  MAKERXSTRING(data_var.shvname, Argv[2].strptr, Argv[2].strlength);
  MAKERXSTRING(data_var.shvvalue, databuf, 32000);
  data_var.shvvaluelen = 32000;
  len_var.shvnext = &key_var;
  len_var.shvcode = RXSHV_SYFET;
  len_var.shvret = (UCHAR)0;
  MAKERXSTRING(len_var.shvname, Argv[3].strptr, Argv[3].strlength);
  MAKERXSTRING(len_var.shvvalue, datalen_string, 5);
  len_var.shvvaluelen = 5;
  key_var.shvnext = (PSHVBLOCK)0;
  key_var.shvcode = RXSHV_SYFET;
  key_var.shvret = (UCHAR)0;
  MAKERXSTRING(key_var.shvname, Argv[4].strptr, Argv[4].strlength);
  MAKERXSTRING(key_var.shvvalue, keybuf, 255);
  key_var.shvvaluelen = 255;
  rc = RexxVariablePool(&pos_var);
  if (rc != 0)
        return 40;

  operation = atoi(Argv[0].strptr);
  keynum = atoi(Argv[5].strptr);
  datalen = atoi(datalen_string);

  rcs = BTRCALL(operation, posblock, databuf, &datalen, keybuf,
                   keylen, keynum);

  sprintf(Retstr->strptr, "%d", rcs);
  Retstr->strlength = strlen(Retstr->strptr);
  pos_var.shvcode = RXSHV_SYSET;
  pos_var.shvret = (UCHAR)0;
  MAKERXSTRING(pos_var.shvvalue, posblock, 128);
  pos_var.shvvaluelen = 128;
  data_var.shvcode = RXSHV_SYSET;
  data_var.shvret = (UCHAR)0;
  MAKERXSTRING(data_var.shvvalue, databuf, datalen);
  data_var.shvvaluelen = datalen;
  len_var.shvcode = RXSHV_SYSET;
  len_var.shvret = (UCHAR)0;
  sprintf(datalen_string, "%d", datalen);
  MAKERXSTRING(len_var.shvvalue, datalen_string, strlen(datalen_string));
  len_var.shvvaluelen = strlen(datalen_string);
  key_var.shvcode = RXSHV_SYSET;
  key_var.shvret = (UCHAR)0;
  MAKERXSTRING(key_var.shvvalue, keybuf, key_var.shvvaluelen);
  rc = RexxVariablePool(&pos_var);
  if (rc != 0)
        return 40;
  return 0;
}
