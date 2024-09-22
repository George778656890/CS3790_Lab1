# CS3790_Lab1
1.When the simulator prompts to input the file name, type "gcd.sml" or "maxMin.sml",the simulator will read the file and execute the SML instructions
2.The simulator is finished completely,and it works well;
3.For the two questions of GCD and MaxMin ,I only finish them partially,the following are the detailed description of the two problems's SML code

/***************************************************************************************************************************************************/
Given two positive integers, compute their greatest common divisor. 

100100 ; READ  Read the value of m to address 0100
100101 ; READ  Read the value of n to address 0101

200101 ; LOAD  Load the "n at 0101" to accumulator
4200?? ; BRANCHZERO  Branch to output the final result of "m" when n=0

200100 ; LOAD  Load the "m at 0100" to the accumulator
340101 ; DIVIDE Divide the "m at accumulator" by "n at 0101",now accumulator holds the Quotient
250102 ; STORE  Store the Quotient to address 0102
200100 ; LOAD  Load the "m at 0100" to the accumulator
360102 ; MULTIPLY  Multiply the "m at accumulator" by "Quotient at 0102",now accumulator holds the product of m* Quotient
250106 ; STORE     Store the "product of m* Quotient" to address 0106
200100 ; LOAD  Load the "m at 0100" to the accumulator
320106 ; SUBTRACT  Subtract the "m at accumulator" by "the product of m*Quotient",now accumulator holds the remainder
250103 ; STORE     Store the remainder to address 0103

;n--->m
200101 ; LOAD  Load the "n at 0101" to accumulator
250100 ; STORE Store the "n at accumulator" to address 0100 to replace m

;Remainder--->n
200103 ; LOAD  Load the "remainder at 0103" to accumulator
250101 ; STORE Store the "remainder at accumulator" to address 0101 to replace n

4000?? ; BRANCH  Branch back to continue the loop

;Output m
110100 ; WRITE   Write the "m" to the terminal
450001 ; HALT



000100           ; m
000101           ; n
000102           ; Quotient
000103           ; Remainder
000104           ; Greatest Common Divisor
000105           ; Loop iteration amount control
000106           ; tmp variable to hold the product of m * Quotient


/*******************************************************************************************************************************************/
Given an array as input , find the largest amd smallest elements in the array

210106 ; LOADIM 0106 , load the (operand)starting address of array into the accumulator
250100 ; STORE 0100  , Store the content of accumulator(starting address of array 0105) into 0100
220100 ; LOADX  Load the starting location of array from 0100 to the index register
100105 ; READ   "tmp var at 0105" to hold value that we will store in array
200105 ; LOAD   Load "tmp var at 0105" into accumulator
*410009 ; BRANCHNEG  if "the value at accumulator"< 0 , the reading is finished,continue execution
260000 ; STOREIDX   Store "the value at accumulator" to the array whose memory address is in the index register
380000 ; INC        Increment the index register to move to the next array location
400003 ; BRANCH    Jump to the memory address 3 to read the next element of array

430000 ; SWAP  Swap the content of index register with accumulator,now accumulator holds the array address location one past the last element
320100 ; SUBTRACT  Subtract the "starting address of array" from the accumulator(current index register value) 
4200?? ; BRANCHZERO Branch to the code that output -1
300100 ; ADD  Add back the array address
430000 ; SWAP  Swap the content of index register with accumulator,now index register holds the array address location one past  last element

;Find the Max
210000 ; LOADIM Accumulator  has 0 in it
*390000; DEC    Decrement the index register to the last element of the array
200101 ; LOAD   Load "the Max value at 0101" to the accumulator
330000 ; SUBTRACTX  Subtract the "current value of array at index register" from the accumulator("the Max value at 0101")
#41???? ; BRANCHNEG   Negative means current array element is bigger than "the Max value",update the Max value
430000 ; SWAP  Swap the content of index register with accumulator,now accumulator holds the array address location
320100 ;SUBTRACT  Subtract "the starting location of array" from the accumulator
4200?? ; BRANCHZERO  Completion of comparison and finding the Max,branch to the code to output the Max
300100 ; ADD  Add back the array address
430000 ; SWAP  Swap the content of index register with accumulator,now index register holds the array address location
4000?? ; BRANCH Branch back to continue the loop


;Update the Max value
230000 ; LOADIDX   Load the "current array element "at the index register to the accumulator
250101 ; STORE Store the "current array element " at the accumulator to "0101"
4000?? ; BRANCH  Branch back to continue the loop                    


;Output the Max
110101 ; WRITE   Write the "Max value at 0101" to the terminal
#4000?? ; BRANCH Branch to "find the Min"                ******************Test  HALT

;Find the Min



;Output -1
210001 ; LOADIM  Load the value "0001" to the accumulator
250103 ; STORE Store the value "0001" of the accumulator to address 0103
210000 ; LOADIM Accumulator  has 0 in it
320103 ; SUBTRACT   Accumulator is -1 now
250104 ; STORE    Store the value of "-1" to the address 0104
110104 ; WRITE    Write the value of "-1" to the terminal
450001 ; HALT   


230000 ; LOADIDX Load the last element of the array into accumulator
250101 ; STORE  Store "the last element of the array in the accumulator" to the 0101 which stores the Max value

230000 ; LOADIDX   Load "current element of the array" into the accumulator
320101 ; SUBTRACT  Subtract "the Max value at 0101" from the accumulator("current element of the array")
390000 ; DEC    Decrement to the index register to the next element of the array



#230000 ; LOAD   Load "current element of the array" into the accumulator
250101 ; STORE  Store "current array element" into the 0101 which stores the Max value




000100   0106    ;holds the starting loc of array
000101           ;holds the Max value
000102           ;holds the Min value
000103           ;holds the temp var=1
000104           ;holds the output value of -1
000105           ;holds the "tmp value" during reading
000106           ;array elements are stored starting here
