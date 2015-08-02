#include <pebble.h>
#include "craft.h"
#include "main.h"

Window *craft_window;
static GFont craft_font;
static BitmapLayer *crafting_table;
static GBitmap *background_bitmap;
Recipe craft_recipe;
//Crafting Table Text Boxes
TextLayer *a1, *b1, *c1, *a2, *b2, *c2, *a3, *b3, *c3;
/*
	a1 b1 c1
	a2 b2 c2
	a3 b3 c3
*/
//Key TextLayer
TextLayer *key;

void craft_window_load(Window *window)
{
  //Create GBitmap, then set to created BitmapLayer
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CRAFT);
  crafting_table = bitmap_layer_create(GRect(12, 12, 120, 120));
  bitmap_layer_set_bitmap(crafting_table, background_bitmap);
  layer_add_child(window_get_root_layer(craft_window), bitmap_layer_get_layer(crafting_table));

	a1 = text_layer_create(GRect(20, 20, 32, 32));
	text_layer_set_background_color(a1, GColorClear);
	text_layer_set_text_color(a1, GColorBlack);
    text_layer_set_text(a1, craft_recipe.simple_table[0]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(a1));
	text_layer_set_text_alignment(a1, GTextAlignmentCenter);

	b1 = text_layer_create(GRect(56, 20, 32, 32));
	text_layer_set_background_color(b1, GColorClear);
	text_layer_set_text_color(b1, GColorBlack);
    text_layer_set_text(b1, craft_recipe.simple_table[1]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(b1));
	text_layer_set_text_alignment(b1, GTextAlignmentCenter);

	c1 = text_layer_create(GRect(92, 20, 32, 32));
	text_layer_set_background_color(c1, GColorClear);
	text_layer_set_text_color(c1, GColorBlack);
    text_layer_set_text(c1, craft_recipe.simple_table[2]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(c1));
	text_layer_set_text_alignment(c1, GTextAlignmentCenter);

	a2 = text_layer_create(GRect(20, 56, 32, 32));
	text_layer_set_background_color(a2, GColorClear);
	text_layer_set_text_color(a2, GColorBlack);
    text_layer_set_text(a2, craft_recipe.simple_table[3]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(a2));
	text_layer_set_text_alignment(a2, GTextAlignmentCenter);

	b2 = text_layer_create(GRect(56, 56, 32, 32));
	text_layer_set_background_color(b2, GColorClear);
	text_layer_set_text_color(b2, GColorBlack);
    text_layer_set_text(b2, craft_recipe.simple_table[4]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(b2));
	text_layer_set_text_alignment(b2, GTextAlignmentCenter);

	c2 = text_layer_create(GRect(92, 56, 32, 32));
	text_layer_set_background_color(c2, GColorClear);
	text_layer_set_text_color(c2, GColorBlack);
    text_layer_set_text(c2, craft_recipe.simple_table[5]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(c2));
	text_layer_set_text_alignment(c2, GTextAlignmentCenter);

	a3 = text_layer_create(GRect(20, 92, 32, 32));
	text_layer_set_background_color(a3, GColorClear);
	text_layer_set_text_color(a3, GColorBlack);
    text_layer_set_text(a3, craft_recipe.simple_table[6]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(a3));
	text_layer_set_text_alignment(a3, GTextAlignmentCenter);

	b3 = text_layer_create(GRect(56, 92, 32, 32));
	text_layer_set_background_color(b3, GColorClear);
	text_layer_set_text_color(b3, GColorBlack);
    text_layer_set_text(b3, craft_recipe.simple_table[7]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(b3));
	text_layer_set_text_alignment(b3, GTextAlignmentCenter);

	c3 = text_layer_create(GRect(92, 92, 32, 32));
	text_layer_set_background_color(c3, GColorClear);
	text_layer_set_text_color(c3, GColorBlack);
    text_layer_set_text(c3, craft_recipe.simple_table[8]);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(c3));
	text_layer_set_text_alignment(c3, GTextAlignmentCenter);

	key = text_layer_create(GRect(0, 144, 144, 168));
	text_layer_set_background_color(key, GColorWhite);
	text_layer_set_text_color(key, GColorBlack);
	layer_add_child(window_get_root_layer(craft_window), text_layer_get_layer(key));
	text_layer_set_text_alignment(key, GTextAlignmentCenter);

return;
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
	 gbitmap_destroy(background_bitmap);
	fonts_unload_custom_font(craft_font);
}

void craft_window_set_recipe(Recipe recipe){
	craft_recipe = recipe;
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
}

void craft_window_deinit() {
    // Destroy Window
    window_destroy(craft_window);
}
