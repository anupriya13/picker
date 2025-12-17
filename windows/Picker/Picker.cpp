#include "pch.h"
#include "Picker.h"

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
  // Opening picker programmatically is not currently supported on Windows
  // The picker opens when the user clicks on the ComboBox
  return false;
}

bool Picker::closePicker() noexcept {
  // Closing picker programmatically is not currently supported on Windows
  // The picker closes when the user makes a selection or clicks outside
  return false;
}

} // namespace winrt::Picker