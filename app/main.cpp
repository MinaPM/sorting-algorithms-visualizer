#include "global.hpp"
#include "./controls/ControlGroup.hpp"
#include "./Bar/BarShape.h"
#include "./Bar/BarBoard.h"

void addControls(ControlGroup &controlGroup)
{
	controlGroup.addSlider("Count", Slider("Count", 1, 600, 1000));
	controlGroup.addSlider("Max Height", Slider("Max Height", 10, 300, Resources::window_size.y + Resources::padding.bottom * 2));
	controlGroup.addSlider("Width", Slider("Width", 1, 1, 40));
	controlGroup.addSlider("Spacing", Slider("Spacing", 1, 1, 40));
	controlGroup.addSlider("Speed", Slider("Speed", 1, 5, 100));
	controlGroup.addButton("Shuffle");
	controlGroup.addButton("Sort");
}

void bindControls(BarBoard &barboard, ControlGroup &barControls)
{
	barControls.sliders["Count"].setOnTrigger([&]()
											  { barboard.updateBarCount(); });
	barControls.sliders["Max Height"].setOnTrigger([&]()
												   { barboard.updateBarSize(); });
	barControls.sliders["Width"].setOnTrigger([&]()
											  { barboard.updateBarSize(); });
	barControls.sliders["Spacing"].setOnTrigger([&]()
												{ barboard.updateSpacing(); });
	barControls.sliders["Speed"].setOnTrigger([&]()
											  { barboard.updateSpacing(); });
	(barControls.buttons["Shuffle"])->setOnTrigger([&]()
												   { barboard.shuffle(); });
	(barControls.buttons["Sort"])->setOnTrigger([&]()
												{ barboard.sort(); });

	barboard.center();
}

int main()
{
	Resources::initialize();

	ControlGroup barControls;
	addControls(barControls);

	BarBoard barboard(
		barControls.sliders["Count"].controlable,
		barControls.sliders["Max Height"].controlable,
		barControls.sliders["Width"].controlable,
		barControls.sliders["Spacing"].controlable,
		barControls.sliders["Speed"].controlable

	);

	bindControls(barboard, barControls);
	barboard.shuffle();

	// events
	const auto onClose = [](const sf::Event::Closed &)
	{
		Resources::window.close();
		// return 0;
	};

	const auto onMouseButtonPressed = [&barControls](sf::Event::MouseButtonPressed)
	{
		barControls.mouseClicked();
	};
	const auto onMouseButtonReleased = [&barControls](sf::Event::MouseButtonReleased)
	{
		barControls.mouseReleased();
	};
	const auto onMouseMoved = [&barControls](sf::Event::MouseMoved)
	{
		barControls.update();
	};

	while (Resources::window.isOpen())
	{

		Resources::window.handleEvents(onClose, onMouseButtonPressed, onMouseButtonReleased, onMouseMoved);

		Resources::window.clear();
		Resources::window.draw(barboard);
		Resources::window.draw(barControls);
		Resources::window.draw(Resources::debugText);
		Resources::window.display();
	}
	return 0;
}