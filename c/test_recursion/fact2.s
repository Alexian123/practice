	.text
	.file	"fact2.c"
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4                               # -- Begin function factorial
.LCPI0_0:
	.zero	4
	.long	1                               # 0x1
	.long	1                               # 0x1
	.long	1                               # 0x1
.LCPI0_1:
	.long	0                               # 0x0
	.long	4294967295                      # 0xffffffff
	.long	4294967294                      # 0xfffffffe
	.long	4294967293                      # 0xfffffffd
.LCPI0_2:
	.long	1                               # 0x1
	.long	1                               # 0x1
	.long	1                               # 0x1
	.long	1                               # 0x1
.LCPI0_3:
	.long	4294967292                      # 0xfffffffc
	.long	4294967292                      # 0xfffffffc
	.long	4294967292                      # 0xfffffffc
	.long	4294967292                      # 0xfffffffc
.LCPI0_4:
	.long	4294967288                      # 0xfffffff8
	.long	4294967288                      # 0xfffffff8
	.long	4294967288                      # 0xfffffff8
	.long	4294967288                      # 0xfffffff8
.LCPI0_5:
	.long	4294967284                      # 0xfffffff4
	.long	4294967284                      # 0xfffffff4
	.long	4294967284                      # 0xfffffff4
	.long	4294967284                      # 0xfffffff4
.LCPI0_6:
	.long	4294967280                      # 0xfffffff0
	.long	4294967280                      # 0xfffffff0
	.long	4294967280                      # 0xfffffff0
	.long	4294967280                      # 0xfffffff0
.LCPI0_7:
	.long	4294967276                      # 0xffffffec
	.long	4294967276                      # 0xffffffec
	.long	4294967276                      # 0xffffffec
	.long	4294967276                      # 0xffffffec
.LCPI0_8:
	.long	4294967272                      # 0xffffffe8
	.long	4294967272                      # 0xffffffe8
	.long	4294967272                      # 0xffffffe8
	.long	4294967272                      # 0xffffffe8
.LCPI0_9:
	.long	4294967268                      # 0xffffffe4
	.long	4294967268                      # 0xffffffe4
	.long	4294967268                      # 0xffffffe4
	.long	4294967268                      # 0xffffffe4
.LCPI0_10:
	.long	4294967264                      # 0xffffffe0
	.long	4294967264                      # 0xffffffe0
	.long	4294967264                      # 0xffffffe0
	.long	4294967264                      # 0xffffffe0
	.text
	.globl	factorial
	.p2align	4, 0x90
	.type	factorial,@function
factorial:                              # @factorial
	.cfi_startproc
# %bb.0:
	movl	%esi, %eax
	testl	%edi, %edi
	je	.LBB0_12
# %bb.1:
	cmpl	$8, %edi
	jb	.LBB0_11
# %bb.2:
	movl	%edi, %ecx
	andl	$-8, %ecx
	movd	%eax, %xmm1
	movaps	.LCPI0_0(%rip), %xmm0           # xmm0 = <u,1,1,1>
	movss	%xmm1, %xmm0                    # xmm0 = xmm1[0],xmm0[1,2,3]
	movd	%edi, %xmm1
	pshufd	$0, %xmm1, %xmm6                # xmm6 = xmm1[0,0,0,0]
	paddd	.LCPI0_1(%rip), %xmm6
	leal	-8(%rcx), %esi
	movl	%esi, %edx
	shrl	$3, %edx
	addl	$1, %edx
	movl	%edx, %eax
	andl	$3, %eax
	cmpl	$24, %esi
	jae	.LBB0_4
# %bb.3:
	movdqa	.LCPI0_2(%rip), %xmm2           # xmm2 = [1,1,1,1]
	jmp	.LBB0_6
.LBB0_4:
	andl	$-4, %edx
	movdqa	.LCPI0_2(%rip), %xmm2           # xmm2 = [1,1,1,1]
	movdqa	.LCPI0_4(%rip), %xmm9           # xmm9 = [4294967288,4294967288,4294967288,4294967288]
	movdqa	.LCPI0_5(%rip), %xmm10          # xmm10 = [4294967284,4294967284,4294967284,4294967284]
	movdqa	.LCPI0_6(%rip), %xmm11          # xmm11 = [4294967280,4294967280,4294967280,4294967280]
	movdqa	.LCPI0_7(%rip), %xmm12          # xmm12 = [4294967276,4294967276,4294967276,4294967276]
	movdqa	.LCPI0_8(%rip), %xmm13          # xmm13 = [4294967272,4294967272,4294967272,4294967272]
	movdqa	.LCPI0_9(%rip), %xmm14          # xmm14 = [4294967268,4294967268,4294967268,4294967268]
	movdqa	.LCPI0_10(%rip), %xmm15         # xmm15 = [4294967264,4294967264,4294967264,4294967264]
	.p2align	4, 0x90
