/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @format
 */

'use strict';

import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

/**
 * Native Picker TurboModule for Windows.
 * Provides native functionality for the Picker component.
 */
export interface Spec extends TurboModule {
  /**
   * Simple multiply function for testing TurboModule connection.
   * @param a First number
   * @param b Second number
   * @returns Product of a and b
   */
  multiply(a: number, b: number): number;

  /**
   * Opens the picker programmatically (if supported).
   * Returns true if the picker was opened successfully.
   */
  openPicker?(): boolean;

  /**
   * Closes the picker programmatically (if supported).
   * Returns true if the picker was closed successfully.
   */
  closePicker?(): boolean;
}

export default TurboModuleRegistry.getEnforcing<Spec>('Picker');
