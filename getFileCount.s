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
 * Function prototype: int getFileCount(const struct fileInfo *fi);
 * Description: Counts file in a filetree struct
 * Parameters: fi - Pointer fo filetree struct
 * Side Effects: Calls itself recursively
 * Error Conditions: None.
 * Return Value: int number of files in tree
 * Registers Used: 
 *	r0 - arg 1 -- struct fileInto *fi
 *	r1 - counter variable
 *  r2 - index variable, temp values
 *  r3 - global offsets and temp values
 *
 */
getFileCount:
    @ Save caller's registers on the stack
    push {fp, lr}
    add fp, sp, FP_OFFSET
    sub sp, sp, PARAM_SPACE     @ Allocate space for parameters
    sub sp, sp, LOCAL_SPACE     @ Allocate space for local variables
    str r0, [fp, PARAM_OFFSET]  @ Store parameter to stack

    @ int counter = 0
    mov r1, 0                   @ Set r1 to 0
    str r1, [fp, COUNTER_OFFSET] @ Set counter to 0

    @ for (int i = 0; i < fi->childrenSize; i++) {
    mov r2, 0                   @ Set r1 to 0
    str r2, [fp, INDEX_OFFSET]  @ Set index to 0

    ldr r3, =offset_childrenSize @ Get offset for childrenSize
    ldr r3, [r3]                 @ from global offsets
    ldr r0, [fp, PARAM_OFFSET]   @ Load pointer to filetree
    ldr r0, [r0, r3]             @ Load fi->childrenSize
    cmp r2, r0                   @ Check if index >= childrenSize
    bge endfor                   @ If so, skip the for loop

for:

    @ counter += getFileCount(fi->children[i])
    ldr r0, [fp, PARAM_OFFSET]   @ Load pointer to filetree
    ldr r3, =offset_children     @ Load offset to children
    ldr r3, [r3]                 @ array from global offsets
    ldr r0, [r0, r3]             @ Load fi->children
    
    ldr r2, [fp, INDEX_OFFSET]   @ Load index for for loop
    mov r1, INT_SIZE             @ Size of integer
    mul r2, r2, r1               @ Multiply them together to
    add r0, r0, r2               @ move to fi->children[i]

    bl getFileCount              @ getFileCount(fi->children[i])
    ldr r1, [fp, COUNTER_OFFSET] @ Load value of counter
    add r1, r1, r0               @ Increment it by one
    str r1, [fp, COUNTER_OFFSET] @ Store value back to stack

    ldr r2, [fp, INDEX_OFFSET]   @ Load value of index
    add r2, r2, 1                @ Increment it by one
    str r2, [fp, INDEX_OFFSET]   @ Store value back to stack

    ldr r3, =offset_childrenSize @ Get offset for childrenSize
    ldr r3, [r3]                 @ from global offsets
    ldr r0, [fp, PARAM_OFFSET]   @ Load pointer to filetree
    ldr r0, [r0, r3]             @ Load fi->childrenSize
    cmp r2, r0                   @ If index < childrenSize
    blt for                      @ Continue for loop
endfor:

    @ return counter
    ldr r0, [fp, COUNTER_OFFSET]

    @ Restore caller's registers
    pop {fp, pc}
