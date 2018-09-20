	.global _start
	.align
_start:
	// SVCモードのスタックポインタ設定
	// IRQ,FIQ disable, Thumb disable, SVC mode 
	//mov	r0, =0x000000d3
	//msr	cpsr, r0
	ldr	sp, =0x40000000

	//cpsrの上位27bitをクリアしてモード比較を行う
	mrs	r0, cpsr
	ldr	r1, =0xffffffe0
	bic	r0, r0, r1;
	
	//ユーザモード
	ldr	r1, =0x00000010
	tst	r0, r1
	beq	main

	//FIQモード
	ldr	r1, =0x00000011
	tst	r0, r1
	beq 	main

	//IRQモード
	ldr	r1, =0x00000012
	tst	r0, r1
	beq	main

	//スーパバイザモード
	ldr	r1, =0x00000013
	tst	r0, r1
	beq	main

	//アボートモード
	ldr	r1, =0x00000017
	tst	r0, r1
	beq	main

	//未定義モード
	ldr	r1, =0x0000001b
	tst	r0, r1
	beq	main

	//システムモード
	ldr	r1, =0x0000001f
	tst	r0, r1
	beq	main

	//モニタモード
	ldr	r1, =0x00000016
	tst	r0, r1
	beq	main

	//ハイパーバイザモード
	ldr	r1, =0x0000001a
	tst	r0, r1
	beq	main

	bne	main
	// 終了（無限ループ）
	b .
