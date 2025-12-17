import * as React from 'react';
import {View, Text, Button, StyleSheet} from 'react-native';
import {Picker} from '@react-native-picker/picker';
import {multiply} from '@react-native-picker/picker/src';

const Item = Picker.Item;

// Example 1: Basic Picker with Placeholder
function PlaceholderPickerExample() {
  const [value, setValue] = React.useState(null);
  return (
    <View>
      <Picker
        placeholder="Select a value"
        selectedValue={value}
        onValueChange={(v) => setValue(v)}
        accessibilityLabel="Placeholder Picker"
      >
        <Item label="hello" value="key0" />
        <Item label="world" value="key1" />
      </Picker>
      <Text>Selected: {value || 'None'}</Text>
    </View>
  );
}

// Example 2: Basic Picker with Value Change
function BasicPickerExample() {
  const [value, setValue] = React.useState('key1');
  return (
    <View>
      <Picker
        testID="basic-picker-windows"
        selectedValue={value}
        onValueChange={(v, index) => {
          console.log(`Selected: ${v} at index ${index}`);
          setValue(v);
        }}
        accessibilityLabel="Basic Picker"
      >
        <Item label="Option 1" value="key0" />
        <Item label="Option 2" value="key1" />
        <Item label="Option 3" value="key2" />
      </Picker>
      <Text>Selected: {value}</Text>
    </View>
  );
}

// Example 3: Disabled Picker
function DisabledPickerExample() {
  const [value] = React.useState('key1');
  return (
    <View>
      <Picker
        enabled={false}
        selectedValue={value}
        accessibilityLabel="Disabled Picker"
      >
        <Item label="Cannot change" value="key0" />
        <Item label="This is selected" value="key1" />
      </Picker>
      <Text>This picker is disabled</Text>
    </View>
  );
}

// Example 4: Styled Picker with Colors
function StyledPickerExample() {
  const [value, setValue] = React.useState('red');
  return (
    <View>
      <Picker
        selectedValue={value}
        onValueChange={(v) => setValue(v)}
        style={styles.styledPicker}
        accessibilityLabel="Styled Picker"
      >
        <Item label="Red" value="red" color="red" />
        <Item label="Green" value="green" color="green" />
        <Item label="Blue" value="blue" color="blue" />
      </Picker>
      <Text style={{color: value}}>Selected color: {value}</Text>
    </View>
  );
}

// Example 5: Picker with Many Items
function ManyItemsPickerExample() {
  const [value, setValue] = React.useState('5');
  const items = Array.from({length: 20}, (_, i) => ({
    label: `Item ${i + 1}`,
    value: `${i + 1}`,
  }));

  return (
    <View>
      <Picker
        selectedValue={value}
        onValueChange={(v) => setValue(v)}
        accessibilityLabel="Many Items Picker"
      >
        {items.map((item) => (
          <Item key={item.value} label={item.label} value={item.value} />
        ))}
      </Picker>
      <Text>Selected: Item {value}</Text>
    </View>
  );
}

// Example 6: TurboModule Test - multiply function
function TurboModuleTestExample() {
  const [result, setResult] = React.useState(null);
  const [a, setA] = React.useState('3');
  const [b, setB] = React.useState('7');

  const handleMultiply = () => {
    try {
      const numA = parseInt(a, 10);
      const numB = parseInt(b, 10);
      const res = multiply(numA, numB);
      setResult(res);
    } catch (error) {
      console.error('Error calling multiply:', error);
      setResult('Error');
    }
  };

  return (
    <View>
      <Text style={styles.label}>TurboModule: multiply(a, b)</Text>
      <View style={styles.row}>
        <Text>a = </Text>
        <Picker
          selectedValue={a}
          onValueChange={(v) => setA(v)}
          style={styles.numberPicker}
        >
          {[1, 2, 3, 4, 5, 6, 7, 8, 9, 10].map((n) => (
            <Item key={n} label={`${n}`} value={`${n}`} />
          ))}
        </Picker>
        <Text> × b = </Text>
        <Picker
          selectedValue={b}
          onValueChange={(v) => setB(v)}
          style={styles.numberPicker}
        >
          {[1, 2, 3, 4, 5, 6, 7, 8, 9, 10].map((n) => (
            <Item key={n} label={`${n}`} value={`${n}`} />
          ))}
        </Picker>
      </View>
      <Button title="Calculate" onPress={handleMultiply} />
      <Text style={styles.result}>
        Result: {result !== null ? result : 'Press Calculate'}
      </Text>
    </View>
  );
}

