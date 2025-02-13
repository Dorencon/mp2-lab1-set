// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

#include <stdexcept>
#include <algorithm>

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if ((MaxPower != s.MaxPower) || (BitField != s.BitField))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if ((MaxPower != s.MaxPower) || (BitField != s.BitField))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet c (max(MaxPower, s.MaxPower));
	c.BitField = BitField | s.BitField;
	return c;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower)
	{
		throw runtime_error("");
	}
	TSet c (BitField);
	c.InsElem(Elem);
	return c;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet c (BitField);
	c.DelElem(Elem);
	return c;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet c (max(MaxPower, s.MaxPower));
	c.BitField = BitField & s.BitField;
	return c;
}

TSet TSet::operator~(void) // дополнение
{
	TSet c (MaxPower);
	c.BitField = ~BitField;
	return c;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int temp;
	istr >> temp;
	while (temp >= 0)
	{
		s.InsElem(temp);
		istr >> temp;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (size_t i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i))
		{
			ostr << i << " ";
		}
	}
	return ostr;
}