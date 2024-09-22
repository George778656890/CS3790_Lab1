100100 ; READ  Read the value of m to address 0100
100101 ; READ  Read the value of n to address 0101
200101 ; LOAD  Load the "n at 0101" to accumulator
420018 ; BRANCHZERO  Branch to output the final result of "m" when n=0
200100 ; LOAD  Load the "m at 0100" to the accumulator
340101 ; DIVIDE Divide the "m at accumulator" by "n at 0101",now accumulator holds the Quotient
250102 ; STORE  Store the Quotient to address 0102
200100 ; LOAD  Load the "m at 0100" to the accumulator
360102 ; MULTIPLY  Multiply the "m at accumulator" by "Quotient at 0102",now accumulator holds the product of m* Quotient
250106 ; STORE     Store the "product of m* Quotient" to address 0106
200100 ; LOAD  Load the "m at 0100" to the accumulator
320106 ; SUBTRACT  Subtract the "m at accumulator" by "the product of m*Quotient",now accumulator holds the remainder
250103 ; STORE     Store the remainder to address 0103
200101 ; LOAD  Load the "n at 0101" to accumulator
250100 ; STORE Store the "n at accumulator" to address 0100 to replace m
200103 ; LOAD  Load the "remainder at 0103" to accumulator
250101 ; STORE Store the "remainder at accumulator" to address 0101 to replace n
400002 ; BRANCH  Branch back to continue the loop
110100 ; WRITE   Write the "m" to the terminal
450001 ; HALT