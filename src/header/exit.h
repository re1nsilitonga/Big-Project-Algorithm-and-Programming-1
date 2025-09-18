#ifndef EXIT_H
#define EXIT_H

#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "user.h"
#include "boolean.h"
#include "denah.h"
#include "save.h"
#include "dataperut.h"

void Exit(const char *sourceFolder, dataAkun akunData, Denah denah, DataPerutPasien DPP);
/* I.S. : sourceFolder adalah path folder sumber, akunData, denah, dan DPP terdefinisi
   F.S. : melakukan exit dan memberikan pilihan kepada pengguna untuk save atau tidak */

#endif