#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include <vector>
#include <string>

std::vector<std::string> MainMenu = {
	"Interaction mode",
	"Demo mode",
	"Benchmark mode",
	"Quit"
};

enum class MainAction
{
	Undefined = -1,
	Interactive,
	Demo,
	Benchmark,
	Quit
};

#endif // !INTERACTION_HPP

