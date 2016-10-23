	.file	"prog.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	call foo
	out 0x4,r24
	ldi r24,lo8(-1)
	out 0x5,r24
	ldi r24,0
	ldi r25,0
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9.2"
