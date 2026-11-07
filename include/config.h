
//Shows current firmware version. PLEASE RAISE NUMBER IF CHANGING ELF API!!!
#define FIRMWARE_VERSION 1

//Where on the SD card the applications are stored
#define APP_FOLDER "/apps/"
#define BOOT_APP "Boot.app"
#define BOOT_MENU "Menu.app"

//Allows debugging over Serial
#define DEBUG true
#define DEBUG_RATE 115200

//Sets the screen height of the connected Display
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

#define QUEUESIZEAPPLICATION 10
#define QUEUESIZEAUDIO 10
#define QUEUESIZEBLUETOOTH 10
#define QUEUESIZEDISPLAY 10
#define QUEUESIZEFILESYSTEM 10
#define QUEUESIZEINPUT 10
#define QUEUESIZELED 10
#define QUEUESIZESTATS 10
#define QUEUESIZEWIFI 10

//Notification settings
#define NOTIFICATION_HEIGHT 10
#define NOTIFICATION_TEXT_SIZE 2
#define NOTIFICATION_PIXELS_PER_CHARACTER 5
#define NOTIFICATION_Y_HEIGHT 5
#define NOTIFICATION_X_OFFSET 5