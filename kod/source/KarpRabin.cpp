
#include "KarpRabin.h"
#include <cstring>
using namespace std;

KarpRabin::KarpRabin()
{
}


KarpRabin::~KarpRabin()
{
}

int KarpRabin::karp_rabin(std::string pat, std::string txt, int q, int number_of_character_in_input_alphabet) {
	int pattern_length = strlen(pat.c_str());
	int text_length = strlen(txt.c_str());

	if (pattern_length > text_length) {
		return -1;
	}

	int i, j;

	int hash_pattern = 0;  

	int hash_text = 0; 

	int h = 1;

	for (i = 0; i < pattern_length - 1; i++) {
		h = (h * number_of_character_in_input_alphabet) % q;
	}
	
	for (i = 0; i < pattern_length; i++) {
		hash_pattern = (number_of_character_in_input_alphabet * hash_pattern + pat[i]) % q;
		hash_text = (number_of_character_in_input_alphabet * hash_text + txt[i]) % q;
	}

	for (i = 0; i <= text_length - pattern_length; i++) {
		if (hash_pattern == hash_text) {
			for (j = 0; j < pattern_length; j++) {
				if (txt[i + j] != pat[j]) {
					break;
				}
			}
			if (j == pattern_length) {
				return i;
			}
		}

		if (i < text_length - pattern_length) {
			hash_text = (number_of_character_in_input_alphabet * (hash_text - txt[i] * h) + txt[i + pattern_length]) % q;
			if (hash_text < 0) {
				hash_text = hash_text + q;
			}
		}
	}
	return -1;
}
