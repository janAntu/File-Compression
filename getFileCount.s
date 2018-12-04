/*
 * Filename: getFileCount.s
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: defines the getFileCount funtion that is passed in as
 *              parameter for qsort() function used in the PA4 program.
 * Date: Nov 27 2018
 * Sources of Help: Paul Cao's Worksheet 10
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 4
.equ LOCAL_SPACE, 8

.equ PARAM_OFFSET, -4
.equ COUNTER_OFFSET, -8
.equ INDEX_OFFSET, -12

.equ INT_SIZE, 4

.text
.align 2
.global getFileCount

/*
 * Function name: getFileCount()
 * Function prototype: int getFileCount(const void *p1, const void *p2);
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
getFileCount:
    @ Save caller's registers on the stack
    push {fp, lr}
    add fp, sp, FP_OFFSET
    sub sp, sp, PARAM_SPACE 
    sub sp, sp, LOCAL_SPACE
    str r0, [fp, PARAM_OFF]

    @ int counter = 0
    mov r1, 0
    str r1, [fp, COUNTER_OFF]

    @ for (int i = 0; i < fi->childrenSize; i++) {
    mov r2, 0
    str r2, [fp, INDEX_OFFSET]

    ldr r3, =offset_childrenSize
    ldr r3, [r3]
    ldr r0, [fp, PARAM_OFF]
    ldr r0, [r0, r3]
    cmp r2, r0
    bge endfor

for:

    @ counter += getFileCount(fi->children[i])
    ldr r0, [fp, PARAM_OFF]
    ldr r3, =offset_children
    ldr r3, [r3]
    ldr r0, [r0, r3]
    
    ldr r2, [fp, INDEX_OFF]
    mul r2, r2, INT_SIZE
    add r0, r0, r2

    bl getFileCount
    ldr r1, [fp, COUNTER_OFF]
    add r1, r1, r0
    str r1, [fp, COUNTER_OFF]





    ldr r2, [fp, INDEX_OFFSET]
    add r2, r2, 1
    str r2, [fp, INDEX_OFFSET]

    ldr r3, =offset_childrenSize
    ldr r3, [r3]
    ldr r0, [fp, PARAM_OFF]
    ldr r0, [r0, r3]
    cmp r2, r0
    blt for
endfor:

    @ return counter
    ldr r0, [fp, COUNTER_OFFSET]

    @ Restore caller's registers
    pop {fp, pc}
