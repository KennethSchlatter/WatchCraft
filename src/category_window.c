#include <pebble.h>
#include "category_window.h"
#include "craft.h"

static MenuLayer *category_menu_layer;
static Window *category_window;
int category_section = 0;

uint16_t category_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
  return 7;
}

void category_draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context){
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, "Redstone", "", NULL);
    break;
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, "Food", "", NULL);
    break;
    case 2:
    menu_cell_basic_draw(ctx, cell_layer, "Special Items", "", NULL);
    break;
    case 3:
    menu_cell_basic_draw(ctx, cell_layer, "Building Blocks", "", NULL);
    break;
    case 4:
    menu_cell_basic_draw(ctx, cell_layer, "Decoration Blocks", "", NULL);
    break;
    case 5:
    menu_cell_basic_draw(ctx, cell_layer, "Transportation", "", NULL);
    break;
    case 6:
    menu_cell_basic_draw(ctx, cell_layer, "Tools, Weapons & Armor", "", NULL);
    break;
  }
}

void category_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  //get which row
  int which = cell_index->row;
	craft_window_set_index(which);
	window_stack_push(craft_window_get_window(), true);
}

void category_set_index(int index){
	category_section = index;
}

Window *category_get_window(){
	return category_window;
}

static void window_load(Window *window) {
  //menu layer
  category_menu_layer = menu_layer_create(GRect(0, 0, 144, 168 - 16));
  menu_layer_set_click_config_onto_window(category_menu_layer, window);
  MenuLayerCallbacks callbacks = 
  {
    .draw_row = (MenuLayerDrawRowCallback) category_draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) category_num_rows_callback,
    .select_click = (MenuLayerSelectCallback) category_select_click_callback,
    
  };
  menu_layer_set_callbacks(category_menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(window), menu_layer_get_layer(category_menu_layer));
  
}

static void window_unload(Window *window) 
{
  	menu_layer_destroy(category_menu_layer);
}

void category_init() {
  category_window = window_create();
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(category_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
}

void category_deinit() {
    // Destroy Window
    window_destroy(category_window);
}