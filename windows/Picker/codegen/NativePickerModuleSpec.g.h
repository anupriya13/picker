
/*
 * This file is auto-generated from a NativeModule spec file in js.
 *
 * This is a C++ Spec class that should be used with MakeTurboModuleProvider to register native modules
 * in a way that also verifies at compile time that the native module matches the interface required
 * by the TurboModule JS spec.
 */
#pragma once

// #include "NativePickerModuleDataTypes.g.h" before this file to use the generated type definition
#include <NativeModules.h>
#include <tuple>

namespace PickerCodegen {

inline winrt::Microsoft::ReactNative::FieldMap GetStructInfo(PickerModuleSpec_PickerItem*) noexcept {
    winrt::Microsoft::ReactNative::FieldMap fieldMap {
        {L"label", &PickerModuleSpec_PickerItem::label},
        {L"value", &PickerModuleSpec_PickerItem::value},
        {L"color", &PickerModuleSpec_PickerItem::color},
        {L"testID", &PickerModuleSpec_PickerItem::testID},
    };
    return fieldMap;
}

inline winrt::Microsoft::ReactNative::FieldMap GetStructInfo(PickerModuleSpec_open_params*) noexcept {
    winrt::Microsoft::ReactNative::FieldMap fieldMap {
        {L"items", &PickerModuleSpec_open_params::items},
        {L"selectedIndex", &PickerModuleSpec_open_params::selectedIndex},
        {L"enabled", &PickerModuleSpec_open_params::enabled},
        {L"prompt", &PickerModuleSpec_open_params::prompt},
        {L"placeholder", &PickerModuleSpec_open_params::placeholder},
        {L"testID", &PickerModuleSpec_open_params::testID},
        {L"accessibilityLabel", &PickerModuleSpec_open_params::accessibilityLabel},
    };
    return fieldMap;
}

inline winrt::Microsoft::ReactNative::FieldMap GetStructInfo(PickerModuleSpec_open_returnType*) noexcept {
    winrt::Microsoft::ReactNative::FieldMap fieldMap {
        {L"action", &PickerModuleSpec_open_returnType::action},
        {L"selectedIndex", &PickerModuleSpec_open_returnType::selectedIndex},
        {L"selectedValue", &PickerModuleSpec_open_returnType::selectedValue},
        {L"selectedLabel", &PickerModuleSpec_open_returnType::selectedLabel},
    };
    return fieldMap;
}

inline winrt::Microsoft::ReactNative::FieldMap GetStructInfo(PickerModuleSpec_Constants*) noexcept {
    winrt::Microsoft::ReactNative::FieldMap fieldMap {
        {L"isWindows", &PickerModuleSpec_Constants::isWindows},
        {L"defaultHeight", &PickerModuleSpec_Constants::defaultHeight},
    };
    return fieldMap;
}

struct PickerModuleSpec : winrt::Microsoft::ReactNative::TurboModuleSpec {
  static constexpr auto constants = std::tuple{
      TypedConstant<PickerModuleSpec_Constants>{0},
  };
  static constexpr auto methods = std::tuple{
      Method<void(PickerModuleSpec_open_params, Promise<PickerModuleSpec_open_returnType>) noexcept>{0, L"open"},
      Method<void(Promise<bool>) noexcept>{1, L"dismiss"},
      SyncMethod<std::optional<double>(std::string) noexcept>{2, L"processPickerColor"},
      SyncMethod<double() noexcept>{3, L"getDefaultPickerHeight"},
      SyncMethod<bool(std::string, std::string) noexcept>{4, L"validatePickerItem"},
      SyncMethod<double(std::vector<PickerModuleSpec_PickerItem>, std::string) noexcept>{5, L"getSelectedIndexForValue"},
      SyncMethod<std::vector<PickerModuleSpec_PickerItem>(std::vector<PickerModuleSpec_PickerItem>) noexcept>{6, L"processPickerItems"},
      Method<void(double, std::string) noexcept>{7, L"setNativeProps"},
  };

  template <class TModule>
  static constexpr void ValidateModule() noexcept {
    constexpr auto constantCheckResults = CheckConstants<TModule, PickerModuleSpec>();
    constexpr auto methodCheckResults = CheckMethods<TModule, PickerModuleSpec>();

    REACT_SHOW_CONSTANT_SPEC_ERRORS(
          0,
          "PickerModuleSpec_Constants",
          "    REACT_GET_CONSTANTS(GetConstants) PickerModuleSpec_Constants GetConstants() noexcept {/*implementation*/}\n"
          "    REACT_GET_CONSTANTS(GetConstants) static PickerModuleSpec_Constants GetConstants() noexcept {/*implementation*/}\n");

    REACT_SHOW_METHOD_SPEC_ERRORS(
          0,
          "open",
          "    REACT_METHOD(open) void open(PickerModuleSpec_open_params && params, ::React::ReactPromise<PickerModuleSpec_open_returnType> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(open) static void open(PickerModuleSpec_open_params && params, ::React::ReactPromise<PickerModuleSpec_open_returnType> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          1,
          "dismiss",
          "    REACT_METHOD(dismiss) void dismiss(::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(dismiss) static void dismiss(::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          2,
          "processPickerColor",
          "    REACT_SYNC_METHOD(processPickerColor) std::optional<double> processPickerColor(std::string color) noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(processPickerColor) static std::optional<double> processPickerColor(std::string color) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          3,
          "getDefaultPickerHeight",
          "    REACT_SYNC_METHOD(getDefaultPickerHeight) double getDefaultPickerHeight() noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(getDefaultPickerHeight) static double getDefaultPickerHeight() noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          4,
          "validatePickerItem",
          "    REACT_SYNC_METHOD(validatePickerItem) bool validatePickerItem(std::string label, std::string value) noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(validatePickerItem) static bool validatePickerItem(std::string label, std::string value) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          5,
          "getSelectedIndexForValue",
          "    REACT_SYNC_METHOD(getSelectedIndexForValue) double getSelectedIndexForValue(std::vector<PickerModuleSpec_PickerItem> const & items, std::string selectedValue) noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(getSelectedIndexForValue) static double getSelectedIndexForValue(std::vector<PickerModuleSpec_PickerItem> const & items, std::string selectedValue) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          6,
          "processPickerItems",
          "    REACT_SYNC_METHOD(processPickerItems) std::vector<PickerModuleSpec_PickerItem> processPickerItems(std::vector<PickerModuleSpec_PickerItem> const & items) noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(processPickerItems) static std::vector<PickerModuleSpec_PickerItem> processPickerItems(std::vector<PickerModuleSpec_PickerItem> const & items) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          7,
          "setNativeProps",
          "    REACT_METHOD(setNativeProps) void setNativeProps(double selectedIndex, std::string text) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(setNativeProps) static void setNativeProps(double selectedIndex, std::string text) noexcept { /* implementation */ }\n");
  }
};

} // namespace PickerCodegen
