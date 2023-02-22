	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls

 # -G value = 0, Arch = mips32, ISA = 32
 # GNU C17 (Ubuntu 10.3.0-1ubuntu1) version 10.3.0 (mips-linux-gnu)
 #	compiled by GNU C version 10.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.0, isl version isl-0.24-GMP

 # warning: MPC header version 1.2.0 differs from library version 1.2.1.
 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed:  -imultiarch mips-linux-gnu programa_2.c -meb -mips32
 # -mfpxx -mllsc -mno-lxc1-sxc1 -mno-shared -mabi=32 -g -O0 -fverbose-asm
 # -fstack-protector-strong -Wformat -Wformat-security
 # options enabled:  -faggressive-loop-optimizations -fallocation-dce
 # -fauto-inc-dec -fdelete-null-pointer-checks -fdwarf2-cfi-asm
 # -fearly-inlining -feliminate-unused-debug-symbols
 # -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
 # -fgcse-lm -fgnu-unique -fident -finline-atomics -fipa-stack-alignment
 # -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
 # -fivopts -fkeep-static-consts -fleading-underscore -flifetime-dse
 # -fmath-errno -fmerge-debug-strings -fpcc-struct-return -fpeephole -fpic
 # -fplt -fprefetch-loop-arrays -fsched-critical-path-heuristic
 # -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
 # -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
 # -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
 # -fsemantic-interposition -fshow-column -fshrink-wrap-separate
 # -fsigned-zeros -fsplit-ivs-in-unroller -fssa-backprop
 # -fstack-protector-strong -fstdarg-opt -fstrict-volatile-bitfields
 # -fsync-libcalls -ftrapping-math -ftree-cselim -ftree-forwprop
 # -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
 # -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
 # -ftree-reassoc -ftree-scev-cprop -funit-at-a-time -fverbose-asm
 # -fzero-initialized-in-bss -mabicalls -mcheck-zero-division
 # -mdivide-traps -mdouble-float -meb -mexplicit-relocs -mextern-sdata
 # -mfp-exceptions -mfp32 -mfpxx -mglibc -mgp32 -mgpopt -mhard-float
 # -mimadd -mllsc -mload-store-pairs -mlocal-sdata -mlong32 -mlra -mmadd4
 # -mno-mdmx -mno-mips16 -mno-mips3d -mrelax-pic-calls -msplit-addresses

	.text
$Ltext0:
	.cfi_sections	.debug_frame
	.globl	suma
	.section	.bss,"aw",@nobits
	.align	2
	.type	suma, @object
	.size	suma, 4
suma:
	.space	4
	.globl	M
	.align	2
	.type	M, @object
	.size	M, 4
M:
	.space	4
	.globl	T
	.align	2
	.type	T, @object
	.size	T, 4
T:
	.space	4
	.text
	.align	2
	.globl	sum
$LFB6 = .
	.file 1 "programa_2.c"
	.loc 1 12 1
	.cfi_startproc
	.set	nomips16
	.set	nomicromips
	.ent	sum
	.type	sum, @function
sum:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16	 #,,
	.cfi_def_cfa_offset 16
	sw	$fp,12($sp)	 #,
	.cfi_offset 30, -4
	move	$fp,$sp	 #,
	.cfi_def_cfa_register 30
	sw	$4,16($fp)	 # philo, philo
 # programa_2.c:13:     uintptr_t hilo = (uintptr_t) philo;
	.loc 1 13 15
	lw	$2,16($fp)		 # tmp199, philo
	sw	$2,4($fp)	 # tmp199, hilo
 # programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 12
	lw	$2,4($fp)		 # tmp200, hilo
	sw	$2,0($fp)	 # tmp200, j
 # programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 5
	.option	pic0
	b	$L2
	nop
	 #
	.option	pic2
$L3:
 # programa_2.c:17:         suma = suma + j;
	.loc 1 17 21 discriminator 3
	lui	$2,%hi(suma)	 # tmp201,
	lw	$3,%lo(suma)($2)		 # suma.0_1, suma
	lw	$2,0($fp)		 # tmp202, j
	addu	$3,$3,$2	 # _2, suma.0_1, tmp202
 # programa_2.c:17:         suma = suma + j;
	.loc 1 17 14 discriminator 3
	lui	$2,%hi(suma)	 # tmp203,
	sw	$3,%lo(suma)($2)	 # _2, suma
 # programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 30 discriminator 3
	lui	$2,%hi(T)	 # tmp204,
	lw	$2,%lo(T)($2)		 # T.1_3, T
	lw	$3,0($fp)		 # tmp206, j
	addu	$2,$3,$2	 # tmp205, tmp206, T.1_3
	sw	$2,0($fp)	 # tmp205, j
