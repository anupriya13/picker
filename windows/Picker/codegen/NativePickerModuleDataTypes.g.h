
/*
 * This file is auto-generated from a NativeModule spec file in js.
 *
 * This is a C++ Spec class that should be used with MakeTurboModuleProvider to register native modules
 * in a way that also verifies at compile time that the native module matches the interface required
 * by the TurboModule JS spec.
 */
#pragma once

#include <string>
#include <optional>
#include <functional>
#include <vector>

namespace PickerCodegen {

struct PickerModuleSpec_PickerItem {
    std::string label;
    std::optional<std::string> value;
    std::optional<std::string> color;
    std::optional<std::string> testID;
};

struct PickerModuleSpec_open_params {
    std::vector<PickerModuleSpec_PickerItem> items;
    std::optional<double> selectedIndex;
    std::optional<bool> enabled;
    std::optional<std::string> prompt;
    std::optional<std::string> placeholder;
    std::optional<std::string> testID;
    std::optional<std::string> accessibilityLabel;
};

struct PickerModuleSpec_open_returnType {
    std::string action;
    double selectedIndex;
    std::optional<std::string> selectedValue;
    std::optional<std::string> selectedLabel;
};

struct PickerModuleSpec_Constants {
    std::optional<bool> isWindows;
    std::optional<double> defaultHeight;
};

} // namespace PickerCodegen
