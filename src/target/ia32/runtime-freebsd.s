	.file	"tiger-runtime.c"
	.text
	.type	__sputc, @function
__sputc:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	leal	-1(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	jns	.L2
	movl	12(%ebp), %eax
	movl	8(%eax), %edx
	movl	12(%ebp), %eax
	movl	24(%eax), %eax
	cmpl	%eax, %edx
	jl	.L3
	movl	8(%ebp), %eax
	cmpb	$10, %al
	je	.L3
.L2:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %ecx
	movl	12(%ebp), %edx
	movl	%ecx, (%edx)
	movl	8(%ebp), %edx
	movb	%dl, (%eax)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	jmp	.L4
.L3:
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__swbuf
.L4:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	__sputc, .-__sputc
	.globl	tc_init_array
	.type	tc_init_array, @function
tc_init_array:
.LFB1:
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
	jmp	.L6
.L7:
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	-16(%ebp), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%eax, (%edx)
	addl	$1, -12(%ebp)
.L6:
	movl	-12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	.L7
	movl	-16(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$8
	.cfi_endproc
.LFE1:
	.size	tc_init_array, .-tc_init_array
	.globl	tc_malloc
	.type	tc_malloc, @function
tc_malloc:
.LFB2:
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
	jne	.L10
	movl	__stderrp, %eax
	movl	%eax, 12(%esp)
	movl	$25, 8(%esp)
	movl	$1, 4(%esp)
	movl	$msg.2444, (%esp)
	call	fwrite
	movl	$120, (%esp)
	call	exit
.L10:
	movl	$0, -12(%ebp)
	jmp	.L11
.L12:
	movl	-16(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -16(%ebp)
	movl	$0, (%eax)
	movl	-12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -12(%ebp)
.L11:
	movl	-12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	.L12
	movl	-20(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE2:
	.size	tc_malloc, .-tc_malloc
	.globl	tc_not
	.type	tc_not, @function
tc_not:
.LFB3:
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
.LFE3:
	.size	tc_not, .-tc_not
	.globl	tc_exit
	.type	tc_exit, @function
tc_exit:
.LFB4:
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
.LFE4:
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
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$0, 8(%ebp)
	js	.L18
	cmpl	$255, 8(%ebp)
	jle	.L19
.L18:
	movl	__stderrp, %eax
	movl	%eax, 12(%esp)
	movl	$28, 8(%esp)
	movl	$1, 4(%esp)
	movl	$msg.2462, (%esp)
	call	fwrite
	movl	$120, (%esp)
	call	exit
.L19:
	movl	8(%ebp), %eax
	sall	$3, %eax
	addl	$consts, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE5:
	.size	tc_chr, .-tc_chr
	.globl	tc_concat
	.type	tc_concat, @function
tc_concat:
.LFB6:
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
	jne	.L22
	movl	12(%ebp), %eax
	jmp	.L23
.L22:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L24
	movl	8(%ebp), %eax
	jmp	.L23
.L24:
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
	jmp	.L25
.L26:
	movl	8(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %eax
	movl	-20(%ebp), %ecx
	movl	-12(%ebp), %edx
	addl	%ecx, %edx
	movb	%al, 4(%edx)
	addl	$1, -12(%ebp)
.L25:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L26
	movl	$0, -12(%ebp)
	jmp	.L27
.L28:
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
.L27:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L28
	movl	-20(%ebp), %eax
.L23:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$8
	.cfi_endproc
.LFE6:
	.size	tc_concat, .-tc_concat
	.globl	tc_ord
	.type	tc_ord, @function
tc_ord:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L30
	movl	$-1, %eax
	jmp	.L31
.L30:
	movl	8(%ebp), %eax
	movzbl	4(%eax), %eax
	movzbl	%al, %eax
.L31:
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE7:
	.size	tc_ord, .-tc_ord
	.globl	tc_size
	.type	tc_size, @function
tc_size:
.LFB8:
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
.LFE8:
	.size	tc_size, .-tc_size
	.globl	tc_substring
	.type	tc_substring, @function
tc_substring:
.LFB9:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	cmpl	$0, 12(%ebp)
	js	.L35
	cmpl	$0, 16(%ebp)
	js	.L35
	movl	16(%ebp), %eax
	movl	12(%ebp), %edx
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	.L36
.L35:
	movl	__stderrp, %eax
	movl	%eax, 12(%esp)
	movl	$35, 8(%esp)
	movl	$1, 4(%esp)
	movl	$msg.2487, (%esp)
	call	fwrite
	movl	$120, (%esp)
	call	exit
.L36:
	cmpl	$1, 16(%ebp)
	jne	.L37
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %eax
	movzbl	%al, %eax
	sall	$3, %eax
	addl	$consts, %eax
	jmp	.L38
.L37:
	movl	16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, (%eax)
	movl	$0, -12(%ebp)
	jmp	.L39
.L40:
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
.L39:
	movl	-12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	.L40
	movl	-16(%ebp), %eax
.L38:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$12
	.cfi_endproc
.LFE9:
	.size	tc_substring, .-tc_substring
	.globl	tc_strcmp
	.type	tc_strcmp, @function
tc_strcmp:
.LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	cmovle	%edx, %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jne	.L42
	movl	$0, %eax
	jmp	.L43
.L42:
	movl	$0, -4(%ebp)
	jmp	.L44
.L47:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %edx
	movl	12(%ebp), %ecx
	movl	-4(%ebp), %eax
	addl	%ecx, %eax
	movzbl	4(%eax), %eax
	cmpb	%al, %dl
	jae	.L45
	movl	$-1, %eax
	jmp	.L43
.L45:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %edx
	movl	12(%ebp), %ecx
	movl	-4(%ebp), %eax
	addl	%ecx, %eax
	movzbl	4(%eax), %eax
	cmpb	%al, %dl
	jbe	.L46
	movl	$1, %eax
	jmp	.L43
.L46:
	addl	$1, -4(%ebp)
.L44:
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jl	.L47
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jge	.L48
	movl	$-1, %eax
	jmp	.L43
.L48:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	.L49
	movl	$1, %eax
	jmp	.L43
.L49:
	movl	$0, %eax
.L43:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$8
	.cfi_endproc
.LFE10:
	.size	tc_strcmp, .-tc_strcmp
	.globl	tc_streq
	.type	tc_streq, @function
tc_streq:
.LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jne	.L51
	movl	$1, %eax
	jmp	.L52
.L51:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	je	.L53
	movl	$0, %eax
	jmp	.L52
.L53:
	movl	$0, -4(%ebp)
	jmp	.L54
.L56:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movzbl	4(%eax), %edx
	movl	12(%ebp), %ecx
	movl	-4(%ebp), %eax
	addl	%ecx, %eax
	movzbl	4(%eax), %eax
	cmpb	%al, %dl
	je	.L55
	movl	$0, %eax
	jmp	.L52
.L55:
	addl	$1, -4(%ebp)
.L54:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-4(%ebp), %eax
	jg	.L56
	movl	$1, %eax
.L52:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$8
	.cfi_endproc
.LFE11:
	.size	tc_streq, .-tc_streq
	.globl	tc_getchar
	.type	tc_getchar, @function
tc_getchar:
.LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	__isthreaded, %eax
	testl	%eax, %eax
	jne	.L58
	movl	__stdinp, %eax
	movl	4(%eax), %edx
	subl	$1, %edx
	movl	%edx, 4(%eax)
	movl	4(%eax), %eax
	testl	%eax, %eax
	jns	.L59
	movl	__stdinp, %eax
	movl	%eax, (%esp)
	call	__srget
	jmp	.L61
.L59:
	movl	__stdinp, %edx
	movl	(%edx), %eax
	leal	1(%eax), %ecx
	movl	%ecx, (%edx)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	jmp	.L61
.L58:
	movl	__stdinp, %eax
	movl	%eax, (%esp)
	call	getc
.L61:
	movl	%eax, -12(%ebp)
	cmpl	$-1, -12(%ebp)
	jne	.L62
	movl	$empty, %eax
	jmp	.L63
.L62:
	movl	-12(%ebp), %eax
	sall	$3, %eax
	addl	$consts, %eax
.L63:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE12:
	.size	tc_getchar, .-tc_getchar
	.globl	tc_print
	.type	tc_print, @function
tc_print:
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
	jmp	.L65
.L68:
	movl	__isthreaded, %eax
	testl	%eax, %eax
	jne	.L66
	movl	__stdoutp, %edx
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__sputc
	jmp	.L67
.L66:
	movl	__stdoutp, %edx
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	putc
.L67:
	addl	$1, -12(%ebp)
	addl	$1, -16(%ebp)
.L65:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L68
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE13:
	.size	tc_print, .-tc_print
	.globl	tc_print_err
	.type	tc_print_err, @function
tc_print_err:
.LFB14:
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
	jmp	.L70
.L73:
	movl	__isthreaded, %eax
	testl	%eax, %eax
	jne	.L71
	movl	__stderrp, %edx
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__sputc
	jmp	.L72
.L71:
	movl	__stderrp, %edx
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	putc
.L72:
	addl	$1, -12(%ebp)
	addl	$1, -16(%ebp)
.L70:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L73
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE14:
	.size	tc_print_err, .-tc_print_err
	.globl	tc_print_int
	.type	tc_print_int, @function
tc_print_int:
.LFB15:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	cmpl	$0, 8(%ebp)
	jns	.L75
	movl	__isthreaded, %eax
	testl	%eax, %eax
	jne	.L76
	movl	__stdoutp, %eax
	movl	%eax, 4(%esp)
	movl	$45, (%esp)
	call	__sputc
	jmp	.L77
.L76:
	movl	__stdoutp, %eax
	movl	%eax, 4(%esp)
	movl	$45, (%esp)
	call	putc
.L77:
	negl	8(%ebp)
.L75:
	movl	$1, -12(%ebp)
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%ebp)
	jmp	.L78
.L79:
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
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%ebp)
.L78:
	cmpl	$0, -16(%ebp)
	jne	.L79
	jmp	.L80
.L83:
	movl	8(%ebp), %eax
	cltd
	idivl	-12(%ebp)
	movl	%eax, -16(%ebp)
	movl	__isthreaded, %eax
	testl	%eax, %eax
	jne	.L81
	movl	__stdoutp, %eax
	movl	-16(%ebp), %edx
	addl	$48, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	__sputc
	jmp	.L82
.L81:
	movl	__stdoutp, %eax
	movl	-16(%ebp), %edx
	addl	$48, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	putc
.L82:
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
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -12(%ebp)
.L80:
	cmpl	$0, -12(%ebp)
	jg	.L83
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE15:
	.size	tc_print_int, .-tc_print_int
	.globl	tc_flush
	.type	tc_flush, @function
tc_flush:
.LFB16:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	__stdoutp, %eax
	movl	%eax, (%esp)
	call	fflush
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE16:
	.size	tc_flush, .-tc_flush
	.globl	main
	.type	main, @function
main:
.LFB17:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 28(%esp)
	jmp	.L86
.L87:
	movl	28(%esp), %eax
	movl	$1, consts(,%eax,8)
	movl	28(%esp), %eax
	movl	%eax, %edx
	movl	28(%esp), %eax
	movb	%dl, consts+4(,%eax,8)
	addl	$1, 28(%esp)
.L86:
	cmpl	$255, 28(%esp)
	jle	.L87
	movl	$0, (%esp)
	call	tc_main
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE17:
	.size	main, .-main
	.section	.rodata
	.type	msg.2444, @object
	.size	msg.2444, 26
msg.2444:
	.string	"malloc: memory exhausted\n"
	.type	msg.2462, @object
	.size	msg.2462, 29
msg.2462:
	.string	"chr: character out of range\n"
	.align 32
	.type	msg.2487, @object
	.size	msg.2487, 36
msg.2487:
	.string	"substring: arguments out of bounds\n"
	.ident	"GCC: (FreeBSD Ports Collection) 4.8.2 20130815 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
