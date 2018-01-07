#include "Image.h"
#include "StickerSheet.h"

int main() {
    //
    // Reminder:
    //   Before exiting main, save your creation to disk as myImage.png
    //
    cs225::Image base, wade, ui_logo, screen_shot;
    base.readFromFile("./part3/base.png");
    wade.readFromFile("./part3/wade.png");
    ui_logo.readFromFile("./part3/ui_logo.png");
    screen_shot.readFromFile("./part3/screen_shot.png");

    cs225::StickerSheet sheet(base, 10);

    sheet.addSticker(wade, 510, 250);
    sheet.addSticker(ui_logo, 600, 550);
    sheet.addSticker(screen_shot, 100, 160);
    sheet.addSticker(screen_shot, 100, 570);
    sheet.addSticker(screen_shot, 200, 420);
    sheet.addSticker(screen_shot, 740, 375);
    sheet.addSticker(screen_shot, 920, 510);

    sheet.render().writeToFile("./myImage.png");

    return 0;
}
