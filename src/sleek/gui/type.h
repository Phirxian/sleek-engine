#ifndef GUI_TYPE
#define GUI_TYPE

namespace sleek
{
    namespace gui
    {
        enum INTERFACE_GUI_CODE
        {
            IGT_NOTHINK,
            IGT_BUTTON,
            IGT_CHECKBOX,
            IGT_CURSOR,
            IGT_EDITBOX,
            IGT_FRAME,
            IGT_PICTURE,
            IGT_COLORPICKER,
            IGT_SCROLLBAR,
            IGT_PROGRESSBAR,
            IGT_STATICTEXT,
            IGT_WINDOW,
            IGT_COUNT
        };
        static const char* interface_gui_code_name[] =
        {
            "IGT_NOTHINK",
            "IGT_BUTTON",
            "IGT_CHECKBOX",
            "IGT_CURSOR",
            "IGT_EDITBOX",
            "IGT_FRAME",
            "IGT_PICTURE",
            "IGT_STATICTEXT",
            "IGT_WINDOW",
            "IGT_COUNT"
        };
        enum INTERFACE_EVENT_CODE
        {
            IET_NOTHINK,
            /** button event **/
            IET_BUTTON_PUSHED,
            IET_BUTTON_CLICKED,
            IET_BUTTON_HOVERED,
            IET_BUTTON_FOCUSED,
            /** checkbox event **/
            IET_CHECKBOX_CHANGED,
            IET_CHECKBOX_HOVERED,
            IET_CHECKBOX_FOCUSED,
            /** editbox event **/
            IET_EDITBOX_CLICKED,
            IET_EDITBOX_CHANGED,
            IET_EDITBOX_FOCUSED,
            IET_EDITBOX_HOVORED,
            /** picture event **/
            IET_PICTURE_FOCUSED,
            IET_PICTURE_HOVORED,
            /** progressbar event **/
            IET_COLORPICKER_CLOSED,
            IET_COLORPICKER_FOCUSED,
            IET_COLORPICKER_HOVORED,
            IET_COLORPICKER_UPDATED,
            IET_COLORPICKER_SELECTED,
            /** progressbar event **/
            IET_SCROLLBAR_FOCUSED,
            IET_SCROLLBAR_HOVORED,
            IET_SCROLLBAR_UPDATED,
            /** progressbar event **/
            IET_PROGRESSBAR_FOCUSED,
            IET_PROGRESSBAR_HOVORED,
            IET_PROGRESSBAR_UPDATED,
            /** static text event **/
            IET_STATICTEXT_FOCUSED,
            IET_STATICTEXT_HOVORED,
            /** window event **/
            IET_WINDOW_MOVED,
            IET_WINDOW_HOVORED,
            IET_WINDOW_FOCUSED,
            IET_WINDOW_CLOSED,
            IET_COUNT
        };
        static const char* interface_event_code_name[] =
        {
            "IET_NOTHINK",
            "IET_BUTTON_PUSHED",
            "IET_BUTTON_CLICKED",
            "IET_BUTTON_HOVERED",
            "IET_BUTTON_FOCUSED",
            "IET_CHECKBOX_CHANGED",
            "IET_CHECKBOX_HOVERED",
            "IET_CHECKBOX_FOCUSED",
            "IET_EDITBOX_CLICKED",
            "IET_EDITBOX_CHANGED",
            "IET_EDITBOX_FOCUSED",
            "IET_EDITBOX_HOVORED",
            "IET_PICTURE_FOCUSED",
            "IET_PICTURE_HOVORED",
            "IET_PROGRESSBAR_FOCUSED",
            "IET_PROGRESSBAR_HOVORED",
            "IET_PROGRESSBAR_UPDATED",
            "IET_STATICTEXT_FOCUSED",
            "IET_STATICTEXT_HOVORED",
            "IET_WINDOW_MOVED",
            "IET_WINDOW_HOVORED",
            "IET_WINDOW_FOCUSED",
            "IET_COUNT"
        };
    }
}

#endif
