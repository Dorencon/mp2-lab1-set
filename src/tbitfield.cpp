// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#include <algorithm>
#include <stdexcept>

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw runtime_error("");
	}
	BitLen = len;
	MemLen = BitLen / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) : TBitField(bf.BitLen)// конструктор копирования
{
	for (size_t i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[](pMem);
	BitLen = 0;
	MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	size_t temp = n % (sizeof(TELEM) * 8);
	int t = 1;
	t = t << temp;
	return t;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
	{
		throw runtime_error("");
	}
	int t1 = GetMemIndex(n);
	int t2 = GetMemMask(n);
	pMem[t1] = pMem[t1] | t2;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
	{
		throw runtime_error("");
	}
	int t1 = GetMemIndex(n);
	int t2 = ~GetMemMask(n);
	pMem[t1] = pMem[t1] & t2;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
	{
		throw runtime_error("");
	}
	int t1 = GetMemIndex(n);
	int t2 = GetMemMask(n);
	return int(pMem[t1] & t2);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		delete[](pMem);
		BitLen = BitLen;
		MemLen = MemLen;
	}
	for (size_t i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
  {
	  return 0;
  }
  for (size_t i = 0; i < MemLen; i++)
  {
	  if (pMem[i] != bf.pMem[i])
	  {
		  return 0;
	  }
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
  {
	  return 1;
  }
  for (size_t i = 0; i < MemLen; i++)
  {
	  if (pMem[i] != bf.pMem[i])
	  {
		  return 1;
	  }
  }
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField c(max(BitLen, bf.BitLen));
	for (size_t i = 0; i < min(MemLen, bf.MemLen); i++)
	{
		c.pMem[i] = pMem[i]|bf.pMem[i];
	}
	if (MemLen < bf.MemLen)
	{
		for (size_t i = MemLen; i < bf.MemLen; i++)
		{
			c.pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		for (size_t i = bf.MemLen; i < MemLen; i++)
		{
			c.pMem[i] = pMem[i];
		}
	}
	return c;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField c(max(BitLen, bf.BitLen));
	for (size_t i = 0; i < min(MemLen, bf.MemLen); i++)
	{
		c.pMem[i] = pMem[i]&bf.pMem[i];
	}
	return c;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField c(BitLen);
	for (size_t i = 0; i < MemLen; i++)
	{
		c.pMem[i] = ~pMem[i];
	}
	return c;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char c;
	istr >> c;
	while ((c == '0') || (c == '1'))
	{
		if (c == '1')
		{
			bf.SetBit(i);
		}
		else
		{
			bf.ClrBit(i);
		}
		i++;
		istr >> c;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (size_t i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}