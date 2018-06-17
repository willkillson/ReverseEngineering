#include <iostream>
#include <Windows.h>


int main() {


	//-Declare a variable named varInt of type integer equal to 123456
	//- Declare a variable named varString of type string with the text "DefaultString" (C++ only, ignore if writing in C)
	//- Declare an array of char named arrChar of size 128 with the text "Long char array right there ->" (you can put the size in a declared constant)
	//- Declare a pointer to integer named ptr2int pointing to varInt
	//- Declare a pointer to pointer to int named ptr2ptr pointing to ptr2int
	//- Declare a pointer to pointer to pointer to int named ptr2ptr2 pointing to ptr2ptr

	int varInt = 123456;
	std::string varString = "DefaultString";
	char arrChar[128] = "Long char array right here ->";
	int *ptr2int = &varInt;
	int **ptr2ptr = &ptr2int;
	int ***ptr2ptr2ptr = &ptr2ptr;



	while (1) {


		std::cout << "Process ID: " << GetCurrentProcessId() << std::endl << std::endl;
		std::cout << "varInt     " <<'\t' << "(0x" << &varInt << ") = "<< varInt << std::endl;
		std::cout << "varString  " << '\t' << "(0x" << &varString << ") = " << varString.c_str() << std::endl;
		std::cout << "arrChar    " << '\t' << "(0x" << &arrChar << ") = " << arrChar << std::endl;
		std::cout << "ptr2int    " << '\t' << "(0x" << &ptr2int << ") = " << ptr2int << std::endl;
		std::cout << "ptr2ptr    " << '\t' << "(0x" << &ptr2ptr << ") = " << ptr2ptr << std::endl;
		std::cout << "ptr2ptr2ptr" << '\t' << "(0x" << &ptr2ptr2ptr << ") = " << ptr2ptr2ptr << std::endl << std::endl;

		std::cout << "Press ENTER to print again" << '\n' << '\n' << '\n'<<"------------------------------------------" << '\n';


		std::cin.ignore();


	} 



}