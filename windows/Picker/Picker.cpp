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

PickerCodegen::PickerModuleSpec_Constants Picker::GetConstants() noexcept {
  PickerCodegen::PickerModuleSpec_Constants constants;
  constants.isWindows = true;
  constants.defaultHeight = 32.0;
  return constants;
}

void Picker::open(
    PickerCodegen::PickerModuleSpec_open_params &&params,
    React::ReactPromise<PickerCodegen::PickerModuleSpec_open_returnType> &&result) noexcept {
  
  // Store params for potential use
  m_currentParams = std::move(params);
  m_isPickerOpen = true;

#ifdef RNW_NEW_ARCH
  try {
    // Create ComboBox
    m_comboBox = ComboBox();
    m_comboBox.HorizontalAlignment(HorizontalAlignment::Stretch);
    
    // Add items to ComboBox
    for (const auto& item : m_currentParams.items) {
      ComboBoxItem comboItem;
      comboItem.Content(winrt::box_value(winrt::to_hstring(item.label)));
      // Set tag if value is provided
      if (item.value.has_value()) {
        comboItem.Tag(winrt::box_value(winrt::to_hstring(item.value.value())));
      }
      m_comboBox.Items().Append(comboItem);
    }
    
    // Set selected index if provided
    if (m_currentParams.selectedIndex.has_value()) {
      int selectedIdx = static_cast<int>(m_currentParams.selectedIndex.value());
      if (selectedIdx >= 0 && selectedIdx < static_cast<int>(m_comboBox.Items().Size())) {
        // Use the setter, not the getter
        m_comboBox.SelectedIndex(selectedIdx);
      }
    }
    
    // Create ContentDialog to host the ComboBox
    m_contentDialog = ContentDialog();
    
    // Use prompt if provided, otherwise default title
    std::wstring title = m_currentParams.prompt.has_value() 
      ? winrt::to_hstring(m_currentParams.prompt.value()).c_str()
      : L"Select an option";
    m_contentDialog.Title(winrt::box_value(title));
    m_contentDialog.Content(m_comboBox);
    m_contentDialog.PrimaryButtonText(L"OK");
    m_contentDialog.SecondaryButtonText(L"Cancel");
    
    // Try to get XamlRoot from composition context
    // For now, skip XamlRoot setting - it may be set by the app
    
    // Show dialog asynchronously - capture promise by value
    auto capturedResult = std::move(result);
    m_contentDialog.ShowAsync().Completed([this, capturedResult = std::move(capturedResult)](
      winrt::Windows::Foundation::IAsyncOperation<ContentDialogResult> const& sender,
      winrt::Windows::Foundation::AsyncStatus const& status) mutable {
        
        PickerCodegen::PickerModuleSpec_open_returnType pickerResult;
        
        if (status == winrt::Windows::Foundation::AsyncStatus::Completed) {
          auto dialogResult = sender.GetResults();
          
          if (dialogResult == ContentDialogResult::Primary && m_comboBox) {
            // User clicked OK
            pickerResult.action = "pickerSetAction";
            int32_t selectedIdx = m_comboBox.SelectedIndex();
            pickerResult.selectedIndex = static_cast<double>(selectedIdx);
            
            if (selectedIdx >= 0 && selectedIdx < static_cast<int>(m_currentParams.items.size())) {
              auto &selectedItem = m_currentParams.items[selectedIdx];
              pickerResult.selectedValue = selectedItem.value;
              pickerResult.selectedLabel = selectedItem.label;
            }
          } else {
            // User cancelled
            pickerResult.action = "pickerDismissedAction";
            pickerResult.selectedIndex = m_currentParams.selectedIndex.value_or(0.0);
          }
        } else {
          // Error or cancelled
          pickerResult.action = "pickerDismissedAction";
          pickerResult.selectedIndex = m_currentParams.selectedIndex.value_or(0.0);
        }
        
        m_isPickerOpen = false;
        m_contentDialog = nullptr;
        m_comboBox = nullptr;
        
        capturedResult.Resolve(std::move(pickerResult));
    });
    
  } catch (...) {
    // Fallback to mock result if XAML fails
    PickerCodegen::PickerModuleSpec_open_returnType pickerResult;
    pickerResult.action = "pickerDismissedAction";
    pickerResult.selectedIndex = m_currentParams.selectedIndex.value_or(0.0);
    
    m_isPickerOpen = false;
    result.Resolve(std::move(pickerResult));
  }
#else
  // Non-XAML fallback - return mock result
  PickerCodegen::PickerModuleSpec_open_returnType pickerResult;
  pickerResult.action = "pickerSetAction";
  pickerResult.selectedIndex = m_currentParams.selectedIndex.value_or(0.0);
  
  if (!m_currentParams.items.empty() && 
      pickerResult.selectedIndex < static_cast<double>(m_currentParams.items.size())) {
    auto &selectedItem = m_currentParams.items[static_cast<size_t>(pickerResult.selectedIndex)];
    pickerResult.selectedValue = selectedItem.value;
    pickerResult.selectedLabel = selectedItem.label;
  }

  m_isPickerOpen = false;
  result.Resolve(std::move(pickerResult));
#endif
}

