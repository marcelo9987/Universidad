	.file	"programa_2.c"
# GNU C17 (Ubuntu 11.3.0-1ubuntu1~22.04) version 11.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -m32 -mtune=generic -march=i686 -g -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection
	.text
.Ltext0:
	.file 0 "/home/ssoo/EnlaceSSOO/opcionales/1" "programa_2.c"
	.globl	suma
	.bss
	.align 4
	.type	suma, @object
	.size	suma, 4
suma:
	.zero	4
	.globl	M
	.align 4
	.type	M, @object
	.size	M, 4
M:
	.zero	4
	.globl	T
	.align 4
	.type	T, @object
	.size	T, 4
T:
	.zero	4
	.text
	.globl	sum
	.type	sum, @function
sum:
.LFB6:
	.file 1 "programa_2.c"
	.loc 1 12 1
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$16, %esp	#,
	call	__x86.get_pc_thunk.ax	#
	addl	$_GLOBAL_OFFSET_TABLE_, %eax	# tmp82,
# programa_2.c:13:     uintptr_t hilo = (uintptr_t) philo;
	.loc 1 13 15
	movl	8(%ebp), %edx	# philo, tmp88
	movl	%edx, -4(%ebp)	# tmp88, hilo
# programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 12
	movl	-4(%ebp), %edx	# hilo, tmp89
	movl	%edx, -8(%ebp)	# tmp89, j
# programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 5
	jmp	.L2	#
.L3:
# programa_2.c:17:         suma = suma + j;
	.loc 1 17 21 discriminator 3
	movl	suma@GOTOFF(%eax), %ecx	# suma, suma.0_1
	movl	-8(%ebp), %edx	# j, tmp90
	addl	%ecx, %edx	# suma.0_1, _2
# programa_2.c:17:         suma = suma + j;
	.loc 1 17 14 discriminator 3
	movl	%edx, suma@GOTOFF(%eax)	# _2, suma
# programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 30 discriminator 3
	movl	T@GOTOFF(%eax), %edx	# T, T.1_3
	addl	%edx, -8(%ebp)	# T.1_3, j
.L2:
# programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 22 discriminator 1
	movl	M@GOTOFF(%eax), %edx	# M, M.2_4
	cmpl	%edx, -8(%ebp)	# M.2_4, j
	jle	.L3	#,
# programa_2.c:19: }
	.loc 1 19 1
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE6:
	.size	sum, .-sum
	.section	.rodata
.LC0:
	.string	"OK"
.LC1:
	.string	"Error"
.LC2:
	.string	"%d,%d,%d,%d,[%s]\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.loc 1 22 1
	.cfi_startproc
	leal	4(%esp), %ecx	#,
	.cfi_def_cfa 1, 0
	andl	$-16, %esp	#,
	pushl	-4(%ecx)	#
	pushl	%ebp	#
	movl	%esp, %ebp	#,
	.cfi_escape 0x10,0x5,0x2,0x75,0
	pushl	%edi	#
	pushl	%esi	#
	pushl	%ebx	#
	pushl	%ecx	#
	.cfi_escape 0xf,0x3,0x75,0x70,0x6
	.cfi_escape 0x10,0x7,0x2,0x75,0x7c
	.cfi_escape 0x10,0x6,0x2,0x75,0x78
	.cfi_escape 0x10,0x3,0x2,0x75,0x74
	subl	$56, %esp	#,
	call	__x86.get_pc_thunk.bx	#
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx	# tmp82,
	movl	%ecx, %eax	#, tmp163
	movl	4(%eax), %edx	# argv, tmp128
	movl	%edx, -60(%ebp)	# tmp128, argv
# programa_2.c:22: {
	.loc 1 22 1
	movl	%gs:20, %edx	# MEM[(<address-space-2> unsigned int *)20B], tmp166
	movl	%edx, -28(%ebp)	# tmp166, D.3034
	xorl	%edx, %edx	# tmp166
	movl	%esp, %edx	#, tmp129
	movl	%edx, -72(%ebp)	# tmp129, %sfp
# programa_2.c:23:     if (argc < 3)
	.loc 1 23 8
	cmpl	$2, (%eax)	#, argc
	jg	.L5	#,
