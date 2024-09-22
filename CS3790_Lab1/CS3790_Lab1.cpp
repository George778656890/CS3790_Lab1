#include <iostream>
#include <iomanip>
#include<string>
#include<vector>
#include<iterator>
#include<type_traits>
#include<iterator>
#include<algorithm>
#include<utility>
#include <cctype> 
#include <fstream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::ostream;
using std::pair;
using std::setw;
using std::setfill;
using std::ifstream;
using std::getline;

int upperBound = 999999;
int lowerBound = -999999;

//dumpCore() whose page number is calculated based on the instructionCounter
void dumpCore(int m[], int accumulator, int instructionCounter, int indexRegister, int operationCode, int operand) {

	int temp = instructionCounter + 100000;//Create a 6-digits numbers for manipulation convenience

	//Use the middle two digits of the Instruction Counter to determine the Page Number
	char thirdDigitChar = (std::to_string(temp))[2];
	char fourthDigitChar = (std::to_string(temp))[3];

	//Char to String to Number
	int ThirdDigit = std::stoi(std::string(1, thirdDigitChar));
	int FourthDigit = std::stoi(std::string(1, fourthDigitChar));
	int pageNumber = ThirdDigit * 10 + FourthDigit;

	cout << "\n\n";
	cout << "PAGE # " << pageNumber << "\n\n";


	cout << "REGISTERS:\n\n";

	cout << "accumulator             " << setw(6) << setfill('0') << accumulator << endl;
	cout << "InstructionCounter      " << setw(6) << setfill('0') << instructionCounter << endl;
	cout << "IndexRegister           " << setw(6) << setfill('0') << indexRegister << endl;
	cout << "operationCode               " << operationCode << endl;
	cout << "operand                   " << setw(4) << setfill('0') << operand << "\n\n";
	cout << "MEMORY" << endl;


	cout << "\t0      1      2      3      4      5      6      7      8      9\t";

	//Use pageNumber to determine the dumpCore memory range
	int startingIndex = pageNumber * 100;
	int endingIndex = pageNumber * 100 + 100;

	for (unsigned i = startingIndex; i != endingIndex; ++i) {
		if (i % 10 == 0) {
			cout << endl;
			cout << setw(2) << i<<" ";
		}
		cout << setw(6) << setfill('0')<< m[i]<<" ";
	}
	cout << endl;
}

//Overloaded dumpCore() in which page number is provided as the parameter
void dumpCore(int m[], int accumulator, int instructionCounter, int indexRegister, int operationCode, int operand,int pageNumber) {

	
	cout << "\n\n";
	cout << "PAGE # " << pageNumber << "\n\n";


	cout << "REGISTERS:\n\n";

	cout << "accumulator             " << setw(6) << setfill('0') << accumulator << endl;
	cout << "InstructionCounter      " << setw(6) << setfill('0') << instructionCounter << endl;
	cout << "IndexRegister           " << setw(6) << setfill('0') << indexRegister << endl;
	cout << "operationCode               " << operationCode << endl;
	cout << "operand                 " << setw(4) << setfill('0') << operand << "\n\n";
	cout << "MEMORY" << endl;


	cout << "\t0      1      2      3      4      5      6      7      8      9\t";

	//Use pageNumber to determine the dumpCore memory range
	int startingIndex = pageNumber * 100;
	int endingIndex = pageNumber * 100 + 100;

	for (unsigned i = startingIndex; i != endingIndex; ++i) {
		if (i % 10 == 0) {
			cout << endl;
			cout << setw(2) << i << " ";
		}
		cout << setw(6) << setfill('0') << m[i] << " ";
	}
	cout << endl;
}



//Invalid operation code error
bool invalidOperationCode(int operationCode) {
	if (operationCode==10|| operationCode==11||
		operationCode==20|| operationCode==21||
		operationCode==22|| operationCode==23||
		operationCode==25|| operationCode==26||
		operationCode==30|| operationCode==31||
		operationCode==32|| operationCode==33||
		operationCode==34|| operationCode==35||
		operationCode==36|| operationCode==37||
		operationCode==38|| operationCode==39||
		operationCode==40|| operationCode==41||
		operationCode==42|| operationCode==43||
		operationCode==45) {

		return false;
	}
	else {
		return true;
	}
}


//Accumulator overflow error
bool accumulatorOverflow(int accumulator) {
	if (accumulator > upperBound || accumulator < lowerBound) {
		return true;
	}
	else {
		return false;
	}
}


