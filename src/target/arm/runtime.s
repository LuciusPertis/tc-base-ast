# runtime arm
.data
Lmalloc_failure_msg:
  .asciz "malloc: memory exhausted\n"

.extern malloc
.text
tc_malloc:
  push {r1-r10,lr}
  mov r0, r1
  bl malloc
  cmp r0, #0
  beq Lmalloc_failure
  pop {r1-r10,pc}

Lmalloc_failure:
  mov r0, #2
  ldr r1, =Lmalloc_failure_msg
  mov r2, #25
  mov r7, #4
  svc #0

  mov r0, #120
  mov r7, #1
  svc #0

.extern exit
tc_exit:
  push {lr}
  mov r0, r1
  mov r7, #1
  svc #0
  pop {pc}

.text
tc_init_array:
  push {r1-r10, lr}
  mov r4, r1
  mov r5, r2
  lsl r1, r1, #2
  bl tc_malloc

  mov r1, r0
Linit_array_begin:
  str r5, [r1, #0 ]
  sub r4, r4, #1
  add r1, r1, #4
Linit_array_end:
  cmp r4, #0
  bne Linit_array_begin

  pop {r1-r10, pc}

;.extern strcmp
  # FIXME: Some code was deleted here (strcmp).
  # FIXME: Some code was deleted here (streq).
;.extern fputs
.text
;.extern stdout
tc_print:
  push {r1-r3, r7, lr}

  mov r0, #1
  ldr r2, [r1]
  add r1, r1, #4
  mov r7, #4

  svc #0

  pop {r1-r3, r7, pc}
.ltorg

.text
;.extern stderr
tc_print_err:
  push {r1-r3, r7, lr}

  mov r0, #2
  ldr r2, [r1]
  add r1, r1, #4
  mov r7, #4

  svc #0

  pop {r1-r3, r7, pc}
.ltorg

.data
minus:
  .ascii "-"
num:
  .byte '0'

.text
tc_print_int:
  push {r1-r7, lr}
  mov r4, r1

  cmp r4, #0
  bge Lprint_int_pow

  mov r0, #1
  ldr r1, =minus
  mov r2, #1
  mov r7, #4
  svc #0
  neg r4, r4

Lprint_int_pow:
  mov r5, #1

  mov r1, r4
  mov r2, #10
  bl tc_div
  mov r6, r0

Lprint_int_pow_loop:
  cmp r6, #0
  beq Lprint_int_pow_loop_end
  mul r5, r5, r2
  mov r1, r6
  mov r2, #10
  bl tc_div
  mov r6, r0
  b Lprint_int_pow_loop


Lprint_int_pow_loop_end:
  cmp r5, #1
  blt Lprint_int_print_end

  mov r1, r4
  mov r2, r5
  bl tc_div
  mov r6, r0

  mov r0, #1
  add r7, r6, #48
  ldr r1, =num
  strb r7, [r1]
  mov r2, #1
  mov r7, #4
  svc #0

  mul r7, r5, r6
  sub r4, r4, r7
  mov r1, r5
  mov r2, #10
  bl tc_div
  mov r5, r0

  b Lprint_int_pow_loop_end

Lprint_int_print_end:
  pop {r1-r7, pc}
.ltorg

.text
.extern fflush
tc_flush:
  mov pc, lr
.ltorg

.global main
.text
main:
  push {r7, lr}


  bl tc_main
  mov r0, #0
  pop {r7, pc}

.text
tc_ord:
  push {r1-r3, lr}
  ldr r2, [r1]
  cmp r2, #0
  bne Lord_load
  mov r0, #-1
  b Lord_end

Lord_load:
  add r0, r1, #4
  ldrb r0, [r0]

Lord_end:
  pop {r1-r3, pc}

.data
Lchr_except_msg:
  .asciz "chr: character out of range\n"

.text
tc_chr:
  push {r1-r4, lr}
  cmp r1, #0
  blt Lchr_except
  ldr r2, =256
  cmp r1, r2
  bge Lchr_except
  mov r0, #2
  mov r4, r1
  bl malloc
  strb r4, [r0, #4]
  mov r4, #1
  str r4, [r0]
  pop {r1-r4, pc}

Lchr_except:
  mov r0, #2
  ldr r1, =Lchr_except_msg
  mov r2, #28
  mov r7, #4
  svc #0
  mov r0, #120
  mov r7, #1
  svc #0
.ltorg

.text
tc_size:
  push {r1-r3, lr}
  ldr r0, [r1]
  pop {r1-r3, pc}

        .data
Lsubstring_except_msg:
        .asciz "substring: arguments out of bounds\n"
.text
tc_substring:
  push {r1-r6, lr}

  cmp r2, #0
  blt Lsubstring_error

  cmp r3, #0
  blt Lsubstring_error

  add r4, r2, r3
  ldr r5, [r1]
  cmp r4, r5
  bgt Lsubstring_error

  mov r6, r1
  add r1, r4, #4
  bl tc_malloc

  str r3, [r0]
  add r6, r6, #4
  add r6, r6, r2
  add r5, r0, #4

Lsubstring_loop:
  cmp r3, #0
  beq Lsubstring_end

  ldrb r4, [r6]
  strb r4, [r5]
  add r5, r5, #1
  add r6, r6, #1
  sub r3, r3, #1
  b Lsubstring_loop

Lsubstring_end:
  pop {r1-r6, pc}

Lsubstring_error:
  mov r0, #2
  ldr r1, =Lsubstring_except_msg
  mov r2, #35
  mov r7, #4
  svc #0
  mov r0, #120
  mov r7, #1
  svc #0
  pop {r1-r6, pc}
.ltorg

.text
.extern strcpy
tc_concat:
  push {r1-r10, lr}

  ldr r4, [r1]
  cmp r4, #0
  bne Lconcat_next
  mov r0, r2
  b Lconcat_end

Lconcat_next:
  ldr r5, [r2]
  cmp r5, #0
  bne Lconcat_begin
  mov r0, r1
  b Lconcat_end

Lconcat_begin:
  add r6, r4, r5
  mov r9, r1
  add r1, r6, #4
  bl tc_malloc
  str r6, [r0]
  add r7, r0, #4

  add r9, r9, #4
  add r2, r2, #4

Lconcat_first_loop:
  cmp r4, #0
  beq Lconcat_second_loop
  ldrb r8, [r9]
  strb r8, [r7]
  add r7, r7, #1
  add r9, r9, #1
  sub r4, r4, #1
  b Lconcat_first_loop

Lconcat_second_loop:
  cmp r5, #0
  beq Lconcat_end
  ldrb r8, [r2]
  strb r8, [r7]
  add r7, r7, #1
  add r2, r2, #1
  sub r5, r5, #1
  b Lconcat_second_loop

Lconcat_end:
  pop {r1-r10, pc}

.text
tc_not:
  push {lr}
  cmp r1, #0
  beq L_not_1
  mov r0, #0
  pop {pc}
L_not_1:
  mov r0, #1
  pop {pc}

.text
tc_getchar:
  push {r1-r4, r7, lr}
  mov r0, #5
  bl malloc

  mov r4, r0
  mov r2, #1
  add r1, r0, #4
  mov r0, #0
  mov r7, #3
  svc #0

  str r0, [r4]
  mov r0, r4
  pop {r1-r4, r7, pc}

.text
tc_div:
  push {r1-r10, lr}
  mov r5, r1
  mov r6, r2

  cmp r5, #0
  bge Ldiv_neg_test

Ldiv_negative_1:
  mvn r1, r5
  add r1, r1, #1

Ldiv_neg_test:
  cmp r6, #0
  bge Ldiv_begin

Ldiv_negative_2:
  mvn r2, r6
  add r2, r2, #1

Ldiv_begin:
  clz r4, r1
  clz r3, r2
  sub r4, r3, r4

  add r4, r4, #1
  mov r3, #0
  b Ldiv_check
Ldiv_loop:
  cmp r1, r2, lsl r4
  adc r3, r3, r3

  subcs r1, r1, r2, lsl r4
Ldiv_check:
  subs r4, r4, #1
  bpl Ldiv_loop

  cmp r5, #0
  blt Ldiv_neg_check

  cmp r6, #0
  blt Ldiv_negative_end

Ldiv_positive_end:
  mov r0, r3
  pop {r1-r10, pc}

Ldiv_neg_check:
  cmp r6, #0
  blt Ldiv_positive_end

Ldiv_negative_end:
  mvn r0, r3
  add r0, r0, #1
  pop {r1-r10, pc}
