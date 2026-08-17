#pragma once
#include "../global.hpp"
#include "../../controls/ControlGroup.hpp"
#include "../../graphics/bar/BarBoard.hpp"

#include "../smartArray.hpp"

#include "../../algorithms/SortAlgorithm.hpp"
#include "../../algorithms/BubbleSort.hpp"
#include "../../algorithms/HeapSort.hpp"
#include "../../algorithms/InsertionSort.hpp"
#include "../../algorithms/MergeSort.hpp"
#include "../../algorithms/QuickSort.hpp"
class Application
{
public:
    BarBoard barboard;
    SmartArray<BarShape> bars;
    Text debugText;
    ControlGroup barControls;

    InsertionSort insersion;
    MergeSort mergeSort;
    HeapSort heapSort;
    QuickSort quickSort;
    BubbleSort bubbleSort;

    Algorithm *sortingAlgorithm;

    void setAlgorithm(int algorithmChoice=0)
    {
        switch (algorithmChoice)
        {
        case 0:
            sortingAlgorithm = &insersion;
            break;
        case 1:
            sortingAlgorithm = &heapSort;
            break;
        case 2:
            sortingAlgorithm = &mergeSort;
            break;
        case 3:
            sortingAlgorithm = &quickSort;
            break;
        case 4:
            sortingAlgorithm = &bubbleSort;
            break;

        default:
            sortingAlgorithm = &insersion;
            break;
        }
    }

    Application() : bars(), insersion(bars), mergeSort(bars), heapSort(bars), quickSort(bars), bubbleSort(bars)
    {
        if (Resources::initialize())
        {
            Resources::windowRunning = false;
            return;
        }

        setAlgorithm();

        // bars.resize(40, BarShape());
        createControls();
        barboard = BarBoard(
            &barControls.sliders["Count"].controlable,
            &barControls.sliders["Max Height"].controlable,
            &barControls.sliders["Width"].controlable,
            &barControls.sliders["Spacing"].controlable,
            bars);
        
        bindControls(barboard);

    }

    void run()
    {

        while (Resources::windowRunning)
        {


            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    Resources::windowRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    barControls.mouseClicked();
                    break;
                case SDL_MOUSEBUTTONUP:
                    barControls.mouseReleased();
                    break;
                case SDL_MOUSEMOTION:
                    barControls.update();
                    break;
                }
            }

            SDL_SetRenderDrawColor(Resources::gRenderer, 20, 20, 20, 255);
            SDL_RenderClear(Resources::gRenderer);

            barboard.draw();
            barControls.draw(Resources::gRenderer);


            SDL_RenderPresent(Resources::gRenderer);


#ifndef __EMSCRIPTEN__
            SDL_Delay(16);
#endif
        }
    }

    void createControls()
    {
        barControls.addSlider("Count", Slider("Count", 1, 600, 1000));

        barControls.addSlider("Max Height", Slider("Max Height", 10, 300, Resources::window_size.y + Resources::padding.bottom * 2));
        barControls.addSlider("Width", Slider("Width", 1, 1, 40));
        barControls.addSlider("Spacing", Slider("Spacing", 0, 1, 40));
        barControls.addSlider("Speed", Slider("Speed", 1, 2, 5));
        barControls.addButton("Shuffle");
        barControls.addButton("Sort");
        barControls.addCheckGroup("Sorting Algorithm");
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Insertion"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Heap"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Merge"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Quick"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Bubble"));

        barControls.setPosition({20, 100});
    }

    void bindControls(BarBoard &barboard)
    {
        barControls.sliders["Count"].setOnTrigger([&]()
                                                  { barboard.updateBarCount(); });
        barControls.sliders["Max Height"].setOnTrigger([&]()
                                                       { barboard.updateBarSize(); });
        barControls.sliders["Width"].setOnTrigger([&]()
                                                  { barboard.updateBarSize(); });
        barControls.sliders["Spacing"].setOnTrigger([&]()
                                                    { barboard.updateSpacing(); });

        barControls.buttons["Shuffle"]->setOnTrigger([&]()
                                                     { bars.shuffle(); });
        barControls.buttons["Sort"]->setOnTrigger([&]()
                                                  { sortingAlgorithm->sort(); });

        barControls.checkGroups["Sorting Algorithm"].setOnTrigger([&]
                                                                  { setAlgorithm(barControls.checkGroups["Sorting Algorithm"].controlable); });
        barControls.checkGroups["Sorting Algorithm"].setChoice();
        Algorithm::setDelay(barControls.sliders["Speed"].controlable);
    }

private:
};
