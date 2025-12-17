// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "RNCPickerComponentView.h"
#include <limits>

namespace winrt::Picker::implementation {

#ifdef RNW_NEW_ARCH
// Static member definitions
std::mutex RNCPickerComponentView::s_instancesMutex;
std::vector<RNCPickerComponentView*> RNCPickerComponentView::s_instances;

RNCPickerComponentView::RNCPickerComponentView() {
  RegisterInstance(this);
}

RNCPickerComponentView::~RNCPickerComponentView() {
  UnregisterInstance(this);
}

void RNCPickerComponentView::RegisterInstance(RNCPickerComponentView* instance) {
  std::lock_guard<std::mutex> lock(s_instancesMutex);
  s_instances.push_back(instance);
}

void RNCPickerComponentView::UnregisterInstance(RNCPickerComponentView* instance) {
  std::lock_guard<std::mutex> lock(s_instancesMutex);
  s_instances.erase(
    std::remove(s_instances.begin(), s_instances.end(), instance),
    s_instances.end());
}

bool RNCPickerComponentView::OpenPicker() {
  std::lock_guard<std::mutex> lock(s_instancesMutex);
  if (!s_instances.empty()) {
    // Open the most recently created picker
    return s_instances.back()->Open();
  }
  return false;
}

bool RNCPickerComponentView::ClosePicker() {
  std::lock_guard<std::mutex> lock(s_instancesMutex);
  if (!s_instances.empty()) {
    // Close the most recently created picker
    return s_instances.back()->Close();
  }
  return false;
}

bool RNCPickerComponentView::Open() {
  try {
    if (m_comboBox) {
      m_comboBox.IsDropDownOpen(true);
      return true;
    }
  } catch (...) {
    // Ignore exceptions during open
  }
  return false;
}

bool RNCPickerComponentView::Close() {
  try {
    if (m_comboBox) {
      m_comboBox.IsDropDownOpen(false);
      return true;
    }
  } catch (...) {
    // Ignore exceptions during close
  }
  return false;
}
#endif // RNW_NEW_ARCH

void RegisterRNCPickerComponentView(
  winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) noexcept {
#ifdef RNW_NEW_ARCH
  PickerCodegen::RegisterRNCPickerNativeComponent<winrt::Picker::implementation::RNCPickerComponentView>(
    packageBuilder,
    [](const winrt::Microsoft::ReactNative::Composition::IReactCompositionViewComponentBuilder &builder) {
      builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().XamlSupport(true);
      // Use SetContentIslandComponentViewInitializer
      builder.SetContentIslandComponentViewInitializer(
        [](const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept {
          auto userData = winrt::make_self<winrt::Picker::implementation::RNCPickerComponentView>();
          userData->InitializeContentIsland(islandView);
          islandView.UserData(*userData);
        });
      // Set up initial state with zero size
      builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().SetInitialStateDataFactory(
        [](const winrt::Microsoft::ReactNative::IComponentProps& /*props*/) noexcept {
          return winrt::make<RNCPickerStateData>(winrt::Windows::Foundation::Size{ 0, 0 });
        });

      // Register the measure function - reads from state
      builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().SetMeasureContentHandler(
        [](winrt::Microsoft::ReactNative::ShadowNode const& shadowNode,
           winrt::Microsoft::ReactNative::LayoutContext const& ,
           winrt::Microsoft::ReactNative::LayoutConstraints const&) noexcept {

          auto currentState = winrt::get_self<RNCPickerStateData>(shadowNode.StateData());

          if (currentState && currentState->desiredSize.Width > 0) {
            // Return the measured size from state
            return currentState->desiredSize;
          }

          // Return a default size if we don't have a measurement yet
          return winrt::Windows::Foundation::Size{ 100, 32 };
        });

      // Handle state updates
      builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().SetUpdateStateHandler(
        [](const winrt::Microsoft::ReactNative::ComponentView& view,
           const winrt::Microsoft::ReactNative::IComponentState& newState) {
          auto islandView = view.as<winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView>();
          auto userData = islandView.UserData().as<winrt::Picker::implementation::RNCPickerComponentView>();
          userData->UpdateState(view, newState);
        });
    });
#endif
}

#ifdef RNW_NEW_ARCH
void RNCPickerComponentView::InitializeContentIsland(
  const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) {
  // Create ComboBox for picker functionality
  m_comboBox = winrt::Microsoft::UI::Xaml::Controls::ComboBox();
  m_comboBox.HorizontalAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Stretch);

  // Listen for size changes on the comboBox
  m_comboBox.SizeChanged([this](auto const& /*sender*/, auto const& /*args*/) {
    RefreshSize();
  });

  // Listen for selection changes
  m_selectionChangedToken = m_comboBox.SelectionChanged([this](auto const& sender, auto const& /*args*/) {
    if (m_updating) {
      return;
    }

    if (auto eventEmitter = this->EventEmitter()) {
      auto cb = sender.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
      int32_t selectedIndex = cb.SelectedIndex();

      PickerCodegen::RNCPicker_OnPickerSelect eventArgs;
      eventArgs.itemIndex = selectedIndex;
      
      // Get the selected item value if available
      if (selectedIndex >= 0 && selectedIndex < static_cast<int32_t>(m_items.size())) {
        eventArgs.value = m_items[selectedIndex].value.value_or("");
        eventArgs.text = m_items[selectedIndex].label;
      }
      
      eventEmitter->onPickerSelect(eventArgs);
    }
  });

  m_island = winrt::Microsoft::UI::Xaml::XamlIsland{};
  m_island.Content(m_comboBox);
  islandView.Connect(m_island.ContentIsland());
  m_islandView = winrt::make_weak(islandView);
}

void RNCPickerComponentView::UpdateProps(
  const winrt::Microsoft::ReactNative::ComponentView &view,
  const winrt::com_ptr<PickerCodegen::RNCPickerProps> &newProps,
  const winrt::com_ptr<PickerCodegen::RNCPickerProps> &oldProps) noexcept {
  BaseRNCPicker::UpdateProps(view, newProps, oldProps);
  
  if (!m_comboBox) {
    return;
  }
  
  m_updating = true;

  // Update enabled state
  m_comboBox.IsEnabled(newProps->enabled);

  // Update placeholder text
  if (newProps->placeholder.has_value()) {
    m_comboBox.PlaceholderText(winrt::to_hstring(newProps->placeholder.value()));
  }

  // Update items
  m_comboBox.Items().Clear();
  m_items.clear();
  
  for (const auto& item : newProps->items) {
    // Store item data
    m_items.push_back(item);
    
    // Create ComboBoxItem
    auto comboBoxItem = winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem();
    comboBoxItem.Content(winrt::box_value(winrt::to_hstring(item.label)));
    
    // Set testID if provided
    if (item.testID.has_value()) {
      comboBoxItem.Name(winrt::to_hstring(item.testID.value()));
    }
    
    m_comboBox.Items().Append(comboBoxItem);
  }

  // Update selected index
  int32_t selectedIndex = newProps->selectedIndex;
  if (selectedIndex >= 0 && selectedIndex < static_cast<int32_t>(m_comboBox.Items().Size())) {
    m_comboBox.SelectedIndex(selectedIndex);
  }

  m_updating = false;
  
  RefreshSize();
}

// Measure comboBox with new content and update state if needed.
void RNCPickerComponentView::RefreshSize() {
  if (!m_comboBox) {
    return;
  }
  
  m_comboBox.Measure(winrt::Windows::Foundation::Size{
      std::numeric_limits<float>::infinity(),
      std::numeric_limits<float>::infinity()
    });

  auto desiredSize = m_comboBox.DesiredSize();

  if (m_state) {
    auto currentState = winrt::get_self<RNCPickerStateData>(m_state.Data());
    if (desiredSize != currentState->desiredSize) {
      m_state.UpdateStateWithMutation([desiredSize](winrt::Windows::Foundation::IInspectable /*data*/) {
        return winrt::make<RNCPickerStateData>(desiredSize);
      });
    }
  }
}

void RNCPickerComponentView::UpdateState(
  const winrt::Microsoft::ReactNative::ComponentView& /*view*/,
  const winrt::Microsoft::ReactNative::IComponentState& newState) noexcept {
  m_state = newState;
}
#endif // defined(RNW_NEW_ARCH)

} // namespace winrt::Picker::implementation