$L2:
 # programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 22 discriminator 1
	lui	$2,%hi(M)	 # tmp207,
	lw	$2,%lo(M)($2)		 # M.2_4, M
 # programa_2.c:15:     for (j = hilo; j <= M; j += T)
	.loc 1 15 5 discriminator 1
	lw	$3,0($fp)		 # tmp208, j
	slt	$2,$2,$3	 # tmp209, M.2_4, tmp208
	beq	$2,$0,$L3
	nop
	 #, tmp209,,
 # programa_2.c:19: }
	.loc 1 19 1
	nop	
	move	$sp,$fp	 #,
	.cfi_def_cfa_register 29
	lw	$fp,12($sp)		 #,
	addiu	$sp,$sp,16	 #,,
	.cfi_restore 30
	.cfi_def_cfa_offset 0
	jr	$31
	nop
	 #
	.set	macro
	.set	reorder
	.end	sum
	.cfi_endproc
$LFE6:
	.size	sum, .-sum
	.rdata
	.align	2
$LC0:
	.ascii	"OK\000"
	.align	2
$LC1:
	.ascii	"Error\000"
	.align	2
$LC2:
	.ascii	"%d,%d,%d,%d,[%s]\012\000"
	.text
	.align	2
	.globl	main
$LFB7 = .
	.loc 1 22 1
	.cfi_startproc
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,112,$31		# vars= 32, regs= 10/0, args= 32, gp= 8
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-112	 #,,
	.cfi_def_cfa_offset 112
	sw	$31,108($sp)	 #,
	sw	$fp,104($sp)	 #,
	sw	$23,100($sp)	 #,
	sw	$22,96($sp)	 #,
	sw	$21,92($sp)	 #,
	sw	$20,88($sp)	 #,
	sw	$19,84($sp)	 #,
	sw	$18,80($sp)	 #,
	sw	$17,76($sp)	 #,
	sw	$16,72($sp)	 #,
	.cfi_offset 31, -4
	.cfi_offset 30, -8
	.cfi_offset 23, -12
	.cfi_offset 22, -16
	.cfi_offset 21, -20
	.cfi_offset 20, -24
	.cfi_offset 19, -28
	.cfi_offset 18, -32
	.cfi_offset 17, -36
	.cfi_offset 16, -40
	move	$fp,$sp	 #,
	.cfi_def_cfa_register 30
	lui	$28,%hi(__gnu_local_gp)	 #,
	addiu	$28,$28,%lo(__gnu_local_gp)	 #,,
	.cprestore	32	 #
	sw	$4,112($fp)	 # argc, argc
	sw	$5,44($fp)	 # argv, argv
 # programa_2.c:22: {
	.loc 1 22 1
	lw	$2,%got(__stack_chk_guard)($28)	 # tmp238,,
	lw	$2,0($2)		 # tmp239, __stack_chk_guard
	sw	$2,68($fp)	 # tmp239, D.2916
	move	$2,$sp	 # tmp240,
	sw	$2,40($fp)	 # tmp240, %sfp
 # programa_2.c:23:     if (argc < 3)
	.loc 1 23 8
	lw	$2,112($fp)		 # tmp241, argc
	slt	$2,$2,3	 # tmp242, tmp241,
	beq	$2,$0,$L5
	nop
	 #, tmp242,,
 # programa_2.c:24:     { return (-1); }
	.loc 1 24 14
	li	$2,-1			# 0xffffffffffffffff	 # _13,
	.option	pic0
	b	$L6
	nop
	 #
	.option	pic2
$L5:
 # programa_2.c:25:     M = atoi(argv[1]);
	.loc 1 25 18
	lw	$2,44($fp)		 # tmp243, argv
	addiu	$2,$2,4	 # _1, tmp243,
 # programa_2.c:25:     M = atoi(argv[1]);
	.loc 1 25 9
	lw	$2,0($2)		 # _2, *_1
	move	$4,$2	 #, _2
	lw	$2,%call16(atoi)($28)	 # tmp244,,
	move	$25,$2	 # tmp244, tmp244
	.reloc	1f,R_MIPS_JALR,atoi	 #
1:	jalr	$25
	nop
	 # tmp244
