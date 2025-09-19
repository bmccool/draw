#include <stdio.h>
#include <Windows.h>


int draw(void) {
	// Drawing logic would go here
	printf("Drawing...\n");
	HDC screen = GetDC(NULL);
	int red = 0;
	int blue = 0;
	int green = 0;

	for (int counter = 0;; counter += 1) {
		Rectangle(screen, 50, 50, counter + 500, 500);
		HBRUSH brush = CreateSolidBrush(RGB(red, green, blue));
		SelectObject(screen, brush);
		red += 5;
		red %= 256;
		blue += 15;
		blue %= 256;
		green += 25;
		green %= 256;
	}
	return 0;
}