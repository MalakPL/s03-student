/*
	Zrobiłem z obsługą znaków UTF-8
*/

#include <iostream>
#include <sstream>
#include <io.h>
#include <fcntl.h>

using std::wcout;
using std::wcerr;
using std::endl;
using std::wstring;
using std::wstringstream;
using std::exception;

struct Student
{
	wstring imie;
	wstring nazwisko;
	wstring numer_indeksu;
	unsigned char semestr; /* Najmniejsze możliwe słowo dla semestru w jezyku c++ */
	double srednia;

	Student(wstring imie, wstring nazwisko, wstring numer_indeksu, unsigned char semestr, double srednia)
	{
		if (imie.length() < 2 || imie.length() > 32)
		{
			throw exception{ "Imię musi zawierać od 2 do 32 znaków" };
		}

		if (nazwisko.length() < 2 || nazwisko.length() > 32)
		{
			throw exception{ "Nazwisko musi zawierać od 2 do 32 znaków" };
		}

		if (semestr == 0 || semestr > 8)
		{
			throw exception{ "Semestr musi być w przedziale od 1 do 8" };
		}

		if (srednia < 1 || srednia > 6)
		{
			throw exception{ "Średnia musi być w przedziale od 1 do 6" };
		}

		this->imie = imie;
		this->nazwisko = nazwisko;
		this->numer_indeksu = numer_indeksu;
		this->semestr = semestr;
		this->srednia = srednia;
	}

	auto to_string() const -> wstring
	{
		wstringstream stream;
		stream << imie << L" " << nazwisko << L" o numerze indeksu " << numer_indeksu << L", jest na " << (int)semestr << L" semestrze z średnia oceną " << srednia;

		return stream.str();
	}
};

auto main() -> int
{
	try
	{
		if (_setmode(_fileno(stdout), _O_U8TEXT) == -1)
		{
			throw exception{ "Nie można ustawić kodowania UTF-8" };
		}

		Student Karol{ L"Karol", L"Szmajda", L"s24574", 1, 1.618 };
		wcout << Karol.to_string() << endl;
	}
	catch (exception ex)
	{
		wcerr << "Wyjatek: " << ex.what() << endl;
		return 1;
	}

	return 0;
}