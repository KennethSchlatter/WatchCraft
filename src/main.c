#include <pebble.h>
#include "category_window.h"
#include "craft.h"
#include "main.h"

static MenuLayer *menu_layer;
static Window *window;
Recipe current_recipe;

uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
  return 7;
}

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, "Redstone", NULL, NULL);
    break;
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, "Food", NULL, NULL);
    break;
    case 2:
    menu_cell_basic_draw(ctx, cell_layer, "Special Items", NULL, NULL);
    break;
    case 3:
    menu_cell_basic_draw(ctx, cell_layer, "Building Blocks", NULL, NULL);
    break;
    case 4:
    menu_cell_basic_draw(ctx, cell_layer, "Decoration Blocks", NULL, NULL);
    break;
    case 5:
    menu_cell_basic_draw(ctx, cell_layer, "Transportation", NULL, NULL);
    break;
    case 6:
    menu_cell_basic_draw(ctx, cell_layer, "Tools, Weapons & Armor", NULL, NULL);
    break;
  }
}

void process_tuple(Tuple *t){
	int key = t->key;
	int value = t->value->int32;
  switch (key) {
	case 0:
        current_recipe.type = value;
        break;
    case 1:
        strcpy(current_recipe.title[0], t->value->cstring);
        break;
    case 2:
        strcpy(current_recipe.name[0], t->value->cstring);
        break;
    default:
        if(key > 9 && key < 20){
            strcpy(current_recipe.simple_table[key-10], t->value->cstring);
        }
        else if(key > 19 && key < 30){
            strcpy(current_recipe.advanced_table[key-20], t->value->cstring);
        }
        else{
            APP_LOG(APP_LOG_LEVEL_ERROR, "Error: Unrecognized key %d.", key);
        }
  }
}

void inbox(DictionaryIterator *iter, void *context){
	Tuple *t = dict_read_first(iter);
	if(t){
		process_tuple(t);
	}
	while(t != NULL){
		t = dict_read_next(iter);
		if(t){
			process_tuple(t);
		}
	}
    category_add_recipe(current_recipe);
}

void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
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

static void window_unload(Window *window){
  	menu_layer_destroy(menu_layer);
}

static void init() {
    APP_LOG(APP_LOG_LEVEL_INFO, "Hello");
  window = window_create();
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
	app_message_register_inbox_received(inbox);
	app_message_open(512, 512);

	window_stack_push(window, true);
}

static void deinit() {
    // Destroy Window
    window_destroy(window);
}

int main(void) {
  init();
  category_init();
  craft_window_init();
  app_event_loop();
  category_deinit();
  craft_window_deinit();
  deinit();
}
