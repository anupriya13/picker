#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativePickerDataTypes.g.h")
  #include "codegen/NativePickerDataTypes.g.h"
#endif
#include "codegen/react/components/rnpicker/RNCPickerWindows.g.h"

#include "NativeModules.h"

namespace winrt::Picker
{

// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

REACT_MODULE(Picker)
struct Picker
{
  using ModuleSpec = PickerCodegen::PickerSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_SYNC_METHOD(multiply)
  double multiply(double a, double b) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::Picker