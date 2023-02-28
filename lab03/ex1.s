.data
.word 2, 4, 6, 8
n: .word 9  #  creates a label n that points to a memory location where the value 9 is stored

.text
main:   
    add t0, x0, x0  # t0 = 0
    addi t1, x0, 1 # t1 = 1
    la t3, n    # load address of n into t3
    lw t3, 0(t3) # load value of n into t3
fib:    
    beq t3, x0, finish # if t3 == 0, jump to finish
    add t2, t1, t0 
    mv t0, t1   # t0 = t1   
    mv t1, t2   # t1 = t2
    addi t3, t3, -1  
    j fib
finish: 
    # sets the value of the a0 register to the integer value 1, 
    # which specifies the print integer service to be invoked by the ecall instruction.
    addi a0, x0, 1  
    # store the value of t0 in the a1 register, which is the first argument to the print integer service
    addi a1, t0, 0  
    ecall # print integer ecall
    # Programs end with an ecall with argument value 10.
    addi a0, x0, 10
    ecall # terminate ecall
