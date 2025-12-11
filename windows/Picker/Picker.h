#pragma once

#include "pch.h"
#include "resource.h"

#include "codegen/NativePickerModuleDataTypes.g.h"
#include "codegen/NativePickerModuleSpec.g.h"
#include "NativeModules.h"

namespace winrt::Picker
{

REACT_MODULE(Picker)
struct Picker
{
  using ModuleSpec = PickerCodegen::PickerModuleSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_GET_CONSTANTS(GetConstants)
  PickerCodegen::PickerModuleSpec_Constants GetConstants() noexcept;

  REACT_METHOD(open)
  void open(PickerCodegen::PickerModuleSpec_open_params &&params, React::ReactPromise<PickerCodegen::PickerModuleSpec_open_returnType> &&result) noexcept;

  REACT_METHOD(dismiss)
  void dismiss(React::ReactPromise<bool> &&result) noexcept;

  REACT_SYNC_METHOD(processPickerColor)
  std::optional<double> processPickerColor(std::string color) noexcept;

  REACT_SYNC_METHOD(getDefaultPickerHeight)
  double getDefaultPickerHeight() noexcept;

  REACT_SYNC_METHOD(validatePickerItem)
  bool validatePickerItem(std::string label, std::string value) noexcept;

  REACT_SYNC_METHOD(getSelectedIndexForValue)
  double getSelectedIndexForValue(std::vector<PickerCodegen::PickerModuleSpec_PickerItem> items, std::string selectedValue) noexcept;

  REACT_SYNC_METHOD(processPickerItems)
  std::vector<PickerCodegen::PickerModuleSpec_PickerItem> processPickerItems(std::vector<PickerCodegen::PickerModuleSpec_PickerItem> items) noexcept;

  REACT_METHOD(setNativeProps)
  void setNativeProps(double selectedIndex, std::string text) noexcept;

private:
  React::ReactContext m_context;
  bool m_isPickerOpen = false;
  PickerCodegen::PickerModuleSpec_open_params m_currentParams;
  
#ifdef RNW_NEW_ARCH
  winrt::Microsoft::UI::Xaml::Controls::ContentDialog m_contentDialog{nullptr};
  winrt::Microsoft::UI::Xaml::Controls::ComboBox m_comboBox{nullptr};
#endif
};

} // namespace winrt::Picker