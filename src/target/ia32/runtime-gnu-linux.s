	.file	"tiger-runtime.c"
	.text
	.globl	tc_init_array
	.type	tc_init_array, @function
tc_init_array:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -16(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	-16(%ebp), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%eax, (%edx)
	addl	$1, -12(%ebp)
.L2:
	movl	-12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	.L3
	movl	-16(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$8
	.cfi_endproc
.LFE0:
	.size	tc_init_array, .-tc_init_array
	.globl	tc_malloc
	.type	tc_malloc, @function
tc_malloc:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
	cmpl	$0, -20(%ebp)
	jne	.L6
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$25, 8(%esp)
	movl	$1, 4(%esp)
	movl	$msg.2328, (%esp)
	call	fwrite
	movl	$120, (%esp)
	call	exit
.L6:
	movl	$0, -12(%ebp)
	jmp	.L7
.L8:
	movl	-16(%ebp), %eax
	movl	$0, (%eax)
	addl	$4, -16(%ebp)
	movl	-12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -12(%ebp)
.L7:
	movl	-12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	.L8
	movl	-20(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE1:
	.size	tc_malloc, .-tc_malloc
	.globl	tc_not
	.type	tc_not, @function
tc_not:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	cmpl	$0, 8(%ebp)
	sete	%al
	movzbl	%al, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE2:
	.size	tc_not, .-tc_not
	.globl	tc_exit
	.type	tc_exit, @function
tc_exit:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	exit
	.cfi_endproc
.LFE3:
	.size	tc_exit, .-tc_exit
	.globl	consts
	.bss
	.align 32
	.type	consts, @object
	.size	consts, 2048
consts:
	.zero	2048
	.globl	empty
	.align 4
	.type	empty, @object
	.size	empty, 8
empty:
	.zero	8
	.text
	.globl	tc_chr
	.type	tc_chr, @function
tc_chr:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$0, 8(%ebp)
	js	.L14
	cmpl	$255, 8(%ebp)
	jle	.L15
.L14:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$28, 8(%esp)
	movl	$1, 4(%esp)
	movl	$msg.2346, (%esp)
	call	fwrite
	movl	$120, (%esp)
	call	exit
.L15:
	movl	8(%ebp), %eax
	sall	$3, %eax
	addl	$consts, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE4:
	.size	tc_chr, .-tc_chr
	.globl	tc_concat
	.type	tc_concat, @function
tc_concat:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L18
	movl	12(%ebp), %eax
	jmp	.L19
.L18:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L20
	movl	8(%ebp), %eax
	jmp	.L19
.L20:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, (%eax)
	movl	$0, -12(%ebp)
	jmp	.L21
.L22:
	movl	8(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %eax
	movl	-20(%ebp), %ecx
	movl	-12(%ebp), %edx
	addl	%ecx, %edx
	movb	%al, 4(%edx)
	addl	$1, -12(%ebp)
.L21:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L22
	movl	$0, -12(%ebp)
	jmp	.L23
.L24:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	12(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %edx
	movl	-20(%ebp), %eax
	movb	%dl, 4(%eax,%ecx)
	addl	$1, -12(%ebp)
.L23:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L24
	movl	-20(%ebp), %eax
.L19:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$8
	.cfi_endproc
.LFE5:
	.size	tc_concat, .-tc_concat
	.globl	tc_ord
	.type	tc_ord, @function
tc_ord:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L26
	movl	$-1, %eax
	jmp	.L27
.L26:
	movl	8(%ebp), %eax
	movzbl	4(%eax), %eax
	movzbl	%al, %eax
.L27:
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE6:
	.size	tc_ord, .-tc_ord
	.globl	tc_size
	.type	tc_size, @function
tc_size:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE7:
	.size	tc_size, .-tc_size
	.globl	tc_substring
	.type	tc_substring, @function
tc_substring:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	cmpl	$0, 12(%ebp)
	js	.L31
	cmpl	$0, 16(%ebp)
	js	.L31
	movl	16(%ebp), %eax
	movl	12(%ebp), %edx
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	.L32
.L31:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$35, 8(%esp)
	movl	$1, 4(%esp)
	movl	$msg.2371, (%esp)
	call	fwrite
	movl	$120, (%esp)
	call	exit
.L32:
	cmpl	$1, 16(%ebp)
	jne	.L33
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %eax
	movzbl	%al, %eax
	sall	$3, %eax
	addl	$consts, %eax
	jmp	.L34
.L33:
	movl	16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, (%eax)
	movl	$0, -12(%ebp)
	jmp	.L35
.L36:
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movzbl	4(%eax,%edx), %eax
	movl	-16(%ebp), %ecx
	movl	-12(%ebp), %edx
	addl	%ecx, %edx
	movb	%al, 4(%edx)
	addl	$1, -12(%ebp)
.L35:
	movl	-12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	.L36
	movl	-16(%ebp), %eax
.L34:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$12
	.cfi_endproc
.LFE8:
	.size	tc_substring, .-tc_substring
	.globl	tc_strcmp
	.type	tc_strcmp, @function
  # FIXME: Some code was deleted here (strcmp).
  # FIXME: Some code was deleted here (streq).
tc_getchar:
.LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	stdin, %eax
	movl	%eax, (%esp)
	call	_IO_getc
	movl	%eax, -12(%ebp)
	cmpl	$-1, -12(%ebp)
	jne	.L55
	movl	$empty, %eax
	jmp	.L56
.L55:
	movl	-12(%ebp), %eax
	sall	$3, %eax
	addl	$consts, %eax
.L56:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	tc_getchar, .-tc_getchar
	.globl	tc_print
	.type	tc_print, @function
tc_print:
.LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -16(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L58
.L59:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, (%esp)
	call	putchar
	addl	$1, -12(%ebp)
	addl	$1, -16(%ebp)
.L58:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L59
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE12:
	.size	tc_print, .-tc_print
	.globl	tc_print_err
	.type	tc_print_err, @function
tc_print_err:
.LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -16(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L61
.L62:
	movl	stderr, %edx
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_IO_putc
	addl	$1, -12(%ebp)
	addl	$1, -16(%ebp)
.L61:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L62
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE13:
	.size	tc_print_err, .-tc_print_err
	.globl	tc_print_int
	.type	tc_print_int, @function
tc_print_int:
.LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	cmpl	$0, 8(%ebp)
	jns	.L64
	movl	stdout, %eax
	movl	%eax, 4(%esp)
	movl	$45, (%esp)
	call	_IO_putc
	negl	8(%ebp)
.L64:
	movl	$1, -12(%ebp)
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -16(%ebp)
	jmp	.L65
.L66:
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -16(%ebp)
.L65:
	cmpl	$0, -16(%ebp)
	jne	.L66
	jmp	.L67
.L68:
	movl	8(%ebp), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-12(%ebp)
	movl	%eax, -16(%ebp)
	movl	stdout, %eax
	movl	-16(%ebp), %edx
	addl	$48, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	_IO_putc
	movl	-16(%ebp), %eax
	imull	-12(%ebp), %eax
	subl	%eax, 8(%ebp)
	movl	-12(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -12(%ebp)
.L67:
	cmpl	$0, -12(%ebp)
	jg	.L68
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE14:
	.size	tc_print_int, .-tc_print_int
	.globl	tc_flush
	.type	tc_flush, @function
tc_flush:
.LFB15:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	stdout, %eax
	movl	%eax, (%esp)
	call	fflush
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE15:
	.size	tc_flush, .-tc_flush
	.globl	main
	.type	main, @function
main:
.LFB16:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 28(%esp)
	jmp	.L71
.L72:
	movl	28(%esp), %eax
	movl	$1, consts(,%eax,8)
	movl	28(%esp), %eax
	movl	%eax, %edx
	movl	28(%esp), %eax
	movb	%dl, consts+4(,%eax,8)
	addl	$1, 28(%esp)
.L71:
	cmpl	$255, 28(%esp)
	jle	.L72
	movl	$0, (%esp)
	call	tc_main
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE16:
	.size	main, .-main
	.section	.rodata
	.align 32
	.type	msg.2371, @object
	.size	msg.2371, 36
msg.2371:
	.string	"substring: arguments out of bounds\n"
	.type	msg.2346, @object
	.size	msg.2346, 29
msg.2346:
	.string	"chr: character out of range\n"
	.type	msg.2328, @object
	.size	msg.2328, 26
msg.2328:
	.string	"malloc: memory exhausted\n"
	.ident	"GCC: (Debian 4.7.2-5) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
