#pragma once

class kmw {

public:
	static bool compare(char *s1, char *s2) {

		/*
			Compares all characters until s1, or s2 hit a null terminator.
			If all chars before that event happens are the same, the function returns true
			else it returns false.
		*/
		
		char* s1itb = s1;
		char* s2itb = s2;

		while (*s1itb != '\0' && *s2itb != '\0')
		{
			if (*s1itb != *s2itb) {
				return false;
			}
			s1itb++;
			s2itb++;
		}
		return true;
		
	}
};