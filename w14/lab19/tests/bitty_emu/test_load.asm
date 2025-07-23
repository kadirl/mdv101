# xor r0, r0  # r0 = mem_pointer
# xor r1, r1  # r1 = counter

# loop:
#     # init condition
#     xor r2, r2  # r2 = 0
#     add r2, 200 # r2 = 200 = upper mem_pointer limit

#     # retrieve data from memory
#     ld  r1, r0  # r1 = mem[r0]
#     add r0, 2   # r0 += 2

#     # check condition
#     cmp r2, r0  # if r2 > r0 : 200 > mem_addr
#     big loop    # then jump to loop


ld r1, r0   # load at 0

add r0, 10  # load at 10
ld r2, r0

add r0, 25  # load at 35
ld r3, r0

add r0, 5   # load at 40
ld r4, r0

add r0, 20  # load at 60
ld r5, r0

add r0, 30  # load at 90
ld r6, r0

add r0, 35  # load at 125
ld r7, r0

add r0, 5   # load at 130
ld r0, r0
