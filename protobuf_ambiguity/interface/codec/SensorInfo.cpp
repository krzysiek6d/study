#include <sensor_data.pb.h>
#include <codec/SensorInfo.hpp>

std::string encode(const SensorInfo& sensorInfo)
{
    auto sensor_info_proto = adet::SensorInfo();
    sensor_info_proto.set_name(sensorInfo.name);
    auto* details_proto = new adet::Details();
    details_proto->set_time(sensorInfo.data.time);
    details_proto->set_value1(sensorInfo.data.value1);
    details_proto->set_value2(sensorInfo.data.value2);
    details_proto->set_description(sensorInfo.data.description);
    sensor_info_proto.set_allocated_data(details_proto);
    return sensor_info_proto.SerializeAsString();
}

void decode(std::string payload, SensorInfo& sensorInfo)
{
    adet::SensorInfo sensor_info_proto;
    sensor_info_proto.ParseFromString(payload);
    sensorInfo.name = sensor_info_proto.name();
    sensorInfo.data.time = sensor_info_proto.data().time();
    sensorInfo.data.value1 = sensor_info_proto.data().value1();
    sensorInfo.data.value2 = sensor_info_proto.data().value2();
    sensorInfo.data.description = sensor_info_proto.data().description();
}