//Divide by zero error
int divideByZero(int operand) {
	cout << "Divide by Zero Error";
	return operand;
}

int main()
{
	int accumulator = 0;				
	int instructionCounter = 0;			
	int instructionRegister = 0;		
	int indexRegister = 0;
	int operationCode = 0;				
	int operand = 0;					

	int memory[10000] = { 0 };//Memory Initialization

	string userInput = "";
	string userInstructionInput = "";
	bool runningFlag = false;
	

	

	cout << "*** Welcome to Simpletron V2! ***\n***\nDo you have a file that contains your SML program (Y/N) ?";
	cin >> userInput;
	cout << endl;

	if (userInput=="Y"||userInput=="y") {
		cout << "Filename: ";

		// Get the file name from the user
		string userFile = "";
		cin >> userFile;

		//string fileLocation = "f:\\";
		//fileLocation = fileLocation + userFile;


		string SML_Instruction = "";

		// Create an input file stream
		ifstream inputFile(userFile);

		while (getline(inputFile, SML_Instruction)) //getline() reads file line by line until newline or the end of file
		{
			
			// Find the position of the semicolon  
			size_t pos = SML_Instruction.find(';');

			// Extract the part before the semicolon
			SML_Instruction = SML_Instruction.substr(0, pos);
			

			//Convert the string to digit,and store in the memory
			memory[instructionCounter] = std::stoi(SML_Instruction);
			++instructionCounter;
		}


		// Close the file  
		inputFile.close();

		


	}
	else if (userInput == "N" || userInput == "n") {

		cout << "*** Please enter your program one instruction( or data word ) at a time        ***\n\
*** I will type the location number and a question mark (?). You then          ***\n\
*** type the word for that location. Type the word GO to execute  your program ***\n\n";

		int lineNumber = 0;
		//Loading the SML instructions into the Simulator 
		do {
			cout << setw(4) << setfill('0') << lineNumber<<"?";
			cin >> userInstructionInput;

			if (userInstructionInput=="GO"||userInstructionInput=="go") {
				break;
			}

			//Convert the string to digit,and store in the memory
			if (std::stoi(userInstructionInput) > upperBound || std::stoi(userInstructionInput) < lowerBound) {
				cout << "Your input is out of the normal range,please restart the program\n\n";
				return 1;
			}else{
			memory[instructionCounter]=std::stoi(userInstructionInput);
			++lineNumber;
			++instructionCounter;
			}
		} while (true);
		
	}
	else {
		cout << "Your input is invalid,please restart the program\n\n";
		return 1;
	}


	//Executes the SML instructions

	instructionCounter = 0;

	do {
		instructionRegister = memory[instructionCounter];
		operationCode = abs(instructionRegister )/ 10000;

		if (invalidOperationCode(operationCode)) {
			cout << "\n";
			cout << "*******Invalid Operation Code Error*******";
			dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
			return 1;
		}

		operand = abs(instructionRegister) % 10000;

		//OperationCode Selection
		switch (operationCode)
		{
        //Read a word from the terminal into a location whose address is the operand
		case 10: 
		{
			cout << "?";

			int terminalInput =0;
			cin >> terminalInput;
			memory[operand] = terminalInput;

			dumpCore(memory,accumulator,instructionCounter, indexRegister,operationCode,operand);

			++instructionCounter;
			break;
		}

		//Write a word from the location whose address is the operand to the terminal
		case 11: 
		{
			cout << memory[operand] << endl;

			dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

			++instructionCounter;
			break;

		}

		//Load a word from the memory location specified by the operand into the accumulator
		case 20: 
		{
			accumulator = memory[operand];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}
		}

		//Load the operand into the accumulator
		case 21: 
		{
			accumulator = operand;

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}
		}

		//Load word from the memory location specified by the operand into the index register
		case 22: 
		{
			indexRegister= memory[operand];

			dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

			++instructionCounter;
			break;
		}

		//Load word from the memory location specified by index register into accumulator
		case 23: 
		{
			accumulator = memory[indexRegister];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}
		}

		//Store a word from the acccumulator into the memory location specified by the operand
		case 25: 
		{
			memory[operand] = accumulator;

			dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

			++instructionCounter;
			break;
		}

		//store a word from the accumulator into a memory location specified by index register
		case 26:
		{
			memory[indexRegister] = accumulator;

			dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

			++instructionCounter;
			break;
		}

		//Add the word in memory whose address is the operand to the accumulator and leave result in accumulator(ACC += MEM)
		case 30: 
		{
			accumulator += memory[operand];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}
		}

		//Add a word in memory whose address is stored in index register to the accumulator and leave result in accumulator
		case 31: 
		{
			accumulator += memory[indexRegister];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}
		}

		//Subtract a word whose address stored in the operand from the accumulator and leave result in accumulator(ACC -= MEM)
		case 32: 
		{
			accumulator -= memory[operand];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}

		}

		//Subtract a word whose address is stored in the index register from the accumulator and leave result in accumulator
		case 33: 
		{
			accumulator -= memory[indexRegister];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}
		}

		//Divide the accumulator by a word whose address stored in the operand and leave result in accumulator and lose the remainder.(ACC /= MEM)
		case 34: 
		{
			if (divideByZero(memory[operand]) == 0) {
				cout << "\n\n";
				cout << "*******Divide by Zero Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {
				accumulator /= memory[operand];

				if (accumulatorOverflow(accumulator)) {
					cout << "\n\n";
					cout << "*******Accumulator Overflow Error*******";
					dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
					return 1;
				}
				else {
					dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

					++instructionCounter;
					break;
				}
			}

		}

		//Divide the accumulator by a word whose address is stored in the index register and leave result in accumulator and lose the remainder.
		case 35: 
		{
			if (divideByZero(memory[indexRegister]) == 0) {
				cout << "\n\n";
				cout << "*******Divide by Zero Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {
				accumulator /= memory[indexRegister];

				if (accumulatorOverflow(accumulator)) {
					cout << "\n\n";
					cout << "*******Accumulator Overflow Error*******";
					dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
					return 1;
				}
				else {
					dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

					++instructionCounter;
					break;
				}
			}
			
		}

		//Multiply the accumulator by a word from a specific location in memory and leave result in accumulator(ACC *= MEM)
		case 36: 
		{
			accumulator *= memory[operand];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}
		}

		//Multiply the accumulator by a word whose address is stored in the index register and leave result in accumulator
		case 37: 
		{
			accumulator *= memory[indexRegister];

			if (accumulatorOverflow(accumulator)) {
				cout << "\n\n";
				cout << "*******Accumulator Overflow Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;
				break;
			}

		}

		//increase index register by 1
		case 38: 
		{
			++indexRegister;

			if (indexRegister > upperBound || indexRegister < lowerBound) {
				cout << "\n\n";
				cout << "*******Index Out of Bound Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}else{

			dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

			++instructionCounter;

			break;
			}
		}

		//decrease index register by 1
		case 39: 
		{
			--indexRegister;

			if (indexRegister > upperBound || indexRegister < lowerBound) {
				cout << "\n\n";
				cout << "*******Index Out of Bound Error*******";
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);
				return 1;
			}
			else {

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter;

				break;
			}
		}

		//Branch to a specific location in memory, location address is in operand
		case 40: 
		{
			instructionCounter = operand;

			dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

			//++instructionCounter;  No increment here!!!

			break;
		}

		//Branch to a specific location in memory if accumulator is negative
		case 41: 
		{
			if (accumulator < 0) {

				instructionCounter = operand;

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				//++instructionCounter;  No increment here!!!

				break;
			}
			else {
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter; //Must increment here !!!

				break;
			}
		}

		//Branch to a specific location in memory if the accumulator is zero
		case 42:
		{
			if (accumulator == 0) {

				instructionCounter = operand;

				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				//++instructionCounter;  No increment here!!!

				break;
			}
			else {
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand);

				++instructionCounter; //Must increment here !!!

				break;
			}
		}

		//swap contents of index register and accumulator
		case 43: 
		{
			int temp = 0;
			temp = indexRegister;
			indexRegister = accumulator;
			accumulator = temp;
		}

		//halt program dump register values and a range of pages. The starting page of the range is stored as 
		// the top 2 digits of the operand and the last page as the least significant 2 digits( core dump ).
		case 45: 
		{
			cout << "\n\n";
			cout << "*******HALT*******";

			//Dump register values and a range of pages
			unsigned startPage = abs(operand) / 100;
			unsigned endingPage = abs(operand) % 100;
			for (unsigned i = startPage; i != endingPage + 1;++i) {
				//Calling the overloaded dumpCore() in which page number is provided as the parameter
				dumpCore(memory, accumulator, instructionCounter, indexRegister, operationCode, operand,i);
			}
			cout << "\n\n";
			break;
		}


		default:
		{
			break;
		}

		}
		
			

	} while (operationCode != 45);






	return 0;

}

