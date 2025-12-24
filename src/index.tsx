/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @format
 */

// Export the native component and its types
export { default as RNCPicker } from './RNCPickerNativeComponent';
export type {
  RNCPickerProps,
  RNCPickerItem,
  RNCPickerChangeEvent,
} from './RNCPickerNativeComponent';

// Re-export the native module for direct access
export { default as NativePickerModule } from './NativePickerModule';
export type { Spec as NativePickerModuleSpec } from './NativePickerModule';