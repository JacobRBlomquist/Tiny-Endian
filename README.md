# C++ Header-Only Int and Float Endianness Library
This library was created in order to efficiently write to binary file formats
that contain data that is **_endian sensitive_**. 

## Usage Example:
```c++
#include <fstream>
#include <iostream>
#include "tinyEndian.hpp"

int main()
{
    double value = 1.23456;
    tinyEndian::Float64 float64 = value;

	//Outputs a Double
    double bigEndianDouble = float64.Big();
    double littleEndianDouble = float64.Little();

    std::cout << "Value: " << value << "\nBigEndian: " 
      << bigEndianDouble << "\nLittleEndian: " << littleEndianDouble << std::endl;

    std::cout << "Your architecture is: " 
      << (tinyEndian::Arch_Is_Big_Endian() ? "Big Endian" : "Little Endian");

    std::ofstream out("out.dat", std::ofstream::binary);

    out.write(float64.BigAsBytes(), 8);

    out.close();

    return 0;
}
```
Standard out:
```
Value: 1.23456
BigEndian: 1.23456
LittleEndian: 5.45501e-038
Your architecture is: Little Endian
```
Hex contents of `out.dat`.
```
 3F F3 C0 C1 FC 8F 32 38
```
## Features:
The following types are currently supported:
* Int16
* Int32
* Int64
* Float32
* Float64

There is also a static function `tinyEndian::Arch_Is_Big_Endian()` which determines the endianness of the current architecture.

Each type is of the same size as its container type (tinyEndian::Int64 is 8 bytes, etc). This will allow
tinyEndian object to be stored in datastructures without any space overhead.
