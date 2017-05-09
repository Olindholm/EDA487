@
@ Copyright 2017 (C) Osvald Lindholm
@
@ This file is the result of the lab excercises provided
@ for the Maskinorienterad programmering (EDA407)
@ course at Chalmers. The lab exercises can be found at:
@ http://www.cse.chalmers.se/edu/year/2017/course/EDA482_7/Documents/LabPM-MOP-2017-02-18.pdf
@
@ This file is written for the MD407 lab computer
@ using an ARM V6-m processor.
@ Detailed specficiations can be found at:
@ http://www.cse.chalmers.se/edu/resources/mop/documents/MD407_beskrivning.pdf
@ http://www.cse.chalmers.se/edu/year/2017/course/EDA482_7/Documents/quickguide-mop.pdf
@ 

start:	@ Configure the GPIO D (port) to output
	LDR	R0,=0x55555555
	LDR	R1,=0x40020C00
	STR	R0,[R1]

	LDR	R1,=0x40020C14	@ GPIO D output address
	LDR	R2,=0x40021010	@ GPIO E input address (input by default)

main:	@ Read input, write output, repeat
	LDR	R0,[R2]
	STR	R0,[R1]
	B	main