$LVL0 = .
	lw	$28,32($fp)		 #,
	move	$3,$2	 # _3,
 # programa_2.c:25:     M = atoi(argv[1]);
	.loc 1 25 7
	lui	$2,%hi(M)	 # tmp245,
	sw	$3,%lo(M)($2)	 # _3, M
 # programa_2.c:26:     T = atoi(argv[2]);
	.loc 1 26 18
	lw	$2,44($fp)		 # tmp246, argv
	addiu	$2,$2,8	 # _4, tmp246,
 # programa_2.c:26:     T = atoi(argv[2]);
	.loc 1 26 9
	lw	$2,0($2)		 # _5, *_4
	move	$4,$2	 #, _5
	lw	$2,%call16(atoi)($28)	 # tmp247,,
	move	$25,$2	 # tmp247, tmp247
	.reloc	1f,R_MIPS_JALR,atoi	 #
1:	jalr	$25
	nop
	 # tmp247
$LVL1 = .
	lw	$28,32($fp)		 #,
	move	$3,$2	 # _6,
 # programa_2.c:26:     T = atoi(argv[2]);
	.loc 1 26 7
	lui	$2,%hi(T)	 # tmp248,
	sw	$3,%lo(T)($2)	 # _6, T
 # programa_2.c:27:     pthread_t hilos[T];
	.loc 1 27 5
	lui	$2,%hi(T)	 # tmp249,
	lw	$2,%lo(T)($2)		 # T.3_50, T
 # programa_2.c:27:     pthread_t hilos[T];
	.loc 1 27 15
	addiu	$3,$2,-1	 # _7, T.3_50,
	sw	$3,60($fp)	 # _7, D.2901
	move	$3,$2	 # T.4_9, T.3_50
	move	$23,$3	 # _10, T.4_9
	move	$22,$0	 # _10,
	srl	$3,$23,27	 # tmp250, _10,
	sll	$18,$22,5	 # _52, _10,
	or	$18,$3,$18	 # _52, tmp250, _52
	sll	$19,$23,5	 # _52, _10,
	move	$3,$2	 # T.6_14, T.3_50
	move	$21,$3	 # _15, T.6_14
	move	$20,$0	 # _15,
	srl	$3,$21,27	 # tmp251, _15,
	sll	$16,$20,5	 # _54, _15,
	or	$16,$3,$16	 # _54, tmp251, _54
	sll	$17,$21,5	 # _54, _15,
	sll	$2,$2,2	 # _55, T.7_17,
	addiu	$2,$2,7	 # tmp252, _55,
	srl	$2,$2,3	 # tmp253, tmp252,
	sll	$2,$2,3	 # tmp254, tmp253,
	subu	$sp,$sp,$2	 #,, tmp254
	addiu	$2,$sp,32	 # tmp255,,
	addiu	$2,$2,3	 # tmp256, tmp255,
	srl	$2,$2,2	 # tmp257, tmp256,
	sll	$2,$2,2	 # tmp258, tmp257,
	sw	$2,64($fp)	 # tmp258, hilos.8
$LBB2 = .
 # programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 20
	sw	$0,56($fp)	 #, indice_creacionHilos
 # programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 5
	.option	pic0
	b	$L7
	nop
	 #
	.option	pic2
$L8:
 # programa_2.c:30:         pthread_create(&hilos[indice_creacionHilos], NULL, &sum, (void *) indice_creacionHilos);
	.loc 1 30 9 discriminator 3
	lw	$2,56($fp)		 # tmp260, indice_creacionHilos
	sll	$2,$2,2	 # tmp259, tmp260,
	lw	$3,64($fp)		 # tmp261, hilos.8
	addu	$3,$3,$2	 # _19, tmp261, tmp259
	lw	$2,56($fp)		 # indice_creacionHilos.9_20, indice_creacionHilos
	move	$7,$2	 #, indice_creacionHilos.9_20
	lui	$2,%hi(sum)	 # tmp262,
	addiu	$6,$2,%lo(sum)	 #, tmp262,
	move	$5,$0	 #,
	move	$4,$3	 #, _19
	lw	$2,%call16(pthread_create)($28)	 # tmp263,,
	move	$25,$2	 # tmp263, tmp263
	.reloc	1f,R_MIPS_JALR,pthread_create	 #
1:	jalr	$25
	nop
	 # tmp263
$LVL2 = .
	lw	$28,32($fp)		 #,
 # programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 92 discriminator 3
	lw	$2,56($fp)		 # tmp265, indice_creacionHilos
	addiu	$2,$2,1	 # tmp264, tmp265,
	sw	$2,56($fp)	 # tmp264, indice_creacionHilos
