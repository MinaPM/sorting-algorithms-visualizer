#include "global.hpp"
#include "./controls/ControlGroup.hpp"
#include "./Bar/BarShape.h"

int main()
{
	Resources::initialize();

	ControlGroup barControls = ControlGroup();

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
		}

		Resources::window.clear();
		Resources::window.draw(barboard);
		Resources::window.draw(barControls);
		Resources::window.draw(Resources::debugText);
		Resources::window.display();
	}
	return 0;
}