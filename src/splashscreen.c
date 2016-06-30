#include <pebble.h>
#include "splashscreen.h"

static BitmapLayer *splashscreenLayer;
static GBitmap *splashscreenBitmap;



void create_splashscreen() {
    splashscreenLayer = bitmap_layer_create(GRect(0, 0, 144, 168));
    splashscreenBitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASHSCREEN);
    bitmap_layer_set_bitmap(splashscreenLayer, splashscreenBitmap);
}

void show_splashscreen(const Window *gameWindow) {
    Layer *windowLayer = window_get_root_layer(gameWindow);
    layer_add_child(windowLayer, bitmap_layer_get_layer(splashscreenLayer));

}

void hide_splashscreen() {
    layer_remove_from_parent((Layer *)splashscreenLayer);
}

void destroy_splashscreen() {
    layer_remove_from_parent((Layer *)splashscreenLayer);
    bitmap_layer_destroy(splashscreenLayer);
    gbitmap_destroy(splashscreenBitmap);
}
