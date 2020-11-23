// B8541F4BD6E8787F8CD61AE8AF47E141

#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include "B8541F4BD6E8787F8CD61AE8AF47E141.hpp"

using namespace std;

void get_resolution(int& horizontal, int& vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
    cout << "\nW:" << horizontal << " H:" << vertical << "\n";
}
//
void check_adb()
{
    system("MODE CON COLS=75 LINES=22");
    cout << "Connecting the device...\n";
    cout << "Starting ADB server...\n";
    // ADB stuff
    system("adb kill-server");
    system("adb start-server");
    system("adb devices");
    // Running ADB in root requires a rooted device with adbd Insecure.
    cout << "Running debug bridge in root mode...\n";
    system("adb root");
    // Setting permissions for the event directory
    system("adb shell chmod 666 /dev/input/event7");
}
int main()
{
    // We store our resolution here
    resolution a;
    
    // We run a block of ADB commands (kill,start and run ADB as root
    check_adb();

    // We get the resolution of the monitor
    get_resolution(a.w, a.h);

    // Example struct for storing RGB values, neat and compact
    pixel_color color_2{ 0, 0 ,0 };
 

        COLORREF find = RGB(0, 0, 0);
        COLORREF color;
        HDC hdc = GetDC(NULL);

        while (true)
        {
            // Trigger toggle
            if (GetAsyncKeyState(VK_SHIFT)) {

                // We get the pixel color
                color = GetPixel(hdc, a.w  / 2, a.h / 2);
                
                // We check if the pixel color matches the wanted one
                if (GetBValue(color) > 170 && GetBValue(color) < 240) {

                   // Simulate a tap and mouse input with a certain mouse-simulating application (random one from Google Play)
                    // 1. sendevent: MT_SLOT 0
                    // 2. sendevent: X coords of the screen
                    // 3. sendevent: Y coords of the screen
                    // 4. sendevent: Press down the touchscreen
                    // 5. sendevent: Sending a report
                    // 6. sendevent: Release the issued touch
                    // 7. sendevent: Sending a report
                    // /dev/input/event7 is the name of the directory that contains touchscreen events. Yours may differ, find it out with adb shell getevent -l
                   system("adb shell \"sendevent /dev/input/event7 3 47 0;sendevent /dev/input/event7 3 53 124;sendevent /dev/input/event7 3 54 1023;sendevent /dev/input/event7 1 330 1;sendevent /dev/input/event7 0 0 0;sendevent /dev/input/event7 1 330 0; sendevent /dev/input/event7 0 0 0;\"");
                }
            }
            Sleep(1);
        }

        ReleaseDC(NULL, hdc);    
}

