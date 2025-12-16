/**
 * Copyright (c) Microsoft Corporation.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow strict-local
 * @format
 */

'use strict';

import type {ColorValue} from 'react-native/Libraries/StyleSheet/StyleSheet';
import type {ViewProps} from 'react-native/Libraries/Components/View/ViewPropTypes';
import type {HostComponent} from 'react-native/Libraries/Renderer/shims/ReactNativeTypes';
import type {
  BubblingEventHandler,
  Int32,
} from 'react-native/Libraries/Types/CodegenTypes';

import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';

type RNCPickerWindowsChangeEvent = $ReadOnly<{|
  itemIndex: Int32,
  value: ?string,
  text: ?string,
|}>;

type RNCPickerWindowsItem = $ReadOnly<{|
  label: string,
  value: ?string,
  textColor: ?ColorValue,
  testID: ?string,
|}>;

export type NativeProps = $ReadOnly<{|
  ...ViewProps,
  items: $ReadOnlyArray<RNCPickerWindowsItem>,
  selectedIndex: Int32,
  enabled?: ?boolean,
  placeholder?: ?string,
  testID?: ?string,
  accessibilityLabel?: ?string,
  onChange?: BubblingEventHandler<RNCPickerWindowsChangeEvent>,
|}>;

export default (codegenNativeComponent<NativeProps>('RNCPicker', {
  excludedPlatforms: ['iOS', 'android'],
}): HostComponent<NativeProps>);
