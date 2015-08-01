#include <pebble.h>

static MenuLayer *menu_layer;
static Window *craft_window;
static GFont craft_font;
//static BitmapLayer *crafting_table;
//static GBitmap *background_bitmap;
//Crafting Table Text Boxes
TextLayer *a1, *b1, *c1, *a2, *b2, *c2, *a3, *b3, *c3;
/*
	a1 b1 c1
	a2 b2 c2
	a3 b3 c3
*/
//Key TextLayer
TextLayer *key;


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
  uint32_t segments[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for(int i = 0; i < which + 1; i++) 
  {
    segments[2 * i] = 200;
    segments[(2 * i) + 1] = 100;
  }
  VibePattern pattern = {.durations = segments, .num_segments = 16};
  vibes_enqueue_custom_pattern(pattern);
}



static void craft_window_load(Window *window) {
  //menu layer
  menu_layer = menu_layer_create(GRect(0, 0, 144, 168 - 16));
  menu_layer_set_click_config_onto_window(menu_layer, craft_window);
  MenuLayerCallbacks callbacks = 
  {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
    
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(craft_window), menu_layer_get_layer(menu_layer));
  
  
  // Create GBitmap, then set to created BitmapLayer
  /*background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CRAFT);
  crafting_table = bitmap_layer_create(GRect(12, 12, 120, 120));
  bitmap_layer_set_bitmap(crafting_table, background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(crafting_table));
  */
	
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

static void craft_window_unload(Window *window) {
	//bitmap_layer_destroy(crafting_table);
	fonts_unload_custom_font(craft_font);
  	menu_layer_destroy(menu_layer);
	
	text_layer_destroy(a1);
	text_layer_destroy(b1);
	text_layer_destroy(c1);
	text_layer_destroy(a2);
	text_layer_destroy(b2);
	text_layer_destroy(c2);
	text_layer_destroy(a3);
	text_layer_destroy(b3);
	text_layer_destroy(c3);

}

static void init() {
  craft_window = window_create();
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(craft_window, (WindowHandlers) {
    .load = craft_window_load,
    .unload = craft_window_unload
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