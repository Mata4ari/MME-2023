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
		ERROR_ENTRY(111,"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,"Ошибка при создании файла out"),
		ERROR_ENTRY(114,"Ошибка открытия файла .out"),
		ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Таблица лексем: превышен допустимый размер таблицы"),
		ERROR_ENTRY(121, "Превышена длина имя переменной или недопустимое имя переменной"),
		ERROR_ENTRY(122, "Таблица идентификаторов: превышен допустимый размер таблицы"),
		ERROR_ENTRY(123, "Лексический анализ: нераспознанная лексема"),
		ERROR_ENTRY(124, "Лексический анализ: превышена длина литерала"),
		ERROR_ENTRY(125, "Лексический анализ: перезапись идентификатора"),
		ERROR_ENTRY(126, "Лексический анализ: неизвестная переменная"),
		ERROR_ENTRY(127, "Лексический анализ: превышена длина строкового литерала"),
		ERROR_ENTRY(128, "Не удалось создать файл с таблицами лексем и идентификаторов"),
		ERROR_ENTRY(129, "Лексический анализ: найдено несколько точек входа (main)"),
		ERROR_ENTRY(130, "Лексический анализ: превышено максимальное значение целочисленного типа"),
		ERROR_ENTRY(131,"Не задан тип переменной или тип возвращаемого значения функции"),
		ERROR_ENTRY(132,"Не найдено точки входа main"),
		ERROR_ENTRY(133,"Превышено максимальное допустимое число параметров функции"),
		ERROR_ENTRY(134,"Неверные параметры функции"),
		ERROR_ENTRY_NODEF(135),
		ERROR_ENTRY_NODEF(136),ERROR_ENTRY_NODEF(137),ERROR_ENTRY_NODEF(138),ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"Неверная структура программы"),
		ERROR_ENTRY(601,"Ошибочный оператор"),
		ERROR_ENTRY(602,"Ошибка в выражении"),
		ERROR_ENTRY(603,"Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605,"Ошибочный оператор внутри блока if/else"),
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