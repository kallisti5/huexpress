#ifndef _DJGPP_INCLUDE_FOLLOWOP_H
#define _DJGPP_INCLUDE_FOLLOWOP_H

// Declaration for functions used to know the following instruction

#include "config.h"
#include "cleantyp.h"
#include "optable.h"

#if defined(KERNEL_DS)

#include "h6280.h"

#else

#include "m6502.h"

#endif

#include "pce.h"

UInt16 follow_straight(UInt16);
// for most op, IP just go on

UInt16 follow_BBRi(UInt16 where);
// for BBRi op

UInt16 follow_BCC(UInt16 where);
// for BCC op

UInt16 follow_BBSi(UInt16 where);
// for BBSi op

UInt16 follow_BCS(UInt16 where);
// for BCS op

UInt16 follow_BEQ(UInt16 where);
// for BEQ op

UInt16 follow_BNE(UInt16 where);
// for BNE op

UInt16 follow_BMI(UInt16 where);
// for BMI op

UInt16 follow_BPL(UInt16 where);
// for BPL op

UInt16 follow_BRA(UInt16 where);
// for BRA op

UInt16 follow_BSR(UInt16 where);
// for BSR op

UInt16 follow_BVS(UInt16 where);
// for BVS op

UInt16 follow_BVC(UInt16 where);
// for BVC op

UInt16 follow_JMPabs(UInt16 where);
// for JMP absolute

UInt16 follow_JMPindir(UInt16 where);
// for JMP indirect

UInt16 follow_JMPindirX(UInt16 where);
// for JMP indirect with X

UInt16 follow_JSR(UInt16 where);
// for JSR op

UInt16 follow_RTI(UInt16 where);
// for RTI op

UInt16 follow_RTS(UInt16 where);
// for RTS op

#endif
