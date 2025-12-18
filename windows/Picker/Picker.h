#pragma once

#include "pch.h"
#include "resource.h"

#include "codegen/NativePickerModuleSpec.g.h"
#include "codegen_manual/react/components/RNCPickerSpec/RNCPicker.g.h"
#include "NativeModules.h"

namespace winrt::Picker
{

REACT_MODULE(Picker)
struct Picker
{
  using ModuleSpec = PickerCodegen::PickerModuleSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  // TurboModule methods from NativePickerModule.ts spec
  REACT_SYNC_METHOD(multiply)
  double multiply(double a, double b) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::Picker