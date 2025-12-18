/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @format
 */

import NativePickerModule from './NativePickerModule';

/**
 * Simple multiply function for testing TurboModule connection.
 * @param a First number
 * @param b Second number
 * @returns Product of a and b
 */
export function multiply(a: number, b: number): number {
  return NativePickerModule.multiply(a, b);
}

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