# programa_2.c:24:     { return (-1); }
	.loc 1 24 14
	movl	$-1, %eax	#, _43
	jmp	.L6	#
.L5:
# programa_2.c:25:     M = atoi(argv[1]);
	.loc 1 25 18
	movl	-60(%ebp), %eax	# argv, tmp130
	addl	$4, %eax	#, _1
# programa_2.c:25:     M = atoi(argv[1]);
	.loc 1 25 9
	movl	(%eax), %eax	# *_1, _2
	subl	$12, %esp	#,
	pushl	%eax	# _2
	call	atoi@PLT	#
	addl	$16, %esp	#,
# programa_2.c:25:     M = atoi(argv[1]);
	.loc 1 25 7
	movl	%eax, M@GOTOFF(%ebx)	# _3, M
# programa_2.c:26:     T = atoi(argv[2]);
	.loc 1 26 18
	movl	-60(%ebp), %eax	# argv, tmp131
	addl	$8, %eax	#, _4
# programa_2.c:26:     T = atoi(argv[2]);
	.loc 1 26 9
	movl	(%eax), %eax	# *_4, _5
	subl	$12, %esp	#,
	pushl	%eax	# _5
	call	atoi@PLT	#
	addl	$16, %esp	#,
# programa_2.c:26:     T = atoi(argv[2]);
	.loc 1 26 7
	movl	%eax, T@GOTOFF(%ebx)	# _6, T
# programa_2.c:27:     pthread_t hilos[T];
	.loc 1 27 5
	movl	T@GOTOFF(%ebx), %eax	# T, T.3_55
# programa_2.c:27:     pthread_t hilos[T];
	.loc 1 27 15
	leal	-1(%eax), %edx	#, _7
	movl	%edx, -36(%ebp)	# _8, D.3019
	leal	0(,%eax,4), %edx	#, _18
	movl	$16, %eax	#, tmp164
	subl	$1, %eax	#, tmp132
	addl	%edx, %eax	# _18, tmp133
	movl	$16, %esi	#, tmp165
	movl	$0, %edx	#, tmp136
	divl	%esi	# tmp165
	imull	$16, %eax, %eax	#, tmp135, tmp137
	movl	%eax, %ecx	# tmp137, tmp139
	andl	$-4096, %ecx	#, tmp139
	movl	%esp, %edx	#, tmp140
	subl	%ecx, %edx	# tmp139, tmp140
.L7:
	cmpl	%edx, %esp	# tmp140,
	je	.L8	#,
	subl	$4096, %esp	#,
	orl	$0, 4092(%esp)	#,
	jmp	.L7	#
.L8:
	movl	%eax, %edx	# tmp137, tmp141
	andl	$4095, %edx	#, tmp141
	subl	%edx, %esp	# tmp141,
	movl	%eax, %edx	# tmp137, tmp142
	andl	$4095, %edx	#, tmp142
	testl	%edx, %edx	# tmp142
	je	.L9	#,
	andl	$4095, %eax	#, tmp143
	subl	$4, %eax	#, tmp143
	addl	%esp, %eax	#, tmp144
	orl	$0, (%eax)	#,
.L9:
	movl	%esp, %eax	#, tmp138
	addl	$3, %eax	#, tmp145
	shrl	$2, %eax	#, tmp146
	sall	$2, %eax	#, tmp147
	movl	%eax, -32(%ebp)	# tmp147, hilos.8
.LBB2:
# programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 20
	movl	$0, -44(%ebp)	#, indice_creacionHilos
# programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 5
	jmp	.L10	#
.L11:
# programa_2.c:30:         pthread_create(&hilos[indice_creacionHilos], NULL, &sum, (void *) indice_creacionHilos);
	.loc 1 30 9 discriminator 3
	movl	-44(%ebp), %eax	# indice_creacionHilos, indice_creacionHilos.9_19
	movl	-44(%ebp), %edx	# indice_creacionHilos, tmp149
	leal	0(,%edx,4), %ecx	#, tmp148
	movl	-32(%ebp), %edx	# hilos.8, tmp150
	addl	%ecx, %edx	# tmp148, _20
	pushl	%eax	# indice_creacionHilos.9_19
	leal	sum@GOTOFF(%ebx), %eax	#, tmp151
	pushl	%eax	# tmp151
	pushl	$0	#
	pushl	%edx	# _20
	call	pthread_create@PLT	#
	addl	$16, %esp	#,
# programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 92 discriminator 3
	addl	$1, -44(%ebp)	#, indice_creacionHilos
.L10:
# programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 67 discriminator 1
	movl	T@GOTOFF(%ebx), %eax	# T, T.10_21
	cmpl	%eax, -44(%ebp)	# T.11_22, indice_creacionHilos
	jb	.L11	#,
.LBE2:
.LBB3:
# programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 14
	movl	$0, -40(%ebp)	#, indice_creacionHilos
# programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 5
	jmp	.L12	#
.L13:
# programa_2.c:35:         pthread_join(hilos[indice_creacionHilos], NULL);
	.loc 1 35 9 discriminator 3
	movl	-32(%ebp), %eax	# hilos.8, tmp152
	movl	-40(%ebp), %edx	# indice_creacionHilos, tmp153
	movl	(%eax,%edx,4), %eax	# (*hilos.8_62)[indice_creacionHilos_42], _23
	subl	$8, %esp	#,
	pushl	$0	#
	pushl	%eax	# _23
	call	pthread_join@PLT	#
	addl	$16, %esp	#,
# programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 86 discriminator 3
	addl	$1, -40(%ebp)	#, indice_creacionHilos
.L12:
# programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 61 discriminator 1
	movl	T@GOTOFF(%ebx), %eax	# T, T.12_24
	cmpl	%eax, -40(%ebp)	# T.12_24, indice_creacionHilos
	jl	.L13	#,
.LBE3:
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 90
	movl	M@GOTOFF(%ebx), %eax	# M, M.14_25
	leal	1(%eax), %edx	#, _26
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 85
	movl	M@GOTOFF(%ebx), %eax	# M, M.15_27
	imull	%edx, %eax	# _26, _28
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 96
	movl	%eax, %edx	# _28, tmp154
	shrl	$31, %edx	#, tmp154
	addl	%edx, %eax	# tmp154, tmp155
	sarl	%eax	# tmp156
	negl	%eax	# tmp156
	movl	%eax, %edx	# tmp156, _29
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 80
	movl	suma@GOTOFF(%ebx), %eax	# suma, suma.16_30
	addl	%edx, %eax	# _29, _31
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5
	testl	%eax, %eax	# _31
	jne	.L14	#,
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5 is_stmt 0 discriminator 1
	leal	.LC0@GOTOFF(%ebx), %ecx	#, iftmp.13_44
	jmp	.L15	#
.L14:
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5 discriminator 2
	leal	.LC1@GOTOFF(%ebx), %ecx	#, iftmp.13_44
.L15:
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5 discriminator 4
	movl	suma@GOTOFF(%ebx), %eax	# suma, suma.17_32
	movl	%eax, -64(%ebp)	# suma.17_32, %sfp
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 57 is_stmt 1 discriminator 4
	movl	M@GOTOFF(%ebx), %eax	# M, M.18_33
	leal	1(%eax), %edx	#, _34
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 52 discriminator 4
	movl	M@GOTOFF(%ebx), %eax	# M, M.19_35
	imull	%edx, %eax	# _34, _36
# programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5 discriminator 4
	movl	%eax, %edx	# _36, tmp157
	shrl	$31, %edx	#, tmp157
	addl	%edx, %eax	# tmp157, tmp158
	sarl	%eax	# tmp159
	movl	%eax, -68(%ebp)	# tmp159, %sfp
	movl	T@GOTOFF(%ebx), %edi	# T, T.20_38
	movl	M@GOTOFF(%ebx), %esi	# M, M.21_39
	movl	stdout@GOT(%ebx), %eax	#, tmp160
	movl	(%eax), %edx	# stdout, stdout.22_40
	subl	$4, %esp	#,
	pushl	%ecx	# iftmp.13_44
	pushl	-64(%ebp)	# %sfp
	pushl	-68(%ebp)	# %sfp
	pushl	%edi	# T.20_38
	pushl	%esi	# M.21_39
	leal	.LC2@GOTOFF(%ebx), %eax	#, tmp161
	pushl	%eax	# tmp161
	pushl	%edx	# stdout.22_40
	call	fprintf@PLT	#
	addl	$32, %esp	#,
