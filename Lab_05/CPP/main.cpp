#include <iostream>
#include "../Include/Interaction.hpp"

int main()
{
	FlawlessMenu::Menu::Filler = "============";
	FlawlessMenu::Menu::Selector = "-->";
	FlawlessMenu::Menu::GetKeyFunc = _getch;

	auto Menu = new FlawlessMenu::Menu("Lab 05");

	auto demoMenu = new FlawlessMenu::Menu("Demo mode");
	auto interMenu = new FlawlessMenu::Menu("Iteractive mode");
	auto benchMenu = new FlawlessMenu::Menu("Benchmark mode");

	auto createGraphMenu = new FlawlessMenu::Menu("Create Graph");
	auto fillGraphMenuM = new FlawlessMenu::Menu("Fill Graph");
	auto fillGraphMenuS = new FlawlessMenu::Menu("Fill Graph");

	interMenu->Add("Create new graph", createGraphMenu);
	interMenu->Add("Show graph", ShowGraph);
	interMenu->Add("Check connectivity", CheckConnectivity);
	interMenu->Add("Depth First Search Any", DFSA);
	interMenu->Add("Depth First Search Sorted", DFSS);
	interMenu->Add("Dijkstra algorytm", Dijkstra);
	interMenu->Add("Kahn's sort", KahnsSort);
	interMenu->Add("Find Minimum Spanning Tree", FindMST);
	interMenu->Add("Kruskal Minimum Spanning Tree", KruskalMST);

	createGraphMenu->Add("Matrix graph", fillGraphMenuM);
	createGraphMenu->Add("Structure graph", fillGraphMenuS);

	fillGraphMenuM->Add("Random graph", FillMatrixRandom);
	fillGraphMenuM->Add("Type by hand", FillMatrixByHand);

	fillGraphMenuS->Add("Random graph", FillStructureRandom);
	fillGraphMenuS->Add("Type by hand", FillStructureByHand);







	Menu->Add("Interactive mode", interMenu);
	Menu->Add("Demo mode", Demo);
	Menu->Add("Benchmark mode", Benchmark);

	Menu->Start();

}