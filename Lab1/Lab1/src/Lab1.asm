;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"Tombola.c"
	list	p=12f683
	radix dec
	include "p12f683.inc"
;--------------------------------------------------------
; config word(s)
;--------------------------------------------------------
	__config 0x3fd7
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	__moduint
	extern	__divuint
	extern	__muluschar
	extern	__mulint
	extern	_TRISIO
	extern	_GPIO
	extern	_GPIObits
	extern	__gptrget2
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_random
	global	_print
	global	_delay
	global	_isNumberInArray

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0070
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_Tombola_0	udata
r0x1026	res	1
r0x1027	res	1
r0x1029	res	1
r0x1028	res	1
r0x102B	res	1
r0x102A	res	1
r0x102D	res	1
r0x102C	res	1
r0x102F	res	1
r0x102E	res	1
r0x1031	res	1
r0x1032	res	1
r0x1021	res	1
r0x1020	res	1
r0x1023	res	1
r0x1022	res	1
r0x1025	res	1
r0x1024	res	1
r0x101D	res	1
r0x101C	res	1
r0x101E	res	1
r0x1015	res	1
r0x1014	res	1
r0x1016	res	1
r0x1017	res	1
r0x1018	res	1
r0x1019	res	1
r0x101A	res	1
r0x101B	res	1
r0x1006	res	1
r0x1005	res	1
r0x1004	res	1
r0x1008	res	1
r0x1007	res	1
r0x100A	res	1
r0x1009	res	1
r0x100B	res	1
r0x100C	res	1
r0x100D	res	1
r0x100E	res	1
r0x100F	res	1
r0x1010	res	1
r0x1012	res	1
_main_ganadores_65537_7	res	2
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

IDD_Tombola_0	idata
_random_rand_65536_14
	db	0xe7, 0x03	; 999

;--------------------------------------------------------
; initialized absolute data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_Tombola	code
;***
;  pBlock Stats: dbName = M
;***
;has an exit
;functions called:
;   _random
;   _random
;   _print
;   _delay
;   _print
;   _delay
;   __mulint
;   _print
;   _delay
;   _print
;   _delay
;   _isNumberInArray
;   __muluschar
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;   _random
;   _random
;   _print
;   _delay
;   _print
;   _delay
;   __mulint
;   _print
;   _delay
;   _print
;   _delay
;   _isNumberInArray
;   __muluschar
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;   _print
;   _delay
;19 compiler assigned registers:
;   r0x1026
;   r0x1027
;   STK02
;   STK01
;   STK00
;   r0x1028
;   r0x1029
;   r0x102A
;   r0x102B
;   r0x102C
;   r0x102D
;   r0x102E
;   r0x102F
;   r0x1030
;   r0x1031
;   r0x1032
;   STK05
;   STK04
;   STK03
;; Starting pCode block
S_Tombola__main	code
_main:
; 2 exit points
;	.line	20; "Tombola.c"	TRISIO = 0b00010000; // GP4 como entrada por default
	MOVLW	0x10
	BANKSEL	_TRISIO
	MOVWF	_TRISIO
;	.line	21; "Tombola.c"	GPIO = 0x00; //Todos los pines en bajo
	BANKSEL	_GPIO
	CLRF	_GPIO
;	.line	26; "Tombola.c"	unsigned int bolas = 0;
	BANKSEL	r0x1026
	CLRF	r0x1026
	CLRF	r0x1027
_00115_DS_:
;	.line	34; "Tombola.c"	num_1 = random(0,9);
	MOVLW	0x09
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x00
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_random
	CALL	_random
	PAGESEL	$
	BANKSEL	r0x1028
	MOVWF	r0x1028
	MOVF	STK00,W
	MOVWF	r0x1029
;	.line	35; "Tombola.c"	num_2 = random(0,9);
	MOVLW	0x09
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x00
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_random
	CALL	_random
	PAGESEL	$
	BANKSEL	r0x102A
	MOVWF	r0x102A
	MOVF	STK00,W
	MOVWF	r0x102B