# programa_2.c:40:     return (0);
	.loc 1 40 12 discriminator 4
	movl	$0, %eax	#, _43
.L6:
	movl	-72(%ebp), %esp	# %sfp,
# programa_2.c:41: }
	.loc 1 41 1
	movl	-28(%ebp), %edx	# D.3034, tmp167
	subl	%gs:20, %edx	# MEM[(<address-space-2> unsigned int *)20B], tmp167
	je	.L17	#,
	call	__stack_chk_fail_local	#
.L17:
	leal	-16(%ebp), %esp	#,
	popl	%ecx	#
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx	#
	.cfi_restore 3
	popl	%esi	#
	.cfi_restore 6
	popl	%edi	#
	.cfi_restore 7
	popl	%ebp	#
	.cfi_restore 5
	leal	-4(%ecx), %esp	#,
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB8:
	.cfi_startproc
	movl	(%esp), %eax	#,
	ret
	.cfi_endproc
.LFE8:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB9:
	.cfi_startproc
	movl	(%esp), %ebx	#,
	ret
	.cfi_endproc
.LFE9:
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h"
	.file 3 "/usr/include/bits/types.h"
	.file 4 "/usr/include/bits/types/struct_FILE.h"
	.file 5 "/usr/include/bits/types/FILE.h"
	.file 6 "/usr/include/bits/pthreadtypes.h"
	.file 7 "/usr/include/stdint.h"
	.file 8 "/usr/include/stdio.h"
	.file 9 "/usr/include/pthread.h"
	.file 10 "/usr/include/stdlib.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x491
	.value	0x5
	.byte	0x1
	.byte	0x4
	.long	.Ldebug_abbrev0
	.uleb128 0x10
	.long	.LASF66
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x5
	.long	.LASF9
	.byte	0x2
	.byte	0xd1
	.byte	0x17
	.long	0x32
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF3
	.uleb128 0xd
	.long	0x39
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF6
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF8
	.uleb128 0x11
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.long	.LASF10
	.byte	0x3
	.byte	0x2f
	.byte	0x2c
	.long	0x7b
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF11
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF12
	.uleb128 0x5
	.long	.LASF13
	.byte	0x3
	.byte	0x98
	.byte	0x19
	.long	0x95
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.long	.LASF14
	.uleb128 0x5
	.long	.LASF15
	.byte	0x3
	.byte	0x99
	.byte	0x1b
	.long	0x6f
	.uleb128 0x12
	.byte	0x4
	.uleb128 0x6
	.long	0xa8
	.uleb128 0x2
	.long	0x39
	.uleb128 0x13
	.long	.LASF67
	.byte	0x94
	.byte	0x4
	.byte	0x31
	.byte	0x8
	.long	0x21e
	.uleb128 0x1
	.long	.LASF16
	.byte	0x33
	.byte	0x7
	.long	0x68
	.byte	0
	.uleb128 0x1
	.long	.LASF17
	.byte	0x36
	.byte	0x9
	.long	0xaf
	.byte	0x4
	.uleb128 0x1
	.long	.LASF18
	.byte	0x37
	.byte	0x9
	.long	0xaf
	.byte	0x8
	.uleb128 0x1
	.long	.LASF19
	.byte	0x38
	.byte	0x9
	.long	0xaf
	.byte	0xc
	.uleb128 0x1
	.long	.LASF20
	.byte	0x39
	.byte	0x9
	.long	0xaf
	.byte	0x10
	.uleb128 0x1
	.long	.LASF21
	.byte	0x3a
	.byte	0x9
	.long	0xaf
	.byte	0x14
	.uleb128 0x1
	.long	.LASF22
	.byte	0x3b
	.byte	0x9
	.long	0xaf
	.byte	0x18
	.uleb128 0x1
	.long	.LASF23
	.byte	0x3c
	.byte	0x9
	.long	0xaf
	.byte	0x1c
	.uleb128 0x1
	.long	.LASF24
	.byte	0x3d
	.byte	0x9
	.long	0xaf
	.byte	0x20
	.uleb128 0x1
	.long	.LASF25
	.byte	0x40
	.byte	0x9
	.long	0xaf
	.byte	0x24
	.uleb128 0x1
	.long	.LASF26
	.byte	0x41
	.byte	0x9
	.long	0xaf
	.byte	0x28
	.uleb128 0x1
	.long	.LASF27
	.byte	0x42
	.byte	0x9
	.long	0xaf
	.byte	0x2c
	.uleb128 0x1
	.long	.LASF28
	.byte	0x44
	.byte	0x16
	.long	0x237
	.byte	0x30
	.uleb128 0x1
	.long	.LASF29
	.byte	0x46
	.byte	0x14
	.long	0x23c
	.byte	0x34
	.uleb128 0x1
	.long	.LASF30
	.byte	0x48
	.byte	0x7
	.long	0x68
	.byte	0x38
	.uleb128 0x1
	.long	.LASF31
	.byte	0x49
	.byte	0x7
	.long	0x68
	.byte	0x3c
	.uleb128 0x1
	.long	.LASF32
	.byte	0x4a
	.byte	0xb
	.long	0x89
	.byte	0x40
	.uleb128 0x1
	.long	.LASF33
	.byte	0x4d
	.byte	0x12
	.long	0x4c
	.byte	0x44
	.uleb128 0x1
	.long	.LASF34
	.byte	0x4e
	.byte	0xf
	.long	0x5a
	.byte	0x46
	.uleb128 0x1
	.long	.LASF35
	.byte	0x4f
	.byte	0x8
	.long	0x241
	.byte	0x47
	.uleb128 0x1
	.long	.LASF36
	.byte	0x51
	.byte	0xf
	.long	0x251
	.byte	0x48
	.uleb128 0x1
	.long	.LASF37
	.byte	0x59
	.byte	0xd
	.long	0x9c
	.byte	0x4c
	.uleb128 0x1
	.long	.LASF38
	.byte	0x5b
	.byte	0x17
	.long	0x25b
	.byte	0x54
	.uleb128 0x1
	.long	.LASF39
	.byte	0x5c
	.byte	0x19
	.long	0x265
	.byte	0x58
	.uleb128 0x1
	.long	.LASF40
	.byte	0x5d
	.byte	0x14
	.long	0x23c
	.byte	0x5c
	.uleb128 0x1
	.long	.LASF41
	.byte	0x5e
	.byte	0x9
	.long	0xa8
	.byte	0x60
	.uleb128 0x1
	.long	.LASF42
	.byte	0x5f
	.byte	0xa
	.long	0x26
	.byte	0x64
	.uleb128 0x1
	.long	.LASF43
	.byte	0x60
	.byte	0x7
	.long	0x68
	.byte	0x68
	.uleb128 0x1
	.long	.LASF44
	.byte	0x62
	.byte	0x8
	.long	0x26a
	.byte	0x6c
	.byte	0
	.uleb128 0x5
	.long	.LASF45
	.byte	0x5
	.byte	0x7
	.byte	0x19
	.long	0xb4
	.uleb128 0x14
	.long	.LASF68
	.byte	0x4
	.byte	0x2b
	.byte	0xe
	.uleb128 0x9
	.long	.LASF46
	.uleb128 0x2
	.long	0x232
	.uleb128 0x2
	.long	0xb4
	.uleb128 0x7
	.long	0x39
	.long	0x251
	.uleb128 0xa
	.long	0x32
	.byte	0
	.byte	0
	.uleb128 0x2
	.long	0x22a
	.uleb128 0x9
	.long	.LASF47
	.uleb128 0x2
	.long	0x256
	.uleb128 0x9
	.long	.LASF48
	.uleb128 0x2
	.long	0x260
	.uleb128 0x7
	.long	0x39
	.long	0x27a
	.uleb128 0xa
	.long	0x32
	.byte	0x27
	.byte	0
	.uleb128 0x2
	.long	0x21e
	.uleb128 0x6
	.long	0x27a
	.uleb128 0x15
	.long	.LASF54
	.byte	0x8
	.byte	0x90
	.byte	0xe
	.long	0x27a
	.uleb128 0x2
	.long	0x40
	.uleb128 0x6
	.long	0x290
	.uleb128 0x5
	.long	.LASF49
	.byte	0x6
	.byte	0x1b
	.byte	0x1b
	.long	0x53
	.uleb128 0x16
	.long	.LASF52
	.byte	0x24
	.byte	0x6
	.byte	0x38
	.byte	0x7
	.long	0x2ca
	.uleb128 0xe
	.long	.LASF50
	.byte	0x3a
	.byte	0x8
	.long	0x2ca
	.uleb128 0xe
	.long	.LASF51
	.byte	0x3b
	.byte	0xc
	.long	0x95
	.byte	0
	.uleb128 0x7
	.long	0x39
	.long	0x2da
	.uleb128 0xa
	.long	0x32
	.byte	0x23
	.byte	0
	.uleb128 0x5
	.long	.LASF52
	.byte	0x6
	.byte	0x3e
	.byte	0x1e
	.long	0x2a6
	.uleb128 0xd
	.long	0x2da
	.uleb128 0x5
	.long	.LASF53
	.byte	0x7
	.byte	0x60
	.byte	0x17
	.long	0x32
	.uleb128 0x17
	.long	.LASF55
	.byte	0x1
	.byte	0x8
	.byte	0x5
	.long	0x68
	.uleb128 0x5
	.byte	0x3
	.long	suma
	.uleb128 0xf
	.string	"M"
	.byte	0x5
	.long	0x68
	.uleb128 0x5
	.byte	0x3
	.long	M
	.uleb128 0xf
	.string	"T"
	.byte	0x8
	.long	0x68
	.uleb128 0x5
	.byte	0x3
	.long	T
	.uleb128 0x18
	.long	.LASF56
	.byte	0x8
	.value	0x15e
	.byte	0xc
	.long	0x68
	.long	0x342
	.uleb128 0x4
	.long	0x27f
	.uleb128 0x4
	.long	0x295
	.uleb128 0x19
	.byte	0
	.uleb128 0xb
	.long	.LASF57
	.byte	0x9
	.byte	0xdb
	.long	0x68
	.long	0x35c
	.uleb128 0x4
	.long	0x29a
	.uleb128 0x4
	.long	0x35c
	.byte	0
	.uleb128 0x2
	.long	0xa8
	.uleb128 0xb
	.long	.LASF58
	.byte	0x9
	.byte	0xca
	.long	0x68
	.long	0x385
	.uleb128 0x4
	.long	0x38a
	.uleb128 0x4
	.long	0x394
	.uleb128 0x4
	.long	0x399
	.uleb128 0x4
	.long	0xaa
	.byte	0
	.uleb128 0x2
	.long	0x29a
	.uleb128 0x6
	.long	0x385
	.uleb128 0x2
	.long	0x2e6
	.uleb128 0x6
	.long	0x38f
	.uleb128 0x2
	.long	0x39e
	.uleb128 0x1a
	.long	0xa8
	.long	0x3ad
	.uleb128 0x4
	.long	0xa8
	.byte	0
	.uleb128 0xb
	.long	.LASF59
	.byte	0xa
	.byte	0x69
	.long	0x68
	.long	0x3c2
	.uleb128 0x4
	.long	0x290
	.byte	0
	.uleb128 0x1b
	.long	.LASF69
	.byte	0x1
	.byte	0x15
	.byte	0x5
	.long	0x68
	.long	.LFB7
	.long	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x43c
	.uleb128 0xc
	.long	.LASF60
	.byte	0x15
	.byte	0xe
	.long	0x68
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xc
	.long	.LASF61
	.byte	0x15
	.byte	0x1a
	.long	0x43c
	.uleb128 0x2
	.byte	0x75
	.sleb128 -60
	.uleb128 0x8
	.long	.LASF62
	.byte	0x1b
	.byte	0xf
	.long	0x441
	.uleb128 0x3
	.byte	0x75
	.sleb128 -32
	.byte	0x6
	.uleb128 0x1c
	.long	.LBB2
	.long	.LBE2-.LBB2
	.long	0x423
	.uleb128 0x8
	.long	.LASF63
	.byte	0x1c
	.byte	0x14
	.long	0x2eb
	.uleb128 0x2
	.byte	0x75
	.sleb128 -44
	.byte	0
	.uleb128 0x1d
	.long	.LBB3
	.long	.LBE3-.LBB3
	.uleb128 0x8
	.long	.LASF63
	.byte	0x21
	.byte	0xe
	.long	0x68
	.uleb128 0x2
	.byte	0x75
	.sleb128 -40
	.byte	0
	.byte	0
	.uleb128 0x2
	.long	0xaf
	.uleb128 0x7
	.long	0x29a
	.long	0x454
	.uleb128 0x1e
	.long	0x32
	.uleb128 0x3
	.byte	0x75
	.sleb128 -36
	.byte	0x6
	.byte	0
	.uleb128 0x1f
	.string	"sum"
	.byte	0x1
	.byte	0xb
	.byte	0x7
	.long	0xa8
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xc
	.long	.LASF64
	.byte	0xb
	.byte	0x11
	.long	0xa8
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x8
	.long	.LASF65
	.byte	0xd
	.byte	0xf
	.long	0x2eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x20
	.string	"j"
	.byte	0x1
	.byte	0xe
	.byte	0x9
	.long	0x68
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 12
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x17
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF32:
	.string	"_old_offset"
