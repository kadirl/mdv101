nop         # 0

# Count from 0 to 100
xor r0, r0  # 1: init counter
xor r1, r1  # 2: init condition
add r1, 5   # 3: 
add r0, 1   # 4: counter++
cmp r1, r0  # 5: counter < 100? 
big 2       # 6: if counter < 100, jump to 5

# Count from 100 to 0
# xor r0, r0   # 7: init counter
# add r0, 5    # 8: 
xor r1, r1   # 7: init condition
sub r0, 1    # 8: counter--
cmp r1, r0   # 9: counter > 0?
bil 7        # 10: if counter > 0, jump to 7
