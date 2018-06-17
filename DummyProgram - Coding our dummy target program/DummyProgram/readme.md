#Directions:

You are going to code a simple console program everything will go in main() that does the following things:
- Declare a variable named varInt of type integer equal to 123456
- Declare a variable named varString of type string with the text "DefaultString" (C++ only, ignore if writing in C)
- Declare an array of char named arrChar of size 128 with the text "Long char array right there ->" (you can put the size in a declared constant)
- Declare a pointer to integer named ptr2int pointing to varInt
- Declare a pointer to pointer to int named ptr2ptr pointing to ptr2int
- Declare a pointer to pointer to pointer to int named ptr2ptr2 pointing to ptr2ptr

Once this is done you will create an infinite loop in which you will:
- Print to console "Process ID: " followed by the process ID of the program using the Windows API function GetCurrentProcessId() (Therefore, don't forget to #include <Windows.h> !!)
- Print to console "varInt (0x[ADDRESS OR THE VARIABLE]) = [VALUE OF THE VARIABLE]" (Remember that you can get the address of a variable by prefixing it by "&")
- Same thing for varString and varChar
- Same thing for our 3 pointers, print for example "ptr2int (0x[ADDRESS OF THE POINTER]) = 0x[ADDRESS POINTED])
- Print to console "Press ENTER to print again."
- Put something to pause, you can either use getchar() or system("pause > nul")
- Print to console a line of dashes ("-") and then let it loop back to the beginning