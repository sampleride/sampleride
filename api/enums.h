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
        BG_SELECT = 5
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

} // namespace sampleride

#endif //SAMPLERIDE_ENUMS_H
