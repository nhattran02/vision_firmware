#pragma once

#include <vector>
#include "__base__.hpp"

typedef enum
{
    BUTTON_IDLE = 0,
    BUTTON_0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4, 
    BUTTON_5, 
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
    BUTTON_9, 
    BUTTON_STAR, //star
    BUTTON_OK,   //sharp
    BUTTON_ESC,  //A 
    BUTTON_MENU, //B 
    BUTTON_UP,   //C
    BUTTON_DOWN, //D
} button_name_t;


typedef struct
{
    button_name_t key; /**< button index on the channel */
} key_config_t;

class Button : public Subject
{
public:
    std::vector<key_config_t> key_configs;
    button_name_t pressed;
    
    uint8_t menu;
    
    Button();
    ~Button();

    void run();
};
