// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#ifdef RNW_NEW_ARCH

#include "codegen_manual/react/components/RNCPickerSpec/RNCPicker.g.h"

#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Microsoft.ReactNative.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <limits>

namespace winrt::Picker::implementation {

// State to store the measured size
struct RNCPickerStateData : winrt::implements<RNCPickerStateData, winrt::IInspectable> {
  RNCPickerStateData(winrt::Windows::Foundation::Size ds) : desiredSize(ds) {}
  winrt::Windows::Foundation::Size desiredSize;
};

struct RNCPickerComponentView : winrt::implements<RNCPickerComponentView, winrt::IInspectable>,
                                  PickerCodegen::BaseRNCPicker<RNCPickerComponentView> {

  void InitializeContentIsland(
    const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView);

  void UpdateProps(
    const winrt::Microsoft::ReactNative::ComponentView &view,
    const winrt::com_ptr<PickerCodegen::RNCPickerProps> &newProps,
    const winrt::com_ptr<PickerCodegen::RNCPickerProps> &oldProps) noexcept override;

  void UpdateState(
    const winrt::Microsoft::ReactNative::ComponentView &view,
    const winrt::Microsoft::ReactNative::IComponentState &newState) noexcept override;

private:
  void RefreshSize();

  winrt::weak_ref<winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView> m_islandView;
  winrt::Microsoft::UI::Xaml::XamlIsland m_island{nullptr};
  winrt::Microsoft::UI::Xaml::Controls::ComboBox m_comboBox{nullptr};
  winrt::Microsoft::ReactNative::IComponentState m_state{nullptr};
  std::vector<PickerCodegen::RNCPickerSpec_RNCPickerProps_items> m_items;
  winrt::event_token m_selectionChangedToken{};
  bool m_updating{false};
};

void RegisterRNCPickerComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const& packageBuilder) noexcept;

} // namespace winrt::Picker::implementation

#endif // RNW_NEW_ARCH



