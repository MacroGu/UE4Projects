@echo off

..\..\Protobuf\bin\protoc.exe --proto_path=. --cpp_out=. login.proto
..\..\Protobuf\bin\protoc.exe --proto_path=. --cpp_out=. scene.proto
..\..\Protobuf\bin\protoc.exe --proto_path=. --cpp_out=. entity.proto


pause