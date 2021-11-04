# PCA9955B
Arduino library for the PCA9955B LED Driver

## Usage

```cpp
PCA9955B pca = PCA9955B(0x3F);

void setup() {
  pca.begin(); // Join I2C
  pca.setIRef(255); // Set current to max (defaults to 0)
  pca.setPwm(0, 255); // Set LED0 to max brightness
}

```