.LBB0_5:                                # =>This Inner Loop Header: Depth=1
	movdqa	%xmm6, %xmm1
	paddd	.LCPI0_3(%rip), %xmm1
	pshufd	$245, %xmm6, %xmm7              # xmm7 = xmm6[1,1,3,3]
	pshufd	$245, %xmm0, %xmm3              # xmm3 = xmm0[1,1,3,3]
	pmuludq	%xmm7, %xmm3
	pmuludq	%xmm6, %xmm0
	pshufd	$245, %xmm2, %xmm7              # xmm7 = xmm2[1,1,3,3]
	pshufd	$245, %xmm1, %xmm4              # xmm4 = xmm1[1,1,3,3]
	pmuludq	%xmm7, %xmm4
	pmuludq	%xmm2, %xmm1
	movdqa	%xmm6, %xmm2
	paddd	%xmm9, %xmm2
	movdqa	%xmm6, %xmm7
	paddd	%xmm10, %xmm7
	pmuludq	%xmm2, %xmm0
	pshufd	$245, %xmm2, %xmm2              # xmm2 = xmm2[1,1,3,3]
	pmuludq	%xmm3, %xmm2
	pmuludq	%xmm7, %xmm1
	pshufd	$245, %xmm7, %xmm3              # xmm3 = xmm7[1,1,3,3]
	pmuludq	%xmm4, %xmm3
	movdqa	%xmm6, %xmm4
	paddd	%xmm11, %xmm4
	movdqa	%xmm6, %xmm7
	paddd	%xmm12, %xmm7
	pshufd	$245, %xmm4, %xmm5              # xmm5 = xmm4[1,1,3,3]
	pmuludq	%xmm2, %xmm5
	pmuludq	%xmm0, %xmm4
	pshufd	$245, %xmm7, %xmm8              # xmm8 = xmm7[1,1,3,3]
	pmuludq	%xmm3, %xmm8
	pmuludq	%xmm1, %xmm7
	movdqa	%xmm6, %xmm1
	paddd	%xmm13, %xmm1
	movdqa	%xmm6, %xmm3
	paddd	%xmm14, %xmm3
	pmuludq	%xmm1, %xmm4
	pshufd	$232, %xmm4, %xmm0              # xmm0 = xmm4[0,2,2,3]
	pshufd	$245, %xmm1, %xmm1              # xmm1 = xmm1[1,1,3,3]
	pmuludq	%xmm5, %xmm1
	pshufd	$232, %xmm1, %xmm1              # xmm1 = xmm1[0,2,2,3]
	punpckldq	%xmm1, %xmm0            # xmm0 = xmm0[0],xmm1[0],xmm0[1],xmm1[1]
	pmuludq	%xmm3, %xmm7
	pshufd	$232, %xmm7, %xmm2              # xmm2 = xmm7[0,2,2,3]
	pshufd	$245, %xmm3, %xmm1              # xmm1 = xmm3[1,1,3,3]
	pmuludq	%xmm8, %xmm1
	pshufd	$232, %xmm1, %xmm1              # xmm1 = xmm1[0,2,2,3]
	punpckldq	%xmm1, %xmm2            # xmm2 = xmm2[0],xmm1[0],xmm2[1],xmm1[1]
	paddd	%xmm15, %xmm6
	addl	$-4, %edx
	jne	.LBB0_5
.LBB0_6:
	testl	%eax, %eax
	je	.LBB0_9
# %bb.7:
	movdqa	.LCPI0_3(%rip), %xmm3           # xmm3 = [4294967292,4294967292,4294967292,4294967292]
	movdqa	.LCPI0_4(%rip), %xmm4           # xmm4 = [4294967288,4294967288,4294967288,4294967288]
	.p2align	4, 0x90
.LBB0_8:                                # =>This Inner Loop Header: Depth=1
	movdqa	%xmm6, %xmm1
	paddd	%xmm3, %xmm1
	pshufd	$245, %xmm0, %xmm5              # xmm5 = xmm0[1,1,3,3]
	pmuludq	%xmm6, %xmm0
	pshufd	$232, %xmm0, %xmm0              # xmm0 = xmm0[0,2,2,3]
	pshufd	$245, %xmm6, %xmm7              # xmm7 = xmm6[1,1,3,3]
	pmuludq	%xmm5, %xmm7
	pshufd	$232, %xmm7, %xmm5              # xmm5 = xmm7[0,2,2,3]
	punpckldq	%xmm5, %xmm0            # xmm0 = xmm0[0],xmm5[0],xmm0[1],xmm5[1]
	pshufd	$245, %xmm2, %xmm5              # xmm5 = xmm2[1,1,3,3]
	pmuludq	%xmm1, %xmm2
	pshufd	$232, %xmm2, %xmm2              # xmm2 = xmm2[0,2,2,3]
	pshufd	$245, %xmm1, %xmm1              # xmm1 = xmm1[1,1,3,3]
	pmuludq	%xmm5, %xmm1
	pshufd	$232, %xmm1, %xmm1              # xmm1 = xmm1[0,2,2,3]
	punpckldq	%xmm1, %xmm2            # xmm2 = xmm2[0],xmm1[0],xmm2[1],xmm1[1]
	paddd	%xmm4, %xmm6
	addl	$-1, %eax
	jne	.LBB0_8
.LBB0_9:
	pshufd	$245, %xmm0, %xmm1              # xmm1 = xmm0[1,1,3,3]
	pshufd	$245, %xmm2, %xmm3              # xmm3 = xmm2[1,1,3,3]
	pmuludq	%xmm1, %xmm3
	pmuludq	%xmm0, %xmm2
	pshufd	$238, %xmm2, %xmm0              # xmm0 = xmm2[2,3,2,3]
	pmuludq	%xmm2, %xmm0
	pshufd	$170, %xmm3, %xmm1              # xmm1 = xmm3[2,2,2,2]
	pmuludq	%xmm3, %xmm1
	pmuludq	%xmm0, %xmm1
	movd	%xmm1, %eax
	cmpl	%edi, %ecx
	je	.LBB0_12
# %bb.10:
	andl	$7, %edi
	.p2align	4, 0x90
.LBB0_11:                               # =>This Inner Loop Header: Depth=1
	imull	%edi, %eax
	addl	$-1, %edi
	jne	.LBB0_11
.LBB0_12:
	retq
.Lfunc_end0:
	.size	factorial, .Lfunc_end0-factorial
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
