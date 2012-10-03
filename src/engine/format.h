/****************************************************************************
 format.h
 Function protoypes for formatting routines
 ****************************************************************************/

#ifndef FORMAT_H_

#define FORMAT_H_
extern void implicit (char *, long, unsigned char *, char *);
extern void immed    (char *, long, unsigned char *, char *);
extern void relative (char *, long, unsigned char *, char *);
extern void ind_zp   (char *, long, unsigned char *, char *);
extern void ind_zpx  (char *, long, unsigned char *, char *);
extern void ind_zpy  (char *, long, unsigned char *, char *);
extern void ind_zpind(char *, long, unsigned char *, char *);
extern void ind_zpix (char *, long, unsigned char *, char *);
extern void ind_zpiy (char *, long, unsigned char *, char *);
extern void absol    (char *, long, unsigned char *, char *);
extern void absx     (char *, long, unsigned char *, char *);
extern void absy     (char *, long, unsigned char *, char *);
extern void absind   (char *, long, unsigned char *, char *);
extern void absindx  (char *, long, unsigned char *, char *);
extern void pseudorel(char *, long, unsigned char *, char *);
extern void tst_zp   (char *, long, unsigned char *, char *);
extern void tst_abs  (char *, long, unsigned char *, char *);
extern void tst_zpx  (char *, long, unsigned char *, char *);
extern void tst_absx (char *, long, unsigned char *, char *);
extern void xfer     (char *, long, unsigned char *, char *);

#endif