$L7:
 # programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 67 discriminator 1
	lui	$2,%hi(T)	 # tmp266,
	lw	$2,%lo(T)($2)		 # T.10_21, T
	move	$3,$2	 # T.11_22, T.10_21
 # programa_2.c:28:     for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 28 5 discriminator 1
	lw	$2,56($fp)		 # tmp267, indice_creacionHilos
	sltu	$2,$2,$3	 # tmp268, tmp267, T.11_22
	bne	$2,$0,$L8
	nop
	 #, tmp268,,
$LBE2 = .
$LBB3 = .
 # programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 14
	sw	$0,52($fp)	 #, indice_creacionHilos
 # programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 5
	.option	pic0
	b	$L9
	nop
	 #
	.option	pic2
$L10:
 # programa_2.c:35:         pthread_join(hilos[indice_creacionHilos], NULL);
	.loc 1 35 9 discriminator 3
	lw	$3,64($fp)		 # tmp269, hilos.8
	lw	$2,52($fp)		 # tmp270, indice_creacionHilos
	sll	$2,$2,2	 # tmp271, tmp270,
	addu	$2,$3,$2	 # tmp272, tmp269, tmp271
	lw	$2,0($2)		 # _23, (*hilos.8_57)[indice_creacionHilos_16]
	move	$5,$0	 #,
	move	$4,$2	 #, _23
	lw	$2,%call16(pthread_join)($28)	 # tmp273,,
	move	$25,$2	 # tmp273, tmp273
	.reloc	1f,R_MIPS_JALR,pthread_join	 #
1:	jalr	$25
	nop
	 # tmp273
$LVL3 = .
	lw	$28,32($fp)		 #,
 # programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 86 discriminator 3
	lw	$2,52($fp)		 # tmp275, indice_creacionHilos
	addiu	$2,$2,1	 # tmp274, tmp275,
	sw	$2,52($fp)	 # tmp274, indice_creacionHilos
$L9:
 # programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 61 discriminator 1
	lui	$2,%hi(T)	 # tmp276,
	lw	$2,%lo(T)($2)		 # T.12_24, T
 # programa_2.c:33:     for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
	.loc 1 33 5 discriminator 1
	lw	$3,52($fp)		 # tmp277, indice_creacionHilos
	slt	$2,$3,$2	 # tmp278, tmp277, T.12_24
	bne	$2,$0,$L10
	nop
	 #, tmp278,,
$LBE3 = .
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5
	lw	$2,%got(stdout)($28)	 # tmp279,,
	lw	$8,0($2)		 # stdout.13_25, stdout
	lui	$2,%hi(M)	 # tmp280,
	lw	$5,%lo(M)($2)		 # M.14_26, M
	lui	$2,%hi(T)	 # tmp281,
	lw	$6,%lo(T)($2)		 # T.15_27, T
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 57
	lui	$2,%hi(M)	 # tmp282,
	lw	$2,%lo(M)($2)		 # M.16_28, M
	addiu	$3,$2,1	 # _29, M.16_28,
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 52
	lui	$2,%hi(M)	 # tmp283,
	lw	$2,%lo(M)($2)		 # M.17_30, M
	mul	$2,$3,$2	 # _31, _29, M.17_30
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5
	srl	$3,$2,31	 # tmp284, _31,
	addu	$2,$3,$2	 # tmp285, tmp284, _31
	sra	$2,$2,1	 # tmp286, tmp285,
	move	$7,$2	 # _32, tmp286
	lui	$2,%hi(suma)	 # tmp287,
	lw	$3,%lo(suma)($2)		 # suma.18_33, suma
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 90
	lui	$2,%hi(M)	 # tmp288,
	lw	$2,%lo(M)($2)		 # M.20_34, M
	addiu	$4,$2,1	 # _35, M.20_34,
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 85
	lui	$2,%hi(M)	 # tmp289,
	lw	$2,%lo(M)($2)		 # M.21_36, M
	mul	$2,$4,$2	 # _37, _35, M.21_36
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 96
	srl	$4,$2,31	 # tmp290, _37,
	addu	$2,$4,$2	 # tmp291, tmp290, _37
	sra	$2,$2,1	 # tmp292, tmp291,
	subu	$2,$0,$2	 # tmp292, tmp292
	move	$4,$2	 # _38, tmp292
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 80
	lui	$2,%hi(suma)	 # tmp293,
	lw	$2,%lo(suma)($2)		 # suma.22_39, suma
	addu	$2,$4,$2	 # _40, _38, suma.22_39
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5
	bne	$2,$0,$L11
	nop
	 #, _40,,
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5 is_stmt 0 discriminator 1
	lui	$2,%hi($LC0)	 # tmp294,
	addiu	$2,$2,%lo($LC0)	 # iftmp.19_11, tmp294,
	.option	pic0
	b	$L12
	nop
	 #
	.option	pic2
