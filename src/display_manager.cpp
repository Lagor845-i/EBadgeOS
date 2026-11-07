#include "display_manager.h"

Display_Manager::Display_Manager(systemQueues* system_queues):_system_queues(system_queues) {
    _width = SCREEN_WIDTH;
    _height = SCREEN_HEIGHT;
};

void Display_Manager::begin() {
    lcd.init();
    lcd.initDMA();
    lcd.setRotation(3);
    lcd.fillScreen(TFT_BLACK);
    forceLovyanGFXSymbols();
    //_system_services.systemLog("Display Initialized");
    _notification = true;
    _notification_text = "";
    _notification_time_limit = 0;

    while (true) {
        vTaskDelay(1);
    }
};

void Display_Manager::forceLovyanGFXSymbols() {
    LGFX_Sprite* sprite = new LGFX_Sprite();
    delete sprite;
}

void Display_Manager::setDisplayBuffer(LGFX_Sprite* buffer) {
    _display_buffer = buffer;
}

void Display_Manager::updateDisplay() {
    _notification_sprite.deleteSprite();
    if (_notification == true) {
        if ((millis() - _notification_timer_start) * 1000 < _notification_time_limit)  {
            drawNotificationText();
        } else {
            _notification = false;
        }
    }
    lcd.pushImageDMA(0,0,_display_buffer->width(),_display_buffer->height(),_display_buffer->getBuffer());
}

void Display_Manager::fill(uint16_t color) {
    lcd.fillScreen(color);
};

int Display_Manager::getDisplayWidth() {
    return _width;
}

int Display_Manager::getDisplayHeight() {
    return _height;
}

void Display_Manager::sendNotification(std::string notification) {
    _notification_text = notification;
    _notification_time_limit = 2;
    _notification = true;
}

bool Display_Manager::displayingNotification() {
    return _notification;
}

void Display_Manager::error(std::string error) {
    lcd.fillScreen(TFT_BLUE);
    drawTextToDisplay(error,TFT_WHITE,45,int(_height/3));
}

void Display_Manager::drawNotificationText() {
    int notification_width = NOTIFICATION_PIXELS_PER_CHARACTER * _notification_text.length();
    _notification_sprite.createSprite(notification_width,NOTIFICATION_HEIGHT);
    _notification_sprite.setTextColor(TFT_WHITE);
    _notification_sprite.setTextSize(NOTIFICATION_TEXT_SIZE);
    _notification_sprite.setCursor(SCREEN_WIDTH - notification_width - NOTIFICATION_X_OFFSET,SCREEN_HEIGHT - NOTIFICATION_HEIGHT - NOTIFICATION_Y_HEIGHT);
    _notification_sprite.print(_notification_text.c_str());
    _display_buffer->pushImageDMA(_width,_height,notification_width,NOTIFICATION_HEIGHT,_notification_sprite.getBuffer());
}

void Display_Manager::drawTextToDisplay(std::string text,int forground,int x,int y) {
    lcd.setTextColor(TFT_WHITE);
    lcd.setTextSize(2);
    lcd.setCursor(x, y);
    lcd.print(text.c_str());
};
