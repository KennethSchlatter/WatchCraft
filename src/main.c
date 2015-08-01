#include <pebble.h>

static Window *craft_window;
static GFont craft_font;
static BitmapLayer *crafting_table;
static GBitmap *background_bitmap;
//Crafting Table Text Boxes
TextLayer *a1, *b1, *c1, *a2, *b2, *c2, *a3, *b3, *c3;
/*
	a1 b1 c1
	a2 b2 c2
	a3 b3 c3
*/
//Key TextLayer
TextLayer *key;

static void craft_window_load(Window *window) {
  // Create GBitmap, then set to created BitmapLayer
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CRAFT);
  crafting_table = bitmap_layer_create(GRect(12, 12, 120, 120));
  bitmap_layer_set_bitmap(crafting_table, background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(crafting_table));
	
	//8-Bit Font
	craft_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_MC_FONT_20));
	text_layer_set_font(a1, craft_font);
	text_layer_set_font(b1, craft_font);
	text_layer_set_font(c1, craft_font);
	text_layer_set_font(a2, craft_font);
	text_layer_set_font(b2, craft_font);
	text_layer_set_font(c2, craft_font);
	text_layer_set_font(a3, craft_font);
	text_layer_set_font(b3, craft_font);
	text_layer_set_font(c3, craft_font);
}

static void window_unload(Window *window) {
	bitmap_layer_destroy(crafting_table);
	fonts_unload_custom_font(craft_font);
}

static void init() {
  craft_window = window_create();
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(craft_window, (WindowHandlers) {
    .load = craft_window_load,
    //.unload = craft_window_unload;
  });
	window_stack_push(craft_window, true);
}

static void deinit() {
    // Destroy Window
    window_destroy(craft_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}