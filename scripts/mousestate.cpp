#include <stdio.h>
#include <windows.h>

int main() {
  printf("Checking mouse state... ");
  // Check the mouse left button is pressed or not
  if ((GetKeyState(VK_LBUTTON) & 0x80) != 0) {
    printf("left key pressed!\n");
    return 1;
  }

  // Check the mouse right button is pressed or not
  if ((GetKeyState(VK_RBUTTON) & 0x80) != 0) {
    printf("right key pressed!\n");
    return 2;
  }

  printf("no key pressed.\n");

  return 0;
}
