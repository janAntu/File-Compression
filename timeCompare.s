/*
 * Filetime: timeCompare.s
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: defines the timeCompare funtion that is passed in as
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
.global timeCompare

/*
 * Function time: timeCompare()
 * Function prototype: int timeCompare(const void *p1, const void *p2);
 * Description: Compares two file's times
 * Parameters: p1 - Pointer to first struct fileinfo
 *             p2 - Pointer to second struct fileinfo
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: 1 if the first time is smaller, 
 *               0 if times are the same, or -1 if first time is larger.
 * Registers Used: 
 *	r0 - arg 1 -- input fileinfo p1
 *	r1 - arg 2 -- input fileinfo p2
 *
 */
timeCompare:
    @ Save caller's registers on the stack
    push {fp, lr}
    add fp, sp, FP_OFFSET
    sub sp, sp, PARAM_SPACE
    str r0, [fp, P1_OFFSET]
    str r1, [fp, P2_OFFSET]

if:
    @ Call strcmp on two times
    ldr r0, [fp, P1_OFFSET]
    ldr r0, [r0, =offset_time]     @ get 1st time into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1, =offset_time]     @ get 2nd time into r1

    @ check if first < second
    cmp r0, r1
    bge else_if

    @ return -1
    mov r0, -1
    b end_if

else_if:
    @ Call strcmp on two times
    ldr r0, [fp, P1_OFFSET]
    ldr r0, [r0, =offset_time]     @ get 1st time into r0    
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1, =offset_time]     @ get 2nd time into r1

    @ check if first > second
    cmp r0, r1
    ble else

    @ return 1
    mov r0, 1
    b end_if

else:
    @ Else, equal, so return 0
    mov r0, 0

end_if:
    sub sp, fp, FP_OFFSET

    @ Restore caller's registers
    pop {fp, pc}