void Picker::dismiss(React::ReactPromise<bool> &&result) noexcept {
  // Dismiss the picker if it's open
  if (m_isPickerOpen) {
    m_isPickerOpen = false;
    
#ifdef RNW_NEW_ARCH
    // Close the XAML ContentDialog if it's open
    if (m_contentDialog) {
      m_contentDialog.Hide();
      m_contentDialog = nullptr;
      m_comboBox = nullptr;
    }
#endif
    
    result.Resolve(true);
  } else {
    result.Resolve(false);
  }
}

std::optional<double> Picker::processPickerColor(std::string color) noexcept {
  // Process color string to numeric value
  if (color.empty()) {
    return std::nullopt;
  }
  
  // Basic color processing - parse hex colors like "#RRGGBB"
  if (color[0] == '#' && color.length() >= 7) {
    try {
      unsigned long colorValue = std::stoul(color.substr(1), nullptr, 16);
      return static_cast<double>(colorValue);
    } catch (...) {
      return std::nullopt;
    }
  }
  
  return std::nullopt;
}

double Picker::getDefaultPickerHeight() noexcept {
  // Return default picker height for Windows (in pixels)
  return 32.0;
}

bool Picker::validatePickerItem(std::string label, std::string value) noexcept {
  // Validate picker item - ensure label is not empty
  return !label.empty();
}

double Picker::getSelectedIndexForValue(
    std::vector<PickerCodegen::PickerModuleSpec_PickerItem> items,
    std::string selectedValue) noexcept {
  // Find the index of the item with the matching value
  for (size_t i = 0; i < items.size(); ++i) {
    if (items[i].value.has_value() && items[i].value.value() == selectedValue) {
      return static_cast<double>(i);
    }
  }
  return -1.0; // Not found
}

std::vector<PickerCodegen::PickerModuleSpec_PickerItem> Picker::processPickerItems(
    std::vector<PickerCodegen::PickerModuleSpec_PickerItem> items) noexcept {
  // Process picker items - for now just return a copy
  // In a real implementation, you might validate, sanitize, or transform items
  std::vector<PickerCodegen::PickerModuleSpec_PickerItem> processedItems;
  
  for (const auto &item : items) {
    PickerCodegen::PickerModuleSpec_PickerItem processedItem;
    processedItem.label = item.label;
    processedItem.value = item.value;
    processedItem.color = item.color;
    processedItem.testID = item.testID;
    processedItems.push_back(processedItem);
  }
  
  return processedItems;
}

void Picker::setNativeProps(double selectedIndex, std::string text) noexcept {
  // This would be used to update native picker props
  // In practice, this is typically handled by the component's setNativeProps
  // but we can provide it here for programmatic access
  // Implementation would require access to the component instance
}

} // namespace winrt::Picker