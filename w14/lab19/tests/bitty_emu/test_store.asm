xor     r0, r0  # 0: init counter: r0 = 0
xor     r2, r2  # 1: init addr pointer: r2 = 0

loop:
    xor     r1, r1  # 2: init number upper limit
    add     r1, 101 # 3: r1 = 101

    st      r0, r2  # 4: memory[r2] = r0
    add     r0, 1   # 5: counter++
    add     r2, 2   # 6: r2 += 2
    cmp     r1, r0  # is r1 < r0?
    big     loop    # if so, then jump to label 2