$L11:
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5 discriminator 2
	lui	$2,%hi($LC1)	 # tmp295,
	addiu	$2,$2,%lo($LC1)	 # iftmp.19_11, tmp295,
$L12:
 # programa_2.c:39:     fprintf(stdout, "%d,%d,%d,%d,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
	.loc 1 39 5 discriminator 4
	sw	$2,24($sp)	 # iftmp.19_11,
	sw	$3,20($sp)	 # suma.18_33,
	sw	$7,16($sp)	 # _32,
	move	$7,$6	 #, T.15_27
	move	$6,$5	 #, M.14_26
	lui	$2,%hi($LC2)	 # tmp296,
	addiu	$5,$2,%lo($LC2)	 #, tmp296,
	move	$4,$8	 #, stdout.13_25
	lw	$2,%call16(fprintf)($28)	 # tmp297,,
	move	$25,$2	 # tmp297, tmp297
	.reloc	1f,R_MIPS_JALR,fprintf	 #
1:	jalr	$25
	nop
	 # tmp297
$LVL4 = .
	lw	$28,32($fp)		 #,
 # programa_2.c:40:     return (0);
	.loc 1 40 12 is_stmt 1 discriminator 4
	move	$2,$0	 # _13,
$L6:
	lw	$sp,40($fp)		 #, %sfp
 # programa_2.c:41: }
	.loc 1 41 1
	move	$4,$2	 # <retval>, _13
	lw	$2,%got(__stack_chk_guard)($28)	 # tmp299,,
	lw	$3,68($fp)		 # tmp300, D.2916
	lw	$2,0($2)		 # tmp301, __stack_chk_guard
	beq	$3,$2,$L14
	nop
	 #, tmp300, tmp301,
	lw	$2,%call16(__stack_chk_fail)($28)	 # tmp302,,
	move	$25,$2	 # tmp302, tmp302
	.reloc	1f,R_MIPS_JALR,__stack_chk_fail	 #
1:	jalr	$25
	nop
	 # tmp302
$LVL5 = .
$L14:
	move	$2,$4	 #, <retval>
	move	$sp,$fp	 #,
	.cfi_def_cfa_register 29
	lw	$31,108($sp)		 #,
	lw	$fp,104($sp)		 #,
	lw	$23,100($sp)		 #,
	lw	$22,96($sp)		 #,
	lw	$21,92($sp)		 #,
	lw	$20,88($sp)		 #,
	lw	$19,84($sp)		 #,
	lw	$18,80($sp)		 #,
	lw	$17,76($sp)		 #,
	lw	$16,72($sp)		 #,
	addiu	$sp,$sp,112	 #,,
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 23
	.cfi_restore 30
	.cfi_restore 31
	.cfi_def_cfa_offset 0
	jr	$31
	nop
	 #
	.set	macro
	.set	reorder
	.end	main
	.cfi_endproc
$LFE7:
	.size	main, .-main
$Letext0:
	.file 2 "/usr/lib/gcc-cross/mips-linux-gnu/10/include/stddef.h"
	.file 3 "/usr/mips-linux-gnu/include/bits/types.h"
	.file 4 "/usr/mips-linux-gnu/include/bits/types/struct_FILE.h"
	.file 5 "/usr/mips-linux-gnu/include/bits/types/FILE.h"
	.file 6 "/usr/mips-linux-gnu/include/bits/pthreadtypes.h"
	.file 7 "/usr/mips-linux-gnu/include/stdint.h"
	.file 8 "/usr/mips-linux-gnu/include/stdio.h"
	.section	.debug_info,"",@progbits
