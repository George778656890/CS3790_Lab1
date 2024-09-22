210106 ; LOADIM 0106 , load the (operand)starting address of array into the accumulator
250100 ; STORE 0100  , Store the content of accumulator(starting address of array 0105) into 0100
220100 ; LOADX  Load the starting location of array from 0100 to the index register
100105 ; READ   "tmp var at 0105" to hold value that we will store in array
200105 ; LOAD   Load "tmp var at 0105" into accumulator
410009 ; BRANCHNEG  if "the value at accumulator"< 0 , the reading is finished,continue execution
260000 ; STOREIDX   Store "the value at accumulator" to the array whose memory address is in the index register
380000 ; INC        Increment the index register to move to the next array location
400003 ; BRANCH    Jump to the memory address 3 to read the next element of array
430000 ; SWAP  Swap the content of index register with accumulator,now accumulator holds the array address location one past the last element
320100 ; SUBTRACT  Subtract the "starting address of array" from the accumulator(current index register value) 
420030 ; BRANCHZERO Branch to the code that output -1
300100 ; ADD  Add back the array address
430000 ; SWAP  Swap the content of index register with accumulator,now index register holds the array address location one past  last element
210000 ; LOADIM Accumulator  has 0 in it
390000 ; DEC    Decrement the index register to the last element of the array
200101 ; LOAD   Load "the Max value at 0101" to the accumulator
330000 ; SUBTRACTX  Subtract the "current value of array at index register" from the accumulator("the Max value at 0101")
410025 ; BRANCHNEG   Negative means current array element is bigger than "the Max value",update the Max value
430000 ; SWAP  Swap the content of index register with accumulator,now accumulator holds the array address location
320100 ;SUBTRACT  Subtract "the starting location of array" from the accumulator
420028 ; BRANCHZERO  Completion of comparison and finding the Max,branch to the code to output the Max
300100 ; ADD  Add back the array address
430000 ; SWAP  Swap the content of index register with accumulator,now index register holds the array address location
400015 ; BRANCH Branch back to continue the loop
230000 ; LOADIDX   Load the "current array element "at the index register to the accumulator
250101 ; STORE Store the "current array element " at the accumulator to "0101"
400007 ; BRANCH  Branch back to continue the loop
110101 ; WRITE   Write the "Max value at 0101" to the terminal
450001 ; HALT 
210001 ; LOADIM  Load the value "0001" to the accumulator
250103 ; STORE Store the value "0001" of the accumulator to address 0103
210000 ; LOADIM Accumulator  has 0 in it
320103 ; SUBTRACT   Accumulator is -1 now
250104 ; STORE    Store the value of "-1" to the address 0104
110104 ; WRITE    Write the value of "-1" to the terminal
450001 ; HALT