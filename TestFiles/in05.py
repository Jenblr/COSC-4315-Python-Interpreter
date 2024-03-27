#5: Double Nested if-else Condition

z = 20

if z > 10:
    if z > 30:
        resultDoubleNested = z - 10
    else:
        if z > 15:
            resultDoubleNested = z + 10  #30
        else:
            resultDoubleNested = z * 2
else:
    resultDoubleNested = z / 2

print("ResultDoubleNested =", resultDoubleNested)