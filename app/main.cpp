// #include "Header/PuzzleShape.h"
// #include "./Header/BarShape.h"
#include "global.hpp"
#include "./controls/ControlGroup.hpp"
#include "./Bar/BarShape.h"

/*
void solve()
{
	tileControlsPtr->setFunctions(SOLVE, false);
	tileControlsPtr->setFunctions(SHUFFLE, false);
	tileControlsPtr->setFunctions(SOLUTION, false);
	tileControlsPtr->sliders[SOLVE].enable();
	tileControlsPtr->checkboxes[UseThreadsCheckBox].disable();

	puzzlePtr->solve(tileControlsPtr->checkboxes[UseThreadsCheckBox].controlable);

	if (puzzlePtr->isSolved())
		tileControlsPtr->setFunctions(SOLUTION, true);
}
void shuffle()
{
	tileControlsPtr->setFunctions(SOLVE, false);
	tileControlsPtr->setFunctions(SHUFFLE, false);
	tileControlsPtr->setFunctions(SOLUTION, false);

	puzzlePtr->shuffle();

	tileControlsPtr->setFunctions(SOLVE, true);
	tileControlsPtr->setFunctions(SHUFFLE, true);
}
void display_solution()
{
	tileControlsPtr->setFunctions(SOLVE, false);
	tileControlsPtr->setFunctions(SHUFFLE, false);
	tileControlsPtr->setFunctions(SOLUTION, false);
	tileControlsPtr->sliders[SOLUTION].enable();

	puzzlePtr->display_solution();
	tileControlsPtr->setFunctions(SOLUTION, true);
}
*/
int main()
{

	// ControlGroup tileControls();
	// TileData tileData(roboto_font);
	// TileGrid tileShape(roboto_font, buffer, tileControls.checkboxes[SoundCheckBox].controlable);

	// Puzzle puzzle(tileControls, tileData, tileShape);
	Resources::initialize();
	// Resources::load_resourses();

	// std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	ControlGroup barControls = ControlGroup();

	//////////
	BarBoard barboard = BarBoard(
		barControls.sliders[COUNT].controlable,
		barControls.sliders[HEIGHT].controlable,
		barControls.sliders[WIDTH].controlable,
		barControls.sliders[SPACING].controlable

	);

	barControls.sliders[COUNT].setOnTrigger([&]()
											{ barboard.updateBarCount(); });
	barControls.sliders[HEIGHT].setOnTrigger([&]()
											 { barboard.updateBarSize(); });
	barControls.sliders[WIDTH].setOnTrigger([&]()
											{ barboard.updateBarSize(); });
	barControls.sliders[SPACING].setOnTrigger([&]()
											  { barboard.updateSpacing(); });

	barboard.center_bars();


	while (true)
	{
		sf::Event event;
		while (Resources::window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Resources::window.close();
				return 0;
			}
			barControls.somethingHappened(event);

			// switch (event.type)
			// {
			// case sf::Event::MouseButtonPressed:
			// 	slider.clickWithin(sf::Mouse::getPosition(Resources::window));
			// case sf::Event::MouseMoved:
			// 	slider.setValue(sf::Mouse::getPosition(Resources::window));
			// 	break;

			// case sf::Event::MouseButtonReleased:
			// 	slider.mouseReleased();
			// 	break;
			// }
		}

		Resources::window.clear();
		Resources::window.draw(barControls);
		Resources::window.draw(barboard);
		Resources::window.draw(Resources::debugText);
		// Resources::window.draw(slider);
		Resources::window.display();
	}
	return 0;
}