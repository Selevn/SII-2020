#include "Error.h"
namespace Error
{
	//се ия ошибок 0-99 - системные ошибки
	// 100 - 109 - ошибки па амет ов
	// 110 - 119 - ошибки отк ытия и чтения файлов
	// 120 - 129 - лексические ошибки
	// 600 - 610  - синтаксическая ошибка
	// 700 - 710  - семантическая ошибкаошибка
	ERROR errors[ERROR_MAX_ENTRY] = //таблица ошибок
	{
		ERROR_ENTRY(0, "[SYS]: Недопустимый код ошибки"), // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "[SYS]: Системный сбой"), //
		ERROR_ENTRY(2, "[SYS]: Недопустимое количество ошибок"),//
		ERROR_ENTRY(3, "[SYS]: "),
		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),
		ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),
		ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[PARM]: Параметр -in должен быть задан"),//+
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "[PARM]: Превышена длина входного параметра"),//+
		ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "[IN]: Ошибка при открытии файла с исходным кодом (-in)"),//+
		ERROR_ENTRY(111, "[IN]: Недопустимый символ в исходном файле (-in)"),//+
		ERROR_ENTRY(112, "[IN]: Превышен предел размера входного файла (-in)"),//+
		ERROR_ENTRY(113, "[IN]: Превышен предел размера лексемы"),//+
		ERROR_ENTRY(114, "[IN]: Отсуствует закрывающая кавычка"),//
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "[LA]: Ошибка при разборе токена"),//+
		ERROR_ENTRY(121, "[LA]: Используется необъявленный идентификатор"),//+
		ERROR_ENTRY(122, "[LA]: Итендификатор не имеет типа"),//+
		ERROR_ENTRY(123, "[LA]: Повторное объявление итедификатора"),//+
		//ERROR_ENTRY_NODEF(123),
		//ERROR_ENTRY_NODEF(123),
		ERROR_ENTRY(124, "[LA]: Отсутствует точка входа"),//+
		ERROR_ENTRY(125, "[LA]: Обнаружена вторая точка входа"),//+
		ERROR_ENTRY(126, "[LA]: Ошибка закрывающей скобки - открывающая скобка не обработана"),//+
		ERROR_ENTRY(127, "[LA]: Ошибка закрывающей фигурной скобки - открывающая скобка не обработана"),//+
		//ERROR_ENTRY_NODEF(126),
		//ERROR_ENTRY_NODEF(127),
		ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "[ITable]: Ошибка создания таблицы итендификаторов: размер превышает допустимое значение"),//+
		ERROR_ENTRY(131, "[LTable]: Ошибка создания таблицы литералов: размер превышает допустимое значение"),//+
		ERROR_ENTRY(132, "[ITable]: Ошибка добавления в таблицу лексем: превышен макимальный размер таблицы"),//+
		ERROR_ENTRY(133, "[LTable]: Ошибка добавления в таблицу итендификаторов: превышен макимальный размер таблицы"),//+
		ERROR_ENTRY(134, "[ITable]: Ошибка получения элемента из таблицы итендификаторов: элемент не создан или индекс выходит за границы массива"),//+
		ERROR_ENTRY(135, "[LTable]: Ошибка получения элемента из таблицы литералов: элемент не создан или индекс выходит за границы массива"),//+
		ERROR_ENTRY_NODEF(136),
		ERROR_ENTRY_NODEF(137),
		ERROR_ENTRY_NODEF(138),
		ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600, "[SA]: Неверная структура программы"),
		ERROR_ENTRY(601, "[SA]: Ошибочный оператор"),
		ERROR_ENTRY(602, "[SA]: Ошибка в выражении"),
		ERROR_ENTRY(603, "[SA]: Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "[SA]: Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605, "[SA]: Ошибка знака в выражении"),
		ERROR_ENTRY(606, "[SA]: Ошибка в синтаксическом анализе"),
		ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY(609, "[SA]: Обнаружена синтаксическая ошибка(смотри журнал Log)"),
		ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),
		ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),

		ERROR_ENTRY(700, "[Semantic]: Повторное объявление идентификатора"),//+
		ERROR_ENTRY(701, "[Semantic]: Ошибка в возвращаемом значении"),//+
		ERROR_ENTRY(702, "[Semantic]: Ошибка в передаваемых значениях в функции: количество параметров не совпадает"),//+
		ERROR_ENTRY(703, "[Semantic]: Ошибка в передаваемых значениях в функции: типы параметров не совпадают"),//+
		ERROR_ENTRY(704, "[Semantic]: Нарушены типы данных в выражении"),//+

		ERROR_ENTRY_NODEF(705),	ERROR_ENTRY_NODEF(706),
		ERROR_ENTRY_NODEF(707),	ERROR_ENTRY_NODEF(708),	ERROR_ENTRY_NODEF(709),
		ERROR_ENTRY_NODEF10(710),ERROR_ENTRY_NODEF10(720),ERROR_ENTRY_NODEF10(730),ERROR_ENTRY_NODEF10(740),
		ERROR_ENTRY_NODEF10(750),ERROR_ENTRY_NODEF10(760),ERROR_ENTRY_NODEF10(770),ERROR_ENTRY_NODEF10(780),
		ERROR_ENTRY_NODEF10(790),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	/*ERROR_ENTRY(0,"Недопустимый код ошибки"),
	ERROR_ENTRY(1,"Системный сбой"),
	ERROR_ENTRY_NODEF(2),
	ERROR_ENTRY_NODEF(3),
	ERROR_ENTRY_NODEF(4),
	ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6),
	ERROR_ENTRY_NODEF(7),
	ERROR_ENTRY_NODEF(8),
	ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10),
	ERROR_ENTRY_NODEF10(20),
	ERROR_ENTRY_NODEF10(30),
	ERROR_ENTRY_NODEF10(40),
	ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60),
	ERROR_ENTRY_NODEF10(70),
	ERROR_ENTRY_NODEF10(80),
	ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100, "парамет -in должен быть задан"),
	ERROR_ENTRY_NODEF(101),
	ERROR_ENTRY_NODEF(102),
	ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104, "превышена длина входного параметра"),
	ERROR_ENTRY_NODEF(105),
	ERROR_ENTRY_NODEF(106),
	ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108),
	ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110,"ошибка открытия файла с исходным кодом (-in)"),
	ERROR_ENTRY(111,"недопустимый символ в исходном файле"),
	ERROR_ENTRY(112,"ошибка создания файла потока (-log)"),
	ERROR_ENTRY_NODEF(113),
	ERROR_ENTRY_NODEF(114),
	ERROR_ENTRY_NODEF(115),
	ERROR_ENTRY_NODEF(116),
	ERROR_ENTRY_NODEF(117),
	ERROR_ENTRY_NODEF(118),
	ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY(120, "Цепочка не распознана"),
	ERROR_ENTRY_NODEF(121),
	ERROR_ENTRY_NODEF(122),
	ERROR_ENTRY_NODEF(123),
	ERROR_ENTRY_NODEF(124),
	ERROR_ENTRY_NODEF(125),
	ERROR_ENTRY_NODEF(126),
	ERROR_ENTRY_NODEF(127),
	ERROR_ENTRY_NODEF(128),
	ERROR_ENTRY_NODEF(129),
	ERROR_ENTRY(130, "Ошибка создания таблицы итендификаторов: размер превышает допустимое значение"),
	ERROR_ENTRY(131, "Ошибка создания таблицы литералов: размер превышает допустимое значение"),
	ERROR_ENTRY(132, "Ошибка добавления в таблицу лексем: превышен макимальный размер таблицы"),
	ERROR_ENTRY(133, "Ошибка добавления в таблицу итендификаторов: превышен макимальный размер таблицы"),
	ERROR_ENTRY(134, "Ошибка получения элемента из таблицы итендификаторов: элемент не создан или индекс выходит за границы массива" ),
	ERROR_ENTRY(135, "Ошибка получения элемента из таблицы литералов: элемент не создан или индекс выходит за границы массива"),
	ERROR_ENTRY_NODEF(136),
	ERROR_ENTRY_NODEF(137),
	ERROR_ENTRY_NODEF(138),
	ERROR_ENTRY_NODEF(139),
	ERROR_ENTRY_NODEF10(140),
	ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160),
	ERROR_ENTRY_NODEF10(170),
	ERROR_ENTRY_NODEF10(180),
	ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY_NODEF100(200),
	ERROR_ENTRY_NODEF100(300),
	ERROR_ENTRY_NODEF100(400),
	ERROR_ENTRY_NODEF100(500),
	ERROR_ENTRY(600,"Неверная структура программы"),
	ERROR_ENTRY(601,"Неверная структура программы"),
	ERROR_ENTRY(602,"Неверная структура программы"),
	ERROR_ENTRY(603,"Неверная структура программы"),
	ERROR_ENTRY(604,"Неверная структура программы"),
	ERROR_ENTRY_NODEF(605),
	ERROR_ENTRY_NODEF(606),
	ERROR_ENTRY_NODEF(607),
	ERROR_ENTRY_NODEF(608),
	ERROR_ENTRY_NODEF(609),
	ERROR_ENTRY_NODEF10(610),
	ERROR_ENTRY_NODEF10(620),
	ERROR_ENTRY_NODEF10(630),
	ERROR_ENTRY_NODEF10(640),
	ERROR_ENTRY_NODEF10(650),
	ERROR_ENTRY_NODEF10(660),
	ERROR_ENTRY_NODEF10(670),
	ERROR_ENTRY_NODEF10(680),
	ERROR_ENTRY_NODEF10(690),
	ERROR_ENTRY_NODEF100(700),
	ERROR_ENTRY_NODEF100(800),
	ERROR_ENTRY_NODEF100(900),*/
	};
	ERROR geterror(int id)
	{
		ERROR out;

		if (0 > id || id > ERROR_MAX_ENTRY)
			out = errors[0];
		else
			out = errors[id];
		return out;
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR out;

		if (0 > id || id > ERROR_MAX_ENTRY)
			out = errors[0];
		else
			out = errors[id];
		out.inext.line = line;
		out.inext.col = col;
		return out;
	}
}