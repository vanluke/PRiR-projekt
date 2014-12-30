#ifndef KARP_RABIN_H
#define KARP_RABIN_H

#include <iostream>

class KarpRabin
{
public:
	KarpRabin();
	~KarpRabin();
	/*
		=======================================================
		usage
		=======================================================
		number_of_character_in_input_alphabet - liczba znakow w alfabecie,
		pat - wzorzec,
		txt - tekst, w ktorym szukasz,
		q - liczba pierwsza dla unikniecia kolizji.

		returns:
		-1: gdy nie znajdzie badz gdy dlugosc tekstu jest mniejsza od szukanego wzorca.
	*/
	int karp_rabin(std::string pat, std::string txt, int q, int number_of_character_in_input_alphabet = 256);
};
// hash(txt[s + 1 ..s + m]) = d(hash(txt[s ..s + m - 1]) – txt[s] * h) + txt[s + m] ) mod q
//
// hash(txt[s ..s + m - 1]) : Hash value at shift s.
// hash(txt[s + 1 ..s + m]) : Hash value at next shift(or shift s + 1)
// d : Number of characters in the alphabet
// q : A prime number
// h : d ^ (m - 1)
#endif

