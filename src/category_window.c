#include <pebble.h>
#include "category_window.h"
#include "craft.h"
#include "main.h"

static MenuLayer *category_menu_layer;
static Window *category_window;
int category_section = 0, category_stack_count = 0;
Recipe category_recipes[50];

uint16_t category_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
  return category_stack_count;
}

void category_draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context){
    menu_cell_basic_draw(ctx, cell_layer, category_recipes[cell_index->row].name[0], NULL, NULL);
}

void category_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
    APP_LOG(APP_LOG_LEVEL_INFO, "1");
	craft_window_set_recipe(category_recipes[cell_index->row]);
    APP_LOG(APP_LOG_LEVEL_INFO, "2");
    APP_LOG(APP_LOG_LEVEL_INFO, "%d", heap_bytes_free());
	window_stack_push(craft_window_get_window(), true);
    APP_LOG(APP_LOG_LEVEL_INFO, "3");
}

void category_add_recipe(Recipe recipe){
    category_recipes[category_stack_count] = recipe;
    category_stack_count++;
    menu_layer_reload_data(category_menu_layer);
}

void category_set_index(int index){
	category_section = index;
}

void send_request(int type){
	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);

	if (iter == NULL) {
	  return;
	}

	dict_write_uint16(iter, 200, type);
	dict_write_end(iter);

	app_message_outbox_send();
    APP_LOG(APP_LOG_LEVEL_INFO, "Sent message");
}

Window *category_get_window(){
	return category_window;
}

static void window_load(Window *window) {
  //menu layer
  category_stack_count = 0;

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
  send_request(category_section);
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
