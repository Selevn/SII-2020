#pragma once
#include "LEX.h"
#include "Out.h"

namespace CG {
	void Generate(LEX::LEX t);
	void Head(std::ofstream* stream, LEX::LEX t);
	void Constants(std::ofstream* stream, LEX::LEX t);
	void Data(std::ofstream* stream, LEX::LEX t);
	void WriteFunctions(std::ofstream* stream, LEX::LEX t);
	void Code(std::ofstream* stream, LEX::LEX t);
}