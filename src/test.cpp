#include "consoleUtils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iomanip> // for std::setfill & std::setw

#define WAIT_ANY_KEY std::cout << "Press any key to continue..." << std::endl; getch();

int main() {

	std::cout << "Console test program." << std::endl;
	WAIT_ANY_KEY

	std::cout << "Test 1: Colors" << std::endl;
	for (int i = 0; i < 16; i++) {
		consoleUtils::SetColor(static_cast<consoleUtils::Color>(i));
		std::cout << i << " ";
	}
	consoleUtils::SetColor(consoleUtils::Color::GREY);
	std::cout << std::endl << "You should see numbers 0-15 in different colors." << std::endl;
	WAIT_ANY_KEY
	
	std::cout << "\nTest 2: Background colors\n";
	for (int i = 0; i < 8; i++) {
		consoleUtils::SetBackgroundColor(static_cast<consoleUtils::BackgroundColor>(i));
		std::cout << i;
		consoleUtils::SetBackgroundColor(consoleUtils::BackgroundColor::BLACK);
		std::cout << ' ';
	}
	consoleUtils::SetBackgroundColor(consoleUtils::BackgroundColor::BLACK);
	std::cout << "\nYou should see numbers 0-7 in different-colored backgrounds.\n";
	WAIT_ANY_KEY

	consoleUtils::cls();
	std::cout << "Test 3: Clear screen" << std::endl;
	std::cout << "The colors should now be gone." << std::endl;
	WAIT_ANY_KEY

	consoleUtils::cls();
	std::cout << "Test 6: Cursor positioning" << std::endl;
	consoleUtils::locate(16,6); std::cout << "(16,6)";
	consoleUtils::locate(4,3); std::cout << "(4,3)";
	consoleUtils::locate(8,8); std::cout << "(8,8)";
	std::cout << std::endl << "You should see three coordinates in their specified locations." << std::endl;
	WAIT_ANY_KEY

	consoleUtils::cls();
	std::cout << "Test 7: Blocking keyboard input" << std::endl;
	std::cout << "You should be able to move the '@' character with ZQSD keys." << std::endl;
	std::cout << "Hit Space to continue to the next test." << std::endl;
	std::cout << "Last pressed key:" << std::endl;
	{	
		int x = 7; int y = 7; bool spaceHit = false;

		while (!spaceHit) {
			consoleUtils::locate(x,y); std::cout << '@'; // Output player
			char c = getch(); // Get
			consoleUtils::locate(18,3); std::cout << c;
			consoleUtils::locate(x,y); std::cout << ' '; // Clean
			switch (c) {
				case 'z': --y; break;
				case 's': ++y; break;
				case 'q': --x; break;
				case 'd': ++x; break;
				case ' ': spaceHit = true; break;
				default: break;
			}
		}
	}

	consoleUtils::cls();
	std::cout << "Test 8:  Non-blocking keyboard input" << std::endl;
	std::cout << "You should be able to move the '@' character with ZQSD keys." << std::endl;
	std::cout << "Hit Space to continue to the next test." << std::endl;
	std::cout << "Last pressed key:" << std::endl;
	std::cout << "Count:" << std::endl;
	{	
		int x = 7;
		int y = 7;
		bool spaceHit = false;
		unsigned int cnt = 0;

		consoleUtils::locate(x,y); std::cout << '@'; // first display
		while (!spaceHit) {
			
			consoleUtils::locate(7,4); std::cout << std::setfill('0') << std::setw(5) << cnt; // update cnt

			if (kbhit()) {
				const char c = getch(); // Get character
				consoleUtils::locate(x,y); std::cout << ' '; // clean
				switch (c) {
					case 'z': --y; break;
					case 's': ++y; break;
					case 'q': --x; break;
					case 'd': ++x; break;
					case ' ': spaceHit = true; break;
					default: break;
				}
				consoleUtils::locate(x,y); std::cout << '@'; // display
			}

			Sleep(10);
			++cnt;

		}
	}

	consoleUtils::cls();
	std::cout << "Test 10: extended ascii char" << std::endl;

	for (int i=0; i<257; i++) {
		std::cout << "[" << i << " = " << (char)i << "] ";
		if (i % 10 == 0) std::cout << std::endl;
	}
	WAIT_ANY_KEY
	consoleUtils::cls();
	std::cout << "Test 11: border in extended ascii char" << std::endl << std::endl;
	// '─' =  (char)196
	// '│' = (char)179
	// '┌' = (char)218
	// '┐' = (char)191
	// '┘' = (char)217
	// '└' = (char)192

	std::cout << (char)218;  
    for (int i = 0; i < 8; ++i) std::cout << (char)196;
    std::cout << (char)191 << std::endl;

    for (int i = 0; i < 8; ++i) {
        std::cout << (char)179; 
        consoleUtils::locate(9,i+3);
        std::cout << (char)179 << std::endl;
    }

	std::cout << (char)192;
    for (int i = 0; i < 8; ++i) std::cout << (char)196;
    std::cout << (char)217 << std::endl;
	
	WAIT_ANY_KEY

	consoleUtils::cls();
	std::cout << "All tests done. Bye!" << std::endl;
	return 0;
}
