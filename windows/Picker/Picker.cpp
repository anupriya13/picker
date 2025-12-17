#include "pch.h"
#include "Picker.h"
#include "RNCPickerComponentView.h"

namespace winrt::Picker
{

// Native module for Picker
// The actual picker functionality is provided by the RNCPicker Fabric component (see RNCPickerComponentView.h/cpp)
// See https://microsoft.github.io/react-native-windows/docs/native-modules for details on writing native modules

void Picker::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

double Picker::multiply(double a, double b) noexcept {
  return a * b;
}

bool Picker::openPicker() noexcept {
#ifdef RNW_NEW_ARCH
  return winrt::Picker::implementation::RNCPickerComponentView::OpenPicker();
#else
  return false;
#endif
}

bool Picker::closePicker() noexcept {
#ifdef RNW_NEW_ARCH
  return winrt::Picker::implementation::RNCPickerComponentView::ClosePicker();
#else
  return false;
#endif
}

} // namespace winrt::Picker