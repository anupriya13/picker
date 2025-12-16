import Picker from './NativePickerModule';

export function multiply(a: number, b: number): number {
  return Picker.multiply(a, b);
}

export {default as PickerProps} from './RNCPickerNativeComponent';
export * from './RNCPickerNativeComponent';