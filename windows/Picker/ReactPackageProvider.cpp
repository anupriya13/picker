#include "pch.h"

#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "Picker.h"

#ifdef RNW_NEW_ARCH
#include "RNCPickerComponentView.h"
#endif

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Picker::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
#ifdef RNW_NEW_ARCH
  // Register Fabric (New Architecture) component
  RegisterRNCPickerComponentView(packageBuilder);
  
  // Register TurboModule
  AddAttributedModules(packageBuilder, true);
#else
  // Register TurboModule only for old architecture
  AddAttributedModules(packageBuilder, true);
#endif
}

} // namespace winrt::Picker::implementation
