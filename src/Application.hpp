#pragma once
#include "./global.hpp"
#include "../controls/ControlGroup.hpp"
#include "../graphics/bar/BarBoard.hpp"

#include "./smartArray.hpp"

#include "../algorithms/SortAlgorithm.hpp"
#include "../algorithms/BubbleSort.hpp"
#include "../algorithms/HeapSort.hpp"
#include "../algorithms/InsertionSort.hpp"
#include "../algorithms/MergeSort.hpp"
#include "../algorithms/QuickSort.hpp"

#include "../graphics/Renderer.hpp"

// Forward declarations for Emscripten callback
class Application;
static Application *g_app_instance = nullptr;

#ifdef __EMSCRIPTEN__
extern "C" void emscripten_main_loop_wrapper();
#endif

class Application
{
public:
    BarBoard barboard;
    SmartArray<BarShape> bars;
    Text debugText;
    ControlGroup barControls;
    Renderer renderer;

    InsertionSort insersion;
    MergeSort mergeSort;
    HeapSort heapSort;
    QuickSort quickSort;
    BubbleSort bubbleSort;

    Algorithm *sortingAlgorithm;
    bool sortingInProgress = false;
    Uint64 lastSortStepMs = 0;

    Application() : bars(), insersion(bars), mergeSort(bars), heapSort(bars), quickSort(bars), bubbleSort(bars)
    {
        if (loadResources() != 0)
        {
            exit(1);
        }

        int width = 1500;
        int height = 800;
#ifdef __EMSCRIPTEN__
        width = EM_ASM_INT({
            return window.innerWidth * window.devicePixelRatio;
        });
        height = EM_ASM_INT({
            return window.innerHeight * window.devicePixelRatio;
        });
#endif
        renderer.setWindowSize(width, height);
        renderer.setWindowTitle("Sorting Algorithms Visualizer");
        renderer.initialize();

        setAlgorithm();

        createControls();
        bindControls();
    }

    void run()
    {
        g_app_instance = this;

#ifdef __EMSCRIPTEN__
        // On web, use Emscripten's main loop which yields to the browser
        emscripten_set_main_loop(emscripten_main_loop_wrapper, 0, 1);
#else
        // On native platforms, use traditional blocking loop
        while (renderer.isRunning())
        {
            mainLoop();
            SDL_Delay(16);
        }
#endif
    }

    void mainLoop()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                renderer.stop();
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

        sortingLoop();

        renderer.clear();

        barboard.draw(renderer);
        barControls.draw(renderer);

        renderer.present();
    }

    int loadResources()
    {
        TTF_Font *font = Text::loadStaticFont("assets/fonts/roboto.ttf");
        if (font == nullptr)
        {
            std::cerr << "Couldn't open font: " << SDL_GetError() << std::endl;
            return 1;
        }
        return 0;
    }

    void createControls()
    {
        barControls.addSlider("Count", Slider("Count", 1, 200, 1000));

        barControls.addSlider("Max Height", Slider("Max Height", 10, 300, 500));
        barControls.addSlider("Width", Slider("Width", 1, 3, 40));
        barControls.addSlider("Spacing", Slider("Spacing", 0, 0, 40));
        barControls.addSlider("Speed", Slider("Speed", 1, 2, sizeof(Algorithm::delays) / sizeof(Algorithm::delays[0])));
        barControls.addButton("Shuffle");
        barControls.addButton("Sort");
        barControls.addCheckGroup("Sorting Algorithm");
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Insertion"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Heap"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Merge"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Quick"));
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Bubble"));

        barControls.setPosition({20, 100});

        barboard = BarBoard(
            &barControls.sliders["Count"].controlable,
            &barControls.sliders["Max Height"].controlable,
            &barControls.sliders["Width"].controlable,
            &barControls.sliders["Spacing"].controlable,
            bars,
            Rectangle(200, 10, renderer.getWindowSize().x - 210, renderer.getWindowSize().y - 20));
    }

    void bindControls()
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
                                                  { startSorting(); });

        barControls.checkGroups["Sorting Algorithm"].setOnTrigger([&]
                                                                  { setAlgorithm(barControls.checkGroups["Sorting Algorithm"].controlable); });
        barControls.checkGroups["Sorting Algorithm"].setChoice();
        Algorithm::setDelay(barControls.sliders["Speed"].controlable);
    }

    void sortingLoop()
    {
        if (sortingInProgress && sortingAlgorithm != nullptr)
        {
            const Uint64 stepDelay = Algorithm::getDelayMs();
            const Uint64 now = SDL_GetTicks64();

            if (stepDelay == 0)
            {
                const int maxBatch = 64;
                for (int i = 0; i < maxBatch; ++i)
                {
                    if (!sortingAlgorithm->step())
                    {
                        sortingInProgress = false;
                        setDuringSorting(true);

                        break;
                    }
                }
            }
            else if (now - lastSortStepMs >= stepDelay)
            {
                lastSortStepMs = now;
                if (!sortingAlgorithm->step())
                {
                    sortingInProgress = false;
                    setDuringSorting(true);
                }
            }
        }
    }

    void startSorting()
    {
        if (sortingAlgorithm == nullptr || sortingInProgress)
            return;

        setDuringSorting(false);
        sortingAlgorithm->reset();
        sortingInProgress = true;
        lastSortStepMs = SDL_GetTicks64();
    }

    void setDuringSorting(bool enable = true)
    {
        if (enable)
        {
            barControls.sliders["Count"].enable();
            barControls.sliders["Max Height"].enable();
            barControls.buttons["Shuffle"]->enable();
            barControls.checkGroups["Sorting Algorithm"].enable();
        }
        else
        {
            barControls.sliders["Count"].disable();
            barControls.sliders["Max Height"].disable();
            barControls.buttons["Shuffle"]->disable();
            barControls.checkGroups["Sorting Algorithm"].disable();
        }
    }

    void setAlgorithm(int algorithmChoice = 0)
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

private:
};

#ifdef __EMSCRIPTEN__
// Emscripten callback - defined after class to access mainLoop()
extern "C" void emscripten_main_loop_wrapper()
{
    if (g_app_instance)
    {
        g_app_instance->mainLoop();
    }
}
#endif
