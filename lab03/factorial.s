.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:  # use iteration to get factorial
    # set t0 = a0 = n
    add t0, a0, x0
    # set t1 = 1, t1 stores the result
    addi t1, x0, 1
loop:
    # check if n == 0
    beq t0, x0, end
    # t1 = t1 * t0
    mul t1, t1, t0
    # t0 = t0 - 1
    addi t0, t0, -1
    # go back to loop
    j loop
end:
    # return t1
    add a0, t1, x0
    ret