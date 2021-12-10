#include "consoleUtils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iomanip> // for std::setfill & std::setw

#define WAIT_ANY_KEY std::cout << "Press any key to continue..." << std::endl; consoleUtils::getChar();

int main() {

	std::cout << "Console test program." << std::endl;
	WAIT_ANY_KEY

	std::cout << "Test 1: Colors" << std::endl;
	for (int i = 0; i < 16; i++) {
		consoleUtils::setColor(static_cast<consoleUtils::Color>(i));
		std::cout << i << " ";
	}
	consoleUtils::resetColors();
	std::cout << std::endl << "You should see numbers 0-15 in different colors." << std::endl;
	WAIT_ANY_KEY
	
	std::cout << "\nTest 2: Background colors\n";
	for (int i = 0; i < 8; i++) {
		consoleUtils::setBackgroundColor(static_cast<consoleUtils::BackgroundColor>(i));
		std::cout << i;
		consoleUtils::setBackgroundColor(consoleUtils::BackgroundColor::BLACK);
		std::cout << ' ';
	}
	consoleUtils::setBackgroundColor(consoleUtils::BackgroundColor::BLACK);
	consoleUtils::resetColors();
	std::cout << "\nYou should see numbers 0-7 in different-colored backgrounds.\n";
	WAIT_ANY_KEY

	consoleUtils::clear();
	std::cout << "Test 3: Clear screen" << std::endl;
	std::cout << "The colors should now be gone." << std::endl;
	WAIT_ANY_KEY

	consoleUtils::clear();
	std::cout << "Test 6: Cursor positioning" << std::endl;
	consoleUtils::setCursorPos(16,6); std::cout << "(16,6)";
	consoleUtils::setCursorPos(4,3); std::cout << "(4,3)";
	consoleUtils::setCursorPos(8,8); std::cout << "(8,8)";
	std::cout << std::endl << "You should see three coordinates in their specified locations." << std::endl;
	WAIT_ANY_KEY

	consoleUtils::clear();
	std::cout << "Test 7: Blocking keyboard input" << std::endl;
	std::cout << "You should be able to move the '@' character with zqsd keys." << std::endl;
	std::cout << "Hit Space to continue to the next test." << std::endl;
	std::cout << "Last pressed key:" << std::endl;
	{	
		int x = 7; int y = 7; bool spaceHit = false;

		while (!spaceHit) {
			consoleUtils::setCursorPos(x,y); std::cout << '@'; // Output player
			char c = consoleUtils::getChar(); // Get
			consoleUtils::setCursorPos(19,4); std::cout << c;
			consoleUtils::setCursorPos(x,y); std::cout << ' '; // Clean
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

	consoleUtils::clear();
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

		consoleUtils::setCursorPos(x,y); std::cout << '@'; // first display
		while (!spaceHit) {
			
			consoleUtils::setCursorPos(8, 5); std::cout << std::setfill('0') << std::setw(8) << cnt; // update cnt

			if (consoleUtils::kbhit()) {
				const char c = consoleUtils::getChar(); // Get character
				consoleUtils::setCursorPos(x, y); std::cout << ' '; // clean
				switch (c) {
					case 'z': --y; break;
					case 's': ++y; break;
					case 'q': --x; break;
					case 'd': ++x; break;
					case ' ': spaceHit = true; break;
					default: break;
				}
				consoleUtils::setCursorPos(x,y); std::cout << '@'; // display
			}
			// Wanning: this sleep somehow breaks the console print
			consoleUtils::sleep(1);
			++cnt;

		}
	}

	// TODO: fix it as extended ascii not work on linux (use utf-8 unstead)

	consoleUtils::clear();
	std::cout << "All tests done. Bye!" << std::endl;
	return 0;
}