$Ldebug_info0:
	.4byte	0x3cd
	.2byte	0x4
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$LASF58
	.byte	0xc
	.4byte	$LASF59
	.4byte	$LASF60
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	$Ldebug_line0
	.uleb128 0x2
	.4byte	$LASF6
	.byte	0x2
	.byte	0xd1
	.byte	0x17
	.4byte	0x31
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	$LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	$LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	$LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	$LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	$LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	$LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.4byte	$LASF7
	.byte	0x3
	.byte	0x2f
	.byte	0x2c
	.4byte	0x6e
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	$LASF8
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	$LASF9
	.uleb128 0x2
	.4byte	$LASF10
	.byte	0x3
	.byte	0x98
	.byte	0x19
	.4byte	0x88
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	$LASF11
	.uleb128 0x2
	.4byte	$LASF12
	.byte	0x3
	.byte	0x99
	.byte	0x1b
	.4byte	0x62
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x6
	.byte	0x4
	.4byte	0xa3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	$LASF13
	.uleb128 0x7
	.4byte	$LASF61
	.byte	0x98
	.byte	0x4
	.byte	0x31
	.byte	0x8
	.4byte	0x231
	.uleb128 0x8
	.4byte	$LASF14
	.byte	0x4
	.byte	0x33
	.byte	0x7
	.4byte	0x5b
	.byte	0
	.uleb128 0x8
	.4byte	$LASF15
	.byte	0x4
	.byte	0x36
	.byte	0x9
	.4byte	0x9d
	.byte	0x4
	.uleb128 0x8
	.4byte	$LASF16
	.byte	0x4
	.byte	0x37
	.byte	0x9
	.4byte	0x9d
	.byte	0x8
	.uleb128 0x8
	.4byte	$LASF17
	.byte	0x4
	.byte	0x38
	.byte	0x9
	.4byte	0x9d
	.byte	0xc
	.uleb128 0x8
	.4byte	$LASF18
	.byte	0x4
	.byte	0x39
	.byte	0x9
	.4byte	0x9d
	.byte	0x10
	.uleb128 0x8
	.4byte	$LASF19
	.byte	0x4
	.byte	0x3a
	.byte	0x9
	.4byte	0x9d
	.byte	0x14
	.uleb128 0x8
	.4byte	$LASF20
	.byte	0x4
	.byte	0x3b
	.byte	0x9
	.4byte	0x9d
	.byte	0x18
	.uleb128 0x8
	.4byte	$LASF21
	.byte	0x4
	.byte	0x3c
	.byte	0x9
	.4byte	0x9d
	.byte	0x1c
	.uleb128 0x8
	.4byte	$LASF22
	.byte	0x4
	.byte	0x3d
	.byte	0x9
	.4byte	0x9d
	.byte	0x20
	.uleb128 0x8
	.4byte	$LASF23
	.byte	0x4
	.byte	0x40
	.byte	0x9
	.4byte	0x9d
	.byte	0x24
	.uleb128 0x8
	.4byte	$LASF24
	.byte	0x4
	.byte	0x41
	.byte	0x9
	.4byte	0x9d
	.byte	0x28
	.uleb128 0x8
	.4byte	$LASF25
	.byte	0x4
	.byte	0x42
	.byte	0x9
	.4byte	0x9d
	.byte	0x2c
	.uleb128 0x8
	.4byte	$LASF26
	.byte	0x4
	.byte	0x44
	.byte	0x16
	.4byte	0x24a
	.byte	0x30
	.uleb128 0x8
	.4byte	$LASF27
	.byte	0x4
	.byte	0x46
	.byte	0x14
	.4byte	0x250
	.byte	0x34
	.uleb128 0x8
	.4byte	$LASF28
	.byte	0x4
	.byte	0x48
	.byte	0x7
	.4byte	0x5b
	.byte	0x38
	.uleb128 0x8
	.4byte	$LASF29
	.byte	0x4
	.byte	0x49
	.byte	0x7
	.4byte	0x5b
	.byte	0x3c
	.uleb128 0x8
	.4byte	$LASF30
	.byte	0x4
	.byte	0x4a
	.byte	0xb
	.4byte	0x7c
	.byte	0x40
	.uleb128 0x8
	.4byte	$LASF31
	.byte	0x4
	.byte	0x4d
	.byte	0x12
	.4byte	0x3f
	.byte	0x44
	.uleb128 0x8
	.4byte	$LASF32
	.byte	0x4
	.byte	0x4e
	.byte	0xf
	.4byte	0x4d
	.byte	0x46
	.uleb128 0x8
	.4byte	$LASF33
	.byte	0x4
	.byte	0x4f
	.byte	0x8
	.4byte	0x256
	.byte	0x47
	.uleb128 0x8
	.4byte	$LASF34
	.byte	0x4
	.byte	0x51
	.byte	0xf
	.4byte	0x266
	.byte	0x48
	.uleb128 0x8
	.4byte	$LASF35
	.byte	0x4
	.byte	0x59
	.byte	0xd
	.4byte	0x8f
	.byte	0x50
	.uleb128 0x8
	.4byte	$LASF36
	.byte	0x4
	.byte	0x5b
	.byte	0x17
	.4byte	0x271
	.byte	0x58
	.uleb128 0x8
	.4byte	$LASF37
	.byte	0x4
	.byte	0x5c
	.byte	0x19
	.4byte	0x27c
	.byte	0x5c
	.uleb128 0x8
	.4byte	$LASF38
	.byte	0x4
	.byte	0x5d
	.byte	0x14
	.4byte	0x250
	.byte	0x60
	.uleb128 0x8
	.4byte	$LASF39
	.byte	0x4
	.byte	0x5e
	.byte	0x9
	.4byte	0x9b
	.byte	0x64
	.uleb128 0x8
	.4byte	$LASF40
	.byte	0x4
	.byte	0x5f
	.byte	0xa
	.4byte	0x25
	.byte	0x68
	.uleb128 0x8
	.4byte	$LASF41
	.byte	0x4
	.byte	0x60
	.byte	0x7
	.4byte	0x5b
	.byte	0x6c
	.uleb128 0x8
	.4byte	$LASF42
	.byte	0x4
	.byte	0x62
	.byte	0x8
	.4byte	0x282
	.byte	0x70
	.byte	0
	.uleb128 0x2
	.4byte	$LASF43
	.byte	0x5
	.byte	0x7
	.byte	0x19
	.4byte	0xaa
	.uleb128 0x9
	.4byte	$LASF62
	.byte	0x4
	.byte	0x2b
	.byte	0xe
	.uleb128 0xa
	.4byte	$LASF44
	.uleb128 0x6
	.byte	0x4
	.4byte	0x245
	.uleb128 0x6
	.byte	0x4
	.4byte	0xaa
	.uleb128 0xb
	.4byte	0xa3
	.4byte	0x266
	.uleb128 0xc
	.4byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x23d
	.uleb128 0xa
	.4byte	$LASF45
	.uleb128 0x6
	.byte	0x4
	.4byte	0x26c
	.uleb128 0xa
	.4byte	$LASF46
	.uleb128 0x6
	.byte	0x4
	.4byte	0x277
	.uleb128 0xb
	.4byte	0xa3
	.4byte	0x292
	.uleb128 0xc
	.4byte	0x31
	.byte	0x27
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x231
	.uleb128 0xd
	.4byte	$LASF50
	.byte	0x8
	.byte	0x90
	.byte	0xe
	.4byte	0x292
	.uleb128 0x2
	.4byte	$LASF47
	.byte	0x6
	.byte	0x1b
	.byte	0x1b
	.4byte	0x46
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	$LASF48
	.uleb128 0x2
	.4byte	$LASF49
	.byte	0x7
	.byte	0x60
	.byte	0x17
	.4byte	0x31
	.uleb128 0xe
	.4byte	$LASF51
	.byte	0x1
	.byte	0x8
	.byte	0x5
	.4byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	suma
	.uleb128 0xf
	.ascii	"M\000"
	.byte	0x1
	.byte	0x9
	.byte	0x5
	.4byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	M
	.uleb128 0xf
	.ascii	"T\000"
	.byte	0x1
	.byte	0x9
	.byte	0x8
	.4byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	T
	.uleb128 0x10
	.4byte	$LASF63
	.byte	0x1
	.byte	0x15
	.byte	0x5
	.4byte	0x5b
	.4byte	$LFB7
	.4byte	$LFE7-$LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x375
	.uleb128 0x11
	.4byte	$LASF52
	.byte	0x1
	.byte	0x15
	.byte	0xe
	.4byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x11
	.4byte	$LASF53
	.byte	0x1
	.byte	0x15
	.byte	0x1a
	.4byte	0x375
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x12
	.4byte	$LASF54
	.byte	0x1
	.byte	0x1b
	.byte	0xf
	.4byte	0x37b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x6
	.uleb128 0x13
	.4byte	$LBB2
	.4byte	$LBE2-$LBB2
	.4byte	0x35b
	.uleb128 0x12
	.4byte	$LASF55
	.byte	0x1
	.byte	0x1c
	.byte	0x14
	.4byte	0x2b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.uleb128 0x14
	.4byte	$LBB3
	.4byte	$LBE3-$LBB3
	.uleb128 0x12
	.4byte	$LASF55
	.byte	0x1
	.byte	0x21
	.byte	0xe
	.4byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x9d
	.uleb128 0xb
	.4byte	0x2a4
	.4byte	0x38e
	.uleb128 0x15
	.4byte	0x31
	.uleb128 0x3
	.byte	0x91
	.sleb128 -52
	.byte	0x6
	.byte	0
	.uleb128 0x16
	.ascii	"sum\000"
	.byte	0x1
	.byte	0xb
	.byte	0x7
	.4byte	0x9b
	.4byte	$LFB6
	.4byte	$LFE6-$LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x11
	.4byte	$LASF56
	.byte	0x1
	.byte	0xb
	.byte	0x11
	.4byte	0x9b
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x12
	.4byte	$LASF57
	.byte	0x1
	.byte	0xd
	.byte	0xf
	.4byte	0x2b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x17
	.ascii	"j\000"
	.byte	0x1
	.byte	0xe
	.byte	0x9
	.4byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
$Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
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
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0xd
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
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.4byte	0x1c
	.2byte	0x2
	.4byte	$Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
$Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
$LASF30:
	.ascii	"_old_offset\000"
$LASF48:
	.ascii	"double\000"
$LASF61:
	.ascii	"_IO_FILE\000"
$LASF25:
	.ascii	"_IO_save_end\000"
$LASF60:
	.ascii	"/home/ssoo/EnlaceSSOO/opcionales/1\000"
$LASF5:
	.ascii	"short int\000"
$LASF6:
	.ascii	"size_t\000"
$LASF35:
	.ascii	"_offset\000"
$LASF19:
	.ascii	"_IO_write_ptr\000"
$LASF14:
	.ascii	"_flags\000"
$LASF21:
	.ascii	"_IO_buf_base\000"
$LASF26:
	.ascii	"_markers\000"
$LASF16:
	.ascii	"_IO_read_end\000"
$LASF39:
	.ascii	"_freeres_buf\000"
$LASF49:
	.ascii	"uintptr_t\000"
$LASF54:
	.ascii	"hilos\000"
$LASF43:
	.ascii	"FILE\000"
$LASF8:
	.ascii	"long long int\000"
$LASF34:
	.ascii	"_lock\000"
$LASF11:
	.ascii	"long int\000"
