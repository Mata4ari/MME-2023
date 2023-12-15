#include "stdafx.h"

namespace Error 
{
	Error errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"),
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY(101,"Неверно указан параметр"),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"Лексический анализ: Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,"Таблица лексем: превышен допустимый размер таблицы"),
		ERROR_ENTRY(114,"Лексический анализ: Превышена длина имя переменной или недопустимое имя переменной"),
		ERROR_ENTRY(115,"Таблица идентификаторов: превышен допустимый размер таблицы"),
		ERROR_ENTRY(116,"Лексический анализ: нераспознанная лексема"),
		ERROR_ENTRY(117,"Лексический анализ: превышена длина литерала"),
		ERROR_ENTRY(118,""),
		ERROR_ENTRY(119,""),
		ERROR_ENTRY(120, "Лексический анализ: превышена длина строкового литерала"),
		ERROR_ENTRY(121, "Не удалось создать файл с таблицами лексем и идентификаторов"),
		ERROR_ENTRY(122, ""),
		ERROR_ENTRY(123, "Лексический анализ: превышено максимальное значение целочисленного типа"),
		ERROR_ENTRY(124, "Лексический анализ: Не задан тип переменной или тип возвращаемого значения функции"),
		ERROR_ENTRY(125, ""),
		ERROR_ENTRY(126, "Лексический анализ: Превышено максимальное допустимое число параметров функции"),
		ERROR_ENTRY(127, ""),
		ERROR_ENTRY(128, ""),
		ERROR_ENTRY(129, ""),
		ERROR_ENTRY(130,"Семантический анализ: Неверные параметры функции"),
		ERROR_ENTRY(131,"Семантический анализ: Неверный тип возвращаемого значения функции"),
		ERROR_ENTRY(132,"Семантический анализ: Разнотипные значения в выражении"),
		ERROR_ENTRY(133,"Семантический анализ: Недопустимая операция над строкой"),
		ERROR_ENTRY(134,"Семантический анализ: Встречена переменная а подразумевался вызов функции"),
		ERROR_ENTRY(135,"Семантический анализ: неизвестная переменная"),
		ERROR_ENTRY(136,"Семантический анализ: перезапись идентификатора"),
		ERROR_ENTRY(137,"Семантический анализ: найдено несколько точек входа (main)"),
		ERROR_ENTRY(138,"Семантический анализ: Не найдено точки входа main"),
		ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY(150,"Ошибка открытия выходного файла, параметр -out:"),
		ERROR_ENTRY(151,"Переполнение при сложении"),
		ERROR_ENTRY(152,"Переполнение при умножении"),
		ERROR_ENTRY(153,"Недопустимое значение разности"),
		ERROR_ENTRY(154,"Деление на 0"),
		ERROR_ENTRY_NODEF(155),
		ERROR_ENTRY_NODEF(156),
		ERROR_ENTRY_NODEF(157),
		ERROR_ENTRY_NODEF(158),
		ERROR_ENTRY_NODEF(159),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"Неверная структура программы"),
		ERROR_ENTRY(601,"Ошибочный оператор"),
		ERROR_ENTRY(602,"Ошибка в выражении"),
		ERROR_ENTRY(603,"Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605,"Ошибочное выражение внутри блока if/else"),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),

		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),
		ERROR_ENTRY_NODEF100(900)
	};

	Error geterror(int id)
	{
		Error e;
		if (id<0 || id>=ERROR_MAX_ENTRY)
		{
			e = errors[0];
			e.inext.col = -1;
			e.inext.line = -1;
			return e;
		}
		else
		{
			e = errors[id];
			e.inext.col = -1;
			e.inext.line = -1;
			return e;
		}
	}


	Error geterrorin(int id, int line = -1, int col = -1)
	{
		Error e;
		if (id < 0 || id >= ERROR_MAX_ENTRY)
		{
			e = errors[0];
			e.inext.col = -1;
			e.inext.line = -1;
			return e;
		}
		else
		{
			int i = 0;
			e.id = id;
			while (errors[id].message[i] != '\0')
			{
				e.message[i] = errors[id].message[i];
				i++;
			}
			e.message[i] = '\0';
			e.inext.line = line;
			e.inext.col = col;
			return e;
		}
	}
}