#pragma once


#define FUNCTION(string) string, 5,			  \
			FST::NODE(1, FST::RELATION('f', 1)),  \
			FST::NODE(1, FST::RELATION('u', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('c', 4)),  \
			FST::NODE()

#define ELSE_G(string) string, 5,			  \
			FST::NODE(1, FST::RELATION('e', 1)),  \
			FST::NODE(1, FST::RELATION('l', 2)),  \
			FST::NODE(1, FST::RELATION('s', 3)),  \
			FST::NODE(1, FST::RELATION('e', 4)),  \
			FST::NODE()

#define IF_G(string) string, 3,			  \
			FST::NODE(1, FST::RELATION('i', 1)),  \
			FST::NODE(1, FST::RELATION('f', 2)),  \
			FST::NODE()

#define MAIN(string) string, 5,			  \
			FST::NODE(1, FST::RELATION('m', 1)),  \
			FST::NODE(1, FST::RELATION('a', 2)),  \
			FST::NODE(1, FST::RELATION('i', 3)),  \
			FST::NODE(1, FST::RELATION('n', 4)),  \
			FST::NODE()	

#define INTEGER(string) string, 5,			  \
			FST::NODE(1, FST::RELATION('u', 1)),  \
			FST::NODE(1, FST::RELATION('i', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('t', 4)),  \
			FST::NODE()		

#define STRING(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('s', 1)),  \
			FST::NODE(1, FST::RELATION('t', 2)),  \
			FST::NODE(1, FST::RELATION('r', 3)),  \
			FST::NODE(1, FST::RELATION('i', 4)),  \
			FST::NODE(1, FST::RELATION('n', 5)),  \
			FST::NODE(1, FST::RELATION('g', 6)),  \
			FST::NODE()		

#define RETURN(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('r', 1)),  \
			FST::NODE(1, FST::RELATION('e', 2)),  \
			FST::NODE(1, FST::RELATION('t', 3)),  \
			FST::NODE(1, FST::RELATION('u', 4)),  \
			FST::NODE(1, FST::RELATION('r', 5)),  \
			FST::NODE(1, FST::RELATION('n', 6)),  \
			FST::NODE()	

#define WRITE(string) string, 6,				  \
			FST::NODE(1, FST::RELATION('w', 1)),  \
			FST::NODE(1, FST::RELATION('r', 2)),  \
			FST::NODE(1, FST::RELATION('i', 3)),  \
			FST::NODE(1, FST::RELATION('t', 4)),  \
			FST::NODE(1, FST::RELATION('e', 5)),  \
			FST::NODE()	

#define WRITE_LINE(string) string, 10,				  \
			FST::NODE(1, FST::RELATION('w', 1)),  \
			FST::NODE(1, FST::RELATION('r', 2)),  \
			FST::NODE(1, FST::RELATION('i', 3)),  \
			FST::NODE(1, FST::RELATION('t', 4)),  \
			FST::NODE(1, FST::RELATION('e', 5)),  \
			FST::NODE(1, FST::RELATION('l', 6)),  \
			FST::NODE(1, FST::RELATION('i', 7)),  \
			FST::NODE(1, FST::RELATION('n', 8)),  \
			FST::NODE(1, FST::RELATION('e', 9)),  \
			FST::NODE()	

#define IDENTIFICATOR(string) string, 2, \
			FST::NODE(53, \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('z', 1), \
		FST::RELATION('A', 1),	\
		FST::RELATION('B', 1),	\
		FST::RELATION('C', 1),	\
		FST::RELATION('D', 1),	\
		FST::RELATION('E', 1),	\
		FST::RELATION('F', 1),	\
		FST::RELATION('G', 1),	\
		FST::RELATION('H', 1),	\
		FST::RELATION('I', 1),	\
		FST::RELATION('J', 1),	\
		FST::RELATION('K', 1),	\
		FST::RELATION('L', 1),	\
		FST::RELATION('M', 1),	\
		FST::RELATION('N', 1),	\
		FST::RELATION('O', 1),	\
		FST::RELATION('P', 1),	\
		FST::RELATION('Q', 1),	\
		FST::RELATION('R', 1),	\
		FST::RELATION('S', 1),	\
		FST::RELATION('T', 1),	\
		FST::RELATION('U', 1),	\
		FST::RELATION('V', 1),	\
		FST::RELATION('W', 1),	\
		FST::RELATION('X', 1),	\
		FST::RELATION('Y', 1),	\
		FST::RELATION('Z', 1),	\
	FST::RELATION('_', 1)), \
FST::NODE(63, \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('A', 1),	\
	FST::RELATION('B', 1),	\
	FST::RELATION('C', 1),	\
	FST::RELATION('D', 1),	\
	FST::RELATION('E', 1),	\
	FST::RELATION('F', 1),	\
	FST::RELATION('G', 1),	\
	FST::RELATION('H', 1),	\
	FST::RELATION('I', 1),	\
	FST::RELATION('J', 1),	\
	FST::RELATION('K', 1),	\
	FST::RELATION('L', 1),	\
	FST::RELATION('M', 1),	\
	FST::RELATION('N', 1),	\
	FST::RELATION('O', 1),	\
	FST::RELATION('P', 1),	\
	FST::RELATION('Q', 1),	\
	FST::RELATION('R', 1),	\
	FST::RELATION('S', 1),	\
	FST::RELATION('T', 1),	\
	FST::RELATION('U', 1),	\
	FST::RELATION('V', 1),	\
	FST::RELATION('W', 1),	\
	FST::RELATION('X', 1),	\
	FST::RELATION('Y', 1),	\
	FST::RELATION('Z', 1),	\
	FST::RELATION('z', 1), \
	FST::RELATION('_', 1), \
	FST::RELATION('0', 1), \
	FST::RELATION('1', 1), \
	FST::RELATION('2', 1), \
	FST::RELATION('3', 1), \
	FST::RELATION('4', 1), \
	FST::RELATION('5', 1), \
	FST::RELATION('6', 1), \
	FST::RELATION('7', 1), \
	FST::RELATION('8', 1), \
	FST::RELATION('9', 1)), \
	FST::NODE()

#define STRING_LITERAL(string) string, 3,	\
		FST::NODE(1, FST::RELATION('\'', 1)),	\
		FST::NODE(144,	\
		FST::RELATION(' ', 1),	\
		FST::RELATION('a', 1),	\
		FST::RELATION('b', 1),	\
		FST::RELATION('c', 1),	\
		FST::RELATION('d', 1),	\
		FST::RELATION('e', 1),	\
		FST::RELATION('f', 1),	\
		FST::RELATION('g', 1),	\
		FST::RELATION('h', 1),	\
		FST::RELATION('i', 1),	\
		FST::RELATION('j', 1),	\
		FST::RELATION('k', 1),	\
		FST::RELATION('l', 1),	\
		FST::RELATION('m', 1),	\
		FST::RELATION('n', 1),	\
		FST::RELATION('o', 1),	\
		FST::RELATION('p', 1),	\
		FST::RELATION('q', 1),	\
		FST::RELATION('r', 1),	\
		FST::RELATION('s', 1),	\
		FST::RELATION('t', 1),	\
		FST::RELATION('u', 1),	\
		FST::RELATION('v', 1),	\
		FST::RELATION('w', 1),	\
		FST::RELATION('x', 1),	\
		FST::RELATION('y', 1),	\
		FST::RELATION('z', 1),	\
		FST::RELATION('A', 1),	\
		FST::RELATION('B', 1),	\
		FST::RELATION('C', 1),	\
		FST::RELATION('D', 1),	\
		FST::RELATION('E', 1),	\
		FST::RELATION('F', 1),	\
		FST::RELATION('G', 1),	\
		FST::RELATION('H', 1),	\
		FST::RELATION('I', 1),	\
		FST::RELATION('J', 1),	\
		FST::RELATION('K', 1),	\
		FST::RELATION('L', 1),	\
		FST::RELATION('M', 1),	\
		FST::RELATION('N', 1),	\
		FST::RELATION('O', 1),	\
		FST::RELATION('P', 1),	\
		FST::RELATION('Q', 1),	\
		FST::RELATION('R', 1),	\
		FST::RELATION('S', 1),	\
		FST::RELATION('T', 1),	\
		FST::RELATION('U', 1),	\
		FST::RELATION('V', 1),	\
		FST::RELATION('W', 1),	\
		FST::RELATION('X', 1),	\
		FST::RELATION('Y', 1),	\
		FST::RELATION('Z', 1),	\
		FST::RELATION('0', 1),	\
		FST::RELATION('1', 1),	\
		FST::RELATION('2', 1),	\
		FST::RELATION('3', 1),	\
		FST::RELATION('4', 1),	\
		FST::RELATION('5', 1),	\
		FST::RELATION('6', 1),	\
		FST::RELATION('7', 1),	\
		FST::RELATION('8', 1),	\
		FST::RELATION('9', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('�', 1),	\
		FST::RELATION('=', 1),	\
		FST::RELATION('+', 1),	\
		FST::RELATION('-', 1),	\
		FST::RELATION('*', 1),	\
		FST::RELATION('/', 1),	\
		FST::RELATION('(', 1),	\
		FST::RELATION(')', 1),	\
		FST::RELATION('{', 1),	\
		FST::RELATION('}', 1),	\
		FST::RELATION(';', 1),	\
		FST::RELATION(',', 1),	\
		FST::RELATION('?', 1),	\
		FST::RELATION('!', 1),	\
		FST::RELATION('\'', 2)),\
		FST::NODE()

#define INTEGER_LITERAL(string) string, 1,	\
	FST::NODE(10,	FST::RELATION('0', 0),	\
					FST::RELATION('1', 0),	\
					FST::RELATION('2', 0),	\
					FST::RELATION('3', 0),	\
					FST::RELATION('4', 0),	\
					FST::RELATION('5', 0),	\
					FST::RELATION('6', 0),	\
					FST::RELATION('7', 0),	\
					FST::RELATION('8', 0),	\
					FST::RELATION('9', 0)),	\
					FST::NODE()

#define INTEGER_LITERAL16(string) string, 3,	 \
			FST::NODE(1, FST::RELATION('0', 1)),  \
			FST::NODE(1, FST::RELATION('x', 2)),  \
			FST::NODE(15, \
			FST::RELATION('1', 2), \
			FST::RELATION('2', 2), \
			FST::RELATION('3', 2), \
			FST::RELATION('4', 2), \
			FST::RELATION('5', 2), \
			FST::RELATION('6', 2), \
			FST::RELATION('7', 2), \
			FST::RELATION('8', 2), \
			FST::RELATION('9', 2), \
			FST::RELATION('0', 2),  \
			FST::RELATION('a', 2), \
			FST::RELATION('b', 2), \
			FST::RELATION('c', 2), \
			FST::RELATION('d', 2), \
			FST::RELATION('f', 2)),  \
			FST::NODE()	