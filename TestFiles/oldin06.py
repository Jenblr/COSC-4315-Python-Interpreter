# Test Case 6:Local/Global Variables + Functions 

# Global
globalNumber = 5

def addToGlobal(x):
    localNumber = x
    result = globalNumber + localNumber  # Uses global variable
    return result

localInput = 10
resultFunctionCall = addToGlobal(localInput)

print("ResultFunctionCall =", resultFunctionCall)