//
// Created by cauchywei on 2017/8/16.
//

#ifndef DCRAFT_WINDOWEVENT_H
#define DCRAFT_WINDOWEVENT_H

#include <string>

namespace shiba {

    enum EventType {
        CLOSE,
        RESIZE
    };

    struct SizeEvent
    {
        unsigned int width;
        unsigned int height;
    };

    struct KeyEvent
    {
//        Keyboard::Key code;    ///< Code of the key that has been pressed
        bool          alt;     ///< Is the Alt key pressed?
        bool          control; ///< Is the Control key pressed?
        bool          shift;   ///< Is the Shift key pressed?
        bool          system;  ///< Is the System key pressed?
    };

    class WindowEvent {

    public:
        EventType type;
        std::string *message = nullptr;
        union {
            SizeEvent size;
        };
    };


}
#endif //DCRAFT_WINDOWEVENT_H
