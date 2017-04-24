#include <iostream>
#include "EnumerateSources.hpp"

int main(void)
{
#if 0
	Superior_Goat goat;
	goat.AddAspect(Aspects::SUBLIME_HERD);
	goat.AddAspect(Aspects::SUBLIME_HERD);
	goat.Print();
		std::cout << std::endl;
	goat.AddAspect(Aspects::SUBLIME_EXOTIC);
	goat.AddAspect(Aspects::SUBLIME_EXOTIC);
	goat.Print();
		std::cout << std::endl;
	SourceList sl;
	goat.GetUpgrades(OCEAN, sl);
		std::cout << std::endl;
	for (auto it = sl.cbegin(); it != sl.cend(); ++it)
	{
		(*it)->Print();
		std::cout << std::endl;
	}
	return 0;
#endif
	std::array<unsigned, SOURCE_TYPE_T_MAX> best_source_level = {0};
	enumerateSources(best_source_level);
	for (size_t i = BUILDING+1; i < SOURCE_TYPE_T_MAX; i++)
	{
		std::cout << "Source " << i;
		if (!best_source_level[i])
			std::cout << " not seen" << std::endl;
		else
			std::cout << " best level=" << best_source_level[i] << std::endl;
	}
	return 0;
}
