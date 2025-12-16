#include "pch.h"

#include "Picker.h"

#ifdef RNW_NEW_ARCH
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Controls::Primitives;
#endif

namespace winrt::Picker
{

// Native module for Picker
// The actual picker functionality is provided by the RNCPicker component (see RNCPickerComponentView.h/cpp)
// See https://microsoft.github.io/react-native-windows/docs/native-modules for details on writing native modules

void Picker::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

double Picker::multiply(double a, double b) noexcept {
  return a * b;
}

} // namespace winrt::Picker