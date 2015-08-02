#include <pebble.h>
#include "category_window.h"
#include "craft.h"
#include "main.h"

static MenuLayer *menu_layer;
static Window *window;

uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  return 7;
}

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
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

void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  //get which row
  int which = cell_index->row;
	
	category_set_index(which);
	window_stack_push(category_get_window(), true);
}



static void window_load(Window *window) {
  //menu layer
  menu_layer = menu_layer_create(GRect(0, 0, 144, 168 - 16));
  menu_layer_set_click_config_onto_window(menu_layer, window);
  MenuLayerCallbacks callbacks = 
  {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
    
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));
  
}

static void window_unload(Window *window) 
{
  	menu_layer_destroy(menu_layer);
}

static void init() {
  window = window_create();
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
	window_stack_push(window, true);
}

static void deinit() {
    // Destroy Window
    window_destroy(window);
}

int main(void) {
  init();
  category_init();
  app_event_loop();
  category_deinit();
  deinit();
}