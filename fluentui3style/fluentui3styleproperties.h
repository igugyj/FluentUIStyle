#ifndef FLUENTUI3STYLEPROPERTIES_H
#define FLUENTUI3STYLEPROPERTIES_H

enum SpinBoxButtonLayout
{
    ArrowsHorizontalRight,
    ArrowsVertical,
    ArrowsHorizontalSides,
    PlusMinusHorizontalSides
};

[[maybe_unused]] constexpr const char *TabBarStyleProperty = "tabBarStyle";
enum TabBarStyle
{
    Capsule = 1,
    Pivot_Grow,
    Pivot_Slide,
    Pivot_Stretch,
    PillTabs,
    Segmented_Slide,
    Segmented_Fade,
    Navigation,
    Segmented_WinUI3
};

[[maybe_unused]] constexpr const char *ProgressBarThicknessProperty = "progressBarThickness";
[[maybe_unused]] constexpr const char *ProgressBarStyleProperty = "progressBarStyle";
enum ProgressBarStyle
{
    ProgressBarThin = 0,
    ProgressBarThick = 1,
    ProgressBarRing = 2
};

[[maybe_unused]] constexpr const char *ButtonAccentStyleProperty = "accent";
[[maybe_unused]] constexpr const char *SwitchStyleProperty = "isSwitchButton";
[[maybe_unused]] constexpr const char *NavigationViewStyleProperty = "navigationViewIndicator";
[[maybe_unused]] constexpr const char *NoRoundedCorners = "noRoundedCorners";

#endif // FLUENTUI3STYLEPROPERTIES_H
