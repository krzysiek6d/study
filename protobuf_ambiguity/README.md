This example shows that protobuf without proto file sometimes can be ambiguous

because of ambiguity of "xEpRhRHOPRX!" can be decoded in 2 ways:
- as a string "xEpRhRHOPRX!"
- or as a structure of numbers:
     - x -> variant with fieldNo 15  + 69 as a value of that field (E is 69 in ASCII)
     - p -> variant with fieldNo 14  + 82 as a value of that field (R is 82 in ASCII)
     - h -> variant with fieldNo 13  + 82 as a value of that field (R is 82 in ASCII)
     - H -> variant with fieldNo 9   + 79 as a value of that field (O is 79 in ASCII)
     - P -> variant with fieldNo 10  + 82 as a value of that field (R is 82 in ASCII)
     - X -> variant with fieldNo 11  + 33 as a value of that field (! is 33 in ASCII)

you can check ambiguous values using findAsciiThatCanBeAmbigious.

In such cases protoc --decode will decode it as a structure, but you can pass proto file to decode it properly

Some useful commands if you want to do some experiments:
```
proto_example | protoc --decode_raw
proto_example | protoc --decode=adet.SensorInfo <PROJECT_PATH>/interface/protobuf/sensor_data.proto  --proto_path=<PROJECT_PATH>/interface/protobuf/
proto_example | xxd -ps | xxd -r -p | protoc --decode_raw
proto_example | xxd -ps
```

information about encoding:
https://developers.google.com/protocol-buffers/docs/encoding
