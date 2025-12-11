// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"

#include "PickerFabric.h"

#if defined(RNW_NEW_ARCH)

#include "codegen/react/components/Picker/Picker.g.h"

#include <winrt/Microsoft.ReactNative.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>

namespace winrt::Picker {

// PickerComponentView implements the Fabric architecture for
// Picker using XAML ComboBox hosted in a XamlIsland
struct PickerComponentView
    : public winrt::
          implements<PickerComponentView, winrt::IInspectable>,
      Codegen::BasePicker<PickerComponentView> {
  void InitializeContentIsland(
      const winrt::Microsoft::ReactNative::Composition::
          ContentIslandComponentView& islandView) noexcept {
    m_xamlIsland = winrt::Microsoft::UI::Xaml::XamlIsland{};
    m_comboBox = winrt::Microsoft::UI::Xaml::Controls::ComboBox{};
    islandView.Connect(m_xamlIsland.ContentIsland());

    RegisterEvents();

    // Mount the ComboBox immediately so it's visible
    m_xamlIsland.Content(m_comboBox);
  }

  void MountChildComponentView(
      const winrt::Microsoft::ReactNative::ComponentView& childView,
      uint32_t index) noexcept {
    // Mount the ComboBox into the XamlIsland
    m_xamlIsland.Content(m_comboBox);
  }

  void UnmountChildComponentView(
      const winrt::Microsoft::ReactNative::ComponentView& childView,
      uint32_t index) noexcept {
    // Unmount the ComboBox from the XamlIsland
    m_xamlIsland.Content(nullptr);
  }

  void RegisterEvents() {
    // Register the SelectionChanged event handler
    m_comboBox.SelectionChanged([this](auto&& sender, auto&& args) {
      if (m_updating) {
        return;
      }

      if (auto emitter = EventEmitter()) {
        auto comboBox = sender.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
        int32_t selectedIndex = comboBox.SelectedIndex();

        Codegen::Picker_OnChange eventArgs;
        eventArgs.itemIndex = selectedIndex;
        
        // Get the selected item value if available
        if (selectedIndex >= 0 && selectedIndex < static_cast<int32_t>(m_items.size())) {
          eventArgs.value = m_items[selectedIndex].value;
          eventArgs.text = m_items[selectedIndex].label;
        }
        
        emitter->onChange(eventArgs);
      }
    });
  }

  void UpdateProps(
      const winrt::Microsoft::ReactNative::ComponentView& view,
      const winrt::com_ptr<Codegen::PickerProps>& newProps,
      const winrt::com_ptr<Codegen::PickerProps>& oldProps) noexcept
      override {
    Codegen::BasePicker<PickerComponentView>::UpdateProps(
        view, newProps, oldProps);

    if (!newProps) {
      return;
    }

    m_updating = true;

    // Update enabled state
    if (newProps->enabled.has_value()) {
      m_comboBox.IsEnabled(newProps->enabled.value());
    } else {
      m_comboBox.IsEnabled(true);
    }

    // Update placeholder text
    if (newProps->placeholder.has_value()) {
      m_comboBox.PlaceholderText(
          winrt::to_hstring(newProps->placeholder.value()));
    }

    // Update items
    if (newProps->items.has_value()) {
      m_comboBox.Items().Clear();
      m_items.clear();
      
      for (const auto& item : newProps->items.value()) {
        // Store item data
        PickerItem pickerItem;
        pickerItem.label = item.label.value_or("");
        pickerItem.value = item.value;
        m_items.push_back(pickerItem);
        
        // Create ComboBoxItem
        winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem comboBoxItem;
        comboBoxItem.Content(winrt::box_value(winrt::to_hstring(pickerItem.label)));
        
        // Set color if provided
        if (item.color.has_value()) {
          // TODO: Apply color to the item
        }
        
        // Set testID if provided
        if (item.testID.has_value()) {
          comboBoxItem.Name(winrt::to_hstring(item.testID.value()));
        }
        
        m_comboBox.Items().Append(comboBoxItem);
      }
    }

    // Update selected index
    if (newProps->selectedIndex.has_value()) {
      int32_t selectedIndex = static_cast<int32_t>(newProps->selectedIndex.value());
      if (selectedIndex >= 0 && selectedIndex < static_cast<int32_t>(m_comboBox.Items().Size())) {
        m_comboBox.SelectedIndex(selectedIndex);
      }
    }

    // Update accessibilityLabel (using Name property)
    if (newProps->accessibilityLabel.has_value()) {
      m_comboBox.Name(
          winrt::to_hstring(newProps->accessibilityLabel.value()));
    }

    m_updating = false;
  }

 private:
  struct PickerItem {
    std::string label;
    std::optional<std::string> value;
  };

  winrt::Microsoft::UI::Xaml::XamlIsland m_xamlIsland{nullptr};
  winrt::Microsoft::UI::Xaml::Controls::ComboBox m_comboBox{nullptr};
  std::vector<PickerItem> m_items;
  bool m_updating = false;

};

} // namespace winrt::Picker

void RegisterPickerComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const& packageBuilder) {
  winrt::Picker::Codegen::RegisterPickerNativeComponent<
      winrt::Picker::PickerComponentView>(
      packageBuilder,
      [](const winrt::Microsoft::ReactNative::Composition::
             IReactCompositionViewComponentBuilder& builder) {
        builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>()
            .XamlSupport(true);
        builder.SetContentIslandComponentViewInitializer(
            [](const winrt::Microsoft::ReactNative::Composition::
                   ContentIslandComponentView& islandView) noexcept {
              auto userData = winrt::make_self<
                  winrt::Picker::PickerComponentView>();
              userData->InitializeContentIsland(islandView);
              islandView.UserData(*userData);
            });

        builder.SetMountChildComponentViewHandler(
            [](const winrt::Microsoft::ReactNative::ComponentView& view,
               const winrt::Microsoft::ReactNative::ComponentView& childView,
               uint32_t index) noexcept {
              auto userData =
                  view.UserData()
                      .as<winrt::Picker::PickerComponentView>();
              userData->MountChildComponentView(childView, index);
            });

        builder.SetUnmountChildComponentViewHandler(
            [](const winrt::Microsoft::ReactNative::ComponentView& view,
               const winrt::Microsoft::ReactNative::ComponentView& childView,
               uint32_t index) noexcept {
              auto userData =
                  view.UserData()
                      .as<winrt::Picker::PickerComponentView>();
              userData->UnmountChildComponentView(childView, index);
            });
      });
}

#endif // defined(RNW_NEW_ARCH)