.LASF66:
	.string	"GNU C17 11.3.0 -m32 -mtune=generic -march=i686 -g -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection"
.LASF67:
	.string	"_IO_FILE"
.LASF27:
	.string	"_IO_save_end"
.LASF8:
	.string	"short int"
.LASF9:
	.string	"size_t"
.LASF37:
	.string	"_offset"
.LASF21:
	.string	"_IO_write_ptr"
.LASF16:
	.string	"_flags"
.LASF23:
	.string	"_IO_buf_base"
.LASF36:
	.string	"_lock"
.LASF51:
	.string	"__align"
.LASF28:
	.string	"_markers"
.LASF18:
	.string	"_IO_read_end"
.LASF41:
	.string	"_freeres_buf"
.LASF53:
	.string	"uintptr_t"
.LASF62:
	.string	"hilos"
.LASF45:
	.string	"FILE"
.LASF11:
	.string	"long long int"
.LASF57:
	.string	"pthread_join"
.LASF58:
	.string	"pthread_create"
.LASF14:
	.string	"long int"
.LASF10:
	.string	"__int64_t"
.LASF64:
	.string	"philo"
.LASF33:
	.string	"_cur_column"
.LASF56:
	.string	"fprintf"
.LASF59:
	.string	"atoi"
.LASF61:
	.string	"argv"
