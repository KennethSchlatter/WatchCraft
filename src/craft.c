#include <pebble.h>
#include "craft.h"
#include "main.h"

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
int section = 0;

void craft_window_load(Window *window)
{  
  //Create GBitmap, then set to created BitmapLayer
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CRAFT);
  crafting_table = bitmap_layer_create(GRect(12, 12, 120, 120));
  bitmap_layer_set_bitmap(crafting_table, background_bitmap);
  layer_add_child(window_get_root_layer(craft_window), bitmap_layer_get_layer(crafting_table));
  
	
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
	
	a1 = text_layer_create(GRect(36, 36, 24, 24));
	text_layer_set_background_color(a1, GColorClear);
	text_layer_set_text_color(a1, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(a1));
	text_layer_set_text_alignment(a1, GTextAlignmentCenter);
	
	b1 = text_layer_create(GRect(72, 36, 24, 24));
	text_layer_set_background_color(b1, GColorClear);
	text_layer_set_text_color(b1, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(b1));
	text_layer_set_text_alignment(b1, GTextAlignmentCenter);
	
	c1 = text_layer_create(GRect(108, 36, 24, 24));
	text_layer_set_background_color(c1, GColorClear);
	text_layer_set_text_color(c1, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(c1));
	text_layer_set_text_alignment(c1, GTextAlignmentCenter);
	
	a2 = text_layer_create(GRect(36, 72, 24, 24));
	text_layer_set_background_color(a2, GColorClear);
	text_layer_set_text_color(a2, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(a2));
	text_layer_set_text_alignment(a2, GTextAlignmentCenter);
	
	b2 = text_layer_create(GRect(72, 72, 24, 24));
	text_layer_set_background_color(b2, GColorClear);
	text_layer_set_text_color(b2, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(b2));
	text_layer_set_text_alignment(b2, GTextAlignmentCenter);
	
	c2 = text_layer_create(GRect(108, 72, 24, 24));
	text_layer_set_background_color(c2, GColorClear);
	text_layer_set_text_color(c2, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(c2));
	text_layer_set_text_alignment(c2, GTextAlignmentCenter);
	
	a3 = text_layer_create(GRect(36, 108, 24, 24));
	text_layer_set_background_color(a3, GColorClear);
	text_layer_set_text_color(a3, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(a3));
	text_layer_set_text_alignment(a3, GTextAlignmentCenter);
	
	b3 = text_layer_create(GRect(72, 108, 24, 24));
	text_layer_set_background_color(b3, GColorClear);
	text_layer_set_text_color(b3, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(b3));
	text_layer_set_text_alignment(b3, GTextAlignmentCenter);
	
	c3 = text_layer_create(GRect(108, 108, 24, 24));
	text_layer_set_background_color(c3, GColorClear);
	text_layer_set_text_color(c3, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(c3));
	text_layer_set_text_alignment(c3, GTextAlignmentCenter);
	
	key = text_layer_create(GRect(0, 144, 144, 168));
	text_layer_set_background_color(key, GColorWhite);
	text_layer_set_text_color(key, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(key));
	text_layer_set_text_alignment(key, GTextAlignmentCenter);
}

 void craft_window_unload(Window *window){
	text_layer_destroy(a1);
	text_layer_destroy(b1);
	text_layer_destroy(c1);
	text_layer_destroy(a2);
	text_layer_destroy(b2);
	text_layer_destroy(c2);
	text_layer_destroy(a3);
	text_layer_destroy(b3);
	text_layer_destroy(c3);

	bitmap_layer_destroy(crafting_table);
	fonts_unload_custom_font(craft_font);
}

void craft_window_set_index(int index){
	section = index;
}

Window *craft_window_get_window(){
	return craft_window;
}

void craft_window_init() {
  craft_window = window_create();
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(craft_window, (WindowHandlers) {
    .load = craft_window_load,
    .unload = craft_window_unload
  });
	window_stack_push(craft_window, true);
}

void craft_window_deinit() {
    // Destroy Window
    window_destroy(craft_window);
}