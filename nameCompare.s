/*
 * Filename: nameCompare.s
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: defines the nameCompare funtion that is passed in as
 *              parameter for qsort() function used in the PA4 program.
 * Date: Nov 27 2018
 * Sources of Help: Paul Cao's Worksheet 10
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 16
.equ P1_OFFSET, -8
.equ P2_OFFSET, -12

.text
.align 2
.global nameCompare

/*
 * Function name: nameCompare()
 * Function prototype: int nameCompare(const void *p1, const void *p2);
 * Description: Compares two filenames using alphabetical order
 * Parameters: p1 - Pointer to first struct fileinfo
 *             p2 - Pointer to second struct fileinfo
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: -1 if the first name is smaller, 
 *               0 if names are the same, or 1 if first name is larger.
 * Registers Used: 
 *	r0 - arg 1 -- input fileinfo p1
 *	r1 - arg 2 -- input fileinfo p2
 *
 */
nameCompare:
    @ Save caller's registers on the stack
    push {fp, lr}

    @ Translation #1: Assembly to Machine Instruction: ADD
    @ add fp, sp, FP_OFFSET
    .word 0xE28DB004

    sub sp, sp, PARAM_SPACE

    @ Translation #2: Assembly to Machine Instruction: STR
    @ str r0, [fp, P1_OFFSET]
    .word 0xE50B0008

    str r1, [fp, P2_OFFSET]

if:
    @ Call strcmp on two names

    @ Translation #3: Assembly to Machine Instruction: LDR
    @ ldr r0, [fp, P1_OFFSET]
    .word 0xE51B0008

    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp

    @ strcmp returned value < 0, first < second
    cmp r0, 0
    @ Translation #4: Assembly to Machine Instruction: BGE
    @ bge else_if
    .word 0xAA000001

    @ return -1
    mov r0, -1
    b end_if

else_if:
    @ Call strcmp on two names
    ldr r0, [fp, P1_OFFSET]
    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp

    @ strcmp returned value > 0, first > second
    cmp r0, 0

    @ Translation #5: Assembly to Machine Instruction: BLE
    @ ble else
    .word 0xDA000001

    @ return 1
    mov r0, 1
    b end_if

else:
    @ Else, equal, so return 0
    mov r0, 0

end_if:
    @ Translation #6: Assembly to Machine Instruction: SUB
    @ sub sp, fp, FP_OFFSET
    .word 0xE24BD004

    @ Restore caller's registers
    pop {fp, pc}
