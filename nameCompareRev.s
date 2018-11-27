/*
 * Filename: nameCompareRev.s
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: defines the nameCompareRev funtion that is passed in as
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
.global nameCompareRev

/*
 * Function name: nameCompareRev()
 * Function prototype: int nameCompareRev(const void *p1, const void *p2);
 * Description: Compares two names using reverse alphabetical order
 * Parameters: p1 - Pointer to first struct fileinfo
 *             p2 - Pointer to second struct fileinfo
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: 1 if the first name is smaller, 
 *               0 if names are the same, or -1 if first name is larger.
 * Registers Used: 
 *	r0 - arg 1 -- input fileinfo p1
 *	r1 - arg 2 -- input fileinfo p2
 *
 */
nameCompareRev:
    @ Save caller's registers on the stack
    push {fp, lr}
    add fp, sp, FP_OFFSET
    sub sp, sp, PARAM_SPACE
    str r0, [fp, P1_OFFSET]
    str r1, [fp, P2_OFFSET]

if:
    @ Call strcmp on two names
    ldr r0, [fp, P1_OFFSET]
    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp

    @ strcmp returned value < 0, first < second
    cmp r0, 0
    bge else_if

    @ return 1
    mov r0, 1
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
    ble else

    @ return -1
    mov r0, -1
    b end_if

else:
    @ Else, equal, so return 0
    mov r0, 0

end_if:
    sub sp, fp, FP_OFFSET

    @ Restore caller's registers
    pop {fp, pc}