$LASF7:
	.ascii	"__int64_t\000"
$LASF56:
	.ascii	"philo\000"
$LASF31:
	.ascii	"_cur_column\000"
$LASF53:
	.ascii	"argv\000"
$LASF59:
	.ascii	"programa_2.c\000"
$LASF1:
	.ascii	"unsigned char\000"
$LASF52:
	.ascii	"argc\000"
$LASF4:
	.ascii	"signed char\000"
$LASF36:
	.ascii	"_codecvt\000"
$LASF9:
	.ascii	"long long unsigned int\000"
$LASF0:
	.ascii	"unsigned int\000"
$LASF44:
	.ascii	"_IO_marker\000"
$LASF33:
	.ascii	"_shortbuf\000"
$LASF18:
	.ascii	"_IO_write_base\000"
$LASF42:
	.ascii	"_unused2\000"
$LASF15:
	.ascii	"_IO_read_ptr\000"
$LASF22:
	.ascii	"_IO_buf_end\000"
$LASF13:
	.ascii	"char\000"
$LASF63:
	.ascii	"main\000"
$LASF37:
	.ascii	"_wide_data\000"
$LASF38:
	.ascii	"_freeres_list\000"
$LASF55:
	.ascii	"indice_creacionHilos\000"
$LASF40:
	.ascii	"__pad5\000"
$LASF58:
	.ascii	"GNU C17 10.3.0 -meb -mips32 -mfpxx -mllsc -mno-lxc1-sxc1"
	.ascii	" -mno-shared -mabi=32 -g -O0 -fstack-protector-strong\000"
$LASF57:
	.ascii	"hilo\000"
$LASF3:
	.ascii	"long unsigned int\000"
$LASF20:
	.ascii	"_IO_write_end\000"
$LASF12:
	.ascii	"__off64_t\000"
$LASF28:
	.ascii	"_fileno\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF27:
	.ascii	"_chain\000"
$LASF46:
	.ascii	"_IO_wide_data\000"
$LASF41:
	.ascii	"_mode\000"
$LASF10:
	.ascii	"__off_t\000"
$LASF24:
	.ascii	"_IO_backup_base\000"
$LASF29:
	.ascii	"_flags2\000"
$LASF45:
	.ascii	"_IO_codecvt\000"
$LASF17:
	.ascii	"_IO_read_base\000"
$LASF32:
	.ascii	"_vtable_offset\000"
$LASF23:
	.ascii	"_IO_save_base\000"
$LASF51:
	.ascii	"suma\000"
$LASF47:
	.ascii	"pthread_t\000"
$LASF50:
	.ascii	"stdout\000"
$LASF62:
	.ascii	"_IO_lock_t\000"
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