.LASF4:
	.string	"unsigned char"
.LASF60:
	.string	"argc"
.LASF7:
	.string	"signed char"
.LASF38:
	.string	"_codecvt"
.LASF12:
	.string	"long long unsigned int"
.LASF2:
	.string	"unsigned int"
.LASF46:
	.string	"_IO_marker"
.LASF35:
	.string	"_shortbuf"
.LASF20:
	.string	"_IO_write_base"
.LASF44:
	.string	"_unused2"
.LASF17:
	.string	"_IO_read_ptr"
.LASF50:
	.string	"__size"
.LASF24:
	.string	"_IO_buf_end"
.LASF3:
	.string	"char"
.LASF69:
	.string	"main"
.LASF39:
	.string	"_wide_data"
.LASF40:
	.string	"_freeres_list"
.LASF63:
	.string	"indice_creacionHilos"
.LASF42:
	.string	"__pad5"
.LASF5:
	.string	"short unsigned int"
.LASF65:
	.string	"hilo"
.LASF6:
	.string	"long unsigned int"
.LASF22:
	.string	"_IO_write_end"
.LASF15:
	.string	"__off64_t"
.LASF30:
	.string	"_fileno"
.LASF29:
	.string	"_chain"
.LASF48:
	.string	"_IO_wide_data"
.LASF43:
	.string	"_mode"
.LASF13:
	.string	"__off_t"
.LASF26:
	.string	"_IO_backup_base"
.LASF31:
	.string	"_flags2"
.LASF47:
	.string	"_IO_codecvt"
.LASF19:
	.string	"_IO_read_base"
.LASF34:
	.string	"_vtable_offset"
.LASF25:
	.string	"_IO_save_base"
.LASF55:
	.string	"suma"
.LASF52:
	.string	"pthread_attr_t"
.LASF49:
	.string	"pthread_t"
.LASF54:
	.string	"stdout"
.LASF68:
	.string	"_IO_lock_t"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/ssoo/EnlaceSSOO/opcionales/1"
.LASF0:
	.string	"programa_2.c"
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
