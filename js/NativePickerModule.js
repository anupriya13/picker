/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @flow strict
 * @format
 */

'use strict';

import type {TurboModule} from 'react-native/Libraries/TurboModule/RCTExport';
import {TurboModuleRegistry} from 'react-native';

export type PickerItem = {|
  label: string,
  value?: string,
  color?: string,
  testID?: string,
|};

export type PickerOpenParams = $ReadOnly<{|
  items: Array<PickerItem>,
  selectedIndex?: number,
  enabled?: boolean,
  prompt?: string,
  placeholder?: string,
  testID?: string,
  accessibilityLabel?: string,
|}>;

type PickerSetAction = 'pickerSetAction' | 'dismissedAction';

export type PickerResult = $ReadOnly<{|
  action: PickerSetAction,
  selectedIndex: number,
  selectedValue?: string,
  selectedLabel?: string,
|}>;

export interface Spec extends TurboModule {
  // Get platform-specific constants
  +getConstants: () => {|
    +isWindows?: boolean,
    +defaultHeight?: number,
  |};
  
  // Open picker dialog (Windows-specific)
  +open: (params: PickerOpenParams) => Promise<PickerResult>;
  
  // Dismiss picker dialog
  +dismiss: () => Promise<boolean>;
  
  // Process color value for picker items
  +processPickerColor?: (color?: string) => ?number;
  
  // Get default picker height for the platform
  +getDefaultPickerHeight?: () => number;
  
  // Validate picker item
  +validatePickerItem?: (label: string, value?: string) => boolean;
  
  // Get selected index from value
  +getSelectedIndexForValue?: (items: Array<PickerItem>, selectedValue?: string) => number;
  
  // Process picker items
  +processPickerItems?: (items: Array<PickerItem>) => Array<PickerItem>;
  
  // Set native props (for updating picker state)
  +setNativeProps?: (selectedIndex: number, text?: string) => void;
}

export default (TurboModuleRegistry.get<Spec>('RNCPickerWindows'): ?Spec);
