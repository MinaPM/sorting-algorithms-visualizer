# for building on linux run (without quotes): "make linux"
# for building on windows run (without quotes): "mingw32-make windows" or "mingw32-make windows-d"

app_name = sorting_algorithms

source_file = ./app/main.cpp
other_files = \
# ./app/global.cpp \

output_path_windows = ./Build/Windows/
output_path_linux = ./Build/Linux/

SFML_include_path = ./src/include
SFML_library_path = ./src/lib
SFML_libraries =  -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system



#Windows------------------------
windows: build-windows run-windows

#dynamic link
build-windows:
	g++ $(source_file) $(other_files) \
	-o $(output_path_windows)$(app_name).exe \
	-I$(SFML_include_path) \
	-L$(SFML_library_path) \
	$(SFML_libraries)

run-windows:
	$(output_path_windows)$(app_name).exe