;	.line	38; "Tombola.c"	print(num_1, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVF	r0x1029,W
	MOVWF	STK00
	MOVF	r0x1028,W
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	39; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	40; "Tombola.c"	print(num_2, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x102B
	MOVF	r0x102B,W
	MOVWF	STK00
	MOVF	r0x102A,W
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	41; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	44; "Tombola.c"	if(GP4)  
	BANKSEL	_GPIObits
	BTFSS	_GPIObits,4
	GOTO	_00111_DS_
;	.line	46; "Tombola.c"	while (GP4)
	BANKSEL	r0x1029
	MOVF	r0x1029,W
	MOVWF	STK02
	MOVF	r0x1028,W
	MOVWF	STK01
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	__mulint
	CALL	__mulint
	PAGESEL	$
	BANKSEL	r0x102C
	MOVWF	r0x102C
	MOVF	STK00,W
	MOVWF	r0x102D
	MOVF	r0x102B,W
	ADDWF	r0x102D,F
	MOVF	r0x102A,W
	BTFSC	STATUS,0
	INCFSZ	r0x102A,W
	ADDWF	r0x102C,F
_00107_DS_:
	BANKSEL	_GPIObits
	BTFSS	_GPIObits,4
	GOTO	_00111_DS_
;	.line	48; "Tombola.c"	print(num_1, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x1029
	MOVF	r0x1029,W
	MOVWF	STK00
	MOVF	r0x1028,W
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	49; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	50; "Tombola.c"	print(num_2, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	BANKSEL	r0x102B
	MOVF	r0x102B,W
	MOVWF	STK00
	MOVF	r0x102A,W
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	51; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	56; "Tombola.c"	if (!isNumberInArray(ganadores, bolas+1, ganador))
	MOVLW	high (_main_ganadores_65537_7 + 0)
	BANKSEL	r0x102E
	MOVWF	r0x102E
	MOVLW	(_main_ganadores_65537_7 + 0)
	MOVWF	r0x102F
;;1	CLRF	r0x1030
	MOVLW	0x01
	ADDWF	r0x1026,W
	MOVWF	r0x1031
	CLRF	r0x1032
	RLF	r0x1032,F
	MOVF	r0x1027,W
	ADDWF	r0x1032,F
	MOVF	r0x102D,W
	MOVWF	STK05
	MOVF	r0x102C,W
	MOVWF	STK04
	MOVF	r0x1031,W
	MOVWF	STK03
	MOVF	r0x1032,W
	MOVWF	STK02
	MOVF	r0x102F,W
	MOVWF	STK01
	MOVF	r0x102E,W
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_isNumberInArray
	CALL	_isNumberInArray
	PAGESEL	$
	BANKSEL	r0x102E
	MOVWF	r0x102E
	MOVF	STK00,W
	MOVWF	r0x102F
	IORWF	r0x102E,W
	BTFSS	STATUS,2
	GOTO	_00106_DS_
;	.line	59; "Tombola.c"	ganadores[bolas+1] = ganador;
	MOVF	r0x1026,W
	MOVWF	r0x102F
	MOVWF	r0x102E
	INCF	r0x102E,W
	MOVWF	r0x102F
	MOVLW	0x02
	MOVWF	STK00
	MOVF	r0x102F,W
	PAGESEL	__muluschar
	CALL	__muluschar
	PAGESEL	$
	BANKSEL	r0x102E
	MOVWF	r0x102E
	MOVF	STK00,W
	MOVWF	r0x102F
	ADDLW	(_main_ganadores_65537_7 + 0)
	MOVWF	r0x102F
	MOVF	r0x102E,W
	BTFSC	STATUS,0
	INCFSZ	r0x102E,W
	ADDLW	high (_main_ganadores_65537_7 + 0)
	MOVWF	r0x102E
	MOVF	r0x102F,W
	BANKSEL	FSR
	MOVWF	FSR
	BCF	STATUS,7
	BANKSEL	r0x102E
	BTFSC	r0x102E,0
	BSF	STATUS,7
	MOVF	r0x102D,W
	BANKSEL	INDF
	MOVWF	INDF
	INCF	FSR,F
	BANKSEL	r0x102C
	MOVF	r0x102C,W
	BANKSEL	INDF
	MOVWF	INDF
;	.line	61; "Tombola.c"	bolas = bolas + 1;
	BANKSEL	r0x1031
	MOVF	r0x1031,W
	MOVWF	r0x1026
	MOVF	r0x1032,W
	MOVWF	r0x1027
_00106_DS_:
;	.line	64; "Tombola.c"	bolas = bolas + 1;
	BANKSEL	r0x1026
	INCF	r0x1026,F
	BTFSC	STATUS,2
	INCF	r0x1027,F
	GOTO	_00107_DS_
_00111_DS_:
;	.line	70; "Tombola.c"	if (bolas == 10)
	BANKSEL	r0x1026
	MOVF	r0x1026,W
	XORLW	0x0a
	BTFSS	STATUS,2
	GOTO	_00115_DS_
	MOVF	r0x1027,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00115_DS_
;	.line	73; "Tombola.c"	print(9, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	74; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	75; "Tombola.c"	print(9, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	76; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	78; "Tombola.c"	print(9, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	79; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	80; "Tombola.c"	print(9, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	81; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	83; "Tombola.c"	print(9, 0);
	MOVLW	0x00
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	84; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	85; "Tombola.c"	print(9, 1);
	MOVLW	0x01
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVLW	0x09
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_print
	CALL	_print
	PAGESEL	$
;	.line	86; "Tombola.c"	delay(time);
	MOVLW	0x0a
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	89; "Tombola.c"	bolas = 0;
	BANKSEL	r0x1026
	CLRF	r0x1026
	CLRF	r0x1027
	GOTO	_00115_DS_
;	.line	93; "Tombola.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;functions called:
;   __gptrget2
;   __gptrget2
;22 compiler assigned registers:
;   r0x1004
;   STK00
;   r0x1005
;   STK01
;   r0x1006
;   STK02
;   r0x1007
;   STK03
;   r0x1008
;   STK04
;   r0x1009
;   STK05
;   r0x100A
;   r0x100B
;   r0x100C
;   r0x100D
;   r0x100E
;   r0x100F
;   r0x1010
;   r0x1011
;   r0x1012
;   r0x1013
;; Starting pCode block
S_Tombola__isNumberInArray	code
_isNumberInArray:
; 2 exit points
;	.line	171; "Tombola.c"	int isNumberInArray(unsigned int *array, unsigned int size, unsigned int number)
	BANKSEL	r0x1004
	MOVWF	r0x1004
	MOVF	STK00,W
	MOVWF	r0x1005
	MOVF	STK01,W
	MOVWF	r0x1006
	MOVF	STK02,W
	MOVWF	r0x1007
	MOVF	STK03,W
	MOVWF	r0x1008
	MOVF	STK04,W
	MOVWF	r0x1009
	MOVF	STK05,W
	MOVWF	r0x100A
;	.line	173; "Tombola.c"	for (unsigned int i = 0; i < size; ++i)
	CLRF	r0x100B
	CLRF	r0x100C
	CLRF	r0x100D
	CLRF	r0x100E
_00222_DS_:
	BANKSEL	r0x1007
	MOVF	r0x1007,W
	SUBWF	r0x100C,W
	BTFSS	STATUS,2
	GOTO	_00238_DS_
	MOVF	r0x1008,W
	SUBWF	r0x100B,W
_00238_DS_:
	BTFSC	STATUS,0
	GOTO	_00220_DS_
;;genSkipc:3307: created from rifx:0x7ffef2424db0
;	.line	175; "Tombola.c"	if (array[i] == number)
	BANKSEL	r0x100D
	MOVF	r0x100D,W
	ADDWF	r0x1006,W
	MOVWF	r0x100F
	MOVF	r0x1005,W
	MOVWF	r0x1010
	MOVF	r0x100E,W
	BTFSC	STATUS,0
	INCFSZ	r0x100E,W
	ADDWF	r0x1010,F
;;101	MOVF	r0x1004,W
;;99	MOVWF	r0x1011
	MOVF	r0x100F,W
	MOVWF	STK01
	MOVF	r0x1010,W
	MOVWF	STK00
;;100	MOVF	r0x1011,W
	MOVF	r0x1004,W
	PAGESEL	__gptrget2
	CALL	__gptrget2
	PAGESEL	$
	BANKSEL	r0x1012
	MOVWF	r0x1012
	MOVF	STK00,W
;;1	MOVWF	r0x1013
	XORWF	r0x100A,W
	BTFSS	STATUS,2
	GOTO	_00223_DS_
	MOVF	r0x1009,W
	XORWF	r0x1012,W
	BTFSS	STATUS,2
	GOTO	_00223_DS_
;	.line	178; "Tombola.c"	return 1; // Verdadero
	MOVLW	0x01
	MOVWF	STK00
	MOVLW	0x00
	GOTO	_00224_DS_
_00223_DS_:
;	.line	173; "Tombola.c"	for (unsigned int i = 0; i < size; ++i)
	MOVLW	0x02
	BANKSEL	r0x100D
	ADDWF	r0x100D,F
	BTFSC	STATUS,0
	INCF	r0x100E,F
	INCF	r0x100B,F
	BTFSC	STATUS,2
	INCF	r0x100C,F
	GOTO	_00222_DS_
_00220_DS_:
;	.line	183; "Tombola.c"	return 0; // Falso
	MOVLW	0x00
	MOVWF	STK00
	MOVLW	0x00
_00224_DS_:
;	.line	184; "Tombola.c"	}
	RETURN	
; exit point of _isNumberInArray

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;9 compiler assigned registers:
;   r0x1014
;   STK00
;   r0x1015
;   r0x1016
;   r0x1017
;   r0x1018
;   r0x1019
;   r0x101A
;   r0x101B
;; Starting pCode block
S_Tombola__delay	code
_delay:
; 2 exit points
;	.line	160; "Tombola.c"	void delay(unsigned int time)
	BANKSEL	r0x1014
	MOVWF	r0x1014
	MOVF	STK00,W
	MOVWF	r0x1015
;	.line	165; "Tombola.c"	for(i=0;i<time;i++)
	CLRF	r0x1016
	CLRF	r0x1017
_00192_DS_:
	BANKSEL	r0x1014
	MOVF	r0x1014,W
	SUBWF	r0x1017,W
	BTFSS	STATUS,2
	GOTO	_00213_DS_
	MOVF	r0x1015,W
	SUBWF	r0x1016,W
_00213_DS_:
	BTFSC	STATUS,0
	GOTO	_00194_DS_
;;genSkipc:3307: created from rifx:0x7ffef2424db0
;	.line	166; "Tombola.c"	for(j=0;j<1275;j++);
	MOVLW	0xfb
	BANKSEL	r0x1018
	MOVWF	r0x1018
	MOVLW	0x04
	MOVWF	r0x1019
_00190_DS_:
	MOVLW	0xff
	BANKSEL	r0x1018
	ADDWF	r0x1018,W
	MOVWF	r0x101A
	MOVLW	0xff
	MOVWF	r0x101B
	MOVF	r0x1019,W
	BTFSC	STATUS,0
	INCFSZ	r0x1019,W
	ADDWF	r0x101B,F
	MOVF	r0x101A,W
	MOVWF	r0x1018
	MOVF	r0x101B,W
	MOVWF	r0x1019
	MOVF	r0x101B,W
	IORWF	r0x101A,W
	BTFSS	STATUS,2
	GOTO	_00190_DS_
;	.line	165; "Tombola.c"	for(i=0;i<time;i++)
	INCF	r0x1016,F
	BTFSC	STATUS,2
	INCF	r0x1017,F
	GOTO	_00192_DS_
_00194_DS_:
;	.line	167; "Tombola.c"	}
	RETURN	
; exit point of _delay

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;7 compiler assigned registers:
;   r0x101C
;   STK00
;   r0x101D
;   STK01
;   r0x101E
;   STK02
;   r0x101F
;; Starting pCode block
S_Tombola__print	code
_print:
; 2 exit points
;	.line	110; "Tombola.c"	void print(int value, int display)
	BANKSEL	r0x101C
	MOVWF	r0x101C
	MOVF	STK00,W
	MOVWF	r0x101D
	MOVF	STK01,W
	MOVWF	r0x101E
	MOVF	STK02,W
;;1	MOVWF	r0x101F
;	.line	112; "Tombola.c"	if (display == 0)
	IORWF	r0x101E,W
	BTFSS	STATUS,2
	GOTO	_00179_DS_
;	.line	114; "Tombola.c"	if (value == 0) GPIO = 0b00000000;
	MOVF	r0x101C,W
	IORWF	r0x101D,W
	BTFSS	STATUS,2
	GOTO	_00149_DS_
	BANKSEL	_GPIO
	CLRF	_GPIO
	GOTO	_00181_DS_
_00149_DS_:
;	.line	116; "Tombola.c"	else if (value == 1) GPIO = 0b00000001; 
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00146_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00146_DS_
	MOVLW	0x01
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00146_DS_:
;	.line	118; "Tombola.c"	else if (value == 2) GPIO = 0b00000010; 
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x02
	BTFSS	STATUS,2
	GOTO	_00143_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00143_DS_
	MOVLW	0x02
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00143_DS_:
;	.line	120; "Tombola.c"	else if (value == 3) GPIO = 0b00000011;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x03
	BTFSS	STATUS,2
	GOTO	_00140_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00140_DS_
	MOVLW	0x03
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00140_DS_:
;	.line	122; "Tombola.c"	else if (value == 4) GPIO = 0b00000100;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x04
	BTFSS	STATUS,2
	GOTO	_00137_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00137_DS_
	MOVLW	0x04
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00137_DS_:
;	.line	124; "Tombola.c"	else if (value == 5) GPIO = 0b00000101;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x05
	BTFSS	STATUS,2
	GOTO	_00134_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00134_DS_
	MOVLW	0x05
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00134_DS_:
;	.line	126; "Tombola.c"	else if (value == 6) GPIO = 0b00000110;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x06
	BTFSS	STATUS,2
	GOTO	_00131_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00131_DS_
	MOVLW	0x06
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00131_DS_:
;	.line	128; "Tombola.c"	else if (value == 7) GPIO = 0b00000111;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x07
	BTFSS	STATUS,2
	GOTO	_00128_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00128_DS_
	MOVLW	0x07
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00128_DS_:
;	.line	130; "Tombola.c"	else if (value == 8) GPIO = 0b00010000;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x08
	BTFSS	STATUS,2
	GOTO	_00125_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00125_DS_
	MOVLW	0x10
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00125_DS_:
;	.line	132; "Tombola.c"	else GPIO = 0b00010001;
	MOVLW	0x11
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00179_DS_:
;	.line	137; "Tombola.c"	if (value == 0) GPIO = 0b00100000;
	BANKSEL	r0x101C
	MOVF	r0x101C,W
	IORWF	r0x101D,W
	BTFSS	STATUS,2
	GOTO	_00176_DS_
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00176_DS_:
;	.line	139; "Tombola.c"	else if (value == 1) GPIO = 0b00100001; 
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00173_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00173_DS_
	MOVLW	0x21
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00173_DS_:
;	.line	141; "Tombola.c"	else if (value == 2) GPIO = 0b00100010; 
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x02
	BTFSS	STATUS,2
	GOTO	_00170_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00170_DS_
	MOVLW	0x22
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00170_DS_:
;	.line	143; "Tombola.c"	else if (value == 3) GPIO = 0b00100011;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x03
	BTFSS	STATUS,2
	GOTO	_00167_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00167_DS_
	MOVLW	0x23
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00167_DS_:
;	.line	145; "Tombola.c"	else if (value == 4) GPIO = 0b00100100;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x04
	BTFSS	STATUS,2
	GOTO	_00164_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00164_DS_
	MOVLW	0x24
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00164_DS_:
;	.line	147; "Tombola.c"	else if (value == 5) GPIO = 0b00100101;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x05
	BTFSS	STATUS,2
	GOTO	_00161_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00161_DS_
	MOVLW	0x25
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00161_DS_:
;	.line	149; "Tombola.c"	else if (value == 6) GPIO = 0b00100110;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x06
	BTFSS	STATUS,2
	GOTO	_00158_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00158_DS_
	MOVLW	0x26
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00158_DS_:
;	.line	151; "Tombola.c"	else if (value == 7) GPIO = 0b00100111;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x07
	BTFSS	STATUS,2
	GOTO	_00155_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00155_DS_
	MOVLW	0x27
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00155_DS_:
;	.line	153; "Tombola.c"	else if (value == 8) GPIO = 0b00110000;
	BANKSEL	r0x101D
	MOVF	r0x101D,W
	XORLW	0x08
	BTFSS	STATUS,2
	GOTO	_00152_DS_
	MOVF	r0x101C,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00152_DS_
	MOVLW	0x30
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00181_DS_
_00152_DS_:
;	.line	155; "Tombola.c"	else GPIO = 0b00110001;
	MOVLW	0x31
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00181_DS_:
;	.line	157; "Tombola.c"	}
	RETURN	
; exit point of _print

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;functions called:
;   __mulint
;   __divuint
;   __moduint
;   __moduint
;   __mulint
;   __divuint
;   __moduint
;   __moduint
;9 compiler assigned registers:
;   r0x1020
;   STK00
;   r0x1021
;   STK01
;   r0x1022
;   STK02
;   r0x1023
;   r0x1024
;   r0x1025
;; Starting pCode block
S_Tombola__random	code
_random:
; 2 exit points
;	.line	96; "Tombola.c"	unsigned int random(unsigned int min, unsigned int max)
	BANKSEL	r0x1020
	MOVWF	r0x1020
	MOVF	STK00,W
	MOVWF	r0x1021
	MOVF	STK01,W
	MOVWF	r0x1022
	MOVF	STK02,W
	MOVWF	r0x1023
;	.line	101; "Tombola.c"	rand += ((rand * rand) /100) % 10000;
	BANKSEL	_random_rand_65536_14
	MOVF	_random_rand_65536_14,W
	MOVWF	STK02
	MOVF	(_random_rand_65536_14 + 1),W
	MOVWF	STK01
	MOVF	_random_rand_65536_14,W
	MOVWF	STK00
	MOVF	(_random_rand_65536_14 + 1),W
	PAGESEL	__mulint
	CALL	__mulint
	PAGESEL	$
	BANKSEL	r0x1024
	MOVWF	r0x1024
	MOVF	STK00,W
	MOVWF	r0x1025
	MOVLW	0x64
	MOVWF	STK02
	MOVLW	0x00
	MOVWF	STK01
	MOVF	r0x1025,W
	MOVWF	STK00
	MOVF	r0x1024,W
	PAGESEL	__divuint
	CALL	__divuint
	PAGESEL	$
	BANKSEL	r0x1024
	MOVWF	r0x1024
	MOVF	STK00,W
	MOVWF	r0x1025
	MOVLW	0x10
	MOVWF	STK02
	MOVLW	0x27
	MOVWF	STK01
	MOVF	r0x1025,W
	MOVWF	STK00
	MOVF	r0x1024,W
	PAGESEL	__moduint
	CALL	__moduint
	PAGESEL	$
	BANKSEL	r0x1024
	MOVWF	r0x1024
	MOVF	STK00,W
	MOVWF	r0x1025
	BANKSEL	_random_rand_65536_14
	ADDWF	_random_rand_65536_14,F
	BANKSEL	r0x1024
	MOVF	r0x1024,W
	BTFSC	STATUS,0
	INCF	r0x1024,W
	BTFSC	STATUS,2
	GOTO	_00001_DS_
	BANKSEL	_random_rand_65536_14
	ADDWF	(_random_rand_65536_14 + 1),F
_00001_DS_:
;	.line	104; "Tombola.c"	return rand % (max+1-min)+min;
	BANKSEL	r0x1023
	INCF	r0x1023,F
	BTFSC	STATUS,2
	INCF	r0x1022,F
	MOVF	r0x1021,W
	SUBWF	r0x1023,F
	MOVF	r0x1020,W
	BTFSS	STATUS,0
	INCFSZ	r0x1020,W
	SUBWF	r0x1022,F
	MOVF	r0x1023,W
	MOVWF	STK02
	MOVF	r0x1022,W
	MOVWF	STK01
	BANKSEL	_random_rand_65536_14
	MOVF	_random_rand_65536_14,W
	MOVWF	STK00
	MOVF	(_random_rand_65536_14 + 1),W
	PAGESEL	__moduint
	CALL	__moduint
	PAGESEL	$
	BANKSEL	r0x1022
	MOVWF	r0x1022
	MOVF	STK00,W
	MOVWF	r0x1023
	MOVF	r0x1021,W
	ADDWF	r0x1023,W
	MOVWF	r0x1021
	MOVF	r0x1022,W
	BTFSC	STATUS,0
	INCFSZ	r0x1022,W
	ADDWF	r0x1020,F
	MOVF	r0x1021,W
	MOVWF	STK00
	MOVF	r0x1020,W
;	.line	106; "Tombola.c"	}
	RETURN	
; exit point of _random


;	code size estimation:
;	  634+  142 =   776 instructions ( 1836 byte)

	end
