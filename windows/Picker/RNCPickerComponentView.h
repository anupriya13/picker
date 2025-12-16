// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#ifdef RNW_NEW_ARCH

#include "codegen/NativePickerModuleSpec.g.h"

#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Microsoft.ReactNative.Composition.h>
#include <winrt/Microsoft.ReactNative.Composition.Experimental.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.h>

namespace winrt::Picker::implementation {

// State to store the measured size
struct PickerStateData : winrt::implements<PickerStateData, winrt::IInspectable> {
  PickerStateData(winrt::Windows::Foundation::Size ds) : desiredSize(ds) {}
  winrt::Windows::Foundation::Size desiredSize;
};

// Alias for state data
using RNCPickerStateData = PickerStateData;

struct RNCPickerComponentView : winrt::implements<RNCPickerComponentView, winrt::IInspectable>,
                                  PickerCodegen::BasePicker<RNCPickerComponentView> {
  void InitializeContentIsland(
    const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView);

  void UpdateProps(
    const winrt::Microsoft::ReactNative::ComponentView &/*view*/,
    const winrt::com_ptr<PickerCodegen::PickerProps> &newProps,
    const winrt::com_ptr<PickerCodegen::PickerProps> &oldProps) noexcept override;

  void UpdateState(
    const winrt::Microsoft::ReactNative::ComponentView &/*view*/,
    const winrt::Microsoft::ReactNative::IComponentState &newState) noexcept override;

private:
  void RefreshSize();

  winrt::weak_ref<winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView> m_islandView;
  winrt::Microsoft::UI::Xaml::XamlIsland m_island{nullptr};
  winrt::Microsoft::ReactNative::IComponentState m_state{ nullptr };
  std::vector<PickerCodegen::PickerModuleSpec_PickerItem> m_items;
  bool m_updating = false;
  winrt::event_token m_selectionChangedToken;
};

void RegisterRNCPickerComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const& packageBuilder) noexcept;

} // namespace winrt::Picker::implementation

#endif // RNW_NEW_ARCH