// Example 7: Picker with TestID
function TestIDPickerExample() {
  const [value, setValue] = React.useState('opt1');
  return (
    <View>
      <Picker
        testID="testid-picker"
        selectedValue={value}
        onValueChange={(v) => setValue(v)}
        accessibilityLabel="TestID Picker for E2E testing"
      >
        <Item label="Option A" value="opt1" testID="option-a" />
        <Item label="Option B" value="opt2" testID="option-b" />
        <Item label="Option C" value="opt3" testID="option-c" />
      </Picker>
      <Text>Selected: {value}</Text>
    </View>
  );
}

// Example 8: Dynamic Items Picker
function DynamicItemsPickerExample() {
  const [value, setValue] = React.useState('');
  const [items, setItems] = React.useState([
    {label: 'Apple', value: 'apple'},
    {label: 'Banana', value: 'banana'},
  ]);

  const addItem = () => {
    const fruits = ['Cherry', 'Date', 'Elderberry', 'Fig', 'Grape', 'Honeydew'];
    const newFruit = fruits[items.length % fruits.length];
    setItems([...items, {label: newFruit, value: newFruit.toLowerCase()}]);
  };

  const removeItem = () => {
    if (items.length > 1) {
      const newItems = items.slice(0, -1);
      setItems(newItems);
      if (!newItems.find((i) => i.value === value)) {
        setValue(newItems[0]?.value || '');
      }
    }
  };

  return (
    <View>
      <Picker
        selectedValue={value}
        onValueChange={(v) => setValue(v)}
        placeholder="Select a fruit"
        accessibilityLabel="Dynamic Items Picker"
      >
        {items.map((item) => (
          <Item key={item.value} label={item.label} value={item.value} />
        ))}
      </Picker>
      <View style={styles.buttonRow}>
        <Button title="Add Item" onPress={addItem} />
        <Button title="Remove Item" onPress={removeItem} />
      </View>
      <Text>Items count: {items.length}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  styledPicker: {
    backgroundColor: '#f0f0f0',
  },
  numberPicker: {
    width: 80,
  },
  row: {
    flexDirection: 'row',
    alignItems: 'center',
    marginVertical: 10,
  },
  buttonRow: {
    flexDirection: 'row',
    justifyContent: 'space-around',
    marginTop: 10,
  },
  label: {
    fontSize: 16,
    fontWeight: 'bold',
    marginBottom: 10,
  },
  result: {
    fontSize: 18,
    marginTop: 10,
    color: '#007AFF',
  },
});

export const examples = [
  {
    title: 'Picker with placeholder',
    render: PlaceholderPickerExample,
  },
  {
    title: 'Basic Picker',
    render: BasicPickerExample,
  },
  {
    title: 'Disabled Picker',
    render: DisabledPickerExample,
  },
  {
    title: 'Styled Picker with Colors',
    render: StyledPickerExample,
  },
  {
    title: 'Picker with Many Items',
    render: ManyItemsPickerExample,
  },
  {
    title: 'TurboModule Test (multiply)',
    render: TurboModuleTestExample,
  },
  {
    title: 'Picker with TestID',
    render: TestIDPickerExample,
  },
  {
    title: 'Dynamic Items Picker',
    render: DynamicItemsPickerExample,
  },
];
