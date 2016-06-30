#include <pebble.h>
#include "statemachine.h"
#include "mainmenu.h"
#include "pebble.h"


static Window *mainMenuWindow;
static SimpleMenuLayer *mainMenuLayer;
SimpleMenuItem mainMenuItems[3];
SimpleMenuSection mainMenuSection;

static void mm_marathon_not_a_sprint(int index, void *ctx) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "MARATHON SELECTED");
    set_current_state(STATE_MARATHON);
    window_stack_pop(true);
}

static void mm_sprint_not_a_marathon(int index, void *ctx) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "SPRINT SELECTED");
    set_current_state(STATE_SPRINT);
    window_stack_pop(true);
}

static void mm_tutorial(int index, void *ctx) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "TUTORIAL SELECTED");
    set_current_state(STATE_TUTORIAL);
    // window_stack_pop(true);
}


// window should be gameWindow, passed from horizontalboost.c
Window *main_menu_create() {
    // Unless we hear otherwise, leaving the menu quits the game
    // Check out mm_marathon_not_a_sprint(..) above to see how to prevent this!
    set_current_state(STATE_QUITTING);

    mainMenuItems[0].title  = "SPRINT";
    mainMenuItems[0].subtitle = "700m";
    mainMenuItems[0].icon = NULL;
    mainMenuItems[0].callback = mm_sprint_not_a_marathon;

    mainMenuItems[1].title  = "LONG RACE";
    mainMenuItems[1].subtitle = "1400m";
    mainMenuItems[1].icon = NULL;
    mainMenuItems[1].callback = mm_marathon_not_a_sprint;    

    mainMenuItems[2].title  = "TUTORIAL";
    mainMenuItems[2].subtitle = "how to play";
    mainMenuItems[2].icon = NULL;
    mainMenuItems[2].callback = mm_tutorial;    

    mainMenuSection.title = "MAIN MENU";
    mainMenuSection.items = mainMenuItems;
    mainMenuSection.num_items = 2;
    
    mainMenuWindow = window_create();
    window_set_window_handlers(mainMenuWindow, (WindowHandlers) {
        .unload = main_menu_destroy,
    });

    Layer *windowLayer = window_get_root_layer(mainMenuWindow);
    GRect bounds = layer_get_frame(windowLayer);

    mainMenuLayer = simple_menu_layer_create(bounds, mainMenuWindow, &mainMenuSection, 1, NULL);

    layer_add_child(windowLayer, simple_menu_layer_get_layer(mainMenuLayer));

    window_stack_push(mainMenuWindow, false);
    
    return mainMenuWindow;
}


void main_menu_destroy() {
    if(mainMenuLayer != NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "hello from main_menu_destroy!!!!!");
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Current state is: %d!!!!", get_current_state());
        layer_remove_from_parent((Layer *)mainMenuLayer);
        simple_menu_layer_destroy(mainMenuLayer);
        window_stack_remove(mainMenuWindow, false);
        window_destroy(mainMenuWindow);
        mainMenuLayer = NULL;
        mainMenuWindow = NULL;
    }
    if(mainMenuWindow != NULL) {
        window_stack_remove(mainMenuWindow, false);
        window_destroy(mainMenuWindow);
        mainMenuLayer = NULL;
        mainMenuWindow = NULL;        
    }
}

