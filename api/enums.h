//
// Created by Flynn on 21.08.2023.
//

#ifndef SAMPLERIDE_ENUMS_H
#define SAMPLERIDE_ENUMS_H

namespace sampleride
{

    enum class ColorTypes
    {
        FG = 0,
        BG = 1,
        FG_HOVER = 2,
        BG_HOVER = 3,
        FG_SELECT = 4,
        BG_SELECT = 5,
        FG_COMP_HOVER = 6,
        FG_COMP_SELECT = 7
    };

    enum class ModuleTypes
    {
        None = 0,
        Other = 1,
        SingleTray = 2,
        Tray = 3,
        RectTray = 4,
        Container = 5,
    };

    enum class ModuleFlags
    {
        TrayNozzleContainer = 0b1,
    };

    enum class SelectorState
    {
        Default = 0,
        SelectPos = 1,
        SelectModule = 2,
        SelectTray = 3
    };

    enum class SelectorFlags
    {
        MultipleSelections = 0b1,
    };

} // namespace sampleride

#endif //SAMPLERIDE_ENUMS_H
