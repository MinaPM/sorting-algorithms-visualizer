#include "global.hpp"
#include "./controls/ControlGroup.hpp"
#include "./Bar/BarShape.h"

void addControls(ControlGroup &controlGroup)
{
	controlGroup.addSlider("Count", Slider("Count", 1, 5, 1000));
	controlGroup.addSlider("Height", Slider("Height", 10, 100, Resources::window_size.y + Resources::padding.bottom * 2));
	controlGroup.addSlider("Width", Slider("Width", 1, 10, 40));
	controlGroup.addSlider("Spacing", Slider("Spacing", 1, 5, 40));
}

void bindControls(BarBoard &barboard, ControlGroup &barControls)
{

	barControls.sliders["Count"].setOnTrigger([&]()
											  { barboard.updateBarCount(); });
	barControls.sliders["Height"].setOnTrigger([&]()
											   { barboard.updateBarSize(); });
	barControls.sliders["Width"].setOnTrigger([&]()
											  { barboard.updateBarSize(); });
	barControls.sliders["Spacing"].setOnTrigger([&]()
												{ barboard.updateSpacing(); });

	barboard.center();
}

int main()
{
	Resources::initialize();

	ControlGroup barControls;
	addControls(barControls);

	BarBoard barboard(
		barControls.sliders["Count"].controlable,
		barControls.sliders["Height"].controlable,
		barControls.sliders["Width"].controlable,
		barControls.sliders["Spacing"].controlable);

	bindControls(barboard, barControls);

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
		// Resources::window.draw(slider);
		Resources::window.display();
	}
	return 0;
}